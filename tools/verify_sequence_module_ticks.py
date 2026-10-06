"""Run complete recovered ticks against all music loaded directly from original VF."""
import argparse, ctypes, json, subprocess
from pathlib import Path
from verify_sequence_tick import Song, Sequence, Global, Row, Column, Memory, Extended, Playback, Publication, Reader
from verify_sequence_start import Header
from verify_mixer_attach import Binding
Callback = ctypes.CFUNCTYPE(None, ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('music', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--ticks', type=int, default=2048)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'module-ticks.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    n = ctypes.CDLL(str(library))
    n.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    n.vertrix_vf_open.restype = ctypes.c_void_p
    n.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    n.vertrix_sequence_module_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint8, ctypes.c_void_p]
    n.vertrix_sequence_module_load.restype = ctypes.c_void_p
    n.vertrix_sequence_module_free.argtypes = [ctypes.c_void_p]
    n.vertrix_sequence_module_header.argtypes = [ctypes.c_void_p]
    n.vertrix_sequence_module_header.restype = ctypes.POINTER(Header)
    n.vertrix_sequence_module_song.argtypes = [ctypes.c_void_p]
    n.vertrix_sequence_module_song.restype = ctypes.POINTER(Song)
    n.vertrix_sequence_module_bindings.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t)]
    n.vertrix_sequence_module_bindings.restype = ctypes.POINTER(Binding)
    n.vertrix_sequence_start.argtypes = [ctypes.POINTER(Header), ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Sequence), ctypes.POINTER(Global), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(Reader), ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory), ctypes.POINTER(Extended), ctypes.POINTER(Playback), ctypes.c_size_t, ctypes.POINTER(Publication), ctypes.POINTER(ctypes.c_uint32)]
    n.vertrix_sequence_tick.argtypes = [ctypes.POINTER(Song), ctypes.POINTER(Sequence), ctypes.POINTER(Global), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(Reader), ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory), ctypes.POINTER(Extended), ctypes.POINTER(Playback), ctypes.c_size_t, ctypes.POINTER(Publication), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_int), Callback, ctypes.c_void_p]
    modules = []
    total_ticks = total_commands = 0
    for path in sorted(args.music.glob('*.xm')):
        vf = n.vertrix_vf_open(str(args.archive.resolve()).encode())
        assert vf
        try:
            module = n.vertrix_sequence_module_load(vf, ('musique/' + path.name).encode(), 0, None)
            assert module, path.name
        finally:
            n.vertrix_vf_close(vf)
        try:
            header = n.vertrix_sequence_module_header(module)
            song = n.vertrix_sequence_module_song(module)
            channels = header.contents.channels
            sequence = Sequence()
            global_state = Global()
            delay = ctypes.c_uint32()
            reader = Reader()
            tempo = ctypes.c_uint32()
            changed = ctypes.c_int()
            rows = (Row * channels)()
            columns = (Column * channels)()
            memory = (Memory * channels)()
            extended = (Extended * channels)()
            playback = (Playback * channels)()
            publication = (Publication * channels)()
            assert not n.vertrix_sequence_start(
                header, None, ctypes.byref(sequence), ctypes.byref(global_state),
                ctypes.byref(delay), ctypes.byref(reader), rows, columns, memory, extended,
                playback, channels, publication, ctypes.byref(tempo))
            count = ctypes.c_size_t()
            bindings = n.vertrix_sequence_module_bindings(module, ctypes.byref(count))
            callback = Callback()
            orders = set()
            ticks = commands = 0
            for tick in range(args.ticks):
                result = n.vertrix_sequence_tick(
                    song, ctypes.byref(sequence), ctypes.byref(global_state), ctypes.byref(delay),
                    ctypes.byref(reader), rows, columns, memory, extended, playback, channels,
                    publication, ctypes.byref(tempo), ctypes.byref(changed), callback, None)
                assert result >= 0, (path.name, tick, sequence.order, sequence.row, result)
                if not result:
                    break
                ticks += 1
                orders.add(sequence.order)
                for ci in range(channels):
                    assert not rows[ci].selection.flags and not playback[ci].vibrato.flags
                    for j in range(publication[ci].count):
                        command = publication[ci].commands[j]
                        assert command.kind <= 6
                        if command.kind == 0:
                            assert 1 <= command.value <= count.value
                        commands += 1
            modules.append({
                'name': path.name,
                'ticks': ticks,
                'orders_visited': len(orders),
                'commands': commands,
                'stopped': bool(sequence.flags & 32)
            })
            total_ticks += ticks
            total_commands += commands
        finally:
            n.vertrix_sequence_module_free(module)
    report = {
        'status': 'passed',
        'modules': len(modules),
        'executed_ticks': total_ticks,
        'emitted_commands': total_commands,
        'songs': modules,
        'scope': 'Complete native startup/ticks over all original VF-loaded modules after archive closure; row/effect/envelope execution and bounded sample handles. Each song runs up to requested ticks. Underlying routines and synthetic complete ticks have original-executable proofs; this run is a native real-resource integration check, not an end-to-end x86 differential comparison. Excludes mixer command execution and audio.'
    }
    (build / 'sequence-module-ticks-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k != 'songs'}, indent=2))


if __name__ == '__main__':
    main()

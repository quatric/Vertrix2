"""Run complete recovered ticks against all music loaded directly from original VF."""
import argparse, ctypes, json, subprocess, struct
from original import Original, MASK, BOARD, STACK
from verify_sequence_tick import SN, SO, NAMES, OFFSETS, reconstruct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_EIP
from pathlib import Path
from verify_sequence_tick import Song, Sequence, Global, Row, Column, Memory, Extended, Playback, Publication, Reader
from verify_sequence_start import Header
from verify_mixer_attach import Binding
from verify_mixer_channel import Channel
from verify_xm_samples import decode
Pointer = ctypes.POINTER(ctypes.c_uint8)
Callback = ctypes.CFUNCTYPE(None, ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p)


def original_song(original, data):
    cursor = 0x900000

    def allocate(size):
        nonlocal cursor
        result = cursor
        cursor += (size + 3) & ~3
        return result

    length, restart, channels, patterns, instruments, flags, speed, bpm = struct.unpack_from(
        '<8H', data, 64)
    song = bytearray(344)
    struct.pack_into('<8H', song, 32, flags & 1, length, restart, channels, patterns, instruments,
                     speed, bpm)
    song[48:48 + length] = data[80:80 + length]
    song[304:304 + channels] = bytes([127]) * channels
    pattern_base = allocate(patterns * 12)
    pattern_records = bytearray(patterns * 12)
    offset = 60 + struct.unpack_from('<I', data, 60)[0]
    packed_addresses = []
    for index in range(patterns):
        size = struct.unpack_from('<I', data, offset)[0]
        rows, packed = struct.unpack_from('<HH', data, offset + 5)
        offset += size
        pointer = allocate(packed) if packed else 0
        if packed:
            original.cpu.mem_write(pointer, data[offset:offset + packed])
        struct.pack_into('<H', pattern_records, index * 12 + 4, rows)
        struct.pack_into('<I', pattern_records, index * 12 + 8, pointer)
        packed_addresses.append(pointer)
        offset += packed
    original.cpu.mem_write(pattern_base, bytes(pattern_records))
    instrument_base = allocate(instruments * 252)
    sample_bases = []
    sample_handles = {}
    pcm_addresses = []
    first = 0
    scratch = bytearray(243)
    frame = STACK + 512
    for index in range(instruments):
        size = struct.unpack_from('<I', data, offset)[0]
        count = struct.unpack_from('<H', data, offset + 27)[0]
        header = data[offset:offset + size]
        if count:
            scratch[:] = header[:243]
        else:
            scratch[:29] = header[:29]
        original.cpu.mem_write(0x5326d1, bytes(scratch))
        original.cpu.mem_write(BOARD, bytes(252))
        original.cpu.mem_write(frame - 16, struct.pack('<I', BOARD))
        original.cpu.mem_write(frame - 24, struct.pack('<I', MASK))
        original.cpu.reg_write(UC_X86_REG_EBP, frame)
        original.call(0x4117e0, stop=0x411a00)
        instrument = bytearray(original.cpu.mem_read(BOARD, 252))
        scratch[:] = original.cpu.mem_read(0x5326d1, 243)
        sample_base = allocate(count * 60) if count else 0
        sample_bases.append(sample_base)
        struct.pack_into('<I', instrument, 248, sample_base)
        original.cpu.mem_write(instrument_base + index * 252, bytes(instrument))
        sample_header = struct.unpack_from('<I', header, 29)[0] if count else 0
        offset += size
        payload = offset + count * sample_header
        for sample in range(count):
            h = data[offset + sample * sample_header:offset + sample * sample_header + 40]
            record = bytearray(60)
            record[32:36] = bytes((h[12], h[15], h[16], h[13]))
            pointer = sample_base + sample * 60
            size, start, loop = struct.unpack_from('<III', h)
            sample_flags = (1 if h[14] & 16 else 0) | (16 if h[14] & 1 else 0) | (
                32 if h[14] & 2 else 0)
            pcm = allocate(size + 4) if size else 0
            if size:
                prepared = bytearray(decode(data[payload:payload + size], h[14] & 16)) + bytes(4)
                if sample_flags & 16:
                    prepared[start + loop:start + loop + 4] = prepared[start:start + 4]
                original.cpu.mem_write(pcm, bytes(prepared))
            struct.pack_into('<IIIIH', record, 40, pcm, size, start,
                             (start + loop) & 0xffffffff, 8363)
            record[58] = sample_flags
            original.cpu.mem_write(pointer, bytes(record))
            sample_handles[pointer] = first + 1
            pcm_addresses.append(pcm)
            first += 1
            payload += size
        offset = payload
    struct.pack_into('<II', song, 336, pattern_base, instrument_base)
    original.cpu.mem_write(MASK, bytes(song))
    return instrument_base, sample_bases, packed_addresses, sample_handles, pcm_addresses


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('music', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--ticks', type=int, default=128)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'module-pcm.dylib'
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
    n.vertrix_sequence_execute.argtypes = [ctypes.POINTER(Binding), ctypes.c_size_t, ctypes.c_uint32, ctypes.POINTER(Publication), ctypes.POINTER(Channel), ctypes.POINTER(Pointer), ctypes.c_size_t]
    n.vertrix_sequence_mix.argtypes = [ctypes.POINTER(Binding), ctypes.c_size_t, ctypes.c_uint32, ctypes.c_int, ctypes.c_int, ctypes.POINTER(Channel), ctypes.POINTER(Pointer), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int32), ctypes.c_size_t, ctypes.c_size_t]
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x1000000)
    original.cpu.mem_map(0x2000000, 0x20000)
    original.cpu.mem_map(0x2020000, 0x10000)
    original.cpu.mem_write(0x52f910, struct.pack('<I', 0x2000000))
    original.cpu.mem_write(0x52f914, struct.pack('<I', 0x2020000))
    original.cpu.mem_write(0x52fc2c, struct.pack('<I', 1))
    mixer_events = []
    tempo_events = []
    slots = []
    sample_handles = {}
    addresses = (0x40adb0, 0x40ade0, 0x40add0, 0x40adf0, 0x40ae00, 0x40ae10, 0x40adc0)
    def capture(cpu, address, size, context):
        eax = cpu.reg_read(UC_X86_REG_EAX)
        edx = cpu.reg_read(UC_X86_REG_EDX)
        if address == 0x40acf0:
            slots.append(eax)
            cpu.mem_write(eax, struct.pack('<I', len(slots)))
        elif address == 0x40ac20:
            tempo_events.append(eax)
        elif address != 0x40ac10:
            kind = addresses.index(address)
            value = sample_handles[edx - 36] if kind == 0 else 0 if kind in (2, 6) else edx
            mixer_events.append((eax - 1, kind, value))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
        cpu.reg_write(UC_X86_REG_EAX, 0)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, capture, begin=a, end=a) for a in (0x40acf0, 0x40ac20, 0x40ac10)]
    for address, target in zip(range(0x52f060, 0x52f07c, 4), (0x40c9d0, 0x40ca70, 0x40caa0, 0x40cad0, 0x40cb10, 0x40cb70, 0x40cbb0)):
        original.cpu.mem_write(address, struct.pack('<I', target))
    original.cpu.mem_write(0x52fc18, struct.pack('<I', 32))
    modules = []
    total_ticks = total_commands = 0
    compared_channels = 0
    pcm_frames = 0
    pcm_values = 0
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
            data = path.read_bytes()
            instrument_base, sample_bases, packed_addresses, sample_handles, pcm_addresses = original_song(original, data)
            stereo = (len(modules) // 2) % 2
            interpolate = len(modules) % 2
            master = 255
            frames = 64
            values = frames * (1 + stereo)
            original.cpu.mem_write(0x52fc1d, bytes([stereo]))
            original.call(0x40c7d0, eax=1, edx=master)
            kernels = ((0x40109c, 0x402934), (0x401328, 0x402c18)) if not interpolate else ((0x401cd0, 0x4036c8), (0x401f9c, 0x4039e4))
            original.cpu.mem_write(0x52fc34, struct.pack('<I', kernels[stereo][0]))
            original.cpu.mem_write(0x52fc38, struct.pack('<I', kernels[stereo][1]))
            rate = (32000, 48000)[len(modules) % 2]
            original.cpu.mem_write(0x52fc20, struct.pack('<I', rate))
            raw_mixer = bytearray(32 * 24)
            for ci in range(32):
                raw_mixer[ci * 24 + 22] = 1
            original.cpu.mem_write(0x52f918, bytes(raw_mixer))
            mixer = (Channel * channels)()
            sources = (Pointer * channels)()
            for ci in range(channels):
                mixer[ci].cursor.flags = 1
            original.cpu.mem_write(0x531b44, bytes(60))
            mixer_events.clear()
            tempo_events.clear()
            slots.clear()
            original.call(0x40ec40, eax=MASK)
            assert original.cpu.reg_read(UC_X86_REG_EAX) == 0
            assert not n.vertrix_sequence_start(header, None, ctypes.byref(sequence), ctypes.byref(global_state), ctypes.byref(delay), ctypes.byref(reader), rows, columns, memory, extended, playback, channels, publication, ctypes.byref(tempo))
            count = ctypes.c_size_t()
            bindings = n.vertrix_sequence_module_bindings(module, ctypes.byref(count))
            callback = Callback()
            orders = set()
            ticks = commands = 0
            assert n.vertrix_sequence_execute(bindings, count.value, rate, publication, mixer, sources, channels)
            source_addresses = {ctypes.cast(bindings[i].samples, ctypes.c_void_p).value: pcm_addresses[i] for i in range(count.value) if bindings[i].samples}
            for tick in range(args.ticks):
                mixer_events.clear()
                tempo_events.clear()
                prior = tempo.value
                original.call(0x40eb10)
                result = n.vertrix_sequence_tick(song, ctypes.byref(sequence), ctypes.byref(global_state), ctypes.byref(delay), ctypes.byref(reader), rows, columns, memory, extended, playback, channels, publication, ctypes.byref(tempo), ctypes.byref(changed), callback, None)
                assert result >= 0, (path.name, tick, sequence.order, sequence.row, result)
                if not result:
                    break
                expected_global = bytearray(60)
                expected_global[0] = sequence.flags
                expected_global[2] = song.contents.linear
                expected_global[3] = song.contents.module_flags
                struct.pack_into('<I', expected_global, 4, channels)
                for field, offset in zip(SN, SO):
                    struct.pack_into('<I', expected_global, offset, getattr(sequence, field))
                struct.pack_into('<4I', expected_global, 28, global_state.speed, global_state.tempo, global_state.volume, global_state.memory)
                struct.pack_into('<I', expected_global, 52, delay.value)
                assert bytes(expected_global) == bytes(original.cpu.mem_read(0x531b44, 60)), (path.name, tick, 'globals')
                assert changed.value == bool(tempo_events) and tempo.value == (tempo_events[0] if tempo_events else prior)
                pointer = 0
                if reader.data:
                    for pi in range(song.contents.pattern_count):
                        if song.contents.patterns[pi].packed == reader.data:
                            pointer = packed_addresses[pi] + reader.cursor
                            break
                    assert pointer
                assert pointer == struct.unpack('<I', original.cpu.mem_read(0x530440, 4))[0], (path.name, tick, 'reader')
                assert n.vertrix_sequence_execute(bindings, count.value, rate, publication, mixer, sources, channels)
                output = (ctypes.c_int32 * values)()
                original.cpu.mem_write(BOARD + 2048, bytes(values * 4))
                for ci in range(channels):
                    original.call(0x40c460, eax=BOARD + 2048, edx=values, ebx=0x52f918 + ci * 24)
                assert n.vertrix_sequence_mix(bindings, count.value, master, stereo, interpolate, mixer, sources, channels, output, frames, values), (path.name, tick, 'native mix')
                assert bytes(output) == bytes(original.cpu.mem_read(BOARD + 2048, values * 4)), (path.name, tick, 'PCM')
                pcm_frames += frames
                pcm_values += values
                native_events = []
                ticks += 1
                orders.add(sequence.order)
                for ci in range(channels):
                    actual = bytearray(reconstruct(bytes(180), rows[ci]))
                    column = columns[ci]
                    mem = memory[ci]
                    ext = extended[ci]
                    pb = playback[ci]
                    struct.pack_into('<I', actual, 52, 0 if not rows[ci].instrument.selected else instrument_base + (rows[ci].instrument.selected - 1) * 252)
                    struct.pack_into('<I', actual, 56, 0 if rows[ci].selection.selected == 0xffffffff else sample_bases[rows[ci].owner - 1] + rows[ci].selection.selected * 60)
                    for field, offset in zip(NAMES, OFFSETS):
                        struct.pack_into('<I', actual, offset, getattr(column, field))
                    for field, offset in zip(('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset'), (88, 92, 80, 84, 116)):
                        struct.pack_into('<I', actual, offset, getattr(mem, field))
                    for field, offset in zip(('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval'), (104, 105, 113, 108, 109, 110, 111)):
                        actual[offset] = getattr(mem, field)
                    struct.pack_into('<II', actual, 172, ext.start, ext.remaining)
                    actual[106] = ext.decrease
                    actual[107] = ext.increase
                    actual[61] = ext.glissando
                    struct.pack_into('<I', actual, 24, pb.output_volume)
                    struct.pack_into('<I', actual, 32, pb.output_pan)
                    struct.pack_into('<I', actual, 44, pb.vibrato.output)
                    for offset, env in ((128, pb.volume), (144, pb.pan)):
                        struct.pack_into('<4I', actual, offset, env.tick, env.value, env.point, env.slope)
                    expected = bytes(original.cpu.mem_read(0x530444 + ci * 180, 180))
                    assert bytes(actual) == expected, (path.name, tick, ci, [(i, a, b) for i, (a, b) in enumerate(zip(actual, expected)) if a != b])
                    compared_channels += 1
                    m = mixer[ci]
                    pointer = ctypes.cast(sources[ci], ctypes.c_void_p).value
                    actual_mixer = struct.pack('<5I', source_addresses[pointer] if pointer else 0, m.cursor.position, m.step, m.cursor.start, m.cursor.end) + bytes((m.volume, m.pan, m.cursor.flags, m.last))
                    assert actual_mixer == bytes(original.cpu.mem_read(0x52f918 + ci * 24, 24)), (path.name, tick, ci, 'mixer')
                    assert not rows[ci].selection.flags and not playback[ci].vibrato.flags
                    for j in range(publication[ci].count):
                        command = publication[ci].commands[j]
                        assert command.kind <= 6
                        if command.kind == 0:
                            assert 1 <= command.value <= count.value
                        native_events.append((ci, command.kind, command.value))
                        commands += 1
            print(path.name + ' passed ' + str(ticks) + ' ticks', flush=True)
            modules.append({'name': path.name, 'ticks': ticks, 'orders_visited': len(orders), 'commands': commands, 'stopped': bool(sequence.flags & 32)})
            total_ticks += ticks
            total_commands += commands
        finally:
            n.vertrix_sequence_module_free(module)
    prior = bytes(mixer), bytes(sources)
    publication[0].count = 1
    publication[0].commands[0].kind = 0
    publication[0].commands[0].value = count.value + 1
    assert not n.vertrix_sequence_execute(bindings, count.value, rate, publication, mixer, sources, channels) and (bytes(mixer), bytes(sources)) == prior
    prior = bytes(mixer), bytes(output)
    unknown = (ctypes.c_uint8 * 4)()
    old_source = sources[0]
    sources[0] = ctypes.cast(unknown, Pointer)
    assert not n.vertrix_sequence_mix(bindings, count.value, 255, stereo, interpolate, mixer, sources, channels, output, frames, values) and (bytes(mixer), bytes(output)) == prior
    for hook in hooks:
        original.cpu.hook_del(hook)
    report = {'status': 'passed', 'modules': len(modules), 'executed_ticks': total_ticks, 'emitted_commands': total_commands, 'compared_channels': compared_channels, 'pcm_frames': pcm_frames, 'pcm_values': pcm_values, 'songs': modules, 'scope': 'All original VF songs compared through x86 startup, complete ticks, actual mixer commands and 64-frame per-channel PCM mixing after each tick. Whole sequencer/mixer states and PCM accumulators match, mono/stereo and interpolation modes distributed across modules, at 32000/48000 Hz. Only slot allocation, tempo setter and tick registration captured. Invalid source preserves native mixer/output. Fixed-size chunks do not yet implement original tempo-based scheduling or audible delivery.'}
    (build / 'sequence-module-pcm-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k != 'songs'}, indent=2))
if __name__ == '__main__':
    main()

"""Verify sequencer instrument views built from every original VF XM sample."""
import argparse, ctypes, json, struct, subprocess
from pathlib import Path
from verify_xm_instrument_header import Instrument
from verify_xm_samples import Sample
from verify_sequence_process import RuntimeInstrument
from verify_mixer_row import View
from verify_mixer_sample_selection import Pitch
from verify_mixer_envelope import Point
from verify_mixer_attach import Binding


class Storage(ctypes.Structure):
    _fields_ = [('instrument', RuntimeInstrument), ('row', View), ('mapping', ctypes.c_uint8 * 96), ('pitches', Pitch * 16), ('volumes', ctypes.c_uint8 * 16), ('pans', ctypes.c_uint8 * 16), ('volume_points', Point * 12), ('pan_points', Point * 12), ('bindings', Binding * 16)]


def address(pointer):
    return ctypes.cast(pointer, ctypes.c_void_p).value
    def main():
        parser = argparse.ArgumentParser(description=__doc__)
        parser.add_argument('archive', type=Path)
        parser.add_argument('music', type=Path)
        parser.add_argument('--build-dir', type=Path, required=True)
        args = parser.parse_args()
        build = args.build_dir.resolve()
        build.mkdir(parents=True, exist_ok=True)
        source = Path(__file__).resolve().parents[1] / 'source'
        library = build / 'instrument-bind.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_xm_instrument_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(Instrument), ctypes.POINTER(Instrument)]
    native.vertrix_xm_sample_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Sample)]
    native.vertrix_xm_sample_free.argtypes = [ctypes.POINTER(Sample)]
    native.vertrix_sequence_instrument_bind.argtypes = [ctypes.POINTER(Instrument), ctypes.POINTER(Sample), ctypes.c_size_t, ctypes.c_uint32, ctypes.POINTER(Storage)]
    vf = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert vf
    modules = instruments = samples_checked = 0
    try:
        for path in sorted(args.music.glob('*.xm')):
            data = path.read_bytes()
            count = struct.unpack_from('<H', data, 72)[0]
            first = 0
            name = ('musique/' + path.name).encode()
            for index in range(count):
                metadata = Instrument()
                assert native.vertrix_xm_instrument_load(vf, name, index, None, ctypes.byref(metadata))
                samples = (Sample * metadata.samples)()
                output = Storage()
                try:
                    for sample in range(metadata.samples):
                        assert native.vertrix_xm_sample_load(vf, name, index, sample, ctypes.byref(samples[sample]))
                        assert native.vertrix_sequence_instrument_bind(ctypes.byref(metadata), samples, metadata.samples, first, ctypes.byref(output))
                        base = ctypes.addressof(output)
                        trigger = output.instrument.trigger
                    assert address(trigger.mapping) == base + Storage.mapping.offset and bytes(output.mapping) == bytes(metadata.mapping)
                    assert address(trigger.samples) == base + Storage.pitches.offset
                    assert trigger.count == metadata.samples and trigger.fade == metadata.fade and trigger.volume == metadata.volume.flags and trigger.pan == metadata.pan.flags
                    assert trigger.sweep == metadata.sweep and trigger.depth == metadata.depth
                    assert bytes(output.row.trigger) == bytes(trigger)
                    assert address(output.row.volumes) == base + Storage.volumes.offset and address(output.row.pans) == base + Storage.pans.offset
                    assert output.instrument.first_sample == first
                    for sample in range(metadata.samples):
                        loaded = samples[sample]
                        binding = output.bindings[sample]
                        assert output.pitches[sample].relative == loaded.relative and output.pitches[sample].finetune == loaded.finetune
                        assert output.volumes[sample] == loaded.volume and output.pans[sample] == loaded.panning
                        assert address(binding.samples) == loaded.samples and binding.count == loaded.size and binding.start == loaded.loop_start and binding.end == loaded.loop_end and binding.flags == loaded.native_flags
                    playback = output.instrument.playback
                    assert (playback.waveform, playback.depth, playback.rate) == (metadata.waveform, metadata.depth, metadata.rate)
                    for field, points in (('volume', 'volume_points'), ('pan', 'pan_points')):
                        view = getattr(playback, field)
                        original = getattr(metadata, field)
                        assert address(view.points) == base + getattr(Storage, points).offset and view.storage == 12
                        assert (view.count, view.flags, view.sustain, view.start, view.end) == (original.count, original.flags, original.sustain, original.start, original.end)
                        assert bytes(getattr(output, points)) == bytes(original.points)
                        prior = bytes(output)
                        assert not native.vertrix_sequence_instrument_bind(ctypes.byref(metadata), samples, metadata.samples + 1, first, ctypes.byref(output)) and bytes(output) == prior
                        first += metadata.samples
                        samples_checked += metadata.samples
                        instruments += 1
                finally:
                    for sample in samples:
                        native.vertrix_xm_sample_free(ctypes.byref(sample))
            modules += 1
    finally:
        native.vertrix_vf_close(vf)
    report = {'status': 'passed', 'modules': modules, 'instruments': instruments, 'samples': samples_checked, 'scope': 'All original VF-loaded XM instruments and PCM samples bound to recovered row/trigger/playback views. Exact mapping, tuning, volume/pan, envelopes, fade/vibrato, binding offsets/source pointers and sample loop flags; internal pointers target stable caller storage. Invalid count preserves output. Metadata/PCM have separate original-executable proof. Excludes tick playback and audio delivery.'}
    (build / 'sequence-instrument-bind-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

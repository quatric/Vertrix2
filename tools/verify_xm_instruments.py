"""Compare original XM instrument metadata normalization and empty-header carry."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, STACK
from unicorn.x86_const import UC_X86_REG_EBP


class Point(ctypes.Structure):
    _fields_ = [('tick', ctypes.c_uint16), ('value', ctypes.c_uint16)]


class Envelope(ctypes.Structure):
    _fields_ = [('points', Point * 12)] + [(n, ctypes.c_uint8) for n in ('count', 'sustain', 'start', 'end', 'flags')]


class Instrument(ctypes.Structure):
    _fields_ = [('name', ctypes.c_char * 23), ('mapping', ctypes.c_uint8 * 96), ('samples', ctypes.c_uint16)] + [(n, ctypes.c_uint8) for n in ('waveform', 'sweep', 'depth', 'rate')] + [('fade', ctypes.c_uint16), ('volume', Envelope), ('pan', Envelope)]


def encode(instrument):
    data = bytearray(252)
    data[: 22] = bytes(instrument)[: 22]
    data[32: 128] = bytes(instrument.mapping)
    struct.pack_into('<H', data, 128, instrument.samples)
    data[130: 134] = bytes((instrument.waveform, instrument.sweep, instrument.depth, instrument.rate))
    struct.pack_into('<H', data, 134, instrument.fade)
    for offset, meta, env in ((136, 184, instrument.volume), (192, 240, instrument.pan)):
        for point in range(env.count):
            struct.pack_into('<HH', data, offset + point * 4, env.points[point].tick, env.points[point].value)
        data[meta: meta + 5] = bytes((env.count, env.sustain, env.start, env.end, env.flags))
    return bytes(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('music', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'instrument-load.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [ctypes.c_char_p]
    native.vertrix_vf_open.restype = ctypes.c_void_p
    native.vertrix_vf_close.argtypes = [ctypes.c_void_p]
    native.vertrix_xm_instrument_load.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32, ctypes.POINTER(Instrument), ctypes.POINTER(Instrument)]
    vf = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert vf
    original = Original(args.executable)
    frame = STACK + 512
    scratch = bytearray(243)
    carry = Instrument()
    files = records = empty = 0
    try:
        for chained in (False, True):
            for path in sorted(args.music.glob('*.xm')):
                if not chained:
                    scratch = bytearray(243)
                    carry = Instrument()
                initial = Instrument.from_buffer_copy(bytes(carry))
                data = path.read_bytes()
                name = ('musique/' + path.name).encode()
                offset = 60 + struct.unpack_from('<I', data, 60)[0]
                patterns, count = struct.unpack_from('<HH', data, 70)
                for _ in range(patterns):
                    offset += struct.unpack_from('<I', data, offset)[0] + struct.unpack_from(
                        '<H', data, offset + 7)[0]
                for index in range(count):
                    length = struct.unpack_from('<I', data, offset)[0]
                    samples = struct.unpack_from('<H', data, offset + 27)[0]
                    header = data[offset:offset + length]
                    if samples:
                        scratch[:] = header[:243]
                    else:
                        scratch[:29] = header[:29]
                        empty += 1
                    original.cpu.mem_write(0x5326d1, bytes(scratch))
                    original.cpu.mem_write(BOARD, bytes(252))
                    original.cpu.mem_write(frame - 16, struct.pack('<I', BOARD))
                    original.cpu.mem_write(frame - 24, struct.pack('<I', MASK))
                    original.cpu.reg_write(UC_X86_REG_EBP, frame)
                    original.call(0x4117e0, stop=0x411a00)
                    loaded = Instrument()
                    assert native.vertrix_xm_instrument_load(
                        vf, name, index, ctypes.byref(initial), ctypes.byref(loaded)), (path.name, index)
                    assert encode(loaded) == bytes(original.cpu.mem_read(BOARD, 252)), (
                        path.name, index, chained)
                    scratch[:] = original.cpu.mem_read(0x5326d1, 243)
                    carry = loaded
                    records += 1
                    sample_header_size = struct.unpack_from('<I', header, 29)[0] if samples else 0
                    sample_headers = offset + length
                    payload = sample_headers + samples * sample_header_size
                    for sample in range(samples):
                        payload += struct.unpack_from('<I', data, sample_headers + sample * sample_header_size)[0]
                    offset = payload
                before = bytes(loaded)
                assert not native.vertrix_xm_instrument_load(vf, name, count, ctypes.byref(initial), ctypes.byref(loaded)) and bytes(loaded) == before
                files += 1
    finally:
        native.vertrix_vf_close(vf)
    report = {'status': 'passed', 'module_passes': files, 'instrument_records': records, 'empty_instruments': empty, 'scope': 'All original VF XM instrument metadata loaded natively and compared with original 0x4117e0..0x411a00 conversion of independently located original header bytes. Two passes cover zero initial scratch per song and carried scratch across songs. Whole 252-byte records, sample maps, bounded names, envelopes and vibrato/fade metadata match. Invalid index preserves output. Excludes runtime view construction and audio.'}
    (build / 'xm-instrument-load-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

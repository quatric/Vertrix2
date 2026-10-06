"""Verify original complete trigger and extended retrigger/note-delay dispatch."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, BLOCKS
from verify_mixer_sample_selection import Pitch, State as Selection
from verify_mixer_trigger_reset import State as Reset, NAMES, OFFSETS, BYTES

class Instrument(ctypes.Structure):
    _fields_ = [('mapping', ctypes.POINTER(ctypes.c_uint8)), ('samples', ctypes.POINTER(Pitch)),
        ('count', ctypes.c_uint16), ('fade', ctypes.c_uint16)] + [
        (name, ctypes.c_uint8) for name in ('volume', 'pan', 'sweep', 'depth')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'timed-trigger.dylib'
    subprocess.run(
        [
            'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
            str(source / 'mixer.c'), '-o', str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    tail = [
        ctypes.POINTER(Instrument), ctypes.c_int, ctypes.POINTER(Selection),
        ctypes.POINTER(Reset)
    ]
    native.vertrix_mixer_trigger.argtypes = tail
    native.vertrix_mixer_timed_trigger.argtypes = [ctypes.c_uint8, ctypes.c_int32] + tail
    original = Original(args.executable)
    rng = random.Random(0x40e670); cases = 24000
    for mode in (0, 9, 13):
        for index in range(cases):
            data = bytearray(rng.randbytes(192));
            instrument = bytearray(rng.randbytes(252))
            data[7] = index % 256; data[4] = mode * 16 + index % 16
            data[3] = (3, 5, rng.randrange(256))[index % 3]
            data[2] = 0xf0 | rng.randrange(16) if index % 5 == 0 else rng.randrange(256)
            data[60] = (index // 2) % 256
            count = index % 257; present = (index // 256) % 2; linear = index % 2
            tick = (0, index % 16, -(index % 16), rng.randrange(-2147483648, 2147483648))[index % 4]
            mapping = rng.randbytes(96); instrument[32:128] = mapping
            instrument[131] = 0 if index % 5 == 0 else rng.randrange(256)
            instrument[132] = 0 if index % 7 == 0 else rng.randrange(256)
            struct.pack_into('<H', instrument, 128, count); struct.pack_into('<I', instrument, 248, BLOCKS)
            struct.pack_into('<I', data, 52, MASK if present else 0)
            old = rng.randrange(256); struct.pack_into('<I', data, 56, BLOCKS + old * 60)
            sample_bytes = bytearray(rng.randbytes(256 * 60))
            samples = (Pitch * 256)(*[Pitch(*struct.unpack_from('<bb', sample_bytes, i * 60 + 34)) for i in range(256)])
            native_mapping = (ctypes.c_uint8 * 96).from_buffer_copy(mapping)
            context = Instrument(native_mapping, samples, count, struct.unpack_from('<H', instrument, 134)[0],
                instrument[188], instrument[244], instrument[131], instrument[132])
            selection = Selection(old, struct.unpack_from('<i', data, 12)[0],
                struct.unpack_from('<i', data, 8)[0], *struct.unpack_from('<II', data, 36),
                data[7], data[0], data[6], data[3], data[2], data[1])
            reset = Reset(*[struct.unpack_from('<I', data, offset)[0] for offset in OFFSETS],
                *[data[offset] for offset in BYTES])
            original.cpu.mem_write(BOARD, bytes(data)); original.cpu.mem_write(MASK, bytes(instrument))
            original.cpu.mem_write(BLOCKS, bytes(sample_bytes)); original.cpu.mem_write(0x531b46, bytes([linear]))
            original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
            original.call(0x40d540 if mode else 0x40e670, eax=BOARD, ecx=BOARD)
            expected = bytes(original.cpu.mem_read(BOARD, 192))
            inputs = (ctypes.byref(context) if present else None, linear, ctypes.byref(selection), ctypes.byref(reset))
            assert (native.vertrix_mixer_timed_trigger(data[4], tick, *inputs) if mode else native.vertrix_mixer_trigger(*inputs))
            actual = bytearray(data)
            struct.pack_into('<I', actual, 56, 0 if selection.selected == 0xffffffff else BLOCKS + selection.selected * 60)
            struct.pack_into('<ii', actual, 8, selection.finetune, selection.relative)
            struct.pack_into('<II', actual, 36, selection.base, selection.output)
            for offset, value in ((7,selection.note),(0,selection.active),(6,selection.mapping),(3,selection.effect),(2,selection.volume),(1,selection.flags)):
                actual[offset] = value
            for name, offset in zip(NAMES, OFFSETS): struct.pack_into('<I', actual, offset, getattr(reset, name))
            for name, offset in zip(('waveform', 'state_112', 'state_114', 'state_115'), BYTES): actual[offset] = getattr(reset, name)
            assert bytes(actual) == expected, (mode, index)
    selection.note = 1; context.mapping = None
    before = bytes(selection), bytes(reset)
    assert not native.vertrix_mixer_timed_trigger(0xd0, 0, ctypes.byref(context), 0, ctypes.byref(selection), ctypes.byref(reset))
    assert (bytes(selection), bytes(reset)) == before
    assert not native.vertrix_mixer_timed_trigger(0x80, 0, None, 0, ctypes.byref(selection), ctypes.byref(reset))
    assert not native.vertrix_mixer_trigger(None, 0, None, ctypes.byref(reset))
    report = {'status':'passed', 'direct_trigger_cases':cases, 'retrigger_cases':cases, 'note_delay_cases':cases,
        'scope':'Complete original 0x40e670 and complete extended dispatcher 0x40d540 selectors 9/D; whole 192-byte channel comparisons, signed ticks, zero intervals, invalid notes, absent instruments and combined selection/envelope reset. Excludes sequencing and envelope advancement.'}
    (build / 'mixer-timed-trigger-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__': main()

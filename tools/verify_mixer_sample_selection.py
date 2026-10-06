"""Compare complete original instrument sample-selection routine."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, BLOCKS

class Pitch(ctypes.Structure):
    _fields_ = [('relative', ctypes.c_int8), ('finetune', ctypes.c_int8)]
class State(ctypes.Structure):
    _fields_ = [('selected', ctypes.c_uint32), ('relative', ctypes.c_int32),
        ('finetune', ctypes.c_int32), ('base', ctypes.c_uint32), ('output', ctypes.c_uint32)] + [
        (name, ctypes.c_uint8) for name in ('note', 'active', 'mapping', 'effect', 'volume', 'flags')]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sample-selection.dylib'
    subprocess.run(
        [
            'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
            str(source / 'mixer.c'), '-o', str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_mixer_select_sample
    function.argtypes = [
        ctypes.c_int, ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Pitch), ctypes.c_uint16,
        ctypes.c_int, ctypes.POINTER(State)
    ]
    original = Original(args.executable)
    rng = random.Random(0x40e580); cases = 40000
    for index in range(cases):
        data = bytearray(rng.randbytes(192));
        instrument = bytearray(rng.randbytes(252))
        data[7] = index % 256
        data[3] = (3, 5, rng.randrange(256))[index % 3]
        data[2] = 0xf0 | rng.randrange(16) if index % 5 == 0 else rng.randrange(256)
        count = index % 257; present = (index // 256) % 2; linear = index % 2
        mapping = rng.randbytes(96); instrument[32:128] = mapping
        struct.pack_into('<H', instrument, 128, count); struct.pack_into('<I', instrument, 248, BLOCKS)
        struct.pack_into('<I', data, 52, MASK if present else 0)
        old_selection = rng.randrange(256); struct.pack_into('<I', data, 56, BLOCKS + old_selection * 60)
        sample_bytes = bytearray(rng.randbytes(256 * 60))
        samples = (Pitch * 256)(*[Pitch(*struct.unpack_from('<bb', sample_bytes, i * 60 + 34)) for i in range(256)])
        native_mapping = (ctypes.c_uint8 * 96).from_buffer_copy(mapping)
        state = State(old_selection, struct.unpack_from('<i', data, 12)[0],
            struct.unpack_from('<i', data, 8)[0], *struct.unpack_from('<II', data, 36),
            data[7], data[0], data[6], data[3], data[2], data[1])
        original.cpu.mem_write(BOARD, bytes(data)); original.cpu.mem_write(MASK, bytes(instrument))
        original.cpu.mem_write(BLOCKS, bytes(sample_bytes)); original.cpu.mem_write(0x531b46, bytes([linear]))
        original.call(0x40e580, eax=BOARD); expected = bytes(original.cpu.mem_read(BOARD, 192))
        assert function(present, native_mapping, samples, count, linear, ctypes.byref(state))
        actual = bytearray(data)
        struct.pack_into('<I', actual, 56, 0 if state.selected == 0xffffffff else BLOCKS + state.selected * 60)
        struct.pack_into('<ii', actual, 8, state.finetune, state.relative)
        struct.pack_into('<II', actual, 36, state.base, state.output)
        for offset, value in ((7,state.note),(0,state.active),(6,state.mapping),(3,state.effect),(2,state.volume),(1,state.flags)):
            actual[offset] = value
        assert bytes(actual) == expected, index
    state.note = 1; before = bytes(state)
    assert not function(1, None, samples, 256, 0, ctypes.byref(state)) and bytes(state) == before
    native_mapping[0] = 0
    assert not function(1, native_mapping, None, 256, 0, ctypes.byref(state)) and bytes(state) == before
    assert not function(0, None, None, 0, 0, None)
    report = {'status':'passed', 'sample_selection_cases':cases,
        'scope':'Complete original 0x40e580, whole 192-byte channel comparison with native indices translated to original sample pointers; notes 0..255, missing instruments, invalid mappings, signed sample tuning, both period modes and pitch-preserving effects. Excludes envelope reset and full sequencing.'}
    (build / 'mixer-sample-selection-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__': main()

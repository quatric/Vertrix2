"""Compare complete original publication through actual mixer setters."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK, BLOCKS
from verify_mixer_channel import Channel, Cursor
from verify_mixer_row import State as Row
from verify_mixer_playback_tick import State as Playback
from verify_sequence_advance import row_state, reconstruct
from verify_mixer_attach import Binding, Pointer


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-deliver.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / name) for name in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_sequence_deliver
    function.argtypes = [ctypes.c_uint32, ctypes.c_int, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Binding), ctypes.c_size_t, ctypes.POINTER(Row), ctypes.POINTER(Playback), ctypes.POINTER(Channel), ctypes.POINTER(Pointer)]
    original = Original(args.executable)
    rng = random.Random(0x40e8a1)
    cases = 30000
    for address, target in zip(range(0x52f060, 0x52f07c, 4), (0x40c9d0, 0x40ca70, 0x40caa0, 0x40cad0, 0x40cb10, 0x40cb70, 0x40cbb0)):
        original.cpu.mem_write(address, struct.pack('<I', target))
    original.cpu.mem_write(0x52fc18, struct.pack('<I', 1))
    storage = (ctypes.c_uint8 * 1)(0)
    old_storage = (ctypes.c_uint8 * 1)(0)
    for index in range(cases):
        data = bytearray(rng.randbytes(192))
        mixer = bytearray(rng.randbytes(24))
        descriptor = bytearray(rng.randbytes(24))
        present = index % 2
        valid_source = index % 5 != 0
        linear = (index // 512) % 2
        data[1] = (index // 2) % 256
        descriptor[22] = (index // 3) % 256
        struct.pack_into('<I', descriptor, 4, BLOCKS if valid_source else 0)
        struct.pack_into('<I', data, 56, MASK if present else 0)
        struct.pack_into('<I', mixer, 0, BLOCKS + 1)
        offset, period, volume, pan = [rng.getrandbits(32) for _ in range(4)]
        if index % 3 == 0:
            offset = rng.randrange(100)
            period = rng.randrange(1, 7680)
            volume = rng.randrange(65)
            pan = rng.randrange(256)
        for position, value in ((116, offset), (44, period), (24, volume), (32, pan)):
            struct.pack_into('<I', data, position, value)
        global_volume = rng.getrandbits(32) if index % 3 else rng.randrange(65)
        rate = rng.randrange(1, 0x100000000)
        sample = Binding(ctypes.cast(storage, Pointer) if valid_source else None, * struct.unpack_from('<III', descriptor, 8), descriptor[22])
#Decode the row with absent pointers; sample binding is supplied separately.
        row_data = bytearray(data)
        struct.pack_into('<II', row_data, 52, 0, 0)
        row = row_state(row_data)
        playback = Playback.from_buffer_copy(rng.randbytes(ctypes.sizeof(Playback)))
        playback.vibrato.output = period
        playback.output_volume = volume
        playback.output_pan = pan
        playback.vibrato.flags = row.selection.flags
        row_before = bytes(row)
        playback_before = bytes(playback)
        pointer, position, step, start, end = struct.unpack_from('<5I', mixer)
        channel = Channel(Cursor(position, start, end, mixer[22]), step, mixer[20], mixer[21], mixer[23])
        bound = ctypes.cast(old_storage, Pointer)
        original.cpu.mem_write(BOARD, bytes(data))
        original.cpu.mem_write(MASK + 36, bytes(descriptor))
        original.cpu.mem_write(0x52f918, bytes(mixer))
        original.cpu.mem_write(0x531b46, bytes([linear]))
        original.cpu.mem_write(0x531b68, struct.pack('<I', global_volume))
        original.cpu.mem_write(0x52fc20, struct.pack('<I', rate))
        original.call(0x40e8a0, eax=1, edx=BOARD)
        assert function(global_volume, linear, rate, present, offset, ctypes.byref(sample), 1, ctypes.byref(row), ctypes.byref(playback), ctypes.byref(channel), ctypes.byref(bound))
        actual = bytearray(data)
        actual[1] = row.selection.flags
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), index
        assert not row.defaults.flags and not playback.vibrato.flags
        expected_row = Row.from_buffer_copy(row_before)
        expected_row.selection.flags = 0
        expected_row.defaults.flags = 0
        expected_playback = Playback.from_buffer_copy(playback_before)
        expected_playback.vibrato.flags = 0
        assert bytes(row) == bytes(expected_row) and bytes(playback) == bytes(expected_playback), index
        new_pointer = BLOCKS if ctypes.cast(bound, ctypes.c_void_p).value == ctypes.addressof(storage) else BLOCKS + 1
        actual_mixer = bytearray(mixer)
        struct.pack_into('<5I', actual_mixer, 0, new_pointer, channel.cursor.position, channel.step, channel.cursor.start, channel.cursor.end)
        actual_mixer[20: 24] = bytes((channel.volume, channel.pan, channel.cursor.flags, channel.last))
        assert bytes(actual_mixer) == bytes(original.cpu.mem_read(0x52f918, 24)), index
    row.selection.flags = 0x28
    before = bytes(row), bytes(playback), bytes(channel), ctypes.cast(bound, ctypes.c_void_p).value
    assert not function(64, 0, 48000, 2, 0, ctypes.byref(sample), 1, ctypes.byref(row), ctypes.byref(playback), ctypes.byref(channel), ctypes.byref(bound))
    assert (bytes(row), bytes(playback), bytes(channel), ctypes.cast(bound, ctypes.c_void_p).value) == before
    assert not function(64, 0, 0, 1, 0, ctypes.byref(sample), 1, ctypes.byref(row), ctypes.byref(playback), ctypes.byref(channel), ctypes.byref(bound))
    assert (bytes(row), bytes(playback), bytes(channel), ctypes.cast(bound, ctypes.c_void_p).value) == before
    report = {'status': 'passed', 'delivery_cases': cases, 'scope': 'Final persistent playback through complete original 0x40e8a0 and actual wrapper calls/mixer setters, no hooks. Row/default/playback flags synchronize; other native fields preserved. Whole sequencer and mixer channel comparisons cover every flag byte, missing/rejected sample attachment, all sample flag bytes, invalid setters, both pitch modes and continued command execution. Excludes slot indexing, sequencing and real-time audio.'}
    (build / 'sequence-deliver-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

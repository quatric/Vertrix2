""
    "Compare integrated song control across ordered channel effects and consecutive ticks."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD,
    MASK from verify_mixer_row import State as Row from verify_mixer_global_effects import State
        as Global from verify_mixer_sequence_row import State as Sequence,
    NAMES, OFFSETS from verify_sequence_advance import row_state,
    reconstruct from verify_mixer_playback_tick import State as Playback
        from unicorn import UC_HOOK_CODE from unicorn.x86_const import UC_X86_REG_EAX,
    UC_X86_REG_ESP,
    UC_X86_REG_EIP

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('executable',
                                                                                  type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source'; library = build / 'sequence-global.dylib'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source / n) for n in ('sequencer.c','mixer.c','xm.c','vf.c','audio.c')],'-o',str(library)],check=True)
    native = ctypes.CDLL(str(library));
function = native.vertrix_sequence_global_effect function.argtypes =
    [
        ctypes.c_int32, ctypes.c_uint16, ctypes.POINTER(Row), ctypes.POINTER(Sequence),
        ctypes.POINTER(Global)
    ] native.vertrix_sequence_pending.argtypes =
        [
            ctypes.POINTER(Sequence), ctypes.POINTER(Global), ctypes.POINTER(ctypes.c_uint32),
            ctypes.POINTER(Row), ctypes.POINTER(Playback), ctypes.c_size_t,
            ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_int)
        ] original = Original(args.executable);
rng = random.Random(0x40d881);
sequences = 4000;
ticks = 6;
channels = 3 effects = (11, 13, 15, 16, 17)tempos =
    [] def capture(cpu, address, size, context) : tempos.append(cpu.reg_read(UC_X86_REG_EAX));
stack = cpu.reg_read(UC_X86_REG_ESP) target =
    struct.unpack('<I', cpu.mem_read(stack, 4))[0] cpu.reg_write(UC_X86_REG_ESP, stack + 4); cpu.reg_write(UC_X86_REG_EIP,target)
    hook = original.cpu.hook_add(UC_HOOK_CODE,capture,begin=0x40ac20,end=0x40ac20)
    for index in range(sequences):
        region = bytearray(rng.randbytes(64)); sequence = Sequence(*[struct.unpack_from('<I',region,o)[0] for o in OFFSETS],region[0])
        global_state = Global(*struct.unpack_from('<4I',region,28),rng.randrange(256))
        song_length = rng.randrange(65536);
song = bytearray(344);
struct.pack_into('<H', song, 34, song_length) original.cpu.mem_write(MASK, bytes(song)); original.cpu.mem_write(0x53043c,struct.pack('<I',MASK))
        for ti in range(ticks):
            tick = ti % 3 if index % 3 else (0,-1,2147483647)[ti % 3]
            struct.pack_into('<i',region,8,tick); sequence.tick = tick & 0xffffffff
            for ci in range(channels):
                data = bytearray(rng.randbytes(180));
struct.pack_into('<II', data, 52, 0, 0) data[3] = effects[(index + ti + ci) % len(effects)];
data[4] = (index + ci) % 256 if ti == 0 else rng.randrange(256) row = row_state(data);
before_row = bytes(row) original.cpu.mem_write(BOARD, bytes(data));
original.cpu.mem_write(0x531b44, bytes(region)) original.call(0x40dc50, eax = BOARD) assert
    function(tick, song_length, ctypes.byref(row), ctypes.byref(sequence),
             ctypes.byref(global_state)) actual = bytearray(region); actual[0] = sequence.flags
                for name,offset in zip(NAMES,OFFSETS): struct.pack_into('<I',actual,offset,getattr(sequence,name))
                struct.pack_into('<4I',actual,28,global_state.speed,global_state.tempo,global_state.volume,global_state.memory)
                assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44,64)),(index,ti,ci,data[3])
                assert bytes(row) == before_row and bytes(data) == bytes(original.cpu.mem_read(BOARD,180))
                assert sequence.flags == global_state.flags
                region = actual
            records = bytearray(rng.randbytes(channels*180));
rows = (Row * channels)(); playback = (Playback*channels)()
            for ci in range(channels):
                struct.pack_into('<II',records,ci*180+52,0,0)
                rows[ci] = row_state(records[ci*180:(ci+1)*180])
                playback[ci] = Playback.from_buffer_copy(rng.randbytes(ctypes.sizeof(Playback)))
                playback[ci].vibrato.flags = rows[ci].selection.flags
            struct.pack_into('<I',region,4,channels)
            delay = ctypes.c_uint32(struct.unpack_from('<I',region,52)[0]);
output = ctypes.c_uint32(rng.getrandbits(32));
prior_output = output.value;
changed = ctypes.c_int(-1) original.cpu.mem_write(0x531b44, bytes(region));
original.cpu.mem_write(0x530444, bytes(records));
tempos.clear() original.call(0x40eb6e, stop = 0x40ebf3) assert native
            .vertrix_sequence_pending(ctypes.byref(sequence), ctypes.byref(global_state),
                                      ctypes.byref(delay), rows, playback, channels,
                                      ctypes.byref(output),
                                      ctypes.byref(changed)) assert changed.value
        == bool(tempos) and
    output.value == (tempos[0] if tempos else prior_output)actual = bytearray(region);
actual[0] = sequence.flags; struct.pack_into('<I',actual,52,delay.value)
            assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44,64)),(index,ti,'pending')
            for ci in range(channels):
                records[ci*180:(ci+1)*180] = reconstruct(records[ci*180:(ci+1)*180],rows[ci])
                assert rows[ci].selection.flags == rows[ci].defaults.flags == playback[ci].vibrato.flags
            assert bytes(records) == bytes(original.cpu.mem_read(0x530444,len(records))),(index,ti,'channels')
            assert global_state.flags == sequence.flags
            region = actual
    row.selection.effect = 14;
before = bytes(row), bytes(sequence),
    bytes(global_state) assert
        not function(0, 1, ctypes.byref(row), ctypes.byref(sequence), ctypes.byref(global_state))
            assert(bytes(row), bytes(sequence), bytes(global_state)) == before
        before_pending = bytes(sequence),
        bytes(global_state), delay.value, output.value,
        changed.value assert
            not native.vertrix_sequence_pending(ctypes.byref(sequence), ctypes.byref(global_state),
                                                ctypes.byref(delay), None, playback, channels,
                                                ctypes.byref(output), ctypes.byref(changed))
                assert(bytes(sequence), bytes(global_state), delay.value, output.value,
                       changed.value) == before_pending original.cpu.hook_del(hook) report =
            {
                'status' : 'passed',
                'sequences' : sequences,
                'ticks_per_sequence' : ticks,
                'channels_per_tick' : channels,
                'integrated_global_effects' : sequences * ticks * channels,
                'integrated_pending_phases' : sequences * ticks,
                'scope' :
                    'Complete original 0x40dc50 for effects 11/13/15/16/17 across three ordered channels and six consecutive ticks, without hooks. Whole global/channel records match; pending jump/break state, speed/tempo/volume flags and memory synchronize. Signed ticks, all parameter bytes and arbitrary song lengths. Unsupported native effect preserves state. Also compares post-envelope pending consumption after each tick: delay, global-volume propagation and captured tempo updates. Invalid pending storage preserves state. Row advancement and audio excluded.'
            }(build / 'sequence-global-effect-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()

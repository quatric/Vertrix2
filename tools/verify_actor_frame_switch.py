"""Compare complete original actor frame decay/switch routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
ACTOR, STATE = 0x801000, 0x5bb710
SIZE = 0x200
Cb2 = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
Cb1 = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)


class Ops(c.Structure):
    _fields_ = [('attach', Cb2), ('set_frame', Cb2), ('bind', Cb1)]


class State(c.Structure):
    _fields_ = [('gate', U), ('refresh', U * 6)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-frame-switch',
              ['actor_frame_switch.c', 'actor_refresh_state.c', 'word_transition.c', 'actor_storage.c',
               'piece_actor_destroy.c', 'player_piece.c', 'piece_actor_construct.c',
               'piece_actor_layout.c', 'piece_child_update.c', 'timer.c', 'timing.c',
               'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c'])
    n.vertrix_actor_frame_decay.argtypes = [c.POINTER(State), c.c_void_p, c.c_size_t, U]
    n.vertrix_actor_frame_switch.argtypes = [c.POINTER(State), c.c_void_p, c.c_size_t, U, U,
                                             c.POINTER(Ops), c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    stubs = Stubs(cpu, lambda *a: None)
    for address in (0x4ac8d0, 0x4ac710, 0x4ac8a0):
        stubs.add(address)
    native = []
    ops = Ops(Cb2(lambda a, r, ctx: native.append((0x4ac8d0, a, r))),
              Cb2(lambda a, f, ctx: native.append((0x4ac710, a, f))),
              Cb1(lambda a, ctx: native.append((0x4ac8a0, a))))
    rng = random.Random(0x449360)
    totals = {}
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<h', memory, 0x148, rng.choice([-1, 0, 1, 2, 3, 4, 5, 6, 0x7fff]))
        word = rng.choice([0, 1, 3, 4, 100, 0x7fff, -1, -400, rng.randrange(-32768, 32768)])
        struct.pack_into('<h', memory, 0x48, word)
        frame = rng.choice([0, 1, 2, 0xffffffff, rng.getrandbits(32)])
        struct.pack_into('<I', memory, 0xb8, frame if rng.random() < 0.3 else rng.getrandbits(32))
        state = struct.pack('<7I', *[rng.choice([0, 1, rng.getrandbits(32)]) for _ in range(7)])
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(memory))
        cycles = rng.choice([0, 1, 2, 5, 100, 0x10000, 0xffffffff, rng.getrandbits(32)])
        for name, address, edx in (('decay', 0x449360, cycles), ('switch', 0x449390, frame)):
            cpu.mem_write(ACTOR, bytes(memory))
            cpu.mem_write(STATE, state)
            stubs.log.clear()
            native.clear()
            c.memmove(buffer, bytes(memory), SIZE)
            native_state = State.from_buffer_copy(state)
            original.call(address, eax=ACTOR, edx=edx)
            if name == 'decay':
                n.vertrix_actor_frame_decay(c.byref(native_state), buffer, SIZE, cycles)
            else:
                n.vertrix_actor_frame_switch(c.byref(native_state), buffer, SIZE, ACTOR, frame,
                                             c.byref(ops), None)
            assert bytes(buffer) == bytes(cpu.mem_read(ACTOR, SIZE)), (case, name)
            assert bytes(native_state) == bytes(cpu.mem_read(STATE, 28)), (case, name)
            events = [(e[0], e[1]) if e[0] == 0x4ac8a0 else (e[0], e[1], e[2]) for e in stubs.log]
            assert events == native, (case, name)
            totals[name] = totals.get(name, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 449360 and 449390 execute in the original (4ac8d0, 4ac710 and '
                       '4ac8a0 stubbed and logged; 4ad530 and 4adfe0 run for real); the whole '
                       'actor, the refresh state at 5bb710 and the ordered calls compare.'}
    (args.build_dir / 'actor-frame-switch-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

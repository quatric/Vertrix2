"""Compare the original reaction time 0x43b5b0 with the native vertrix_ai_reaction_time."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, BOARD
from oracle_kit import build, Stubs

DRAW = c.CFUNCTYPE(c.c_uint16, c.c_void_p, c.c_uint16)
U = c.c_uint32


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2000)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-timing', ['ai_timing.c', 'ai_player.c', 'ai_features.c',
                                            'match.c', 'board.c'])
    n.vertrix_ai_reaction_time.argtypes = [U, U, U, DRAW, c.c_void_p]
    n.vertrix_ai_reaction_time.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b5b0)
    draws = []

    def handler(address, eax, edx, ebx, ecx, stack):
        draws.append((edx & 0xffff, rng.randrange(max(edx & 0xffff, 1))))
        return draws[-1][1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    replay = []

    @DRAW
    def draw(context, divisor):
        expected, value = replay.pop(0)
        assert expected == divisor, (expected, divisor)
        return value

    seen = set()
    for case in range(args.cases):
        skill = rng.randrange(19)
        difficulty = rng.randrange(3)
        speed = rng.randrange(0, 20)
        cpu.mem_write(BOARD, bytes(0x600))
        cpu.mem_write(BOARD + 0x488, struct.pack('<I', skill))
        cpu.mem_write(BOARD + 0x17c, struct.pack('<I', speed))
        cpu.mem_write(0x532bbc, struct.pack('<I', difficulty))
        del draws[:]
        original.call(0x43b5b0, eax=BOARD, edx=0, ebx=0, ecx=0, args=())
        expected = struct.unpack('<I', cpu.mem_read(BOARD + 0x458, 4))[0]
        replay[:] = list(draws)
        got = n.vertrix_ai_reaction_time(skill, difficulty, speed, draw, None)
        assert got == expected and not replay, (case, skill, difficulty, speed, got, expected)
        seen.add(got)
    report = {'status': 'passed', 'complete_original_executions': {'0x43b5b0': args.cases},
              'distinct_results': len(seen),
              'scope': 'The complete reaction time runs in the original (only the 0x4826c0 draw '
                       'is stubbed and replayed, its divisor checked) over every skill, '
                       'difficulty and a range of speeds; the result compares with the native one.'}
    (args.build_dir / 'ai-timing-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

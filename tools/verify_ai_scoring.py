"""Compare complete original computer-player board/record scoring with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, build
U = c.c_uint32
BASE = 0x80c000


def column(rng):
    kind = rng.random()
    empty = rng.randrange(14) if kind < 0.8 else rng.choice([0, 13])
    return bytes([0xff] * empty + [rng.choice([0, 1, 2, 3, 4, 5, 5, 6, 6, 7]) for _ in range(13 - empty)])


def board(rng):
    density = rng.random()
    return b''.join(column(rng) if rng.random() < density + 0.2 else bytes([0xff] * 13) for _ in range(5))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-scoring', ['ai_scoring.c'])
    B = c.c_uint8
    n.vertrix_ai_compare_boards.argtypes = [B * 65, B * 65, B, B * 0x13]
    n.vertrix_ai_record_score.argtypes = [c.c_char_p, B * 256, U, c.POINTER(c.c_int32)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x428110)
    pool = Pool(cpu, 2, 0x1000)
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    for case in range(args.cases):
        a, b = board(rng), board(rng)
        level = rng.choice([0, 0, 1, 2, 255])
        pool.fill(rng)
        player = pool.handles[0]
        raw = bytearray(pool.buffers[player].raw)
        raw[0x17c] = level
        cpu.mem_write(player, bytes(raw))
        cpu.mem_write(BASE, a)
        cpu.mem_write(BASE + 0x100, b)
        data = bytes(rng.randrange(256) for _ in range(0x13))
        cpu.mem_write(BASE + 0x200, data)
        original.call(0x428110, eax=player, edx=BASE, ebx=BASE + 0x100, ecx=BASE + 0x200)
        out = (B * 0x13).from_buffer_copy(data)
        n.vertrix_ai_compare_boards((B * 65).from_buffer_copy(a), (B * 65).from_buffer_copy(b), level, out)
        assert bytes(out) == bytes(cpu.mem_read(BASE + 0x200, 0x13)), case
        count('compare_boards')
# 428610 : record score
        table = bytes(rng.choice([0, 4, 4, 1, 2, 3, 5, 100, 200, 255, rng.randrange(256)]) for _ in range(256))
        records = rng.randrange(0, 9)
        header = bytes([rng.choice([0, 1, 2, 2, 3, 255]), records, 0, 0, 0])
        body = bytearray()
        for _ in range(records):
            kind = rng.choice([0, 1, 2, 3, 4, 5, 2, 3, 6, 255])
            slot = rng.randrange(6) if kind in (2, 3, 4, 5) else rng.randrange(256)
            body += bytes([slot, rng.randrange(256), kind, rng.randrange(8), rng.randrange(8)])
        record_data = header + bytes(body)
        max_limit = rng.randrange(10)
        cpu.mem_write(BASE + 0x400, table)
        cpu.mem_write(BASE + 0x600, record_data)
        result = original.call(0x428610, edx=BASE + 0x400, ebx=max_limit, ecx=BASE + 0x600)
        score = c.c_int32(0x7777)
        assert n.vertrix_ai_record_score(record_data, (B * 256).from_buffer_copy(table), max_limit, c.byref(score))
        assert score.value == struct.unpack('<i', struct.pack('<I', result & 0xffffffff))[0], (case, score.value, result)
        count('record_score')
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 428110 and 428610 execute in the original (4eb5c0 fill runs for ' 'real); every output byte and the signed score compare over random boards, ' 'levels, record lists, tables and limits.'}
    (args.build_dir / 'ai-scoring-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

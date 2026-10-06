import ctypes as c, os, random, struct
from pathlib import Path
from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build
EXE = Path('/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/extraction-check/original/Vertrix2.exe')
os.environ['FIGDBG'] = '1'
original = Original(EXE)
cpu = original.cpu
n = build(Path('/tmp/vb-acc'), 'fig-acc', ['match.c', 'board.c'])
cells = c.c_uint8 * 65
n.vertrix_figure_pass.argtypes = [cells, cells, c.POINTER(c.c_int)]
n.vertrix_figure_pass.restype = c.c_int
# case-74 kinds: need them; replicate seeding quickly by importing verifier seeding is complex.
# Instead use the kinds from the earlier staged run: recompute via snapshot here.
rng = random.Random(0x432480)
cpu.mem_map(0x900000, 0x1000)
cpu.mem_map(0x901000, 0x100000)
top = [0x901000]
def take(size):
    h = top[0]; top[0] += (size + 0xf) & ~0xf; return h
slots = []
for _ in range(65):
    h = take(0x180); slots.append(h)
    blk = bytearray(rng.randbytes(0x180)); blk[0x15c] = 7
    cpu.mem_write(h, bytes(blk))
data = bytearray(rng.randbytes(0x1000))
for i in range(65):
    struct.pack_into('<I', data, 0x220 + i * 4, slots[i])
cpu.mem_write(0x900000, bytes(data))
# run 74 cases worth of RNG consumption? Too fragile. Just use current rng state is wrong.
print('abort: seeding fragile')

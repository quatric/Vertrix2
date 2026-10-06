import ctypes as c, random, struct
from pathlib import Path
from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build
EXE = Path('/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/extraction-check/original/Vertrix2.exe')
original = Original(EXE)
cpu = original.cpu
n = build(Path('/tmp/vb-stg2'), 'stg2', ['match.c', 'board.c'])
cells = c.c_uint8 * 65
n.vertrix_figure_pass.argtypes = [cells, cells, c.POINTER(c.c_int)]
n.vertrix_figure_pass.restype = c.c_int
n.vertrix_line_pass.argtypes = [cells, cells, c.c_int, c.POINTER(c.c_int)]
n.vertrix_line_pass.restype = c.c_int
import pickle
d = pickle.load(open('/tmp/vb-ms/case74.pkl', 'rb'))
print('side', d['side'])
# NOTE: kinds in pickle are PRE-snapshot seeds; snapshot overwrites. Need slots instead.
# Re-derive: this approach needs slots; abort and do it live instead.

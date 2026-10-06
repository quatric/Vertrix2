import ctypes as c, random, struct
from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build
from pathlib import Path
EXE = '/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/extraction-check/original/Vertrix2.exe'
original = Original(EXE)
cpu = original.cpu
rng = random.Random(0x432480)
# replicate case-0 seeding up to the kinds: player random, 65 slots, snapshot via original
import tools.verify_match_scan as V  # noqa

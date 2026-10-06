import ctypes as c, random, struct
from pathlib import Path
from original import Original, BOARD, MASK, COUNTER
from oracle_kit import build
EXE = Path('/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/extraction-check/original/Vertrix2.exe')
# Replicate verify_match_scan case-74 seeding exactly up to slots/kinds/image/side.
# That requires the full seeding code; instead read them from a live run is complex.
# Shortcut: run the real verifier to case 74 and dump PRE-run snapshot kinds by
# calling the original snapshot on the seeded slots before the full call.
print('placeholder')

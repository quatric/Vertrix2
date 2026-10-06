import ctypes as c, random, struct
from original import Original, BOARD, MASK, COUNTER
EXE = '/Volumes/SSD/larsen/Documents/Codex/2026-10-03/goal-ok-i-have-a-big/work/extraction-check/original/Vertrix2.exe'
original = Original(EXE)
cpu = original.cpu
rng = random.Random(1234)
# Seed a player-like kinds block and run the figure pass exactly as 0x432480 does
kinds = bytes(rng.choice([0,1,2,3,4,5,6,7,0xff]) for _ in range(65))
cpu.mem_write(0x900000, kinds)
cpu.mem_write(MASK, bytes(260))
cpu.mem_write(COUNTER, bytes(4))
cpu.mem_map(0x900000, 0x1000) if False else None
eax = original.call(0x434ee0, eax=0x900000, edx=MASK, ebx=0, ecx=1, args=(COUNTER,)) & 0xffffffff
print('eax', eax, 'counter', struct.unpack('<H', cpu.mem_read(COUNTER, 2))[0])

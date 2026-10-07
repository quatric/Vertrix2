"""Write the mapped image of Vertrix2.exe (0x400000..0x600000) for tools/host_probe.c and the
Wii lifted probe. Standard library only.

usage: dump_image.py OUTPUT [EXECUTABLE]
"""
import struct
import sys
from pathlib import Path

root = Path(__file__).resolve().parents[1]
exe = Path(sys.argv[2]) if len(sys.argv) > 2 else root / 'Vertrix2.exe'
data = exe.read_bytes()
pe = struct.unpack_from('<I', data, 0x3c)[0]
count = struct.unpack_from('<H', data, pe + 6)[0]
optional = struct.unpack_from('<H', data, pe + 20)[0]
base = struct.unpack_from('<I', data, pe + 52)[0]
headers = struct.unpack_from('<I', data, pe + 84)[0]
image = bytearray(0x200000)
image[:headers] = data[:headers]
table = pe + 24 + optional
for i in range(count):
    name, vsize, vaddr, rawsize, rawptr = struct.unpack_from('<8sIIII', data, table + 40 * i)
    flags = struct.unpack_from('<I', data, table + 40 * i + 36)[0]
    if rawptr and not flags & 0x80:
        chunk = data[rawptr:rawptr + min(rawsize, max(vsize, rawsize))]
        image[vaddr:vaddr + len(chunk)] = chunk
assert base == 0x400000
Path(sys.argv[1]).write_bytes(bytes(image))

#!/usr/bin/env python3
"""Pad the section at the end of a DOL to a 32-byte size, in place:  dol_align.py FILE.dol ...

dolxz stores its xz stream as the last data section with the stream's exact size, and Dolphin
refuses such a DOL ("Failed to init core") when that size is not a multiple of 32. The padding
is zeros after the stream; dolxz's loader reads the stream's own length (kept at 0x124), not the
section size, so the program is unchanged. Sections inside the file (the loader's own small
.data) are left as they are: Dolphin only warns about those."""
import struct
import sys


def align(path):
    data = bytearray(open(path, 'rb').read())
    changed = False
    for i in range(18):
        offset = struct.unpack_from('>I', data, 4 * i)[0]
        size = struct.unpack_from('>I', data, 0x90 + 4 * i)[0]
        pad = -size % 32
        if size == 0 or pad == 0 or offset + size != len(data):
            continue
        data += b'\0' * pad
        struct.pack_into('>I', data, 0x90 + 4 * i, size + pad)
        changed = True
    if changed:
        open(path, 'wb').write(data)


for name in sys.argv[1:]:
    align(name)

"""Read an original VF v10 archive (both games), independently of source/vf.c.

Layout: u32 version (10), u32 count, then per entry u32 size, u32 offset, u32 name length and
the name (no terminator); all little-endian.
"""
import struct


def entries(path):
    """name -> bytes, in archive order."""
    data = open(path, 'rb').read()
    version, count = struct.unpack_from('<II', data, 0)
    if version != 10:
        raise ValueError('not a VF v10 archive')
    out = {}
    offset = 8
    for _ in range(count):
        size, start, length = struct.unpack_from('<III', data, offset)
        offset += 12
        name = data[offset:offset + length].decode('latin-1')
        offset += length
        out[name] = data[start:start + size]
    return out

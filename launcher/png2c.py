#!/usr/bin/env python3
"""Turn an 8-bit RGB or RGBA PNG (not interlaced) into a C array of 0xAARRGGBB pixels.

    png2c.py IN.png NAME OUT.h

Only the standard library is used, so the launcher builds without Pillow."""
import struct
import sys
import zlib


def read_png(path):
    data = open(path, 'rb').read()
    if data[:8] != b'\x89PNG\r\n\x1a\n':
        raise SystemExit('%s: not a PNG' % path)
    pos, idat, header = 8, b'', None
    while pos < len(data):
        length, kind = struct.unpack('>I4s', data[pos:pos + 8])
        body = data[pos + 8:pos + 8 + length]
        if kind == b'IHDR':
            header = struct.unpack('>IIBBBBB', body)
        elif kind == b'IDAT':
            idat += body
        pos += 12 + length
    width, height, depth, colour, _, _, interlace = header
    channels = {2: 3, 6: 4}.get(colour)
    if depth != 8 or channels is None or interlace:
        raise SystemExit('%s: only 8-bit RGB/RGBA, not interlaced' % path)
    raw = zlib.decompress(idat)
    stride = width * channels
    rows, previous, pos = [], bytearray(stride), 0
    for _ in range(height):
        kind, line = raw[pos], bytearray(raw[pos + 1:pos + 1 + stride])
        pos += 1 + stride
        for i in range(stride):
            a = line[i - channels] if i >= channels else 0
            b = previous[i]
            c = previous[i - channels] if i >= channels else 0
            if kind == 1:
                line[i] = (line[i] + a) & 255
            elif kind == 2:
                line[i] = (line[i] + b) & 255
            elif kind == 3:
                line[i] = (line[i] + (a + b) // 2) & 255
            elif kind == 4:
                p = a + b - c
                pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
                line[i] = (line[i] + (a if pa <= pb and pa <= pc else b if pb <= pc else c)) & 255
        rows.append(line)
        previous = line
    pixels = []
    for line in rows:
        for x in range(width):
            r, g, b = line[x * channels:x * channels + 3]
            alpha = line[x * channels + 3] if channels == 4 else 255
            pixels.append(alpha << 24 | r << 16 | g << 8 | b)
    return width, height, pixels


def main():
    source, name, target = sys.argv[1:4]
    width, height, pixels = read_png(source)
    with open(target, 'w') as out:
        out.write('/* Generated from %s by launcher/png2c.py. */\n' % source.split('/')[-1])
        out.write('#include <stdint.h>\n')
        out.write('enum { %s_width = %d, %s_height = %d };\n' % (name, width, name, height))
        out.write('static const uint32_t %s_pixels[%d] = {\n' % (name, len(pixels)))
        for i in range(0, len(pixels), 8):
            out.write('    ' + ', '.join('0x%08x' % p for p in pixels[i:i + 8]) + ',\n')
        out.write('};\n')


if __name__ == '__main__':
    main()

#!/usr/bin/env python3
"""The consoles' icons and splash screens from the Vertrix logo (wii-game/icon.png, 128x48), on
the launcher's background (launcher/main.c: a blue to purple gradient):

    console_art.py LOGO KIND OUT

KIND is switch-icon (256x256 JPEG), wiiu-icon (128x128), wiiu-tv (1280x720), wiiu-drc (854x480)
3ds-icon (48x48), 3ds-banner (256x128, the CIA's HOME Menu banner; a .wav OUT is a short
silence for its jingle) or nds-icon (32x32 in 16 colours, the BMP ndstool takes). The logo is
scaled by whole pixels where it is enlarged. Needs Pillow."""
import sys
import wave

from PIL import Image

SIZES = {
    'switch-icon': ((256, 256), 2),
    'wiiu-icon': ((128, 128), 1),
    'wiiu-tv': ((1280, 720), 6),
    'wiiu-drc': ((854, 480), 4),
    '3ds-icon': ((48, 48), None),
    '3ds-banner': ((256, 128), 1),
    'nds-icon': ((32, 32), None),
}
TOP, BOTTOM = (0x0b, 0x18, 0x30), (0x1c, 0x10, 0x30)


def silence(path):
    with wave.open(path, 'wb') as out:
        out.setnchannels(1)
        out.setsampwidth(2)
        out.setframerate(32728)
        out.writeframes(bytes(2 * 32728))


def main():
    if len(sys.argv) != 4 or sys.argv[2] not in SIZES:
        sys.exit(__doc__)
    if sys.argv[3].endswith('.wav'):
        silence(sys.argv[3])
        return
    logo = Image.open(sys.argv[1]).convert('RGB')
    (width, height), scale = SIZES[sys.argv[2]]
    art = Image.new('RGB', (width, height))
    for y in range(height):
        t = y / max(1, height - 1)
        colour = tuple(round(a + (b - a) * t) for a, b in zip(TOP, BOTTOM))
        art.paste(colour, (0, y, width, y + 1))
    if scale:
        logo = logo.resize((logo.width * scale, logo.height * scale), Image.NEAREST)
    else:
        logo = logo.resize((width, round(logo.height * width / logo.width)), Image.LANCZOS)
    art.paste(logo, ((width - logo.width) // 2, (height - logo.height) // 2))
    if sys.argv[2] == 'nds-icon':
        art.quantize(16).save(sys.argv[3])
    elif sys.argv[3].endswith('.jpg'):
        art.save(sys.argv[3], quality=95)
    else:
        art.save(sys.argv[3])


if __name__ == '__main__':
    main()

"""Unpack Vertrix (1997)'s data into files for inspection, with a page that shows them.

The game keeps its data in BIN1.BIN (docs/VERTRIX1.md, "The data formats"): a table of 135 entries, then
their bytes. The formats, as VERTRIX.EXE reads them:

- **.MXB, the pictures:** GIF image data without the GIF header: an LZW minimum code size (8),
  sub-blocks and a 3Bh trailer. They unpack to 320x200 or 320x400 bytes of colour indices, row by
  row. The palette is set separately from a .PAL file.
- **.PAL:** 256 RGB triples, 8 bits a component.
- **.VXL** (`VXL_Decompresser_To_Memory_`, 0x11c60): u32 unpacked size, u8 method (0 stored,
  1 packed), then the data. Packed is PCX's run-length code: a byte of C0h or more repeats the
  next byte (its low six bits) times; any other byte is itself.
  - FX*.VXL are WAV files (8-bit mono, 11,111 Hz).
  - MUS*.VXL are MODPLAY modules without samples (`charger_fichier_pattern_`, 0x3fccc): u16
    channels, u16 song length, 128 orders, then patterns of 64 rows x channels x 4 bytes. A
    cell is note, instrument, parameter, effect (`_MODPlayModule`'s row step, 0x4bc51); the note
    indexes the period table at 0x664bc, where 1 is 3424 and each step is a semitone.
- **BANK1.GSP, the instruments** (`charger_groupe_samples_`, 0x3fb38): 171 samples, each a
  ProTracker sample header (22-byte name, big-endian word length, finetune, volume, loop start,
  loop length) followed by its signed 8-bit data. Samples count from 1; a loop of two bytes or
  less is no loop.
- **The tunes' instruments:** tune n (MUSn.VXL) takes slot s (1-31) from bank sample
  table[n * 31 + s], the table at 0x65b48 (`gsptomod_fonc_`, 0x3fe68). 0 is none.
- **INSTVGA.CAR:** the setup screen's font, 224 glyphs of u16 width, u16 height and the
  pixels.
- **GAME.HUE:** read by `charger_hue_` (0x11f5c); written out as it is.

Each tune is written as a ProTracker-style module (`6CHN` and the like) with its instruments
from the bank, so any tracker plays it. MODPLAY starts at speed 6, tempo 125
(`_MODPlayModule`, 0x4b9ff) as ProTracker does. It ignores effects 8 and E and always breaks to
row 0 on D; those are written as MODPLAY plays them. With openmpt123 and lame on the PATH each
tune is also rendered to MP3 for the page.

usage: assets.py VERTRIX_EXE BIN1_BIN OUT_DIR
"""
import argparse
import base64
import importlib.util
import json
import shutil
import struct
import subprocess
import sys
import tempfile
import zlib
from pathlib import Path

# vertrix1/recomp.py, for VERTRIX.EXE's image at its link addresses.
_spec = importlib.util.spec_from_file_location('vertrix1_recomp',
                                               Path(__file__).resolve().parent / 'recomp.py')
r1 = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(r1)

PERIODS = 0x664bc  # u16 periods by note, 0 for none
TUNE_SAMPLES = 0x65b48  # u8 bank sample by tune * 31 + slot
BANK_SAMPLES = 0xab
SAMPLE_RATE = 8363  # C-2 (period 428), the rate the instruments are written at
ROW_EFFECTS = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x9, 0xa, 0xb, 0xc, 0xd, 0xf}


def entries(data):
    count = struct.unpack_from('<H', data)[0]
    out = {}
    for i in range(count):
        name, size, offset = struct.unpack_from('<16sII', data, 2 + 24 * i)
        out[name.split(b'\0')[0].decode()] = (offset, data[offset:offset + size])
    return out


def unrle(data, size):
    out = bytearray()
    i = 0
    while i < len(data) and len(out) < size:
        c = data[i]
        i += 1
        if c >= 0xc0:
            out += bytes([data[i]]) * (c & 0x3f)
            i += 1
        else:
            out.append(c)
    if len(out) != size:
        sys.exit('VXL: %d bytes of %d' % (len(out), size))
    return bytes(out)


def vxl(data):
    size, method = struct.unpack_from('<IB', data)
    return unrle(data[5:], size) if method else data[5:5 + size]


def unlzw(data):
    """GIF image data (minimum code size, sub-blocks) to its indices."""
    minimum = data[0]
    i = 1
    stream = bytearray()
    while data[i]:
        stream += data[i + 1:i + 1 + data[i]]
        i += 1 + data[i]
    clear, end = 1 << minimum, (1 << minimum) + 1
    table = [bytes([k]) for k in range(clear)] + [b'', b'']
    size = minimum + 1
    out = bytearray()
    previous = None
    bits = count = pos = 0
    while True:
        while count < size:
            if pos == len(stream):
                return bytes(out)
            bits |= stream[pos] << count
            pos += 1
            count += 8
        code = bits & ((1 << size) - 1)
        bits >>= size
        count -= size
        if code == clear:
            table = table[:clear + 2]
            size = minimum + 1
            previous = None
            continue
        if code == end:
            return bytes(out)
        entry = table[code] if code < len(table) else previous + previous[:1]
        out += entry
        if previous is not None and len(table) < 4096:
            table.append(previous + entry[:1])
            if len(table) == 1 << size and size < 12:
                size += 1
        previous = entry


def bank(data):
    """BANK1.GSP: (name, data, volume, loop start, loop length) by sample number, from 1."""
    samples = [None]
    pos = 0
    for _ in range(BANK_SAMPLES):
        name, words, _, volume, start, length = struct.unpack_from('>22sHBBHH', data, pos)
        pos += 30
        size = words * 2
        samples.append({'name': name.split(b'\0')[0].decode('latin-1'), 'data': data[pos:pos + size],
                        'volume': volume, 'loop_start': start * 2 if length * 2 > 2 else 0,
                        'loop_length': length * 2 if length * 2 > 2 else 0})
        pos += size
    if pos != len(data):
        sys.exit('BANK1.GSP: %d bytes left' % (len(data) - pos))
    return samples


def wav(pcm, rate):
    return (b'RIFF' + struct.pack('<I', 36 + len(pcm)) + b'WAVEfmt ' +
            struct.pack('<IHHIIHH', 16, 1, 1, rate, rate, 1, 8) + b'data' +
            struct.pack('<I', len(pcm)) + pcm)


def module(name, tune, image, samples):
    """MUSn.VXL and its instruments as a ProTracker-style module. `image(address, size)` reads
    VERTRIX.EXE's image."""
    channels, length = struct.unpack_from('<HH', tune)
    orders = tune[4:132]
    patterns = max(orders) + 1
    cells = tune[132:132 + patterns * 64 * channels * 4]
    out = bytearray(name.encode().ljust(20, b'\0'))
    slots = []
    for slot in range(1, 32):
        number = image(TUNE_SAMPLES + tune_number(name) * 31 + slot, 1)[0]
        s = samples[number] if number else None
        slots.append(number)
        if s is None or not s['data']:
            out += b'\0' * 22 + struct.pack('>HBBHH', 0, 0, 0, 0, 1)
            continue
        loop_words = s['loop_length'] // 2
        out += (('%d %s' % (number, s['name'])).encode('latin-1')[:22].ljust(22, b'\0') +
                struct.pack('>HBBHH', len(s['data']) // 2, 0, s['volume'], s['loop_start'] // 2,
                            loop_words if loop_words else 1))
    out += bytes([length, 0x7f]) + orders
    out += b'M.K.' if channels == 4 else ('%dCHN' % channels).encode()
    for i in range(0, len(cells), 4):
        note, instrument, parameter, effect = cells[i:i + 4]
        p = struct.unpack('<H', image(PERIODS + 2 * note, 2))[0] if note else 0
        effect &= 0xf
        if effect not in ROW_EFFECTS:
            effect = parameter = 0
        elif effect == 0xd:
            parameter = 0
        out += bytes([(instrument & 0xf0) | (p >> 8), p & 0xff, ((instrument & 0xf) << 4) | effect,
                      parameter])
    for number in slots:
        if number and samples[number]['data']:
            out += samples[number]['data']
    return bytes(out), {'channels': channels, 'length': length, 'patterns': patterns,
                        'instruments': [n for n in slots if n]}


def tune_number(name):
    return int(name[3:].split('.')[0])


def render(mod, mp3):
    if not shutil.which('openmpt123') or not shutil.which('lame'):
        return False
    with tempfile.TemporaryDirectory() as folder:
        wav_path = Path(folder) / 'tune.wav'
        # Once through the song (the game loops it), mono as the Sound Blaster plays it.
        subprocess.run(['openmpt123', '--batch', '--quiet', '--no-float', '--repeat', '0',
                        '--end-time', '240', '--channels', '1', '--samplerate', '44100',
                        '-o', str(wav_path), str(mod)],
                       check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        subprocess.run(['lame', '--quiet', '-V', '4', str(wav_path), str(mp3)], check=True)
    return True


def png(path, width, height, indices, palette):
    rows = b''.join(b'\0' + indices[y * width:(y + 1) * width] for y in range(height))

    def chunk(kind, body):
        return (struct.pack('>I', len(body)) + kind + body +
                struct.pack('>I', zlib.crc32(kind + body) & 0xffffffff))

    Path(path).write_bytes(b'\x89PNG\r\n\x1a\n' +
                           chunk(b'IHDR', struct.pack('>IIBBBBB', width, height, 8, 3, 0, 0, 0)) +
                           chunk(b'PLTE', bytes(palette)) +
                           chunk(b'IDAT', zlib.compress(rows, 9)) + chunk(b'IEND', b''))


# The palette each picture is shown with: the game sets it from one of the .PAL files. These are
# the ones that give the screens the game shows (the intro's and the title's under INTRO.PAL,
# the rest under GAME.PAL); GAMEPAL1-7 are GAME.PAL's tinted variants.
PICTURE_PALETTES = {'INTRO1.MXB': 'INTRO.PAL', 'INTRO2.MXB': 'INTRO.PAL',
                    'INTROMSQ.MXB': 'INTRO.PAL', 'CLUSTERS.MXB': 'LOGO.PAL'}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('exe')
    parser.add_argument('bin1')
    parser.add_argument('out', type=Path)
    args = parser.parse_args()
    p = r1.LEProgram(args.exe)

    def image(address, size):
        return p.image[address - p.base:address - p.base + size]

    data = Path(args.bin1).read_bytes()
    files = entries(data)
    out = args.out
    for sub in ('raw', 'pictures', 'sounds', 'instruments', 'music'):
        (out / sub).mkdir(parents=True, exist_ok=True)
    page = {'entries': [], 'pictures': [], 'palettes': {}, 'sounds': [], 'instruments': [],
            'tunes': [], 'font': None}

    for name, (offset, body) in files.items():
        unpacked = vxl(body) if name.endswith('.VXL') else (
            unlzw(body) if name.endswith('.MXB') else body)
        (out / 'raw' / name).write_bytes(unpacked)
        page['entries'].append({'name': name, 'offset': offset, 'size': len(body),
                                'unpacked': len(unpacked)})

    for name, (_, body) in files.items():
        if name.endswith('.PAL'):
            page['palettes'][name] = list(body)

    for name, (_, body) in files.items():
        if name.endswith('.MXB'):
            indices = unlzw(body)
            height = len(indices) // 320
            palette = PICTURE_PALETTES.get(name, 'GAME.PAL')
            png(out / 'pictures' / (name[:-4] + '.png'), 320, height, indices,
                files[palette][1])
            page['pictures'].append({'name': name, 'width': 320, 'height': height,
                                     'palette': palette,
                                     'indices': base64.b64encode(zlib.compress(indices, 9)).decode()})

    for name, (_, body) in files.items():
        if name.startswith('FX'):
            sound = vxl(body)
            (out / 'sounds' / (name[:-4] + '.wav')).write_bytes(sound)
            rate, bits = struct.unpack_from('<I', sound, 24)[0], struct.unpack_from('<H', sound, 34)[0]
            page['sounds'].append({'name': name, 'file': 'sounds/%s.wav' % name[:-4], 'rate': rate,
                                   'bits': bits, 'seconds': round((len(sound) - 44) / rate, 2)})

    samples = bank(files['BANK1.GSP'][1])
    for number in range(1, len(samples)):
        s = samples[number]
        entry = {'number': number, 'name': s['name'], 'bytes': len(s['data']),
                 'volume': s['volume'], 'loop_start': s['loop_start'],
                 'loop_length': s['loop_length']}
        if s['data']:
            pcm = bytes((b + 128) & 0xff for b in s['data'])
            file = 'instruments/%03d.wav' % number
            (out / file).write_bytes(wav(pcm, SAMPLE_RATE))
            entry['file'] = file
        page['instruments'].append(entry)

    tunes = sorted((n for n in files if n.startswith('MUS')), key=tune_number)
    for name in tunes:
        mod, info = module(name, vxl(files[name][1]), image, samples)
        stem = 'MUS%02d' % tune_number(name)
        (out / 'music' / (stem + '.mod')).write_bytes(mod)
        info.update({'name': name, 'mod': 'music/%s.mod' % stem})
        if render(out / 'music' / (stem + '.mod'), out / 'music' / (stem + '.mp3')):
            info['mp3'] = 'music/%s.mp3' % stem
        page['tunes'].append(info)
        print(name, info['channels'], 'channels', info['patterns'], 'patterns',
              len(info['instruments']), 'instruments')

    car = files['INSTVGA.CAR'][1]
    glyphs = []
    pos = 0
    while pos + 4 <= len(car):
        width, height = struct.unpack_from('<HH', car, pos)
        glyphs.append(base64.b64encode(car[pos + 4:pos + 4 + width * height]).decode())
        pos += 4 + width * height
    page['font'] = {'width': 8, 'height': 8, 'first': 32, 'glyphs': glyphs}

    (out / 'data.js').write_text('const VERTRIX = ' + json.dumps(page) + ';\n')
    shutil.copy(Path(__file__).resolve().parent / 'assets.html', out / 'index.html')
    print('%d entries, %d pictures, %d sounds, %d instruments, %d tunes -> %s' % (
        len(files), len(page['pictures']), len(page['sounds']), len(samples) - 1, len(tunes),
        out / 'index.html'))


if __name__ == '__main__':
    main()

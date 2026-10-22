"""Unpack a Vertrix 2 installer (v1.2 or v2.0), a self-extracting ACE 1.0 archive, without running
it.

The archive follows the extractor stub, at the first `**ACE**` signature (7 bytes into the
archive's main header). acefile (https://www.roe.ch/acefile, `pip install acefile==0.6.14`) does
not find that header inside the stub; cut out on its own, it refuses the header until its main
header flags carry bit 12, so the copy here sets it and recomputes the header's CRC.

usage: unace_sfx.py INSTALLER.exe OUT_DIR
"""
import struct
import sys
import tempfile
from pathlib import Path

import acefile


def main():
    installer, out = sys.argv[1], Path(sys.argv[2])
    data = Path(installer).read_bytes()
    start = data.find(b'**ACE**') - 7
    if start < 0:
        sys.exit('%s: no ACE archive' % installer)
    archive = bytearray(data[start:])
    size = struct.unpack_from('<H', archive, 2)[0]
    flags = struct.unpack_from('<H', archive, 5)[0]
    struct.pack_into('<H', archive, 5, flags | 1 << 12)
    struct.pack_into('<H', archive, 0, acefile.ace_crc16(bytes(archive[4:4 + size])))
    out.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(suffix='.ace') as copy:
        copy.write(archive)
        copy.flush()
        with acefile.open(copy.name) as ace:
            ace.extractall(path=str(out))
            bad = ace.testall()
            if bad:
                sys.exit('%s: CRC errors in %s' % (installer, bad))
            for member in ace.getmembers():
                print(member.filename, member.size)


if __name__ == '__main__':
    main()

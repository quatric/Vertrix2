"""Write the mapped image of Vertrix2.exe (0x400000..0x600000) for tools/host_probe.c."""
import sys
from pathlib import Path

import pefile

root = Path(__file__).resolve().parents[1]
pe = pefile.PE(str(root / 'Vertrix2.exe'))
image = bytearray(0x200000)
data = pe.get_memory_mapped_image()
image[:len(data)] = data[:0x200000]
Path(sys.argv[1]).write_bytes(bytes(image))

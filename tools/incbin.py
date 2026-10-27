#!/usr/bin/env python3
"""Writes the C file that builds a file into a program, as the arrays and sizes the shell reads:

    incbin.py <target triple> <file> <name>      e.g. x86_64-linux-gnu, v3_image.bin, v3_image_bin

gives `const unsigned char <name>[]` (the file, by .incbin) and `const unsigned <name>_size`.
The data directive and the symbol's prefix depend on the object format of the target.
"""
import os
import sys


def main():
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    target, path, name = sys.argv[1:]
    path = os.path.abspath(path).replace("\\", "/")
    size = os.path.getsize(path)
    if "apple" in target or "darwin" in target:
        section, symbol = '.section __DATA,__const', "_" + name
    elif "mingw" in target or "windows" in target:
        # 32-bit Windows prefixes C symbols with an underscore, 64-bit does not
        section, symbol = '.section .rdata,\\"dr\\"', ("_" + name) if target.startswith("i") else name
    else:
        section, symbol = ".section .rodata", name
    print(f'''/* made by tools/incbin.py */
__asm__(
    "{section}\\n"
    ".balign 16\\n"
    ".globl {symbol}\\n"
    "{symbol}:\\n"
    ".incbin \\"{path}\\"\\n"
    ".text\\n");
extern const unsigned char {name}[];
const unsigned {name}_size = {size}u;''')


if __name__ == "__main__":
    main()

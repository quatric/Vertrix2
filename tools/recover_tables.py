"""Recover character and delay tables from the verified original executable."""

import argparse
import json
import struct
import subprocess
from pathlib import Path

from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    original = Original(args.executable)
    powers = [[original.power(character, slot) for slot in range(28)] for character in range(19)]
    speeds = original.speeds()
    delays = struct.unpack("<180I", original.pe.get_data(0xF8D84, 720))
    text = [
        "/* Recovered from the fingerprinted original; regenerate with tools/recover_tables.py. */",
        "#ifndef VERTRIX_RECOVERED_H", "#define VERTRIX_RECOVERED_H", "#include <stdint.h>",
        "/* 0x00417c80 / 0x004178d0: seven rows of four slots per character. */",
        "static const signed char character_powers[19][28] = {",
    ]
    text.extend("{" + ",".join(map(str, row)) + "}," for row in powers)
    text.extend([
        "};", "/* Data at 0x004f8d38. */",
        "static const uint32_t character_speed[19] = {" + ",".join(map(str, speeds)) + "};",
        "/* Data at 0x004f8d84: difficulty, parameter row, speed index. */",
        "static const uint32_t character_delays[3][6][10] = {",
    ])
    for difficulty in range(3):
        text.append("{")
        for row in range(6):
            start = difficulty * 60 + row * 10
            text.append("{" + ",".join(map(str, delays[start : start + 10])) + "},")
        text.append("},")
    text.extend(["};", "/* Side-shift patterns 0..2 at 0x004f9ad8. */",
                 "static const uint8_t side_shift_masks[3][13] = {"])
    masks = original.pe.get_data(0xF9AD8, 39)
    for pattern in range(3):
        text.append("{" + ",".join(map(str, masks[pattern * 13 : pattern * 13 + 13])) + "},")
    text.append("};")
    for name, address in [("piece_motion_period", 0xF7D50), ("piece_motion_step", 0xF7DC8)]:
        values = struct.unpack("<30I", original.pe.get_data(address, 120))
        text.extend([f"/* Original data at {address + 0x400000:#010x}. */",
                     f"static const uint32_t {name}[3][10] = {{"])
        for difficulty in range(3):
            text.append("{" + ",".join(map(str, values[difficulty * 10 : difficulty * 10 + 10])) + "},")
        text.append("};")
    for name, address in [("piece_fast_period", 0xF7D14), ("piece_fast_step", 0xF7D20)]:
        values = struct.unpack("<3I", original.pe.get_data(address, 12))
        text.extend([f"/* Original data at {address + 0x400000:#010x}. */",
                     f"static const uint32_t {name}[3] = {{" + ",".join(map(str, values)) + "};"])
    text.extend(["#endif", ""])
    header = root / "source/recovered.h"
    header.write_text("\n".join(text))
    subprocess.run(["clang-format", "-i", str(header)], check=True)
    (root / "docs/character-powers.json").write_text(json.dumps(powers, indent=2) + "\n")
    (root / "docs/character-delays.json").write_text(json.dumps({
        "speeds": speeds,
        "delays": [[list(delays[d * 60 + r * 10 : d * 60 + r * 10 + 10]) for r in range(6)]
                   for d in range(3)],
    }, indent=2) + "\n")
    print("Recovered 532 power slots, 19 speed indices, and 180 delay parameters")


if __name__ == "__main__":
    main()

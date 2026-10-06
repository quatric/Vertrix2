"""Extract verified original renderer flag rules and function dispatch table."""
import argparse
import json
import struct
from pathlib import Path
from original import Original

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable",type=Path)
    parser.add_argument("header",type=Path)
    parser.add_argument("report",type=Path)
    args=parser.parse_args()
    original=Original(args.executable)
    rules=list(struct.iter_unpack("<II",original.cpu.mem_read(0x4FED44,92*8)))
    rows=[list(struct.unpack("<92I",original.cpu.mem_read(0x4FF024+row*92*4,92*4))) for row in range(4)]
    lines=["/* Original rule table 0x4fed44 and dispatch table 0x4ff024. */",
           "#ifndef VERTRIX_RENDER_DISPATCH_TABLES_H","#define VERTRIX_RENDER_DISPATCH_TABLES_H",
           "#include <stdint.h>","static const uint32_t render_rules[92][2] = {"]
    lines += ["{0x%08xu, 0x%08xu},"%rule for rule in rules]
    lines += ["};","static const uint32_t render_addresses[4][92] = {"]
    for row in rows:
        lines.append("{")
        lines += ["0x%08xu,"%address for address in row]
        lines.append("},")
    lines += ["};","#endif",""]
    args.header.write_text("\n".join(lines))
    args.report.write_text(json.dumps({"rules":rules,"kernel_rows":rows,
        "format_rows":[4,2,1,0],"scope":"Original addresses are evidence identifiers, not callable native functions."},indent=2)+"\n")

if __name__=="__main__":
    main()

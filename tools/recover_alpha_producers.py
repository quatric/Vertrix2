"""Verify drawing-object alpha overrides at exact executable instructions."""
import argparse
import json
from pathlib import Path
import capstone
from original import Original


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("report", type=Path)
    args = parser.parse_args()
    original = Original(args.executable)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    sites = [0x46711e, 0x46773a, 0x469bd2, 0x469dd0, 0x46e49a,
             0x46e618, 0x472699, 0x473150, 0x47329a, 0x4733c1]
    evidence = []
    for address in sites + [0x4ac10e]:
        instruction = next(decoder.disasm(bytes(original.cpu.mem_read(address, 16)), address))
        expected = "dword ptr [eax + 0x150], 0" if address == 0x4ac10e else "dword ptr [esi + 0x150], 1"
        assert instruction.mnemonic == "mov" and instruction.op_str == expected
        evidence.append({"address": hex(address), "instruction": instruction.mnemonic + " " + instruction.op_str})
    args.report.write_text(json.dumps({"status": "passed", "sites": evidence,
        "scope": "Exact drawing-object default and explicit override stores; does not infer asset-driven selection or recover entire constructors."}, indent=2) + "\n")
    print(f"Verified {len(evidence)} original alpha-state stores")


if __name__ == "__main__":
    main()

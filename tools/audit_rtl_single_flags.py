#!/usr/bin/env python3
"""Audit direct original single-arithmetic callers' integer-flag liveness.

Run from any directory. Requires the original oracle environment (Capstone,
pefile, Unicorn). This is a static direct-call audit, not an execution proof
for indirect callers or the complete game.
"""
import argparse
import collections
import hashlib
import json
import struct
import sys
from pathlib import Path
from unittest.mock import patch

import pefile
from capstone import x86_const as X

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from original import EXECUTABLE_SHA256

ROOTS = (0x404730, 0x405720, 0x407830, 0x4083a0, 0x408800, 0x4088e0,
         0x4095d0, 0x40a190, 0x474560, 0x474910, 0x4ac3d0, 0x4ac560,
         0x4ac660, 0x4b7cf0, 0x423960, 0x43d880, 0x4aca00)
TARGETS = (0x4d809c, 0x4d80a6, 0x4d8177, 0x4d81fe)
WRAPPERS = (0x4ac3d0, 0x4ac560, 0x4ac660, 0x4b7cf0)


def direct_calls(image, targets):
    result = {}
    for section in image.sections:
        if not section.Characteristics & 0x20000000:
            continue
        data = section.get_data()
        base = image.OPTIONAL_HEADER.ImageBase + section.VirtualAddress
        for offset in range(len(data) - 4):
            if data[offset] == 0xe8:
                target = (base + offset + 5 + struct.unpack_from(
                    "<i", data, offset + 1)[0]) & 0xffffffff
                if target in targets:
                    result[base + offset] = target
    return result

FLAGS = ("CF", "PF", "AF", "ZF", "SF", "OF")
ALL = set(FLAGS)


def flags(insn, classes):
    # Capstone shares eflags/fpu_flags storage; x87 bits are not integer EFLAGS.
    if insn.group(X.X86_GRP_FPU):
        return set()
    return {flag for flag in FLAGS if any(
        insn.eflags & getattr(X, "X86_EFLAGS_" + kind + "_" + flag, 0)
        for kind in classes)}


def walk(start):
    pending = [(start, frozenset(FLAGS), [])]
    seen = set()
    result = []
    while pending:
        address, live, path = pending.pop()
        if (address, live) in seen:
            continue
        seen.add((address, live))
        insn = lift.insn_at(address)
        if not insn or len(seen) > 1000:
            result.append(("unresolved", address, sorted(live), path))
            continue
        path = path + [(hex(address), insn.mnemonic, insn.op_str)]
        reads = flags(insn, ("TEST", "PRIOR"))
        if insn.mnemonic in ("pushfd", "pushf"):
            reads = ALL
        if insn.mnemonic == "lahf":
            reads = ALL - {"OF"}
        if reads & live:
            result.append(("consume", address, sorted(reads & live), path))
            continue
        if insn.mnemonic == "ret":
            result.append(("return", address, sorted(live), path))
            continue
        if insn.mnemonic == "call":
            result.append(("call", address, sorted(live), path))
            continue
        writes = flags(insn, ("MODIFY", "RESET", "SET", "UNDEFINED"))
        if insn.mnemonic in ("shl", "sal", "shr", "sar", "rcl", "rcr", "rol", "ror"):
            if len(insn.operands) > 1:
                count = insn.operands[1]
                if count.type != X.X86_OP_IMM or not count.imm & 31:
                    writes = set()
        live = live - writes
        if not live:
            result.append(("killed", address, [], path))
            continue
        following = address + insn.size
        if insn.mnemonic == "jmp":
            if insn.operands[0].type == X.X86_OP_IMM:
                pending.append((insn.operands[0].imm, frozenset(live), path))
            else:
                result.append(("indirect", address, sorted(live), path))
        else:
            pending.append((following, frozenset(live), path))
            if insn.mnemonic in lift.CONDITIONS or insn.mnemonic in (
                    "loop", "loope", "loopne", "jecxz"):
                pending.append((insn.operands[0].imm, frozenset(live), path))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--executable", type=Path, default=ROOT / "Vertrix2.exe")
    parser.add_argument("--output", type=Path,
                        default=ROOT / "docs/rtl-single-caller-flags-audit.json")
    args = parser.parse_args()
    data = args.executable.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != EXECUTABLE_SHA256:
        raise ValueError("Audit requires the verified original executable")
    image = pefile.PE(data=data)
    # lift.py's legacy module-level image path is bypassed without changing it.
    global lift
    with patch("pefile.PE", return_value=image):
        import lift
    lift.pe = image
    lift.BASE = image.OPTIONAL_HEADER.ImageBase
    sites = direct_calls(image, TARGETS)
    validated = set()
    flag_live = set()
    roots = {}
    for root in ROOTS:
        lifter = lift.Lifter(root, "flag_audit")
        owned = set(sites) & set(lifter.insns)
        for address in owned:
            insn = lifter.insns[address]
            if insn.mnemonic != "call" or insn.operands[0].imm != sites[address]:
                raise AssertionError("Scan candidate is not a decoded direct call")
        validated.update(owned)
        flag_live.update(a for a in owned if lifter.flags_live[a])
        roots[hex(root)] = [hex(a) for a in sorted(owned)]
    assert validated == set(sites), "Direct-call scan contains unvalidated instructions"
    assert len(sites) == 795, "Original callsite coverage changed"
    assert flag_live == {0x4ac3f5, 0x4ac585, 0x4ac685, 0x4b7d00}
    paths = {hex(a): {"target": hex(t), "paths": walk(a + 5)}
             for a, t in sorted(sites.items())}
    counts = collections.Counter(p[0] for r in paths.values() for p in r["paths"])
    assert counts == {"call": 761, "killed": 30, "return": 4}, counts
    wrapper_sites = direct_calls(image, WRAPPERS)
    assert wrapper_sites == {0x43d930: 0x4ac560, 0x43daef: 0x4ac560,
                             0x43e3cd: 0x4ac560}
    # Validate reverse-wrapper scan instruction boundaries independently.
    for root, expected in ((0x43d880, {0x43d930, 0x43daef}),
                           (0x43e340, {0x43e3cd})):
        instructions = lift.trace(root)
        for address in expected:
            insn = instructions.get(address)
            assert insn and insn.mnemonic == "call" and insn.operands[0].imm == 0x4ac560
    wrapper_paths = {hex(a): {"target": hex(t), "paths": walk(a + 5)}
                     for a, t in sorted(wrapper_sites.items())}
    assert all(p[0] in ("killed", "call") for r in wrapper_paths.values()
               for p in r["paths"])
    # These subsequent call boundaries must define flags before reading inherited
    # values. Retain their exact decoded proof prefixes in the report.
    boundary_entries = (0x4d809c, 0x4d80a6, 0x4d8177, 0x4d8227,
                        0x4d8217, 0x4d8204, 0x4d82bb,
                        0x4e223c, 0x4d82c6, 0x4eb526, 0x4d67a8, 0x4d67e4)
    boundaries = {hex(a): walk(a) for a in boundary_entries}
    assert all(p[0] in ("killed", "call") for ps in boundaries.values() for p in ps)
    report = {
        "passed": True, "executable_sha256": digest,
        "scope": "Static original executable direct calls, rooted CFG instruction boundaries and current lifter flag liveness; not whole-game or indirect-call execution proof.",
        "liveness_definition": "Track CF/PF/AF/ZF/SF/OF separately. TEST/PRIOR reads consume live flags; MODIFY/RESET/SET/UNDEFINED replace inherited values. Variable or zero-count shifts conservatively retain flags. Follow direct CFG successors. Calls are inspected separately at their entry boundaries; RET propagates flags without consuming them.",
        "lifter_definition": "Current tools/lift.py flags_live treats RET as a flag read and CALL as a kill; the four live arithmetic sites only propagate to RET.",
        "callsite_count": len(sites), "validated_instruction_count": len(validated),
        "target_counts": {hex(t): sum(v == t for v in sites.values()) for t in TARGETS},
        "terminal_counts": dict(counts), "observed_flag_consumers": 0,
        "rooted_cfg_calls": roots, "lifter_flag_live_sites": [hex(a) for a in sorted(flag_live)],
        "callsites": paths,
        "propagating_wrappers": {hex(a): [hex(s) for s, t in wrapper_sites.items() if t == a]
                                 for a in WRAPPERS},
        "wrapper_caller_paths": wrapper_paths, "subsequent_callee_prefixes": boundaries,
        "defined_vs_undefined": "Returned flags depend on arithmetic mode/path. Logical OR/XOR paths define CF/OF/SF/ZF/PF but leave AF architecturally undefined; normal hardware CMP returns define all six. This audit does not assign deterministic values to undefined flags or implement returned flags.",
        "limitations": ["Computed indirect callers and external consumers are not resolved.",
                        "No claim about x87 status, unmasked traps or full-game execution.",
                        "Delegated exceptional callback implementations require their own scope/proof."]}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Passed: {len(sites)} instruction-validated direct calls; zero inherited-flag consumers; {args.output}")


if __name__ == "__main__":
    main()

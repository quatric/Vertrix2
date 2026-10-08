#!/usr/bin/env python3
"""Audit EBX/ECX after direct original double-add/multiply calls.

This local static analysis stops at the next call; it does not assume that
callee preserves, kills, or consumes incoming registers. PUSH counts as a
read, including save-only uses. Requires the original oracle environment.
"""
import argparse
import collections
import hashlib
import json
from pathlib import Path
from unittest.mock import patch

import pefile
from capstone import x86_const as X

from audit_rtl_single_flags import direct_calls
from original import EXECUTABLE_SHA256

ROOT = Path(__file__).resolve().parents[1]
TARGETS = (0x4db350, 0x4db507)
ROOTS = (0x406170, 0x40a590, 0x40ba00, 0x474560, 0x474910,
         0x4c9921, 0x4c9b6a, 0x4c9e2f, 0x4daed8, 0x4db6a4,
         0x4db6d9, 0x4e7200)
ALIASES = {X.X86_REG_EBX: "ebx", X.X86_REG_BX: "ebx",
           X.X86_REG_BL: "ebx", X.X86_REG_BH: "ebx",
           X.X86_REG_ECX: "ecx", X.X86_REG_CX: "ecx",
           X.X86_REG_CL: "ecx", X.X86_REG_CH: "ecx"}
FULL = {X.X86_REG_EBX, X.X86_REG_ECX}


def walk(start, registers=("ebx", "ecx"), preserve_calls=()):
    pending = [(start, frozenset(registers), [])]
    seen = set()
    result = []
    while pending:
        address, live, path = pending.pop()
        if (address, live) in seen:
            continue
        seen.add((address, live))
        insn = lift.insn_at(address)
        if not insn or len(seen) > 2000:
            result.append(("unresolved", hex(address), sorted(live), path))
            continue
        path = path + [(hex(address), insn.mnemonic, insn.op_str)]
        if (insn.mnemonic == "call" and insn.operands[0].type == X.X86_OP_IMM
                and insn.operands[0].imm in preserve_calls):
            pending.append((address + insn.size, live, path))
            continue
        if insn.mnemonic in ("call", "ret"):
            result.append((insn.mnemonic, hex(address), sorted(live), path))
            continue
        read, write = insn.regs_access()
        reads = {ALIASES[r] for r in read if r in ALIASES}
        writes = {ALIASES[r] for r in write if r in FULL}
        # Zeroing idioms do not depend on the previous operand value.
        if insn.mnemonic in ("xor", "sub") and len(insn.operands) == 2:
            first, second = insn.operands
            if (first.type == second.type == X.X86_OP_REG and
                    first.reg == second.reg):
                reads = set()
        if reads & live:
            result.append(("consume", hex(address), sorted(reads & live), path))
            continue
        live = live - writes
        if not live:
            result.append(("killed", hex(address), [], path))
            continue
        if insn.mnemonic == "jmp":
            if insn.operands[0].type == X.X86_OP_IMM:
                pending.append((insn.operands[0].imm, frozenset(live), path))
            else:
                result.append(("indirect", hex(address), sorted(live), path))
        else:
            pending.append((address + insn.size, frozenset(live), path))
            if insn.mnemonic in lift.CONDITIONS or insn.mnemonic in (
                    "loop", "loope", "loopne", "jecxz"):
                pending.append((insn.operands[0].imm, frozenset(live), path))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--executable", type=Path, default=ROOT / "Vertrix2.exe")
    parser.add_argument("--output", type=Path,
                        default=ROOT / "docs/rtl-double-caller-register-audit.json")
    args = parser.parse_args()
    data = args.executable.read_bytes()
    digest = hashlib.sha256(data).hexdigest()
    if digest != EXECUTABLE_SHA256:
        raise ValueError("Audit requires the verified original executable")
    image = pefile.PE(data=data)
    global lift
    with patch("pefile.PE", return_value=image):
        import lift
    lift.pe = image
    lift.BASE = image.OPTIONAL_HEADER.ImageBase
    sites = direct_calls(image, TARGETS)
    validated = set()
    roots = {}
    for root in ROOTS:
        instructions = lift.trace(root)
        found = set(sites) & set(instructions)
        for address in found:
            insn = instructions[address]
            assert insn.mnemonic == "call" and insn.operands[0].imm == sites[address]
        validated.update(found)
        roots[hex(root)] = [hex(a) for a in sorted(found)]
    assert validated == set(sites) and len(sites) == 88
    paths = {hex(a): {"target": hex(t), "paths": walk(a + 5)}
             for a, t in sorted(sites.items())}
    counts = collections.Counter(p[0] for r in paths.values() for p in r["paths"])
    assert counts == {"killed": 58, "call": 33, "ret": 3}, counts
    # Additional inspection resolves the three RET propagation paths. These
    # explicit summaries are limited to inspected conversion/sign routines:
    # 4eb606 has no ECX accesses; 4d6768 saves/restores ECX around its scratch
    # use; 4eb526 does likewise. 4dae4a and 4dad19 never access EBX/ECX.
    summaries = (0x4eb606, 0x4d6768, 0x4eb526, 0x4dae4a, 0x4dad19)
    reverse = direct_calls(image, (0x4c9921, 0x4db6a4, 0x4db6d9))
    reverse_instructions = {}
    for root in (*ROOTS, 0x4c98fc):
        reverse_instructions.update(lift.trace(root))
    for address, target in reverse.items():
        insn = reverse_instructions[address]
        assert insn.mnemonic == "call" and insn.operands[0].imm == target
    continuations = {
        hex(a): {"target": hex(t), "paths": walk(
            a + 5, ("ecx",) if t == 0x4c9921 else ("ebx", "ecx"), summaries)}
        for a, t in sorted(reverse.items())}
    assert all(p[0] != "consume" for r in continuations.values() for p in r["paths"])
    # Enclosing 4c9b6a restores ECX, and each direct caller restores EBX.
    polynomial_callers = direct_calls(image, (0x4c9b6a,))
    assert set(polynomial_callers) == {0x4c9dc2, 0x4c9dec, 0x4c9e16}
    restores = {0x4c9d9a: "ecx", 0x4c9dc7: "ebx",
                0x4c9df1: "ebx", 0x4c9e1b: "ebx"}
    for address, register in restores.items():
        insn = lift.insn_at(address)
        assert insn.mnemonic == "pop" and insn.op_str == register
    conversion_evidence = {}
    for entry in summaries:
        instructions = lift.trace(entry)
        conversion_evidence[hex(entry)] = [
            (hex(a), i.mnemonic, i.op_str) for a, i in sorted(instructions.items())]
    # A next-call boundary to the error helper occurs with only ECX live;
    # its entry pushes ECX and immediately replaces it with EAX. It consumes
    # the explicitly reloaded EBX pointer, not a polynomial result.
    assert lift.insn_at(0x4dad3b).mnemonic == "push"
    assert lift.insn_at(0x4dad40).op_str == "ecx, eax"
    report = {
        "passed": True, "executable_sha256": digest,
        "scope": "Local static direct-call audit for double add/multiply; stops at subsequent calls and returns. The separate 795-call single-integer-flags audit is not evidence of double-register non-use.",
        "liveness_definition": "Track EBX/ECX and all register aliases. Register/memory-address reads consume live values. Only full-width writes kill a value; zeroing XOR/SUB is independent of previous contents. Branches follow both successors; calls and returns are explicit unresolved boundaries.",
        "callsite_count": len(sites), "validated_instruction_count": len(validated),
        "target_counts": {hex(t): sum(v == t for v in sites.values()) for t in TARGETS},
        "terminal_counts": dict(counts), "local_consumers_before_next_call": 0,
        "terminal_count_note": "Counts describe CFG terminal paths and can exceed callsite count.",
        "rooted_cfg_calls": roots, "callsites": paths,
        "return_propagations": {
            "0x4c9aa8": {"wrapper": "0x4c9921", "registers": ["ecx"]},
            "0x4db6ca": {"wrapper": "0x4db6a4", "registers": ["ebx", "ecx"]},
            "0x4db703": {"wrapper": "0x4db6d9", "registers": ["ebx", "ecx"]}},
        "return_propagation_followup": {
            "conclusion": "No data consumer found among the inspected direct reverse callers of the three propagating wrappers. This does not resolve arbitrary indirect callers or all 33 local next-call boundaries.",
            "validated_reverse_calls": len(reverse),
            "direct_reverse_paths": continuations,
            "inspected_preservation_summaries": conversion_evidence,
            "enclosing_polynomial_ecx_restore": "0x4c9d9a POP ECX restores entry ECX saved at 0x4c9b6d",
            "enclosing_polynomial_ebx_callers": {
                hex(a): "Following POP EBX restores wrapper entry EBX, replacing polynomial EBX"
                for a in sorted(polynomial_callers)},
            "error_boundary": "4dad38 saves ECX at4dad3b and replaces it with EAX at4dad40; EBX pointer is explicitly reloaded at4c9d78 before call4c9d88."},
        "limitations": ["Subsequent-call preservation and use require interprocedural analysis.",
                        "Return propagation does not establish absence of downstream consumers.",
                        "Computed indirect callers and complete game execution are outside scope."]}
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n")
    print(f"Passed: {len(sites)} decoded direct calls, zero local consumers; {args.output}")


if __name__ == "__main__":
    main()

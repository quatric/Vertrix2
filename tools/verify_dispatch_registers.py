"""Compare constant and unchanged-return leaf EAX/EDX through real lifted dispatch against executable code."""
import ast
import ctypes
import hashlib
import json
import subprocess
import tempfile
from pathlib import Path

from original import Original
from unicorn.x86_const import UC_X86_REG_EDX


def main():
    root = Path(__file__).resolve().parents[1]
    tree = ast.parse((root / "tools/verify_constant_returns.py").read_text())
    assignment = next(node for node in ast.walk(tree)
                      if isinstance(node, ast.Assign)
                      and any(isinstance(target, ast.Name) and target.id == "routines"
                              for target in node.targets))
    routines = ast.literal_eval(assignment.value)
    removed = {int(value, 16) for value in json.loads(
        (root / "docs/lifted-removed.json").read_text())}
    active = [row for row in routines if row[0] not in removed]
    unchanged = [0x4b9ce0, 0x4bb260, 0x4c5c20, 0x4c6a80, 0x4c93c0]
    active += [(address, "unchanged-return", None) for address in unchanged]
    wrapper = r"""#include <stdint.h>
#include "lifted_dispatch.h"
extern uint32_t vertrix_lift_edx;
uint64_t check_registers(uint32_t target, uint32_t eax, uint32_t edx,
                         uint32_t ebx, uint32_t ecx)
{
    VertrixCallSite site = {0};
    uint32_t result = 0;
    site.target = target;
    site.eax = eax;
    site.edx = edx;
    site.ebx = ebx;
    site.ecx = ecx;
    vertrix_lift_edx = 0xabcdef01;
    if (!vertrix_lifted_dispatch(NULL, NULL, NULL, &site, &result))
    {
        return UINT64_MAX;
    }
    return ((uint64_t)vertrix_lift_edx << 32) | result;
}
"""
    original = Original(root / "Vertrix2.exe")
    inputs = [0, 1, 0x7fffffff, 0x80000000, 0xfffffffe, 0xffffffff]
    cases = 0
    with tempfile.TemporaryDirectory(prefix="vertrix-dispatch-registers-") as directory:
        path = Path(directory)
        (path / "check.c").write_text(wrapper)
        linked = sorted((root / "source").glob("lifted_*.c"))
        linked += [root / "source/actor_storage.c", root / "source/call_glue.c"]
        dependencies = linked + sorted((root / "source").glob("*.h"))

        def source_digest():
            digest = hashlib.sha256()
            for dependency in dependencies:
                digest.update(str(dependency.relative_to(root)).encode())
                digest.update(b"\0")
                digest.update(dependency.read_bytes())
            return digest.hexdigest()

        before = source_digest()
        subprocess.run(["cc", "-std=c11", "-O0", "-shared", "-fPIC", "-Wall",
                        "-Wextra", "-Werror", "-I" + str(root / "source"),
                        str(path / "check.c"), *map(str, linked),
                        "-o", str(path / "check.so")], check=True)
        native = ctypes.CDLL(str(path / "check.so")).check_registers
        native.argtypes = [ctypes.c_uint32] * 5
        native.restype = ctypes.c_uint64
        for address, name, constant in active:
            for index, eax in enumerate(inputs):
                edx = eax ^ 0xffffffff
                ebx, ecx = inputs[(index + 1) % 6], inputs[(index + 2) % 6]
                expected_eax = original.call(address, eax=eax, edx=edx, ebx=ebx, ecx=ecx)
                expected_edx = original.cpu.reg_read(UC_X86_REG_EDX)
                assert expected_eax == (eax if constant is None else constant), (
                    hex(address), name, expected_eax, constant)
                expected = (expected_edx << 32) | expected_eax
                actual = native(address, eax, edx, ebx, ecx)
                assert actual == expected, (hex(address), index, hex(actual), hex(expected))
                cases += 1
        if before != source_digest():
            raise RuntimeError("Compiled source changed during comparison; rerun on stable files")
    report = {"status": "passed", "compiled_source_sha256": before, "entrypoints": len(active), "constant_entrypoints": len(active) - len(unchanged),
              "unchanged_return_entrypoints": len(unchanged), "cases": cases,
              "scope": "Actual original execution versus actual lifted dispatcher EAX and exported EDX for constant and unchanged-return leaf entries, six register-edge fixtures each. No nested callback, floating arithmetic, exceptional path or other routine is verified."}
    (root / "docs/dispatch-register-verification.json").write_text(
        json.dumps(report, indent=2) + "\n")
    print(json.dumps(report))


if __name__ == "__main__":
    main()

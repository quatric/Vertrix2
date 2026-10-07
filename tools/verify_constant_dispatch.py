"""Check constant-return entrypoints through the actual lifted dispatcher."""
import ast
import json
from pathlib import Path
import subprocess
import tempfile


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
    retired = [address for address, name, expected in routines if address in removed]
    fixtures = ",\n".join("    {0x%xu, 0x%xu, %du}" %
                           (address, expected, address in removed)
                           for address, name, expected in routines)
    harness = r'''#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "lifted_dispatch.h"

static const uint32_t fixtures[][3] = {
FIXTURES
};

int main(void)
{
    static const uint32_t inputs[] = {0, 1, 0x7fffffff, 0x80000000, 0xfffffffe, 0xffffffff};
    for (unsigned i = 0; i < sizeof fixtures / sizeof fixtures[0]; ++i)
    {
        if (fixtures[i][2])
        {
            VertrixCallSite site = {0};
            uint32_t result = 0xabcdef01;
            site.target = fixtures[i][0];
            assert(!vertrix_lifted_has(site.target));
            assert(!vertrix_lifted_dispatch(NULL, NULL, NULL, &site, &result));
            assert(result == 0xabcdef01);
            continue;
        }
        if (!vertrix_lifted_has(fixtures[i][0]))
        {
            fprintf(stderr, "Missing constant entrypoint 0x%x\n", fixtures[i][0]);
            return 1;
        }
        for (unsigned j = 0; j < sizeof inputs / sizeof inputs[0]; ++j)
        {
            VertrixCallSite site = {0};
            uint32_t result = ~fixtures[i][1];
            site.target = fixtures[i][0];
            site.eax = inputs[j];
            site.edx = ~inputs[j];
            site.ebx = inputs[(j + 1) % 6];
            site.ecx = inputs[(j + 2) % 6];
            assert(vertrix_lifted_dispatch(NULL, NULL, NULL, &site, &result));
            assert(result == fixtures[i][1]);
        }
    }
    puts("Constant dispatcher cases passed");
    return 0;
}
'''.replace("FIXTURES", fixtures)
    with tempfile.TemporaryDirectory(prefix="vertrix-constant-dispatch-") as directory:
        source = Path(directory) / "check.c"
        executable = Path(directory) / "check"
        source.write_text(harness)
        linked = sorted((root / "source").glob("lifted_*.c"))
        linked += [root / "source/actor_storage.c", root / "source/call_glue.c"]
        subprocess.run(["cc", "-std=c11", "-O0", "-Wall", "-Wextra", "-Werror",
                        "-I" + str(root / "source"), str(source), *map(str, linked),
                        "-o", str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
    report = {"status": "passed", "entrypoints": len(routines) - len(retired),
              "retired_entrypoints": [hex(address) for address in retired],
              "dispatch_cases": (len(routines) - len(retired)) * 6,
              "scope": "Actual lifted dispatch with six unsigned input-register edge fixtures per constant-return entrypoint. Retired entries must decline dispatch and preserve output. No callback, factory or global boundary is supplied. Expected values share the independent original-executable fixtures in verify_constant_returns.py; this integration check does not prove other lifted routines."}
    (root / "docs/constant-dispatch-verification.json").write_text(
        json.dumps(report, indent=2) + "\n")
    print(json.dumps(report))


if __name__ == "__main__":
    main()

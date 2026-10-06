"""Keep only the lifted routines that verify, regenerate source/bonus_lifted.c from them and record
the evidence.

    python3 tools/finalize_lifted.py Vertrix2.exe lreport0.json lreport1.json ... --cases 60

A routine is kept when its report shows no failure and enough completed cases (at least a quarter
of the requested cases, and at least 10).
"""
import argparse
import json
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("reports", type=Path, nargs="+")
    parser.add_argument("--cases", type=int, default=60)
    args = parser.parse_args()
    merged = {}
    for path in args.reports:
        merged.update(json.loads(path.read_text()))
    need = max(10, args.cases // 4)
    kept = sorted(a for a, r in merged.items() if not r["failure"] and r["passed"] >= need)
    weak = sorted(a for a, r in merged.items() if not r["failure"] and r["passed"] < need)
    failed = sorted(a for a, r in merged.items() if r["failure"])
    output = REPO / "source" / "bonus_lifted.c"
    subprocess.run([sys.executable, str(REPO / "tools" / "lift.py"), str(args.executable), *kept,
                    "--output", str(output)], check=True)
    for path in (output, output.with_suffix(".h")):
        subprocess.run(["clang-format", "-i", str(path)], check=True)
    (REPO / "docs" / "lifted-verification.json").write_text(json.dumps({
        "cases_requested": args.cases,
        "kept": {a: merged[a] for a in kept},
        "weak": {a: merged[a] for a in weak},
        "failed": {a: merged[a] for a in failed},
    }, indent=1) + "\n")
    print({"kept": len(kept), "weak": len(weak), "failed": len(failed)})


if __name__ == "__main__":
    main()

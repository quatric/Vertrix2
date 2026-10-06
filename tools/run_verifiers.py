"""Run every tools/verify_*.py against the original executable and compare with docs/*.json.

    python3 tools/prepare_assets.py /tmp/vertrix-work
    python3 tools/run_verifiers.py /tmp/vertrix-work --jobs 4

Each verifier is run with the arguments its usage line asks for (executable, VF archive, extracted
assets, extraction manifest). Its JSON report is compared with the committed evidence in docs/:

  exact       identical to the committed report
  extended    the new report adds keys (committed values all unchanged)
  trimmed     the committed report carries extra hand-written keys
  scope       only prose ("scope") strings differ
  cases=N     the committed counts correspond to --cases N; rerun with N matches
  new         no committed report to compare with
  REVIEW      ran, but numbers differ and no --cases value explains them
  PARTIAL     host part passed; the PowerPC build needs devkitPPC
  SKIP        needs inputs that are not available (see reason)
  FAIL        the verifier raised

Verifiers write their reports into the build directory; the working directory is a throw-away copy
of docs/, so the committed evidence is never modified. Compilers: verifiers call `cc`; a wrapper
is put first on PATH that prefers clang (the toolchain the scripts were written against), uses gcc
for sanitizer builds when clang has no runtime, and maps the macOS-only `-dead_strip` linker flag.
"""
import argparse
import collections
import concurrent.futures
import json
import os
import re
import shutil
import statistics
import subprocess
import sys
import tempfile
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
TOOLS = REPO / "tools"
DOCS = REPO / "docs"

WRAPPER = r"""#!/bin/sh
args=""
san=0
for a in "$@"; do
  case "$a" in
    -Wl,-dead_strip) a="-Wl,--gc-sections";;
    -fsanitize=*) san=1;;
  esac
  args="$args '$a'"
done
if [ $san = 1 ] || ! command -v clang >/dev/null 2>&1; then
  eval exec gcc $args -Wno-type-limits -Wl,--allow-multiple-definition
fi
eval exec clang $args -Wl,--allow-multiple-definition
"""


def leaves(value, prefix=""):
    if isinstance(value, dict):
        for key, item in value.items():
            yield from leaves(item, f"{prefix}{key}.")
    else:
        yield prefix.rstrip("."), value


def compare(produced, committed):
    if produced == committed:
        return "exact"
    if isinstance(produced, dict) and isinstance(committed, dict):
        if all(k in committed and committed[k] == v for k, v in produced.items()):
            return "trimmed"
        if all(k in produced and produced[k] == v for k, v in committed.items()):
            return "extended"
        a, b = dict(leaves(produced)), dict(leaves(committed))
        differing = {k for k in set(a) | set(b) if a.get(k) != b.get(k)}
        if differing and all(isinstance(a.get(k, b.get(k)), str) for k in differing):
            return "scope"
    return "different"


def usage_arguments(script, assets, scratch):
    text = subprocess.run([sys.executable, str(script), "--help"], capture_output=True, text=True,
                          cwd=scratch).stdout
    match = re.search(r"usage:.*?\n\n", text, re.S)
    usage = re.sub(r"\s+", " ", match.group(0) if match else text.split("\n\n")[0])
    usage = re.sub(r"usage: \S+", "", usage)
    usage = re.sub(r"\[[^\]]*\]", "", usage)
    options = re.findall(r"(--[a-z-]+) ([A-Z_]+)", usage)
    usage = re.sub(r"--[a-z-]+ [A-Z_]+", "", usage)
    positionals = [t for t in usage.split() if t.isidentifier() and t.islower()]
    known = {
        "executable": assets / "original" / "Vertrix2.exe",
        "archive": assets / "original" / "Vertrix2.vf",
        "music": assets / "assets" / "musique",
        "references": assets / "assets",
        "extracted_assets": assets / "assets",
        "assets": assets / "assets",
        "manifest": assets / "extraction.json",
        "plan_report": DOCS / "sprite-load-plan-verification.json",
    }
    values, missing = [], []
    for name in positionals:
        if name in known:
            values.append(str(known[name]))
        else:
            missing.append(name)
    for option, _ in options:
        if option == "--build-dir":
            continue
        if option in ("--executable", "--archive"):
            values += [option, str(known[option[2:]])]
        elif option == "--output":
            values += [option, str(scratch / "output.json")]
        else:
            missing.append(option)
    return values, missing


def supports_cases(script):
    return "--cases" in script.read_text()


def run(script, extra, build, scratch, env, timeout):
    build.mkdir(parents=True, exist_ok=True)
    return subprocess.run([sys.executable, str(script), *extra, "--build-dir", str(build)],
                          capture_output=True, text=True, cwd=scratch, env=env, timeout=timeout)


def reports_of(build, scratch, before):
    found = {}
    for path in list(build.glob("*.json")) + [
            p for p in (scratch / "docs").glob("*.json") if before.get(p.name) != p.read_bytes()]:
        if path.name == "output.json":
            continue
        found[path.name] = json.loads(path.read_text())
    return found


def verdict(name, reports):
    results = []
    for filename, produced in reports.items():
        committed_path = DOCS / filename
        if not committed_path.exists():
            results.append("new")
        else:
            results.append(compare(produced, json.loads(committed_path.read_text())))
    return results


def infer_cases(script, reports, default):
    ratios, exact = [], collections.Counter()
    for filename, produced in reports.items():
        path = DOCS / filename
        if not path.exists():
            continue
        a, b = dict(leaves(produced)), dict(leaves(json.loads(path.read_text())))
        for key, value in a.items():
            other = b.get(key)
            if (isinstance(value, int) and isinstance(other, int) and not isinstance(value, bool)
                    and value != other):
                if value == default:
                    exact[other] += 1
                if value >= 100 and other >= 100:
                    ratios.append(other / value)
    candidates = [n for n, _ in exact.most_common(1)]
    if ratios:
        base = default * statistics.median(ratios)
        for quantum in (1000, 500, 100, 50, 10, 1):
            value = int(round(base / quantum) * quantum)
            if value > 0 and value not in candidates:
                candidates.append(value)
    return candidates[:5]


def default_cases(script):
    text = script.read_text()
    match = (re.search(r"--cases['\"]?,[^)]*default\s*=\s*(\d+)", text) or
             re.search(r"default_cases\s*=\s*(\d+)", text))
    return int(match.group(1)) if match else 4096


def classify(script, assets, work, env, timeout):
    name = script.stem
    scratch = work / "cwd" / name
    shutil.rmtree(scratch, ignore_errors=True)
    shutil.copytree(DOCS, scratch / "docs")
    before = {p.name: p.read_bytes() for p in (scratch / "docs").glob("*.json")}
    extra, missing = usage_arguments(script, assets, scratch)
    if missing:
        return name, "SKIP", f"needs {', '.join(missing)}"
    build = work / "build" / name
    try:
        result = run(script, extra, build, scratch, env, timeout)
    except subprocess.TimeoutExpired:
        return name, "FAIL", f"timed out after {timeout}s"
    if result.returncode:
        tail = result.stderr.strip().splitlines()[-1:] or [""]
        if "powerpc" in result.stderr and "CalledProcessError" in result.stderr:
            return name, "PARTIAL", "host part passed; PowerPC build needs devkitPPC"
        return name, "FAIL", tail[0][:200]
    reports = reports_of(build, scratch, before)
    kinds = verdict(name, reports)
    if not kinds:
        return name, "ok", "no report"
    if all(k in ("exact", "trimmed", "extended", "new") for k in kinds):
        return name, "/".join(sorted(set(kinds))), ""
    if all(k in ("exact", "trimmed", "extended", "new", "scope") for k in kinds):
        return name, "scope", "only prose differs from the committed report"
    if supports_cases(script):
        for cases in infer_cases(script, reports, default_cases(script)):
            retry = work / "build" / f"{name}-cases{cases}"
            try:
                again = run(script, extra + ["--cases", str(cases)], retry, scratch, env, timeout)
            except subprocess.TimeoutExpired:
                continue
            if again.returncode:
                continue
            kinds = verdict(name, reports_of(retry, scratch, before))
            if all(k in ("exact", "trimmed", "extended", "new", "scope") for k in kinds):
                return name, f"cases={cases}", "/".join(sorted(set(kinds)))
    return name, "REVIEW", "numbers differ from the committed report"


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("assets", type=Path, help="directory made by tools/prepare_assets.py")
    parser.add_argument("--work", type=Path, default=None)
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    parser.add_argument("--only", default="", help="substring of the verifier name")
    parser.add_argument("--timeout", type=int, default=1800)
    parser.add_argument("--report", type=Path, default=None, help="write the table as JSON")
    args = parser.parse_args()
    assets = args.assets.resolve()
    work = (args.work or Path(tempfile.mkdtemp(prefix="vertrix-verify-"))).resolve()
    (work / "bin").mkdir(parents=True, exist_ok=True)
    wrapper = work / "bin" / "cc"
    wrapper.write_text(WRAPPER)
    wrapper.chmod(0o755)
    env = dict(os.environ, PATH=f"{work / 'bin'}{os.pathsep}{os.environ['PATH']}")
    scripts = sorted(p for p in TOOLS.glob("verify_*.py")
                     if args.only in p.stem and "--build-dir" in p.read_text())
    rows = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as pool:
        futures = [pool.submit(classify, s, assets, work, env, args.timeout) for s in scripts]
        for future in concurrent.futures.as_completed(futures):
            row = future.result()
            rows.append(row)
            print(f"{row[1]:<18} {row[0]}  {row[2]}", flush=True)
    rows.sort()
    summary = collections.Counter(
        "pass" if r[1] not in ("FAIL", "REVIEW", "SKIP", "PARTIAL") else r[1] for r in rows)
    print(dict(summary))
    if args.report:
        args.report.write_text(json.dumps(
            [{"verifier": n, "result": r, "detail": d} for n, r, d in rows], indent=2) + "\n")
    return 1 if summary["FAIL"] or summary["REVIEW"] else 0


if __name__ == "__main__":
    sys.exit(main())

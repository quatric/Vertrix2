"""Shared helpers for the small-routine verifiers: build the native library, patch callees."""
import argparse, ctypes as c, json, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE

DATA = 0x80f300


def parse(description, default_cases=4096):
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=default_cases)
    args = parser.parse_args()
    args.build_dir = args.build_dir.resolve()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    return args


def build(args, name, *sources):
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir / (name + '.dylib')
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror'] +
                   [str(source / s) for s in sources] + ['-o', str(library)], check=True)
    return c.CDLL(str(library))


def stub(cpu, address, on_call, slot=0):
    """Replace the routine at address with 'mov eax, [slot]; ret' and run on_call(cpu) first."""
    cpu.mem_write(address, b'\xa1' + (DATA + 4 * slot).to_bytes(4, 'little') + b'\xc3')
    cpu.hook_add(UC_HOOK_CODE, lambda uc, a, s, x: on_call(uc), begin=address, end=address)


def report(args, name, totals, scope):
    result = {'status': 'passed', 'complete_original_executions': totals, 'scope': scope}
    (args.build_dir / (name + '-verification.json')).write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(result, indent=2))

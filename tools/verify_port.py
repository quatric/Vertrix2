"""Verify a clean port (source/port_*.c) against the original executing in Unicorn.

usage: verify_port.py ADDRESS FUNCTION [--cases N]
       verify_port.py --all [--cases N]   (every port in PORTS, tools/dispatch_boundaries.py)

The routine at ADDRESS is lifted again into build/ports: its metadata and lifted text give the
cases the same hints as its lifted copy had. FUNCTION (a port with the signature of a lifted
routine) is then compared in the batch verifier's modes, wide registers and small ones. It must
pass every mode its lifted copy passes (a mode the lifted copy fails or times out in, such as wide
registers for a loop counted by a register, is not usable), and at least one.

The returned edx is compared as well, and when a lifted caller branches on the flags the routine
leaves (vertrix_lift_fl) right after the call, so are the flags: such a port sets them.
"""
import argparse
import json
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
# Ports whose original runs long loops in Unicorn: checked with fewer cases (still more than the
# 64 per mode the batch used for the lifted copies).
# cdecl routines (plain ret) read stack arguments the lifter cannot count: the oracle draws this
# many, so stores through pointer arguments are compared.
STACK_ARGUMENTS = {0x4db250: 6}
SLOW = {'0x48a930': 64, '0x492980': 256, '0x4ec307': 256, '0x492460': 256, '0x4922f0': 256,
        '0x4db6a4': 256, '0x405720': 512, '0x4af560': 256, '0x4b1fa0': 256, '0x4db250': 512, '0x4928f0': 256, '0x4408e0': 1024, '0x48a3c0': 1024, '0x4b3390': 1024, '0x4ae3e0': 1024, '0x408800': 64, '0x409f00': 256, '0x407280': 128, '0x4095d0': 128, '0x40a190': 512, '0x4d7d70': 128, '0x4ab200': 256, '0x40cda0': 256, '0x4d9060': 512, '0x4daae8': 512, '0x482f80': 512, '0x477f10': 512, '0x485550': 512, '0x4774e0': 512, '0x4d7c40': 512, '0x483ed0': 512, '0x47c520': 512, '0x476d70': 512,
        # Copies whose random pointers overrun a pool page past these counts, for the lifted copy
        # as well.
        '0x4ab310': 64, '0x4ab2a0': 128, '0x492dc0': 64, '0x40c990': 48}
# The native sources the batch harness links with every routine (verify_one.py).
HARNESS = {'call_glue', 'actor_storage', 'block_factory', 'actor_fields', 'board_cells'}
sys.path.insert(0, str(ROOT / 'tools'))

import lift  # noqa: E402


def flag_readers(address):
    """The lifted routines that read the flags right after calling `address`."""
    call = re.compile(r'lift_call\(&env, 0x%xu,' % address)
    readers = []
    for path in sorted((ROOT / 'source').glob('lifted_*.c')):
        lines = path.read_text().splitlines()
        routine = None
        for index, line in enumerate(lines):
            if line.startswith('uint32_t lifted_'):
                routine = line.split('(')[0].split()[-1]
            if not call.search(line):
                continue
            # inc and dec set every flag but the carry, which stays the callee's.
            live = r'\bfl\.'
            for after in lines[index + 1:index + 60]:
                if 'fl = vertrix_lift_fl;' in after or 'edx = vertrix_lift_edx;' in after:
                    continue
                if re.search(live, after):
                    readers.append(routine)
                    break
                if (after.strip().endswith(':') or 'return ' in after or 'goto ' in after or
                        'lift_call' in after):
                    break
                if re.search(r'&fl\b', after):
                    if not re.search(r'lift_(inc|dec)\(', after):
                        break
                    live = r'\bfl\.cf\b'
    return readers


def run_mode(directory, name, cases, mode, flags, timeout, natives=()):
    environment = dict(os.environ, VERTRIX_VERIFY_EDX='1', VERTRIX_VERIFY_FLAGS='1' if flags else '0',
                       VERTRIX_VERIFY_SOURCES=' '.join(natives))
    try:
        done = subprocess.run([sys.executable, str(ROOT / 'tools' / 'verify_one.py'),
                               str(directory), name, str(cases), mode], capture_output=True,
                              text=True, cwd=ROOT / 'tools', env=environment, timeout=timeout)
    except subprocess.TimeoutExpired:
        return False, 'timeout'
    return done.returncode == 0, (done.stderr.strip().splitlines() or [''])[-1][:300]


def verify(address, function, cases, timeout=600):
    """Print the outcome for one port; returns whether it is verified."""
    sources = [p for p in sorted((ROOT / 'source').glob('port_*.c'))
               if re.search(r'^uint32_t %s\(' % function, p.read_text(), re.M)]
    name = 'f%x' % address
    if len(sources) != 1:
        print('%s: %s is defined in %d port sources' % (name, function, len(sources)))
        return False
    built = subprocess.run(['cc', '-std=c11', '-fsyntax-only', '-Wall', '-Wextra', '-Werror', '-I',
                            str(ROOT / 'source'), str(sources[0])], capture_output=True, text=True)
    if built.returncode != 0:
        print('%s: %s does not compile:\n%s' % (name, sources[0].name, built.stderr.strip()))
        return False
    scratch = ROOT / 'build' / 'ports' / name
    lifted = scratch / 'lifted'
    lifted.mkdir(parents=True, exist_ok=True)
    text, header, meta = lift.render(address, name,
                                     STACK_ARGUMENTS.get(address, lift.return_arguments(address)))
    meta['address'] = address
    for directory in (scratch, lifted):
        (directory / ('lifted_%s.h' % name)).write_text(header)
        (directory / (name + '.json')).write_text(json.dumps(meta))
    (scratch / (name + '.lifted.c')).write_text(text)
    (lifted / (name + '.c')).write_text(text)
    # Recovered native code a port calls (an included header with its own source), linked in
    # with it; the harness links the call glue and the object storage itself.
    natives = [header + '.c' for header in
               re.findall(r'^#include "(\w+)\.h"', sources[0].read_text(), re.M)
               if (ROOT / 'source' / (header + '.c')).exists() and header not in HARNESS
               and not header.startswith(('port', 'lift'))]
    # The oracle hands the port the lifted copy's stack below esp (LiftEntry.garbage).
    (scratch / (name + '.c')).write_text(
        '#include "%s"\n#include "lifted_%s.h"\n\nuint32_t lifted_%s(PORT_SIGNATURE);\n'
        'uint32_t lifted_%s(PORT_SIGNATURE)\n{\n    vertrix_port_garbage_size = LIFTED_%s_STACK;\n'
        '    return %s(calls, services, globals, entry);\n}\n'
        % (sources[0], name, name, name, name.upper(), function))
    # Callers that branch on the flags the routine leaves: the flags are compared too.
    readers = sorted(set(flag_readers(address)))
    failed = False
    passed = 0
    modes = {}
    for mode in ('wide', 'small'):
        port_ok, port_detail = run_mode(scratch, name, cases, mode, bool(readers), timeout,
                                        natives)
        if port_ok:
            print('%s %s: port passes %d cases' % (name, mode, cases))
            modes[mode] = 'passed'
            passed += 1
            continue
        lifted_ok, lifted_detail = run_mode(lifted, name, cases, mode, bool(readers), timeout)
        if lifted_ok:
            print('%s %s: PORT FAILS: %s' % (name, mode, port_detail))
            modes[mode] = 'failed'
            failed = True
        else:
            modes[mode] = 'not usable (the lifted copy fails it too)'
            print('%s %s: not usable, the lifted copy fails it too (%s)' % (name, mode,
                                                                           lifted_detail))
    if passed == 0:
        print('%s: no mode passed' % name)
        failed = True
    if readers:
        print('%s: flags compared for the callers that read them: %s'
              % (name, ', '.join(readers[:4]) + (' and %d more' % (len(readers) - 4)
                                                 if len(readers) > 4 else '')))
    print('%s %s: %s' % (name, function, 'FAILED' if failed else 'verified'))
    (scratch / 'result.json').write_text(json.dumps(
        {'address': '0x%x' % address, 'port': function, 'cases': cases, 'modes': modes,
         'flags_compared': bool(readers), 'verified': not failed}, indent=1) + '\n')
    return not failed


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('address', nargs='?', type=lambda text: int(text, 16))
    parser.add_argument('function', nargs='?')
    parser.add_argument('--all', action='store_true')
    parser.add_argument('--cases', type=int, default=4096)
    parser.add_argument('--jobs', type=int, default=8)
    parser.add_argument('--timeout', type=int, default=600, help='seconds per mode and copy')
    args = parser.parse_args()
    if args.all:
        from dispatch_boundaries import PORTS
        slow = {int(a, 16): c for a, c in SLOW.items()}
        with ThreadPoolExecutor(args.jobs) as pool:
            results = list(pool.map(
                lambda item: verify(item[0], item[1], slow.get(item[0], args.cases), args.timeout),
                sorted(PORTS.items())))
        print('%d of %d ports verified' % (sum(results), len(results)))
        record = [json.loads((ROOT / 'build' / 'ports' / ('f%x' % a) / 'result.json').read_text())
                  for a in sorted(PORTS)]
        (ROOT / 'docs' / 'port-verification.json').write_text(json.dumps(
            {'scope': 'Each clean port against the original in Unicorn (tools/verify_port.py): '
                      'calls with registers and stack arguments, eax, edx, stored globals and '
                      'pool objects, and the flags where callers read them. The batch verified '
                      'the lifted copies with 64 cases per mode.',
             'ports': record}, indent=1) + '\n')
        sys.exit(0 if all(results) else 1)
    sys.exit(0 if verify(args.address, args.function, args.cases, args.timeout) else 1)


if __name__ == '__main__':
    main()

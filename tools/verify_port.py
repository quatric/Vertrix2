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
        '0x4db6a4': 256, '0x405720': 512, '0x4af560': 256, '0x4b1fa0': 256, '0x4db250': 512, '0x4928f0': 256, '0x4408e0': 1024, '0x48a3c0': 1024, '0x4b3390': 1024, '0x4ae3e0': 1024, '0x408800': 64, '0x409f00': 256, '0x407280': 128, '0x4095d0': 128, '0x40a190': 512, '0x4d7d70': 128, '0x4ab200': 256, '0x40cda0': 256, '0x4d9060': 512, '0x4daae8': 512, '0x482f80': 512, '0x477f10': 512, '0x485550': 512, '0x4774e0': 512, '0x4d7c40': 512, '0x483ed0': 512, '0x47c520': 512, '0x476d70': 512, '0x482d00': 256, '0x4d92f0': 512, '0x4b2290': 512, '0x43f110': 64, '0x4ca600': 256, '0x41a4e0': 256, '0x4e23e0': 256, '0x4dbac0': 256, '0x4d84f0': 256, '0x4cea15': 256, '0x4ce9c0': 256, '0x487280': 256, '0x4ec910': 256, '0x4ec8d0': 256, '0x4de5c0': 256, '0x4de970': 256, '0x4ccdd0': 256, '0x4cbf10': 256, '0x47f070': 256, '0x41a9a0': 256, '0x4cda10': 256, '0x488b90': 256, '0x4e57ac': 256, '0x48a4a0': 256, '0x4816f0': 256, '0x487660': 256, '0x48a560': 256, '0x48a050': 256, '0x48b240': 256, '0x482aa0': 256, '0x4873d0': 256, '0x4875a0': 256, '0x473f10': 256, '0x484700': 256, '0x45e7b0': 256, '0x45e850': 256, '0x45e9e0': 256, '0x482e80': 256, '0x482f00': 256, '0x4b8fbc': 256, '0x4b7dd0': 256, '0x4b5dc0': 256, '0x483ce0': 256, '0x4b6350': 256, '0x4b3210': 256, '0x4b5420': 256, '0x4b6460': 256, '0x489fa0': 256, '0x489640': 256, '0x4848f0': 256, '0x441450': 256, '0x4b78e0': 256, '0x40b620': 256, '0x40b6a0': 256, '0x41a440': 256, '0x4844b0': 256, '0x4e7200': 256, '0x4e6630': 256, '0x4ca970': 256, '0x476280': 256, '0x4b7c00': 256, '0x475be0': 256, '0x475b20': 256, '0x4761d0': 256, '0x475ec0': 256, '0x4b8187': 256, '0x460a40': 256, '0x4e5794': 256, '0x4db8b0': 256, '0x4dd190': 256, '0x4de630': 256, '0x478860': 256, '0x494e10': 256, '0x49ced0': 256, '0x495b20': 256, '0x49dbe0': 256, '0x496cd0': 256, '0x49ed90': 256, '0x494f30': 256, '0x49cff0': 256, '0x4952c0': 256, '0x49d380': 256, '0x495650': 256, '0x49d710': 256, '0x496350': 256, '0x49e410': 256, '0x493f40': 256, '0x49c000': 256, '0x4941d0': 256, '0x49c290': 256, '0x494310': 256, '0x49c3d0': 256, '0x494940': 256, '0x49ca00': 256, '0x494a80': 256, '0x49cb40': 256, '0x495f40': 256, '0x49e000': 256, '0x497da0': 256, '0x49fe60': 256, '0x499460': 256, '0x4a1520': 256, '0x494080': 256, '0x49c140': 256, '0x495060': 256, '0x49d120': 256, '0x4953f0': 256, '0x49d4b0': 256, '0x495780': 256, '0x49d840': 256, '0x493420': 256, '0x49b4e0': 256, '0x4959e0': 256, '0x49daa0': 256, '0x493720': 256, '0x49b7e0': 256, '0x498570': 256, '0x4a0630': 256, '0x494840': 256, '0x49c900': 256, '0x498470': 256, '0x4a0530': 256, '0x493610': 256, '0x49b6d0': 256, '0x495c40': 256, '0x49dd00': 256, '0x498660': 256, '0x4a0720': 256, '0x499350': 256, '0x4a1410': 256, '0x4974c0': 256, '0x4977c0': 256, '0x49f580': 256, '0x49f880': 256, '0x4933e0': 256, '0x49b4a0': 256, '0x4935c0': 256, '0x49b680': 256, '0x493e70': 256, '0x49bf30': 256, '0x495ac0': 256, '0x49db80': 256, '0x493970': 256, '0x49ba30': 256, '0x493ba0': 256, '0x49bc60': 256, '0x493ec0': 256, '0x49bf80': 256, '0x494bc0': 256, '0x49cc80': 256, '0x495d50': 256, '0x49de10': 256, '0x493500': 256, '0x49b5c0': 256, '0x493c30': 256, '0x49bcf0': 256, '0x493cf0': 256, '0x49bdb0': 256, '0x493db0': 256, '0x49be70': 256, '0x44c960': 256, '0x44cbf0': 256, '0x44cc60': 256, '0x44d2c0': 256, '0x44d410': 256, '0x44d760': 256, '0x4b7080': 256, '0x4b7120': 256, '0x4b71c0': 256, '0x4b7260': 256, '0x4b7300': 256, '0x44a040': 256, '0x44a170': 256, '0x44a2a0': 256, '0x455670': 256, '0x4558e0': 256, '0x455a00': 256, '0x456300': 256, '0x4564e0': 256, '0x4566d0': 256, '0x454e90': 256, '0x455b20': 256, '0x455ca0': 256, '0x45b9c0': 256, '0x4d83f0': 256, '0x4d8b80': 256, '0x4defd0': 256, '0x4ee980': 256, '0x458e30': 256, '0x458fd0': 256, '0x45a1c0': 256, '0x456390': 256, '0x456570': 256, '0x456760': 256, '0x492770': 256, '0x49a480': 256, '0x4a2540': 256, '0x4aa240': 256, '0x49a120': 256, '0x4a21e0': 256, '0x49a270': 256, '0x4a2330': 256, '0x499fb0': 256, '0x4a2070': 256, '0x49a420': 256, '0x4a24e0': 256, '0x49a690': 256, '0x4a2750': 256, '0x452a30': 256, '0x452b00': 256, '0x452bb0': 256, '0x452c60': 256, '0x45a3e0': 256, '0x472570': 256, '0x44c530': 256, '0x44e600': 256, '0x45c0e0': 256, '0x44d660': 256, '0x45b860': 256, '0x44f1e0': 256, '0x45e720': 256, '0x4182f0': 256, '0x418550': 256, '0x418570': 256, '0x472020': 256, '0x472090': 256, '0x4721e0': 256, '0x472250': 256, '0x4722c0': 256, '0x43ba70': 256, '0x475df0': 256, '0x453570': 256, '0x454970': 256, '0x454bd0': 256, '0x454e30': 256, '0x454fc0': 256, '0x44c9d0': 256, '0x44ca40': 256, '0x45b7f0': 256, '0x45bd60': 256, '0x45bf80': 256, '0x44c3e0': 256, '0x44c450': 256, '0x44d3a0': 256, '0x44d5f0': 256, '0x44c880': 256, '0x44c8e0': 256, '0x44ebe0': 256, '0x4582d0': 256, '0x45b790': 256, '0x45bd00': 256, '0x45bf20': 256, '0x478570': 256, '0x4785c0': 256, '0x478610': 256, '0x478660': 256, '0x4786b0': 256, '0x478700': 256, '0x478750': 256, '0x4787a0': 256, '0x4535d0': 256, '0x4537b0': 256, '0x453800': 256, '0x453850': 256, '0x4538a0': 256, '0x453990': 256, '0x4539e0': 256, '0x453a80': 256, '0x44f120': 256, '0x44f180': 256, '0x44f4a0': 256, '0x44f500': 256, '0x44f5d0': 256, '0x44f630': 256, '0x41c0f0': 256, '0x41c160': 256, '0x41c1d0': 256, '0x41c240': 256, '0x41c2b0': 256, '0x41c6d0': 256, '0x41c740': 256, '0x44c4c0': 256, '0x44d1e0': 256, '0x44d250': 256, '0x44d480': 256, '0x44d4f0': 256, '0x44d7d0': 256, '0x44d840': 256, '0x44dc80': 256, '0x44e670': 256, '0x44f040': 256, '0x44f0b0': 256, '0x44f700': 256, '0x44f770': 256, '0x44f920': 256, '0x45bdd0': 256, '0x45be40': 256, '0x445f00': 256, '0x445fc0': 256, '0x446080': 256, '0x446140': 256, '0x446200': 256, '0x4462c0': 256, '0x446380': 256, '0x449500': 256, '0x449660': 256, '0x4497c0': 256, '0x449aa0': 256, '0x449c00': 256, '0x449d60': 256, '0x4ad5e0': 256, '0x4ad630': 256, '0x49a180': 256, '0x4a2240': 256, '0x4a9f40': 256, '0x49a600': 256, '0x4a26c0': 256, '0x4aa3c0': 256, '0x49a590': 256, '0x4a2650': 256, '0x4aa350': 256, '0x4ad110': 256, '0x415db0': 256, '0x4829c0': 256, '0x41a780': 256, '0x410f20': 256, '0x418ce0': 256, '0x4185f0': 256, '0x4191b0': 256, '0x477c90': 256, '0x478dd0': 256, '0x441d60': 256, '0x429530': 256, '0x482550': 256, '0x4ad210': 256, '0x4ad750': 256, '0x4ad790': 256, '0x4b6700': 256, '0x40e670': 256, '0x44c860': 256, '0x44c940': 256, '0x450710': 256, '0x450730': 256, '0x45b0f0': 256, '0x459860': 256, '0x45b150': 256, '0x4ac840': 256, '0x458450': 256, '0x45b0b0': 256, '0x45b130': 256, '0x45b410': 256, '0x4ad580': 256, '0x476010': 256, '0x4766f0': 256, '0x472470': 256, '0x474490': 256, '0x4cce30': 256, '0x4d8ab0': 256, '0x4df0d0': 256, '0x4e7540': 256, '0x425d30': 256, '0x40b0d0': 256, '0x472440': 256, '0x4ea2a8': 256, '0x460ad0': 256, '0x476440': 256, '0x4cdad0': 256, '0x486ed0': 256, '0x425e40': 256, '0x4296a0': 256, '0x42b600': 256, '0x42bb20': 256, '0x43a0b0': 256, '0x43d400': 256, '0x4b3500': 256, '0x4b24e0': 256, '0x429350': 256, '0x487930': 256, '0x48d530': 256, '0x425d50': 256, '0x475700': 256, '0x482320': 256, '0x487890': 256, '0x471c90': 256, '0x471cd0': 256, '0x471d10': 256, '0x471d50': 256, '0x471d90': 256, '0x471dd0': 256, '0x471ba0': 256, '0x472460': 256, '0x415fb0': 256, '0x415fc0': 256, '0x415fd0': 256, '0x415fe0': 256, '0x417880': 256, '0x417890': 256, '0x4178a0': 256, '0x4178b0': 256, '0x4178c0': 256, '0x48b550': 256, '0x487080': 256, '0x40b040': 256, '0x418870': 256, '0x429b10': 256, '0x42b2f0': 256, '0x43a2a0': 256, '0x43a2c0': 256, '0x4523b0': 256, '0x4597a0': 256, '0x45afe0': 256, '0x45c730': 256, '0x4713c0': 256, '0x471ee0': 256, '0x477930': 256, '0x47f8f0': 256, '0x4879f0': 256, '0x48d600': 256, '0x48dcd0': 256, '0x4b3f10': 256, '0x4b3f20': 256, '0x4b6f70': 256, '0x4b9ce0': 256, '0x4ba210': 256, '0x4bb260': 256, '0x4c5c20': 256, '0x4c6a80': 256, '0x4c93c0': 256, '0x4ce080': 256, '0x4e3697': 256, '0x4e55d0': 256, '0x4e9d00': 256, '0x4ec8c0': 256,
        # Copies whose random pointers overrun a pool page past these counts, for the lifted copy
        # as well.
        '0x4ab310': 64, '0x4ab2a0': 128, '0x499350': 48, '0x492dc0': 64, '0x40c990': 48, '0x4ccf3b': 64}
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

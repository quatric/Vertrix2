"""Compare the complete original companion spawner 0x471100 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
CONFIG_SIZE = 0x800
GATE_OFFSET = 0x5cc


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=512)
    args = parser.parse_args()
    n = build(args.build_dir, 'ui-companion-spawn',
              ['ui_companion_actor.c', 'call_glue.c', 'actor_storage.c', 'actor_fields.c',
               'ui_actor_storage.c', 'actor_style_storage.c', 'block_factory.c', 'board_cells.c',
               'ui_display_layout.c'])
    n.vertrix_ui_companion_spawn.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.c_uint16,
                                             c.c_uint16, U, U, U, c.c_void_p, c.c_size_t]
    n.vertrix_ui_companion_spawn.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x471100)
    pool = Pool(cpu, 4, SIZE)
    allocs, appends, nat_allocs, nat_appends = [], [], [], []
    totals = {}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            assert eax == 0x15c, hex(eax)
            handle = rng.choice(pool.handles)
            allocs.append((eax, edx, ebx, ecx, handle))
            return handle
        if address == 0x4b5e70:
            appends.append((eax, edx, ebx, ecx))
            return 0
        raise AssertionError(hex(address))

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4b5e70)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0x4ca000:
            assert (s.eax, s.edx, s.ebx, s.ecx) == allocs[0][:4], (s.eax, s.edx, s.ebx, s.ecx)
            handle = allocs.pop(0)[4]
            nat_allocs.append((s.eax, s.edx, s.ebx, s.ecx, handle))
            return handle
        if s.target == 0x4b5e70:
            nat_appends.append((s.eax, s.edx, s.ebx, s.ecx))
            return 0
        raise AssertionError(hex(s.target))

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    config_base = 0x900000
    cpu.mem_map(config_base, 0x1000)
    for case in range(args.cases):
        pool.fill(rng)
        config = bytearray(rng.randbytes(CONFIG_SIZE))
        index = rng.randrange(64)
        gate = rng.choice([0, 1, 1, rng.getrandbits(32)])
        struct.pack_into('<I', config, GATE_OFFSET + index * 4, gate)
        cpu.mem_write(config_base, bytes(config))
        cconfig = c.create_string_buffer(bytes(config), CONFIG_SIZE)
        x, y = rng.randrange(0x10000), rng.randrange(0x10000)
        frame, sentinel = rng.getrandbits(32), rng.choice([index, rng.getrandbits(32)])
        for log in (allocs, appends, nat_allocs, nat_appends):
            log.clear()
        expect = original.call(0x471100, eax=x, edx=y, ebx=frame, ecx=index,
                               args=(sentinel, config_base)) & 0xffffffff
        orig_allocs, orig_appends = list(allocs), list(appends)
        got = n.vertrix_ui_companion_spawn(c.byref(calls), c.byref(services), x & 0xffff,
                                           y & 0xffff, frame, index, sentinel, cconfig,
                                           CONFIG_SIZE)
        assert got == expect, (case, hex(got), hex(expect))
        assert nat_allocs == orig_allocs, (case, nat_allocs, orig_allocs)
        assert nat_appends == orig_appends, (case, nat_appends, orig_appends)
        assert pool.same(), (case, pool.diff())
        totals['0x471100'] = totals.get('0x471100', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x471100 executions with the allocator 0x4ca000 and '
                       'the list append 0x4b5e70 stubbed and logged (the base constructor, '
                       'the placer, the style applier and the gate read execute for real on '
                       'both sides); the returned actor, the allocator/append call logs and '
                       'every pool object compare.'}
    (args.build_dir / 'ui-companion-spawn-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

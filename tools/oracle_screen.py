"""Shared pieces of the screen builder oracles: call sites, services, supplied static data reads."""
import ctypes as c
import json
import struct

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)
GlobalRead = c.CFUNCTYPE(U, U, c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Globals(c.Structure):
    _fields_ = [('read', GlobalRead), ('context', c.c_void_p)]


class Services(c.Structure):
    from oracle_kit import Resolve
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def site_log(s, count):
    return (s.target, s.eax, s.edx, s.ebx, s.ecx) + (
        s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2, s.rest3, s.rest4,
        s.rest5, s.rest6, s.rest7, s.rest8, s.rest9, s.rest10, s.rest11, s.rest12, s.rest13)[:count]


def global_reader(cpu):
    @GlobalRead
    def read(address, context):
        return struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0]
    return read


def write_report(build_dir, name, report):
    (build_dir / (name + '-verification.json')).write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


def run_screen(name, address, sources, function, argtypes, restype, callees, generate, scope,
               *, wrappers=(), allocator=0x4ca000, globals_ranges=(), patch=None, compare=True,
               result_mask=0xffffffff, description='', table_targets=(), lookups=(), pool_size=0x200, effects=None, fixed_returns=None, handle_returns=(), choices=None,
               setup=None, extras=None, native_extras_arg=None, post=None,
               leading=('calls', 'services', 'globals')):
    """Run `function` against the original routine at `address`.

    generate(rng, pool, cpu) returns (original keyword arguments, original stack arguments, native
    arguments). Callees are stubbed and logged; `wrappers` return their eax (class constructors).
    """
    import argparse
    import random
    from pathlib import Path

    from original import Original
    from oracle_kit import Pool, Stubs, build

    parser = argparse.ArgumentParser(description=description or name)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    sources = list(sources) + ['call_glue.c', 'actor_storage.c', 'block_factory.c',
                               'actor_fields.c', 'board_cells.c']
    native = build(args.build_dir, name, sources)
    fn = getattr(native, function)
    kinds = {'calls': c.POINTER(Calls), 'services': c.POINTER(Services),
             'globals': c.POINTER(Globals)}
    fn.argtypes = [kinds[name_] for name_ in leading] + argtypes
    fn.restype = restype
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(address)
    pool = Pool(cpu, 4, pool_size)
    returns, native_log, replay, replay_out = [], [], [], []
    native_extras = native_extras_arg or {}

    def handler(target, eax, edx, ebx, ecx, stack):
        if target in effects:
            outs.append(effects[target](cpu, rng, eax, edx, ebx, ecx, stack))
        if target in fixed_returns:
            returns.append(fixed_returns[target])
        elif choices and target in choices:
            returns.append(rng.choice(choices[target]))
        elif target in handle_returns:
            returns.append(rng.choice(pool.handles))
        elif target in lookups:
            returns.append(rng.choice(pool.handles + [0] * 2))
        elif target == allocator:
            returns.append(rng.choice(pool.handles))
        elif target in wrappers:
            returns.append(eax)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    if setup:
        setup(cpu)
    effects = effects or {}
    fixed_returns = fixed_returns or {}
    outs = []
    callees = dict(callees)
    for table in table_targets:
        callees[struct.unpack('<I', bytes(cpu.mem_read(table, 4)))[0]] = 0
    stubs = Stubs(cpu, handler)
    for target, count in callees.items():
        stubs.add(target, count)
    stubs.extras.update(extras or {})

    @Call
    def call(site, context):
        s = site.contents
        native_log.append(site_log(s, callees[s.target]) + tuple(
            native_extras[s.target](s) if s.target in native_extras else ()))
        if s.target in effects:
            out = replay_out.pop(0)
            if isinstance(out, tuple):
                s.out_value, s.out_ebx, s.out_ecx = out
            else:
                s.out_value = out
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    reader = global_reader(cpu)
    globals_ = Globals(reader, None)
    for case in range(args.cases):
        if patch:
            pool.fill(rng, lambda handle, data: patch(rng, handle, data))
        else:
            pool.fill(rng)
        for start, length in globals_ranges:
            cpu.mem_write(start, rng.randbytes(length))
        kwargs, stack_args, native_args = generate(rng, pool, cpu)
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        result = original.call(address, args=tuple(stack_args), **kwargs) & 0xffffffff
        replay[:] = list(returns)
        replay_out[:] = list(outs)
        objects = {'calls': calls, 'services': services, 'globals': globals_}
        got = fn(*[c.byref(objects[name_]) for name_ in leading], *native_args)
        if compare:
            assert got == result & result_mask, (case, hex(got), hex(result))
        else:
            assert got == 1, (case, got)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        if post:
            post(cpu, native_args)
        assert not replay and not replay_out and pool.same(), (case, pool.diff())
    write_report(args.build_dir, name, {
        'status': 'passed', 'complete_original_executions': {hex(address): args.cases},
        'scope': scope})

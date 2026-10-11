"""Shared pieces of the screen builder oracles: call sites, services, supplied static data reads."""
from unicorn import (UC_HOOK_MEM_READ_UNMAPPED, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_WRITE_UNMAPPED,
                     UcError)
from unicorn.x86_const import (UC_X86_REG_CS, UC_X86_REG_DS, UC_X86_REG_EDX, UC_X86_REG_EFLAGS,
                               UC_X86_REG_EIP, UC_X86_REG_ES, UC_X86_REG_FS, UC_X86_REG_GDTR,
                               UC_X86_REG_SS)
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


class LiftFlags(c.Structure):
    _fields_ = [(name, U) for name in ('zf', 'sf', 'cf', 'of', 'pf', 'df')]


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


# The bytes a stub effect is about to overwrite, recorded like the write hook records the original's
# own stores (the hook does not see writes made from Python).
_host_before = [None]


def host_write(cpu, address, data):
    """Write from a stub effect into the original's memory, keeping the bytes it replaces for the
    native code's global reads."""
    before = _host_before[0]
    if before is not None:
        old = bytes(cpu.mem_read(address, len(data)))
        for i in range(len(data)):
            before.setdefault(address + i, old[i])
    cpu.mem_write(address, data)


def first_difference(native, original):
    """The index of the first differing call with both entries, both lengths, and the calls
    that led there."""
    index = next((i for i, (a, b) in enumerate(zip(native, original)) if a != b),
                 min(len(native), len(original)))
    return (index, native[index] if index < len(native) else None,
            original[index] if index < len(original) else None, len(native), len(original),
            original[max(0, index - 3):index])


def global_reader(cpu, before=None, shadow=None):
    """Read a global as the native code should see it. The original has already run, so with
    `before` (the bytes it overwrote, as they were before it ran) and `shadow` (the native code's
    own stores so far) a byte comes from the native stores, else from before the original ran, else
    from the oracle's memory; without them the oracle's memory is read as is."""
    @GlobalRead
    def read(address, context):
        try:
            raw = bytearray(cpu.mem_read(address, 4))
        except UcError:
            # The dword wraps past 0xffffffff or ends in an unmapped page: read its bytes alone.
            raw = bytearray(4)
            for i in range(4):
                try:
                    raw[i] = cpu.mem_read((address + i) & 0xffffffff, 1)[0]
                except UcError:
                    pass
        if before is not None:
            for i in range(4):
                byte_address = (address + i) & 0xffffffff
                if byte_address in shadow:
                    raw[i] = shadow[byte_address]
                elif byte_address in before:
                    raw[i] = before[byte_address]
        return struct.unpack('<I', bytes(raw))[0]
    return read


# The original's thread block. fs:[0], the exception chain, lives here rather than at address 0, as
# on Windows: with an FS base of 0 the chain shared page zero with null pointer accesses.
GDT = 0x7ffde000
TEB = 0x7ffdf000


def descriptor(base, limit, access, flags):
    """An x86 segment descriptor."""
    return struct.pack('<Q', (limit & 0xffff) | ((base & 0xffffff) << 16) | (access << 40) |
                       (((limit >> 16) & 0xf) << 48) | (flags << 52) | ((base >> 24) << 56))


def separate_fs(cpu):
    """Point FS at TEB through a GDT. Loading a GDT makes Unicorn rebuild every segment from it, so
    the GDT also holds flat 32-bit code and data segments for CS, SS, DS and ES (without them the
    stack is 16-bit and pushes wrap at 64 KB)."""
    cpu.mem_map(GDT, 0x2000)
    cpu.mem_write(GDT + 8, descriptor(TEB, 0xfff, 0x93, 0x4) +
                  descriptor(0, 0xfffff, 0x93, 0xc) + descriptor(0, 0xfffff, 0x9b, 0xc))
    cpu.reg_write(UC_X86_REG_GDTR, (0, GDT, 0x1f, 0))
    cpu.reg_write(UC_X86_REG_CS, 0x18)
    for register in (UC_X86_REG_SS, UC_X86_REG_DS, UC_X86_REG_ES):
        cpu.reg_write(register, 0x10)
    cpu.reg_write(UC_X86_REG_FS, 8)


def automap(cpu):
    """Map a zero page for any access to unmapped memory so garbage pointers run on."""
    def fault(uc, access, address, size, value, user):
        page = address & ~0xfff
        if page == 0 and address < 0x1000:
            return False
        try:
            uc.mem_map(page, 0x1000)
            if address + size > page + 0x1000:
                uc.mem_map(page + 0x1000, 0x1000)
        except UcError:
            return False
        return True
    cpu.hook_add(UC_HOOK_MEM_READ_UNMAPPED | UC_HOOK_MEM_WRITE_UNMAPPED, fault)


def write_report(build_dir, name, report):
    (build_dir / (name + '-verification.json')).write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


def run_screen(name, address, sources, function, argtypes, restype, callees, generate, scope,
               *, wrappers=(), allocator=0x4ca000, globals_ranges=(), patch=None, compare=True,
               result_mask=0xffffffff, description='', table_targets=(), lookups=(), pool_size=0x200, effects=None, fixed_returns=None, handle_returns=(), choices=None,
               setup=None, automap_enabled=False, tolerate_faults=False, small_returns=False, extras=None, native_extras_arg=None, post=None, mixed_returns=(), flag_targets=(), internal_targets=(),
               leading=('calls', 'services', 'globals'), compare_edx=False,
               compare_flags=False):
    """Run `function` against the original routine at `address`.

    generate(rng, pool, cpu) returns (original keyword arguments, original stack arguments, native
    arguments). Callees are stubbed and logged; `wrappers` return their eax (class constructors).
    """
    import argparse
    import os
    import random
    from pathlib import Path

    from original import Original
    from oracle_kit import Pool, Stubs, build

    parser = argparse.ArgumentParser(description=description or name)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    # VERTRIX_VERIFY_SOURCES (space separated): more sources for the routine under test, such as
    # the recovered native code a clean port calls (tools/verify_port.py).
    sources = list(sources) + ['call_glue.c', 'actor_storage.c', 'block_factory.c',
                               'actor_fields.c', 'board_cells.c'] + \
        os.environ.get('VERTRIX_VERIFY_SOURCES', '').split()
    native = build(args.build_dir, name, sources)
    fn = getattr(native, function)
    kinds = {'calls': c.POINTER(Calls), 'services': c.POINTER(Services),
             'globals': c.POINTER(Globals)}
    fn.argtypes = [kinds[name_] for name_ in leading] + argtypes
    fn.restype = restype
    original = Original(args.executable)
    cpu = original.cpu
    separate_fs(cpu)
    rng = random.Random(address)
    pool = Pool(cpu, 4, pool_size)
    returns, native_log, replay, replay_out, native_stores = [], [], [], [], []
    flag_draws, flag_replay = [], []
    lift_fl = LiftFlags.in_dll(native, 'vertrix_lift_fl') if flag_targets else None
    native_extras = native_extras_arg or {}

    def handler(target, eax, edx, ebx, ecx, stack):
        if target in flag_targets:
            # A callee whose flags the caller branches on (a compare helper such as 0x4eb57c):
            # the stub leaves drawn flags, and the native call hands the same ones back in
            # vertrix_lift_fl, as a lifted callee does.
            flags = [rng.getrandbits(1) for _ in range(5)]
            eflags = cpu.reg_read(UC_X86_REG_EFLAGS) & ~0x8c5
            for bit, value in zip((6, 7, 0, 11, 2), flags):
                eflags |= value << bit
            cpu.reg_write(UC_X86_REG_EFLAGS, eflags)
            flag_draws.append(flags)
        if target in effects:
            outs.append(effects[target](cpu, rng, eax, edx, ebx, ecx, stack))
        if target in fixed_returns:
            returns.append(fixed_returns[target])
        elif choices and target in choices:
            returns.append(rng.choice(choices[target]))
        elif target in mixed_returns:
            returns.append(rng.choice(pool.handles + [0, 1, 2, rng.randrange(0, 40)] +
                                      ([rng.getrandbits(32)] if rng.random() < 0.1 else [])))
        elif target in handle_returns:
            returns.append(rng.choice(pool.handles))
        elif target in lookups:
            returns.append(rng.choice(pool.handles + [0] * 2))
        elif target == allocator:
            returns.append(rng.choice(pool.handles))
        elif target in wrappers:
            returns.append(eax)
        elif small_returns:
            returns.append(rng.choice([0, 0, 1, 2, 3, rng.randrange(0, 64)]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    if automap_enabled:
        automap(cpu)
    if setup:
        setup(cpu)
    effects = effects or {}
    fixed_returns = fixed_returns or {}
    outs = []
    callees = dict(callees)
    cdecl_targets = {t for t, n in callees.items() if isinstance(n, tuple)}
    callees = {t: (n[0] if isinstance(n, tuple) else n) for t, n in callees.items()}
    for table in table_targets:
        callees[struct.unpack('<I', bytes(cpu.mem_read(table, 4)))[0]] = 0
    stubs = Stubs(cpu, handler)
    for target, count in callees.items():
        stubs.add(target, count, cdecl=target in cdecl_targets)
    stubs.extras.update(extras or {})
    stubs.internal.update(t for t in internal_targets if t in callees)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0xf0000000:
            native_stores.append((s.eax, s.edx, s.stack))
            for i in range(s.stack):
                native_shadow[s.eax + i] = (s.edx >> (8 * i)) & 0xff
            return 0
        if s.target in flag_targets:
            lift_fl.zf, lift_fl.sf, lift_fl.cf, lift_fl.of, lift_fl.pf = flag_replay.pop(0)
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
    # The original's overwritten bytes, recorded as it runs, and the native code's global stores:
    # the native code reads globals through them (store-to-load forwarding), not the memory the
    # original left behind.
    before, native_shadow = {}, {}

    def record_write(uc, access, address, size, value, user):
        for i in range(size):
            byte_address = (address + i) & 0xffffffff
            if byte_address not in before:
                try:
                    before[byte_address] = uc.mem_read(byte_address, 1)[0]
                except UcError:
                    pass

    cpu.hook_add(UC_HOOK_MEM_WRITE, record_write)
    _host_before[0] = before
    reader = global_reader(cpu, before, native_shadow)
    globals_ = Globals(reader, None)
    completed = skipped_cases = 0
    fault_reasons = {}
    # With tolerated faults, inputs on which the original itself faults do not count: keep drawing
    # inputs (at most 16 times the case budget) until the budget of complete executions is reached.
    # The pass condition below is unchanged.
    attempts = args.cases * 16 if tolerate_faults else args.cases
    for case in range(attempts):
        if completed >= args.cases:
            break
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
        native_stores.clear()
        native_shadow.clear()
        before.clear()
        flag_draws.clear()
        try:
            result = original.call(address, args=tuple(stack_args), **kwargs) & 0xffffffff
            result_edx = cpu.reg_read(UC_X86_REG_EDX)
            result_flags = cpu.reg_read(UC_X86_REG_EFLAGS)
        except (UcError, RuntimeError) as error:
            if not tolerate_faults:
                raise
            skipped_cases += 1  # the original itself faults or never returns on this input
            reason = '%s at %#x' % ('RuntimeError (%s)' % error if isinstance(error, RuntimeError)
                                    else error, cpu.reg_read(UC_X86_REG_EIP))
            fault_reasons[reason] = fault_reasons.get(reason, 0) + 1
            continue
        completed += 1
        replay[:] = list(returns)
        replay_out[:] = list(outs)
        flag_replay[:] = list(flag_draws)
        objects = {'calls': calls, 'services': services, 'globals': globals_}
        got = fn(*[c.byref(objects[name_]) for name_ in leading], *native_args)
        # The call log first: a diverging path explains a differing result.
        assert native_log == stubs.log, (case, first_difference(native_log, stubs.log))
        if compare:
            assert got == result & result_mask, (case, hex(got), hex(result))
        else:
            assert got == 1, (case, got)
        if compare_edx:
            # The edx the routine leaves (vertrix_lift_edx), which a caller may read as a result.
            got_edx = c.c_uint32.in_dll(native, 'vertrix_lift_edx').value
            assert got_edx == result_edx, (case, 'edx', hex(got_edx), hex(result_edx))
        if compare_flags:
            # The flags the routine leaves (vertrix_lift_fl: zf, sf, cf, of, pf), which callers
            # that branch right after the call read.
            fl = (c.c_uint32 * 6).in_dll(native, 'vertrix_lift_fl')
            want = tuple((result_flags >> bit) & 1 for bit in (6, 7, 0, 11, 2))
            assert tuple(int(fl[i] != 0) for i in range(5)) == want, \
                (case, 'flags zf sf cf of pf', tuple(fl[:5]), want)
        shadow = {}
        for store_address, value, width in native_stores:
            for i in range(width):
                # A store at the top of memory wraps to address 0 as in the original.
                shadow[(store_address + i) & 0xffffffff] = (value >> (8 * i)) & 0xff
        for byte_address, byte in shadow.items():
            held = bytes(cpu.mem_read(byte_address, 1))[0]
            assert held == byte, (case, hex(byte_address), held, byte)
        if post:
            post(cpu, native_args)
        assert not replay and not replay_out and not flag_replay and pool.same(), \
            (case, pool.diff())
    assert completed >= (max(4, args.cases // 4) if tolerate_faults else args.cases), \
        ('too few complete original executions', completed, skipped_cases,
         sorted(fault_reasons.items(), key=lambda item: -item[1])[:3])
    write_report(args.build_dir, name, {
        'status': 'passed', 'complete_original_executions': {hex(address): completed},
        'scope': scope})

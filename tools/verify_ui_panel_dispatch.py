"""Compare complete original UI panel broadcast routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_support as vs

PANELS = (0x54670c, 0x546710, 0x546714, 0x546718)
SINGLE = 0x546794
OBJECTS = vs.SCRATCH
Call = c.CFUNCTYPE(c.c_int32, c.c_void_p, c.c_uint32, c.c_uint32, c.c_uint32)


def main():
    args = vs.parse(__doc__, 2048)
    n = vs.build(args, 'ui-panel-dispatch', ['ui_panel_dispatch.c', 'call_glue.c', 'actor_storage.c'])
    U = c.c_uint32
    P = c.POINTER(U)
    n.vertrix_ui_panels_destroy.argtypes = [P, Call, c.c_void_p]
    n.vertrix_ui_panels_slot1.argtypes = [P, Call, c.c_void_p]
    n.vertrix_ui_panels_slot2.argtypes = [P, U, Call, c.c_void_p]
    n.vertrix_ui_panel_release.argtypes = [U, Call, c.c_void_p]
    n.vertrix_ui_panel_release.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    stubs = vs.VirtualStubs(cpu, register=True)
    rng = random.Random(0x45f9f0)
    native_events = []

    @Call
    def call(context, handle, slot, argument):
        native_events.append((handle, slot, argument))
        return 0

    pool = [OBJECTS + 0x200 * k for k in range(8)]
    for handle in pool:
        cpu.mem_write(handle + 0x158, struct.pack('<I', stubs.VTABLE))
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def run(name, address, panels, eax=0, edx=0, native_run=None, skip_arg=False):
        for slot_address, value in zip(PANELS, panels):
            cpu.mem_write(slot_address, struct.pack('<I', value))
        stubs.events.clear()
        native_events.clear()
        original.call(address, eax=eax, edx=edx)
        native_run((U * 4)(*panels))
        want = [(h, s, 0 if skip_arg else a) for h, s, a in stubs.events]
        got = [(h, s, 0 if skip_arg else a) for h, s, a in native_events]
        assert want == got, (name, want, got)
        count(name)

    for case in range(args.cases):
        mixed = [rng.choice([0, 0] + pool) for _ in range(4)]
        full = [rng.choice(pool) for _ in range(4)]
        run('0x45f9f0', 0x45f9f0, mixed, native_run=lambda a: n.vertrix_ui_panels_destroy(a, call, None))
        run('0x45fa70', 0x45fa70, full, skip_arg=True,
            native_run=lambda a: n.vertrix_ui_panels_slot1(a, call, None))
        argument = rng.getrandbits(32)
        run('0x45fab0', 0x45fab0, full, eax=argument,
            native_run=lambda a: n.vertrix_ui_panels_slot2(a, argument, call, None))
        single = rng.choice([0] + pool)
        cpu.mem_write(SINGLE, struct.pack('<I', single))
        stubs.events.clear()
        native_events.clear()
        original.call(0x472d50)
        assert n.vertrix_ui_panel_release(single, call, None) == struct.unpack(
            '<I', bytes(cpu.mem_read(SINGLE, 4)))[0] == 0
        assert [(h, s, a) for h, s, a in stubs.events] == native_events
        count('0x472d50')
    # Full ABI recovery: independent original/native live-memory dictionaries.
    from verify_call_glue import Site, Call as RuntimeCall, Calls
    from unicorn import UC_HOOK_CODE
    from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX
    Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
    Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
    context_token = 0x1234
    host, original_full, native_full, contexts = {}, [], [], []
    updates = []
    returns = []
    fail_address = None
    @Read
    def read(address, width, output, context):
        contexts.append(('read', context, width))
        if address == fail_address or address not in host: return 0
        output[0] = host[address]
        return 1
    @Write
    def write(address, width, value, context):
        contexts.append(('write', context, width))
        if address == fail_address: return 0
        host[address] = value
        return 1
    @RuntimeCall
    def runtime(site_pointer, context):
        site = site_pointer.contents
        native_full.append((site.target, site.eax, site.edx, site.ebx, site.ecx))
        contexts.append(('call', context, 4))
        if len(native_full) == 1:
            for address, value in updates: host[address] = value
        return returns[len(native_full)-1] if len(native_full) <= len(returns) else 0
    calls = Calls(runtime, context_token)
    for name in ('destroy', 'slot1', 'slot2'):
        getattr(n, 'vertrix_ui_panels_'+name+'_full').argtypes = [c.POINTER(Calls), Read, c.c_void_p, U, U, U, c.POINTER(U)]
    n.vertrix_ui_panel_release_full.argtypes = [c.POINTER(Calls), Read, Write, c.c_void_p, U, U, U, c.POINTER(U)]
    alternate_table = stubs.VTABLE + 0x300
    alternate_targets = [stubs.STUBS + 0x400 + 0x10*i for i in range(3)]
    def full_hook(cpu, address, size, context):
        original_full.append((address, *[cpu.reg_read(r) for r in
            (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]))
        if len(original_full) == 1:
            for at, value in updates: cpu.mem_write(at, struct.pack('<I', value))
        cpu.reg_write(UC_X86_REG_EAX, returns[len(original_full)-1])
    for target in [stubs.STUBS+0x10*i for i in range(3)] + alternate_targets:
        cpu.mem_write(target, b'\xc3')
        cpu.hook_add(UC_HOOK_CODE, full_hook, begin=target, end=target)
    full_totals = {}
    for address, name in ((0x45f9f0,'destroy'),(0x45fa70,'slot1'),(0x45fab0,'slot2'),(0x472d50,'single')):
        for case in range(args.cases + 3):
            eax, ebx, ecx = [rng.getrandbits(32) for _ in range(3)]
            selected = [rng.choice([0]+pool) if name in ('destroy','single') else rng.choice(pool) for _ in range(4)]
            if case >= args.cases: selected = pool[:4]
            host.clear()
            for at, value in zip(PANELS, selected): host[at] = value
            host[SINGLE] = selected[0]
            for handle in pool: host[handle+0x158] = stubs.VTABLE
            for i in range(3):
                host[stubs.VTABLE+4*i] = stubs.STUBS+0x10*i
                host[alternate_table+4*i] = alternate_targets[i]
            updates = []
            if case == args.cases: updates = [(PANELS[3], pool[4])]
            if case == args.cases+1: updates = [(pool[3]+0x158, alternate_table)]
            if case == args.cases+2: updates = [(SINGLE, pool[4]), (PANELS[3],pool[4]),(pool[4]+0x158,alternate_table)]
            returns = [rng.getrandbits(32) for _ in range(4)]
            for at, value in host.items(): cpu.mem_write(at, struct.pack('<I', value))
            original_full.clear(); native_full.clear(); contexts.clear()
            wanted = original.call(address, eax=eax, edx=rng.getrandbits(32), ebx=ebx, ecx=ecx)
            result = U(0xdeadbeef)
            if name == 'single':
                success = n.vertrix_ui_panel_release_full(c.byref(calls), read, write, context_token, eax, ebx, ecx, c.byref(result))
            else:
                success = getattr(n,'vertrix_ui_panels_'+name+'_full')(c.byref(calls),read,context_token,eax,ebx,ecx,c.byref(result))
            assert success and result.value == wanted, (name,case,'return',result.value,wanted)
            assert original_full == native_full, (name,case,original_full,native_full)
            assert all(context == context_token and width == 4 for _,context,width in contexts)
            assert all(value == struct.unpack('<I',cpu.mem_read(at,4))[0] for at,value in host.items())
            full_totals[hex(address)] = full_totals.get(hex(address),0)+1
    # A late failed read/write retains earlier calls and leaves result untouched.
    late_failures = 0
    for single in (False, True):
        updates = [(pool[0]+0x158, alternate_table)]; native_full.clear(); contexts.clear()
        host[PANELS[0]] = pool[0]; host[PANELS[1]] = pool[1]; host[SINGLE] = pool[0]
        fail_address = SINGLE if single else PANELS[1]
        result = U(0xdeadbeef)
        if single:
            # Permit the initial read, then reject the final write.
            fail_address = None
            @Write
            def rejected_write(address,width,value,context):
                contexts.append(('write',context,width)); return 0
            success = n.vertrix_ui_panel_release_full(c.byref(calls),read,rejected_write,context_token,1,2,3,c.byref(result))
        else:
            success = n.vertrix_ui_panels_slot1_full(c.byref(calls),read,context_token,1,2,3,c.byref(result))
        assert not success and len(native_full)==1 and result.value==0xdeadbeef
        assert host[pool[0]+0x158] == alternate_table
        assert all(context == context_token for _,context,_ in contexts)
        late_failures += 1
    fail_address = None
    assert all(total == args.cases for total in totals.values()) and len(totals) == 4
    assert all(total == args.cases + 3 for total in full_totals.values()) and len(full_totals) == 4
    vs.write_report(args, 'ui-panel-dispatch', {
        'status': 'passed', 'complete_original_executions': totals,
        'full_abi_original_executions': full_totals, 'native_late_failure_cases': late_failures,
        'scope': 'Complete 45f9f0, 45fa70, 45fab0 and 472d50 execute in the original with the '
                 'panel globals and per-object vtables; every virtual call (object, slot, edx '
                 'argument for slots 0 and 2) and the cleared global compare, including null '
                 'panels for the null-checked routines. Full APIs independently compare target/eax/edx/ebx/ecx, '
                 'callee return and live globals/vtables, including three mutation fixtures per routine. '
                 'Late native read/write failures retain earlier callbacks and preserve result.'})


if __name__ == '__main__':
    main()

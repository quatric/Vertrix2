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
    n = vs.build(args, 'ui-panel-dispatch', ['ui_panel_dispatch.c'])
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
    vs.write_report(args, 'ui-panel-dispatch', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 45f9f0, 45fa70, 45fab0 and 472d50 execute in the original with the '
                 'panel globals and per-object vtables; every virtual call (object, slot, edx '
                 'argument for slots 0 and 2) and the cleared global compare, including null '
                 'panels for the null-checked routines.'})


if __name__ == '__main__':
    main()

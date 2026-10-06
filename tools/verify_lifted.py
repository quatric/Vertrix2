"""Run each lifted routine (source/bonus_lifted.c) against the original and compare.

    python3 tools/verify_lifted.py Vertrix2.exe --build-dir build --routines 0x456d80 0x456de0 ...

Every case fills the oracle's object pool with random data (small values, zero, handles of other
objects, random dwords), gives the routine random entry registers and stack arguments, stubs
every callee of the routine (the original's own code is not run for them; their random results are
replayed to the native side) and runs the original routine to completion. The native routine then
runs on the same inputs. The ordered call log with registers and stack arguments, the virtual
calls, the result, every object and every global the routine wrote must agree. Cases on which the
original faults or does not finish (wild pointers) are skipped and counted.
"""
import argparse
import ctypes as c
import json
import random
import re
import struct
from pathlib import Path

from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE, UcError
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_EDI, UC_X86_REG_ESI

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x5000
OBJECTS = 8
VTABLE = 0x700400
SLOT_BASE = 0x700500
SLOTS = 16
STACK_SPAN = 0x800
Global = c.CFUNCTYPE(U, U, c.c_void_p)
GlobalWrite = c.CFUNCTYPE(None, U, U, c.c_void_p)
Virtual = c.CFUNCTYPE(c.c_int32, c.c_void_p, U, U, U)
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
# callees that store through pointers: address -> list of (register or stack index, width)
OUTPUTS = {0x43a5b0: [("edx", 1), ("ebx", 1), ("ecx", 1)],
           0x4764a0: [("ebx", 4), ("ecx", 4), ("stack0", 4)]}


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Factory(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('calls', c.POINTER(Calls)), ('resolve', Resolve), ('resolve_context', c.c_void_p),
                ('virtual_call', Virtual), ('virtual_context', c.c_void_p), ('draw', Draw),
                ('draw_context', c.c_void_p), ('factory', c.POINTER(Factory)),
                ('global_read', Global), ('global_context', c.c_void_p),
                ('global_write', GlobalWrite)]


class Context(c.Structure):
    _fields_ = [('services', c.POINTER(Services)), ('stack', c.c_void_p), ('stack_low', U),
                ('stack_size', U), ('failed', c.c_int), ('steps', U)]


class LocalStubs(Stubs):
    """Stubs that can be removed again, so one routine's callees do not shadow the next."""

    def __init__(self, cpu, handler):
        super().__init__(cpu, handler)
        self.handles = {}

    def add(self, address, stack_args=0, cdecl=False):
        self.arguments[address] = stack_args
        self.handles[address] = self.cpu.hook_add(UC_HOOK_CODE, self._hit, begin=address,
                                                  end=address)

    def remove_all(self):
        for handle in self.handles.values():
            self.cpu.hook_del(handle)
        self.handles.clear()
        self.arguments.clear()


def callees(source, address):
    """Call targets (with their stack argument counts) and virtual slots of one lifted routine."""
    match = re.search(r"vertrix_lift_%06x\(.*?\n}\n" % address, source, re.S)
    body = match.group(0)
    calls = {int(t, 16): int(n) for t, n in
             re.findall(r"vertrix_lift_call\(L, (0x[0-9a-f]+), eax, edx, ebx, ecx, esp, (\d+)\)", body)}
    slots = {int(s) for s in re.findall(r"vertrix_lift_virtual\(L, eax, (\d+)u\)", body)}
    return calls, slots


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--source', type=Path,
                        default=Path(__file__).resolve().parents[1] / 'source' / 'bonus_lifted.c')
    parser.add_argument('--routines', nargs='*', default=None)
    parser.add_argument('--cases', type=int, default=300)
    parser.add_argument('--seed', type=int, default=0x1f7)
    parser.add_argument('--report', type=Path, default=None)
    args = parser.parse_args()
    source = args.source.read_text()
    routines = ([int(a, 16) for a in args.routines] if args.routines else
                sorted(int(a, 16) for a in re.findall(r"uint32_t vertrix_lift_([0-9a-f]{6})\(", source)))
    n = build(args.build_dir, 'lifted',
              [str(args.source.name), 'lifted_runtime.c', 'call_glue.c', 'actor_storage.c',
               'bonus_effects.c', 'choice_grid.c', 'actor_fields.c', 'board_conversions.c',
               'block_factory.c', 'board_markers.c', 'board.c', 'board_cells.c', 'fixed_point.c',
               'board_actions.c', 'random.c'])
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x40000)
    cpu.mem_map(0x950000, 0x20000)
    try:
        cpu.mem_map(0, 0x1000)  # fs:[0], the exception chain, reads and writes page zero
    except UcError:
        pass
    pool = Pool(cpu, OBJECTS, SIZE)
    pool.handles = [0x900000 + SIZE * i for i in range(OBJECTS)]
    handles = pool.handles
    rng = random.Random(args.seed)
    state = {'writes': [], 'recording': False}

    def on_write(uc, access, address, size, value, user):
        if not state['recording']:
            return
        if pool.handles[0] <= address < pool.handles[-1] + SIZE:
            return
        if STACK - STACK_SPAN <= address < STACK + 0x40 or 0x700000 <= address < 0x710000:
            return
        old = bytes(uc.mem_read(address, size))
        state['writes'].append((address, size, old, value & ((1 << (8 * size)) - 1)))

    cpu.hook_add(UC_HOOK_MEM_WRITE, on_write)
    # vtable of every object: slot stubs that log themselves
    for slot in range(SLOTS):
        cpu.mem_write(VTABLE + 4 * slot, struct.pack('<I', SLOT_BASE + 0x10 * slot))
        cpu.mem_write(SLOT_BASE + 0x10 * slot, b'\xa1' + struct.pack('<I', 0x80f300) + b'\xc3')

    log, replay, stack_writes = [], [], []
    native_log = []
    stack_buffer = (c.c_uint8 * (STACK_SPAN + 0x40))()
    stack_low = STACK - STACK_SPAN
    outs_pending = []

    def scratch_pointer():
        return 0x950000 + rng.randrange(0, 0x10000)

    def value_mix():
        return rng.choice([0, 1, 2, 3, 0xffffffff, rng.getrandbits(32), rng.randrange(0, 64),
                           rng.choice(handles), scratch_pointer(), scratch_pointer()])

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in OUTPUTS:
            writes = []
            registers = {'eax': eax, 'edx': edx, 'ebx': ebx, 'ecx': ecx}
            for where, width in OUTPUTS[address]:
                pointer = stack[0] if where == 'stack0' else registers[where]
                if stack_low <= pointer < STACK:
                    out = rng.getrandbits(8 * width)
                    cpu.mem_write(pointer, out.to_bytes(width, 'little'))
                    writes.append((pointer, out, width))
            outs_pending.append(writes)
        value = value_mix()
        replay_values.append(value)
        return value

    replay_values = []
    stubs = LocalStubs(cpu, handler)

    @Call
    def call(site, context):
        s = site.contents
        count = counts.get(s.target, 0)
        entry = (s.target, s.eax, s.edx, s.ebx, s.ecx) + tuple(
            (s.stack, s.stack_next, s.stack_third, *[getattr(s, 'rest%d' % i) for i in range(8)])[:count])
        native_log.append(entry)
        if s.target in OUTPUTS and outs_pending_native:
            for pointer, out, width in outs_pending_native.pop(0):
                for index in range(width):
                    stack_buffer[pointer - stack_low + index] = (out >> (8 * index)) & 0xff
        return replay.pop(0)

    @Virtual
    def virtual(context, handle, slot, argument):
        native_log.append(('virtual', handle, slot))
        return replay.pop(0)

    native_writes = {}
    unsupported = [False]

    def touches_pool(address):
        if handles[0] - 8 <= address < handles[-1] + SIZE + 8:
            unsupported[0] = True

    @Global
    def global_read(address, context):
        touches_pool(address)
        try:
            memory = bytes(cpu.mem_read(address, 4))
        except UcError:
            memory = bytes(4)
        return struct.unpack('<I', bytes(native_writes.get(address + i, memory[i])
                                         for i in range(4)))[0]

    @GlobalWrite
    def global_write(address, value, context):
        touches_pool(address)
        for index in range(4):
            native_writes[address + index] = (value >> (8 * index)) & 0xff

    @Draw
    def draw(divisor, context):
        return 0

    @Allocate
    def allocate(size, context):
        return 0

    @Range
    def table_range(index, lo, hi, context):
        return 0

    outs_pending_native = []
    counts = {}
    calls_struct = Calls(call, None)
    factory = Factory(pool.resolve, allocate, draw, table_range, None)
    services = Services(c.pointer(calls_struct), pool.resolve, None, virtual, None, draw, None,
                        c.pointer(factory), global_read, None, global_write)
    results = {}
    for address in routines:
        function = getattr(n, 'vertrix_lift_%06x' % address)
        function.argtypes = [c.POINTER(Context)] + [U] * 8
        function.restype = U
        targets, slots = callees(source, address)
        counts.clear()
        counts.update(targets)
        stubs.remove_all()
        for slot in range(SLOTS):
            stubs.add(SLOT_BASE + 0x10 * slot, 0)
        for target, count in targets.items():
            if target != address:
                stubs.add(target, count)
        cpu.ctl_flush_tb()  # code translated before the hooks existed must be re-translated
        passed = skipped = 0
        failure = None
        reasons = {}
        for case in range(args.cases):
            def patch(handle, data):
                for offset in range(0, SIZE, 4):
                    choice = rng.random()
                    if choice < 0.25:
                        value = rng.choice(handles)
                    elif choice < 0.35:
                        value = scratch_pointer()
                    elif choice < 0.55:
                        value = 0
                    elif choice < 0.8:
                        value = rng.randrange(0, 64)
                    else:
                        value = rng.getrandbits(32)
                    struct.pack_into('<I', data, offset, value)
                struct.pack_into('<I', data, 0x158, VTABLE)
            pool.fill(rng, patch)
            cpu.mem_write(0x950000, rng.randbytes(0x20000))
            for offset in range(0, STACK_SPAN, 4):
                struct.pack_into('<I', stack_buffer, offset, rng.getrandbits(32))
            cpu.mem_write(stack_low, bytes(stack_buffer[:STACK_SPAN]))
            for register in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP):
                cpu.reg_write(register, rng.getrandbits(32))
            registers = {name: value_mix() for name in ('edx', 'ebx', 'ecx')}
            entry_eax = rng.choice(handles)
            esi, edi, ebp = (cpu.reg_read(r) for r in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP))
            arguments = tuple(rng.getrandbits(32) for _ in range(4))
            stubs.log.clear()
            replay_values.clear()
            outs_pending.clear()
            state['writes'].clear()
            state['recording'] = True
            try:
                result = original.call(address, eax=entry_eax, args=arguments, **registers)
                completed = True
            except UcError as error:
                completed = False
                reasons[str(error)] = reasons.get(str(error), 0) + 1
            except RuntimeError:
                completed = False
                reasons['step limit'] = reasons.get('step limit', 0) + 1
            state['recording'] = False
            oracle_writes = list(state['writes'])
            after = {}
            for write_address, size, old, value in oracle_writes:
                for index in range(size):
                    after[write_address + index] = (value >> (8 * index)) & 0xff
            # restore the globals the original wrote, for the native run
            for write_address, size, old, value in reversed(oracle_writes):
                try:
                    cpu.mem_write(write_address, old)
                except UcError:
                    pass
            if not completed:
                skipped += 1
                if skipped >= 25 and passed < 5:
                    break
                continue
            stack_buffer[STACK_SPAN:STACK_SPAN + 20] = (c.c_uint8 * 20).from_buffer_copy(
                struct.pack('<I', 0) + struct.pack('<IIII', *arguments))
            above = bytes(cpu.mem_read(STACK + 20, 0x40 - 20))
            for index, byte in enumerate(above):
                stack_buffer[STACK_SPAN + 20 + index] = byte
            expected = []
            for entry in stubs.log:
                if entry[0] >= SLOT_BASE and entry[0] < SLOT_BASE + 0x10 * SLOTS:
                    expected.append(('virtual', entry[1], (entry[0] - SLOT_BASE) // 0x10))
                else:
                    count = stubs.arguments.get(entry[0], 0)
                    expected.append(tuple(entry[:5 + count]))
            replay[:] = list(replay_values)
            outs_pending_native[:] = [list(w) for w in outs_pending]
            native_log.clear()
            native_writes.clear()
            unsupported[0] = False
            context = Context(c.pointer(services), c.addressof(stack_buffer), stack_low,
                              STACK_SPAN + 0x40, 0, 0)
            got = function(c.byref(context), entry_eax, registers['edx'], registers['ebx'],
                           registers['ecx'], esi, edi, ebp, STACK)
            if unsupported[0]:
                skipped += 1
                reasons['pointer into an object'] = reasons.get('pointer into an object', 0) + 1
                continue
            problems = []
            if native_log != expected:
                first = next((i for i, (x, y) in enumerate(zip(native_log, expected)) if x != y),
                             min(len(native_log), len(expected)))
                problems.append(('calls', 'first difference', first, len(native_log), len(expected),
                                 native_log[first:first + 2], expected[first:first + 2]))
            elif (got & 0xffffffff) != (result & 0xffffffff):
                problems.append(('result', hex(got), hex(result)))
            elif context.failed:
                problems.append(('failed',))
            elif replay:
                problems.append(('replay left', replay))
            elif not pool.same():
                problems.append(('objects', pool.diff()))
            else:
                after_native = dict(native_writes)
                def peek(address):
                    try:
                        return cpu.mem_read(address, 1)[0]
                    except UcError:
                        return None
                for byte_address, value in after.items():
                    original_byte = peek(byte_address)
                    if after_native.get(byte_address, original_byte) != value:
                        problems.append(('global', hex(byte_address), after_native.get(byte_address), value))
                        break
                for byte_address, value in after_native.items():
                    original_byte = peek(byte_address)
                    if after.get(byte_address, original_byte) != value:
                        problems.append(('global native', hex(byte_address), value))
                        break
            if problems:
                failure = (case, problems[0])
                break
            passed += 1
        results[hex(address)] = {'passed': passed, 'skipped': skipped, 'reasons': reasons,
                                 'failure': None if failure is None else str(failure)[:600]}
        print(hex(address), results[hex(address)], flush=True)
    if args.report:
        args.report.write_text(json.dumps(results, indent=1))
    bad = [a for a, r in results.items() if r['failure'] or r['passed'] < args.cases // 4]
    print({'routines': len(results), 'bad': len(bad)})
    return 1 if bad else 0


if __name__ == '__main__':
    raise SystemExit(main())

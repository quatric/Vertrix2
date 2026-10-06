"""Compare complete original display object routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
import verify_support as vs

OBJ, SIZE, POOL = vs.SCRATCH, 0x200, vs.SCRATCH + 0x1000
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
Call = c.CFUNCTYPE(c.c_int32, c.c_void_p, c.c_uint32, c.c_uint32, c.c_uint32)
Call3 = c.CFUNCTYPE(c.c_int32, c.c_void_p, c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32)


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'display-object', ['display_object.c'])
    U8P, U, S = c.POINTER(c.c_uint8), c.c_uint32, c.c_size_t
    n.vertrix_display_chain_count.argtypes = [U8P, S, Resolve, c.c_void_p, c.POINTER(U)]
    n.vertrix_display_chain_find.argtypes = [U8P, S, Resolve, c.c_void_p, c.POINTER(U), c.POINTER(U)]
    n.vertrix_display_ready.argtypes = [U8P, S]
    n.vertrix_display_release_pair.argtypes = [U8P, S, Call, c.c_void_p]
    n.vertrix_display_notify.argtypes = [U8P, S, U, Call3, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    release_stubs = vs.VirtualStubs(cpu, register=False)
    rng = random.Random(0x47f160)
    objects, events = {}, []

    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = len(objects[handle])
        return 1

    @Call
    def call(context, handle, slot, argument):
        events.append((handle, slot))
        return 0

    @Call3
    def call3(context, handle, slot, a, b, d):
        events.append((handle, slot, a, b, d))
        return 0

# 0x47fe20.. use four stack words; the release pair uses one.Share one vtable with ret 16
#for the notifications and the standard one for releases by using separate objects.
    notify_stubs = vs.VirtualStubs(cpu, register=False, stack_args=4, base=0x80e000)
    pool = [POOL + 0x100 * k for k in range(10)]
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def buf(data):
        return (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))

    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        key = rng.randbytes(16)
        data[0xa4:0xb4] = key
        order = rng.sample(pool, rng.randrange(0, 9))
        for index, node in enumerate(order):
            node_data = bytearray(rng.randbytes(0x100))
            node_data[8:24] = key if rng.random() < 0.25 else rng.randbytes(16)
            struct.pack_into('<I', node_data, 0x60, order[index + 1] if index + 1 < len(order) else 0)
            cpu.mem_write(node, bytes(node_data))
            objects[node] = c.create_string_buffer(bytes(node_data), 0x100)
        struct.pack_into('<I', data, 0xc, order[0] if order else 0)
        cpu.mem_write(OBJ, bytes(data))
        original.call(0x47f160, eax=OBJ)
        out = c.c_uint32(7)
        assert n.vertrix_display_chain_count(buf(data), SIZE, resolve, None, c.byref(out))
        assert out.value == cpu.reg_read(UC_X86_REG_EAX), case
        count('0x47f160')
        original.call(0x47f320, eax=OBJ)
        want_handle = cpu.reg_read(UC_X86_REG_EAX)
        original.call(0x47f370, eax=OBJ)
        want_index = cpu.reg_read(UC_X86_REG_EAX)
        handle, index = c.c_uint32(7), c.c_uint32(7)
        assert n.vertrix_display_chain_find(buf(data), SIZE, resolve, None, c.byref(handle), c.byref(index))
        assert (handle.value, index.value) == (want_handle, want_index), case
        count('0x47f320')
        count('0x47f370')
        data[0:4] = rng.choice([b'\0\0\0\0', rng.randbytes(4)])
        data[0x10:0x14] = rng.choice([b'\0\0\0\0', rng.randbytes(4)])
        cpu.mem_write(OBJ, bytes(data))
        original.call(0x47f410, eax=OBJ)
        assert n.vertrix_display_ready(buf(data), SIZE) == cpu.reg_read(UC_X86_REG_EAX), case
        count('0x47f410')
# 0x47ea20 release pair
        for node in pool[:3]:
            cpu.mem_write(node, struct.pack('<I', release_stubs.VTABLE))
        for slot in (4, 8):
            struct.pack_into('<I', data, slot, rng.choice([0] + pool[:3]))
        cpu.mem_write(OBJ, bytes(data))
        release_stubs.events.clear()
        events.clear()
        original.call(0x47ea20, eax=OBJ)
        b = buf(data)
        assert n.vertrix_display_release_pair(b, SIZE, call, None)
        assert bytes(b) == bytes(cpu.mem_read(OBJ, SIZE))
        assert [e[:2] for e in release_stubs.events] == events, case
        count('0x47ea20')
# 0x47fe20 / 0x47fe50 / 0x47fe80 notifications
        for node in pool[3:6]:
            cpu.mem_write(node, struct.pack('<I', notify_stubs.VTABLE))
        struct.pack_into('<I', data, 0x1bc, rng.choice([0] + pool[3:6]))
        struct.pack_into('<I', data, 0x1c0, rng.choice([0, 1, rng.getrandbits(32)]))
        cpu.mem_write(OBJ, bytes(data))
        for address, mode in ((0x47fe20, 1), (0x47fe50, 2), (0x47fe80, 4)):
            notify_stubs.events.clear()
            notify_stubs.stack_log.clear()
            events.clear()
            original.call(address, eax=OBJ)
            assert n.vertrix_display_notify(buf(data), SIZE, mode, call3, None)
            want = [(h, s) + log[1:] for (h, s, _), log in zip(notify_stubs.events, notify_stubs.stack_log)]
            assert want == events, (case, hex(address), want, events)
            count(hex(address))
    vs.write_report(args, 'display-object', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 47f160, 47f320, 47f370, 47f410, 47ea20, 47fe20, 47fe50 and 47fe80 '
                 'execute in the original over guest node chains of 0 to 8 nodes and vtable stubs; '
                 'counts, found nodes/indices, readiness, object bytes and every interface call '
                 '(handle, slot and stack arguments) compare.'})


if __name__ == '__main__':
    main()

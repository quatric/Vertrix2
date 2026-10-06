"""Compare the complete original queue pop with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX
import verify_common_a as common

U = c.c_uint32
Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
Release = c.CFUNCTYPE(None, U, c.c_void_p)
Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
Copy = c.CFUNCTYPE(None, U, U, U, c.c_void_p)
POOL, NODE = 0x806000, 0x40


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'link-queue', 'link_queue.c', 'actor_storage.c')
    n.vertrix_queue_pop.argtypes = [U, Resolve, Release, c.c_void_p]
    n.vertrix_queue_pop.restype = c.c_int
    n.vertrix_queue_push.argtypes = [U, U, U, Resolve, Allocate, Copy, Release, c.c_void_p]
    n.vertrix_queue_push.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x405ea0)
    events, native, objects = [], [], {}
    common.stub(cpu, 0x4ea190, lambda uc: events.append(uc.reg_read(UC_X86_REG_EAX)))

    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = len(objects[handle])
        return 1

    @Release
    def release(handle, context):
        native.append(handle)

    handles = [POOL + NODE * k for k in range(8)]
    totals = {}
    for case in range(args.cases):
        header = handles[0]
        nodes = handles[1:]
        rng.shuffle(nodes)
        length = rng.randrange(1, 7)
        chain = nodes[:length]
        blobs = {}
        for h in handles:
            blobs[h] = bytearray(rng.randbytes(NODE))
        struct.pack_into('<II', blobs[header], 0, chain[-1], chain[0])
        for i, h in enumerate(chain):
            struct.pack_into('<I', blobs[h], 0xc, chain[i + 1] if i + 1 < length else 0)
            struct.pack_into('<I', blobs[h], 0x10, chain[i - 1] if i else 0)
        cpu.mem_write(POOL, bytes(NODE * 8))
        for h, blob in blobs.items():
            cpu.mem_write(h, bytes(blob))
        objects.clear()
        for h, blob in blobs.items():
            objects[h] = c.create_string_buffer(bytes(blob), NODE)
        events.clear(); native.clear()
        original.call(0x405ea0, eax=header)
        assert n.vertrix_queue_pop(header, resolve, release, None) == 1, case
        assert events == native and len(events) == 2, case
        for h in handles:
            assert objects[h].raw == bytes(cpu.mem_read(h, NODE)), (case, hex(h))
        totals['pop_length_%d' % length] = totals.get('pop_length_%d' % length, 0) + 1
    plan, plan_native = [], []

    def on_allocate(uc):
        events.append(('alloc', uc.reg_read(UC_X86_REG_EAX)))
        cpu.mem_write(common.DATA + 8, struct.pack('<I', plan.pop(0)))

    common.stub(cpu, 0x4e7c90, on_allocate, 2)
    common.stub(cpu, 0x4eb5e0, lambda uc: events.append(
        ('copy', uc.reg_read(UC_X86_REG_EAX), uc.reg_read(UC_X86_REG_EDX), uc.reg_read(UC_X86_REG_EBX))), 3)

    @Allocate
    def allocate(size, context):
        native.append(('alloc', size))
        return plan_native.pop(0)

    @Copy
    def copy(destination, source, size, context):
        native.append(('copy', destination, source, size))

    fresh_node, payload_base = handles[7], 0x80c000
    for case in range(args.cases):
        header = handles[0]
        length = rng.randrange(0, 5)
        chain = handles[1:1 + length]
        blobs = {h: bytearray(rng.randbytes(NODE)) for h in handles}
        struct.pack_into('<III', blobs[header], 0, chain[-1] if chain else 0, chain[0] if chain else 0,
                         rng.getrandbits(32))
        for i, h in enumerate(chain):
            struct.pack_into('<I', blobs[h], 0xc, chain[i + 1] if i + 1 < length else 0)
            struct.pack_into('<I', blobs[h], 0x10, chain[i - 1] if i else 0)
        cpu.mem_write(POOL, bytes(NODE * 8))
        for h, blob in blobs.items():
            cpu.mem_write(h, bytes(blob))
        objects.clear()
        for h, blob in blobs.items():
            objects[h] = c.create_string_buffer(bytes(blob), NODE)
        outcome = rng.choice(['ok', 'ok', 'ok', 'no_payload', 'no_node'])
        size = rng.randrange(0, 0x100)
        source = rng.getrandbits(32)
        plan[:] = {'ok': [fresh_node, payload_base], 'no_payload': [fresh_node, 0], 'no_node': [0]}[outcome]
        plan_native[:] = list(plan)
        events.clear(); native.clear()
        want = original.call(0x405e00, eax=header, edx=source, ebx=size)
        got = n.vertrix_queue_push(header, source, size, resolve, allocate, copy, release, None)
        assert want == got, (case, outcome)
        assert events == native, (case, outcome, events, native)
        for h in handles:
            assert objects[h].raw == bytes(cpu.mem_read(h, NODE)), (case, outcome, hex(h))
        key = 'push_' + outcome
        totals[key] = totals.get(key, 0) + 1
    common.report(args, 'link-queue', totals,
                  'Complete 405ea0 and 405e00 run unmodified in the original (allocator 4e7c90 and copy 4eb5e0 stubbed; success and both allocation failures) over random queues of 1..6 nodes; '
                  'release stub 4ea190 records payload then node, and header and all nodes compare. '
                  'The empty queue faults in the original and is not exercised.')


if __name__ == '__main__':
    main()

"""Compare complete original actor list idle checks with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
import verify_support as vs

POOL, ARRAYS = vs.SCRATCH + 0x1000, vs.SCRATCH + 0x400
LISTS = ((0x471c90, 0x546720, 0x546724), (0x471cd0, 0x54675c, 0x546760),
         (0x471d10, 0x546748, 0x54674c), (0x471d50, 0x546734, 0x546738),
         (0x472360, 0x546770, 0x546774))
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'actor-list-idle', ['actor_list_idle.c', 'actor_fields.c', 'actor_storage.c'])
    U = c.c_uint32
    n.vertrix_actor_list_all_idle.argtypes = [c.POINTER(U), U, Resolve, c.c_void_p, c.POINTER(U)]
    n.vertrix_actor_list_idle_except.argtypes = [c.POINTER(U), U, U, Resolve, c.c_void_p, c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x471c90)
    pool = [POOL + 0x200 * k for k in range(12)]
    objects = {}

    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in objects:
            return 0
        storage[0] = c.addressof(objects[handle])
        size[0] = len(objects[handle])
        return 1

    totals = {}
    for case in range(args.cases):
        owner = rng.choice(pool)
        idle_bias = rng.choice([0.5, 0.9, 1.0])
        for handle in pool:
            data = bytearray(rng.randbytes(0x200))
            struct.pack_into('<I', data, 0x154, 0 if rng.random() < idle_bias else rng.getrandbits(32) | 1)
            struct.pack_into('<I', data, 0x14c, owner if rng.random() < 0.3 else rng.choice(pool))
            cpu.mem_write(handle, bytes(data))
            objects[handle] = c.create_string_buffer(bytes(data), 0x200)
        for address, pointer, counter in LISTS:
            count = rng.choice([0, 1, 2, 5, 12])
            handles = [rng.choice(pool) for _ in range(count)]
            cpu.mem_write(ARRAYS, struct.pack('<%dI' % max(count, 1), *(handles or [0])))
            cpu.mem_write(pointer, struct.pack('<I', ARRAYS))
            cpu.mem_write(counter, struct.pack('<I', count))
            original.call(address)
            result = cpu.reg_read(UC_X86_REG_EAX)
            out = c.c_uint32(7)
            assert n.vertrix_actor_list_all_idle((U * max(count, 1))(*(handles or [0])), count, resolve, None, c.byref(out))
            assert out.value == result, (case, hex(address))
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        count = rng.choice([0, 1, 2, 5, 12])
        handles = [rng.choice(pool) for _ in range(count)]
        cpu.mem_write(ARRAYS, struct.pack('<%dI' % max(count, 1), *(handles or [0])))
        cpu.mem_write(0x546720, struct.pack('<I', ARRAYS))
        cpu.mem_write(0x546724, struct.pack('<I', count))
        original.call(0x471c40, eax=owner)
        result = cpu.reg_read(UC_X86_REG_EAX)
        out = c.c_uint32(7)
        assert n.vertrix_actor_list_idle_except((U * max(count, 1))(*(handles or [0])), count, owner, resolve, None, c.byref(out))
        assert out.value == result, (case, 'except')
        totals['0x471c40'] = totals.get('0x471c40', 0) + 1
    vs.write_report(args, 'actor-list-idle', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 471c40, 471c90, 471cd0, 471d10, 471d50 and 472360 execute in the '
                 'original over handle arrays of 0 to 12 actors in guest memory; results compare, '
                 'including early exit and empty arrays.'})


if __name__ == '__main__':
    main()

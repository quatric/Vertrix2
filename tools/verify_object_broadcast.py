"""Compare the original virtual-method broadcasts over object lists with the native loop."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original, STACK
from oracle_kit import build
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_EDI,
                               UC_X86_REG_EDX, UC_X86_REG_ESI, UC_X86_REG_ESP)

LIST_MAIN, LIST_A, LIST_B = 0x54671c, 0x546744, 0x546730
HEAP, ITEMS, OBJECTS, TABLE, STUBS = 0x920000, 0x920000, 0x921000, 0x930000, 0x700100
SLOTS = (0x4, 0xc, 0x10, 0x14, 0x18)


class List(c.Structure):
    _fields_ = [('items', c.POINTER(c.c_uint32)), ('count', c.c_size_t), ('capacity', c.c_size_t)]


Call = c.CFUNCTYPE(None, c.c_uint32, c.c_uint, c.c_uint32, c.c_uint32, c.c_void_p)

# (original address, list address or None for "EAX is the list", slot, register arguments used)
ROUTINES = (
    (0x4b60c0, None, 0xc, 2), (0x4b6120, None, 0x10, 1), (0x4b6170, None, 0x14, 1),
    (0x4b61c0, None, 0x18, 0), (0x4b6200, None, 0x4, 0),
    (0x471a20, LIST_MAIN, 0xc, 2), (0x471a40, LIST_MAIN, 0x10, 1),
    (0x471a50, LIST_MAIN, 0x14, 1), (0x471a60, LIST_MAIN, 0x18, 0), (0x471a70, LIST_MAIN, 0x4, 0),
    (0x471a80, LIST_A, 0x4, 0), (0x471b00, LIST_B, 0x4, 0),
    (0x471ab0, LIST_A, 0xc, 2), (0x471ad0, LIST_A, 0x10, 1), (0x471ae0, LIST_A, 0x14, 1),
    (0x471af0, LIST_A, 0x18, 0),
    (0x471b30, LIST_B, 0xc, 2), (0x471b50, LIST_B, 0x10, 1), (0x471b60, LIST_B, 0x14, 1),
    (0x471b70, LIST_B, 0x18, 0),
)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    p.add_argument('--cases', type=int, default=512)
    a = p.parse_args()
    native = build(a.build_dir, 'object-broadcast', ['object_list.c'])
    native.vertrix_object_list_broadcast.argtypes = [c.POINTER(List), c.c_uint, c.c_uint32,
                                                     c.c_uint32, Call, c.c_void_p]
    o = Original(a.executable)
    cpu = o.cpu
    cpu.mem_map(HEAP, 0x20000)
    stub_slot = {}
    for index, slot in enumerate(SLOTS):
        address = STUBS + 0x10 * (index + 1)
        cpu.mem_write(address, b'\xc3')
        stub_slot[address] = slot
        cpu.mem_write(TABLE + slot, struct.pack('<I', address))
    objects = [OBJECTS + i * 0x200 for i in range(40)]
    for handle in objects:
        cpu.mem_write(handle + 0x158, struct.pack('<I', TABLE))
    rng = random.Random(0x4b60c0)
    plan = {}
    original_events, native_events = [], []

    def mutate(array, index, storage_write):
        if index in plan:
            position, handle = plan[index]
            storage_write(position, handle)

    def guest_call(emu, address, size, context):
        slot = stub_slot[address]
        eax, edx, ebx = (emu.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX))
        original_events.append((eax, slot, edx if slot in (0xc, 0x10, 0x14) else 0,
                                ebx if slot == 0xc else 0))
        mutate(None, len(original_events) - 1,
               lambda position, handle: emu.mem_write(ITEMS + 4 * position, struct.pack('<I', handle)))

    for address in stub_slot:
        cpu.hook_add(UC_HOOK_CODE, guest_call, begin=address, end=address)
    storage = (c.c_uint32 * 40)()

    @Call
    def native_call(handle, slot, edx, ebx, context):
        native_events.append((handle, slot, edx if slot in (0xc, 0x10, 0x14) else 0,
                              ebx if slot == 0xc else 0))
        mutate(None, len(native_events) - 1, lambda position, handle: storage.__setitem__(position, handle))

    totals = {'0x%06x' % r[0]: 0 for r in ROUTINES}
    visited = 0
    for case in range(a.cases):
        count = rng.randrange(0, 33)
        handles = [rng.choice(objects) for _ in range(count)]
        for address, list_address, slot, arguments in ROUTINES:
            plan.clear()
            if count and case % 3 == 0:
                plan[rng.randrange(count)] = (rng.randrange(count), rng.choice(objects))
            for position in range(40):
                storage[position] = handles[position] if position < count else 0xdeadbeef
            cpu.mem_write(ITEMS, bytes(storage))
            list_object = list_address or 0x546700
            cpu.mem_write(list_object, struct.pack('<III', 0x518344, ITEMS, count))
            edx, ebx, other = (rng.getrandbits(32) for _ in range(3))
            for register in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP):
                cpu.reg_write(register, other)
            original_events.clear()
            native_events.clear()
            if list_address is None:
                o.call(address, eax=list_object, edx=edx, ebx=ebx)
                values = (edx, ebx)
            else:
                o.call(address, eax=edx, edx=ebx)
                values = (edx, ebx)
            lst = List(storage, count, 40)
            assert native.vertrix_object_list_broadcast(c.byref(lst), slot, values[0],
                                                       values[1], native_call, None) == 1
            assert original_events == native_events, (case, hex(address), original_events,
                                                    native_events)
            assert len(original_events) == count, (case, hex(address), 'count')
            assert tuple(cpu.reg_read(r) for r in (UC_X86_REG_ESI, UC_X86_REG_EDI,
                                                   UC_X86_REG_EBP)) == (other,) * 3, (
                case, hex(address), 'preserved registers')
            assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4, (case, hex(address), 'stack')
            assert bytes(cpu.mem_read(ITEMS, 160)) == bytes(storage)[:160], (case, 'list storage')
            totals['0x%06x' % address] += 1
            visited += count
    null_storage = (c.c_uint32 * 2)(objects[0], 0)
    lst = List(null_storage, 2, 2)
    native_events.clear()
    assert native.vertrix_object_list_broadcast(c.byref(lst), 0xc, 1, 2, native_call, None) == 0
    assert native.vertrix_object_list_broadcast(None, 0xc, 1, 2, native_call, None) == 0
    assert native.vertrix_object_list_broadcast(c.byref(List(storage, 1, 40)), 0xc, 1, 2,
                                               Call(0), None) == 0 and not native_events
    report = {'status': 'passed', 'complete_original_executions': totals,
              'virtual_calls_compared': visited,
              'scope': 'Complete original routines 0x4b60c0, 0x4b6120, 0x4b6170, 0x4b61c0, '
                       '0x4b6200 and the wrappers 0x471a20, 0x471a40, 0x471a50, 0x471a60, 0x471a70, '
                       '0x471a80, 0x471ab0, 0x471ad0, 0x471ae0, 0x471af0, 0x471b00, 0x471b30, '
                       '0x471b50, 0x471b60 and 0x471b70 run against lists of 0 to 32 '
                       'objects, one third with a virtual method rewriting a later handle. The '
                       'order, receiver and register arguments of every virtual call, the list '
                       'storage, preserved ESI/EDI/EBP and stack cleanup match the native '
                       'broadcast. Null handles, null lists and a null callback are rejected.'}
    (a.build_dir / 'object-broadcast-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print('passed', sum(totals.values()), 'executions', visited, 'virtual calls')


if __name__ == '__main__':
    main()

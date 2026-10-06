"""Compare original dynamic object-list updates, destruction and removal."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_GDTR, UC_X86_REG_SS, UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_CS


class List(c.Structure):
    _fields_ = [('items', c.POINTER(c.c_uint32)), ('count', c.c_size_t), ('capacity', c.c_size_t)]
    Visit = c.CFUNCTYPE(None, c.c_uint32, c.c_uint, c.c_void_p)
    State = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.c_void_p)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'object-list.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'object_list.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_object_list_update.argtypes = [c.POINTER(List), Visit, c.c_void_p]
    n.vertrix_object_list_prune.argtypes = [c.POINTER(List), c.c_uint32, State, Visit, c.c_void_p]
    o = Original(a.executable)
    o.cpu.mem_map(0x900000, 0x10000)
    o.cpu.mem_write(0x700100, b'\xc3')
    o.cpu.mem_write(0x700110, b'\xc3')
    o.cpu.mem_write(0x709000, struct.pack('<II', 0x700110, 0x700100))
#CRT memory move reloads ES.Supply real flat 32 - bit segment descriptors.
    o.cpu.mem_write(0x70a000, struct.pack('<3Q', 0, 0x00cf92000000ffff, 0x00cf9a000000ffff))
    o.cpu.reg_write(UC_X86_REG_GDTR, (0, 0x70a000, 23, 0))
    for reg, selector in ((UC_X86_REG_SS, 8), (UC_X86_REG_DS, 8), (UC_X86_REG_ES, 8), (UC_X86_REG_CS, 16)):
        o.cpu.reg_write(reg, selector)
    objects = [0x900000 + i * 512 for i in range(32)]
    states = {}
    original_events = []
    native_events = []
    mutate = False
    def original_visit(cpu, address, size, context):
        handle = cpu.reg_read(UC_X86_REG_EAX)
        destroy = cpu.reg_read(UC_X86_REG_EDX) if address == 0x700110 else 0
        original_events.append((handle, destroy))
        if not destroy and mutate:
            cpu.mem_write(handle + 0x154, bytes(4))
    for addr in (0x700100, 0x700110):
        o.cpu.hook_add(UC_HOOK_CODE, original_visit, begin=addr, end=addr)
    @ Visit
    def visit(handle, destroy, context):
        native_events.append((handle, destroy))
        if not destroy and mutate:
            states[handle] = 0
    @ State
    def state(handle, output, context):
        if handle not in states:
            return 0
        output[0] = states[handle]
        return 1
        rng = random.Random(0x4b5f50)
        compared = removed = 0
    for case in range(2048):
        count = rng.randrange(33)
        handles = rng.sample(objects, count)
        storage = (c.c_uint32 * 32)(* handles, * [0xdeadbeef] * (32 - count))
        lst = List(storage, count, 32)
        mutate = case % 3 == 0
        matching = rng.choice([0, 1, 2, 0xffffffff])
        states = {handle: rng.choice([0, 1, 2, 0xffffffff]) for handle in objects}
        for handle in objects:
            record = bytearray(512)
        struct.pack_into('<II', record, 0x154, states[handle], 0x709000)
        o.cpu.mem_write(handle, bytes(record))
        o.cpu.mem_write(BOARD, struct.pack('<4I', 0x518344, MASK, count, 32))
        o.cpu.mem_write(MASK, bytes(storage))
        original_events.clear()
        native_events.clear()
        o.call(0x4b6200, eax=BOARD, edx=0)
        assert n.vertrix_object_list_update(c.byref(lst), visit, None)
        assert original_events == native_events, (case, 'updates')
        original_events.clear()
        native_events.clear()
        o.call(0x4b5f50, eax=BOARD, edx=matching)
        assert n.vertrix_object_list_prune(c.byref(lst), matching, state, visit, None)
        assert original_events == native_events, (case, 'destroy order', matching, original_events, native_events)
        assert lst.count == struct.unpack('<I', o.cpu.mem_read(BOARD + 8, 4))[0]
        assert bytes(storage) == bytes(o.cpu.mem_read(MASK, 128)), (case, 'storage including stale tail')
        compared += count
        removed += count - lst.count
        storage = (c.c_uint32 * 2)(objects[0], 0)
        lst = List(storage, 2, 2)
        native_events.clear()
        assert not n.vertrix_object_list_update(c.byref(lst), visit, None) and not native_events
        assert not n.vertrix_object_list_prune(c.byref(lst), 0, state, visit, None) and not native_events
        assert not n.vertrix_object_list_update(None, visit, None)
    report = {'status': 'passed', 'cases': 2048, 'updated_objects': compared, 'destroyed_objects': removed, 'scope': 'Actual original 0x4b6200 updates, 0x4b5f50 state getter/filter, 0x4b5ee0 destructor traversal and 0x4d8950 shift with real original memory move. Only object virtual update/destructor leaves captured. Exact update/destruction order, post-update state matching, count and entire list storage including stale tail. Runtime allocation/object implementations and complete game integration remain unfinished.'}
    (a.build_dir / 'object-list-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

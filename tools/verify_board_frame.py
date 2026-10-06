"""Compare complete board handler composition against original x86 execution."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_scene import Scene, OFFSETS
from verify_object_list import List, Visit
from verify_scene_layout import Resolver
from verify_scene_lock import Object as FullObject, Piece
from verify_descent import DescentState
from verify_timing import Motion
from verify_timer import Timer
from verify_board_effects import Effect, Effects, Timer as EffectTimer
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_GDTR, UC_X86_REG_SS, UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_CS
Object = FullObject


class Frame(c.Structure):
    _fields_ = [('scene', c.POINTER(Scene)), ('list', c.POINTER(List)), ('resolve', Resolver), ('visit', Visit), ('context', c.c_void_p), ('x', c.c_int16), ('y', c.c_int16)]


class Board(c.Structure):
    _fields_ = [('effects', Effects), ('frame', Frame), ('piece', c.POINTER(Piece)), ('descent', c.POINTER(DescentState)), ('elapsed', c.c_uint32), ('paused', c.c_int), ('frozen', c.c_uint32), ('blink', c.c_uint32), ('failed', c.c_uint32)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    lib = a.build_dir.resolve() / 'frame.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / name) for name in ('board_frame.c', 'board_effects.c', 'scene_fall.c', 'scene_descent.c', 'scene_lock.c', 'scene_frame.c', 'scene.c', 'object_list.c', 'descent.c', 'collision.c', 'board.c', 'timer.c')], '-o', str(lib)], check=True)
    n = c.CDLL(str(lib))
    n.vertrix_board_frame.argtypes = [c.POINTER(Board)]
    o = Original(a.executable)
    o.cpu.mem_map(0x900000, 0x10000)
    o.cpu.mem_write(0x700100, b'\xc3')
    o.cpu.mem_write(0x700110, b'\xc3')
    o.cpu.mem_write(0x709000, struct.pack('<II', 0x700110, 0x700100))
    o.cpu.mem_write(0x70a000, struct.pack('<3Q', 0, 0x00cf92000000ffff, 0x00cf9a000000ffff))
    o.cpu.reg_write(UC_X86_REG_GDTR, (0, 0x70a000, 23, 0))
    for reg, sel in ((UC_X86_REG_SS, 8), (UC_X86_REG_DS, 8), (UC_X86_REG_ES, 8), (UC_X86_REG_CS, 16)):
        o.cpu.reg_write(reg, sel)
    objects = {0x900000 + i * 512: Object() for i in range(64)}
    piece_handle = 0x908000
    effect_handles = (0x908200, 0x908400)
    objects[piece_handle] = Object()
    handles = list(objects)
    original_events = []
    native_events = []
    case = 0
    @ Resolver
    def resolve(handle, context):
        return c.addressof(objects[handle]) if handle in objects else None
    @ Visit
    def visit(handle, destroy, context):
        native_events.append((handle, destroy))
        if not destroy and handle in objects and ((handle - 0x900000) // 512 + case) % 3 == 0:
            objects[handle].state = 0
    def original_leaf(cpu, address, size, context):
        handle = cpu.reg_read(UC_X86_REG_EAX)
        if address == 0x4b14c0:
            obj = objects[handle]
            cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX), struct.pack('<i', obj.width))
            cpu.mem_write(cpu.reg_read(UC_X86_REG_EBX), struct.pack('<i', obj.height))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
            return
        destroy = cpu.reg_read(UC_X86_REG_EDX) if address == 0x700110 else 0
        original_events.append((handle, destroy))
        if not destroy and handle in objects and ((handle - 0x900000) // 512 + case) % 3 == 0:
            cpu.mem_write(handle + 0x154, bytes(4))
    for address in (0x4b14c0, 0x700100, 0x700110):
        o.cpu.hook_add(UC_HOOK_CODE, original_leaf, begin=address, end=address)
    rng = random.Random(0x42fb60)
    operations = removed = 0
    for case in range(256):
        scene = Scene()
        raw = bytearray(0xd00)
        ox = rng.randrange(0, 201)
        oy = rng.randrange(200, 401)
        struct.pack_into('<h', raw, 14, ox)
        struct.pack_into('<h', raw, 22, oy)
        for field, offset, size in [('cell_a', 0x15c, 65), ('cell_b', 0x19d, 65), ('columns_a', 0x99c, 5), ('columns_b', 0x9a1, 5), ('rows', 0x9a6, 52)]:
            flags = bytes(rng.randrange(256) for _ in range(size))
            raw[offset: offset + size] = flags
            c.memmove(c.addressof(getattr(scene, field)), flags, size)
        for index, offset in enumerate(OFFSETS):
            handle = rng.choice([0] * 8 + handles[: 32])
            scene.slots[index] = handle
            struct.pack_into('<I', raw, offset, handle)
        scene.active = rng.choice([0, piece_handle])
        scene.extra = rng.choice([0] + handles[: 32])
        scene.suppress_layout = rng.randrange(3)
        scene.active_a = rng.randrange(256)
        scene.active_b = rng.randrange(256)
        struct.pack_into('<I', raw, 0xa60, scene.active)
        struct.pack_into('<I', raw, 0xce0, scene.extra)
        struct.pack_into('<I', raw, 0xb8c, scene.suppress_layout)
        raw[0xa64] = scene.active_a
        raw[0xa65] = scene.active_b
        for handle, obj in objects.items():
            obj.x = rng.randrange(- 32768, 32768)
            obj.y = rng.randrange(- 32768, 32768)
            obj.mode = rng.randrange(17)
            obj.width = rng.randrange(- 32768, 32768)
            obj.height = rng.randrange(- 32768, 32768)
            obj.state = rng.choice([0, 1, 2, 0xffffffff])
            obj.active_a = rng.randrange(256)
            obj.active_b = rng.randrange(256)
            obj.field_93 = rng.randrange(256)
            obj.field_4e = rng.randrange(256)
            obj.effect = rng.randrange(65536)
            data = bytearray(512)
            struct.pack_into('<h', data, 14, obj.x)
            struct.pack_into('<h', data, 22, obj.y)
            data[0x44] = obj.mode
            struct.pack_into('<II', data, 0x154, obj.state, 0x709000)
            data[0x16c] = obj.active_a
            data[0x16d] = obj.active_b
            data[0x93] = obj.field_93
            data[0x4e] = obj.field_4e
            struct.pack_into('<H', data, 0x48, obj.effect)
            o.cpu.mem_write(handle, bytes(data))
        count = rng.randrange(33)
        items = rng.sample(handles[32: 64], count)
        storage = (c.c_uint32 * 32)(* items, * [0xdeadbeef] * (32 - count))
        lst = List(storage, count, 32)
        struct.pack_into('<4I', raw, 0xcec, 0x518344, MASK, count, 32)
        piece = Piece(piece_handle, (c.c_uint32 * 3)(* handles[: 3]), ox + rng.randrange(5) * 24, oy + rng.randrange(- 72, 240))
        objects[piece_handle].x = piece.x
        objects[piece_handle].y = piece.y
        state = DescentState(Motion(rng.choice([0, 1, 100, 0xffffffff]), rng.getrandbits(32), rng.choice([0, 1, 2, 24, 32768, 65535]), rng.getrandbits(32)), Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])), rng.choice([0, 1, 2, 0xffffffff]), rng.getrandbits(32), rng.randrange(3), (c.c_uint16 * 3)())
        elapsed = rng.choice([0, 1, 16, 100, 0xffffffff])
        paused = case % 4 == 0
        frozen = rng.choice([0, 0, 0, 0, 1, 2])
        blink_mode = rng.randrange(3)
        failed = rng.getrandbits(32)
        record = bytearray(o.cpu.mem_read(piece_handle, 512))
        struct.pack_into('<h', record, 14, piece.x)
        struct.pack_into('<h', record, 22, piece.y)
        struct.pack_into('<3I', record, 0x15c, * piece.children)
        struct.pack_into('<I', record, 0xbc, state.motion.counter)
        struct.pack_into('<I', record, 0xc0, state.motion.period)
        struct.pack_into('<H', record, 0x1a, state.motion.step)
        struct.pack_into('<I', record, 0x168, state.motion.state)
        struct.pack_into('<2I', record, 0xdc, state.blink.counter, state.blink.period)
        struct.pack_into('<3I', record, 0x17c, state.cycle_mode, state.frozen, state.flash)
        o.cpu.mem_write(piece_handle, bytes(record))
        first = Effect(0, rng.choice([0, 1, 2]), rng.getrandbits(32), rng.getrandbits(32), EffectTimer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])), rng.randrange(65536))
        second = Effect(0, rng.choice([0, 1, 2]), rng.getrandbits(32), rng.getrandbits(32), EffectTimer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])), rng.randrange(65536))
        parameters = [rng.randrange(3), rng.randrange(3)]
        present = [bool(rng.randrange(2)) for _ in range(2)]
        for kind, actor in enumerate((first, second)):
            record = bytearray(512)
            struct.pack_into('<I', record, 0x158, 0x709000)
            struct.pack_into('<3I', record, 0x15c if kind == 0 else 0x17c, actor.parameter, actor.state, actor.flash)
            struct.pack_into('<I', record, 0xbc, actor.primary)
            struct.pack_into('<2I', record, 0xdc, actor.blink.counter, actor.blink.period)
            struct.pack_into('<H', record, 0x48, actor.effect)
            o.cpu.mem_write(effect_handles[kind], bytes(record))
        struct.pack_into('<I', raw, 0xb70, effect_handles[0] if present[0] else 0)
        struct.pack_into('<I', raw, 0xb78, effect_handles[1] if present[1] else 0)
        struct.pack_into('<I', raw, 0xb84, parameters[0])
        struct.pack_into('<I', raw, 0xb88, parameters[1])
        struct.pack_into('<I', raw, 0xb80, frozen)
        struct.pack_into('<I', raw, 0xb90, blink_mode)
        struct.pack_into('<I', raw, 0xbd8, failed)
        struct.pack_into('<I', raw, 0xce8, 0x90f000)
        o.cpu.mem_write(0x90f000, bytes(0x500))
        o.cpu.mem_write(0x90f4cc, bytes([paused]))
        o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        effects = Effects(c.pointer(first) if present[0] else None, c.pointer(second) if present[1] else None, * effect_handles, * parameters)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.cpu.mem_write(MASK, bytes(storage))
        original_events.clear()
        native_events.clear()
        o.call(0x42fb60, eax=BOARD)
        frame = Frame(c.pointer(scene), c.pointer(lst), resolve, visit, None, ox, oy)
        board = Board(effects, frame, c.pointer(piece), c.pointer(state), elapsed, paused, frozen, blink_mode, failed)
        assert n.vertrix_board_frame(c.byref(board))
        assert scene.active == struct.unpack('<I', o.cpu.mem_read(BOARD + 0xa60, 4))[0] and board.failed == struct.unpack('<I', o.cpu.mem_read(BOARD + 0xbd8, 4))[0]
        assert tuple(piece.children) == struct.unpack('<3I', o.cpu.mem_read(piece_handle + 0x15c, 12))
        assert state.motion.counter == struct.unpack('<I', o.cpu.mem_read(piece_handle + 0xbc, 4))[0] and (state.blink.counter, state.blink.period) == struct.unpack('<2I', o.cpu.mem_read(piece_handle + 0xdc, 8))
        assert (state.cycle_mode, state.frozen, state.flash) == struct.unpack('<3I', o.cpu.mem_read(piece_handle + 0x17c, 12))
        for kind, actor in enumerate((first, second)):
            record = o.cpu.mem_read(effect_handles[kind], 512)
            assert (actor.parameter, actor.state, actor.flash) == struct.unpack_from('<3I', record, 0x15c if kind == 0 else 0x17c)
            assert actor.primary == struct.unpack_from('<I', record, 0xbc)[0]
            assert (actor.blink.counter, actor.blink.period) == struct.unpack_from('<2I', record, 0xdc)
            assert actor.effect == struct.unpack_from('<H', record, 0x48)[0]
        assert original_events == native_events, (case, 'virtual trace')
        assert list(scene.slots) == [struct.unpack('<I', o.cpu.mem_read(BOARD + offset, 4))[0] for offset in OFFSETS]
        assert (state.motion.period, state.motion.step, state.motion.state) == (struct.unpack('<I', o.cpu.mem_read(piece_handle + 0xc0, 4))[0], struct.unpack('<H', o.cpu.mem_read(piece_handle + 0x1a, 2))[0], struct.unpack('<I', o.cpu.mem_read(piece_handle + 0x168, 4))[0])
        for handle, obj in objects.items():
            assert (obj.x, obj.y) == (struct.unpack('<h', o.cpu.mem_read(handle + 14, 2))[0], struct.unpack('<h', o.cpu.mem_read(handle + 22, 2))[0]), (case, hex(handle), 'position')
            assert obj.state == struct.unpack('<I', o.cpu.mem_read(handle + 0x154, 4))[0]
            assert bytes([obj.active_a, obj.active_b]) == bytes(o.cpu.mem_read(handle + 0x16c, 2))
            assert (obj.field_93, obj.field_4e, obj.effect) == (o.cpu.mem_read(handle + 0x93, 1)[0], o.cpu.mem_read(handle + 0x4e, 1)[0], struct.unpack('<H', o.cpu.mem_read(handle + 0x48, 2))[0])
        assert lst.count == struct.unpack('<I', o.cpu.mem_read(BOARD + 0xcf4, 4))[0] and bytes(storage) == bytes(o.cpu.mem_read(MASK, 128))
        for field, offset, size in [('cell_a', 0x15c, 65), ('cell_b', 0x19d, 65), ('columns_a', 0x99c, 5), ('columns_b', 0x9a1, 5), ('rows', 0x9a6, 52)]:
            assert bytes(getattr(scene, field)) == bytes(o.cpu.mem_read(BOARD + offset, size)) == bytes(size)
        assert scene.active_a == scene.active_b == 0
        operations += len(native_events)
        removed += count - lst.count
    assert not n.vertrix_board_frame(None)
    report = {'status': 'passed', 'frames': 256, 'object_state_comparisons': 256 * 65, 'virtual_operations': operations, 'removed_objects': removed, 'scope': 'Complete native board handler compared with actual original 0x42fb60. Actual layout, list update/state filtering/destruction/shift and ten resets execute. Only dimensions and object virtual methods supplied. Positions, active parameters, object states, virtual trace, complete list storage/count and flags match. Effect and fall timers, object transfers, layout, list operations and flags compared together. Object virtual handlers, player/game logic, rendering and complete game remain unfinished.'}
    (a.build_dir / 'board-frame-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

"""Compare board effect prefix with the original state/timer implementations."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_object_list import Visit
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX


class Timer(c.Structure):
    _fields_ = [('counter', c.c_uint32), ('period', c.c_uint32)]


class Effect(c.Structure):
    _fields_ = [('parameter', c.c_uint32), ('state', c.c_uint32), ('flash', c.c_uint32), ('primary', c.c_uint32), ('blink', Timer), ('effect', c.c_uint16)]


class Effects(c.Structure):
    _fields_ = [('first', c.POINTER(Effect)), ('second', c.POINTER(Effect)), ('first_handle', c.c_uint32), ('second_handle', c.c_uint32), ('first_parameter', c.c_uint32), ('second_parameter', c.c_uint32)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    lib = a.build_dir.resolve() / 'effects.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'board_effects.c'), str(source / 'timer.c'), '-o', str(lib)], check=True)
    n = c.CDLL(str(lib))
    n.vertrix_board_effects_tick.argtypes = [c.POINTER(Effects), c.c_uint32, Visit, c.c_void_p]
    o = Original(a.executable)
    o.cpu.mem_map(0x900000, 0x10000)
    o.cpu.mem_write(0x700100, b'\xc3')
    o.cpu.mem_write(0x709004, struct.pack('<I', 0x700100))
    handles = (0x900000, 0x900200)
    native_events = []
    original_events = []
    replacement = 0
    mutate = False
    controller = None
    def original_visit(cpu, address, size, context):
        handle = cpu.reg_read(UC_X86_REG_EAX)
        original_events.append(handle)
        if mutate and handle == handles[0]:
            cpu.mem_write(BOARD + 0xb88, struct.pack('<I', replacement))
            o.cpu.hook_add(UC_HOOK_CODE, original_visit, begin=0x700100, end=0x700100)
            @ Visit
            def visit(handle, destroy, context):
                assert not destroy
                native_events.append(handle)
                if mutate and handle == handles[0]:
                    controller.second_parameter = replacement
                    rng = random.Random(0x42fb60)
                    comparisons = updates = 0
                    def value():
                        return rng.choice([0, 1, 2, 0xffffffff, rng.getrandbits(32)])
                        def encode(effect, kind, data):
                            result = bytearray(data)
                            struct.pack_into('<3I', result, 0x15c if kind == 0 else 0x17c, effect.parameter, effect.state, effect.flash)
                            struct.pack_into('<I', result, 0xbc, effect.primary)
                            struct.pack_into('<2I', result, 0xdc, effect.blink.counter, effect.blink.period)
                            struct.pack_into('<H', result, 0x48, effect.effect)
                            return bytes(result)
    for case in range(4096):
        actors = [Effect(value(), value(), value(), value(), Timer(value(), value()), rng.randrange(65536)) for _ in range(2)]
        present = [bool(rng.randrange(2)) for _ in range(2)]
        params = [value(), value()]
        elapsed = value()
        mutate = case % 2 == 0
        replacement = value()
        raw = bytearray(0xd00)
        struct.pack_into('<I', raw, 0xb70, handles[0] if present[0] else 0)
        struct.pack_into('<I', raw, 0xb78, handles[1] if present[1] else 0)
        struct.pack_into('<I', raw, 0xb84, params[0])
        struct.pack_into('<I', raw, 0xb88, params[1])
        baselines = []
        for kind, actor in enumerate(actors):
            data = bytearray(rng.randbytes(512))
        struct.pack_into('<I', data, 0x158, 0x709000)
        data = encode(actor, kind, data)
        baselines.append(data)
        o.cpu.mem_write(handles[kind], data)
        controller = Effects(c.pointer(actors[0]) if present[0] else None, c.pointer(actors[1]) if present[1] else None, * handles, * params)
        o.cpu.mem_write(BOARD, bytes(raw))
        o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        original_events.clear()
        native_events.clear()
        o.call(0x42fb60, eax=BOARD, stop=0x42fbba)
        assert n.vertrix_board_effects_tick(c.byref(controller), elapsed, visit, None)
        assert native_events == original_events, (case, 'virtual order')
        for kind, actor in enumerate(actors):
            assert encode(actor, kind, baselines[kind]) == bytes(o.cpu.mem_read(handles[kind], 512)), (case, kind, 'whole object')
            comparisons += 1
        assert controller.second_parameter == struct.unpack('<I', o.cpu.mem_read(BOARD + 0xb88, 4))[0]
        updates += len(native_events)
        assert not n.vertrix_board_effects_tick(None, 0, visit, None)
        controller = Effects(c.pointer(actors[0]), None, 0, 0, 0, 0)
        assert not n.vertrix_board_effects_tick(c.byref(controller), 0, visit, None)
    report = {'status': 'passed', 'cases': 4096, 'whole_object_comparisons': comparisons, 'virtual_updates': updates, 'scope': 'Original 0x42fb60..0x42fbba prefix with actual effect state setters, blink/timer methods and toggle routines. Only virtual updates captured. Whole effect objects match, including absent objects, arbitrary state/flash/parameters, zero/wrapped timers and second-parameter mutation during first update. Character meaning, virtual object implementations and complete board/game integration remain unfinished.'}
    (a.build_dir / 'board-effects-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

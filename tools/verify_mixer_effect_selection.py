"""Verify main dispatch selection and complete callback effect."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original, BOARD
Callback = ctypes.CFUNCTYPE(None, ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'effect-selection.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_effect_select.argtypes = [ctypes.c_uint8, ctypes.c_uint8]
    native.vertrix_mixer_effect_callback.argtypes = [ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint32, ctypes.c_uint32, Callback, ctypes.c_void_p]
    original = Original(args.executable)
    targets = struct.unpack('<36I', original.cpu.mem_read(0x4f7444, 144))
    selected = []
    def capture(cpu, address, size, data):
        selected.append(address)
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, capture, begin=a, end=a) for a in set(targets)]
    try:
        for effect in range(256):
            for parameter in range(256):
                data = bytearray(192)
                data[3: 5] = bytes((effect, parameter))
                original.cpu.mem_write(BOARD, bytes(data))
                selected.clear()
                original.call(0x40dc50, eax=BOARD)
                expected = - 1 if not selected or selected[0] in (0x40dc30, 0x40d9a0) else effect
                assert native.vertrix_mixer_effect_select(effect, parameter) == expected, (effect, parameter)
                assert bytes(original.cpu.mem_read(BOARD, 192)) == bytes(data)
    finally:
        for hook in hooks:
            original.cpu.hook_del(hook)
    rng = random.Random(0x40dc10)
    events = []
    native_events = []
    callback_address = 0x700200
    original.cpu.mem_write(callback_address, b'\xc3')
    def callback_capture(cpu, address, size, data):
        events.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX), cpu.reg_read(UC_X86_REG_EBX)))
        hook = original.cpu.hook_add(UC_HOOK_CODE, callback_capture, begin=callback_address, end=callback_address)
        @ Callback
        def callback(parameter, order, row, context):
            assert context == 123
            native_events.append((parameter, order, row))
            cases = 20000
            try:
                for index in range(cases):
                    channel = bytearray(rng.randbytes(192))
                    parameter = index % 256
                    channel[3] = 35
                    channel[4] = parameter
                    tick = 0 if index % 3 == 0 else rng.randrange(- 2147483648, 2147483648)
                    present = index % 2
                    order, row = rng.getrandbits(32), rng.getrandbits(32)
                    original.cpu.mem_write(BOARD, bytes(channel))
                    original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
                    original.cpu.mem_write(0x531b50, struct.pack('<I', row))
                    original.cpu.mem_write(0x531b5c, struct.pack('<I', order))
                    original.cpu.mem_write(0x531b7c, struct.pack('<I', callback_address if present else 0))
                    events.clear()
                    native_events.clear()
                    original.call(0x40dc50, eax=BOARD)
                    native.vertrix_mixer_effect_callback(parameter, tick, order, row, callback if present else Callback(), 123)
                    assert native_events == events, index
                    assert bytes(original.cpu.mem_read(BOARD, 192)) == bytes(channel)
            finally:
                original.cpu.hook_del(hook)
    report = {'status': 'passed', 'dispatch_selection_cases': 65536, 'callback_cases': cases, 'scope': 'Complete original 0x40dc50 selection over every effect/parameter pair; hooks capture selected target without executing it. Complete callback effect executes with a return-only callback and captured arguments. Verifies tick gate, callback presence, parameter/order/row and channel preservation. Excludes unified effect execution.'}
    (build / 'mixer-effect-selection-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

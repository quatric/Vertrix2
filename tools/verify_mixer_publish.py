"""Compare original channel publication command order and arguments."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original, BOARD, MASK

class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('sample', 'offset', 'period', 'volume', 'pan')] + [('flags', ctypes.c_uint8)]
class Command(ctypes.Structure):
    _fields_ = [('value', ctypes.c_uint32), ('kind', ctypes.c_uint8)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'publish.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_publish function.argtypes = [
    ctypes.c_uint32, ctypes.c_int, ctypes.POINTER(State), ctypes.POINTER(Command),
    ctypes.POINTER(ctypes.c_size_t)
] original = Original(args.executable);
rng = random.Random(0x40e8a0);
events = [] addresses = (0x40adb0, 0x40ade0, 0x40add0, 0x40adf0, 0x40ae00, 0x40ae10,
                         0x40adc0)def capture(cpu, address, size, data)
    : kind = addresses.index(address);
value = cpu.reg_read(UC_X86_REG_EDX) assert cpu.reg_read(UC_X86_REG_EAX) == MASK if kind ==
        0 : value = (value - 36) & 0xffffffff if kind in(2, 6)
    : value = 0 events.append((kind, value)) stack = cpu.reg_read(UC_X86_REG_ESP);
target = struct.unpack('<I', cpu.mem_read(stack, 4))[0] cpu.reg_write(UC_X86_REG_ESP, stack + 4); cpu.reg_write(UC_X86_REG_EIP, target)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, capture, begin=a, end=a) for a in addresses]
    cases = 40000
try:
        for
            index in range(cases) : data = bytearray(rng.randbytes(192)); sample = 0 if index % 2 == 0 else rng.getrandbits(32)
            data[1] = (index // 2) % 256; linear = (index // 512) % 2
            offset, period, volume, pan = [rng.getrandbits(32) for _ in range(4)]
            if index % 3 == 0: period = rng.randrange(1, 7680); volume = rng.randrange(65); pan = rng.randrange(256)
            global_volume = rng.getrandbits(32) if index % 3 else rng.randrange(65)
            for position, value in ((56,sample),(116,offset),(44,period),(24,volume),(32,pan)):
                struct.pack_into('<I', data, position, value)
            state = State(sample, offset, period, volume, pan, data[1]); commands = (Command * 7)(); count = ctypes.c_size_t()
            original.cpu.mem_write(BOARD, bytes(data)); original.cpu.mem_write(0x531b46, bytes([linear]))
            original.cpu.mem_write(0x531b68, struct.pack('<I', global_volume)); events.clear()
            original.call(0x40e8a0, eax=MASK, edx=BOARD)
            assert function(global_volume, linear, ctypes.byref(state), commands, ctypes.byref(count))
            assert [(commands[i].kind, commands[i].value) for i in range(count.value)] == events, index
            actual = bytearray(data); actual[1] = state.flags
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 192)), index
    finally:
        for hook in hooks: original.cpu.hook_del(hook)
    before = bytes(state); prior_count = count.value
    assert not function(64, 0, ctypes.byref(state), None, ctypes.byref(count))
    assert bytes(state) == before and count.value == prior_count
    report = {'status':'passed', 'publication_cases':cases,
        'scope':'Complete original 0x40e8a0; captures mixer call order and arguments, all update flags with/without sample, both pitch modes, global-volume wrapping and whole channel preservation. Hooks replace mixer delivery only. Excludes execution of emitted commands and audio delivery.'}
    (build / 'mixer-publish-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__': main()

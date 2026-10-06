"""Shared helpers for the small oracle comparison scripts: native build and scratch memory."""
import argparse, ctypes as c, json, random, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE

ROOT = Path(__file__).resolve().parents[1]
SCRATCH = 0x808000


def parse(description, default_cases=4096):
    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=default_cases)
    return parser.parse_args()


def build(args, name, sources):
    """Compile recovered sources into a shared library and load it."""
    out = args.build_dir.resolve()
    out.mkdir(parents=True, exist_ok=True)
    library = out / (name + '.dylib')
    paths = [str(ROOT / 'source' / s) for s in sources]
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', *paths,
                    '-o', str(library)], check=True)
    return c.CDLL(str(library))


def write_report(args, name, report):
    out = args.build_dir.resolve() / (name + '-verification.json')
    out.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


class VirtualStubs:
    """Data-driven virtual-call stubs shared by every slot of one vtable.

    register=True models Delphi register-convention methods (handle in eax, argument in edx,
    plain ret); otherwise COM-style stdcall methods with the handle pushed (ret 4)."""
    VTABLE, STUBS, STRIDE = 0x80f000, 0x80f100, 0x10

    def __init__(self, cpu, register, slots=16, stack_args=1, base=0x80f000):
        self.VTABLE, self.STUBS = base, base + 0x100
        self.cpu, self.register, self.events, self.returns = cpu, register, [], []
        self.stack_args, self.stack_log = stack_args, []
        for slot in range(slots):
            cpu.mem_write(self.STUBS + slot * self.STRIDE, b'\xc3' if register else b'\xc2' + bytes([4 * stack_args, 0]))
            cpu.mem_write(self.VTABLE + 4 * slot,
                          (self.STUBS + slot * self.STRIDE).to_bytes(4, 'little'))
        cpu.hook_add(UC_HOOK_CODE, self.hook, begin=self.STUBS, end=self.STUBS + slots * self.STRIDE)

    def hook(self, cpu, address, size, user):
        from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP
        slot = (address - self.STUBS) // self.STRIDE
        if self.register:
            self.events.append((cpu.reg_read(UC_X86_REG_EAX), slot, cpu.reg_read(UC_X86_REG_EDX)))
            return
        handle = int.from_bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_ESP) + 4, 4), 'little')
        self.events.append((handle, slot, 0))
        self.stack_log.append(tuple(int.from_bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_ESP) + 4 + 4 * i, 4), 'little')
                                    for i in range(self.stack_args)))
        cpu.reg_write(UC_X86_REG_EAX, (self.returns.pop(0) if self.returns else 0) & 0xffffffff)

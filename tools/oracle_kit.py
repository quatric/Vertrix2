"""Shared helpers for oracle verification scripts: callee stubs and an object pool."""
import ctypes as c
import os
import struct
import subprocess
from pathlib import Path

from unicorn import UC_HOOK_CODE, UcError
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX,
                               UC_X86_REG_EIP, UC_X86_REG_ESP)

POOL = 0x806000
OBJECT_SIZE = 0x200
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t),
                      c.c_void_p)


def build(build_dir, name, sources):
    """Compile the named recovered sources into a shared library and load it."""
    build_dir = Path(build_dir).resolve()
    build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build_dir / (name + '.dylib')
    subprocess.run(['cc', '-std=c11', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', '-I', str(source),
                    *[str(source / item) for item in sources], '-o', str(library)], check=True)
    return c.CDLL(str(library))


# The original's return boundary (original.RETURN).
STOP_RETURN = 0x700000


class Stubs:
    """Replace unrecovered callees with data-driven stubs that log their register arguments.

    handler(address, eax, edx, ebx, ecx, stack_args) returns the new eax (or None to keep it).
    The hooked callee is skipped: its return address is popped together with stack_bytes.
    """

    stops = set()

    # Call site address -> stack argument count, for stubs shared by calls with different counts
    # (every fake object shares one vtable, so slot 0xc serves IDirectSound and its buffers).
    site_arguments = {}

    def __init__(self, cpu, handler):
        self.cpu = cpu
        self.handler = handler
        self.log = []
        self.arguments = {}
        self.cdecl = set()
        self.extras = {}
        # Callees that are also code of the routine under test (0x4e5710 jumps into the body at
        # 0x4e57ac, which it also calls): their stub runs only when a direct call entered them.
        self.internal = set()

    def add(self, address, stack_args=0, cdecl=False):
        self.arguments[address] = stack_args
        if cdecl:
            self.cdecl.add(address)
        self.cpu.hook_add(UC_HOOK_CODE, self._hit, begin=address, end=address)

    def _hit(self, cpu, address, size, context):
        if address in self.internal and not self._called(cpu, address):
            return
        regs = [cpu.reg_read(r) for r in (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX,
                                          UC_X86_REG_ECX)]
        esp = cpu.reg_read(UC_X86_REG_ESP)
        count = self.arguments[address]
        stack = struct.unpack('<' + 'I' * (1 + count), bytes(cpu.mem_read(esp, 4 * (1 + count))))
        popped = self._site_count(cpu, stack[0], count)
        # Slots past the call site's own arguments are the caller's stack, not arguments: the
        # lifted call passes zeros there.
        args = stack[1:1 + popped] + (0,) * (count - popped)
        extra = self.extras[address](cpu, regs, args) if address in self.extras else ()
        self.log.append((address, *regs, *args, *extra))
        result = self.handler(address, *regs, args)
        if result is not None:
            cpu.reg_write(UC_X86_REG_EAX, result & 0xffffffff)
        cpu.reg_write(UC_X86_REG_ESP, esp + 4 + (0 if address in self.cdecl else 4 * popped))
        # A callee that never returns in the game (ExitProcess) ends the original's run there, as
        # its return from the routine (VERTRIX_STOP_CALLEES).
        cpu.reg_write(UC_X86_REG_EIP, STOP_RETURN if address in self.stops else stack[0])


    def _site_count(self, cpu, back, count):
        """The argument count of the indirect call returning to `back`, if it is a known site."""
        for length in (2, 3, 6, 7):
            site = (back - length) & 0xffffffff
            if site in self.site_arguments:
                try:
                    if bytes(cpu.mem_read(site, 1))[0] == 0xff:
                        return min(self.site_arguments[site], count)
                except UcError:
                    pass
        return count

    @staticmethod
    def _called(cpu, address):
        back = struct.unpack('<I', bytes(cpu.mem_read(cpu.reg_read(UC_X86_REG_ESP), 4)))[0]
        try:
            code = bytes(cpu.mem_read((back - 5) & 0xffffffff, 5))
        except UcError:
            return False
        return code[0] == 0xe8 and (back + struct.unpack('<i', code[1:])[0]) & 0xffffffff == address


class Pool:
    """Objects at scratch addresses mirrored as native buffers behind a resolver."""

    def __init__(self, cpu, count=24, size=OBJECT_SIZE):
        self.cpu = cpu
        self.size = size
        self.handles = [POOL + size * i for i in range(count)]
        self.buffers = {}
        self.resolve = Resolve(self._resolve)

    def _resolve(self, handle, storage, size, context):
        index, delta = divmod(handle - POOL, self.size)
        if handle < POOL or index >= len(self.handles) or self.handles[index] not in self.buffers:
            return 0
        storage[0] = c.addressof(self.buffers[self.handles[index]]) + delta
        size[0] = self.size - delta
        return 1

    def fill(self, rng, patch=None):
        for handle in self.handles:
            data = bytearray(rng.randbytes(self.size))
            if patch:
                patch(handle, data)
            self.cpu.mem_write(handle, bytes(data))
            self.buffers[handle] = c.create_string_buffer(bytes(data), self.size)

    # VERTRIX_UNCOMPARED_FIELDS="0x18:4;0x20:12": offsets of every object left out of the
    # comparison, for values the oracle and the lifted runtime cannot share (setjmp's return
    # address and segment selectors).
    UNCOMPARED = [tuple(int(v, 0) for v in item.split(':')) for item in
                  os.environ.get('VERTRIX_UNCOMPARED_FIELDS', '').split(';') if item]

    def _compared(self, data):
        data = bytearray(data)
        for offset, size in self.UNCOMPARED:
            data[offset:offset + size] = bytes(size)
        return bytes(data)

    def same(self):
        return all(self._compared(self.buffers[h].raw) ==
                   self._compared(self.cpu.mem_read(h, self.size)) for h in self.handles)

    def diff(self):
        """The objects that differ, each with its first differing offset and the native and
        original bytes there."""
        result = []
        for h in self.handles:
            native = self._compared(self.buffers[h].raw)
            original = self._compared(self.cpu.mem_read(h, self.size))
            if native != original:
                at = next(i for i in range(self.size) if native[i] != original[i])
                result.append((hex(h), hex(at), native[at], original[at]))
        return result

"""Shared harness for address-space ports (source/native_ports.c, docs/NATIVE-PORTS.md).

Regions of the oracle's memory are mirrored as native buffers. In the object mode the services
resolve them (interior addresses included); in the global mode they are read through the globals
reader and stored through the 0xf0000000 pseudo call, as on the lifted host."""
import ctypes as c

from oracle_kit import Resolve

U = c.c_uint32
GLOBAL_STORE = 0xf0000000


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)
GlobalRead = c.CFUNCTYPE(U, U, c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Globals(c.Structure):
    _fields_ = [('read', GlobalRead), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


class Memory(c.Structure):
    _fields_ = [('calls', c.POINTER(Calls)), ('services', c.POINTER(Services)),
                ('globals', c.POINTER(Globals)), ('ok', c.c_int)]


class Mirror:
    """Native copies of oracle memory regions behind a resolver, a globals reader and stores."""

    def __init__(self, cpu, regions):
        self.cpu = cpu
        self.sizes = dict(regions)
        self.buffers = {base: c.create_string_buffer(size) for base, size in regions.items()}
        self.hidden = set()
        self.stores = []
        self.other = []
        self.resolve = Resolve(self._resolve)
        self.read = GlobalRead(self._read)
        self.call = Call(self._call)
        self.calls = Calls(self.call, None)
        self.services = Services(self.resolve)
        self.globals = Globals(self.read, None)

    def locate(self, address):
        for base, size in self.sizes.items():
            if base <= address < base + size:
                return base
        return None

    def _resolve(self, address, storage, size, context):
        base = self.locate(address)
        if base is None or base in self.hidden:
            return 0
        storage[0] = c.addressof(self.buffers[base]) + address - base
        size[0] = base + self.sizes[base] - address
        return 1

    def _read(self, address, context):
        base = self.locate(address)
        assert base is not None, hex(address)
        raw = self.buffers[base].raw[address - base:address - base + 4]
        return int.from_bytes(raw.ljust(4, b'\0'), 'little')

    def _call(self, site, context):
        s = site.contents
        if s.target != GLOBAL_STORE:
            self.other.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
            return 0
        base = self.locate(s.eax)
        assert base is not None, hex(s.eax)
        c.memmove(c.addressof(self.buffers[base]) + s.eax - base, s.edx.to_bytes(4, 'little'),
                  s.stack)
        self.stores.append(s.eax)
        return 0

    def load(self, rng_bytes):
        """Write the same bytes into the oracle and the mirror: rng_bytes(base, size) -> bytes."""
        for base, size in self.sizes.items():
            blob = rng_bytes(base, size)
            self.cpu.mem_write(base, blob)
            c.memmove(self.buffers[base], blob, size)

    def memory(self, global_mode, hidden=None):
        self.hidden = set(self.sizes if hidden is None else hidden) if global_mode else set()
        self.stores.clear()
        self.other.clear()
        return Memory(c.pointer(self.calls), c.pointer(self.services),
                      c.pointer(self.globals) if global_mode else None, 1)

    def differences(self):
        return [hex(base) for base, size in self.sizes.items()
                if self.buffers[base].raw != bytes(self.cpu.mem_read(base, size))]

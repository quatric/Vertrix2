"""Shared pieces of the screen builder oracles: call sites, services, supplied static data reads."""
import ctypes as c
import json
import struct

U = c.c_uint32


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
    from oracle_kit import Resolve
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def site_log(s, count):
    return (s.target, s.eax, s.edx, s.ebx, s.ecx) + (
        s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2, s.rest3, s.rest4,
        s.rest5, s.rest6, s.rest7)[:count]


def global_reader(cpu):
    @GlobalRead
    def read(address, context):
        return struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0]
    return read


def write_report(build_dir, name, report):
    (build_dir / (name + '-verification.json')).write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

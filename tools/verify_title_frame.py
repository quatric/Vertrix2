"""Compare the original title/menu frame handler 0x41c7b0 with the native call sequence."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original, STACK
from oracle_kit import Stubs, build
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_ESP)

FORM = 0x900100
STORE = 0xf0000000
STARTED, LISTS, MODE, FORWARD, BACKWARD = 0x540338, 0x54033c, 0x532b40, 0x532b48, 0x532b44
CURRENT, REQUESTED, CLOSING, PLAYING, READY = 0x532a50, 0x532a98, 0x532a38, 0x532a84, 0x532a7c
FIRST, SECOND, BACK, BACK_SIZE, FRONT = 0x4f7bb0, 0x4f7bb4, 0x558c84, 0x558c88, 0x558c7c
# Address -> (reads EDX, reads EAX). The others are called with no argument in EAX.
CALLEES = {
    0x41d640: (0, 1), 0x4b7d10: (0, 0), 0x41d670: (0, 1), 0x41dec0: (0, 1), 0x4ac1c0: (0, 0),
    0x419490: (0, 1), 0x472d90: (0, 0), 0x471a70: (0, 0), 0x471a60: (0, 0), 0x4854a0: (0, 1),
    0x471a20: (1, 1), 0x471a40: (0, 1), 0x485520: (0, 1), 0x41aaf0: (0, 1), 0x486d00: (0, 1),
    0x471a50: (0, 1), 0x4194b0: (0, 1), 0x415530: (0, 0), 0x472d50: (0, 0), 0x415550: (0, 0),
    0x41d6d0: (0, 1), 0x41dd60: (0, 1), 0x486da0: (0, 1), 0x487020: (0, 1), 0x41d660: (0, 1),
    0x41de80: (0, 1), 0x41aca0: (0, 1), 0x418130: (0, 0), 0x418840: (1, 1)}
WATCHED = (STARTED, LISTS, CURRENT)


class Call(c.Structure):
    _fields_ = [('target', c.c_uint32), ('eax', c.c_uint32), ('edx', c.c_uint32),
                ('ebx', c.c_uint32), ('ecx', c.c_uint32), ('stack', c.c_uint32),
                ('stack_next', c.c_uint32), ('stack_third', c.c_uint32), ('out_ebx', c.c_uint32),
                ('out_ecx', c.c_uint32), ('stack_rest', c.c_uint32 * 14), ('out_value', c.c_uint32)]


CallFn = c.CFUNCTYPE(c.c_uint32, c.POINTER(Call), c.c_void_p)
ReadFn = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', CallFn), ('context', c.c_void_p)]


class Globals(c.Structure):
    _fields_ = [('read', ReadFn), ('context', c.c_void_p)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    p.add_argument('--cases', type=int, default=4096)
    a = p.parse_args()
    native = build(a.build_dir, 'title-frame', ['title_frame.c', 'call_glue.c', 'actor_storage.c'])
    native.vertrix_title_frame.argtypes = [c.POINTER(Calls), c.POINTER(Globals), c.c_uint32]
    native.vertrix_title_frame.restype = c.c_uint32
    o = Original(a.executable)
    cpu = o.cpu
    rng = random.Random(0x41c7b0)
    events = {'original': [], 'native': []}
    state = {'results': {}}
    memory = {}

    def handler(address, eax, edx, ebx, ecx, args):
        eax_used, edx_used = (edx and 1), None
        events['original'].append(('call', address, eax if CALLEES[address][1] else 0,
                                   edx if CALLEES[address][0] else 0))
        return state['results'].get(address, 0)

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address)

    def written(emu, access, address, size, value, context):
        if address in WATCHED:
            events['original'].append(('store', address, size, value & ((1 << (8 * size)) - 1)))

    cpu.hook_add(UC_HOOK_MEM_WRITE, written)

    def native_call(site, context):
        s = site.contents
        if s.target == STORE:
            size, address, value = s.stack, s.eax, s.edx
            events['native'].append(('store', address, size, value & ((1 << (8 * size)) - 1)))
            for i in range(size):
                memory[address + i] = (value >> (8 * i)) & 255
            return 0
        events['native'].append(('call', s.target, s.eax if CALLEES[s.target][1] else 0,
                                 s.edx if CALLEES[s.target][0] else 0))
        return state['results'].get(s.target, 0)

    def read(address, context):
        return sum(memory.get(address + i, 0) << (8 * i) for i in range(4))

    calls = Calls(CallFn(native_call), None)
    globals_ = Globals(ReadFn(read), None)
    small = (0, 1, 2, 3)
    shapes = set()
    for case in range(a.cases):
        values = {STARTED: rng.choice((0, 1)), LISTS: rng.choice((0, 1)), MODE: rng.choice(small),
                  FORWARD: rng.choice(small), BACKWARD: rng.choice(small),
                  CURRENT: rng.choice(small), REQUESTED: rng.choice(small),
                  CLOSING: rng.choice(small), PLAYING: rng.choice(small),
                  READY: rng.choice(small), FIRST: rng.choice(small), SECOND: rng.choice(small),
                  BACK: rng.getrandbits(32), BACK_SIZE: rng.getrandbits(32),
                  FRONT: rng.getrandbits(32)}
        if case % 4 == 0:
            values[FIRST], values[SECOND] = 1, 2
            values[CURRENT] = rng.choice((1, 2, 3))
        if rng.random() < 0.3:
            values[STARTED] |= rng.choice((0, 0x100, 0xff00))
        memory.clear()
        for address, value in values.items():
            cpu.mem_write(address, struct.pack('<I', value))
            for i in range(4):
                memory[address + i] = (value >> (8 * i)) & 255
        state['results'] = {0x4854a0: rng.choice((0, 1, 2)), 0x418130: rng.choice((0, 0, 1))}
        form = rng.getrandbits(32) | 1
        others = tuple(rng.getrandbits(32) for _ in range(3))
        for register, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others):
            cpu.reg_write(register, value)
        events['original'].clear()
        events['native'].clear()
        o.call(0x41c7b0, eax=form)
        native.vertrix_title_frame(c.byref(calls), c.byref(globals_), form)
        assert events['original'] == events['native'], (case, events['original'], events['native'])
        assert tuple(cpu.reg_read(r) for r in (UC_X86_REG_ESI, UC_X86_REG_EDI,
                                               UC_X86_REG_EBP)) == others, (case, 'registers')
        assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4, (case, 'stack')
        for address in WATCHED:
            assert read(address, None) == struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0], (
                case, hex(address), 'final value')
        shapes.add(tuple(e[1] for e in events['original'] if e[0] == 'call'))
    report = {'status': 'passed', 'complete_original_executions': {'0x41c7b0': a.cases},
              'distinct_call_sequences': len(shapes),
              'scope': 'The complete original 0x41c7b0 runs with every callee (the stage routines '
                       '0x41d640, 0x4b7d10, 0x41d670, 0x41dec0, 0x4ac1c0, 0x419490, 0x472d90, '
                       '0x471a70, 0x471a60, 0x4854a0, 0x471a20, 0x471a40, 0x485520, 0x41aaf0, '
                       '0x486d00, 0x471a50, 0x4194b0, 0x415530, 0x472d50, 0x415550, 0x41d6d0, '
                       '0x41dd60, 0x486da0, 0x487020, 0x41d660, 0x41de80, 0x41aca0, 0x418130 and '
                       '0x418840) replaced by a logging stub, over random flag states, screen '
                       'slots and transition modes. The order of every call with the registers '
                       'it reads (EAX, and EDX for 0x471a20 and 0x418840) and of every store to '
                       '0x540338, 0x54033c and 0x532a50 matches the native sequence; the final '
                       'values, preserved ESI/EDI/EBP and the stack cleanup match too. Callees '
                       'are assumed to read no register other than the ones compared.'}
    (a.build_dir / 'title-frame-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print('passed', a.cases, 'cases', len(shapes), 'distinct call sequences')


if __name__ == '__main__':
    main()

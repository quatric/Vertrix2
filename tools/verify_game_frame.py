"""Compare the original game-screen frame handler 0x41b820 with the native call sequence."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original, STACK
from oracle_kit import Stubs, build
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_ESP)

STORE = 0xf0000000
STARTED = 0x540330
SCREENS = tuple(range(0x4f7b44, 0x4f7bb0, 4))
CURRENT, REQUESTED, MODE, FORWARD, BACKWARD, CLOSING = (0x532a4c, 0x532a98, 0x532b40, 0x532b48,
                                                         0x532b44, 0x532a38)
LISTS, PHASE, CONFIRM, PROFILES = 0x540334, 0x532a0c, 0x532a34, 0x532bcc
SETTINGS = (0x532b54, 0x532b58, 0x532b5c, 0x532b60)
COPIES = (0x532bbc, 0x532bc0, 0x532bc4, 0x532bc8)
STATES = (0x532a74, 0x532a78, 0x532a7c, 0x532a80, 0x532a84, 0x532a8c)
BUFFERS = (0x558c7c, 0x558c84, 0x558c88)
# Address -> (reads EDX, reads EAX). The others are called with no argument in EAX.
CALLEES = {address: flags for address, flags in (
    (0x41d640, (0, 1)), (0x4b7cd0, (0, 0)), (0x4b7d10, (0, 0)), (0x41d670, (0, 1)),
    (0x41dec0, (0, 1)), (0x419490, (0, 1)), (0x472d90, (0, 0)), (0x471a70, (0, 0)),
    (0x471a80, (0, 0)), (0x471b00, (0, 0)), (0x471a60, (0, 0)), (0x471b70, (0, 0)),
    (0x471af0, (0, 0)), (0x4854a0, (0, 1)), (0x471ab0, (1, 1)), (0x471b30, (1, 1)),
    (0x471a20, (1, 1)), (0x471ad0, (0, 1)), (0x471b50, (0, 1)), (0x471a40, (0, 1)),
    (0x485520, (0, 1)), (0x41aaf0, (0, 1)), (0x486d00, (0, 1)), (0x471ae0, (0, 1)),
    (0x471b60, (0, 1)), (0x471a50, (0, 1)), (0x4194b0, (0, 1)), (0x41d6d0, (0, 1)),
    (0x41dd60, (0, 1)), (0x486da0, (0, 1)), (0x487020, (0, 1)), (0x41d660, (0, 1)),
    (0x4154b0, (0, 0)), (0x41de80, (0, 1)), (0x415530, (0, 0)), (0x472d50, (0, 0)),
    (0x415550, (0, 0)), (0x41aca0, (0, 1)), (0x4719e0, (0, 0)), (0x4614c0, (0, 0)),
    (0x461610, (0, 0)), (0x461790, (0, 0)), (0x461360, (0, 0)), (0x461930, (0, 0)),
    (0x461fc0, (0, 0)), (0x4627a0, (0, 0)), (0x4651b0, (0, 1)), (0x4633b0, (0, 1)),
    (0x418840, (1, 1)), (0x415c60, (0, 0)), (0x415b50, (0, 0)), (0x415b10, (0, 0)),
    (0x415b90, (0, 0)), (0x415bd0, (0, 0)), (0x48c6c0, (0, 1)), (0x48c2b0, (0, 1)),
    (0x48b770, (0, 1)))}
WATCHED = (STARTED, LISTS, PHASE, CURRENT) + STATES + COPIES


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
    native = build(a.build_dir, 'game-frame', ['game_frame.c', 'call_glue.c', 'actor_storage.c'])
    native.vertrix_game_frame.argtypes = [c.POINTER(Calls), c.POINTER(Globals), c.c_uint32]
    native.vertrix_game_frame.restype = c.c_uint32
    o = Original(a.executable)
    cpu = o.cpu
    rng = random.Random(0x41b820)
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
        if address in WATCHED and size in (1, 4):
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
    shapes, branches = set(), set()

    def segments(log):
        """Calls in order, with the stores between two calls compared as a set when they hit
        distinct addresses (independent stores) and in order otherwise."""
        result, stores = [], []
        for event in log + [('call', None, 0, 0)]:
            if event[0] == 'store':
                stores.append(event)
                continue
            addresses = [e[1] for e in stores]
            result.append(tuple(sorted(stores)) if len(set(addresses)) == len(addresses)
                          else tuple(stores))
            result.append(event)
            stores = []
        return result

    for case in range(a.cases):
        values = {address: rng.choice(small) for address in
                  (LISTS, PHASE, MODE, FORWARD, BACKWARD, CLOSING, REQUESTED, PROFILES) + STATES}
        values[STARTED] = rng.choice((0, 1)) | (rng.choice((0, 0x100)) if rng.random() < 0.2 else 0)
        values[CONFIRM] = rng.choice((0, 1, 1, 0x101, 2))
        for address in SCREENS:
            values[address] = rng.randrange(0, 12)
        if case % 3 == 0:
            for address in SCREENS:
                values[address] = rng.randrange(0, 40)
        values[CURRENT] = values[rng.choice(SCREENS)] if rng.random() < 0.9 else rng.randrange(40)
        if rng.random() < 0.2:
            values[REQUESTED] = values[CURRENT]
        elif rng.random() < 0.5:
            values[REQUESTED] = values[rng.choice(SCREENS)]
        for address in SETTINGS + BUFFERS + COPIES:
            values[address] = rng.getrandbits(32)
        memory.clear()
        for address, value in values.items():
            cpu.mem_write(address, struct.pack('<I', value))
            for i in range(4):
                memory[address + i] = (value >> (8 * i)) & 255
        state['results'] = {0x4854a0: rng.choice((0, 1, 2)), 0x418130: 0}
        form = rng.getrandbits(32) | 1
        others = tuple(rng.getrandbits(32) for _ in range(3))
        for register, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others):
            cpu.reg_write(register, value)
        events['original'].clear()
        events['native'].clear()
        o.call(0x41b820, eax=form)
        native.vertrix_game_frame(c.byref(calls), c.byref(globals_), form)
        assert segments(events['original']) == segments(events['native']), (
            case, events['original'], events['native'])
        assert tuple(cpu.reg_read(r) for r in (UC_X86_REG_ESI, UC_X86_REG_EDI,
                                               UC_X86_REG_EBP)) == others, (case, 'registers')
        assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4, (case, 'stack')
        for address in WATCHED:
            assert read(address, None) == struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0], (
                case, hex(address), 'final value')
        sequence = tuple(e[1] for e in events['original'] if e[0] == 'call')
        shapes.add(sequence)
        branches.update(sequence)
    assert branches >= set(CALLEES) - {0x4854a0}, sorted(hex(x) for x in set(CALLEES) - branches)
    report = {'status': 'passed', 'complete_original_executions': {'0x41b820': a.cases},
              'distinct_call_sequences': len(shapes),
              'scope': 'The complete original 0x41b820 runs with every callee it reaches (the '
                       'stage routines, the scene-list wrappers 0x471a20..0x471b70, the screen '
                       'routines 0x4614c0, 0x461610, 0x461790, 0x461360, 0x461930, 0x461fc0, '
                       '0x4627a0, 0x4651b0, 0x4633b0, the level resets 0x415b50, 0x415b10, '
                       '0x415b90, 0x415bd0, 0x415c60, the dialog routines 0x48c6c0, 0x48c2b0, '
                       '0x48b770 and the handler installer 0x418840) replaced by a logging stub, '
                       'over random flags, screen tables (with repeated numbers) and current and '
                       'requested screens. The order of every call with the registers it reads '
                       '(EAX, and EDX for the scene-list pairs and 0x418840) matches the native '
                       'sequence, as do the stores between two calls (as a set when they hit '
                       'distinct addresses), the final values of every stored static, preserved '
                       'ESI/EDI/EBP and the stack cleanup. Callees are assumed to read no '
                       'register other than the ones compared, and 0x415b50, 0x415b10 and '
                       '0x48c6c0 to preserve EDX.'}
    (a.build_dir / 'game-frame-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print('passed', a.cases, 'cases', len(shapes), 'distinct call sequences')


if __name__ == '__main__':
    main()

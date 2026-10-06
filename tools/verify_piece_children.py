"""Compare complete original piece child routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Attach = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'piece-children',
              ['piece_children.c', 'actor_storage.c', 'actor_fields.c'])
    K = c.c_uint8 * 3
    n.vertrix_piece_child_kinds.argtypes = [U, Resolve, c.c_void_p, K]
    n.vertrix_piece_children_setup.argtypes = [U, K, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_children_setup_selected.argtypes = [U, K, U * 3, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_children_setup_registers.argtypes = [U, K, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_children_remember_and_setup.argtypes = [U, K, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_set_variant.argtypes = [U, U, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_snap_to_left.argtypes = [U, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_snap_to_origin.argtypes = [U, U, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_children_restore_and_clear.argtypes = [U, Attach, Resolve, c.c_void_p]
    n.vertrix_piece_arm_once.argtypes = [c.c_void_p, c.c_size_t, U, c.c_uint16]
    n.vertrix_piece_children_place.argtypes = [U, Resolve, c.c_void_p]
    n.vertrix_piece_init_from_kind.argtypes = [c.c_void_p, c.c_size_t, c.c_uint8]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43a410)
    pool = Pool(cpu, 16)
    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack: None)
    stubs.add(0x4ac8d0)
    native_log = []

    @Attach
    def attach(actor, resource, context):
        native_log.append((0x4ac8d0, actor, resource))

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    piece = pool.handles[0]
    zeros = [0]
    for case in range(args.cases):
        kinds = [rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0x7f, 0x80, 0xff, rng.getrandbits(8)])
                 for _ in range(3)]

        def patch(handle, data):
            if handle == piece:
                for slot in range(0x15c, 0x180, 4):
                    value = rng.choice(pool.handles[1:] + [piece] + [0] * zeros[0])
                    if slot < 0x168 and value == 0:
                        value = pool.handles[1]
                    struct.pack_into('<I', data, slot, value)

        def fresh():
            pool.fill(rng, patch)

        def check(name):
            assert pool.same(), (case, name, pool.diff())
            count(name)

        fresh()
        out = (c.c_uint8 * 3)(0xaa, 0xaa, 0xaa)
        cpu.mem_write(0x80c000, bytes([0xaa] * 3))
        original.call(0x42a980, eax=piece, edx=0x80c000, ebx=0x80c001, ecx=0x80c002)
        assert n.vertrix_piece_child_kinds(piece, pool.resolve, None, out)
        assert bytes(out) == bytes(cpu.mem_read(0x80c000, 3)), case
        check('child_kinds')
        fresh()
        original.call(0x43a5b0, eax=piece, edx=0x80c000, ebx=0x80c001, ecx=0x80c002)
        assert n.vertrix_piece_child_kinds(piece, pool.resolve, None, out)
        assert bytes(out) == bytes(cpu.mem_read(0x80c000, 3)), case
        check('child_kinds_alias')
        fresh()
        stubs.log.clear()
        native_log.clear()
        original.call(0x43a410, eax=piece, edx=kinds[0], ebx=kinds[1], ecx=kinds[2])
        assert n.vertrix_piece_children_setup(piece, K(*kinds), attach, pool.resolve, None)
        assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, case
        check('setup')
        for address, name, native in (
                (0x43a510, 'setup_registers', n.vertrix_piece_children_setup_registers),
                (0x43a560, 'remember_and_setup', n.vertrix_piece_children_remember_and_setup)):
            fresh()
            stubs.log.clear()
            native_log.clear()
            noise = [rng.getrandbits(24) << 8 for _ in range(3)]
            original.call(address, eax=piece, edx=kinds[0] | noise[0], ebx=kinds[1] | noise[1],
                          ecx=kinds[2] | noise[2])
            assert native(piece, K(*kinds), attach, pool.resolve, None)
            assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, (case, name)
            check(name)
        fresh()
        stubs.log.clear()
        native_log.clear()
        original.call(0x43a520, eax=piece)
        assert n.vertrix_piece_children_restore_and_clear(piece, attach, pool.resolve, None)
        assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, case
        check('restore_and_clear')
        fresh()
        if rng.random() < 0.5:
            struct.pack_into('<I', pool.buffers[piece], 0x170, 0)
            cpu.mem_write(piece + 0x170, bytes(4))
        period, word = rng.getrandbits(32), rng.getrandbits(16)
        original_state = bytes(cpu.mem_read(piece, 0x200))
        cpu.mem_write(0x532bbc, struct.pack('<I', 0))
        cpu.mem_write(0x4f7d14, struct.pack('<I', period))
        cpu.mem_write(0x4f7d20, struct.pack('<H', word))
        original.call(0x42b9f0, eax=piece)
        assert n.vertrix_piece_arm_once(pool.buffers[piece], 0x200, period, word)
        check('arm_once')
        fresh()
        stubs.log.clear()
        native_log.clear()
        variant = rng.choice([0, 1, 2, rng.getrandbits(32)])
        original.call(0x42b920, eax=piece, edx=variant)
        assert n.vertrix_piece_set_variant(piece, variant, attach, pool.resolve, None)
        assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, case
        check('set_variant')
        for name in ('snap_to_left', 'snap_to_origin'):
            fresh()
            stubs.log.clear()
            native_log.clear()
            origin = rng.choice([0, rng.getrandbits(32), rng.getrandbits(16)])
            cpu.mem_write(0x4f9098, struct.pack('<I', origin))
            data = bytearray(pool.buffers[piece].raw)
            if rng.random() < 0.4:
                if name == 'snap_to_left':
                    data[0xe:0x10] = data[0xa8:0xaa]
                else:
                    target = (struct.unpack_from('<h', data, 0xaa)[0] - origin) & 0xffff
                    data[0xe:0x10] = struct.pack('<H', target)
                    if target >= 0x8000:
                        data[0xe:0x10] = struct.pack('<H', target)
                cpu.mem_write(piece, bytes(data))
                pool.buffers[piece] = c.create_string_buffer(bytes(data), len(data))
            if name == 'snap_to_left':
                original.call(0x42b950, eax=piece)
                assert n.vertrix_piece_snap_to_left(piece, attach, pool.resolve, None)
            else:
                original.call(0x42b990, eax=piece)
                assert n.vertrix_piece_snap_to_origin(piece, origin, attach, pool.resolve, None)
            assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, (case, name)
            check(name)
        fresh()
        stubs.log.clear()
        native_log.clear()
        flags = [rng.choice([0, 1, 1, 2]) for _ in range(3)]
        original.call(0x43a5f0, eax=piece, edx=kinds[0], ebx=kinds[1], ecx=kinds[2], args=tuple(flags))
        assert n.vertrix_piece_children_setup_selected(piece, K(*kinds), (U * 3)(*flags), attach,
                                                       pool.resolve, None)
        assert [(a, e, d) for a, e, d, *_ in stubs.log] == native_log, case
        check('setup_selected')
        zeros[0] = 3
        fresh()
        zeros[0] = 0
        original.call(0x42a800, eax=piece)
        assert n.vertrix_piece_children_place(piece, pool.resolve, None)
        check('place')
        fresh()
        index = rng.randrange(19)
        original.call(0x425ef0, eax=piece, edx=index)
        assert n.vertrix_piece_init_from_kind(pool.buffers[piece], 0x200, index)
        check('init_from_kind')
    assert not n.vertrix_piece_init_from_kind(pool.buffers[piece], 0x200, 19)
    report = {'status':
            'passed', 'complete_original_executions' : totals,
                                                       'scope'
                : 'Complete 42b950, 42b990, 42a980, 43a5b0, 43a410, 43a510, 43a520, 43a560, 43a5f0, 42a800, 42b920, 42b9f0 and 425ef0 execute in the ' 'original (resource attach 4ac8d0 stubbed and logged); results, attach ' 'events and every pool object compare, including children that alias the ' 'piece or each other.'
            }
            (args.build_dir / 'piece-children-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()

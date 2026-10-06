"""Compare complete original particle spawn routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import Pool, Resolve, Stubs, build
U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Lookup = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p)
SCREEN = 0x5b9c8e
SCRATCH = {'spread': 0x540fd4, 'burst': 0x541014, 'drift': 0x54101c}


class Scratch(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16), ('half_width', c.c_uint16), ('half_height', c.c_uint16)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('lookup', Lookup), ('draw', Draw), ('context', c.c_void_p)]


def image(bank, index):
    return (bank * 31 + index * 17 + 7) & 0xffffffff


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'particle-spawn', ['particle_spawn.c', 'actor_storage.c', 'actor_fields.c', 'actor_chain_visit.c'])
    S = c.POINTER(Services)
    P = c.POINTER(Scratch)
    n.vertrix_spawn_spread.argtypes = [U, U, c.c_uint16, c.c_uint16, P, S]
    n.vertrix_spawn_burst.argtypes = [U, c.c_uint16, c.c_uint16, P, S]
    n.vertrix_spawn_drift.argtypes = [U, c.c_uint16, c.c_uint16, P, S]
    n.vertrix_spawn_place.argtypes = [U, S]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43dea0)
    pool = Pool(cpu, 8, 0x1000)
    draws = []
    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4877f0:
            return image(eax, edx)
        draws.append(rng.randrange(edx & 0xffff))
        return draws[- 1]
    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    stubs.add(0x4877f0)
    replay = iter([])
    @ Draw
    def draw(divisor, context):
        return next(replay)
    @ Lookup
    def lookup(bank, index, context):
        return image(bank, index)
    services = Services(pool.resolve, lookup, draw, None)
    totals = {}
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    handles = pool.handles
    for case in range(args.cases):
        width = rng.choice([1, 2, 3, 100, 640, 0x7fff, 0xffff, rng.randrange(1, 800)])
        height = rng.choice([1, 2, 3, 100, 480, 0x7fff, 0xffff, rng.randrange(1, 800)])
        cpu.mem_write(SCREEN, struct.pack('<HH', width, height))
        def patch(handle, data):
            struct.pack_into('<I', data, 0x94c, rng.choice([0, 1, 1, 2]))
        def fresh():
            pool.fill(rng, patch)
        def check(name):
            assert pool.same(), (case, name, pool.diff())
            count(name)
        def run(name, address, call, scratch_address, ** registers):
            nonlocal replay
            fresh()
            cpu.mem_write(scratch_address, bytes(8))
            draws.clear()
            stubs.log.clear()
            original.call(address, ** registers)
            replay = iter(list(draws))
            scratch = Scratch()
            call(scratch)
            assert next(replay, None) is None, (case, name)
            words = struct.unpack('<4H', cpu.mem_read(scratch_address, 8))
            return scratch, words
        scene, child = rng.choice(handles), rng.choice(handles)
        scratch, words = run('spread', 0x43dea0, lambda s: n.vertrix_spawn_spread(scene, child, width, height, c.byref(s), c.byref(services)), SCRATCH['spread'], eax=scene, edx=child)
        assert (scratch.width, scratch.height, scratch.half_width, scratch.half_height) == words, case
        check('spread')
        child = rng.choice(handles)
        scratch, words = run('burst', 0x43e740, lambda s: n.vertrix_spawn_burst(child, width, height, c.byref(s), c.byref(services)), SCRATCH['burst'], edx=child)
        assert (scratch.width, scratch.height, scratch.half_width, scratch.half_height) == words, case
        check('burst')
        scratch, words = run('drift', 0x43e840, lambda s: n.vertrix_spawn_drift(child, width, height, c.byref(s), c.byref(services)), SCRATCH['drift'], edx=child)
        assert (scratch.width, scratch.height) == words[: 2], case
        check('drift')
# 43e920 needs nonzero draw ranges
        fresh()
        raw = bytearray(pool.buffers[child].raw)
        struct.pack_into('<I', raw, 0xb8, rng.choice([1, 2, 2, 0, 3]))
        struct.pack_into('<H', raw, 8, rng.randrange(1, 900))
        struct.pack_into('<H', raw, 0xa, rng.randrange(0x137, 0x500))
        cpu.mem_write(child, bytes(raw))
        c.memmove(pool.buffers[child], bytes(raw), len(raw))
        draws.clear()
        original.call(0x43e920, eax=child)
        replay = iter(list(draws))
        assert n.vertrix_spawn_place(child, c.byref(services))
        assert next(replay, None) is None, case
        check('place')
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 43dea0, 43e740, 43e840 and 43e920 execute in the original (the ' 'random draw 4826c0 and image lookup 4877f0 are stubbed; attach, frame, ' 'bind and timer setters run for real); the scratch globals, every pool ' 'object and the replayed draws compare.'}
    (args.build_dir / 'particle-spawn-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

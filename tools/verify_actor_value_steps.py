"""Compare complete original actor value-step routines with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import Stubs, build

ACTOR, SIZE, RESOURCES = 0x801000, 0x200, 0x804000
U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_void_p, c.c_uint16)
Count = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-value-steps', ['actor_value_steps.c', 'actor_storage.c'])
    n.vertrix_step_toward.argtypes = [c.c_int32] * 4
    n.vertrix_step_toward.restype = c.c_int32
    n.vertrix_actor_progress_quotient.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(U)]
    n.vertrix_actor_consume_progress.argtypes = [c.c_void_p, c.c_size_t]
    for name in ('randomize_period', 'randomize_d0'):
        getattr(n, 'vertrix_actor_' + name).argtypes = [c.c_void_p, c.c_size_t, Draw, c.c_void_p]
    for name in ('frame_is_count', 'frame_is_last'):
        getattr(n, 'vertrix_actor_' + name).argtypes = [c.c_void_p, c.c_size_t, Count, c.c_void_p,
                                                        c.POINTER(U)]
    n.vertrix_actor_step_word.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, c.POINTER(U)]
    n.vertrix_object_step_dword.argtypes = n.vertrix_actor_step_word.argtypes
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac980)
    draws = []

    def handler(address, eax, edx, ebx, ecx, stack):
        value = rng.getrandbits(32)
        draws.append((edx, value))
        return value

    stubs = Stubs(cpu, handler)
    stubs.add(0x4826c0)
    replay = iter([])
    seen = []

    @Draw
    def draw(context, divisor):
        seen.append(divisor)
        return next(replay) & 0xffff

    handles = [RESOURCES + 0x20 * i for i in range(8)]
    counts = {}

    @Count
    def frame_count(context, handle):
        return counts[handle]

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def interesting():
        return rng.choice([0, 1, 2, 0x7fffffff, 0x80000000, 0xffffffff, rng.getrandbits(32),
                           rng.randrange(0, 20), (-rng.randrange(1, 20)) & 0xffffffff])

    for case in range(args.cases):
        raw = bytearray(rng.randbytes(SIZE))
        for off in (0xb8, 0xcc, 0xd0, 0x64, 0x68, 0x6c, 0xc4, 0xd4):
            struct.pack_into('<I', raw, off, interesting())
        struct.pack_into('<I', raw, 0xb0, rng.choice(handles))
        for off in (0x1e, 0x20, 0x22):
            struct.pack_into('<h', raw, off, rng.choice([0, 1, -1, 100, -100, 32767, -32768,
                                                          rng.randrange(-300, 300)]))
        for off in (0xc8, 0xd8):
            struct.pack_into('<H', raw, off, rng.choice([1, 2, 7, 100, 65535, rng.getrandbits(16)]))
        if rng.random() < 0.4:
            struct.pack_into('<h', raw, 0x1e, rng.randrange(-5, 5))
            struct.pack_into('<h', raw, 0x20, rng.randrange(-5, 5))
        if rng.random() < 0.4:
            struct.pack_into('<i', raw, 0x64, rng.randrange(-5, 5))
            struct.pack_into('<i', raw, 0x68, rng.randrange(-5, 5))
        for handle in handles:
            counts[handle] = rng.choice([0, 1, 2, 3, 0xffffffff, rng.getrandbits(32)])
            cpu.mem_write(handle, struct.pack('<II', rng.getrandbits(32), counts[handle]))
        if rng.random() < 0.3:
            struct.pack_into('<I', raw, 0xb8, (counts[struct.unpack_from('<I', raw, 0xb0)[0]] - rng.choice([0, 1])) & 0xffffffff)

        def run(address, **registers):
            cpu.mem_write(ACTOR, bytes(raw))
            result = original.call(address, eax=ACTOR, **registers)
            return result, bytes(cpu.mem_read(ACTOR, SIZE))

        def fresh():
            return c.create_string_buffer(bytes(raw), SIZE)

# 4ac980 : pure arithmetic, with the multiplier on the stack
        current, target, step, mult = (interesting() for _ in range(4))
        result = original.call(0x4ac980, ebx=current, ecx=target, edx=step, args=(mult,))
        signed = lambda v: v - (1 << 32) if v & 0x80000000 else v
        assert n.vertrix_step_toward(signed(current), signed(target), signed(step),
                                     signed(mult)) & 0xffffffff == result, case
        count('step_toward')
# 4ac3b0
        result, _ = run(0x4ac3b0)
        out = U()
        assert n.vertrix_actor_progress_quotient(fresh(), SIZE, c.byref(out)) and out.value == result, case
        count('progress_quotient')
# 4ac420 : no return contract(falls off with residue in eax), so only
#the whole object compares.
        _, after = run(0x4ac420)
        buffer = fresh()
        assert n.vertrix_actor_consume_progress(buffer, SIZE)
        assert buffer.raw == after, case
        count('consume_progress')
# 4ac7e0 / 4ac810 with the 4826c0 draw replayed
        for address, name, span in ((0x4ac7e0, 'randomize_period', 0xc8), (0x4ac810, 'randomize_d0', 0xd8)):
            draws.clear()
            run_result, after = run(address)
            assert len(draws) == 1 and draws[0][0] == struct.unpack_from('<H', raw, span)[0], case
            replay = iter([draws[0][1]])
            seen.clear()
            buffer = fresh()
            assert getattr(n, 'vertrix_actor_' + name)(buffer, SIZE, draw, None)
            assert buffer.raw == after and seen == [draws[0][0]], (name, case)
            count(name)
# 4ac760 / 4ac780(original 487860 runs unstubbed)
        for address, name in ((0x4ac760, 'frame_is_count'), (0x4ac780, 'frame_is_last')):
            result, _ = run(address)
            out = U()
            assert getattr(n, 'vertrix_actor_' + name)(fresh(), SIZE, frame_count, None, c.byref(out))
            assert out.value == result & 0xff, (name, case)
            count(name)
# 4acb00 / 4ad750
        for address, name in ((0x4acb00, 'step_word'), (0x4ad750, 'step_dword')):
            mult = interesting()
            result, after = run(address, edx=mult)
            buffer = fresh()
            out = U()
            native = n.vertrix_actor_step_word if name == 'step_word' else n.vertrix_object_step_dword
            assert native(buffer, SIZE, signed(mult), c.byref(out))
            assert buffer.raw == after and out.value == result & 0xff, (name, case)
            count(name)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ac980, 4ac3b0, 4ac420, 4ac7e0, 4ac810, 4ac760, 4ac780, 4acb00 and '
                       '4ad750 execute in the original (4826c0 draws stubbed and replayed; 487860 '
                       'unstubbed); whole object, results and draw divisors compare (4ac420 has no '
                       'return contract, so only its storage compares).'}
    (args.build_dir / 'actor-value-steps-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

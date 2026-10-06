""
    "Compare complete original actor clipping gate 4ae3e0 with the native recovery."
    "" import argparse,
    ctypes as c, json, random, struct,
    subprocess from pathlib import Path from original import Original from unicorn import UcError

        ACTOR,
    OBJECT, IMAGE, SURFACE,
    CELLS = 0x801000, 0x802000, 0x803000, 0x803100, 0x803200 SURF_PIXELS, INDEX_DATA, SHIFT_DATA,
    MASK_DATA, IMAGE_PIXELS = 0x806000, 0x808000, 0x80a000, 0x80c000, 0x80e000 GLOBALS, SIZE,
    POINTER = 0x5bb680, 0x9a0,
    0x544070 Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)

                        def
                        main()
    : parser = argparse.ArgumentParser(description = __doc__)
                   parser.add_argument('executable', type = Path)
                       parser.add_argument('--build-dir', type = Path, required = True)
                           parser.add_argument('--cases', type = int, default = 20000) args =
        parser.parse_args() build =
            args.build_dir.resolve() build.mkdir(parents = True, exist_ok = True) source =
                Path(__file__).resolve().parents[1] / 'source' library =
                    build / 'actor-gate.dylib' subprocess.run(
                                [
                                    'cc',
                                    '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', str(source / 'actor_gate.c'),
                                    str(source / 'actor_storage.c'), '-o', str(library)
                                ],
                                check = True) n =
                        c.CDLL(str(library)) n.vertrix_actor_gate.argtypes =
                            [
                                c.c_void_p, c.c_void_p, c.c_size_t, c.c_uint32, Read, c.c_void_p,
                                c.POINTER(c.c_uint32)
                            ] original = Original(args.executable) cpu =
                                original.cpu

                                @Read def read(address, width, out, context)
    :
try : out
    [0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little') return 1 except UcError
        : return 0

          rng = random.Random(0x4ae3e0) totals = {
        'cases' : 0,
        'returned_zero' : 0,
        'returned_one' : 0,
        'indexed' : 0,
        'mask_rows' : 0,
        'clipped' : 0,
        'faults_rejected' : 0
    } modes,
    kinds, depths = {}, {},
    {
    }

    def word(lo, hi):
        return rng.randint(lo, hi) & 0xffff

    def setup(mode):
        actor = bytearray(rng.randbytes(0x200))
        struct.pack_into('<I', actor, 0x13c, rng.choice([0, 0, 1]))
        struct.pack_into('<I', actor, 0xb4, IMAGE if rng.random() < 0.95 else 0)
        for offset, lo, hi in ((0xe, -4, 24), (0x16, -4, 24), (0x1e, -3, 6), (0xa8, -5, 6),
                               (0xaa, 20, 60), (0xac, -5, 6), (0xae, 20, 60)):
            struct.pack_into('<H', actor, offset, word(lo, hi))
        actor[0x8e] = rng.choice([0, 1, 2, 3, 3, 4])
        actor[0x4e] = rng.choice([0x64, 0, rng.randrange(256)])
        actor[0x91] = rng.getrandbits(1)
        actor[0x92] = rng.getrandbits(1)
        actor[0x44] = rng.choice([0x10, 0x10, 0, 1, 2, 3, rng.randrange(0x20)])
        actor[0x8f] = rng.choice([0, 0, 0, 1])
        obj = bytearray(rng.randbytes(0x300))
        struct.pack_into('<H', obj, 0x208, rng.randint(1, 30))
        struct.pack_into('<H', obj, 0x20c, rng.randint(1, 30))
        for offset in (0x214, 0x216, 0x226):
            struct.pack_into('<H', obj, offset, rng.randint(0, 4))
        obj[0x220], obj[0x222] = rng.getrandbits(1), rng.getrandbits(1)
        for offset, cell in ((0x270, 0), (0x26c, 0x10), (0x274, 0x20)):
            struct.pack_into('<I', obj, offset, CELLS + cell if not (offset == 0x274 and rng.random() < 0.15)
                             else 0)
        image = bytearray(rng.randbytes(0x40))
        struct.pack_into('<H', image, 4, rng.randint(1, 20))
        struct.pack_into('<H', image, 8, rng.randint(1, 20))
        struct.pack_into('<H', image, 0xc, rng.randint(0, 3))
        struct.pack_into('<H', image, 0x10, rng.randint(0, 3))
        struct.pack_into('<I', image, 0, IMAGE_PIXELS)
        surface = bytearray(rng.randbytes(0x40))
        struct.pack_into('<I', surface, 0, SURF_PIXELS + 0x1000)
        struct.pack_into('<H', surface, 4, rng.randint(24, 64))
        struct.pack_into('<H', surface, 8, rng.randint(24, 64))
        surface[0xc] = rng.choice([1, 2, 4, 4, 3])
        surface[0xd] = rng.choice([0, 1, 2, 2, 2, 2, 2, 3])
        struct.pack_into('<I', surface, 0x14, rng.randint(8, 200))
        glob = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<I', glob, 0x5bc010 - GLOBALS, SURFACE)
        for address, data in ((ACTOR, actor), (OBJECT, obj), (IMAGE, image), (SURFACE, surface),
                              (GLOBALS, glob)):
            cpu.mem_write(address, bytes(data))
        cpu.mem_write(POINTER, struct.pack('<I', OBJECT))
        for cell, data in ((0, INDEX_DATA), (0x10, SHIFT_DATA), (0x20, MASK_DATA)):
            cpu.mem_write(CELLS + cell, struct.pack('<I', data))
        for address in (INDEX_DATA, SHIFT_DATA, MASK_DATA, IMAGE_PIXELS):
            cpu.mem_write(address, rng.randbytes(0x1800) if address != MASK_DATA else
                          bytes(rng.choice([0, 0, 1, 2, 3, 7]) for _ in range(0x1800)))
        return actor, glob

    for case in range(args.cases):
    mode = rng.choice([ 0, 0, 1, 2 ]) actor, glob = setup(mode) before_actor,
    before_glob = bytes(actor),
    bytes(glob) g = c.create_string_buffer(before_glob, SIZE) a =
        c.create_string_buffer(before_actor, len(before_actor)) out = c.c_uint32(0xdead)
    try : result = original.call(0x4ae3e0, eax=ACTOR, edx=mode)
            faulted = False
        except UcError:
            faulted = True
        ok = n.vertrix_actor_gate(g, a, len(before_actor), mode, read, None, c.byref(out))
        if faulted:
            assert not ok and g.raw == before_glob and a.raw == before_actor, case
            totals['faults_rejected'] += 1
            continue
        assert ok, (case, 'native rejected a completed original run')
        assert out.value == result & 0xffffffff, (case, out.value, result)
        assert g.raw == bytes(cpu.mem_read(GLOBALS, SIZE)), (case, [
            hex(GLOBALS + i) for i in range(SIZE) if g.raw[i] != cpu.mem_read(GLOBALS + i, 1)[0]][:12])
        assert a.raw == bytes(cpu.mem_read(ACTOR, len(before_actor))), case
        totals['cases'] += 1
        totals['returned_one' if out.value else 'returned_zero'] += 1
        totals['indexed'] += g.raw[0x5bb694 - GLOBALS] == 1
        totals['mask_rows'] += g.raw[0x5bbff0 - GLOBALS] == 1
        totals['clipped'] += g.raw[0x5bc014 - GLOBALS] == 1
        modes[mode] = modes.get(mode, 0) + 1
        kinds[actor[0x8e]] = kinds.get(actor[0x8e], 0) + 1
        depths[g.raw[0x5bb732 - GLOBALS]] = depths.get(g.raw[0x5bb732 - GLOBALS], 0) + 1
    report = {'status':
        'passed', 'complete_original_cases' : totals,
                                              'modes' : modes,
                                                        'clip_kinds' : kinds,
                                                                       'surface_depths' : depths,
                                                                                          'scope'
            : 'Complete 4ae3e0 executes in the original with real 4ae110, 478eb0 and fill 4eb5c0. ' 'Whole 5bb680..5bc01f globals, the eax result and whole actor storage compare. ' 'Memory outside the globals is read through a callback over the oracle memory; ' 'original faults are rejected natively with storage preserved.'
    }
    (build / 'actor-gate-verification.json')
            .write_text(json.dumps(report, indent = 2) + '\n') print(json.dumps(report, indent = 2))

                if __name__ == '__main__' : main()

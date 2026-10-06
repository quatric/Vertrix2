"""Compare complete original chain visit routines 4ac8a0 and 4af8c0."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

ACTOR, LOOKUP, GATE, PAINT, GLOBAL = 0x801000, 0x4877f0, 0x4ae3e0, 0x4af560, 0x5bc010
Lookup = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p)
Gate = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint32, c.c_void_p)
Paint = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'actor-chain-visit.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'actor_chain_visit.c'), str(source / 'actor_storage.c'),
                    '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    U, S, SZ = c.c_uint32, c.c_void_p, c.c_size_t
    n.vertrix_actor_lookup_image.argtypes = [S, SZ, Lookup, S]
    n.vertrix_actor_chain_paint.argtypes = [U, S, SZ, U, c.POINTER(U), Gate, Paint, S]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac8a0)
    events, native = [], []
    gate_result = [0]
    cpu.mem_write(LOOKUP, b'\xb8' + struct.pack('<I', 0) + b'\xc3')
    cpu.mem_write(GATE, b'\xa1' + struct.pack('<I', 0x800ff0) + b'\xc3')
    cpu.mem_write(PAINT, b'\xc3')
    for a, tag in ((LOOKUP, 'lookup'), (GATE, 'gate'), (PAINT, 'paint')):
        cpu.hook_add(UC_HOOK_CODE, lambda cpu, ad, s, x, t=tag: events.append(
            (t, cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX) if t != 'paint' else 0)), begin=a, end=a)

    @Lookup
    def lookup(bank, index, ctx):
        native.append(('lookup', bank, index))
        return 0

    @Gate
    def gate(actor, value, ctx):
        native.append(('gate', actor, value))
        return gate_result[0]

    @Paint
    def paint(actor, ctx):
        native.append(('paint', actor, 0))

    totals = {'lookup': 0, 'lookup_called': 0, 'paint': 0, 'painted': 0}
    for case in range(4096):
raw = bytearray(rng.randbytes(0x200)) if rng.random() < 0.3
    : struct
          .pack_into('<I', raw, 0xb0, 0)
#lookup stub returns 0, so make b4 distinguishable beforehand
              cpu.mem_write(ACTOR, bytes(raw))
                  actor = c.create_string_buffer(bytes(raw), len(raw)) events.clear();
native.clear() original.call(0x4ac8a0, eax = ACTOR) assert n
            .vertrix_actor_lookup_image(actor, len(actor), lookup, None) assert actor.raw
        == bytes(cpu.mem_read(ACTOR, len(actor))) and
    events == native,
    case totals['lookup'] += 1 totals['lookup_called'] += bool(events) before =
        actor.raw assert not n.vertrix_actor_lookup_image(actor, 0xb4, lookup, None) and actor.raw
        == before result = rng.getrandbits(1) gate_result[0] =
            result cpu.mem_write(0x800ff0, struct.pack('<I', result)) cpu.mem_write(
                ACTOR, bytes(raw)) arg = rng.getrandbits(32) events.clear();
    native.clear() original.call(0x4af8c0, eax = ACTOR, edx = arg) g =
        U(0) assert n
            .vertrix_actor_chain_paint(ACTOR, actor, len(actor), arg, c.byref(g), gate, paint,
                                       None) assert g.value
        == struct.unpack('<I', bytes(cpu.mem_read(GLOBAL, 4)))[0] == arg assert events == native,
                                                                       (case, events, native)assert
                                                                           bytes(cpu.mem_read(
                                                                               ACTOR,
                                                                               len(actor))) == raw
                                                                           totals['paint'] +=
                                                                       1 totals['painted'] +=
                                                                       result assert not n
                                                                           .vertrix_actor_chain_paint(
                                                                               ACTOR, actor, 0x100,
                                                                               arg, c.byref(g),
                                                                               gate, paint,
                                                                               None) report = {
                                                                           'status':
'passed', 'complete_original_cases' : totals,
                                      'scope'
    : 'Complete 4ac8a0 and 4af8c0 execute in the original. 4877f0, 4ae3e0 and 4af560 are ' 'recorded stubs; call order and registers, actor storage and global 5bc010 match.'
}
(build / 'actor-chain-visit-verification.json')
        .write_text(json.dumps(report, indent = 2) + '\n') print(json.dumps(report, indent = 2))

            if __name__ == '__main__' : main()

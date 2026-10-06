"""Compare complete original one-field actor setters with the native recovery."""
import argparse, ctypes as c, json, random, subprocess
from pathlib import Path
from original import Original

ACTOR = 0x801000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'actor-fields.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'actor_fields.c'), str(source / 'actor_storage.c'), '-o', str(library)],
                   check=True)
    n = c.CDLL(str(library))
    S, SZ, U = c.c_void_p, c.c_size_t, c.c_uint32
    n.vertrix_actor_clear_counter.argtypes = [S, SZ]
    n.vertrix_actor_clear_cc.argtypes = [S, SZ]
    for name in ('set_period_steps', 'set_period', 'set_handler', 'set_d0', 'set_frame_index'):
        getattr(n, 'vertrix_actor_' + name).argtypes = [S, SZ, U]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ac8f0)
    routines = ((0x4ac510, 'clear_counter'), (0x4ac7b0, 'set_period_steps'), (0x4ac7d0, 'set_period'),
                (0x4ac8f0, 'set_handler'), (0x4ac380, 'clear_cc'), (0x4ac490, 'set_d0'),
                (0x4ac710, 'set_frame_index'))
    totals = {name: 0 for _, name in routines}
    for case in range(4096):
        for
        address,
            name in routines
            : raw = rng.randbytes(0x200)
                        value = rng.getrandbits(32) cpu.mem_write(ACTOR, raw)
                                    actor = c.create_string_buffer(raw, len(raw))
                                                original.call(address, eax = ACTOR, edx = value)
                                                    native = getattr(n, 'vertrix_actor_' + name)
                  ok = native(actor, len(raw)) if name
                           in('clear_counter', 'clear_cc') else native(actor, len(raw), value)
                               assert ok and actor.raw == bytes(cpu.mem_read(ACTOR, len(raw))),
              (case, name)before = actor.raw end = {
                  'clear_counter' : 0xc0,
                  'set_period_steps' : 0xc4,
                  'set_period' : 0xc4,
                  'set_handler' : 0x158,
                  'clear_cc' : 0xd0,
                  'set_d0' : 0xd4,
                  'set_frame_index' : 0xbc
              }[name] short = end -
                              1 rejected = native(actor, short) if name
                                           in('clear_counter', 'clear_cc') else native(actor, short,
                                                                                       value) assert
                                           not rejected
                                           and actor.raw == before,
              (case, name)totals[name] += 1 report = {
                  'status' : 'passed',
                  'complete_original_executions' : totals,
                  'scope' :
                      'Complete 4ac510, 4ac7b0, 4ac7d0, 4ac8f0, 4ac380, 4ac490 and 4ac710 execute in the original; whole actor ' 'storage compares for random contents and parameters.'
              }(build / 'actor-fields-verification.json')
                                                         .write_text(json.dumps(report,
                                                                                indent = 2) +
                                                                     '\n')
                                                             print(json.dumps(report, indent = 2))

                                                                 if __name__
                                                     == '__main__' : main()

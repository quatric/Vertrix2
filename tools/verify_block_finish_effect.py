""
    "Compare three original animated finish handlers without hooks."
    "" import argparse,
    ctypes as c, json, random, struct,
    subprocess from pathlib import Path from original import Original, BOARD,
    MASK from verify_animation import Animation from verify_timer import Timer

    class Combined(c.Structure)
    : _fields_ =
          [
              ('timer', Timer), ('effect', c.c_int16), ('effect_target', c.c_int16),
              ('effect_step', c.c_int16), ('amount', c.c_uint8), ('amount_target', c.c_uint8),
              ('amount_step', c.c_int16), ('field_93', c.c_uint8), ('field_95', c.c_uint8),
              ('handler', c.c_uint32)
          ]

      class Finish(c.Structure)
    : _fields_ = [ ('transition', Combined), ('state', c.c_uint8) ]

      def main()
    : p = argparse.ArgumentParser(description = __doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
lib = a.build_dir.resolve() / 'block.dylib';subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/name) for name in ('block_finish_effect.c','block_update.c','animation.c','timer.c','byte_transition.c','word_transition.c')],'-o',str(lib)],check=True)
    n=c.CDLL(str(lib));
n.vertrix_block_finish_effect_update.argtypes = [
    c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32, c.POINTER(c.c_uint32),
    c.POINTER(Finish)
] o = Original(a.executable);
rng = random.Random(0x44c860);linked=0
    def node(address,count,kind,frames=0,children=0,indices=0):o.cpu.mem_write(address,struct.pack('<6I',frames,count,0,children,indices,kind))
    for case in range(16384):
count = rng.randrange(1, 65);ids=[rng.getrandbits(32) for _ in range(64)];mapping=[rng.randrange(64) for _ in range(count)];second=[rng.randrange(64) for _ in range(64)];
depth = case % 3 o.cpu.mem_write(0x803000, struct.pack('<64I', *ids));
    node(0x802000, 64, 0, frames = 0x803000) if depth:
o.cpu.mem_write(0x803400,
                struct.pack('<' + 'I' * count, *([0x802100 if depth == 2 else 0x802000] * count)));
o.cpu.mem_write(0x803800, struct.pack('<' + 'I' * count, *mapping));
node(MASK, count, 1, children = 0x803400, indices = 0x803800) if depth == 2
    : o.cpu.mem_write(0x803a00, struct.pack('<64I', *([0x802000] * 64)));
o.cpu.mem_write(0x803c00, struct.pack('<64I', *second));node(0x802100,64,1,children=0x803a00,indices=0x803c00)
            resolved=[ids[second[index] if depth==2 else index] for index in mapping];
linked += 1 else : node(MASK, count, rng.choice([ 0, 2, 16, 0xffffffff ]), frames = 0x803000);
resolved = ids[:count] period = rng.randrange(65);
counter = rng.randrange(129) * (period or 1);
elapsed = rng.randrange(129) * (period or 1);
frame = rng.randrange(count);
animation = Animation(Timer(counter, period), frame, count);
frames = (c.c_uint32 * count)(*resolved);
descriptor = c.c_uint32(rng.getrandbits(32));
raw = bytearray(rng.randbytes(0x160)) combined =
    Combined(Timer(rng.getrandbits(32), rng.choice([ 0, 1, 100, 0xffffffff ])),
             rng.randrange(-32768, 32768), rng.randrange(-32768, 32768),
             rng.randrange(-32768, 32768), rng.randrange(256), rng.randrange(256),
             rng.randrange(-32768, 32768), rng.randrange(256), rng.randrange(256),
             [ 0x450330, 0x4503b0, 0x450450, 0x4504e0, 0x450550, 0x4505c0, 0x450630,
               0x4506a0 ][case % 8]) if case %
        8 ==
    0:
combined.effect = 200 if combined.handler == 0x450330 else 0;
combined.amount = 0 finished = Finish(combined, rng.randrange(256));
raw[0x15d] = finished.state;
struct.pack_into('<2I', raw, 0xbc, combined.timer.counter, combined.timer.period);
struct.pack_into('<3hBBh', raw, 0x48, combined.effect, combined.effect_target, combined.effect_step,
                 combined.amount, combined.amount_target, combined.amount_step);
raw[0x93] = combined.field_93;
raw[0x95] = combined.field_95;
struct.pack_into('<I', raw, 0x154, combined.handler);
struct.pack_into('<3I', raw, 0xb0, MASK, descriptor.value, frame);
struct.pack_into('<2I', raw, 0xcc, counter, period);
o.cpu.mem_write(BOARD, bytes(raw));
o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed));
o.call(combined.handler, eax = BOARD) assert n.vertrix_block_finish_effect_update(
    c.byref(animation), frames, count, elapsed, c.byref(descriptor),
    c.byref(finished)) combined = finished.transition expected = bytearray(raw);
expected[0x15d] = finished.state;
struct.pack_into('<I', expected, 0xbc, combined.timer.counter);
struct.pack_into('<3hBBh', expected, 0x48, combined.effect, combined.effect_target,
                 combined.effect_step, combined.amount, combined.amount_target,
                 combined.amount_step);
expected[0x93] = combined.field_93;
expected[0x95] = combined.field_95;
struct.pack_into('<I', expected, 0x154, combined.handler);
struct.pack_into('<I', expected, 0xb4, descriptor.value);
struct.pack_into('<I', expected, 0xb8, animation.frame);
struct.pack_into('<I', expected, 0xcc, animation.timer.counter) assert
    bytes(expected) == bytes(o.cpu.mem_read(BOARD, len(raw))),
    (case,
     'whole normal block')prior = bytes(animation),
     descriptor.value,
     bytes(finished) assert
         not n.vertrix_block_finish_effect_update(c.byref(animation), frames, count - 1, 16,
                                                  c.byref(descriptor), c.byref(finished)) and
         (bytes(animation), descriptor.value,
          bytes(finished)) == prior assert
                              not n.vertrix_block_finish_effect_update(None, frames, count, 16,
                                                                       c.byref(descriptor),
                                                                       c.byref(finished)) report =
         {
             'status' : 'passed',
             'cases' : 16384,
             'linked_resources' : linked,
             'scope' :
                 'Complete original450330/4503b0/450450/4504e0/450550/4505c0/450630/4506a0 without hooks. Whole objects match animation, timers, transitions, flags, handler clearing, state15d completion and direct/linked resource binding. Native receives resolved frame order; full actor/application integration remains unfinished.'
         }(a.build_dir / 'block-finish-effect-verification.json')
             .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()

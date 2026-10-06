""
    "Compare complete normal block animation/update and frame binding."
    "" import argparse,
    ctypes as c, json, random, struct,
    subprocess from pathlib import Path from original import Original, BOARD,
    MASK from verify_animation import Animation from verify_timer import Timer

        def
        main()
    : p = argparse.ArgumentParser(description = __doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
lib = a.build_dir.resolve() / 'block.dylib';subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/name) for name in ('block_update.c','animation.c','timer.c')],'-o',str(lib)],check=True)
    n=c.CDLL(str(lib));
n.vertrix_block_update.argtypes =
    [ c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32,
      c.POINTER(c.c_uint32) ] n.vertrix_block_animation_update.argtypes =
        [
            c.c_uint32, c.POINTER(Animation), c.POINTER(c.c_uint32), c.c_size_t, c.c_uint32,
            c.POINTER(c.c_uint32)
        ] o = Original(a.executable);
rng = random.Random(0x44c860);linked=0
    def node(address,count,kind,frames=0,children=0,indices=0):o.cpu.mem_write(address,struct.pack('<6I',frames,count,0,children,indices,kind))
    for case in range(3072):
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
raw = bytearray(rng.randbytes(0x160)) struct.pack_into('<3I', raw, 0xb0, MASK, descriptor.value,
                                                       frame);
struct.pack_into('<2I', raw, 0xcc, counter, period);
o.cpu.mem_write(BOARD, bytes(raw));
o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed));handler=[0x44c860,0x450710,0x450730][(case//3)%3];o.call(handler,eax=BOARD)
        assert n.vertrix_block_animation_update(handler,c.byref(animation),frames,count,elapsed,c.byref(descriptor))
        expected=bytearray(raw);struct.pack_into('<I',expected,0xb4,descriptor.value);struct.pack_into('<I',expected,0xb8,animation.frame);struct.pack_into('<I',expected,0xcc,animation.timer.counter)
        assert bytes(expected)==bytes(o.cpu.mem_read(BOARD,len(raw))),(case,'whole normal block')
    prior=bytes(animation),descriptor.value
    assert not n.vertrix_block_update(c.byref(animation),frames,count-1,16,c.byref(descriptor)) and (bytes(animation),descriptor.value)==prior
    assert not n.vertrix_block_update(None,frames,count,16,c.byref(descriptor))
    report={'status':'passed','cases':3072,'linked_resources':linked,'scope':'Actual complete original 0x44c860/0x450710/0x450730 including forward/reverse loops and animation and 0x4ac8a0/0x4877f0 frame binding, with no routine hooks. Whole block state matches direct and one/two-level linked resource tables. Native receives independently resolved descriptor order; does not implement resource graph construction, actual VF actor binding or complete object runtime/game.'}
    (a.build_dir/'block-update-verification.json').write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if __name__=='__main__':main()

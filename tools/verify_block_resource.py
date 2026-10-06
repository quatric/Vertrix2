""
    "Compare complete normal block animation/update and frame binding."
    "" import argparse,
    ctypes as c, json, random, struct,
    subprocess from pathlib import Path from original import Original, BOARD,
    MASK from verify_animation import Animation from verify_timer import Timer from
        verify_frame_resource import Resource

            def
            main()
    : p = argparse.ArgumentParser(description = __doc__);
p.add_argument('executable', type = Path);
p.add_argument('--build-dir', type = Path, required = True);
a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';
lib = a.build_dir.resolve() / 'block.dylib';subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/name) for name in ('block_resource.c','frame_resource.c','animation.c','timer.c')],'-o',str(lib)],check=True)
    n=c.CDLL(str(lib));
n.vertrix_block_resource_update.argtypes =
    [ c.POINTER(Animation), c.POINTER(Resource), c.c_size_t, c.c_uint32,
      c.POINTER(c.c_uint32) ] n.vertrix_block_resource_attach.argtypes =
        [ c.POINTER(Animation), c.POINTER(c.POINTER(Resource)),
          c.POINTER(Resource) ] n.vertrix_block_resource_bind.argtypes =
            [ c.POINTER(Animation), c.POINTER(Resource), c.c_size_t,
              c.POINTER(c.c_uint32) ] n.vertrix_block_resource_last.argtypes =
                [ c.POINTER(Animation), c.POINTER(Resource) ] o = Original(a.executable);
rng = random.Random(0x44c860);linked=0
    def node(address,count,kind,frames=0,children=0,indices=0):o.cpu.mem_write(address,struct.pack('<6I',frames,count,0,children,indices,kind))
    for case in range(1024):
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
raw = bytearray(rng.randbytes(0x160)) leaf_frames = (c.c_uint32 * 64)(*ids);
leaf = Resource(0, 64, leaf_frames, None, None) intermediate_indices =
    (c.c_uint32 * 64)(*second)intermediate_children =
        (c.POINTER(Resource) * 64)(*([c.pointer(leaf)] * 64)) intermediate =
            Resource(1, 64, None, intermediate_children, intermediate_indices) top_indices =
                (c.c_uint32 * count)(*mapping)top_children = (c.POINTER(Resource) * count)(
                    *([c.pointer(intermediate if depth == 2 else leaf)] * count)) resource =
                    Resource(1, count, None, top_children, top_indices) if depth else Resource(
                        0, count, leaf_frames, None,
                        None) struct.pack_into('<3I', raw, 0xb0, MASK, descriptor.value, frame);
struct.pack_into('<2I', raw, 0xcc, counter, period);
o.cpu.mem_write(BOARD, bytes(raw));
o.cpu.mem_write(0x5bd834, struct.pack('<I', elapsed));
o.call(0x44c860, eax = BOARD) assert n.vertrix_block_resource_update(
    c.byref(animation), c.byref(resource), depth + 1, elapsed,
    c.byref(descriptor)) expected = bytearray(raw);
struct.pack_into('<I', expected, 0xb4, descriptor.value);
struct.pack_into('<I', expected, 0xb8, animation.frame);struct.pack_into('<I',expected,0xcc,animation.timer.counter)
        assert bytes(expected)==bytes(o.cpu.mem_read(BOARD,len(raw))),(case,'whole normal block')
    for case in range(1024):
raw = bytearray(rng.randbytes(0x160)) counter = rng.getrandbits(32);
period = rng.getrandbits(32);
frame = rng.getrandbits(32) struct.pack_into('<2I', raw, 0xcc, counter, period);struct.pack_into('<I',raw,0xb8,frame)
        animation=Animation(Timer(counter,period),frame,count)
        descriptor=c.c_uint32(struct.unpack_from('<I',raw,0xb4)[0])
        attached=c.POINTER(Resource)()
        target=c.pointer(resource) if case%2 else None
        original_target=MASK if target else 0
        o.cpu.mem_write(BOARD,bytes(raw));o.call(0x4ac8d0,eax=BOARD,edx=original_target)
        assert n.vertrix_block_resource_attach(c.byref(animation),c.byref(attached),target)
        assert bool(attached)==bool(target)
        assert animation.frame_count==(count if target else 0)
        expected=bytearray(raw);struct.pack_into('<I',expected,0xb0,original_target)
        struct.pack_into('<I',expected,0xb8,animation.frame);struct.pack_into('<I',expected,0xcc,animation.timer.counter)
        assert bytes(expected)==bytes(o.cpu.mem_read(BOARD,len(raw))),(case,'attachment')
        o.call(0x4ac8a0,eax=BOARD)
        assert n.vertrix_block_resource_bind(c.byref(animation),attached,depth+1,c.byref(descriptor))
        struct.pack_into('<I',expected,0xb4,descriptor.value)
        assert bytes(expected)==bytes(o.cpu.mem_read(BOARD,len(raw))),(case,'binding')
    for case in range(1024):
endpoint_count =
    rng.choice([ 0, 1, 8, 0xffffffff, rng.getrandbits(32) ])
        raw = bytearray(rng.randbytes(0x160)) struct.pack_into('<I', raw, 0xb0, MASK) counter,
        period = struct.unpack_from('<2I', raw, 0xcc) old_frame =
            struct.unpack_from('<I', raw, 0xb8)[0] animation =
                Animation(Timer(counter, period), old_frame, rng.getrandbits(32)) endpoint =
                    Resource(0, endpoint_count, None, None, None)
                        o.cpu.mem_write(MASK + 4, struct.pack('<I', endpoint_count))
                            o.cpu.mem_write(BOARD, bytes(raw));
o.call(0x4ac720, eax = BOARD) assert n
        .vertrix_block_resource_last(c.byref(animation),
                                     c.byref(endpoint)) assert animation.frame_count
    == endpoint_count expected = bytearray(raw);
struct.pack_into('<I', expected, 0xb8, animation.frame) assert
    bytes(expected) == bytes(o.cpu.mem_read(BOARD, len(raw))),
    (case, 'last frame')assert(animation.timer.counter, animation.timer.period) ==
        (counter, period)assert not n.vertrix_block_resource_last(None, c.byref(endpoint))
            prior = bytes(animation) assert
                    not n.vertrix_block_resource_last(c.byref(animation), None) assert
                    bytes(animation) == prior animation = Animation(Timer(0, 1), 0,
                                                                    count) prior = bytes(animation),
            descriptor.value assert
                not n.vertrix_block_resource_update(c.byref(animation), c.byref(resource), 0, 16,
                                                    c.byref(descriptor)) and
                (bytes(animation), descriptor.value) == prior assert
                                                        not n.vertrix_block_resource_update(
                                                            None, c.byref(resource), depth + 1, 16,
                                                            c.byref(descriptor)) report =
                {
                    'status' : 'passed',
                    'cases' : 1024,
                    'linked_resources' : linked,
                    'attachment_and_binding_cases' : 1024,
                    'last_frame_cases' : 1024,
                    'scope' :
                        'Actual complete original 0x44c860 including animation and 0x4ac8a0/0x4877f0 frame binding, with no routine hooks. Whole block state matches direct and one/two-level linked resource tables. Attachment 0x4ac8d0 and binding 0x4ac8a0 also match whole objects, including NULL detach and retained descriptors. Last-frame selection 0x4ac720 also matches, including zero and full-width counts. Native traverses live resource nodes while updating the block; resource graph construction, actual VF actor binding and complete object runtime/game remain unfinished.'
                }(a.build_dir / 'block-resource-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()

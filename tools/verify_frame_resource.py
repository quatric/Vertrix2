"""Compare native linked frame traversal with actual original 0x4877f0."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original


class Resource(c.Structure):
    pass


Resource._fields_ = [('kind', c.c_uint32), ('count', c.c_size_t),
                    ('frames', c.POINTER(c.c_uint32)),
                    ('children', c.POINTER(c.POINTER(Resource))),
                    ('indices', c.POINTER(c.c_uint32))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'resource.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared',
                    '-fPIC', str(source / 'frame_resource.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    get = native.vertrix_frame_resource_get
    get.argtypes = [c.POINTER(Resource), c.c_uint32, c.c_size_t, c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    rng = random.Random(0x4877f0)
    comparisons = 0
    for case in range(256):
        nodes, owned = [], []
        for level in range(1 + case % 8):
            count = rng.randrange(1, 33)
            address = 0x800000 + level * 0x600
            if level == 0:
                values = [rng.getrandbits(32) for _ in range(count)]
                frames = (c.c_uint32 * count)(*values)
                kind = rng.choice([0, 2, 16, 0xffffffff])
                node = Resource(kind, count, frames, None, None)
                original.cpu.mem_write(address, struct.pack('<6I', address + 0x100,
                                                            count, 0, 0, 0, kind))
                original.cpu.mem_write(address + 0x100, struct.pack('<' + 'I' * count, *values))
                owned.append(frames)
            else:
                prior = nodes[-1]
                indices = [rng.randrange(prior.count) for _ in range(count)]
                mappings = (c.c_uint32 * count)(*indices)
                children = (c.POINTER(Resource) * count)(*([c.pointer(prior)] * count))
                node = Resource(1, count, None, children, mappings)
                original.cpu.mem_write(address, struct.pack('<6I', 0, count, 0,
                                                            address + 0x100, address + 0x200, 1))
                original.cpu.mem_write(address + 0x100,
                                       struct.pack('<' + 'I' * count, *([address - 0x600] * count)))
                original.cpu.mem_write(address + 0x200, struct.pack('<' + 'I' * count, *indices))
                owned.extend([mappings, children])
            nodes.append(node)
        output = c.c_uint32(0x12345678)
        for index in range(nodes[-1].count):
            expected = original.call(0x4877f0, eax=address, edx=index)
            assert get(c.byref(nodes[-1]), index, len(nodes), c.byref(output))
            assert output.value == expected, (case, index, output.value, expected)
            comparisons += 1
        before = output.value
        assert not get(c.byref(nodes[-1]), nodes[-1].count, len(nodes), c.byref(output))
        assert not get(c.byref(nodes[-1]), 0, len(nodes) - 1, c.byref(output))
        assert output.value == before
    cycle = Resource(1, 1, None, None, None)
    children = (c.POINTER(Resource) * 1)(c.pointer(cycle))
    mappings = (c.c_uint32 * 1)(0)
    cycle.children, cycle.indices = children, mappings
    assert not get(c.byref(cycle), 0, 100, c.byref(output))
    assert not get(None, 0, 1, c.byref(output))
    assert not get(c.byref(cycle), 0, 1, None)
    report = {'status': 'passed', 'graphs': 256, 'descriptor_comparisons': comparisons,
              'maximum_depth': 8, 'scope': 'Actual original 0x4877f0 without hooks; direct '
              'and linked descriptor traversal. Invalid bounds, insufficient budget and cyclic '
              'graphs reject without publishing output. Resource construction and VF actor '
              'ownership remain to be integrated.'}
    (args.build_dir / 'frame-resource-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

""
    "Compare original percentage-table construction and row selection."
    "" import argparse import ctypes as c import json from pathlib import Path import struct import
        subprocess from original import Original from unicorn.x86_const import UC_X86_REG_EIP

    class Weights(c.Structure)
    : _fields_ =
    [
        ('bytes', (c.c_uint8 * 256) * 101), ('words', (c.c_uint16 * 512) * 101),
        ('alpha', (c.c_uint8 * 256) * 256), ('inverse_alpha', (c.c_uint8 * 256) * 256)
    ]

    def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument('executable', type = Path) parser.add_argument(
                       '--build-dir', type = Path, required = True) args =
          parser.parse_args() args.build_dir.mkdir(parents = True, exist_ok = True) source =
              Path(__file__).resolve().parents[1] / 'source' library =
                  args.build_dir.resolve() /
                  'render-weights.dylib' subprocess.run(
                      [
                          'cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                          str(source / 'render_weights.c'), '-o', str(library)
                      ],
                      check = True) native =
                      c.CDLL(str(library)) native.vertrix_render_weights_build.argtypes =
                          [c.POINTER(Weights)] native.vertrix_render_weights_select.argtypes =
                              [
                                  c.POINTER(Weights), c.c_uint8, c.POINTER(c.c_void_p),
                                  c.POINTER(c.c_void_p)
                              ] tables =
                                  Weights() assert native.vertrix_render_weights_build(
                                      c.byref(tables)) == 1 original = Original(args.executable)
try : original.call(0x480730)
    except RuntimeError:
        original.cpu.emu_start(original.cpu.reg_read(UC_X86_REG_EIP), 0x700000,
                               count=100_000_000)
        assert original.cpu.reg_read(UC_X86_REG_EIP) == 0x700000
    assert bytes(tables.bytes) == bytes(original.cpu.mem_read(0x558cf0, 101 * 256))
    expected_words = bytes(original.cpu.mem_read(0x55f1f8, 101 * 1024))
    actual_words = b''.join(struct.pack('<512H', *row) for row in tables.words)
    assert actual_words == expected_words
    assert bytes(tables.alpha) == bytes(original.cpu.mem_read(0x578600, 65536))
    assert bytes(tables.inverse_alpha) == bytes(original.cpu.mem_read(0x588600, 65536))
    for amount in range(101):
        original.cpu.mem_write(0x5bc00e, bytes([amount]))
        original.call(0x4ae26d, stop=0x4ae2be)
        original_source = struct.unpack('<I', original.cpu.mem_read(0x55f1f0, 4))[0]
        original_destination = struct.unpack('<I', original.cpu.mem_read(0x55f1f4, 4))[0]
        source_pointer, destination_pointer = c.c_void_p(), c.c_void_p()
        assert native.vertrix_render_weights_select(c.byref(tables), amount,
            c.byref(source_pointer), c.byref(destination_pointer)) == 1
        assert c.string_at(source_pointer, 256) == bytes(original.cpu.mem_read(original_source, 256))
        assert c.string_at(destination_pointer, 256) == bytes(original.cpu.mem_read(original_destination, 256))
    before = source_pointer.value, destination_pointer.value
    assert native.vertrix_render_weights_select(c.byref(tables), 101,
        c.byref(source_pointer), c.byref(destination_pointer)) == 0
    assert (source_pointer.value, destination_pointer.value) == before
    report = {'status': 'passed', 'byte_entries': 25856, 'word_entries': 51712,
        'selected_amounts': 101, 'alpha_entries': 131072,
        'scope': 'Complete original480730 executes unchanged. All percentage '
                 'bytes/words and both alpha tables match. Original4ae26d..4ae2b9 row selection matches '
                 'all valid amounts. Render preparation '
                 'and playable application remain unfinished.'}
    (args.build_dir / 'render-weights-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()

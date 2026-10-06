""
    "Verify native original SPR frame loading against independent byte parsing."
    "" import argparse import ctypes import hashlib import json import struct import
        subprocess from pathlib import Path from verify_image import NativeImage

    class SpriteFrame(ctypes.Structure)
    : _fields_ =
          [
              ("image", NativeImage), ("frame_count", ctypes.c_uint32),
              ("metadata", ctypes.c_uint32 * 10)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument("archive", type = Path) parser.add_argument(
                       "--build-dir", type = Path, required = True) args =
          parser.parse_args() args.build_dir.mkdir(parents = True, exist_ok = True) root =
              Path(__file__).resolve().parents[1] library =
                  args.build_dir.resolve() /
                  "sprite.dylib" subprocess.run(
                      [
                          "rtk", "proxy", "cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                          "-Werror", str(root / "source/image.c"), str(root / "source/vf.c"), "-o",
                          str(library)
                      ],
                      check = True) native =
                      ctypes.CDLL(str(library)) native.vertrix_vf_open.argtypes =
                          [ctypes.c_char_p] native.vertrix_vf_open.restype =
                              ctypes.c_void_p native.vertrix_vf_close.argtypes =
                                  [ctypes.c_void_p] native.vertrix_vf_count.argtypes =
                                      [ctypes.c_void_p] native.vertrix_vf_name.argtypes =
                                          [ ctypes.c_void_p,
                                            ctypes.c_uint32 ] native.vertrix_vf_name.restype =
                                              ctypes.c_char_p native.vertrix_vf_size.argtypes =
                                                  [
                                                      ctypes.c_void_p, ctypes.c_uint32,
                                                      ctypes.POINTER(ctypes.c_uint32)
                                                  ] native.vertrix_vf_read.argtypes =
                                                      [
                                                          ctypes.c_void_p, ctypes.c_uint32,
                                                          ctypes.c_uint32, ctypes.c_void_p,
                                                          ctypes.c_size_t
                                                      ] native.vertrix_image_sprite.argtypes =
                                                          [
                                                              ctypes.c_void_p, ctypes.c_char_p,
                                                              ctypes.c_uint32,
                                                              ctypes.POINTER(SpriteFrame)
                                                          ] native.vertrix_sprite_free.argtypes =
                                                              [ctypes.POINTER(
                                                                  SpriteFrame)] archive =
                                                                  native.vertrix_vf_open(
                                                                      str(args.archive.resolve())
                                                                          .encode())
                                                                      assert archive resources,
      frames, pixels = 0, [], 0
try:
        for index in range(native.vertrix_vf_count(archive)):
            name = native.vertrix_vf_name(archive, index)
            if not name.lower().endswith(b".spr"):
                continue
            resources += 1
            size = ctypes.c_uint32()
            assert native.vertrix_vf_size(archive, index, ctypes.byref(size))
            data = ctypes.create_string_buffer(size.value)
            assert native.vertrix_vf_read(archive, index, 0, data, size.value)
            blob = data.raw
            count = struct.unpack_from("<H", blob)[0]
            cursor = 2
            for frame_index in range(count):
                header = blob[cursor:cursor + 48]
                assert header[0] == 0 and header[47] == 4
                width, height = struct.unpack_from("<2I", header, 12)
                cursor += 48
                payload = blob[cursor:cursor + width * height * 4]
                cursor += len(payload)
                expected = bytearray(payload)
                expected[0::4], expected[2::4] = payload[2::4], payload[0::4]
                frame = SpriteFrame()
                assert native.vertrix_image_sprite(archive, name, frame_index, ctypes.byref(frame)), (name, frame_index)
            try : assert(frame.image.width, frame.image.height, frame.frame_count) == (width, height, count)
                    assert tuple(frame.metadata) == struct.unpack_from("<10I", header, 8)
                    actual = ctypes.string_at(frame.image.rgba, len(expected))
                    assert actual == expected
                    saved = bytes(frame)
                    assert not native.vertrix_image_sprite(archive, name, frame_index, ctypes.byref(frame))
                    assert bytes(frame) == saved
                    pixels += width * height
                    frames.append({"name": name.decode("cp1252"), "frame": frame_index,
                                   "rgba_sha256": hashlib.sha256(actual).hexdigest()})
                finally:
                    native.vertrix_sprite_free(ctypes.byref(frame))
                assert bytes(frame) == bytes(ctypes.sizeof(frame))
            assert cursor == len(blob)
            assert not native.vertrix_image_sprite(archive, name, count, ctypes.byref(SpriteFrame()))
    finally:
        native.vertrix_vf_close(archive)
    header = bytearray(48)
    struct.pack_into("<2I", header, 12, 2, 1)
    header[47] = 4
    valid = struct.pack("<H", 1) + header + bytes([1, 2, 3, 4, 5, 6, 7, 8])
    invalid = [b"", valid[:1], valid[:-1], valid + b"x", b"\x02\0" + valid[2:]]
    for offset, value in [(2, 1), (49, 1), (14, 0), (18, 0)]:
        data = bytearray(valid)
        data[offset] = value
        invalid.append(bytes(data))
    name = b"sprite.spr"
    for i, contents in enumerate(invalid + [valid]):
        path = args.build_dir / f"sprite-{i}.vf"
        path.write_bytes(struct.pack("<IIIII", 10, 1, len(contents), 20 + len(name), len(name)) + name + contents)
        archive = native.vertrix_vf_open(str(path.resolve()).encode())
        assert archive
        frame = SpriteFrame()
                try : result
= native.vertrix_image_sprite(archive, name, 0, ctypes.byref(frame))
      assert bool(result) == (i == len(invalid)),
    i if not result
    : assert bytes(frame) ==
      bytes(ctypes.sizeof(frame)) else : assert ctypes.string_at(frame.image.rgba, 8) ==
      bytes([ 3, 2, 1, 4, 7, 6, 5, 8 ]) finally
    : native.vertrix_sprite_free(ctypes.byref(frame)) native.vertrix_vf_close(
          archive) report = {
        "status" : "passed",
        "sprite_resources_verified" : resources,
        "sprite_frames_verified" : len(frames),
        "sprite_pixels_verified" : pixels,
        "invalid_resources_rejected" : len(invalid),
        "scope" :
            "All original SPR raw frame channels/descriptors checked by independent serialization "
            "parsing; original postprocessing, blending and Wii rendering remain separate",
        "frames" : frames
    }(args.build_dir / "sprite-verification.json")
                                .write_text(json.dumps(report, indent = 2) + "\n") print(json.dumps(
                                    {
                                        key: value for key, value in report.items() if key != "frames"
                                    },
                                    indent = 2))

                                    if __name__
                            == "__main__" : main()

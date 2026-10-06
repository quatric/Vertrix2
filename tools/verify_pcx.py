""
    "Verify original indexed PCX assets read directly from VF."
    "" import argparse import ctypes import hashlib import io import json import struct import
        subprocess from pathlib import Path from PIL import Image

    class Pcx(ctypes.Structure)
    : _fields_ =
          [
              ("width", ctypes.c_uint32), ("height", ctypes.c_uint32), ("indices", ctypes.c_void_p),
              ("palette", ctypes.c_uint8 * 768)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument("archive", type = Path) parser.add_argument(
                       "--build-dir", type = Path, required = True) args =
          parser.parse_args() args.build_dir.mkdir(parents = True, exist_ok = True) root =
              Path(__file__).resolve().parents[1] library =
                  args.build_dir.resolve() /
                  "pcx.dylib" subprocess.run(
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
                                                      ] native.vertrix_image_pcx.argtypes =
                                                          [
                                                              ctypes.c_void_p, ctypes.c_char_p,
                                                              ctypes.POINTER(Pcx)
                                                          ] native.vertrix_pcx_free.argtypes =
                                                              [ctypes.POINTER(Pcx)] pixels,
      verified = 0, [] def compare(archive, name, data)
    : image = Pcx() reference =
          Image.open(io.BytesIO(data)) assert reference.mode in["P", "L"] assert native
              .vertrix_image_pcx(archive, name, ctypes.byref(image)),
      name
try : assert(image.width, image.height)
    == reference.size
            indices = ctypes.string_at(image.indices, image.width *image.height)
                          assert indices == reference.tobytes(),
            name expanded = Image.frombytes("P", reference.size, indices) expanded
                                .putpalette(bytes(image.palette)) assert expanded.convert("RGB")
                                .tobytes() == reference.convert("RGB").tobytes(),
            name saved = bytes(image) assert
                         not native.vertrix_image_pcx(archive, name, ctypes.byref(image)) assert
                         bytes(image) == saved return len(indices),
            hashlib.sha256(indices).hexdigest() finally
        : native.vertrix_pcx_free(ctypes.byref(image)) assert not image.indices
                and image.width == image.height ==
                        0 native.vertrix_pcx_free(ctypes.byref(image)) archive =
                native.vertrix_vf_open(str(args.archive.resolve()).encode()) assert archive
    try:
        for index in range(native.vertrix_vf_count(archive)):
            name = native.vertrix_vf_name(archive, index)
            if not name.lower().endswith(b".pcx"):
                continue
            size = ctypes.c_uint32()
            assert native.vertrix_vf_size(archive, index, ctypes.byref(size))
            data = ctypes.create_string_buffer(size.value)
            assert native.vertrix_vf_read(archive, index, 0, data, size.value)
            count, digest = compare(archive, name, data.raw)
            pixels += count
            verified.append({"name": name.decode("cp1252"), "indices_sha256": digest})
    finally:
        native.vertrix_vf_close(archive)
    valid = []
    for width in [1, 3, 64, 129]:
        for height in [1, 3]:
            image = Image.new("P", (width, height))
            image.putpalette(bytes((i * 13) % 256 for i in range(768)))
            image.putdata([([0, 191, 192, 255][i % 4] if width < 64 else 255) for i in range(width * height)])
            stream = io.BytesIO()
            image.save(stream, format="PCX")
            valid.append(stream.getvalue())
    base = valid[-1]
    invalid = [b"", base[:128], base[:-1], base[:128] + bytes(769),
               base[:128] + b"\xc0\0" + base[-769:]]
    for offset, value in [(0, 0), (1, 2), (2, 0), (3, 4), (65, 3), (66, 0)]:
        data = bytearray(base)
        data[offset] = value
        if offset == 66:
            data[67] = 0
        invalid.append(bytes(data))
    data = bytearray(base)
    struct.pack_into("<H", data, 4, 65535)
    invalid.append(bytes(data))
    name = b"mask.pcx"
    for i, data in enumerate(valid + invalid):
        path = args.build_dir / f"pcx-{i}.vf"
        path.write_bytes(struct.pack("<IIIII", 10, 1, len(data), 20 + len(name), len(name)) + name + data)
        archive = native.vertrix_vf_open(str(path.resolve()).encode())
        assert archive
            try:
                if i
< len(valid)
    : compare(archive, name, data) else
    : image = Pcx() assert not native.vertrix_image_pcx(archive, name, ctypes.byref(image)),
      i assert not image.indices and image.width == image.height ==
                                         0 finally
    : native.vertrix_vf_close(
          archive) report = {
          "status" : "passed",
          "original_pcx_verified" : len(verified),
          "original_pixels_verified" : pixels,
          "layout_fixtures_verified" : len(valid),
          "invalid_pcx_rejected" : len(invalid),
          "scope" : "All original PCX indices and palette-expanded RGB match Pillow; original mask "
                    "application, JPG and Wii rendering remain separate",
          "images" : verified
      }(args.build_dir / "pcx-verification.json")
                                .write_text(json.dumps(report, indent = 2) + "\n") print(json.dumps(
                                    {
                                        key: value for key, value in report.items() if key != "images"
                                    },
                                    indent = 2))

                                    if __name__
                            == "__main__" : main()

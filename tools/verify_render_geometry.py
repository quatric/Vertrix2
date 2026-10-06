"""Compare board clipping and initial cell positioning with original x86."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original

class Clip(ctypes.Structure):
    _fields_ = [(name, ctypes.c_int16) for name in ("left", "right", "top", "bottom")]

class Dimensions(ctypes.Structure):
    _fields_ = [("width", ctypes.c_uint16), ("height", ctypes.c_uint16)]

class SpriteClip(ctypes.Structure):
    _fields_ = [("bounds", Clip), ("width", ctypes.c_uint16), ("height", ctypes.c_uint16),
                ("source_offset", ctypes.c_uint32), ("clipped", ctypes.c_uint8)]

class Binding(ctypes.Structure):
    _fields_=[("source_address",ctypes.c_uint32),("source_width",ctypes.c_uint32),
              ("target_width",ctypes.c_int32),("padding_pixels",ctypes.c_int32),
              ("target_stride",ctypes.c_uint32),("target_padding",ctypes.c_uint32)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "render-geometry.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror",
                    str(root / "source/render_geometry.c"), str(root / "source/surface.c"), str(root / "source/render_dispatch.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_board_clip.argtypes = [ctypes.c_int16, ctypes.c_int16]
    native.vertrix_board_clip.restype = Clip
    native.vertrix_board_cell_position.argtypes = [ctypes.c_int16, ctypes.c_int16, ctypes.c_uint32,
                                                  ctypes.c_uint32, ctypes.c_int8, ctypes.c_int8,
                                                  ctypes.POINTER(ctypes.c_int16), ctypes.POINTER(ctypes.c_int16)]
    native.vertrix_board_cell_center.argtypes = [ctypes.c_int16, ctypes.c_int16, ctypes.c_int32,
                                                ctypes.c_int32, ctypes.POINTER(ctypes.c_int16), ctypes.POINTER(ctypes.c_int16)]
    native.vertrix_resource_measure.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_uint8, ctypes.POINTER(ctypes.c_int32), ctypes.POINTER(ctypes.c_int32)]
    native.vertrix_resource_measure_state.argtypes = [ctypes.POINTER(Dimensions), Dimensions,
        ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_uint8,
        ctypes.POINTER(ctypes.c_int32), ctypes.POINTER(ctypes.c_int32)]
    native.vertrix_resource_bounds.argtypes = [ctypes.c_uint16, ctypes.c_uint16,
        ctypes.c_int16, ctypes.c_int16, ctypes.c_uint8, ctypes.c_int16, ctypes.c_int16] + [ctypes.POINTER(ctypes.c_int32)] * 4
    native.vertrix_sprite_clip.argtypes = [ctypes.c_int16, ctypes.c_int16, ctypes.c_uint16,
        ctypes.c_uint16, Clip, ctypes.POINTER(SpriteClip)]
    native.vertrix_sprite_clip_mode.argtypes = [ctypes.c_int16,ctypes.c_int16,ctypes.c_uint16,
        ctypes.c_uint16,ctypes.c_uint8,ctypes.c_uint16,ctypes.c_uint16,Clip,Clip,ctypes.POINTER(SpriteClip)]
    native.vertrix_render_scale_clip_offset.argtypes = [ctypes.c_uint8,ctypes.c_uint16,
        ctypes.c_uint16,ctypes.c_uint16,ctypes.c_uint32,ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_render_binding.argtypes=[ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint16,
        ctypes.c_uint16,ctypes.c_uint16,ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint8]
    native.vertrix_render_binding.restype=Binding
    oracle = Original(args.executable)
    rng = random.Random(0x430930)
    origins = [(x, y) for x in (-32768, -1, 0, 32649, 32767)
               for y in (-32768, -1, 0, 32457, 32767)]
    origins += [(rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)) for _ in range(1000)]
    for ox, oy in origins:
        offsets = [(rng.randrange(-128, 128), rng.randrange(-128, 128)) for _ in range(65)]
        expected_clip, positions = oracle.board_render_geometry(ox, oy, offsets)
        clip = native.vertrix_board_clip(ox, oy)
        assert tuple(getattr(clip, name) for name, _ in Clip._fields_) == expected_clip
        for index, (dx, dy) in enumerate(offsets):
            x, y = ctypes.c_int16(), ctypes.c_int16()
            assert native.vertrix_board_cell_position(ox, oy, index // 13, index % 13, dx, dy,
                                                      ctypes.byref(x), ctypes.byref(y))
            assert (x.value, y.value) == positions[index]
        dimensions = [(rng.choice((0, 1, 23, 24, 25, 26, 48, 32767, -1, -32768)),
                       rng.choice((0, 1, 23, 24, 25, 26, 48, 32767, -1, -32768))) for _ in range(65)]
        _, centered = oracle.board_render_geometry(ox, oy, offsets, dimensions)
        for index, (width, height) in enumerate(dimensions):
            cx, cy = positions[index]
            x, y = ctypes.c_int16(), ctypes.c_int16()
            assert native.vertrix_board_cell_center(cx, cy, width, height, ctypes.byref(x), ctypes.byref(y))
            assert (x.value, y.value) == centered[index], (ox, oy, index, width, height)
    x, y = ctypes.c_int16(123), ctypes.c_int16(456)
    assert not native.vertrix_board_cell_position(0, 0, 5, 0, 0, 0, ctypes.byref(x), ctypes.byref(y))
    assert (x.value, y.value) == (123, 456)
    cases = [(w, h, mode) for mode in range(17)
             for w in range(32) for h in (0, 15, 16, 24, 32767, 32768, 65535)]
    cases += [(rng.randrange(65536), rng.randrange(65536), rng.randrange(17)) for _ in range(10000)]
    for index, (width, height, mode) in enumerate(cases):
        expected = oracle.resource_measure(width, height, mode, descriptor=bool(index % 2))
        mw, mh = ctypes.c_int32(), ctypes.c_int32()
        assert native.vertrix_resource_measure(width, height, mode, ctypes.byref(mw), ctypes.byref(mh))
        assert (mw.value, mh.value) == expected, (width, height, mode, expected, mw.value, mh.value)
    mw, mh = ctypes.c_int32(123), ctypes.c_int32(456)
    assert not native.vertrix_resource_measure(24, 24, 17, ctypes.byref(mw), ctypes.byref(mh))
    assert (mw.value, mh.value) == (123, 456)
    state_cases = 10000
    for index in range(state_cases):
        width, height = rng.randrange(65536), rng.randrange(65536)
        mode, screen_mode = rng.randrange(17), rng.randrange(17)
        override, unscaled = rng.choice((0, 1, 255)), rng.choice((0, 1, 255))
        descriptor = bool(index % 2)
        expected = oracle.resource_measure(width, height, mode, descriptor, override, unscaled, screen_mode)
        dimensions = Dimensions(width, height)
        fallback = Dimensions(123, 456) if descriptor else dimensions
        mw, mh = ctypes.c_int32(), ctypes.c_int32()
        assert native.vertrix_resource_measure_state(ctypes.byref(dimensions) if descriptor else None,
            fallback, mode, override, unscaled, screen_mode, ctypes.byref(mw), ctypes.byref(mh))
        assert (mw.value, mh.value) == expected
    bounds_cases = 10000
    for _ in range(bounds_cases):
        width, height = rng.randrange(1, 65536), rng.randrange(1, 65536)
        ax, ay, px, py = [rng.randrange(-32768, 32768) for _ in range(4)]
        mode = rng.randrange(17)
        expected = oracle.resource_bounds(width, height, ax, ay, mode, px, py)
        outputs = [ctypes.c_int32() for _ in range(4)]
        assert native.vertrix_resource_bounds(width, height, ax, ay, mode, px, py,
            *[ctypes.byref(value) for value in outputs])
        assert tuple(value.value for value in outputs) == expected, (width, height, ax, ay, mode, expected, [v.value for v in outputs])
    clip_cases = 20000
    for index in range(clip_cases):
        if index < 10000:
            px, py = rng.randrange(-50, 150), rng.randrange(-50, 350)
            width, height = rng.randrange(1, 80), rng.randrange(1, 80)
            rectangle = (0,119,0,311)
        else:
            px, py = rng.randrange(-32768,32768), rng.randrange(-32768,32768)
            width, height = rng.randrange(1,65536), rng.randrange(1,65536)
            rectangle = tuple(rng.randrange(-32768,32768) for _ in range(4))
        expected = oracle.sprite_clip(px, py, width, height, rectangle)
        output = SpriteClip()
        valid = native.vertrix_sprite_clip(px,py,width,height,Clip(*rectangle),ctypes.byref(output))
        assert bool(valid) == (expected is not None), (px,py,width,height,rectangle,expected)
        if valid:
            actual = tuple(getattr(output.bounds,n) for n,_ in Clip._fields_) + (output.width,
                output.height,output.source_offset,output.clipped)
            assert actual == expected, (px,py,width,height,rectangle,actual,expected)
    mode_cases = 10000
    for index in range(mode_cases):
        px,py = rng.randrange(-200,800),rng.randrange(-200,800)
        width,height = rng.randrange(1,200),rng.randrange(1,200)
        mode = rng.choice((0,1,2,3,4,5,127,255))
        target = (rng.randrange(65536),rng.randrange(65536))
        cached = tuple(rng.randrange(-32768,32768) for _ in range(4))
        custom = tuple(rng.randrange(-32768,32768) for _ in range(4))
        expected = oracle.sprite_clip(px,py,width,height,cached,mode,target,custom)
        output = SpriteClip()
        valid = native.vertrix_sprite_clip_mode(px,py,width,height,mode,*target,
            Clip(*custom),Clip(*cached),ctypes.byref(output))
        assert bool(valid) == (expected is not None)
        if valid:
            actual = tuple(getattr(output.bounds,n) for n,_ in Clip._fields_) + (output.width,
                output.height,output.source_offset,output.clipped)
            assert actual == expected,(mode,actual,expected)
    alignment_cases = 10000
    for _ in range(alignment_cases):
        mode,width = rng.randrange(1,16),rng.randrange(65536)
        columns,rows = rng.randrange(1025),rng.randrange(1025)
        initial = rng.randrange(2**32)
        expected = oracle.scale_clip_offset(mode,width,columns,rows,initial)
        output = ctypes.c_uint32()
        assert native.vertrix_render_scale_clip_offset(mode,width,columns,rows,initial,ctypes.byref(output))
        assert output.value == expected
    output = ctypes.c_uint32(123)
    assert not native.vertrix_render_scale_clip_offset(1,24,1025,0,0,ctypes.byref(output))
    assert output.value == 123
    binding_cases=10000
    for _ in range(binding_cases):
        arguments=(rng.randrange(2**32),rng.randrange(2**32),rng.randrange(65536),
                   rng.randrange(65536),rng.randrange(65536),rng.randrange(2**32),
                   rng.randrange(2**32),rng.randrange(256))
        expected=oracle.render_binding(*arguments)
        actual=native.vertrix_render_binding(*arguments)
        assert tuple(getattr(actual,name) for name,_ in Binding._fields_)==expected
    report = {"render_bindings_verified":binding_cases,"scale_clip_alignments_verified": alignment_cases,"clip_mode_cases_verified": mode_cases,"sprite_clipping_cases_verified": clip_cases,"resource_bounds_verified": bounds_cases,"resource_state_measurements_verified": state_cases,"resource_measurements_verified": len(cases),"status": "passed", "clip_rectangles_verified": len(origins),
              "cell_positions_verified": len(origins) * 65,
              "centered_cell_positions_verified": len(origins) * 65,
              "scope": "Complete 0x42ff10 and first positioning phase 0x430930..0x4309f9 execute unchanged for mode-16 and centered cells. Resource measurement 0x4b14c0 also executes unchanged for descriptor and fallback dimensions with resolved modes 0..16. Centering tests supply dimensions at the measurement boundary; Full 0x4b15e0 descriptor bounds and unscaled clipping phase 0x4b1ae9..0x4b1c6f also execute unchanged. Rejection redirects to the phase endpoint before the surrounding function epilogue; Scale clipping phase 0x4ae99f..0x4aea50 also executes unchanged; later effects and drawing remain separate."}
    (args.build_dir / "render-geometry-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()

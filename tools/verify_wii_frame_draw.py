"""Record final-frame GX state and geometry; this does not execute a GPU."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import subprocess
from verify_wii_assets import HEADER
from verify_wii_frame_texture import WiiTexture
CALLS = [('GX_SetNumChans', 'uint8_t a', 'a==0'), ('GX_SetNumTexGens', 'uint8_t a', 'a==1'), ('GX_SetTexCoordGen', 'uint16_t a,uint32_t b,uint32_t d,uint32_t e', 'a==GX_TEXCOORD0 && b==GX_TG_MTX2x4 && d==GX_TG_TEX0 && e==GX_IDENTITY'), ('GX_SetNumTevStages', 'uint8_t a', 'a==1'), ('GX_SetTevOrder', 'uint8_t a,uint8_t b,uint8_t d,uint8_t e', 'a==GX_TEVSTAGE0 && b==GX_TEXCOORD0 && d==GX_TEXMAP0 && e==GX_COLORNULL'), ('GX_SetTevOp', 'uint8_t a,uint8_t b', 'a==GX_TEVSTAGE0 && b==GX_REPLACE'), ('GX_SetZMode', 'uint8_t a,uint8_t b,uint8_t d', 'a==GX_FALSE && b==GX_ALWAYS && d==GX_FALSE'), ('GX_SetBlendMode', 'uint8_t a,uint8_t b,uint8_t d,uint8_t e', 'a==GX_BM_NONE && b==GX_BL_ONE && d==GX_BL_ZERO && e==GX_LO_COPY'), ('GX_SetAlphaCompare', 'uint8_t a,uint8_t b,uint8_t d,uint8_t e,uint8_t f', 'a==GX_ALWAYS && b==0 && d==GX_AOP_AND && e==GX_ALWAYS && f==0'), ('GX_SetColorUpdate', 'uint8_t a', 'a==GX_TRUE'), ('GX_SetAlphaUpdate', 'uint8_t a', 'a==GX_FALSE'), ('GX_SetCullMode', 'uint8_t a', 'a==GX_CULL_NONE'), ('GX_ClearVtxDesc', 'void', '1'), ('GX_SetVtxDesc', 'uint8_t a,uint8_t b', '(a==GX_VA_POS || a==GX_VA_TEX0) && b==GX_DIRECT'), ('GX_SetVtxAttrFmt', 'uint8_t a,uint32_t b,uint32_t d,uint32_t e,uint32_t f', 'a==GX_VTXFMT0 && ((b==GX_VA_POS && d==GX_POS_XYZ) || (b==GX_VA_TEX0 && d==GX_TEX_ST)) && e==GX_F32 && f==0'), ('GX_Begin', 'uint8_t a,uint8_t b,uint16_t d', 'a==GX_QUADS && b==GX_VTXFMT0 && d==4'), ('GX_End', 'void', '1')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    names = 'GX_TEXCOORD0 GX_TG_MTX2x4 GX_TG_TEX0 GX_IDENTITY GX_TEVSTAGE0 GX_COLORNULL GX_REPLACE GX_ALWAYS GX_BM_NONE GX_BL_ONE GX_BL_ZERO GX_LO_COPY GX_AOP_AND GX_CULL_NONE GX_VA_POS GX_VA_TEX0 GX_DIRECT GX_VTXFMT0 GX_POS_XYZ GX_F32 GX_TEX_ST GX_QUADS'.split()
    declarations = '\n'.join(f'void {name}({args});' for name, args, _ in CALLS)
    (build / 'gccore.h').write_text(HEADER + '\n#define GX_TRUE 1\n#define GX_TEXMAP0 0\n' + '\n'.join(f'#define {name} {20+i}' for i, name in enumerate(names)) + '\n' + declarations + '\nvoid GX_Position3f32(float,float,float);\nvoid GX_TexCoord2f32(float,float);\n')
    stubs = '#include "wii_frame_draw.h"\n#include <assert.h>\nunsigned events[64],count,components; float values[20];\nvoid reset(void){count=components=0;}\n'
    for index, (name, args, condition) in enumerate(CALLS):
        stubs += f'void {name}({args}){{assert({condition});assert(count<64);events[count++]={index+1};}}\n'
    stubs += '''
int vertrix_wii_texture_bind(VertrixWiiTexture *t,uint32_t map)
{
    assert(t->ready && t->pixels.data && map == 0);
    events[count++] = 18;
    return 1;
}
void GX_Position3f32(float x, float y, float z)
{
    events[count++] = 19;
    values[components++] = x;
    values[components++] = y;
    values[components++] = z;
}
void GX_TexCoord2f32(float s, float t)
{
    events[count++] = 20;
    values[components++] = s;
    values[components++] = t;
}
'''
    (build / 'stubs.c').write_text(stubs)
    library = build / 'wii-frame-draw.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', '-I', str(build), '-I', str(root / 'source'), str(build / 'stubs.c'), str(root / 'source/wii_frame_draw.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_wii_frame_draw.argtypes = [c.POINTER(WiiTexture), c.c_int16, c.c_int16, c.c_uint16, c.c_uint16]
    count = c.c_uint.in_dll(native, 'count')
    components = c.c_uint.in_dll(native, 'components')
    events = (c.c_uint * 64).in_dll(native, 'events')
    values = (c.c_float * 20).in_dll(native, 'values')
    rng = random.Random(0x475851)
    for case in range(2048):
        texture = WiiTexture()
        texture.ready, texture.pixels.data = 1, 1
        texture.u, texture.v = rng.choice((1, 0.75, 0.5)), rng.choice((1, 0.75, 0.5))
        x, y = rng.randrange(- 32768, 32768), rng.randrange(- 32768, 32768)
        width, height = rng.randrange(1, 65536), rng.randrange(1, 65536)
        native.reset()
        assert native.vertrix_wii_frame_draw(c.byref(texture), x, y, width, height)
        assert list(events[: count.value]) == list(range(1, 15)) + [14, 15, 15, 18, 16] + [19, 20] * 4 + [17]
        assert components.value == 20
        assert list(values) == [x, y, 0, 0, 0, x + width, y, 0, texture.u, 0, x + width, y + height, 0, texture.u, texture.v, x, y + height, 0, 0, texture.v]
        native.reset()
        assert not native.vertrix_wii_frame_draw(c.byref(texture), x, y, 0, height)
        assert not count.value
        texture.u = float('nan')
        assert not native.vertrix_wii_frame_draw(c.byref(texture), x, y, width, height)
        assert not count.value
        subprocess.run(['make', '-s', '-C', str(root), 'wii-frame-draw', f'BUILD={build / "powerpc"}'], check=True)
    report = {'status': 'passed', 'recorded_quad_cases': 2048, 'invalid_no_command_cases': 4096, 'scope': 'Recorded host GX calls verify opaque completed-frame state, vertex/UV order, ' 'padding limits and coordinate range. Source alpha does not reject/blend final RGB. ' 'Compiles against actual libogc for PowerPC. GPU rendering, projection/viewport, ' 'video copy/swap and full application remain unverified.'}
    (build / 'wii-frame-draw-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()

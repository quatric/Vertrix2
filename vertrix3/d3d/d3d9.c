/* Direct3D 9 for the recompiled game: IDirect3D9, IDirect3DDevice9 and the resources the game
 * and its statically linked D3DX create. Objects live in guest memory as a virtual table pointer
 * followed by the host object's index; every method is a host function. Resource memory
 * (texture levels, vertex and index buffers) is guest memory, so Lock hands back real pointers.
 * Draws are decoded into V3Vertex arrays and given to the platform's renderer. */

#include "render.h"
#include "win32.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    D3D_OK = 0,
    D3DERR_INVALIDCALL = 0x8876086cu,
    D3DERR_NOTAVAILABLE = 0x8876086au,
    E_NOINTERFACE = 0x80004002u,
    S_FALSE = 1
};

enum
{
    KIND_D3D = 1,
    KIND_DEVICE,
    KIND_TEXTURE,
    KIND_SURFACE,
    KIND_VERTEX_BUFFER,
    KIND_INDEX_BUFFER,
    KIND_STATE_BLOCK,
    KIND_DECLARATION,
    KIND_SWAP_CHAIN,
    KIND_QUERY,
    KIND_COUNT
};

enum
{
    MAX_LEVELS = 12,
    OBJECTS = 8192
};

/* --- state blocks ------------------------------------------------------------------------- */

typedef struct
{
    V3RenderState r;
    uint32_t fvf, declaration;
    uint32_t stream, stream_offset, stream_stride;
    uint32_t indices;
    uint32_t textures[V3_MAX_STAGES]; /* guest texture objects */
} DeviceState;

typedef struct
{
    uint8_t render[V3_RENDER_STATES];
    uint8_t stage[V3_MAX_STAGES][V3_STAGE_STATES];
    uint8_t sampler[V3_MAX_STAGES][V3_SAMPLER_STATES];
    uint8_t texture[V3_MAX_STAGES];
    uint8_t world, view, projection, texture_transform[V3_MAX_STAGES];
    uint8_t viewport, scissor, material, light[V3_MAX_LIGHTS];
    uint8_t fvf, declaration, stream, indices;
} StateMask;

/* --- objects ------------------------------------------------------------------------------ */

typedef struct
{
    int kind;
    uint32_t guest; /* the guest object: vtable, index */
    int32_t refs;
    union
    {
        struct
        {
            V3Texture levels[MAX_LEVELS];
            uint32_t level_count, usage, pool;
            uint32_t surfaces[MAX_LEVELS]; /* guest surface objects, made on demand */
        } texture;
        struct
        {
            uint32_t texture; /* owning texture object index, or 0 */
            uint32_t level;
            uint32_t width, height, format, pitch, pixels;
            int back_buffer, depth;
        } surface;
        struct
        {
            uint32_t data, size, fvf, format, usage;
        } buffer;
        struct
        {
            DeviceState state;
            StateMask mask;
        } block;
        struct
        {
            uint32_t elements; /* guest copy of the D3DVERTEXELEMENT9 array */
            uint32_t count;
        } declaration;
    } u;
} Object;

static Object *objects[OBJECTS];
static uint32_t vtables[KIND_COUNT];

static Object *object_new(int kind)
{
    for (uint32_t i = 1; i < OBJECTS; ++i)
    {
        if (!objects[i])
        {
            Object *o = calloc(1, sizeof *o);
            o->kind = kind;
            o->refs = 1;
            o->guest = v3_alloc(16);
            v3_w32(o->guest, vtables[kind]);
            v3_w32(o->guest + 4, i);
            v3_w32(o->guest + 8, 0x3d3d9009u);
            objects[i] = o;
            return o;
        }
    }
    v3_fatal("too many Direct3D objects");
}

static uint32_t index_of(const Object *o)
{
    return v3_r32(o->guest + 4);
}

static Object *object_of(uint32_t guest)
{
    if (!guest || v3_r32(guest + 8) != 0x3d3d9009u)
    {
        return NULL;
    }
    const uint32_t i = v3_r32(guest + 4);
    return i < OBJECTS ? objects[i] : NULL;
}

/* --- the device ----------------------------------------------------------------------------- */

static struct
{
    uint32_t guest;
    uint32_t width, height, format, depth_format, windowed;
    DeviceState s;
    uint32_t recording; /* state block being recorded (object index) */
    uint32_t back_buffer, depth_surface;
    int in_scene;
    V3Vertex *vertices;
    uint32_t vertex_capacity;
    uint32_t *indices;
    uint32_t index_capacity;
    unsigned frames;
    unsigned draws;
    uint8_t parameters[56]; /* the D3DPRESENT_PARAMETERS in use */
    uint32_t swap_chain;
} device;

static V3Renderer *renderer;
int v3_trace_d3d;

static void trace(const char *format, ...)
{
    if (!v3_trace_d3d)
    {
        return;
    }
    va_list args;
    va_start(args, format);
    char text[256];
    vsnprintf(text, sizeof text, format, args);
    va_end(args);
    v3_log("d3d: %s", text);
}

static float f32(uint32_t bits)
{
    float f;
    memcpy(&f, &bits, 4);
    return f;
}

static uint32_t bits_of(float f)
{
    uint32_t b;
    memcpy(&b, &f, 4);
    return b;
}

static void identity(float *m)
{
    memset(m, 0, 16 * sizeof *m);
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

static void default_state(DeviceState *d)
{
    memset(d, 0, sizeof *d);
    V3RenderState *s = &d->r;
    uint32_t *rs = s->render;
    rs[7] = 1;            /* ZENABLE */
    rs[8] = 3;            /* FILLMODE solid */
    rs[9] = 2;            /* SHADEMODE gouraud */
    rs[14] = 1;           /* ZWRITEENABLE */
    rs[15] = 0;           /* ALPHATESTENABLE */
    rs[16] = 1;           /* LASTPIXEL */
    rs[19] = 2;           /* SRCBLEND one */
    rs[20] = 1;           /* DESTBLEND zero */
    rs[22] = 3;           /* CULLMODE ccw */
    rs[23] = 4;           /* ZFUNC lessequal */
    rs[24] = 0;           /* ALPHAREF */
    rs[25] = 8;           /* ALPHAFUNC always */
    rs[26] = 0;           /* DITHERENABLE */
    rs[27] = 0;           /* ALPHABLENDENABLE */
    rs[28] = 0;           /* FOGENABLE */
    rs[29] = 0;           /* SPECULARENABLE */
    rs[34] = 0;           /* FOGCOLOR */
    rs[52] = 0;           /* STENCILENABLE */
    rs[53] = 1;           /* STENCILFAIL keep */
    rs[54] = 1;           /* STENCILZFAIL keep */
    rs[55] = 1;           /* STENCILPASS keep */
    rs[56] = 8;           /* STENCILFUNC always */
    rs[57] = 0;           /* STENCILREF */
    rs[58] = 0xffffffffu; /* STENCILMASK */
    rs[59] = 0xffffffffu; /* STENCILWRITEMASK */
    rs[60] = 0xffffffffu; /* TEXTUREFACTOR */
    rs[137] = 1;          /* LIGHTING */
    rs[139] = 0;          /* AMBIENT */
    rs[141] = 1;          /* COLORVERTEX */
    rs[143] = 1;          /* NORMALIZENORMALS off really 0 */
    rs[143] = 0;
    rs[145] = 1;          /* DIFFUSEMATERIALSOURCE color1 */
    rs[146] = 2;          /* SPECULARMATERIALSOURCE color2 */
    rs[147] = 0;          /* AMBIENTMATERIALSOURCE material */
    rs[148] = 0;          /* EMISSIVEMATERIALSOURCE material */
    rs[168] = 0x0f;       /* COLORWRITEENABLE */
    rs[171] = 1;          /* BLENDOP add */
    for (unsigned i = 0; i < V3_MAX_STAGES; ++i)
    {
        uint32_t *ts = s->stage[i];
        ts[1] = i == 0 ? 4 : 1; /* COLOROP modulate / disable */
        ts[2] = 2;              /* COLORARG1 texture */
        ts[3] = 1;              /* COLORARG2 current */
        ts[4] = i == 0 ? 2 : 1; /* ALPHAOP selectarg1 / disable */
        ts[5] = 2;              /* ALPHAARG1 texture */
        ts[6] = 1;              /* ALPHAARG2 current */
        ts[11] = i;             /* TEXCOORDINDEX */
        uint32_t *ss = s->sampler[i];
        ss[1] = 1; /* ADDRESSU wrap */
        ss[2] = 1;
        ss[3] = 1;
        ss[5] = 1; /* MAGFILTER point */
        ss[6] = 1; /* MINFILTER point */
        ss[7] = 0; /* MIPFILTER none */
        identity(s->texture_transform[i]);
    }
    identity(s->world);
    identity(s->view);
    identity(s->projection);
    s->material.diffuse[0] = s->material.diffuse[1] = s->material.diffuse[2] = 1.0f;
    s->material.diffuse[3] = 1.0f;
}

static DeviceState *target(StateMask **mask)
{
    if (device.recording)
    {
        Object *b = objects[device.recording];
        *mask = &b->u.block.mask;
        return &b->u.block.state;
    }
    *mask = NULL;
    return &device.s;
}

#define MARK(field)                                                                                \
    do                                                                                             \
    {                                                                                              \
        if (mask)                                                                                  \
            mask->field = 1;                                                                       \
    } while (0)

/* --- method plumbing ------------------------------------------------------------------------ */

static void method_unimplemented(Cpu *c)
{
    v3_log("unimplemented Direct3D method %s", v3_host_current);
    v3_trap(c, v3_r32(c->esp), "unimplemented Direct3D method");
}

typedef struct
{
    unsigned slot;
    const char *name;
    V3Code code;
} Method;

static uint32_t make_vtable(const char *interface, unsigned slots, const Method *methods)
{
    const uint32_t table = v3_system_alloc(4 * slots);
    for (unsigned i = 0; i < slots; ++i)
    {
        const char *name = NULL;
        V3Code code = method_unimplemented;
        for (const Method *m = methods; m->name; ++m)
        {
            if (m->slot == i)
            {
                name = m->name;
                code = m->code;
            }
        }
        char *label = malloc(96);
        snprintf(label, 96, "%s::%s", interface, name ? name : "?");
        if (!name)
        {
            snprintf(label, 96, "%s::method%u", interface, i);
        }
        v3_w32(table + 4 * i, v3_host_function(label, code));
    }
    return table;
}

/* IUnknown, shared by every interface. */
static void QueryInterface(Cpu *c)
{
    const uint32_t this = ARG(0);
    Object *o = object_of(this);
    const uint32_t iid = ARG(1);
    v3_log("QueryInterface on kind %d for {%08x}", o ? o->kind : 0, v3_r32(iid));
    if (ARG(2))
    {
        v3_w32(ARG(2), 0);
    }
    STDCALL_RETURN(3, E_NOINTERFACE);
}

static void release_object(Object *o);

static void AddRef(Cpu *c)
{
    Object *o = object_of(ARG(0));
    STDCALL_RETURN(1, o ? (uint32_t)++o->refs : 0);
}

static void Release(Cpu *c)
{
    Object *o = object_of(ARG(0));
    if (!o)
    {
        STDCALL_RETURN(1, 0);
    }
    const int32_t refs = --o->refs;
    if (refs <= 0 && o->kind != KIND_DEVICE && o->kind != KIND_D3D && o->kind != KIND_SWAP_CHAIN)
    {
        release_object(o);
    }
    STDCALL_RETURN(1, (uint32_t)(refs < 0 ? 0 : refs));
}

static void GetDevice(Cpu *c)
{
    v3_w32(ARG(1), device.guest);
    STDCALL_RETURN(2, D3D_OK);
}

static void release_object(Object *o)
{
    const uint32_t i = index_of(o);
    switch (o->kind)
    {
    case KIND_TEXTURE:
        for (uint32_t l = 0; l < o->u.texture.level_count; ++l)
        {
            if (renderer->texture_destroyed)
            {
                renderer->texture_destroyed(renderer, &o->u.texture.levels[l]);
            }
            v3_free(o->u.texture.levels[l].pixels);
            if (o->u.texture.surfaces[l])
            {
                Object *s = object_of(o->u.texture.surfaces[l]);
                if (s)
                {
                    s->u.surface.texture = 0;
                }
            }
        }
        for (unsigned stage = 0; stage < V3_MAX_STAGES; ++stage)
        {
            if (device.s.textures[stage] == o->guest)
            {
                device.s.textures[stage] = 0;
                device.s.r.texture[stage] = NULL;
            }
        }
        break;
    case KIND_SURFACE:
        if (!o->u.surface.texture && !o->u.surface.back_buffer && o->u.surface.pixels)
        {
            v3_free(o->u.surface.pixels);
        }
        if (o->u.surface.texture && objects[o->u.surface.texture])
        {
            objects[o->u.surface.texture]->u.texture.surfaces[o->u.surface.level] = 0;
        }
        break;
    case KIND_VERTEX_BUFFER:
    case KIND_INDEX_BUFFER:
        v3_free(o->u.buffer.data);
        break;
    case KIND_DECLARATION:
        v3_free(o->u.declaration.elements);
        break;
    default:
        break;
    }
    v3_w32(o->guest + 8, 0);
    v3_free(o->guest);
    objects[i] = NULL;
    free(o);
}

/* --- formats -------------------------------------------------------------------------------- */

uint32_t v3_format_bytes(uint32_t format)
{
    switch (format)
    {
    case V3_FMT_A8R8G8B8:
    case V3_FMT_X8R8G8B8:
        return 4;
    case V3_FMT_R5G6B5:
    case V3_FMT_X1R5G5B5:
    case V3_FMT_A1R5G5B5:
    case V3_FMT_A4R4G4B4:
    case V3_FMT_A8L8:
        return 2;
    case V3_FMT_A8:
    case V3_FMT_L8:
        return 1;
    default:
        return 0;
    }
}

static int texture_format_supported(uint32_t format)
{
    return v3_format_bytes(format) != 0;
}

uint32_t v3_texel(const V3Texture *t, uint32_t x, uint32_t y)
{
    const uint32_t at = t->pixels + y * t->pitch;
    switch (t->format)
    {
    case V3_FMT_A8R8G8B8:
        return v3_r32(at + 4 * x);
    case V3_FMT_X8R8G8B8:
        return v3_r32(at + 4 * x) | 0xff000000u;
    case V3_FMT_R5G6B5:
    {
        const uint32_t p = v3_r16(at + 2 * x);
        const uint32_t r = (p >> 11) & 31, g = (p >> 5) & 63, b = p & 31;
        return 0xff000000u | ((r << 3 | r >> 2) << 16) | ((g << 2 | g >> 4) << 8) | (b << 3 | b >> 2);
    }
    case V3_FMT_X1R5G5B5:
    case V3_FMT_A1R5G5B5:
    {
        const uint32_t p = v3_r16(at + 2 * x);
        const uint32_t r = (p >> 10) & 31, g = (p >> 5) & 31, b = p & 31;
        const uint32_t a = t->format == V3_FMT_X1R5G5B5 || (p & 0x8000u) ? 0xffu : 0u;
        return a << 24 | ((r << 3 | r >> 2) << 16) | ((g << 3 | g >> 2) << 8) | (b << 3 | b >> 2);
    }
    case V3_FMT_A4R4G4B4:
    {
        const uint32_t p = v3_r16(at + 2 * x);
        return ((p >> 12) & 15) * 0x11000000u | ((p >> 8) & 15) * 0x110000u |
               ((p >> 4) & 15) * 0x1100u | (p & 15) * 0x11u;
    }
    case V3_FMT_A8:
        return v3_r8(at + x) << 24;
    case V3_FMT_L8:
        return 0xff000000u | v3_r8(at + x) * 0x010101u;
    case V3_FMT_A8L8:
    {
        const uint32_t p = v3_r16(at + 2 * x);
        return (p >> 8) << 24 | (p & 0xffu) * 0x010101u;
    }
    default:
        return 0xffff00ffu;
    }
}

/* --- IDirect3D9 ----------------------------------------------------------------------------- */

static const uint32_t MODES[][2] = {{640, 480}, {800, 600}, {1024, 768}};

static void D3D_GetAdapterCount(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void D3D_GetAdapterIdentifier(Cpu *c)
{
    const uint32_t id = ARG(3);
    memset(MEM(id), 0, 1100);
    v3_write_string(id, "wiigx.dll", 512);
    v3_write_string(id + 512, "Wii GX", 512);
    v3_write_string(id + 1024, "\\\\.\\DISPLAY1", 32);
    v3_w32(id + 1056, 0x00010000u);
    v3_w32(id + 1060, 0x00060000u);
    v3_w32(id + 1064, 0x1002);
    v3_w32(id + 1068, 0x4150);
    STDCALL_RETURN(4, D3D_OK);
}

static int mode_format(uint32_t format)
{
    return format == V3_FMT_X8R8G8B8 || format == V3_FMT_R5G6B5;
}

static void D3D_GetAdapterModeCount(Cpu *c)
{
    STDCALL_RETURN(3, mode_format(ARG(2)) ? sizeof MODES / sizeof MODES[0] : 0);
}

static void D3D_EnumAdapterModes(Cpu *c)
{
    const uint32_t i = ARG(3);
    if (!mode_format(ARG(2)) || i >= sizeof MODES / sizeof MODES[0])
    {
        STDCALL_RETURN(5, D3DERR_INVALIDCALL);
    }
    const uint32_t mode = ARG(4);
    v3_w32(mode, MODES[i][0]);
    v3_w32(mode + 4, MODES[i][1]);
    v3_w32(mode + 8, 60);
    v3_w32(mode + 12, ARG(2));
    STDCALL_RETURN(5, D3D_OK);
}

static void D3D_GetAdapterDisplayMode(Cpu *c)
{
    const uint32_t mode = ARG(2);
    v3_w32(mode, 640);
    v3_w32(mode + 4, 480);
    v3_w32(mode + 8, 60);
    v3_w32(mode + 12, V3_FMT_X8R8G8B8);
    STDCALL_RETURN(3, D3D_OK);
}

static void D3D_CheckDeviceType(Cpu *c)
{
    const uint32_t back = ARG(4);
    const int ok = mode_format(ARG(3)) &&
                   (back == V3_FMT_X8R8G8B8 || back == V3_FMT_A8R8G8B8 || back == V3_FMT_R5G6B5 ||
                    back == 0);
    trace("CheckDeviceType(type %u, display %u, back buffer %u, windowed %u) -> %s", ARG(2),
          ARG(3), back, ARG(5), ok ? "ok" : "no");
    STDCALL_RETURN(6, ok ? D3D_OK : D3DERR_NOTAVAILABLE);
}

static void D3D_CheckDeviceFormat(Cpu *c)
{
    const uint32_t usage = ARG(4);
    const uint32_t type = ARG(5);
    const uint32_t format = ARG(6);
    int ok;
    if (usage & 2) /* DEPTHSTENCIL */
    {
        ok = format == 80 || format == 77 || format == 75 || format == 71;
    }
    else if (usage & 1) /* RENDERTARGET */
    {
        ok = format == V3_FMT_X8R8G8B8 || format == V3_FMT_A8R8G8B8;
    }
    else
    {
        ok = (type == 3 || type == 1) && texture_format_supported(format); /* TEXTURE, SURFACE */
    }
    trace("CheckDeviceFormat(usage %x, type %u, format %u) -> %s", usage, type, format,
          ok ? "ok" : "no");
    STDCALL_RETURN(7, ok ? D3D_OK : D3DERR_NOTAVAILABLE);
}

static void D3D_CheckDeviceMultiSampleType(Cpu *c)
{
    if (ARG(6))
    {
        v3_w32(ARG(6), 1);
    }
    STDCALL_RETURN(7, ARG(5) == 0 ? D3D_OK : D3DERR_NOTAVAILABLE);
}

static void D3D_CheckDepthStencilMatch(Cpu *c)
{
    trace("CheckDepthStencilMatch(%u, %u, %u)", ARG(3), ARG(4), ARG(5));
    STDCALL_RETURN(6, D3D_OK);
}

static void D3D_CheckDeviceFormatConversion(Cpu *c)
{
    STDCALL_RETURN(5, D3D_OK);
}

static void fill_caps(uint32_t caps)
{
    memset(MEM(caps), 0, 304);
    v3_w32(caps + 0, 1);              /* HAL */
    v3_w32(caps + 8, 0x20000);        /* Caps: READ_SCANLINE */
    v3_w32(caps + 12, 0x20000000u);   /* Caps2: DYNAMICTEXTURES */
    v3_w32(caps + 16, 0x20 | 0x80);   /* Caps3: ALPHA_FULLSCREEN_FLIP_OR_DISCARD, COPY_TO_VIDMEM */
    v3_w32(caps + 20, 0x8000000fu);   /* presentation intervals one..four, immediate */
    v3_w32(caps + 28, 0x10 | 0x20 | 0x40 | 0x80 | 0x200 | 0x400 | 0x4000 | 0x10000 | 0x80000);
    v3_w32(caps + 32, 0x2 | 0x10 | 0x20 | 0x40 | 0x80 | 0x100 | 0x800); /* misc: masks, culling */
    v3_w32(caps + 36, 0x1 | 0x10 | 0x80 | 0x200000 | 0x4000000); /* dither, ztest, fogvertex, scissor */
    v3_w32(caps + 40, 0xff);          /* all z compares */
    v3_w32(caps + 44, 0x1fff);        /* source blends */
    v3_w32(caps + 48, 0x1fff);        /* destination blends */
    v3_w32(caps + 52, 0xff);          /* alpha compares */
    v3_w32(caps + 56, 0x8 | 0x200 | 0x4000 | 0x80000); /* shade: gouraud colors, specular, alpha */
    v3_w32(caps + 60, 0x1 | 0x2 | 0x4 | 0x40 | 0x100); /* perspective, pow2, alpha, nonpow2 conditional, projected */
    v3_w32(caps + 64, 0x100 | 0x200 | 0x1000000 | 0x2000000); /* min/mag point, linear */
    v3_w32(caps + 76, 0x1 | 0x2 | 0x4 | 0x8 | 0x10 | 0x20); /* wrap, mirror, clamp, border, independent uv */
    v3_w32(caps + 84, 0x1 | 0x2 | 0x4 | 0x8 | 0x10); /* line caps */
    v3_w32(caps + 88, 1024);
    v3_w32(caps + 92, 1024);
    v3_w32(caps + 100, 8192);
    v3_w32(caps + 104, 1024);
    v3_w32(caps + 108, 1);
    v3_w32(caps + 112, bits_of(1e10f));
    v3_w32(caps + 116, bits_of(-1e8f));
    v3_w32(caps + 120, bits_of(-1e8f));
    v3_w32(caps + 124, bits_of(1e8f));
    v3_w32(caps + 128, bits_of(1e8f));
    v3_w32(caps + 136, 0xff);         /* stencil: keep, zero, replace, saturating and wrapping steps, invert */
    v3_w32(caps + 140, 0x80008);      /* FVF: 8 texture coordinates, do not strip elements */
    v3_w32(caps + 144, 0x03ffffffu);  /* every texture op */
    v3_w32(caps + 148, V3_MAX_STAGES);
    v3_w32(caps + 152, 2);
    v3_w32(caps + 156, 0x2 | 0x8 | 0x10 | 0x20); /* texgen, directional and positional lights, local viewer */
    v3_w32(caps + 160, V3_MAX_LIGHTS);
    v3_w32(caps + 176, bits_of(1.0f));
    v3_w32(caps + 180, 0xfffff);
    v3_w32(caps + 184, 0xffff);
    v3_w32(caps + 188, 1);
    v3_w32(caps + 192, 256);
    v3_w32(caps + 196, 0xfffe0000u); /* vertex shader 0.0 */
    v3_w32(caps + 204, 0xffff0000u); /* pixel shader 0.0 */
    v3_w32(caps + 232, 1);
    v3_w32(caps + 236, 0x1 | 0x2);
    v3_w32(caps + 240, 1);
    v3_w32(caps + 244, 0x100 | 0x200 | 0x1000000 | 0x2000000);
}

static void D3D_GetDeviceCaps(Cpu *c)
{
    fill_caps(ARG(3));
    STDCALL_RETURN(4, D3D_OK);
}

static void D3D_GetAdapterMonitor(Cpu *c)
{
    STDCALL_RETURN(2, 0x00040001u);
}

static uint32_t surface_new(uint32_t width, uint32_t height, uint32_t format, int back, int depth)
{
    Object *s = object_new(KIND_SURFACE);
    s->u.surface.width = width;
    s->u.surface.height = height;
    s->u.surface.format = format;
    s->u.surface.back_buffer = back;
    s->u.surface.depth = depth;
    return s->guest;
}

static void reset_device(uint32_t parameters)
{
    memcpy(device.parameters, MEM(parameters), sizeof device.parameters);
    device.width = v3_r32(parameters);
    device.height = v3_r32(parameters + 4);
    if (device.width == 0 || device.height == 0)
    {
        device.width = 640;
        device.height = 480;
        v3_w32(parameters, 640);
        v3_w32(parameters + 4, 480);
    }
    device.format = v3_r32(parameters + 8);
    if (device.format == 0)
    {
        device.format = V3_FMT_X8R8G8B8;
        v3_w32(parameters + 8, device.format);
    }
    device.windowed = v3_r32(parameters + 32);
    device.depth_format = v3_r32(parameters + 36) ? v3_r32(parameters + 40) : 0;
    default_state(&device.s);
    device.s.r.viewport.width = device.width;
    device.s.r.viewport.height = device.height;
    device.s.r.viewport.max_z = 1.0f;
    device.s.r.scissor.right = (int32_t)device.width;
    device.s.r.scissor.bottom = (int32_t)device.height;
    memcpy(device.parameters, MEM(parameters), sizeof device.parameters);
    renderer->begin_frame(renderer, device.width, device.height);
    v3_log("Direct3D device %ux%u, format %u, %s, depth format %u", device.width, device.height,
           device.format, device.windowed ? "windowed" : "full screen", device.depth_format);
}

static void D3D_CreateDevice(Cpu *c)
{
    if (!renderer)
    {
        renderer = v3_renderer();
    }
    if (!device.guest)
    {
        Object *d = object_new(KIND_DEVICE);
        device.guest = d->guest;
    }
    reset_device(ARG(5));
    if (!device.back_buffer)
    {
        device.back_buffer = surface_new(device.width, device.height, device.format, 1, 0);
        device.depth_surface = surface_new(device.width, device.height, device.depth_format, 1, 1);
    }
    v3_w32(ARG(6), device.guest);
    STDCALL_RETURN(7, D3D_OK);
}

static const Method D3D_METHODS[] = {
    {0, "QueryInterface", QueryInterface},
    {1, "AddRef", AddRef},
    {2, "Release", Release},
    {4, "GetAdapterCount", D3D_GetAdapterCount},
    {5, "GetAdapterIdentifier", D3D_GetAdapterIdentifier},
    {6, "GetAdapterModeCount", D3D_GetAdapterModeCount},
    {7, "EnumAdapterModes", D3D_EnumAdapterModes},
    {8, "GetAdapterDisplayMode", D3D_GetAdapterDisplayMode},
    {9, "CheckDeviceType", D3D_CheckDeviceType},
    {10, "CheckDeviceFormat", D3D_CheckDeviceFormat},
    {11, "CheckDeviceMultiSampleType", D3D_CheckDeviceMultiSampleType},
    {12, "CheckDepthStencilMatch", D3D_CheckDepthStencilMatch},
    {13, "CheckDeviceFormatConversion", D3D_CheckDeviceFormatConversion},
    {14, "GetDeviceCaps", D3D_GetDeviceCaps},
    {15, "GetAdapterMonitor", D3D_GetAdapterMonitor},
    {16, "CreateDevice", D3D_CreateDevice},
    {0, NULL, NULL}};

/* --- IDirect3DDevice9: general ------------------------------------------------------------- */

static void Dev_TestCooperativeLevel(Cpu *c)
{
    STDCALL_RETURN(1, D3D_OK);
}

static void Dev_GetAvailableTextureMem(Cpu *c)
{
    STDCALL_RETURN(1, 64u << 20);
}

static void Dev_EvictManagedResources(Cpu *c)
{
    STDCALL_RETURN(1, D3D_OK);
}

static uint32_t d3d_object;

static void Dev_GetDirect3D(Cpu *c)
{
    v3_w32(ARG(1), d3d_object);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetDeviceCaps(Cpu *c)
{
    fill_caps(ARG(1));
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetDisplayMode(Cpu *c)
{
    const uint32_t mode = ARG(2);
    v3_w32(mode, device.width);
    v3_w32(mode + 4, device.height);
    v3_w32(mode + 8, 60);
    v3_w32(mode + 12, device.format);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetCreationParameters(Cpu *c)
{
    const uint32_t p = ARG(1);
    v3_w32(p, 0);
    v3_w32(p + 4, 1);
    v3_w32(p + 8, v3_main_window());
    v3_w32(p + 12, 0x20); /* software vertex processing */
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetCursorProperties(Cpu *c)
{
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_SetCursorPosition(Cpu *c)
{
    STDCALL_RETURN(4, 0);
}

static void Dev_ShowCursor(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void Dev_Reset(Cpu *c)
{
    reset_device(ARG(1));
    STDCALL_RETURN(2, D3D_OK);
}

static void present_frame(void);
static void read_back_into(Object *dst);

static void Dev_Present(Cpu *c)
{
    present_frame();
    STDCALL_RETURN(5, D3D_OK);
}

static void present_frame(void)
{
    renderer->present(renderer);
    ++device.frames;
    /* V3_DUMP=FRAME:PATH writes the first 32 MB of the heap at that frame. */
    static const char *dump = (const char *)1;
    if (dump == (const char *)1)
    {
        dump = getenv("V3_DUMP");
    }
    if (dump && (unsigned)atoi(dump) == device.frames && strchr(dump, ':'))
    {
        FILE *f = fopen(strchr(dump, ':') + 1, "wb");
        if (f)
        {
            fwrite(MEM(0x01000000u), 1, 0x02000000, f);
            fclose(f);
        }
    }
    static int trace_frame = -1;
    if (trace_frame < 0)
    {
        const char *e = getenv("V3_TRACE_FRAME");
        trace_frame = e ? atoi(e) : 0;
    }
    if (trace_frame)
    {
        /* Every host call of that one frame. */
        v3_trace_calls = device.frames + 1 == (unsigned)trace_frame;
    }
    if (device.frames % 300 == 0)
    {
        v3_log("frame %u, %u draws, heap %u KB", device.frames, device.draws,
               v3_heap_used() >> 10);
        /* V3_PEEK: guest dwords to show alongside, `ADDR` or `*ADDR+OFFSET` (hex). */
        const char *peek = getenv("V3_PEEK");
        while (peek && *peek)
        {
            char *end;
            const int deref = *peek == '*';
            uint32_t a = (uint32_t)strtoul(peek + deref, &end, 16);
            if (deref)
            {
                a = v3_r32(a) + (*end == '+' ? (uint32_t)strtoul(end + 1, &end, 16) : 0);
            }
            v3_log("  peek %08x = %08x", a, a >= 0x10000u ? v3_r32(a) : 0);
            peek = *end ? end + 1 : end;
        }
    }
}

/* The device's one swap chain. */
static void Dev_GetSwapChain(Cpu *c)
{
    if (ARG(1) != 0)
    {
        v3_w32(ARG(2), 0);
        STDCALL_RETURN(3, D3DERR_INVALIDCALL);
    }
    if (!device.swap_chain)
    {
        device.swap_chain = object_new(KIND_SWAP_CHAIN)->guest;
    }
    ++object_of(device.swap_chain)->refs;
    v3_w32(ARG(2), device.swap_chain);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetNumberOfSwapChains(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void Swap_Present(Cpu *c)
{
    present_frame();
    STDCALL_RETURN(6, D3D_OK);
}

static void Swap_GetFrontBufferData(Cpu *c)
{
    read_back_into(object_of(ARG(1)));
    STDCALL_RETURN(2, D3D_OK);
}

static void Swap_GetBackBuffer(Cpu *c)
{
    Object *s = object_of(device.back_buffer);
    ++s->refs;
    v3_w32(ARG(3), device.back_buffer);
    STDCALL_RETURN(4, D3D_OK);
}

static void Swap_GetRasterStatus(Cpu *c)
{
    v3_w32(ARG(1), 1);
    v3_w32(ARG(1) + 4, 0);
    STDCALL_RETURN(2, D3D_OK);
}

static void Swap_GetDisplayMode(Cpu *c)
{
    const uint32_t mode = ARG(1);
    v3_w32(mode, device.width);
    v3_w32(mode + 4, device.height);
    v3_w32(mode + 8, 60);
    v3_w32(mode + 12, device.format);
    STDCALL_RETURN(2, D3D_OK);
}

static void Swap_GetPresentParameters(Cpu *c)
{
    memcpy(MEM(ARG(1)), device.parameters, sizeof device.parameters);
    STDCALL_RETURN(2, D3D_OK);
}

static const Method SWAP_CHAIN_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                            {1, "AddRef", AddRef},
                                            {2, "Release", Release},
                                            {3, "Present", Swap_Present},
                                            {4, "GetFrontBufferData", Swap_GetFrontBufferData},
                                            {5, "GetBackBuffer", Swap_GetBackBuffer},
                                            {6, "GetRasterStatus", Swap_GetRasterStatus},
                                            {7, "GetDisplayMode", Swap_GetDisplayMode},
                                            {8, "GetDevice", GetDevice},
                                            {9, "GetPresentParameters", Swap_GetPresentParameters},
                                            {0, NULL, NULL}};

static void Dev_GetBackBuffer(Cpu *c)
{
    Object *s = object_of(device.back_buffer);
    ++s->refs;
    v3_w32(ARG(4), device.back_buffer);
    STDCALL_RETURN(5, D3D_OK);
}

static void Dev_GetRasterStatus(Cpu *c)
{
    v3_w32(ARG(2), 1);
    v3_w32(ARG(2) + 4, 0);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetDialogBoxMode(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetGammaRamp(Cpu *c)
{
    STDCALL_RETURN(4, 0);
}

static void Dev_GetGammaRamp(Cpu *c)
{
    const uint32_t ramp = ARG(2);
    for (uint32_t i = 0; i < 256; ++i)
    {
        v3_w16(ramp + 2 * i, i * 257);
        v3_w16(ramp + 512 + 2 * i, i * 257);
        v3_w16(ramp + 1024 + 2 * i, i * 257);
    }
    STDCALL_RETURN(3, 0);
}

/* --- resources -------------------------------------------------------------------------------- */

static void Dev_CreateTexture(Cpu *c)
{
    uint32_t width = ARG(1), height = ARG(2), levels = ARG(3);
    const uint32_t usage = ARG(4), format = ARG(5), pool = ARG(6);
    if (!texture_format_supported(format) || width == 0 || height == 0)
    {
        v3_log("CreateTexture(%ux%u, format %u) refused", width, height, format);
        STDCALL_RETURN(9, D3DERR_INVALIDCALL);
    }
    /* No mipmaps (see the caps): one level, whatever was asked. */
    (void)levels;
    levels = 1;
    Object *t = object_new(KIND_TEXTURE);
    t->u.texture.level_count = levels;
    t->u.texture.usage = usage;
    t->u.texture.pool = pool;
    for (uint32_t l = 0; l < levels; ++l)
    {
        V3Texture *level = &t->u.texture.levels[l];
        level->width = width;
        level->height = height;
        level->format = format;
        level->pitch = (width * v3_format_bytes(format) + 3u) & ~3u;
        level->pixels = v3_alloc(level->pitch * height);
        if (!level->pixels)
        {
            v3_log("out of memory for a %ux%u texture", width, height);
            STDCALL_RETURN(9, 0x8007000eu);
        }
        width = width > 1 ? width / 2 : 1;
        height = height > 1 ? height / 2 : 1;
    }
    trace("CreateTexture %ux%u format %u -> %08x", ARG(1), ARG(2), format, t->guest);
    v3_w32(ARG(7), t->guest);
    STDCALL_RETURN(9, D3D_OK);
}

static void buffer_create(Cpu *c, int kind, uint32_t length, uint32_t usage, uint32_t fvf_or_format,
                          uint32_t out)
{
    Object *b = object_new(kind);
    b->u.buffer.size = length;
    b->u.buffer.usage = usage;
    if (kind == KIND_VERTEX_BUFFER)
    {
        b->u.buffer.fvf = fvf_or_format;
    }
    else
    {
        b->u.buffer.format = fvf_or_format;
    }
    b->u.buffer.data = v3_alloc(length ? length : 4);
    (void)c;
    v3_w32(out, b->guest);
}

static void Dev_CreateVertexBuffer(Cpu *c)
{
    buffer_create(c, KIND_VERTEX_BUFFER, ARG(1), ARG(2), ARG(3), ARG(5));
    STDCALL_RETURN(7, D3D_OK);
}

static void Dev_CreateIndexBuffer(Cpu *c)
{
    buffer_create(c, KIND_INDEX_BUFFER, ARG(1), ARG(2), ARG(3), ARG(5));
    STDCALL_RETURN(7, D3D_OK);
}

static void Dev_CreateRenderTarget(Cpu *c)
{
    v3_log("CreateRenderTarget(%ux%u) refused", ARG(1), ARG(2));
    STDCALL_RETURN(9, D3DERR_NOTAVAILABLE);
}

static void Dev_CreateDepthStencilSurface(Cpu *c)
{
    v3_w32(ARG(7), surface_new(ARG(1), ARG(2), ARG(3), 0, 1));
    STDCALL_RETURN(9, D3D_OK);
}

static void Dev_CreateOffscreenPlainSurface(Cpu *c)
{
    const uint32_t width = ARG(1), height = ARG(2), format = ARG(3);
    if (!texture_format_supported(format))
    {
        STDCALL_RETURN(7, D3DERR_INVALIDCALL);
    }
    const uint32_t guest = surface_new(width, height, format, 0, 0);
    Object *s = object_of(guest);
    s->u.surface.pitch = (width * v3_format_bytes(format) + 3u) & ~3u;
    s->u.surface.pixels = v3_alloc(s->u.surface.pitch * height);
    v3_w32(ARG(5), guest);
    STDCALL_RETURN(7, D3D_OK);
}

static void Dev_UpdateTexture(Cpu *c)
{
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetRenderTarget(Cpu *c)
{
    Object *s = object_of(device.back_buffer);
    ++s->refs;
    v3_w32(ARG(2), device.back_buffer);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetRenderTarget(Cpu *c)
{
    if (ARG(2) && ARG(2) != device.back_buffer)
    {
        v3_log("SetRenderTarget to another surface is not supported");
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetDepthStencilSurface(Cpu *c)
{
    if (!device.depth_format)
    {
        v3_w32(ARG(1), 0);
        STDCALL_RETURN(2, 0x8876086cu);
    }
    Object *s = object_of(device.depth_surface);
    ++s->refs;
    v3_w32(ARG(1), device.depth_surface);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetDepthStencilSurface(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

/* Copy what the renderer last drew into a system-memory 32-bit surface. */
static void read_back_into(Object *dst)
{
    if (!dst || !dst->u.surface.pixels || !renderer->read_back ||
        (dst->u.surface.format != V3_FMT_X8R8G8B8 && dst->u.surface.format != V3_FMT_A8R8G8B8))
    {
        return;
    }
    /* One buffer for every read-back, kept: allocating 1.2 MB each time the game copies the
     * screen fragmented the Wii's little free memory until it failed. */
    static uint32_t *tmp;
    static size_t tmp_size;
    const size_t size = (size_t)dst->u.surface.width * dst->u.surface.height * 4;
    if (size > tmp_size)
    {
        free(tmp);
        tmp = malloc(size);
        tmp_size = tmp ? size : 0;
        if (!tmp)
        {
            v3_log("d3d9: no memory to read the frame back (%u bytes)", (unsigned)size);
            return;
        }
    }
    renderer->read_back(renderer, tmp, dst->u.surface.width, dst->u.surface.height);
    for (uint32_t y = 0; y < dst->u.surface.height; ++y)
    {
        for (uint32_t x = 0; x < dst->u.surface.width; ++x)
        {
            v3_w32(dst->u.surface.pixels + y * dst->u.surface.pitch + 4 * x,
                   tmp[y * dst->u.surface.width + x] | 0xff000000u);
        }
    }
}

static void Dev_GetRenderTargetData(Cpu *c)
{
    read_back_into(object_of(ARG(2)));
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetFrontBufferData(Cpu *c)
{
    read_back_into(object_of(ARG(2)));
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_StretchRect(Cpu *c)
{
    STDCALL_RETURN(6, D3D_OK);
}

static void Dev_ColorFill(Cpu *c)
{
    STDCALL_RETURN(4, D3D_OK);
}

/* --- scene and state --------------------------------------------------------------------------- */

static void Dev_BeginScene(Cpu *c)
{
    device.in_scene = 1;
    STDCALL_RETURN(1, D3D_OK);
}

static void Dev_EndScene(Cpu *c)
{
    device.in_scene = 0;
    STDCALL_RETURN(1, D3D_OK);
}

static void Dev_Clear(Cpu *c)
{
    const uint32_t flags = ARG(3);
    const uint32_t color = ARG(4);
    const float z = f32(ARG(5));
    if (getenv("V3_STATS") && (flags & 4))
    {
        static uint32_t logged;
        if (logged < 4)
        {
            ++logged;
            v3_log("clear flags %x stencil %u rects %u", flags, ARG(6), ARG(1));
        }
    }
    renderer->clear(renderer, &device.s.r, flags, color, z, ARG(6));
    STDCALL_RETURN(7, D3D_OK);
}

static float *transform_slot(DeviceState *d, uint32_t which, StateMask *mask)
{
    switch (which)
    {
    case 2:
        MARK(view);
        return d->r.view;
    case 3:
        MARK(projection);
        return d->r.projection;
    case 256:
        MARK(world);
        return d->r.world;
    default:
        if (which >= 16 && which < 16 + V3_MAX_STAGES)
        {
            if (mask)
            {
                mask->texture_transform[which - 16] = 1;
            }
            return d->r.texture_transform[which - 16];
        }
        return NULL;
    }
}

static void Dev_SetTransform(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    float *m = transform_slot(d, ARG(1), mask);
    if (m)
    {
        int bad = 0;
        for (unsigned i = 0; i < 16; ++i)
        {
            m[i] = f32(v3_r32(ARG(2) + 4 * i));
            bad |= m[i] != m[i];
        }
        static int reported;
        if (bad && !reported++)
        {
            v3_log("SetTransform(%u) with NaN, called from %08x", ARG(1), v3_r32(c->esp));
            v3_history_dump(400);
        }
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetTransform(Cpu *c)
{
    float *m = transform_slot(&device.s, ARG(1), NULL);
    for (unsigned i = 0; i < 16; ++i)
    {
        v3_w32(ARG(2) + 4 * i, bits_of(m ? m[i] : (i % 5 == 0 ? 1.0f : 0.0f)));
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_MultiplyTransform(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    float *m = transform_slot(d, ARG(1), mask);
    if (m)
    {
        float a[16], b[16], r[16];
        memcpy(a, m, sizeof a);
        for (unsigned i = 0; i < 16; ++i)
        {
            b[i] = f32(v3_r32(ARG(2) + 4 * i));
        }
        for (unsigned i = 0; i < 4; ++i)
        {
            for (unsigned j = 0; j < 4; ++j)
            {
                r[4 * i + j] = a[4 * i] * b[j] + a[4 * i + 1] * b[4 + j] + a[4 * i + 2] * b[8 + j] +
                               a[4 * i + 3] * b[12 + j];
            }
        }
        memcpy(m, r, sizeof r);
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetViewport(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t v = ARG(1);
    d->r.viewport.x = v3_r32(v);
    d->r.viewport.y = v3_r32(v + 4);
    d->r.viewport.width = v3_r32(v + 8);
    d->r.viewport.height = v3_r32(v + 12);
    d->r.viewport.min_z = f32(v3_r32(v + 16));
    d->r.viewport.max_z = f32(v3_r32(v + 20));
    MARK(viewport);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetViewport(Cpu *c)
{
    const uint32_t v = ARG(1);
    v3_w32(v, device.s.r.viewport.x);
    v3_w32(v + 4, device.s.r.viewport.y);
    v3_w32(v + 8, device.s.r.viewport.width);
    v3_w32(v + 12, device.s.r.viewport.height);
    v3_w32(v + 16, bits_of(device.s.r.viewport.min_z));
    v3_w32(v + 20, bits_of(device.s.r.viewport.max_z));
    STDCALL_RETURN(2, D3D_OK);
}

static void read_color(uint32_t at, float *out)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        out[i] = f32(v3_r32(at + 4 * i));
    }
}

static void write_color(uint32_t at, const float *in)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        v3_w32(at + 4 * i, bits_of(in[i]));
    }
}

static void Dev_SetMaterial(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t m = ARG(1);
    read_color(m, d->r.material.diffuse);
    read_color(m + 16, d->r.material.ambient);
    read_color(m + 32, d->r.material.specular);
    read_color(m + 48, d->r.material.emissive);
    d->r.material.power = f32(v3_r32(m + 64));
    MARK(material);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetMaterial(Cpu *c)
{
    const uint32_t m = ARG(1);
    write_color(m, device.s.r.material.diffuse);
    write_color(m + 16, device.s.r.material.ambient);
    write_color(m + 32, device.s.r.material.specular);
    write_color(m + 48, device.s.r.material.emissive);
    v3_w32(m + 64, bits_of(device.s.r.material.power));
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetLight(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t i = ARG(1);
    const uint32_t l = ARG(2);
    if (i < V3_MAX_LIGHTS)
    {
        V3Light *light = &d->r.light[i];
        light->type = v3_r32(l);
        read_color(l + 4, light->diffuse);
        read_color(l + 20, light->specular);
        read_color(l + 36, light->ambient);
        for (unsigned k = 0; k < 3; ++k)
        {
            light->position[k] = f32(v3_r32(l + 52 + 4 * k));
            light->direction[k] = f32(v3_r32(l + 64 + 4 * k));
            light->attenuation[k] = f32(v3_r32(l + 84 + 4 * k));
        }
        light->range = f32(v3_r32(l + 76));
        light->falloff = f32(v3_r32(l + 80));
        light->theta = f32(v3_r32(l + 96));
        light->phi = f32(v3_r32(l + 100));
        if (mask)
        {
            mask->light[i] = 1;
        }
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_LightEnable(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    if (ARG(1) < V3_MAX_LIGHTS)
    {
        d->r.light[ARG(1)].enabled = ARG(2) != 0;
        if (mask)
        {
            mask->light[ARG(1)] = 1;
        }
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetLightEnable(Cpu *c)
{
    v3_w32(ARG(2), ARG(1) < V3_MAX_LIGHTS ? (uint32_t)device.s.r.light[ARG(1)].enabled : 0);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetClipPlane(Cpu *c)
{
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetRenderState(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t state = ARG(1);
    if (state < V3_RENDER_STATES)
    {
        d->r.render[state] = ARG(2);
        if (mask)
        {
            mask->render[state] = 1;
        }
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetRenderState(Cpu *c)
{
    const uint32_t state = ARG(1);
    v3_w32(ARG(2), state < V3_RENDER_STATES ? device.s.r.render[state] : 0);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetTexture(Cpu *c)
{
    const uint32_t stage = ARG(1);
    const uint32_t t = stage < V3_MAX_STAGES ? device.s.textures[stage] : 0;
    if (t)
    {
        ++object_of(t)->refs;
    }
    v3_w32(ARG(2), t);
    STDCALL_RETURN(3, D3D_OK);
}

static void bind_texture(DeviceState *d, uint32_t stage, uint32_t guest)
{
    Object *t = object_of(guest);
    d->textures[stage] = t && t->kind == KIND_TEXTURE ? guest : 0;
    d->r.texture[stage] = t && t->kind == KIND_TEXTURE ? &t->u.texture.levels[0] : NULL;
}

static void Dev_SetTexture(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t stage = ARG(1);
    if (stage < V3_MAX_STAGES)
    {
        bind_texture(d, stage, ARG(2));
        if (mask)
        {
            mask->texture[stage] = 1;
        }
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_GetTextureStageState(Cpu *c)
{
    const uint32_t stage = ARG(1), type = ARG(2);
    v3_w32(ARG(3), stage < V3_MAX_STAGES && type < V3_STAGE_STATES ? device.s.r.stage[stage][type] : 0);
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_SetTextureStageState(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t stage = ARG(1), type = ARG(2);
    if (stage < V3_MAX_STAGES && type < V3_STAGE_STATES)
    {
        d->r.stage[stage][type] = ARG(3);
        if (mask)
        {
            mask->stage[stage][type] = 1;
        }
    }
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_GetSamplerState(Cpu *c)
{
    const uint32_t stage = ARG(1), type = ARG(2);
    v3_w32(ARG(3), stage < V3_MAX_STAGES && type < V3_SAMPLER_STATES ? device.s.r.sampler[stage][type] : 0);
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_SetSamplerState(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    const uint32_t stage = ARG(1), type = ARG(2);
    if (stage < V3_MAX_STAGES && type < V3_SAMPLER_STATES)
    {
        d->r.sampler[stage][type] = ARG(3);
        if (mask)
        {
            mask->sampler[stage][type] = 1;
        }
    }
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_ValidateDevice(Cpu *c)
{
    v3_w32(ARG(1), 1);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetScissorRect(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    d->r.scissor.left = (int32_t)v3_r32(ARG(1));
    d->r.scissor.top = (int32_t)v3_r32(ARG(1) + 4);
    d->r.scissor.right = (int32_t)v3_r32(ARG(1) + 8);
    d->r.scissor.bottom = (int32_t)v3_r32(ARG(1) + 12);
    MARK(scissor);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetScissorRect(Cpu *c)
{
    v3_w32(ARG(1), (uint32_t)device.s.r.scissor.left);
    v3_w32(ARG(1) + 4, (uint32_t)device.s.r.scissor.top);
    v3_w32(ARG(1) + 8, (uint32_t)device.s.r.scissor.right);
    v3_w32(ARG(1) + 12, (uint32_t)device.s.r.scissor.bottom);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetSoftwareVertexProcessing(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetSoftwareVertexProcessing(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void Dev_SetNPatchMode(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetNPatchMode(Cpu *c)
{
    c->eax = 0;
    STDCALL_RETURN(1, 0);
}

/* --- state blocks -------------------------------------------------------------------------------- */

static void mask_all(StateMask *m)
{
    memset(m, 1, sizeof *m);
}

static void copy_masked(DeviceState *to, const DeviceState *from, const StateMask *m)
{
    for (unsigned i = 0; i < V3_RENDER_STATES; ++i)
    {
        if (m->render[i])
        {
            to->r.render[i] = from->r.render[i];
        }
    }
    for (unsigned s = 0; s < V3_MAX_STAGES; ++s)
    {
        for (unsigned i = 0; i < V3_STAGE_STATES; ++i)
        {
            if (m->stage[s][i])
            {
                to->r.stage[s][i] = from->r.stage[s][i];
            }
        }
        for (unsigned i = 0; i < V3_SAMPLER_STATES; ++i)
        {
            if (m->sampler[s][i])
            {
                to->r.sampler[s][i] = from->r.sampler[s][i];
            }
        }
        if (m->texture[s])
        {
            to->textures[s] = from->textures[s];
            to->r.texture[s] = from->r.texture[s];
        }
        if (m->texture_transform[s])
        {
            memcpy(to->r.texture_transform[s], from->r.texture_transform[s], 64);
        }
    }
    if (m->world)
        memcpy(to->r.world, from->r.world, 64);
    if (m->view)
        memcpy(to->r.view, from->r.view, 64);
    if (m->projection)
        memcpy(to->r.projection, from->r.projection, 64);
    if (m->viewport)
        to->r.viewport = from->r.viewport;
    if (m->scissor)
        to->r.scissor = from->r.scissor;
    if (m->material)
        to->r.material = from->r.material;
    for (unsigned i = 0; i < V3_MAX_LIGHTS; ++i)
    {
        if (m->light[i])
        {
            to->r.light[i] = from->r.light[i];
        }
    }
    if (m->fvf)
        to->fvf = from->fvf;
    if (m->declaration)
        to->declaration = from->declaration;
    if (m->stream)
    {
        to->stream = from->stream;
        to->stream_offset = from->stream_offset;
        to->stream_stride = from->stream_stride;
    }
    if (m->indices)
        to->indices = from->indices;
}

static void Dev_CreateStateBlock(Cpu *c)
{
    Object *b = object_new(KIND_STATE_BLOCK);
    mask_all(&b->u.block.mask);
    b->u.block.state = device.s;
    v3_w32(ARG(2), b->guest);
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_BeginStateBlock(Cpu *c)
{
    Object *b = object_new(KIND_STATE_BLOCK);
    memset(&b->u.block.mask, 0, sizeof b->u.block.mask);
    b->u.block.state = device.s;
    device.recording = index_of(b);
    STDCALL_RETURN(1, D3D_OK);
}

static void Dev_EndStateBlock(Cpu *c)
{
    Object *b = objects[device.recording];
    device.recording = 0;
    v3_w32(ARG(1), b ? b->guest : 0);
    STDCALL_RETURN(2, b ? D3D_OK : D3DERR_INVALIDCALL);
}

static void Block_Capture(Cpu *c)
{
    Object *b = object_of(ARG(0));
    if (b)
    {
        copy_masked(&b->u.block.state, &device.s, &b->u.block.mask);
    }
    STDCALL_RETURN(1, D3D_OK);
}

static void Block_Apply(Cpu *c)
{
    Object *b = object_of(ARG(0));
    if (b)
    {
        copy_masked(&device.s, &b->u.block.state, &b->u.block.mask);
        /* A texture released since the capture is gone. */
        for (unsigned s = 0; s < V3_MAX_STAGES; ++s)
        {
            bind_texture(&device.s, s, device.s.textures[s]);
        }
    }
    STDCALL_RETURN(1, D3D_OK);
}

static const Method BLOCK_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                       {1, "AddRef", AddRef},
                                       {2, "Release", Release},
                                       {3, "GetDevice", GetDevice},
                                       {4, "Capture", Block_Capture},
                                       {5, "Apply", Block_Apply},
                                       {0, NULL, NULL}};

/* --- vertex formats -------------------------------------------------------------------------- */

typedef struct
{
    int position; /* 0 none, 3 xyz, 4 xyzrhw */
    uint32_t position_offset;
    int normal;
    uint32_t normal_offset;
    int diffuse, specular;
    uint32_t diffuse_offset, specular_offset;
    unsigned texture_sets;
    uint32_t texture_offset[2];
    uint32_t stride;
} Layout;

static int layout_from_fvf(uint32_t fvf, Layout *l)
{
    memset(l, 0, sizeof *l);
    uint32_t at = 0;
    const uint32_t position = fvf & 0x400e;
    switch (position)
    {
    case 0x2:
        l->position = 3;
        l->position_offset = at;
        at += 12;
        break;
    case 0x4:
        l->position = 4;
        l->position_offset = at;
        at += 16;
        break;
    case 0x6:
    case 0x8:
    case 0xa:
    case 0xc:
    case 0xe:
        l->position = 3;
        l->position_offset = at;
        at += 12 + 4 * ((position - 0x4) / 2);
        break;
    default:
        return 0;
    }
    if (fvf & 0x10)
    {
        l->normal = 1;
        l->normal_offset = at;
        at += 12;
    }
    if (fvf & 0x20)
    {
        at += 4;
    }
    if (fvf & 0x40)
    {
        l->diffuse = 1;
        l->diffuse_offset = at;
        at += 4;
    }
    if (fvf & 0x80)
    {
        l->specular = 1;
        l->specular_offset = at;
        at += 4;
    }
    const unsigned sets = (fvf >> 8) & 15;
    for (unsigned i = 0; i < sets; ++i)
    {
        const unsigned size = (fvf >> (16 + 2 * i)) & 3;
        const unsigned floats = size == 0 ? 2 : size == 1 ? 3 : size == 2 ? 4 : 1;
        if (i < 2)
        {
            l->texture_offset[i] = at;
        }
        at += 4 * floats;
    }
    l->texture_sets = sets < 2 ? sets : 2;
    l->stride = at;
    return 1;
}

static int layout_from_declaration(uint32_t guest, Layout *l)
{
    Object *d = object_of(guest);
    memset(l, 0, sizeof *l);
    if (!d)
    {
        return 0;
    }
    for (uint32_t i = 0; i < d->u.declaration.count; ++i)
    {
        const uint32_t e = d->u.declaration.elements + 8 * i;
        const uint32_t stream = v3_r16(e);
        const uint32_t offset = v3_r16(e + 2);
        const uint32_t type = v3_r8(e + 4);
        const uint32_t usage = v3_r8(e + 6);
        const uint32_t usage_index = v3_r8(e + 7);
        if (stream != 0)
        {
            continue;
        }
        switch (usage)
        {
        case 0: /* POSITION */
            l->position = type == 3 ? 4 : 3;
            l->position_offset = offset;
            break;
        case 9: /* POSITIONT */
            l->position = 4;
            l->position_offset = offset;
            break;
        case 3: /* NORMAL */
            l->normal = 1;
            l->normal_offset = offset;
            break;
        case 10: /* COLOR */
            if (usage_index == 0)
            {
                l->diffuse = 1;
                l->diffuse_offset = offset;
            }
            else
            {
                l->specular = 1;
                l->specular_offset = offset;
            }
            break;
        case 5: /* TEXCOORD */
            if (usage_index < 2)
            {
                l->texture_offset[usage_index] = offset;
                if (l->texture_sets < usage_index + 1)
                {
                    l->texture_sets = usage_index + 1;
                }
            }
            break;
        default:
            break;
        }
    }
    l->stride = 0;
    return l->position != 0;
}

static void decode_vertex(const Layout *l, uint32_t at, V3Vertex *v)
{
    v->x = f32(v3_r32(at + l->position_offset));
    v->y = f32(v3_r32(at + l->position_offset + 4));
    v->z = f32(v3_r32(at + l->position_offset + 8));
    v->w = l->position == 4 ? f32(v3_r32(at + l->position_offset + 12)) : 1.0f;
    if (l->normal)
    {
        v->nx = f32(v3_r32(at + l->normal_offset));
        v->ny = f32(v3_r32(at + l->normal_offset + 4));
        v->nz = f32(v3_r32(at + l->normal_offset + 8));
    }
    v->diffuse = l->diffuse ? v3_r32(at + l->diffuse_offset) : 0xffffffffu;
    v->specular = l->specular ? v3_r32(at + l->specular_offset) : 0;
    for (unsigned i = 0; i < 2; ++i)
    {
        if (i < l->texture_sets)
        {
            v->u[i] = f32(v3_r32(at + l->texture_offset[i]));
            v->v[i] = f32(v3_r32(at + l->texture_offset[i] + 4));
        }
        else
        {
            v->u[i] = v->v[i] = 0.0f;
        }
    }
}

static uint32_t vertex_count_of(uint32_t primitive, uint32_t count)
{
    switch (primitive)
    {
    case 1:
        return count;
    case 2:
        return 2 * count;
    case 3:
        return count + 1;
    case 4:
        return 3 * count;
    case 5:
    case 6:
        return count + 2;
    default:
        return 0;
    }
}

static int current_layout(Layout *l, uint32_t stride)
{
    int ok = device.s.declaration ? layout_from_declaration(device.s.declaration, l)
                                  : layout_from_fvf(device.s.fvf, l);
    if (ok && stride)
    {
        l->stride = stride;
    }
    return ok && l->stride;
}

static V3Vertex *vertex_room(uint32_t n)
{
    if (n > device.vertex_capacity)
    {
        device.vertex_capacity = n + 1024;
        device.vertices = v3_grow(device.vertices, device.vertex_capacity * sizeof(V3Vertex),
                                  "the vertex buffer");
    }
    return device.vertices;
}

static uint32_t *index_room(uint32_t n)
{
    if (n > device.index_capacity)
    {
        device.index_capacity = n + 1024;
        device.indices = v3_grow(device.indices, device.index_capacity * sizeof(uint32_t),
                                 "the index buffer");
    }
    return device.indices;
}

static void submit(uint32_t primitive, const Layout *l, uint32_t vertex_count,
                   const uint32_t *indices, uint32_t index_count)
{
    V3Draw draw = {primitive,         device.vertices, vertex_count, indices, index_count,
                   l->position == 4, l->normal,       l->diffuse,   l->specular,
                   l->texture_sets};
    ++device.draws;
    if (v3_trace_calls)
    {
        const V3RenderState *r = &device.s.r;
        for (uint32_t i = 0; i < vertex_count && i < 4; ++i)
        {
            const V3Vertex *v = &device.vertices[indices ? indices[i] : i];
            v3_log("  vertex %u: %g %g %g %g uv %g %g diffuse %08x", i, v->x, v->y, v->z, v->w,
                   v->u[0], v->v[0], v->diffuse);
        }
        for (int m = 0; m < 3; ++m)
        {
            const float *t = m == 0 ? r->world : m == 1 ? r->view : r->projection;
            v3_log("  %s: %g %g %g %g / %g %g %g %g / %g %g %g %g / %g %g %g %g",
                   m == 0 ? "world" : m == 1 ? "view" : "projection", t[0], t[1], t[2], t[3], t[4],
                   t[5], t[6], t[7], t[8], t[9], t[10], t[11], t[12], t[13], t[14], t[15]);
        }
        v3_log("  viewport %u %u %u %u; texture %p", r->viewport.x, r->viewport.y,
               r->viewport.width, r->viewport.height, (void *)r->texture[0]);
        if (r->texture[0])
        {
            const V3Texture *t = r->texture[0];
            v3_log("  texture %ux%u format %u texels %08x %08x %08x", t->width, t->height,
                   t->format, v3_r32(t->pixels), v3_r32(t->pixels + t->pitch * (t->height / 2) + 2 * t->width),
                   v3_r32(t->pixels + 4 * 7));
        }
    }
    static int stats = -1;
    if (stats < 0)
    {
        stats = getenv("V3_STATS") != NULL;
    }
    if (stats)
    {
        /* Each distinct combination of the states a renderer has to honour, once. */
        const V3RenderState *r = &device.s.r;
        const uint32_t *rs = r->render;
        char line[512];
        int n = snprintf(line, sizeof line,
                         "pre %d lit %u z %u/%u/%u cull %u blend %u %u/%u op %u atest %u/%u/%u "
                         "fog %u stencil %u/%u ops %u/%u/%u ref %u/%x/%x mask %x spec %u tf %08x",
                         l->position == 4, rs[137], rs[7], rs[14], rs[23], rs[22], rs[27], rs[19],
                         rs[20], rs[171], rs[15], rs[25], rs[24], rs[28], rs[52], rs[56], rs[53],
                         rs[54], rs[55], rs[57], rs[58], rs[59], rs[168],
                         rs[29], rs[60] == 0xffffffffu ? 1u : 0u);
        for (unsigned k = 0; k < V3_MAX_STAGES && r->stage[k][1] != 1; ++k)
        {
            const uint32_t *ts = r->stage[k];
            n += snprintf(line + n, sizeof line - (size_t)n,
                          " | c%u(%x,%x) a%u(%x,%x) r%u ti%x tex%u fmt%u adr%u/%u f%u", ts[1],
                          ts[2], ts[3], ts[4], ts[5], ts[6], ts[28], ts[11],
                          r->texture[k] != NULL, r->texture[k] ? r->texture[k]->format : 0,
                          r->sampler[k][1], r->sampler[k][2], r->sampler[k][5]);
        }
        static char *seen[512];
        static unsigned seen_count;
        unsigned i = 0;
        while (i < seen_count && strcmp(seen[i], line) != 0)
        {
            ++i;
        }
        if (i == seen_count && seen_count < 512)
        {
            seen[seen_count++] = strdup(line);
            v3_log("state %s", line);
        }
    }
    renderer->draw(renderer, &device.s.r, &draw);
}

static void Dev_DrawPrimitive(Cpu *c)
{
    const uint32_t primitive = ARG(1), start = ARG(2), count = ARG(3);
    Layout l;
    Object *vb = object_of(device.s.stream);
    if (vb && current_layout(&l, device.s.stream_stride))
    {
        const uint32_t n = vertex_count_of(primitive, count);
        V3Vertex *v = vertex_room(n);
        const uint32_t base = vb->u.buffer.data + device.s.stream_offset;
        for (uint32_t i = 0; i < n; ++i)
        {
            decode_vertex(&l, base + (start + i) * l.stride, &v[i]);
        }
        submit(primitive, &l, n, NULL, 0);
    }
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_DrawIndexedPrimitive(Cpu *c)
{
    const uint32_t primitive = ARG(1);
    const int32_t base_vertex = (int32_t)ARG(2);
    const uint32_t min_index = ARG(3), vertices = ARG(4), start = ARG(5), count = ARG(6);
    Layout l;
    Object *vb = object_of(device.s.stream);
    Object *ib = object_of(device.s.indices);
    if (vb && ib && current_layout(&l, device.s.stream_stride))
    {
        V3Vertex *v = vertex_room(min_index + vertices);
        const uint32_t base = vb->u.buffer.data + device.s.stream_offset;
        for (uint32_t i = min_index; i < min_index + vertices; ++i)
        {
            decode_vertex(&l, base + (uint32_t)((int32_t)i + base_vertex) * l.stride, &v[i]);
        }
        const uint32_t n = vertex_count_of(primitive, count);
        uint32_t *idx = index_room(n);
        const int wide = ib->u.buffer.format == 102;
        for (uint32_t i = 0; i < n; ++i)
        {
            idx[i] = wide ? v3_r32(ib->u.buffer.data + 4 * (start + i))
                          : v3_r16(ib->u.buffer.data + 2 * (start + i));
            if (idx[i] >= min_index + vertices)
            {
                idx[i] = min_index;
            }
        }
        submit(primitive, &l, min_index + vertices, idx, n);
    }
    STDCALL_RETURN(7, D3D_OK);
}

static void Dev_DrawPrimitiveUP(Cpu *c)
{
    const uint32_t primitive = ARG(1), count = ARG(2), data = ARG(3), stride = ARG(4);
    Layout l;
    if (current_layout(&l, stride))
    {
        const uint32_t n = vertex_count_of(primitive, count);
        V3Vertex *v = vertex_room(n);
        for (uint32_t i = 0; i < n; ++i)
        {
            decode_vertex(&l, data + i * l.stride, &v[i]);
        }
        submit(primitive, &l, n, NULL, 0);
    }
    /* Afterwards stream 0 is unset, as on Windows. */
    device.s.stream = 0;
    STDCALL_RETURN(5, D3D_OK);
}

static void Dev_DrawIndexedPrimitiveUP(Cpu *c)
{
    const uint32_t primitive = ARG(1), min_index = ARG(2), vertices = ARG(3), count = ARG(4);
    const uint32_t index_data = ARG(5), format = ARG(6), data = ARG(7), stride = ARG(8);
    Layout l;
    if (current_layout(&l, stride))
    {
        V3Vertex *v = vertex_room(min_index + vertices);
        for (uint32_t i = min_index; i < min_index + vertices; ++i)
        {
            decode_vertex(&l, data + i * l.stride, &v[i]);
        }
        const uint32_t n = vertex_count_of(primitive, count);
        uint32_t *idx = index_room(n);
        for (uint32_t i = 0; i < n; ++i)
        {
            idx[i] = format == 102 ? v3_r32(index_data + 4 * i) : v3_r16(index_data + 2 * i);
            if (idx[i] >= min_index + vertices)
            {
                idx[i] = min_index;
            }
        }
        submit(primitive, &l, min_index + vertices, idx, n);
    }
    device.s.stream = 0;
    device.s.indices = 0;
    STDCALL_RETURN(9, D3D_OK);
}

static void Dev_CreateVertexDeclaration(Cpu *c)
{
    const uint32_t elements = ARG(1);
    uint32_t n = 0;
    while (v3_r16(elements + 8 * n) != 0xff && n < 64)
    {
        ++n;
    }
    Object *d = object_new(KIND_DECLARATION);
    d->u.declaration.count = n;
    d->u.declaration.elements = v3_alloc(8 * (n + 1));
    memcpy(MEM(d->u.declaration.elements), MEM(elements), 8 * (n + 1));
    v3_w32(ARG(2), d->guest);
    STDCALL_RETURN(3, D3D_OK);
}

static void Decl_GetDeclaration(Cpu *c)
{
    Object *d = object_of(ARG(0));
    if (ARG(2))
    {
        v3_w32(ARG(2), d->u.declaration.count + 1);
    }
    if (ARG(1))
    {
        memcpy(MEM(ARG(1)), MEM(d->u.declaration.elements), 8 * (d->u.declaration.count + 1));
    }
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetVertexDeclaration(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    d->declaration = ARG(1);
    if (ARG(1))
    {
        d->fvf = 0;
    }
    MARK(declaration);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetVertexDeclaration(Cpu *c)
{
    v3_w32(ARG(1), device.s.declaration);
    if (device.s.declaration)
    {
        ++object_of(device.s.declaration)->refs;
    }
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetFVF(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    d->fvf = ARG(1);
    if (ARG(1))
    {
        d->declaration = 0;
    }
    MARK(fvf);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetFVF(Cpu *c)
{
    v3_w32(ARG(1), device.s.fvf);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetVertexShader(Cpu *c)
{
    if (ARG(1))
    {
        v3_log("SetVertexShader(%08x) ignored", ARG(1));
    }
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetShader(Cpu *c)
{
    v3_w32(ARG(1), 0);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetPixelShader(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_SetShaderConstant(Cpu *c)
{
    STDCALL_RETURN(4, D3D_OK);
}

static void Dev_SetStreamSource(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    if (ARG(1) == 0)
    {
        d->stream = ARG(2);
        d->stream_offset = ARG(3);
        d->stream_stride = ARG(4);
        MARK(stream);
    }
    STDCALL_RETURN(5, D3D_OK);
}

static void Dev_GetStreamSource(Cpu *c)
{
    v3_w32(ARG(2), device.s.stream);
    if (device.s.stream)
    {
        ++object_of(device.s.stream)->refs;
    }
    v3_w32(ARG(3), device.s.stream_offset);
    v3_w32(ARG(4), device.s.stream_stride);
    STDCALL_RETURN(5, D3D_OK);
}

static void Dev_SetStreamSourceFreq(Cpu *c)
{
    STDCALL_RETURN(3, D3D_OK);
}

static void Dev_SetIndices(Cpu *c)
{
    StateMask *mask;
    DeviceState *d = target(&mask);
    d->indices = ARG(1);
    MARK(indices);
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_GetIndices(Cpu *c)
{
    v3_w32(ARG(1), device.s.indices);
    if (device.s.indices)
    {
        ++object_of(device.s.indices)->refs;
    }
    STDCALL_RETURN(2, D3D_OK);
}

static void Dev_CreateQuery(Cpu *c)
{
    if (ARG(2))
    {
        v3_w32(ARG(2), 0);
    }
    STDCALL_RETURN(3, D3DERR_NOTAVAILABLE);
}

static const Method DEVICE_METHODS[] = {
    {0, "QueryInterface", QueryInterface},
    {1, "AddRef", AddRef},
    {2, "Release", Release},
    {3, "TestCooperativeLevel", Dev_TestCooperativeLevel},
    {4, "GetAvailableTextureMem", Dev_GetAvailableTextureMem},
    {5, "EvictManagedResources", Dev_EvictManagedResources},
    {6, "GetDirect3D", Dev_GetDirect3D},
    {7, "GetDeviceCaps", Dev_GetDeviceCaps},
    {8, "GetDisplayMode", Dev_GetDisplayMode},
    {9, "GetCreationParameters", Dev_GetCreationParameters},
    {10, "SetCursorProperties", Dev_SetCursorProperties},
    {11, "SetCursorPosition", Dev_SetCursorPosition},
    {12, "ShowCursor", Dev_ShowCursor},
    {14, "GetSwapChain", Dev_GetSwapChain},
    {15, "GetNumberOfSwapChains", Dev_GetNumberOfSwapChains},
    {16, "Reset", Dev_Reset},
    {17, "Present", Dev_Present},
    {18, "GetBackBuffer", Dev_GetBackBuffer},
    {19, "GetRasterStatus", Dev_GetRasterStatus},
    {20, "SetDialogBoxMode", Dev_SetDialogBoxMode},
    {21, "SetGammaRamp", Dev_SetGammaRamp},
    {22, "GetGammaRamp", Dev_GetGammaRamp},
    {23, "CreateTexture", Dev_CreateTexture},
    {26, "CreateVertexBuffer", Dev_CreateVertexBuffer},
    {27, "CreateIndexBuffer", Dev_CreateIndexBuffer},
    {28, "CreateRenderTarget", Dev_CreateRenderTarget},
    {29, "CreateDepthStencilSurface", Dev_CreateDepthStencilSurface},
    {31, "UpdateTexture", Dev_UpdateTexture},
    {32, "GetRenderTargetData", Dev_GetRenderTargetData},
    {33, "GetFrontBufferData", Dev_GetFrontBufferData},
    {34, "StretchRect", Dev_StretchRect},
    {35, "ColorFill", Dev_ColorFill},
    {36, "CreateOffscreenPlainSurface", Dev_CreateOffscreenPlainSurface},
    {37, "SetRenderTarget", Dev_SetRenderTarget},
    {38, "GetRenderTarget", Dev_GetRenderTarget},
    {39, "SetDepthStencilSurface", Dev_SetDepthStencilSurface},
    {40, "GetDepthStencilSurface", Dev_GetDepthStencilSurface},
    {41, "BeginScene", Dev_BeginScene},
    {42, "EndScene", Dev_EndScene},
    {43, "Clear", Dev_Clear},
    {44, "SetTransform", Dev_SetTransform},
    {45, "GetTransform", Dev_GetTransform},
    {46, "MultiplyTransform", Dev_MultiplyTransform},
    {47, "SetViewport", Dev_SetViewport},
    {48, "GetViewport", Dev_GetViewport},
    {49, "SetMaterial", Dev_SetMaterial},
    {50, "GetMaterial", Dev_GetMaterial},
    {51, "SetLight", Dev_SetLight},
    {53, "LightEnable", Dev_LightEnable},
    {54, "GetLightEnable", Dev_GetLightEnable},
    {55, "SetClipPlane", Dev_SetClipPlane},
    {57, "SetRenderState", Dev_SetRenderState},
    {58, "GetRenderState", Dev_GetRenderState},
    {59, "CreateStateBlock", Dev_CreateStateBlock},
    {60, "BeginStateBlock", Dev_BeginStateBlock},
    {61, "EndStateBlock", Dev_EndStateBlock},
    {64, "GetTexture", Dev_GetTexture},
    {65, "SetTexture", Dev_SetTexture},
    {66, "GetTextureStageState", Dev_GetTextureStageState},
    {67, "SetTextureStageState", Dev_SetTextureStageState},
    {68, "GetSamplerState", Dev_GetSamplerState},
    {69, "SetSamplerState", Dev_SetSamplerState},
    {70, "ValidateDevice", Dev_ValidateDevice},
    {75, "SetScissorRect", Dev_SetScissorRect},
    {76, "GetScissorRect", Dev_GetScissorRect},
    {77, "SetSoftwareVertexProcessing", Dev_SetSoftwareVertexProcessing},
    {78, "GetSoftwareVertexProcessing", Dev_GetSoftwareVertexProcessing},
    {79, "SetNPatchMode", Dev_SetNPatchMode},
    {80, "GetNPatchMode", Dev_GetNPatchMode},
    {81, "DrawPrimitive", Dev_DrawPrimitive},
    {82, "DrawIndexedPrimitive", Dev_DrawIndexedPrimitive},
    {83, "DrawPrimitiveUP", Dev_DrawPrimitiveUP},
    {84, "DrawIndexedPrimitiveUP", Dev_DrawIndexedPrimitiveUP},
    {86, "CreateVertexDeclaration", Dev_CreateVertexDeclaration},
    {87, "SetVertexDeclaration", Dev_SetVertexDeclaration},
    {88, "GetVertexDeclaration", Dev_GetVertexDeclaration},
    {89, "SetFVF", Dev_SetFVF},
    {90, "GetFVF", Dev_GetFVF},
    {92, "SetVertexShader", Dev_SetVertexShader},
    {93, "GetVertexShader", Dev_GetShader},
    {94, "SetVertexShaderConstantF", Dev_SetShaderConstant},
    {96, "SetVertexShaderConstantI", Dev_SetShaderConstant},
    {98, "SetVertexShaderConstantB", Dev_SetShaderConstant},
    {100, "SetStreamSource", Dev_SetStreamSource},
    {101, "GetStreamSource", Dev_GetStreamSource},
    {102, "SetStreamSourceFreq", Dev_SetStreamSourceFreq},
    {104, "SetIndices", Dev_SetIndices},
    {105, "GetIndices", Dev_GetIndices},
    {107, "SetPixelShader", Dev_SetPixelShader},
    {108, "GetPixelShader", Dev_GetShader},
    {109, "SetPixelShaderConstantF", Dev_SetShaderConstant},
    {111, "SetPixelShaderConstantI", Dev_SetShaderConstant},
    {113, "SetPixelShaderConstantB", Dev_SetShaderConstant},
    {118, "CreateQuery", Dev_CreateQuery},
    {0, NULL, NULL}};

/* --- textures and surfaces -------------------------------------------------------------------- */

static void Res_SetPrivateData(Cpu *c)
{
    STDCALL_RETURN(5, D3D_OK);
}

static void Res_GetPrivateData(Cpu *c)
{
    STDCALL_RETURN(4, 0x88760866u); /* D3DERR_NOTFOUND */
}

static void Res_FreePrivateData(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Res_SetPriority(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void Res_GetPriority(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void Res_PreLoad(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void Tex_GetType(Cpu *c)
{
    STDCALL_RETURN(1, 3); /* D3DRTYPE_TEXTURE */
}

static void Tex_SetLOD(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void Tex_GetLOD(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void Tex_GetLevelCount(Cpu *c)
{
    Object *t = object_of(ARG(0));
    STDCALL_RETURN(1, t ? t->u.texture.level_count : 1);
}

static void Tex_SetAutoGenFilterType(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static void Tex_GetAutoGenFilterType(Cpu *c)
{
    STDCALL_RETURN(1, 2);
}

static void Tex_GenerateMipSubLevels(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void level_desc(const V3Texture *level, uint32_t usage, uint32_t pool, uint32_t desc)
{
    v3_w32(desc, level->format);
    v3_w32(desc + 4, 3); /* D3DRTYPE_SURFACE */
    v3_w32(desc + 8, usage);
    v3_w32(desc + 12, pool);
    v3_w32(desc + 16, 0);
    v3_w32(desc + 20, 0);
    v3_w32(desc + 24, level->width);
    v3_w32(desc + 28, level->height);
}

static void Tex_GetLevelDesc(Cpu *c)
{
    Object *t = object_of(ARG(0));
    const uint32_t l = ARG(1);
    if (!t || l >= t->u.texture.level_count)
    {
        STDCALL_RETURN(3, D3DERR_INVALIDCALL);
    }
    level_desc(&t->u.texture.levels[l], t->u.texture.usage, t->u.texture.pool, ARG(2));
    STDCALL_RETURN(3, D3D_OK);
}

static uint32_t texture_surface(Object *t, uint32_t l)
{
    if (!t->u.texture.surfaces[l])
    {
        Object *s = object_new(KIND_SURFACE);
        const V3Texture *level = &t->u.texture.levels[l];
        s->u.surface.texture = index_of(t);
        s->u.surface.level = l;
        s->u.surface.width = level->width;
        s->u.surface.height = level->height;
        s->u.surface.format = level->format;
        s->u.surface.pitch = level->pitch;
        s->u.surface.pixels = level->pixels;
        s->refs = 0;
        t->u.texture.surfaces[l] = s->guest;
    }
    return t->u.texture.surfaces[l];
}

static void Tex_GetSurfaceLevel(Cpu *c)
{
    Object *t = object_of(ARG(0));
    const uint32_t l = ARG(1);
    if (!t || l >= t->u.texture.level_count)
    {
        STDCALL_RETURN(3, D3DERR_INVALIDCALL);
    }
    const uint32_t s = texture_surface(t, l);
    ++object_of(s)->refs;
    ++t->refs;
    v3_w32(ARG(2), s);
    STDCALL_RETURN(3, D3D_OK);
}

static void lock_rect(uint32_t pixels, uint32_t pitch, uint32_t format, uint32_t locked, uint32_t rect)
{
    uint32_t at = pixels;
    if (rect)
    {
        at += v3_r32(rect + 4) * pitch + v3_r32(rect) * v3_format_bytes(format);
    }
    v3_w32(locked, pitch);
    v3_w32(locked + 4, at);
}

static void Tex_LockRect(Cpu *c)
{
    Object *t = object_of(ARG(0));
    const uint32_t l = ARG(1);
    if (!t || l >= t->u.texture.level_count)
    {
        STDCALL_RETURN(5, D3DERR_INVALIDCALL);
    }
    const V3Texture *level = &t->u.texture.levels[l];
    lock_rect(level->pixels, level->pitch, level->format, ARG(2), ARG(3));
    STDCALL_RETURN(5, D3D_OK);
}

static void texture_changed(Object *t, uint32_t l)
{
    V3Texture *level = &t->u.texture.levels[l];
    ++level->generation;
    if (renderer->texture_changed)
    {
        renderer->texture_changed(renderer, level);
    }
}

static void Tex_UnlockRect(Cpu *c)
{
    Object *t = object_of(ARG(0));
    if (t && ARG(1) < t->u.texture.level_count)
    {
        texture_changed(t, ARG(1));
    }
    STDCALL_RETURN(2, D3D_OK);
}

static void Tex_AddDirtyRect(Cpu *c)
{
    STDCALL_RETURN(2, D3D_OK);
}

static const Method TEXTURE_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                         {1, "AddRef", AddRef},
                                         {2, "Release", Release},
                                         {3, "GetDevice", GetDevice},
                                         {4, "SetPrivateData", Res_SetPrivateData},
                                         {5, "GetPrivateData", Res_GetPrivateData},
                                         {6, "FreePrivateData", Res_FreePrivateData},
                                         {7, "SetPriority", Res_SetPriority},
                                         {8, "GetPriority", Res_GetPriority},
                                         {9, "PreLoad", Res_PreLoad},
                                         {10, "GetType", Tex_GetType},
                                         {11, "SetLOD", Tex_SetLOD},
                                         {12, "GetLOD", Tex_GetLOD},
                                         {13, "GetLevelCount", Tex_GetLevelCount},
                                         {14, "SetAutoGenFilterType", Tex_SetAutoGenFilterType},
                                         {15, "GetAutoGenFilterType", Tex_GetAutoGenFilterType},
                                         {16, "GenerateMipSubLevels", Tex_GenerateMipSubLevels},
                                         {17, "GetLevelDesc", Tex_GetLevelDesc},
                                         {18, "GetSurfaceLevel", Tex_GetSurfaceLevel},
                                         {19, "LockRect", Tex_LockRect},
                                         {20, "UnlockRect", Tex_UnlockRect},
                                         {21, "AddDirtyRect", Tex_AddDirtyRect},
                                         {0, NULL, NULL}};

static void Surf_GetType(Cpu *c)
{
    STDCALL_RETURN(1, 1); /* D3DRTYPE_SURFACE */
}

static void Surf_GetContainer(Cpu *c)
{
    Object *s = object_of(ARG(0));
    if (s && s->u.surface.texture && objects[s->u.surface.texture])
    {
        Object *t = objects[s->u.surface.texture];
        ++t->refs;
        v3_w32(ARG(2), t->guest);
        STDCALL_RETURN(3, D3D_OK);
    }
    v3_w32(ARG(2), device.guest);
    STDCALL_RETURN(3, D3D_OK);
}

static void Surf_GetDesc(Cpu *c)
{
    Object *s = object_of(ARG(0));
    const uint32_t desc = ARG(1);
    v3_w32(desc, s->u.surface.format);
    v3_w32(desc + 4, 1);
    v3_w32(desc + 8, s->u.surface.back_buffer ? 1u : 0u);
    v3_w32(desc + 12, s->u.surface.texture ? objects[s->u.surface.texture]->u.texture.pool : 2u);
    v3_w32(desc + 16, 0);
    v3_w32(desc + 20, 0);
    v3_w32(desc + 24, s->u.surface.width);
    v3_w32(desc + 28, s->u.surface.height);
    STDCALL_RETURN(2, D3D_OK);
}

static void Surf_LockRect(Cpu *c)
{
    Object *s = object_of(ARG(0));
    if (!s || !s->u.surface.pixels)
    {
        v3_log("LockRect on a surface without memory (back buffer %d)",
               s ? s->u.surface.back_buffer : -1);
        STDCALL_RETURN(4, D3DERR_INVALIDCALL);
    }
    lock_rect(s->u.surface.pixels, s->u.surface.pitch, s->u.surface.format, ARG(1), ARG(2));
    STDCALL_RETURN(4, D3D_OK);
}

static void Surf_UnlockRect(Cpu *c)
{
    Object *s = object_of(ARG(0));
    if (s && s->u.surface.texture && objects[s->u.surface.texture])
    {
        texture_changed(objects[s->u.surface.texture], s->u.surface.level);
    }
    STDCALL_RETURN(1, D3D_OK);
}

static void Surf_Release(Cpu *c)
{
    /* A texture level's surface also holds its texture. */
    Object *s = object_of(ARG(0));
    if (s && s->u.surface.texture && objects[s->u.surface.texture])
    {
        Object *t = objects[s->u.surface.texture];
        --s->refs;
        if (--t->refs <= 0)
        {
            release_object(t);
        }
        STDCALL_RETURN(1, (uint32_t)(s->refs < 0 ? 0 : s->refs));
    }
    Release(c);
}

static void Surf_GetDC(Cpu *c)
{
    STDCALL_RETURN(2, D3DERR_INVALIDCALL);
}

static const Method SURFACE_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                         {1, "AddRef", AddRef},
                                         {2, "Release", Surf_Release},
                                         {3, "GetDevice", GetDevice},
                                         {4, "SetPrivateData", Res_SetPrivateData},
                                         {5, "GetPrivateData", Res_GetPrivateData},
                                         {6, "FreePrivateData", Res_FreePrivateData},
                                         {7, "SetPriority", Res_SetPriority},
                                         {8, "GetPriority", Res_GetPriority},
                                         {9, "PreLoad", Res_PreLoad},
                                         {10, "GetType", Surf_GetType},
                                         {11, "GetContainer", Surf_GetContainer},
                                         {12, "GetDesc", Surf_GetDesc},
                                         {13, "LockRect", Surf_LockRect},
                                         {14, "UnlockRect", Surf_UnlockRect},
                                         {15, "GetDC", Surf_GetDC},
                                         {0, NULL, NULL}};

/* --- buffers ----------------------------------------------------------------------------------- */

static void Buf_GetType(Cpu *c)
{
    Object *b = object_of(ARG(0));
    STDCALL_RETURN(1, b && b->kind == KIND_INDEX_BUFFER ? 7 : 6);
}

static void Buf_Lock(Cpu *c)
{
    Object *b = object_of(ARG(0));
    v3_w32(ARG(3), b->u.buffer.data + ARG(1));
    STDCALL_RETURN(5, D3D_OK);
}

static void Buf_Unlock(Cpu *c)
{
    STDCALL_RETURN(1, D3D_OK);
}

static void Buf_GetDesc(Cpu *c)
{
    Object *b = object_of(ARG(0));
    const uint32_t desc = ARG(1);
    if (b->kind == KIND_VERTEX_BUFFER)
    {
        v3_w32(desc, 100); /* D3DFMT_VERTEXDATA */
        v3_w32(desc + 4, 6);
        v3_w32(desc + 8, b->u.buffer.usage);
        v3_w32(desc + 12, 0);
        v3_w32(desc + 16, b->u.buffer.size);
        v3_w32(desc + 20, b->u.buffer.fvf);
    }
    else
    {
        v3_w32(desc, b->u.buffer.format);
        v3_w32(desc + 4, 7);
        v3_w32(desc + 8, b->u.buffer.usage);
        v3_w32(desc + 12, 0);
        v3_w32(desc + 16, b->u.buffer.size);
    }
    STDCALL_RETURN(2, D3D_OK);
}

static const Method BUFFER_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                        {1, "AddRef", AddRef},
                                        {2, "Release", Release},
                                        {3, "GetDevice", GetDevice},
                                        {4, "SetPrivateData", Res_SetPrivateData},
                                        {5, "GetPrivateData", Res_GetPrivateData},
                                        {6, "FreePrivateData", Res_FreePrivateData},
                                        {7, "SetPriority", Res_SetPriority},
                                        {8, "GetPriority", Res_GetPriority},
                                        {9, "PreLoad", Res_PreLoad},
                                        {10, "GetType", Buf_GetType},
                                        {11, "Lock", Buf_Lock},
                                        {12, "Unlock", Buf_Unlock},
                                        {13, "GetDesc", Buf_GetDesc},
                                        {0, NULL, NULL}};

static const Method DECLARATION_METHODS[] = {{0, "QueryInterface", QueryInterface},
                                             {1, "AddRef", AddRef},
                                             {2, "Release", Release},
                                             {3, "GetDevice", GetDevice},
                                             {4, "GetDeclaration", Decl_GetDeclaration},
                                             {0, NULL, NULL}};

/* --- creation ------------------------------------------------------------------------------- */

static void make_vtables(void)
{
    if (vtables[KIND_D3D])
    {
        return;
    }
    vtables[KIND_D3D] = make_vtable("IDirect3D9", 17, D3D_METHODS);
    vtables[KIND_DEVICE] = make_vtable("IDirect3DDevice9", 119, DEVICE_METHODS);
    vtables[KIND_TEXTURE] = make_vtable("IDirect3DTexture9", 22, TEXTURE_METHODS);
    vtables[KIND_SURFACE] = make_vtable("IDirect3DSurface9", 17, SURFACE_METHODS);
    vtables[KIND_VERTEX_BUFFER] = make_vtable("IDirect3DVertexBuffer9", 14, BUFFER_METHODS);
    vtables[KIND_INDEX_BUFFER] = make_vtable("IDirect3DIndexBuffer9", 14, BUFFER_METHODS);
    vtables[KIND_STATE_BLOCK] = make_vtable("IDirect3DStateBlock9", 6, BLOCK_METHODS);
    vtables[KIND_SWAP_CHAIN] = make_vtable("IDirect3DSwapChain9", 10, SWAP_CHAIN_METHODS);
    vtables[KIND_DECLARATION] =
        make_vtable("IDirect3DVertexDeclaration9", 5, DECLARATION_METHODS);
}

static void Direct3DCreate9(Cpu *c)
{
    v3_log("Direct3DCreate9(%u)", ARG(0));
    make_vtables();
    if (!d3d_object)
    {
        d3d_object = object_new(KIND_D3D)->guest;
    }
    STDCALL_RETURN(1, d3d_object);
}

const V3Export v3_d3d9[] = {{"Direct3DCreate9", Direct3DCreate9}, {NULL, NULL}};

/* The Direct3D 9 fixed-function pipeline on the Wii's GX. Vertices go through the same CPU stage
 * as the reference renderer (render_vertex.h: transform, lighting, near clip, culling); GX
 * rasterizes them from clip space with a perspective projection, so colors and texture
 * coordinates interpolate perspective-correctly, and the texture stages become TEV stages.
 *
 * Mapping, in Direct3D's terms:
 * - Positions: GX gets (cx, cy, -cw); its projection keeps x and y and divides by w. Direct3D's
 *   pixel centers are integers, GX's are halves, so the viewport is shifted by half a pixel.
 * - Depth (when enabled): within a draw, z = a + b / w for any perspective or affine
 *   projection; a and b are fitted from the vertices and become the projection's z row.
 * - Texture stages: arguments DIFFUSE (rasterized color), CURRENT (TEVPREV), TEXTURE, TFACTOR
 *   (konstant color 0) and TEMP (TEVREG2); every operation the game's states use, plus the
 *   other blends and lerps, maps onto TEV's d + lerp(a, b, c). COMPLEMENT and SPECULAR, which
 *   the game never selects, read as the plain argument and as zero.
 * - Blending: GX's factors; a reverse subtraction (dst - src * srcalpha) premultiplies the
 *   source in a last stage, as GX's subtract ignores factors.
 * - Stencil: GX has none, but the game never enables depth, so the depth buffer holds the
 *   stencil. A value v is the constant depth -stencil_depth(v) (the projection's z row with
 *   b = 0, so it interpolates exactly); the stencil clear writes it, REPLACE on pass is a depth
 *   write, and the stencil function is the depth function, both comparing ref against the
 *   buffer. Other operations, or stencil with depth on, are logged once and drawn unmasked.
 * - Not modelled (the game never enables them): fog, the color write mask, specular. */

#include "render_vertex.h"
#include "runtime.h"

#include <gccore.h>
#include <malloc.h>
#include <string.h>

typedef struct GxTexture
{
    uint32_t generation;
    uint32_t width, height;
    void *data;
    GXTexObj object;
    uint32_t used; /* the draw that last bound it */
    struct GxTexture *prev, *next;
} GxTexture;

/* Every texture's GX copy, so that one can be dropped when memory runs out: the game's own copy
 * stays in guest memory and is converted again on its next use. */
static GxTexture *textures;
static uint32_t draw_clock;

typedef struct
{
    V3Renderer base;
    uint32_t width, height;
    Out *out;
    uint32_t out_capacity;
    const Out **tris; /* the clipped, culled triangles of one draw */
    Out *clipped;     /* storage for clipped vertices */
    uint32_t tri_capacity;
} Gx;

static int pow2(uint32_t v)
{
    return v && !(v & (v - 1));
}

/* --- textures ----------------------------------------------------------------------------- */

/* A8R8G8B8 (or any format v3_texel reads) into GX's RGBA8: 4x4 tiles of 16 AR pairs, then 16 GB
 * pairs. */
static void convert(const V3Texture *t, uint8_t *dst)
{
    const uint32_t w = t->width, h = t->height;
    const int direct = t->format == V3_FMT_A8R8G8B8 || t->format == V3_FMT_X8R8G8B8;
    const uint8_t opaque = t->format == V3_FMT_X8R8G8B8 ? 0xff : 0x00;
    for (uint32_t ty = 0; ty < h; ty += 4)
    {
        for (uint32_t tx = 0; tx < w; tx += 4)
        {
            uint8_t *ar = dst;
            uint8_t *gb = dst + 32;
            for (uint32_t y = ty; y < ty + 4; ++y)
            {
                for (uint32_t x = tx; x < tx + 4; ++x)
                {
                    uint32_t c = 0;
                    if (x < w && y < h)
                    {
                        if (direct)
                        {
                            const uint8_t *p = MEM(t->pixels + y * t->pitch + 4 * x);
                            c = (uint32_t)(p[3] | opaque) << 24 | (uint32_t)p[2] << 16 |
                                (uint32_t)p[1] << 8 | p[0];
                        }
                        else
                        {
                            c = v3_texel(t, x, y);
                        }
                    }
                    *ar++ = (uint8_t)(c >> 24);
                    *ar++ = (uint8_t)(c >> 16);
                    *gb++ = (uint8_t)(c >> 8);
                    *gb++ = (uint8_t)c;
                }
            }
            dst += 64;
        }
    }
}

/* Texel memory; when there is none left, the GX copies of the textures least recently used
 * (never one bound for the draw being set up) make room. */
static void *alloc_texels(size_t size)
{
    void *p = memalign(32, size);
    if (p)
    {
        return p;
    }
    GX_DrawDone(); /* nothing drawn so far reads them any more */
    for (;;)
    {
        GxTexture *oldest = NULL;
        for (GxTexture *g = textures; g; g = g->next)
        {
            if (g->data && g->used != draw_clock && (!oldest || g->used < oldest->used))
            {
                oldest = g;
            }
        }
        if (!oldest)
        {
            return NULL;
        }
        free(oldest->data);
        oldest->data = NULL;
        if ((p = memalign(32, size)) != NULL)
        {
            return p;
        }
    }
}

static GxTexture *upload(V3Texture *t)
{
    GxTexture *g = t->backend;
    if (g && g->data && g->generation == t->generation && g->width == t->width &&
        g->height == t->height)
    {
        return g;
    }
    if (!g)
    {
        g = calloc(1, sizeof *g);
        t->backend = g;
        g->next = textures;
        if (textures)
        {
            textures->prev = g;
        }
        textures = g;
    }
    const uint32_t w = (t->width + 3) & ~3u, h = (t->height + 3) & ~3u;
    const size_t size = (size_t)w * h * 4;
    if (!g->data || g->width != t->width || g->height != t->height)
    {
        free(g->data);
        g->data = NULL;
        g->data = alloc_texels(size);
    }
    g->width = t->width;
    g->height = t->height;
    g->generation = t->generation;
    if (!g->data)
    {
        static int told;
        if (!told++)
        {
            v3_log("render_gx: no memory for a %ux%u texture", t->width, t->height);
        }
        return NULL;
    }
    convert(t, g->data);
    DCFlushRange(g->data, size);
    GX_InitTexObj(&g->object, g->data, (u16)t->width, (u16)t->height, GX_TF_RGBA8, GX_CLAMP,
                  GX_CLAMP, GX_FALSE);
    GX_InvalidateTexAll();
    return g;
}

static void gx_texture_destroyed(V3Renderer *r, V3Texture *t)
{
    (void)r;
    GxTexture *g = t->backend;
    if (g)
    {
        /* GX may still read it in the frame being drawn. */
        GX_DrawDone();
        if (g->prev)
        {
            g->prev->next = g->next;
        }
        else
        {
            textures = g->next;
        }
        if (g->next)
        {
            g->next->prev = g->prev;
        }
        free(g->data);
        free(g);
        t->backend = NULL;
    }
}

static u8 wrap_mode(uint32_t address, uint32_t size)
{
    if (!pow2(size))
    {
        return GX_CLAMP; /* GX repeats and mirrors only power-of-two sizes */
    }
    switch (address)
    {
    case 2:
        return GX_MIRROR;
    case 3:
    case 4:
    case 5:
        return GX_CLAMP;
    default:
        return GX_REPEAT;
    }
}

/* --- state -------------------------------------------------------------------------------- */

static u8 compare(uint32_t func)
{
    /* Direct3D NEVER..ALWAYS are 1..8; GX's are 0..7 in the same order. */
    return func >= 1 && func <= 8 ? (u8)(func - 1) : GX_ALWAYS;
}

static u8 blend_factor(uint32_t f, int source)
{
    switch (f)
    {
    case 1:
        return GX_BL_ZERO;
    case 2:
        return GX_BL_ONE;
    case 3:
        return source ? GX_BL_ONE : GX_BL_SRCCLR;
    case 4:
        return source ? GX_BL_ZERO : GX_BL_INVSRCCLR;
    case 5:
        return GX_BL_SRCALPHA;
    case 6:
        return GX_BL_INVSRCALPHA;
    case 7:
        return GX_BL_DSTALPHA;
    case 8:
        return GX_BL_INVDSTALPHA;
    case 9:
        return source ? GX_BL_DSTCLR : GX_BL_ONE;
    case 10:
        return source ? GX_BL_INVDSTCLR : GX_BL_ZERO;
    default:
        return GX_BL_ONE;
    }
}

/* A color argument as a TEV color input. */
static u8 color_input(uint32_t arg, unsigned stage, int textured)
{
    const int alpha = (arg & 0x20) != 0;
    switch (arg & 7)
    {
    case 0:
        return alpha ? GX_CC_RASA : GX_CC_RASC;
    case 1:
        if (stage == 0)
        {
            return alpha ? GX_CC_RASA : GX_CC_RASC;
        }
        return alpha ? GX_CC_APREV : GX_CC_CPREV;
    case 2:
        if (!textured)
        {
            return GX_CC_ONE;
        }
        return alpha ? GX_CC_TEXA : GX_CC_TEXC;
    case 3:
        return GX_CC_KONST;
    case 5:
        return alpha ? GX_CC_A2 : GX_CC_C2;
    default:
        return GX_CC_ZERO;
    }
}

/* An alpha argument as a TEV alpha input. */
static u8 alpha_input(uint32_t arg, unsigned stage, int textured)
{
    switch (arg & 7)
    {
    case 0:
        return GX_CA_RASA;
    case 1:
        return stage == 0 ? GX_CA_RASA : GX_CA_APREV;
    case 2:
        return textured ? GX_CA_TEXA : GX_CA_KONST; /* konstant alpha is 1 then */
    case 3:
        return GX_CA_KONST;
    case 5:
        return GX_CA_A2;
    default:
        return GX_CA_ZERO;
    }
}

typedef struct
{
    u8 a, b, c, d, op, bias, scale;
} TevSetup;

/* One Direct3D operation as d op lerp(a, b, c), given its arguments as TEV inputs and the
 * inputs the blends read (alpha of diffuse, texture, factor and current). */
static TevSetup operation(uint32_t op, u8 arg0, u8 arg1, u8 arg2, u8 zero, u8 diffuse_a,
                          u8 texture_a, u8 factor_a, u8 current_a)
{
    TevSetup s = {zero, zero, zero, arg1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1};
    switch (op)
    {
    case 3: /* SELECTARG2 */
        s.d = arg2;
        break;
    case 4: /* MODULATE */
    case 5:
    case 6:
        s.d = zero;
        s.b = arg1;
        s.c = arg2;
        s.scale = op == 4 ? GX_CS_SCALE_1 : op == 5 ? GX_CS_SCALE_2 : GX_CS_SCALE_4;
        break;
    case 7: /* ADD */
    case 8: /* ADDSIGNED */
    case 9: /* ADDSIGNED2X */
        s.a = arg2;
        s.bias = op == 7 ? GX_TB_ZERO : GX_TB_SUBHALF;
        s.scale = op == 9 ? GX_CS_SCALE_2 : GX_CS_SCALE_1;
        break;
    case 10: /* SUBTRACT */
        s.a = arg2;
        s.op = GX_TEV_SUB;
        break;
    case 11: /* ADDSMOOTH: arg1 + (1 - arg1) * arg2 */
        s.a = arg2;
        s.c = arg1;
        break;
    case 12: /* BLENDDIFFUSEALPHA */
    case 13: /* BLENDTEXTUREALPHA */
    case 14: /* BLENDFACTORALPHA */
    case 16: /* BLENDCURRENTALPHA */
        s.d = zero;
        s.a = arg2;
        s.b = arg1;
        s.c = op == 12 ? diffuse_a : op == 13 ? texture_a : op == 14 ? factor_a : current_a;
        break;
    case 15: /* BLENDTEXTUREALPHAPM: arg1 + arg2 * (1 - texture alpha) */
        s.a = arg2;
        s.c = texture_a;
        break;
    case 25: /* MULTIPLYADD: arg0 + arg1 * arg2 */
        s.d = arg0;
        s.b = arg1;
        s.c = arg2;
        break;
    case 26: /* LERP: arg0 * arg1 + (1 - arg0) * arg2 */
        s.d = zero;
        s.a = arg2;
        s.b = arg1;
        s.c = arg0;
        break;
    default: /* SELECTARG1 and the rest */
        break;
    }
    return s;
}

static GXColor gx_color(uint32_t argb)
{
    GXColor c = {(u8)(argb >> 16), (u8)(argb >> 8), (u8)argb, (u8)(argb >> 24)};
    return c;
}

/* Program TEV for the state's texture stages; returns the number of stages. */
static unsigned setup_stages(const V3RenderState *st)
{
    GX_SetTevKColor(GX_KCOLOR0, gx_color(st->render[60]));
    unsigned n = 0;
    for (unsigned k = 0; k < V3_MAX_STAGES; ++k)
    {
        const uint32_t *ts = st->stage[k];
        if (ts[1] == 1)
        {
            break;
        }
        V3Texture *t = st->texture[k];
        GxTexture *g = t ? upload(t) : NULL;
        const int textured = g != NULL;
        const unsigned set = (ts[11] & 0xffff) < 2 ? ts[11] & 0xffff : 0;
        if (textured)
        {
            g->used = draw_clock;
            const uint32_t *sm = st->sampler[k];
            GX_InitTexObjWrapMode(&g->object, wrap_mode(sm[1], t->width), wrap_mode(sm[2], t->height));
            const int linear = sm[5] >= 2 || sm[6] >= 2;
            GX_InitTexObjFilterMode(&g->object, linear ? GX_LINEAR : GX_NEAR,
                                    linear ? GX_LINEAR : GX_NEAR);
            GX_LoadTexObj(&g->object, (u8)(GX_TEXMAP0 + k));
        }
        const u8 stage = (u8)(GX_TEVSTAGE0 + n);
        GX_SetTevOrder(stage, (u8)(GX_TEXCOORD0 + set), textured ? (u8)(GX_TEXMAP0 + k) : GX_TEXMAP_NULL,
                       GX_COLOR0A0);
        GX_SetTevKColorSel(stage, GX_TEV_KCSEL_K0);
        /* Konstant alpha: the factor's, or 1 standing in for an absent texture's alpha. */
        const int needs_one = !textured && ((ts[5] & 7) == 2 || (ts[6] & 7) == 2 || (ts[27] & 7) == 2);
        GX_SetTevKAlphaSel(stage, needs_one ? GX_TEV_KASEL_1 : GX_TEV_KASEL_K0_A);
        const TevSetup color = operation(
            ts[1], color_input(ts[26], k, textured), color_input(ts[2], k, textured),
            color_input(ts[3], k, textured), GX_CC_ZERO, GX_CC_RASA,
            textured ? GX_CC_TEXA : GX_CC_ONE, GX_CC_KONST, k == 0 ? GX_CC_RASA : GX_CC_APREV);
        /* The factor's alpha replicated, for BLENDFACTORALPHA: the stage's konstant selection
         * is the color one, so take the alpha selection instead. */
        TevSetup c = color;
        if (ts[1] == 14)
        {
            GX_SetTevKColorSel(stage, GX_TEV_KCSEL_K0_A);
        }
        GX_SetTevColorIn(stage, c.a, c.b, c.c, c.d);
        const u8 out = ts[28] == 5 ? GX_TEVREG2 : GX_TEVPREV;
        GX_SetTevColorOp(stage, c.op, c.bias, c.scale, GX_TRUE, out);
        TevSetup a;
        if (ts[4] == 1)
        {
            /* Alpha disabled: the current alpha carries on. */
            const u8 current = k == 0 ? GX_CA_RASA : GX_CA_APREV;
            a = (TevSetup){GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, current, GX_TEV_ADD, GX_TB_ZERO,
                           GX_CS_SCALE_1};
        }
        else
        {
            a = operation(ts[4], alpha_input(ts[27], k, textured), alpha_input(ts[5], k, textured),
                          alpha_input(ts[6], k, textured), GX_CA_ZERO, GX_CA_RASA,
                          textured ? GX_CA_TEXA : GX_CA_KONST, GX_CA_KONST,
                          k == 0 ? GX_CA_RASA : GX_CA_APREV);
        }
        GX_SetTevAlphaIn(stage, a.a, a.b, a.c, a.d);
        GX_SetTevAlphaOp(stage, a.op, a.bias, a.scale, GX_TRUE, out);
        ++n;
    }
    if (n == 0)
    {
        /* Stage 0 disabled: the diffuse color as is. */
        GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        n = 1;
    }
    return n;
}

static void setup_blend(const V3RenderState *st, unsigned *stages)
{
    const uint32_t *rs = st->render;
    if (!rs[27])
    {
        GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
        return;
    }
    uint32_t src = rs[19], dst = rs[20];
    if (src == 12)
    {
        src = 5;
        dst = 6;
    }
    else if (src == 13)
    {
        src = 6;
        dst = 5;
    }
    if (rs[171] == 3 || rs[171] == 2)
    {
        /* dst - src * factor: GX subtracts unweighted, so weight the source in TEV first. */
        if (src == 5 && *stages < 16)
        {
            const u8 stage = (u8)(GX_TEVSTAGE0 + *stages);
            GX_SetTevOrder(stage, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLORNULL);
            GX_SetTevColorIn(stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
            GX_SetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GX_SetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GX_SetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            ++*stages;
        }
        GX_SetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
        return;
    }
    GX_SetBlendMode(GX_BM_BLEND, blend_factor(src, 1), blend_factor(dst, 0), GX_LO_CLEAR);
}

/* --- stencil in the depth buffer ------------------------------------------------------------- */

/* The z row constant for stencil value v: z_ndc = -a, and the window depth rises with z_ndc, so a
 * falls as v rises (the depth functions then order codes as the values), all inside the clip
 * range. */
static float stencil_depth(uint32_t v)
{
    return 0.5f - (float)((v & 255) + 1) / 1024.0f;
}

/* Whether this draw's stencil state runs in the depth buffer; logs once when it cannot. */
static int stencil_emulated(const uint32_t *rs)
{
    if (!rs[52])
    {
        return 0;
    }
    const int keep_fails = rs[53] == 1 && rs[54] == 1;
    const int pass_ok = rs[55] == 1 || rs[55] == 3;
    if (!rs[7] && keep_fails && pass_ok)
    {
        return 1;
    }
    static int warned;
    if (!warned)
    {
        warned = 1;
        v3_log("render_gx: stencil ops %u/%u/%u with depth %u are not modelled; drawn unmasked",
               rs[53], rs[54], rs[55], rs[7]);
    }
    return 0;
}

static void setup_raster(Gx *g, const V3RenderState *st)
{
    const uint32_t *rs = st->render;
    int32_t x0 = (int32_t)st->viewport.x, y0 = (int32_t)st->viewport.y;
    int32_t x1 = x0 + (int32_t)st->viewport.width, y1 = y0 + (int32_t)st->viewport.height;
    if (rs[174])
    {
        x0 = st->scissor.left > x0 ? st->scissor.left : x0;
        y0 = st->scissor.top > y0 ? st->scissor.top : y0;
        x1 = st->scissor.right < x1 ? st->scissor.right : x1;
        y1 = st->scissor.bottom < y1 ? st->scissor.bottom : y1;
    }
    x1 = x1 > (int32_t)g->width ? (int32_t)g->width : x1;
    y1 = y1 > (int32_t)g->height ? (int32_t)g->height : y1;
    if (x1 <= x0 || y1 <= y0)
    {
        x1 = x0 + 1;
        y1 = y0 + 1;
    }
    GX_SetScissor((u32)x0, (u32)y0, (u32)(x1 - x0), (u32)(y1 - y0));
    const int stencil = stencil_emulated(rs);
    GX_SetViewport((f32)st->viewport.x + 0.5f, (f32)st->viewport.y + 0.5f, (f32)st->viewport.width,
                   (f32)st->viewport.height, stencil ? 0.0f : st->viewport.min_z,
                   stencil ? 1.0f : st->viewport.max_z);
    if (rs[15])
    {
        GX_SetAlphaCompare(compare(rs[25]), (u8)(rs[24] & 255), GX_AOP_AND, GX_ALWAYS, 0);
    }
    else
    {
        GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    }
    if (stencil)
    {
        GX_SetZMode(GX_TRUE, compare(rs[56]), rs[55] == 3 ? GX_TRUE : GX_FALSE);
    }
    else
    {
        GX_SetZMode(rs[7] ? GX_TRUE : GX_FALSE, compare(rs[23]),
                    rs[7] && rs[14] ? GX_TRUE : GX_FALSE);
    }
}

/* --- drawing ------------------------------------------------------------------------------ */

static void gx_begin(V3Renderer *r, uint32_t width, uint32_t height)
{
    Gx *g = (Gx *)r;
    g->width = width > 640 ? 640 : width;
    g->height = height > 480 ? 480 : height;
    GX_ClearVtxDesc();
    GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GX_SetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GX_SetNumChans(1);
    GX_SetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GX_SetNumTexGens(2);
    GX_SetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GX_SetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
    Mtx identity;
    guMtxIdentity(identity);
    GX_LoadPosMtxImm(identity, GX_PNMTX0);
    GX_SetCurrentMtx(GX_PNMTX0);
    GX_SetCullMode(GX_CULL_NONE);
    GX_SetClipMode(GX_CLIP_ENABLE);
    GX_SetZCompLoc(GX_FALSE);
    GX_SetColorUpdate(GX_TRUE);
    GX_SetAlphaUpdate(GX_FALSE);
}

static void put_vertex(const Out *o)
{
    GX_Position3f32(o->cx, o->cy, -o->cw);
    const u32 rgba = (u32)(clampf(o->color[0]) * 255.0f + 0.5f) << 24 |
                     (u32)(clampf(o->color[1]) * 255.0f + 0.5f) << 16 |
                     (u32)(clampf(o->color[2]) * 255.0f + 0.5f) << 8 |
                     (u32)(clampf(o->color[3]) * 255.0f + 0.5f);
    GX_Color1u32(rgba);
    GX_TexCoord2f32(o->u[0], o->v[0]);
    GX_TexCoord2f32(o->u[1], o->v[1]);
}

/* The projection: x and y pass, w = -z; the z row is either a constant inside the clip range
 * (depth off) or Direct3D's own depth, z = a + b / w, fitted from the draw's vertices. */
static void load_projection(const V3RenderState *st, const Out *const *tris, uint32_t count)
{
    float a = 0.5f, b = 0.0f;
    if (stencil_emulated(st->render))
    {
        a = stencil_depth(st->render[57]);
    }
    else if (st->render[7])
    {
        const Out *p = tris[0];
        const Out *q = NULL;
        for (uint32_t i = 1; i < count; ++i)
        {
            if (fabsf(tris[i]->cw - p->cw) > 1e-4f * fabsf(p->cw))
            {
                q = tris[i];
                break;
            }
        }
        if (q)
        {
            /* cz = a' cw + b'; GX's z_ndc = z_d3d - 1 = (a' - 1) + b' / cw. */
            const float slope = (p->cz - q->cz) / (p->cw - q->cw);
            a = 1.0f - slope;
            b = p->cz - slope * p->cw;
        }
        else
        {
            /* One w for the whole draw: z / w directly. */
            a = 1.0f - p->cz / p->cw;
            b = 0.0f;
        }
    }
    Mtx44 m = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, a, b}, {0, 0, -1, 0}};
    GX_LoadProjectionMtx(m, GX_PERSPECTIVE);
}

static void gx_draw(V3Renderer *r, const V3RenderState *st, const V3Draw *d)
{
    Gx *g = (Gx *)r;
    ++draw_clock;
    if (d->primitive < 4 || d->primitive > 6 || d->pretransformed)
    {
        return; /* points, lines and pretransformed vertices: the game draws none */
    }
    if (d->vertex_count > g->out_capacity)
    {
        g->out_capacity = d->vertex_count + 256;
        g->out = realloc(g->out, g->out_capacity * sizeof(Out));
    }
    process(g->out, st, d);
    const uint32_t n = d->indices ? d->index_count : d->vertex_count;
    const uint32_t triangles = d->primitive == 4 ? n / 3 : n >= 2 ? n - 2 : 0;
    if (2 * triangles * 3 > g->tri_capacity)
    {
        g->tri_capacity = 2 * triangles * 3 + 64;
        g->tris = realloc(g->tris, g->tri_capacity * sizeof(*g->tris));
        g->clipped = realloc(g->clipped, g->tri_capacity * sizeof(Out));
    }
    uint32_t count = 0, used = 0;
#define V(i) (&g->out[d->indices ? d->indices[(i)] : (i)])
    for (uint32_t t = 0; t < triangles; ++t)
    {
        const Out *a, *b, *c;
        if (d->primitive == 4)
        {
            a = V(3 * t), b = V(3 * t + 1), c = V(3 * t + 2);
        }
        else if (d->primitive == 5)
        {
            a = V(t + (t & 1)), b = V(t + 1 - (t & 1)), c = V(t + 2);
        }
        else
        {
            a = V(0), b = V(t + 1), c = V(t + 2);
        }
        Out *poly = &g->clipped[used];
        const unsigned k = clip_near(st, a, b, c, poly);
        if (k == 0 || culled(st, edge(poly[0].x, poly[0].y, poly[1].x, poly[1].y, poly[2].x, poly[2].y)))
        {
            continue;
        }
        used += k;
        for (unsigned i = 1; i + 1 < k; ++i)
        {
            g->tris[count++] = &poly[0];
            g->tris[count++] = &poly[i];
            g->tris[count++] = &poly[i + 1];
        }
    }
#undef V
    if (count == 0)
    {
        return;
    }
    unsigned stages = setup_stages(st);
    setup_blend(st, &stages);
    GX_SetNumTevStages((u8)stages);
    setup_raster(g, st);
    load_projection(st, g->tris, count);
    GX_Begin(GX_TRIANGLES, GX_VTXFMT0, (u16)count);
    for (uint32_t i = 0; i < count; ++i)
    {
        put_vertex(g->tris[i]);
    }
    GX_End();
}

/* Clear: a quad over the viewport in the clear color at the clear depth. */
static void clear_stencil(Gx *g, const V3RenderState *st, uint32_t stencil);

static void gx_clear(V3Renderer *r, const V3RenderState *st, uint32_t flags, uint32_t color,
                     float z, uint32_t stencil)
{
    Gx *g = (Gx *)r;
    if (flags & 4)
    {
        clear_stencil(g, st, stencil);
    }
    if (!(flags & 3))
    {
        return;
    }
    Mtx44 ortho;
    guOrtho(ortho, 0, (f32)g->height, 0, (f32)g->width, 0, 1);
    GX_LoadProjectionMtx(ortho, GX_ORTHOGRAPHIC);
    GX_SetViewport(0, 0, (f32)g->width, (f32)g->height, 0, 1);
    const uint32_t x0 = st->viewport.x, y0 = st->viewport.y;
    const uint32_t x1 = x0 + st->viewport.width, y1 = y0 + st->viewport.height;
    GX_SetScissor(x0, y0, st->viewport.width, st->viewport.height);
    GX_SetNumTevStages(1);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GX_SetColorUpdate(flags & 1 ? GX_TRUE : GX_FALSE);
    GX_SetZMode(flags & 2 ? GX_TRUE : GX_FALSE, GX_ALWAYS, flags & 2 ? GX_TRUE : GX_FALSE);
    const u32 rgba = (color & 0x00ffffffu) << 8 | color >> 24;
    const f32 depth = -z;
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    GX_Position3f32((f32)x0, (f32)y0, depth);
    GX_Color1u32(rgba);
    GX_TexCoord2f32(0, 0);
    GX_TexCoord2f32(0, 0);
    GX_Position3f32((f32)x1, (f32)y0, depth);
    GX_Color1u32(rgba);
    GX_TexCoord2f32(0, 0);
    GX_TexCoord2f32(0, 0);
    GX_Position3f32((f32)x1, (f32)y1, depth);
    GX_Color1u32(rgba);
    GX_TexCoord2f32(0, 0);
    GX_TexCoord2f32(0, 0);
    GX_Position3f32((f32)x0, (f32)y1, depth);
    GX_Color1u32(rgba);
    GX_TexCoord2f32(0, 0);
    GX_TexCoord2f32(0, 0);
    GX_End();
    GX_SetColorUpdate(GX_TRUE);
}

/* The stencil clear: the viewport's depth set to the value's code, through the same projection
 * the draws use, so the codes match exactly. Leaves the color alone. */
static void clear_stencil(Gx *g, const V3RenderState *st, uint32_t stencil)
{
    (void)g;
    Mtx44 m = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, stencil_depth(stencil), 0}, {0, 0, -1, 0}};
    GX_LoadProjectionMtx(m, GX_PERSPECTIVE);
    GX_SetViewport((f32)st->viewport.x + 0.5f, (f32)st->viewport.y + 0.5f, (f32)st->viewport.width,
                   (f32)st->viewport.height, 0.0f, 1.0f);
    GX_SetScissor(st->viewport.x, st->viewport.y, st->viewport.width, st->viewport.height);
    GX_SetNumTevStages(1);
    GX_SetTevOrder(GX_TEVSTAGE0, GX_TEXCOORDNULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GX_SetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GX_SetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GX_SetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GX_SetColorUpdate(GX_FALSE);
    GX_SetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    static const float corner[4][2] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};
    GX_Begin(GX_QUADS, GX_VTXFMT0, 4);
    for (unsigned i = 0; i < 4; ++i)
    {
        GX_Position3f32(corner[i][0], corner[i][1], -1.0f);
        GX_Color1u32(0);
        GX_TexCoord2f32(0, 0);
        GX_TexCoord2f32(0, 0);
    }
    GX_End();
    GX_SetColorUpdate(GX_TRUE);
}

static void gx_present(V3Renderer *r)
{
    Gx *g = (Gx *)r;
    if (v3_platform->present)
    {
        const V3Frame frame = {g->width, g->height, NULL};
        v3_platform->present(&frame);
    }
}

/* The EFB through a texture copy, untiled into 0xAARRGGBB rows. */
static void gx_read_back(V3Renderer *r, uint32_t *out, uint32_t width, uint32_t height)
{
    Gx *g = (Gx *)r;
    const uint32_t w = g->width & ~3u, h = g->height & ~3u;
    static uint8_t *copy;
    if (!copy)
    {
        copy = alloc_texels((size_t)w * h * 4);
    }
    if (!copy)
    {
        v3_log("render_gx: no memory to read the frame back");
        memset(out, 0, (size_t)width * height * 4);
        return;
    }
    GX_DrawDone();
    GX_SetTexCopySrc(0, 0, (u16)w, (u16)h);
    GX_SetTexCopyDst((u16)w, (u16)h, GX_TF_RGBA8, GX_FALSE);
    DCInvalidateRange(copy, w * h * 4);
    GX_CopyTex(copy, GX_FALSE);
    GX_PixModeSync();
    GX_DrawDone();
    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            uint32_t c = 0xff000000u;
            if (x < w && y < h)
            {
                const uint8_t *tile = copy + ((y / 4) * (w / 4) + x / 4) * 64;
                const unsigned i = (y % 4) * 4 + x % 4;
                c = 0xff000000u | (uint32_t)tile[2 * i + 1] << 16 | (uint32_t)tile[32 + 2 * i] << 8 |
                    tile[32 + 2 * i + 1];
            }
            out[y * width + x] = c;
        }
    }
}

V3Renderer *v3_renderer(void)
{
    static Gx gx = {{gx_begin, gx_clear, gx_draw, NULL, gx_texture_destroyed, gx_present,
                     gx_read_back},
                    0, 0, NULL, 0, NULL, NULL, 0};
    return &gx.base;
}

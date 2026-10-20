/* The Direct3D 9 fixed-function pipeline on the CPU: transform and lighting, near-plane clipping,
 * culling, perspective-correct triangle rasterization with Direct3D's integer pixel centers and
 * top-left rule, texture stages, alpha test, depth test and blending. The reference the Wii
 * renderer is compared against. */

#include "render_vertex.h"
#include "runtime.h"

#include <string.h>

typedef struct
{
    V3Renderer base;
    uint32_t width, height;
    uint32_t *color;
    float *depth;
    Out *out;
    uint32_t out_capacity;
} Soft;

static void soft_begin(V3Renderer *r, uint32_t width, uint32_t height)
{
    Soft *s = (Soft *)r;
    if (s->width != width || s->height != height)
    {
        free(s->color);
        free(s->depth);
        s->width = width;
        s->height = height;
        s->color = calloc((size_t)width * height, 4);
        s->depth = calloc((size_t)width * height, sizeof(float));
    }
}

static void soft_clear(V3Renderer *r, const V3RenderState *st, uint32_t flags, uint32_t color, float z)
{
    Soft *s = (Soft *)r;
    const uint32_t x0 = st->viewport.x, y0 = st->viewport.y;
    uint32_t x1 = x0 + st->viewport.width, y1 = y0 + st->viewport.height;
    if (x1 > s->width)
        x1 = s->width;
    if (y1 > s->height)
        y1 = s->height;
    for (uint32_t y = y0; y < y1; ++y)
    {
        for (uint32_t x = x0; x < x1; ++x)
        {
            if (flags & 1)
                s->color[y * s->width + x] = color;
            if (flags & 2)
                s->depth[y * s->width + x] = z;
        }
    }
}

/* --- pixels ------------------------------------------------------------------------------- */

static int compare(uint32_t func, float a, float b)
{
    switch (func)
    {
    case 1:
        return 0;
    case 2:
        return a < b;
    case 3:
        return a == b;
    case 4:
        return a <= b;
    case 5:
        return a > b;
    case 6:
        return a != b;
    case 7:
        return a >= b;
    default:
        return 1;
    }
}

static int wrap(int i, int n, uint32_t mode)
{
    switch (mode)
    {
    case 2: /* mirror */
    {
        const int period = 2 * n;
        int m = i % period;
        if (m < 0)
            m += period;
        return m < n ? m : period - 1 - m;
    }
    case 3: /* clamp */
    case 4: /* border (as clamp) */
    case 5:
        return i < 0 ? 0 : i >= n ? n - 1 : i;
    default:
    {
        int m = i % n;
        return m < 0 ? m + n : m;
    }
    }
}

static void sample(const V3Texture *t, const uint32_t *sampler, float u, float v, float *out)
{
    const int w = (int)t->width, h = (int)t->height;
    const uint32_t au = sampler[1], av = sampler[2];
    const int linear = sampler[5] >= 2 || sampler[6] >= 2;
    if (!linear)
    {
        const int x = wrap((int)floorf(u * (float)w), w, au);
        const int y = wrap((int)floorf(v * (float)h), h, av);
        unpack(v3_texel(t, (uint32_t)x, (uint32_t)y), out);
        return;
    }
    const float fu = u * (float)w - 0.5f, fv = v * (float)h - 0.5f;
    const int x0 = (int)floorf(fu), y0 = (int)floorf(fv);
    const float ax = fu - (float)x0, ay = fv - (float)y0;
    float c00[4], c10[4], c01[4], c11[4];
    unpack(v3_texel(t, (uint32_t)wrap(x0, w, au), (uint32_t)wrap(y0, h, av)), c00);
    unpack(v3_texel(t, (uint32_t)wrap(x0 + 1, w, au), (uint32_t)wrap(y0, h, av)), c10);
    unpack(v3_texel(t, (uint32_t)wrap(x0, w, au), (uint32_t)wrap(y0 + 1, h, av)), c01);
    unpack(v3_texel(t, (uint32_t)wrap(x0 + 1, w, au), (uint32_t)wrap(y0 + 1, h, av)), c11);
    for (unsigned k = 0; k < 4; ++k)
    {
        const float top = c00[k] + (c10[k] - c00[k]) * ax;
        const float bottom = c01[k] + (c11[k] - c01[k]) * ax;
        out[k] = top + (bottom - top) * ay;
    }
}

static void argument(uint32_t arg, const float *diffuse, const float *current, const float *texture,
                     const float *factor, const float *specular, const float *temp, float *out)
{
    const float *src;
    switch (arg & 7)
    {
    case 0:
        src = diffuse;
        break;
    case 1:
        src = current;
        break;
    case 2:
        src = texture;
        break;
    case 3:
        src = factor;
        break;
    case 4:
        src = specular;
        break;
    case 5:
        src = temp;
        break;
    default:
        src = factor;
        break;
    }
    for (unsigned k = 0; k < 4; ++k)
    {
        out[k] = src[k];
    }
    if (arg & 0x20) /* ALPHAREPLICATE */
    {
        out[0] = out[1] = out[2] = out[3];
    }
    if (arg & 0x10) /* COMPLEMENT */
    {
        for (unsigned k = 0; k < 4; ++k)
        {
            out[k] = 1.0f - out[k];
        }
    }
}

static float op(uint32_t operation, unsigned k, const float *a1, const float *a2, const float *a0,
                const float *diffuse, const float *texture, const float *factor, const float *current)
{
    switch (operation)
    {
    case 2:
        return a1[k];
    case 3:
        return a2[k];
    case 4:
        return a1[k] * a2[k];
    case 5:
        return 2.0f * a1[k] * a2[k];
    case 6:
        return 4.0f * a1[k] * a2[k];
    case 7:
        return a1[k] + a2[k];
    case 8:
        return a1[k] + a2[k] - 0.5f;
    case 9:
        return 2.0f * (a1[k] + a2[k] - 0.5f);
    case 10:
        return a1[k] - a2[k];
    case 11:
        return a1[k] + a2[k] - a1[k] * a2[k];
    case 12:
        return a1[k] * diffuse[3] + a2[k] * (1.0f - diffuse[3]);
    case 13:
        return a1[k] * texture[3] + a2[k] * (1.0f - texture[3]);
    case 14:
        return a1[k] * factor[3] + a2[k] * (1.0f - factor[3]);
    case 15:
        return a1[k] + a2[k] * (1.0f - texture[3]);
    case 16:
        return a1[k] * current[3] + a2[k] * (1.0f - current[3]);
    case 18:
        return k < 3 ? a1[k] + a1[3] * a2[k] : a1[k];
    case 19:
        return k < 3 ? a1[k] * a2[k] + a1[3] : a1[k];
    case 20:
        return k < 3 ? (1.0f - a1[3]) * a2[k] + a1[k] : a1[k];
    case 21:
        return k < 3 ? (1.0f - a1[k]) * a2[k] + a1[3] : a1[k];
    case 24:
    {
        const float d = 4.0f * ((a1[0] - 0.5f) * (a2[0] - 0.5f) + (a1[1] - 0.5f) * (a2[1] - 0.5f) +
                                (a1[2] - 0.5f) * (a2[2] - 0.5f));
        return d;
    }
    case 25:
        return a0[k] + a1[k] * a2[k];
    case 26:
        return a0[k] * a1[k] + (1.0f - a0[k]) * a2[k];
    default:
        return a1[k];
    }
}

static void blend_factor(uint32_t f, const float *src, const float *dst, float *out)
{
    for (unsigned k = 0; k < 4; ++k)
    {
        switch (f)
        {
        case 1:
            out[k] = 0.0f;
            break;
        case 2:
            out[k] = 1.0f;
            break;
        case 3:
            out[k] = src[k];
            break;
        case 4:
            out[k] = 1.0f - src[k];
            break;
        case 5:
            out[k] = src[3];
            break;
        case 6:
            out[k] = 1.0f - src[3];
            break;
        case 7:
            out[k] = dst[3];
            break;
        case 8:
            out[k] = 1.0f - dst[3];
            break;
        case 9:
            out[k] = dst[k];
            break;
        case 10:
            out[k] = 1.0f - dst[k];
            break;
        case 11:
        {
            const float a = src[3] < 1.0f - dst[3] ? src[3] : 1.0f - dst[3];
            out[k] = k < 3 ? a : 1.0f;
            break;
        }
        default:
            out[k] = 1.0f;
            break;
        }
    }
}

static void shade(Soft *s, const V3RenderState *st, unsigned texture_sets, uint32_t x, uint32_t y,
                  float z, const float *color, const float *spec, const float *u, const float *v)
{
    const uint32_t *rs = st->render;
    const size_t at = (size_t)y * s->width + x;
    if (rs[7] && !compare(rs[23], z, s->depth[at]))
    {
        return;
    }
    float diffuse[4] = {color[0], color[1], color[2], color[3]};
    float current[4] = {color[0], color[1], color[2], color[3]};
    float specular[4] = {spec[0], spec[1], spec[2], spec[3]};
    float factor[4], temp[4] = {0, 0, 0, 0};
    unpack(rs[60], factor);
    for (unsigned stage = 0; stage < V3_MAX_STAGES; ++stage)
    {
        const uint32_t *ts = st->stage[stage];
        if (ts[1] == 1) /* COLOROP disable ends the cascade */
        {
            break;
        }
        float texture[4] = {1, 1, 1, 1};
        const V3Texture *t = st->texture[stage];
        if (t)
        {
            const unsigned set = ts[11] & 0xffff;
            const unsigned k = set < 2 && set < (texture_sets ? texture_sets : 1) ? set : 0;
            sample(t, st->sampler[stage], u[k], v[k], texture);
        }
        float a1[4], a2[4], a0[4], result[4];
        argument(ts[2], diffuse, current, texture, factor, specular, temp, a1);
        argument(ts[3], diffuse, current, texture, factor, specular, temp, a2);
        argument(ts[26], diffuse, current, texture, factor, specular, temp, a0);
        for (unsigned k = 0; k < 3; ++k)
        {
            result[k] = clampf(op(ts[1], k, a1, a2, a0, diffuse, texture, factor, current));
        }
        if (ts[1] == 24)
        {
            result[3] = result[0];
        }
        float b1[4], b2[4], b0[4];
        argument(ts[5], diffuse, current, texture, factor, specular, temp, b1);
        argument(ts[6], diffuse, current, texture, factor, specular, temp, b2);
        argument(ts[27], diffuse, current, texture, factor, specular, temp, b0);
        if (ts[4] != 1)
        {
            result[3] = clampf(op(ts[4], 3, b1, b2, b0, diffuse, texture, factor, current));
        }
        else
        {
            result[3] = current[3];
        }
        float *destination = ts[28] == 5 ? temp : current;
        for (unsigned k = 0; k < 4; ++k)
        {
            destination[k] = result[k];
        }
    }
    if (rs[29]) /* SPECULARENABLE */
    {
        for (unsigned k = 0; k < 3; ++k)
        {
            current[k] = clampf(current[k] + specular[k]);
        }
    }
    if (rs[15]) /* alpha test */
    {
        const float a = (float)(uint32_t)(clampf(current[3]) * 255.0f + 0.5f);
        if (!compare(rs[25], a, (float)(rs[24] & 255)))
        {
            return;
        }
    }
    float out[4];
    if (rs[27]) /* alpha blending */
    {
        float dst[4], fs[4], fd[4];
        unpack(s->color[at], dst);
        uint32_t src_blend = rs[19], dst_blend = rs[20];
        if (src_blend == 12) /* BOTHSRCALPHA */
        {
            src_blend = 5;
            dst_blend = 6;
        }
        else if (src_blend == 13)
        {
            src_blend = 6;
            dst_blend = 5;
        }
        blend_factor(src_blend, current, dst, fs);
        blend_factor(dst_blend, current, dst, fd);
        for (unsigned k = 0; k < 4; ++k)
        {
            const float a = current[k] * fs[k], b = dst[k] * fd[k];
            switch (rs[171])
            {
            case 2:
                out[k] = a - b;
                break;
            case 3:
                out[k] = b - a;
                break;
            case 4:
                out[k] = current[k] < dst[k] ? current[k] : dst[k];
                break;
            case 5:
                out[k] = current[k] > dst[k] ? current[k] : dst[k];
                break;
            default:
                out[k] = a + b;
                break;
            }
        }
    }
    else
    {
        for (unsigned k = 0; k < 4; ++k)
        {
            out[k] = current[k];
        }
    }
    const uint32_t mask = rs[168];
    uint32_t pixel = pack(out);
    if ((mask & 15) != 15)
    {
        uint32_t keep = 0;
        if (!(mask & 1))
            keep |= 0x00ff0000u;
        if (!(mask & 2))
            keep |= 0x0000ff00u;
        if (!(mask & 4))
            keep |= 0x000000ffu;
        if (!(mask & 8))
            keep |= 0xff000000u;
        pixel = (pixel & ~keep) | (s->color[at] & keep);
    }
    s->color[at] = pixel;
    if (rs[7] && rs[14])
    {
        s->depth[at] = z;
    }
}

/* --- triangles ---------------------------------------------------------------------------------- */

static int top_left(float ax, float ay, float bx, float by)
{
    /* Clockwise screen-space triangles (y down): a top edge is horizontal going right, a left
     * edge goes up. */
    return (ay == by && bx > ax) || by < ay;
}

static void triangle(Soft *s, const V3RenderState *st, unsigned texture_sets, const Out *a,
                     const Out *b, const Out *c, const Out *flat)
{
    float area = edge(a->x, a->y, b->x, b->y, c->x, c->y);
    if (area == 0.0f)
    {
        return;
    }
    if (area < 0.0f)
    {
        const Out *t = b;
        b = c;
        c = t;
        area = -area;
    }
    int32_t minx = (int32_t)ceilf(fminf(a->x, fminf(b->x, c->x)));
    int32_t maxx = (int32_t)floorf(fmaxf(a->x, fmaxf(b->x, c->x)));
    int32_t miny = (int32_t)ceilf(fminf(a->y, fminf(b->y, c->y)));
    int32_t maxy = (int32_t)floorf(fmaxf(a->y, fmaxf(b->y, c->y)));
    int32_t clip_x0 = (int32_t)st->viewport.x, clip_y0 = (int32_t)st->viewport.y;
    int32_t clip_x1 = (int32_t)(st->viewport.x + st->viewport.width) - 1;
    int32_t clip_y1 = (int32_t)(st->viewport.y + st->viewport.height) - 1;
    if (st->render[174]) /* scissor */
    {
        if (st->scissor.left > clip_x0)
            clip_x0 = st->scissor.left;
        if (st->scissor.top > clip_y0)
            clip_y0 = st->scissor.top;
        if (st->scissor.right - 1 < clip_x1)
            clip_x1 = st->scissor.right - 1;
        if (st->scissor.bottom - 1 < clip_y1)
            clip_y1 = st->scissor.bottom - 1;
    }
    if (clip_x1 >= (int32_t)s->width)
        clip_x1 = (int32_t)s->width - 1;
    if (clip_y1 >= (int32_t)s->height)
        clip_y1 = (int32_t)s->height - 1;
    if (minx < clip_x0)
        minx = clip_x0;
    if (miny < clip_y0)
        miny = clip_y0;
    if (maxx > clip_x1)
        maxx = clip_x1;
    if (maxy > clip_y1)
        maxy = clip_y1;
    const int tl0 = top_left(b->x, b->y, c->x, c->y);
    const int tl1 = top_left(c->x, c->y, a->x, a->y);
    const int tl2 = top_left(a->x, a->y, b->x, b->y);
    const float inv_area = 1.0f / area;
    const int flat_shade = st->render[9] == 1;
    for (int32_t y = miny; y <= maxy; ++y)
    {
        const float py = (float)y;
        for (int32_t x = minx; x <= maxx; ++x)
        {
            const float px = (float)x;
            const float w0 = edge(b->x, b->y, c->x, c->y, px, py);
            const float w1 = edge(c->x, c->y, a->x, a->y, px, py);
            const float w2 = edge(a->x, a->y, b->x, b->y, px, py);
            if (w0 < 0 || w1 < 0 || w2 < 0 || (w0 == 0 && !tl0) || (w1 == 0 && !tl1) ||
                (w2 == 0 && !tl2))
            {
                continue;
            }
            const float l0 = w0 * inv_area, l1 = w1 * inv_area, l2 = w2 * inv_area;
            const float z = l0 * a->z + l1 * b->z + l2 * c->z;
            const float q0 = l0 * a->rhw, q1 = l1 * b->rhw, q2 = l2 * c->rhw;
            const float q = q0 + q1 + q2;
            const float iq = q != 0.0f ? 1.0f / q : 0.0f;
            float color[4], spec[4], u[2], v[2];
            for (unsigned k = 0; k < 4; ++k)
            {
                color[k] = flat_shade ? flat->color[k]
                                      : (q0 * a->color[k] + q1 * b->color[k] + q2 * c->color[k]) * iq;
                spec[k] = flat_shade ? flat->spec[k]
                                     : (q0 * a->spec[k] + q1 * b->spec[k] + q2 * c->spec[k]) * iq;
            }
            for (unsigned k = 0; k < 2; ++k)
            {
                u[k] = (q0 * a->u[k] + q1 * b->u[k] + q2 * c->u[k]) * iq;
                v[k] = (q0 * a->v[k] + q1 * b->v[k] + q2 * c->v[k]) * iq;
            }
            shade(s, st, texture_sets, (uint32_t)x, (uint32_t)y, z, color, spec, u, v);
        }
    }
}

static void clipped_triangle(Soft *s, const V3RenderState *st, const V3Draw *d, const Out *a,
                             const Out *b, const Out *c)
{
    /* Cull on screen-space winding (clockwise is front). */
    if (d->pretransformed)
    {
        if (culled(st, edge(a->x, a->y, b->x, b->y, c->x, c->y)))
        {
            return;
        }
        triangle(s, st, d->texture_sets, a, b, c, a);
        return;
    }
    Out poly[4];
    const unsigned n = clip_near(st, a, b, c, poly);
    if (n == 0)
    {
        return;
    }
    const float area = edge(poly[0].x, poly[0].y, poly[1].x, poly[1].y, poly[2].x, poly[2].y);
    if (culled(st, area))
    {
        return;
    }
    for (unsigned i = 1; i + 1 < n; ++i)
    {
        triangle(s, st, d->texture_sets, &poly[0], &poly[i], &poly[i + 1], a);
    }
}

static void soft_draw(V3Renderer *r, const V3RenderState *st, const V3Draw *d)
{
    Soft *s = (Soft *)r;
    if (!s->color)
    {
        return;
    }
    if (d->vertex_count > s->out_capacity)
    {
        s->out_capacity = d->vertex_count + 256;
        s->out = realloc(s->out, s->out_capacity * sizeof(Out));
    }
    process(s->out, st, d);
    const uint32_t n = d->indices ? d->index_count : d->vertex_count;
#define V(i) (&s->out[d->indices ? d->indices[(i)] : (i)])
    switch (d->primitive)
    {
    case 4:
        for (uint32_t i = 0; i + 2 < n; i += 3)
        {
            clipped_triangle(s, st, d, V(i), V(i + 1), V(i + 2));
        }
        break;
    case 5:
        for (uint32_t i = 0; i + 2 < n; ++i)
        {
            if (i & 1)
            {
                clipped_triangle(s, st, d, V(i + 1), V(i), V(i + 2));
            }
            else
            {
                clipped_triangle(s, st, d, V(i), V(i + 1), V(i + 2));
            }
        }
        break;
    case 6:
        for (uint32_t i = 1; i + 1 < n; ++i)
        {
            clipped_triangle(s, st, d, V(0), V(i), V(i + 1));
        }
        break;
    default:
        /* Points and lines: not used by the game's renderer so far. */
        break;
    }
#undef V
}

static void soft_present(V3Renderer *r)
{
    Soft *s = (Soft *)r;
    if (v3_platform->present && s->color)
    {
        const V3Frame frame = {s->width, s->height, s->color};
        v3_platform->present(&frame);
    }
}

static void soft_read_back(V3Renderer *r, uint32_t *out, uint32_t width, uint32_t height)
{
    Soft *s = (Soft *)r;
    for (uint32_t y = 0; y < height; ++y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            out[y * width + x] = x < s->width && y < s->height ? s->color[y * s->width + x] : 0;
        }
    }
}

V3Renderer *v3_renderer(void)
{
    static Soft soft = {{soft_begin, soft_clear, soft_draw, NULL, NULL, soft_present, soft_read_back},
                        0, 0, NULL, NULL, NULL, 0};
    return &soft.base;
}

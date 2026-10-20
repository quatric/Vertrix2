#ifndef V3_RENDER_VERTEX_H
#define V3_RENDER_VERTEX_H

/* The Direct3D 9 fixed-function vertex stage both renderers share: transform and lighting on the
 * CPU, the near-plane clip and the viewport projection. render_soft.c rasterizes its output;
 * render_gx.c hands it to GX. */

#include "render.h"

#include <math.h>
#include <stdlib.h>

typedef struct
{
    float x, y, z, rhw;  /* screen */
    float cx, cy, cz, cw; /* clip space (for clipping) */
    float color[4];      /* diffuse r, g, b, a in 0..1 */
    float spec[4];
    float u[2], v[2];
} Out;

static float clampf(float v)
{
    return v < 0.0f ? 0.0f : v > 1.0f ? 1.0f : v;
}

static void unpack(uint32_t c, float *out)
{
    out[0] = (float)((c >> 16) & 255) / 255.0f;
    out[1] = (float)((c >> 8) & 255) / 255.0f;
    out[2] = (float)(c & 255) / 255.0f;
    out[3] = (float)(c >> 24) / 255.0f;
}

static uint32_t pack(const float *c)
{
    return (uint32_t)(clampf(c[3]) * 255.0f + 0.5f) << 24 |
           (uint32_t)(clampf(c[0]) * 255.0f + 0.5f) << 16 |
           (uint32_t)(clampf(c[1]) * 255.0f + 0.5f) << 8 | (uint32_t)(clampf(c[2]) * 255.0f + 0.5f);
}

static void multiply(const float *a, const float *b, float *r)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        for (unsigned j = 0; j < 4; ++j)
        {
            r[4 * i + j] = a[4 * i] * b[j] + a[4 * i + 1] * b[4 + j] + a[4 * i + 2] * b[8 + j] +
                           a[4 * i + 3] * b[12 + j];
        }
    }
}

/* --- vertex processing ---------------------------------------------------------------------- */

static void light_vertex(const V3RenderState *st, const V3Draw *d, const V3Vertex *v,
                         const float *world, float *color, float *spec)
{
    const uint32_t *rs = st->render;
    float vd[4], vs[4];
    unpack(v->diffuse, vd);
    unpack(v->specular, vs);
    const int color_vertex = rs[141] != 0;
    const float *mat_diffuse = st->material.diffuse;
    const float *mat_ambient = st->material.ambient;
    const float *mat_emissive = st->material.emissive;
    const float *mat_specular = st->material.specular;
#define SOURCE(state, material)                                                                    \
    (color_vertex && rs[state] == 1 && d->has_diffuse   ? vd                                       \
     : color_vertex && rs[state] == 2 && d->has_specular ? vs                                      \
                                                         : (material))
    const float *diff = SOURCE(145, mat_diffuse);
    const float *amb = SOURCE(147, mat_ambient);
    const float *emis = SOURCE(148, mat_emissive);
    const float *specm = SOURCE(146, mat_specular);
#undef SOURCE
    float global[4];
    unpack(rs[139], global);
    float n[3] = {0, 0, 0};
    float p[3];
    p[0] = v->x * world[0] + v->y * world[4] + v->z * world[8] + world[12];
    p[1] = v->x * world[1] + v->y * world[5] + v->z * world[9] + world[13];
    p[2] = v->x * world[2] + v->y * world[6] + v->z * world[10] + world[14];
    if (d->has_normal)
    {
        n[0] = v->nx * world[0] + v->ny * world[4] + v->nz * world[8];
        n[1] = v->nx * world[1] + v->ny * world[5] + v->nz * world[9];
        n[2] = v->nx * world[2] + v->ny * world[6] + v->nz * world[10];
        const float len = sqrtf(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
        if (len > 0.0f)
        {
            n[0] /= len;
            n[1] /= len;
            n[2] /= len;
        }
    }
    for (unsigned k = 0; k < 3; ++k)
    {
        color[k] = emis[k] + amb[k] * global[k];
        spec[k] = 0.0f;
    }
    for (unsigned i = 0; i < V3_MAX_LIGHTS; ++i)
    {
        const V3Light *l = &st->light[i];
        if (!l->enabled)
        {
            continue;
        }
        float dir[3];
        float atten = 1.0f;
        if (l->type == 3)
        {
            dir[0] = -l->direction[0];
            dir[1] = -l->direction[1];
            dir[2] = -l->direction[2];
        }
        else
        {
            dir[0] = l->position[0] - p[0];
            dir[1] = l->position[1] - p[1];
            dir[2] = l->position[2] - p[2];
            const float dist = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
            if (l->range > 0.0f && dist > l->range)
            {
                continue;
            }
            const float a = l->attenuation[0] + l->attenuation[1] * dist +
                            l->attenuation[2] * dist * dist;
            atten = a > 0.0f ? 1.0f / a : 1.0f;
        }
        const float len = sqrtf(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
        if (len > 0.0f)
        {
            dir[0] /= len;
            dir[1] /= len;
            dir[2] /= len;
        }
        float ndotl = n[0] * dir[0] + n[1] * dir[1] + n[2] * dir[2];
        if (ndotl < 0.0f)
        {
            ndotl = 0.0f;
        }
        for (unsigned k = 0; k < 3; ++k)
        {
            color[k] += atten * (l->ambient[k] * amb[k] + ndotl * l->diffuse[k] * diff[k]);
        }
        if (rs[29] && ndotl > 0.0f) /* SPECULARENABLE */
        {
            float h[3] = {dir[0], dir[1], dir[2] + 1.0f};
            const float hl = sqrtf(h[0] * h[0] + h[1] * h[1] + h[2] * h[2]);
            const float ndoth = hl > 0 ? (n[0] * h[0] + n[1] * h[1] + n[2] * h[2]) / hl : 0;
            if (ndoth > 0.0f)
            {
                const float f = powf(ndoth, st->material.power);
                for (unsigned k = 0; k < 3; ++k)
                {
                    spec[k] += atten * f * l->specular[k] * specm[k];
                }
            }
        }
    }
    color[3] = diff[3];
    spec[3] = 0.0f;
}

/* Transform and light a draw's vertices into `out` (vertex_count of them). */
static void process(Out *out, const V3RenderState *st, const V3Draw *d)
{
    float wv[16], wvp[16];
    multiply(st->world, st->view, wv);
    multiply(wv, st->projection, wvp);
    const int lighting = !d->pretransformed && st->render[137];
    const float vx = (float)st->viewport.x, vy = (float)st->viewport.y;
    const float vw = (float)st->viewport.width, vh = (float)st->viewport.height;
    for (uint32_t i = 0; i < d->vertex_count; ++i)
    {
        const V3Vertex *v = &d->vertices[i];
        Out *o = &out[i];
        if (d->pretransformed)
        {
            o->x = v->x;
            o->y = v->y;
            o->z = v->z;
            o->rhw = v->w != 0.0f ? v->w : 1.0f;
            o->cx = o->cy = 0.0f;
            o->cz = 0.0f;
            o->cw = 1.0f;
        }
        else
        {
            o->cx = v->x * wvp[0] + v->y * wvp[4] + v->z * wvp[8] + wvp[12];
            o->cy = v->x * wvp[1] + v->y * wvp[5] + v->z * wvp[9] + wvp[13];
            o->cz = v->x * wvp[2] + v->y * wvp[6] + v->z * wvp[10] + wvp[14];
            o->cw = v->x * wvp[3] + v->y * wvp[7] + v->z * wvp[11] + wvp[15];
        }
        if (lighting)
        {
            light_vertex(st, d, v, st->world, o->color, o->spec);
        }
        else
        {
            unpack(d->has_diffuse ? v->diffuse : 0xffffffffu, o->color);
            unpack(d->has_specular ? v->specular : 0, o->spec);
        }
        for (unsigned k = 0; k < 2; ++k)
        {
            o->u[k] = v->u[k];
            o->v[k] = v->v[k];
        }
    }
    (void)vx;
    (void)vy;
    (void)vw;
    (void)vh;
}

static void project(const V3RenderState *st, Out *o)
{
    const float inv = 1.0f / o->cw;
    const float vx = (float)st->viewport.x, vy = (float)st->viewport.y;
    const float vw = (float)st->viewport.width, vh = (float)st->viewport.height;
    o->x = vx + (o->cx * inv + 1.0f) * 0.5f * vw;
    o->y = vy + (1.0f - o->cy * inv) * 0.5f * vh;
    o->z = st->viewport.min_z + o->cz * inv * (st->viewport.max_z - st->viewport.min_z);
    o->rhw = inv;
}

static float edge(float ax, float ay, float bx, float by, float px, float py)
{
    return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
}

static Out lerp_out(const Out *a, const Out *b, float t)
{
    Out o;
    o.cx = a->cx + (b->cx - a->cx) * t;
    o.cy = a->cy + (b->cy - a->cy) * t;
    o.cz = a->cz + (b->cz - a->cz) * t;
    o.cw = a->cw + (b->cw - a->cw) * t;
    for (unsigned k = 0; k < 4; ++k)
    {
        o.color[k] = a->color[k] + (b->color[k] - a->color[k]) * t;
        o.spec[k] = a->spec[k] + (b->spec[k] - a->spec[k]) * t;
    }
    for (unsigned k = 0; k < 2; ++k)
    {
        o.u[k] = a->u[k] + (b->u[k] - a->u[k]) * t;
        o.v[k] = a->v[k] + (b->v[k] - a->v[k]) * t;
    }
    return o;
}

/* Clip a triangle against the near plane (z >= 0) in clip space and project the result: 0, 3 or
 * 4 vertices in `poly`, wound as the input. */
static unsigned clip_near(const V3RenderState *st, const Out *a, const Out *b, const Out *c, Out *poly)
{
    const Out in[3] = {*a, *b, *c};
    unsigned n = 0;
    for (unsigned i = 0; i < 3; ++i)
    {
        const Out *p = &in[i], *q = &in[(i + 1) % 3];
        const int pin = p->cz >= 0.0f && p->cw > 1e-6f, qin = q->cz >= 0.0f && q->cw > 1e-6f;
        if (pin)
        {
            poly[n++] = *p;
        }
        if (pin != qin && n < 4)
        {
            const float t = p->cz / (p->cz - q->cz);
            poly[n++] = lerp_out(p, q, t);
        }
    }
    if (n < 3)
    {
        return 0;
    }
    for (unsigned i = 0; i < n; ++i)
    {
        if (poly[i].cw <= 1e-6f)
        {
            poly[i].cw = 1e-6f;
        }
        project(st, &poly[i]);
    }
    return n;
}

/* Whether the cull mode removes a triangle of this screen-space signed area (clockwise, y down,
 * is positive). */
static int culled(const V3RenderState *st, float area)
{
    return (st->render[22] == 3 && area < 0) || (st->render[22] == 2 && area > 0);
}

#endif

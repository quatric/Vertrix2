#ifndef V3_RENDER_H
#define V3_RENDER_H

/* What the Direct3D 9 device (d3d9.c) hands a renderer: the fixed-function state in Direct3D's
 * own terms and draws whose vertices are already decoded. render_soft.c rasterizes on the CPU
 * (the build machine's reference); render_gx.c drives the Wii's GX. */

#include <stdint.h>

enum
{
    V3_MAX_STAGES = 4,
    V3_MAX_LIGHTS = 8,
    V3_RENDER_STATES = 256,
    V3_STAGE_STATES = 33,
    V3_SAMPLER_STATES = 14
};

/* Texture formats the device accepts (Direct3D numbering). */
enum
{
    V3_FMT_A8R8G8B8 = 21,
    V3_FMT_X8R8G8B8 = 22,
    V3_FMT_R5G6B5 = 23,
    V3_FMT_X1R5G5B5 = 24,
    V3_FMT_A1R5G5B5 = 25,
    V3_FMT_A4R4G4B4 = 26,
    V3_FMT_A8 = 28,
    V3_FMT_L8 = 50,
    V3_FMT_A8L8 = 51
};

typedef struct V3Texture
{
    uint32_t width, height, format;
    uint32_t pitch;      /* bytes per row of level 0 */
    uint32_t pixels;     /* guest address of level 0 */
    uint32_t generation; /* bumped on every unlock, for renderers that cache a converted copy */
    void *backend;       /* the renderer's own data */
} V3Texture;

typedef struct
{
    float x, y, z, w;  /* position: object space (w = 1) or, pretransformed, screen x, y, z, rhw */
    float nx, ny, nz;  /* normal, when has_normal */
    uint32_t diffuse;  /* 0xAARRGGBB */
    uint32_t specular; /* 0xAARRGGBB */
    float u[2], v[2];  /* two texture coordinate sets */
} V3Vertex;

typedef struct
{
    float diffuse[4], ambient[4], specular[4], emissive[4]; /* r, g, b, a */
    float power;
} V3Material;

typedef struct
{
    uint32_t type; /* 1 point, 2 spot, 3 directional */
    float diffuse[4], specular[4], ambient[4];
    float position[3], direction[3];
    float range, falloff, attenuation[3], theta, phi;
    int enabled;
} V3Light;

typedef struct
{
    uint32_t render[V3_RENDER_STATES];
    uint32_t stage[V3_MAX_STAGES][V3_STAGE_STATES];
    uint32_t sampler[V3_MAX_STAGES][V3_SAMPLER_STATES];
    V3Texture *texture[V3_MAX_STAGES];
    float world[16], view[16], projection[16]; /* row-major, Direct3D's row vectors */
    float texture_transform[V3_MAX_STAGES][16];
    struct
    {
        uint32_t x, y, width, height;
        float min_z, max_z;
    } viewport;
    struct
    {
        int32_t left, top, right, bottom;
    } scissor;
    V3Material material;
    V3Light light[V3_MAX_LIGHTS];
} V3RenderState;

typedef struct
{
    uint32_t primitive; /* Direct3D primitive type: 1 points .. 6 triangle fan */
    const V3Vertex *vertices;
    uint32_t vertex_count;
    const uint32_t *indices; /* NULL for non-indexed */
    uint32_t index_count;
    int pretransformed; /* XYZRHW */
    int has_normal, has_diffuse, has_specular;
    unsigned texture_sets;
} V3Draw;

typedef struct V3Renderer
{
    void (*begin_frame)(struct V3Renderer *r, uint32_t width, uint32_t height);
    void (*clear)(struct V3Renderer *r, const V3RenderState *s, uint32_t flags, uint32_t color,
                  float z);
    void (*draw)(struct V3Renderer *r, const V3RenderState *s, const V3Draw *draw);
    void (*texture_changed)(struct V3Renderer *r, V3Texture *texture);
    void (*texture_destroyed)(struct V3Renderer *r, V3Texture *texture);
    /* The finished back buffer: shown or handed to the platform. */
    void (*present)(struct V3Renderer *r);
    /* Copy the back buffer as 0xAARRGGBB (for GetRenderTargetData/GetFrontBufferData). */
    void (*read_back)(struct V3Renderer *r, uint32_t *out, uint32_t width, uint32_t height);
} V3Renderer;

/* The platform's renderer (render_soft.c or render_gx.c). */
V3Renderer *v3_renderer(void);

/* A texel of a texture in its format as 0xAARRGGBB. */
uint32_t v3_texel(const V3Texture *t, uint32_t x, uint32_t y);
uint32_t v3_format_bytes(uint32_t format);

#endif

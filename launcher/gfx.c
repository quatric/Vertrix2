#include "gfx.h"

#include <gccore.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

extern const uint8_t console_font_8x16[];

static uint32_t canvas[GFX_WIDTH * GFX_HEIGHT];
static uint32_t background[GFX_WIDTH * GFX_HEIGHT];
static GXRModeObj *mode;
static uint32_t *xfb[2];
static int current;
static int wide;

void gfx_init(void)
{
    VIDEO_Init();
    mode = VIDEO_GetPreferredMode(NULL);
    wide = CONF_GetAspectRatio() == CONF_ASPECT_16_9;
    VIDEO_Configure(mode);
    for (int i = 0; i < 2; ++i)
    {
        xfb[i] = (uint32_t *)MEM_K0_TO_K1(SYS_AllocateFramebuffer(mode));
        VIDEO_ClearFrameBuffer(mode, xfb[i], COLOR_BLACK);
    }
    VIDEO_SetNextFramebuffer(xfb[0]);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (mode->viTVMode & VI_NON_INTERLACE)
    {
        VIDEO_WaitVSync();
    }
}

void gfx_save_background(void)
{
    memcpy(background, canvas, sizeof canvas);
}

void gfx_restore_background(void)
{
    memcpy(canvas, background, sizeof canvas);
}

int gfx_save_ppm(const char *path)
{
    FILE *file = fopen(path, "wb");
    if (file == NULL)
    {
        return 0;
    }
    fprintf(file, "P6\n%d %d\n255\n", GFX_WIDTH, GFX_HEIGHT);
    for (int i = 0; i < GFX_WIDTH * GFX_HEIGHT; ++i)
    {
        const uint8_t rgb[3] = {(uint8_t)(canvas[i] >> 16), (uint8_t)(canvas[i] >> 8),
                                (uint8_t)canvas[i]};
        fwrite(rgb, 1, 3, file);
    }
    fclose(file);
    return 1;
}

int gfx_widescreen(void)
{
    return wide;
}

/* Two pixels to one Y0 Cb Y1 Cr word (ITU-R BT.601, studio range). */
static uint32_t yuyv(uint32_t a, uint32_t b)
{
    const int r0 = (int)(a >> 16 & 255), g0 = (int)(a >> 8 & 255), b0 = (int)(a & 255);
    const int r1 = (int)(b >> 16 & 255), g1 = (int)(b >> 8 & 255), b1 = (int)(b & 255);
    const int y0 = (66 * r0 + 129 * g0 + 25 * b0 + 128 + 4096) >> 8;
    const int y1 = (66 * r1 + 129 * g1 + 25 * b1 + 128 + 4096) >> 8;
    const int r = r0 + r1, g = g0 + g1, bl = b0 + b1;
    const int cb = (-38 * r - 74 * g + 112 * bl + 256 + 65536) >> 9;
    const int cr = (112 * r - 94 * g - 18 * bl + 256 + 65536) >> 9;
    return (uint32_t)y0 << 24 | (uint32_t)cb << 16 | (uint32_t)y1 << 8 | (uint32_t)cr;
}

void gfx_present(void)
{
    current ^= 1;
    uint32_t *out = xfb[current];
    const int lines = mode->xfbHeight, words = mode->fbWidth / 2;
    const int top = lines > GFX_HEIGHT ? (lines - GFX_HEIGHT) / 2 : 0;
    const uint32_t black = 0x10801080u;
    for (int y = 0; y < lines; ++y)
    {
        uint32_t *row = out + y * words;
        /* A 480-line canvas on a 480-line TV mode; taller PAL modes get black bars. */
        const int source = lines < GFX_HEIGHT ? y * GFX_HEIGHT / lines : y - top;
        if (source < 0 || source >= GFX_HEIGHT)
        {
            for (int x = 0; x < words; ++x)
            {
                row[x] = black;
            }
            continue;
        }
        const uint32_t *in = canvas + source * GFX_WIDTH;
        for (int x = 0; x < words && 2 * x + 1 < GFX_WIDTH; ++x)
        {
            row[x] = yuyv(in[2 * x], in[2 * x + 1]);
        }
    }
    VIDEO_SetNextFramebuffer(out);
    VIDEO_Flush();
    VIDEO_WaitVSync();
}

void gfx_black(void)
{
    VIDEO_SetBlack(TRUE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
}

static inline uint32_t blend(uint32_t under, uint32_t over)
{
    const uint32_t a = over >> 24;
    if (a == 255)
    {
        return over & 0xffffff;
    }
    if (a == 0)
    {
        return under;
    }
    const uint32_t rb = ((over & 0xff00ff) * a + (under & 0xff00ff) * (255 - a)) >> 8 & 0xff00ff;
    const uint32_t g = ((over & 0xff00) * a + (under & 0xff00) * (255 - a)) >> 8 & 0xff00;
    return rb | g;
}

static inline void plot(int x, int y, uint32_t argb)
{
    if ((unsigned)x < GFX_WIDTH && (unsigned)y < GFX_HEIGHT)
    {
        uint32_t *p = &canvas[y * GFX_WIDTH + x];
        *p = blend(*p, argb);
    }
}

void gfx_fill(int x, int y, int w, int h, uint32_t argb)
{
    int x1 = x + w, y1 = y + h;
    x = x < 0 ? 0 : x;
    y = y < 0 ? 0 : y;
    x1 = x1 > GFX_WIDTH ? GFX_WIDTH : x1;
    y1 = y1 > GFX_HEIGHT ? GFX_HEIGHT : y1;
    for (int j = y; j < y1; ++j)
    {
        uint32_t *row = canvas + j * GFX_WIDTH;
        for (int i = x; i < x1; ++i)
        {
            row[i] = blend(row[i], argb);
        }
    }
}

static uint32_t mix(uint32_t a, uint32_t b, int t, int n)
{
    uint32_t out = 0;
    for (int shift = 0; shift < 32; shift += 8)
    {
        const int ca = (int)(a >> shift & 255), cb = (int)(b >> shift & 255);
        out |= (uint32_t)(ca + (cb - ca) * t / (n > 0 ? n : 1)) << shift;
    }
    return out;
}

void gfx_gradient(int x, int y, int w, int h, uint32_t top, uint32_t bottom)
{
    for (int j = 0; j < h; ++j)
    {
        gfx_fill(x, y + j, w, 1, mix(top, bottom, j, h - 1));
    }
}

/* Coverage of a corner pixel, 0..255, for a circle of the given radius. */
static int corner(int dx, int dy, int radius)
{
    int inside = 0;
    for (int sy = 0; sy < 4; ++sy)
    {
        for (int sx = 0; sx < 4; ++sx)
        {
            const int px = dx * 4 + sx, py = dy * 4 + sy, r = radius * 4;
            inside += (px - r) * (px - r) + (py - r) * (py - r) <= r * r;
        }
    }
    return inside * 255 / 16;
}

static uint32_t with_alpha(uint32_t argb, int coverage)
{
    return (argb & 0xffffff) | (uint32_t)((int)(argb >> 24) * coverage / 255) << 24;
}

void gfx_round_box(int x, int y, int w, int h, int radius, uint32_t argb)
{
    radius = radius * 2 > h ? h / 2 : radius;
    for (int j = 0; j < h; ++j)
    {
        const int dy = j < radius ? j : (j >= h - radius ? h - 1 - j : -1);
        if (dy < 0)
        {
            gfx_fill(x, y + j, w, 1, argb);
            continue;
        }
        for (int i = 0; i < radius; ++i)
        {
            const uint32_t c = with_alpha(argb, corner(i, dy, radius));
            plot(x + i, y + j, c);
            plot(x + w - 1 - i, y + j, c);
        }
        gfx_fill(x + radius, y + j, w - 2 * radius, 1, argb);
    }
}

void gfx_frame(int x, int y, int w, int h, int radius, uint32_t argb)
{
    gfx_fill(x + radius, y, w - 2 * radius, 2, argb);
    gfx_fill(x + radius, y + h - 2, w - 2 * radius, 2, argb);
    gfx_fill(x, y + radius, 2, h - 2 * radius, argb);
    gfx_fill(x + w - 2, y + radius, 2, h - 2 * radius, argb);
    for (int dy = 0; dy < radius; ++dy)
    {
        for (int dx = 0; dx < radius; ++dx)
        {
            /* A two-pixel ring: the outer circle less the inner one. */
            const int outer = corner(dx, dy, radius);
            const int inner = radius > 2 ? corner(dx - 2, dy - 2, radius - 2) : 0;
            const int ring = dx >= 2 && dy >= 2 ? outer - inner : outer;
            if (ring <= 0)
            {
                continue;
            }
            const uint32_t c = with_alpha(argb, ring);
            plot(x + dx, y + dy, c);
            plot(x + w - 1 - dx, y + dy, c);
            plot(x + dx, y + h - 1 - dy, c);
            plot(x + w - 1 - dx, y + h - 1 - dy, c);
        }
    }
}

static uint32_t sample(const uint32_t *pixels, int pw, int ph, int fx, int fy)
{
    /* fx, fy in 1/256 pixels; bilinear over premultiplied colour. */
    int x0 = fx >> 8, y0 = fy >> 8;
    const int tx = fx & 255, ty = fy & 255;
    int x1 = x0 + 1, y1 = y0 + 1;
    x0 = x0 < 0 ? 0 : (x0 >= pw ? pw - 1 : x0);
    y0 = y0 < 0 ? 0 : (y0 >= ph ? ph - 1 : y0);
    x1 = x1 >= pw ? pw - 1 : x1;
    y1 = y1 >= ph ? ph - 1 : y1;
    const uint32_t c[4] = {pixels[y0 * pw + x0], pixels[y0 * pw + x1], pixels[y1 * pw + x0],
                           pixels[y1 * pw + x1]};
    const int weight[4] = {(256 - tx) * (256 - ty), tx * (256 - ty), (256 - tx) * ty, tx * ty};
    int sum[4] = {0, 0, 0, 0};
    for (int k = 0; k < 4; ++k)
    {
        const int a = (int)(c[k] >> 24);
        sum[3] += a * weight[k];
        sum[2] += (int)(c[k] >> 16 & 255) * a / 255 * weight[k];
        sum[1] += (int)(c[k] >> 8 & 255) * a / 255 * weight[k];
        sum[0] += (int)(c[k] & 255) * a / 255 * weight[k];
    }
    const int alpha = sum[3] >> 16;
    if (alpha == 0)
    {
        return 0;
    }
    const int r = (sum[2] >> 16) * 255 / alpha, g = (sum[1] >> 16) * 255 / alpha,
              b = (sum[0] >> 16) * 255 / alpha;
    return (uint32_t)alpha << 24 | (uint32_t)(r > 255 ? 255 : r) << 16 |
           (uint32_t)(g > 255 ? 255 : g) << 8 | (uint32_t)(b > 255 ? 255 : b);
}

void gfx_image(const uint32_t *pixels, int pw, int ph, int x, int y, int w, int h)
{
    for (int j = 0; j < h; ++j)
    {
        const int fy = ((2 * j + 1) * ph * 128) / h - 128;
        for (int i = 0; i < w; ++i)
        {
            const int fx = ((2 * i + 1) * pw * 128) / w - 128;
            plot(x + i, y + j, sample(pixels, pw, ph, fx, fy));
        }
    }
}

/* Latin-1 0xa0..0xff to code page 437 (0 where it has no glyph: drawn as '?'). */
static const uint8_t latin1_to_437[96] = {
    0xff, 0xad, 0x9b, 0x9c, 0,    0x9d, 0x7c, 0x15, 0x22, 0,    0xa6, 0xae, 0xaa, 0x2d, 0,    0,
    0xf8, 0xf1, 0xfd, 0,    0x27, 0xe6, 0x14, 0xfa, 0x2c, 0,    0xa7, 0xaf, 0xac, 0xab, 0,    0xa8,
    0x41, 0x41, 0x41, 0x41, 0x8e, 0x8f, 0x92, 0x80, 0x45, 0x90, 0x45, 0x45, 0x49, 0x49, 0x49, 0x49,
    0x44, 0xa5, 0x4f, 0x4f, 0x4f, 0x4f, 0x99, 0x78, 0x4f, 0x55, 0x55, 0x55, 0x9a, 0x59, 0,    0xe1,
    0x85, 0xa0, 0x83, 0x61, 0x84, 0x86, 0x91, 0x87, 0x8a, 0x82, 0x88, 0x89, 0x8d, 0xa1, 0x8c, 0x8b,
    0,    0xa4, 0x95, 0xa2, 0x93, 0x6f, 0x94, 0xf6, 0x6f, 0x97, 0xa3, 0x96, 0x81, 0x79, 0,    0x98,
};

static uint8_t glyph_of(uint8_t c)
{
    if (c < 0x80)
    {
        return c;
    }
    if (c >= 0xa0 && latin1_to_437[c - 0xa0] != 0)
    {
        return latin1_to_437[c - 0xa0];
    }
    return '?';
}

static void draw_glyph(int x, int y, uint8_t c, int scale, uint32_t argb)
{
    const uint8_t *rows = console_font_8x16 + 16 * glyph_of(c);
    for (int row = 0; row < 16; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (rows[row] & (0x80 >> col))
            {
                if (scale == 1)
                {
                    plot(x + col, y + row, argb);
                }
                else
                {
                    gfx_fill(x + col * scale, y + row * scale, scale, scale, argb);
                }
            }
        }
    }
}

int gfx_text_width(const char *text, int scale)
{
    return (int)strlen(text) * 8 * scale;
}

int gfx_text(int x, int y, const char *text, int scale, uint32_t argb)
{
    int n = 0;
    for (; text[n] != '\0'; ++n)
    {
        draw_glyph(x + n * 8 * scale, y, (uint8_t)text[n], scale, argb);
    }
    return n * 8 * scale;
}

int gfx_text_shadow(int x, int y, const char *text, int scale, uint32_t argb)
{
    gfx_text(x + scale, y + scale, text, scale, 0xa0000000u);
    return gfx_text(x, y, text, scale, argb);
}

void gfx_text_fit(int x, int y, const char *text, int scale, int max_width, uint32_t argb)
{
    const int room = max_width / (8 * scale);
    const int n = (int)strlen(text);
    if (n <= room)
    {
        gfx_text(x, y, text, scale, argb);
        return;
    }
    char cut[256];
    int keep = room > 3 ? room - 3 : 0;
    keep = keep > (int)sizeof cut - 4 ? (int)sizeof cut - 4 : keep;
    memcpy(cut, text, (size_t)keep);
    strcpy(cut + keep, "...");
    gfx_text(x, y, cut, scale, argb);
}

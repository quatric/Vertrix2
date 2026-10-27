/* The launcher's canvas and what it draws (gfx.h); gfx_wii.c shows it on the Wii, the console
 * shell (consoles/) elsewhere. */
#include "gfx.h"

#include "font.h"

#include <stdio.h>
#include <string.h>


static uint32_t canvas[GFX_WIDTH * GFX_HEIGHT];
static uint32_t background[GFX_WIDTH * GFX_HEIGHT];

const uint32_t *gfx_canvas(void)
{
    return canvas;
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

static const FontGlyph *glyph_of(const FontSet *set, uint8_t c)
{
    int low = 0, high = set->count - 1;
    const FontGlyph *question = NULL;
    for (int pass = 0; pass < 2; ++pass)
    {
        const uint8_t want = pass == 0 ? c : '?';
        low = 0;
        high = set->count - 1;
        while (low <= high)
        {
            const int middle = (low + high) / 2;
            const FontGlyph *glyph = &set->glyphs[middle];
            if (glyph->code == want)
            {
                if (pass == 0)
                {
                    return glyph;
                }
                question = glyph;
                break;
            }
            if (glyph->code < want)
            {
                low = middle + 1;
            }
            else
            {
                high = middle - 1;
            }
        }
    }
    return question;
}

static const FontSet *set_of(int scale)
{
    return &font_sets[scale > 1 ? 1 : 0];
}

static void draw_glyph(int x, int y, const FontSet *set, const FontGlyph *glyph, uint32_t argb)
{
    const uint8_t *rows = set->pixels + glyph->offset;
    const uint32_t alpha = argb >> 24;
    for (int row = 0; row < glyph->height; ++row)
    {
        for (int col = 0; col < glyph->width; ++col)
        {
            const uint32_t coverage = rows[row * glyph->width + col];
            if (coverage != 0)
            {
                plot(x + glyph->x + col, y + glyph->y + row,
                     (argb & 0xffffff) | (alpha * coverage / 255) << 24);
            }
        }
    }
}

int gfx_text_width(const char *text, int scale)
{
    const FontSet *set = set_of(scale);
    int width = 0;
    for (; *text != '\0'; ++text)
    {
        width += glyph_of(set, (uint8_t)*text)->advance;
    }
    return width;
}

int gfx_text(int x, int y, const char *text, int scale, uint32_t argb)
{
    const FontSet *set = set_of(scale);
    int width = 0;
    for (; *text != '\0'; ++text)
    {
        const FontGlyph *glyph = glyph_of(set, (uint8_t)*text);
        draw_glyph(x + width, y, set, glyph, argb);
        width += glyph->advance;
    }
    return width;
}

int gfx_text_shadow(int x, int y, const char *text, int scale, uint32_t argb)
{
    gfx_text(x + scale, y + scale, text, scale, 0xa0000000u);
    return gfx_text(x, y, text, scale, argb);
}

void gfx_text_fit(int x, int y, const char *text, int scale, int max_width, uint32_t argb)
{
    if (gfx_text_width(text, scale) <= max_width)
    {
        gfx_text(x, y, text, scale, argb);
        return;
    }
    const FontSet *set = set_of(scale);
    const int dots = 3 * glyph_of(set, '.')->advance;
    char cut[256];
    int keep = 0, width = dots;
    while (text[keep] != '\0' && keep < (int)sizeof cut - 4)
    {
        width += glyph_of(set, (uint8_t)text[keep])->advance;
        if (width > max_width)
        {
            break;
        }
        ++keep;
    }
    memcpy(cut, text, (size_t)keep);
    strcpy(cut + keep, "...");
    gfx_text(x, y, cut, scale, argb);
}

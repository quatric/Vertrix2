#include "actor_gate.h"
#include "actor_storage.h"
#include <string.h>

/* Original render globals touched by 0x4ae3e0: type, name, executable address. Fields keep their
 * original widths; coordinates are stored as words and read signed where the original used
 * movsx/sar. Bytes of the block that are not listed here are preserved. */
#define GATE_GLOBALS(F)                                                                            \
    F(uint16_t, count, 0x5bb68a)                                                                   \
    F(uint16_t, columns, 0x5bb68c)                                                                 \
    F(uint16_t, saved_si, 0x5bb68e)                                                                \
    F(uint16_t, sum, 0x5bb690)                                                                     \
    F(uint32_t, indexed, 0x5bb694)                                                                 \
    F(uint8_t, layer, 0x5bb730)                                                                    \
    F(uint8_t, image_flag, 0x5bb731)                                                               \
    F(uint8_t, depth, 0x5bb732)                                                                    \
    F(uint8_t, surface_kind, 0x5bb733)                                                             \
    F(uint32_t, image, 0x5bb734)                                                                   \
    F(uint8_t, index, 0x5bb738)                                                                    \
    F(uint8_t, actor_93, 0x5bb739)                                                                 \
    F(uint8_t, actor_8c, 0x5bb73a)                                                                 \
    F(uint32_t, cell, 0x5bb73c)                                                                    \
    F(uint16_t, cell_x, 0x5bb740)                                                                  \
    F(uint16_t, cell_y, 0x5bb742)                                                                  \
    F(uint16_t, map_width, 0x5bb744)                                                               \
    F(uint16_t, map_height, 0x5bb746)                                                              \
    F(uint16_t, right, 0x5bb748)                                                                   \
    F(uint16_t, bottom, 0x5bb74a)                                                                  \
    F(uint16_t, scaled_width, 0x5bb74c)                                                            \
    F(uint16_t, scaled_height, 0x5bb74e)                                                           \
    F(uint16_t, clip_width, 0x5bb750)                                                              \
    F(uint16_t, clip_height, 0x5bb752)                                                             \
    F(uint32_t, destination_a, 0x5bb764)                                                           \
    F(uint32_t, destination_b, 0x5bb76c)                                                           \
    F(uint32_t, pixel_32_a, 0x5bb768)                                                              \
    F(uint32_t, pixel_32_b, 0x5bb770)                                                              \
    F(uint32_t, pixel_8_a, 0x5bb778)                                                               \
    F(uint32_t, pixel_8_b, 0x5bb77c)                                                               \
    F(uint32_t, pixel_16_a, 0x5bb780)                                                              \
    F(uint32_t, pixel_16_b, 0x5bb784)                                                              \
    F(uint32_t, skip, 0x5bb790)                                                                    \
    F(uint32_t, slack, 0x5bb794)                                                                   \
    F(uint16_t, surface_width, 0x5bb798)                                                           \
    F(uint32_t, skipped_columns, 0x5bb79c)                                                         \
    F(uint16_t, x, 0x5bb7a0)                                                                       \
    F(uint16_t, y, 0x5bb7a2)                                                                       \
    F(uint16_t, origin_x, 0x5bb7a4)                                                                \
    F(uint16_t, origin_y, 0x5bb7a6)                                                                \
    F(uint16_t, mask_top, 0x5bb7a8)                                                                \
    F(uint16_t, mask_bottom, 0x5bb7aa)                                                             \
    F(uint16_t, mask_rows, 0x5bb7ac)                                                               \
    F(uint16_t, lift, 0x5bb7ae)                                                                    \
    F(uint16_t, anchor_x, 0x5bb7b0)                                                                \
    F(uint16_t, anchor_y, 0x5bb7b2)                                                                \
    F(uint16_t, image_width, 0x5bb7b4)                                                             \
    F(uint16_t, image_height, 0x5bb7b6)                                                            \
    F(uint8_t, actor_80, 0x5bb7b8)                                                                 \
    F(uint32_t, surface_columns, 0x5bb7bc)                                                         \
    F(uint32_t, source_width, 0x5bb7c0)                                                            \
    F(uint32_t, surface_pitch, 0x5bb7c4)                                                           \
    F(uint32_t, row_base, 0x5bb7c8)                                                                \
    F(uint32_t, cursor, 0x5bb7cc)                                                                  \
    F(uint32_t, scan, 0x5bb7d0)                                                                    \
    F(uint32_t, table_a, 0x5bb7d4)                                                                 \
    F(uint32_t, table_b, 0x5bb7d8)                                                                 \
    F(uint16_t, row_sum, 0x5bb7e0)                                                                 \
    F(uint32_t, mask_source, 0x5bb7e4)                                                             \
    F(uint32_t, mask_scan, 0x5bb7e8)                                                               \
    F(uint32_t, mask_cursor, 0x5bbfec)                                                             \
    F(uint8_t, mask_flag, 0x5bbff0)                                                                \
    F(uint16_t, start_x, 0x5bbff2)                                                                 \
    F(uint16_t, start_y, 0x5bbff4)                                                                 \
    F(uint16_t, limit_left, 0x5bbff6)                                                              \
    F(uint16_t, limit_right, 0x5bbff8)                                                             \
    F(uint16_t, limit_top, 0x5bbffa)                                                               \
    F(uint16_t, limit_bottom, 0x5bbffc)                                                            \
    F(uint8_t, clip_kind, 0x5bbffe)                                                                \
    F(uint8_t, image_mask, 0x5bbfff)                                                               \
    F(uint8_t, shift, 0x5bc000)                                                                    \
    F(uint16_t, shift_step, 0x5bc002)                                                              \
    F(uint8_t, shift_code, 0x5bc004)                                                               \
    F(uint8_t, no_mask, 0x5bc005)                                                                  \
    F(uint8_t, actor_94, 0x5bc00c)                                                                 \
    F(uint8_t, actor_95, 0x5bc00d)                                                                 \
    F(uint8_t, power, 0x5bc00e)                                                                    \
    F(uint32_t, surface, 0x5bc010)                                                                 \
    F(uint8_t, clipped, 0x5bc014)                                                                  \
    F(uint16_t, saved_di, 0x5bc016)

#define MASK_ARRAY 0x5bb7ecu
#define MASK_WORDS 0x400u
#define OBJECT_POINTER 0x544070u
#define SCALE_TABLE 0x5c1b00u
#define SKIP_TABLE 0x5c1c00u
#define FLAG_CLEAR_LAYER 0x0d

/* Actor storage offsets. */
enum
{
    ACTOR_X = 0xe,
    ACTOR_Y = 0x16,
    ACTOR_LIFT = 0x1e,
    ACTOR_INDEX = 0x44,
    ACTOR_SHIFT_STEP = 0x48,
    ACTOR_POWER = 0x4e,
    ACTOR_SHIFT = 0x52,
    ACTOR_FLAG_80 = 0x80,
    ACTOR_FLAG_8C = 0x8c,
    ACTOR_CLIP_KIND = 0x8e,
    ACTOR_NO_MASK = 0x8f,
    ACTOR_MAP_INDEX = 0x91,
    ACTOR_MAP_SHIFT = 0x92,
    ACTOR_FLAG_93 = 0x93,
    ACTOR_FLAG_94 = 0x94,
    ACTOR_FLAG_95 = 0x95,
    ACTOR_LIMIT_LEFT = 0xa8,
    ACTOR_LIMIT_RIGHT = 0xaa,
    ACTOR_LIMIT_TOP = 0xac,
    ACTOR_LIMIT_BOTTOM = 0xae,
    ACTOR_IMAGE = 0xb4,
    ACTOR_RECTANGLE_LOCKED = 0x13c
};

/* Image descriptor offsets. */
enum
{
    IMAGE_PIXELS = 0x0,
    IMAGE_WIDTH = 0x4,
    IMAGE_HEIGHT = 0x8,
    IMAGE_ANCHOR_X = 0xc,
    IMAGE_ANCHOR_Y = 0x10,
    IMAGE_MASK = 0x26,
    IMAGE_FLAG = 0x27
};

/* Surface descriptor offsets. */
enum
{
    SURFACE_PIXELS = 0x0,
    SURFACE_WIDTH = 0x4,
    SURFACE_HEIGHT = 0x8,
    SURFACE_DEPTH = 0xc,
    SURFACE_KIND = 0xd,
    SURFACE_PITCH = 0x14,
    SURFACE_OFFSET = 0x18
};

/* Map object offsets (object pointer at 0x544070). */
enum
{
    MAP_WIDTH = 0x208,
    MAP_HEIGHT = 0x20c,
    MAP_ORIGIN_X = 0x214,
    MAP_ORIGIN_Y = 0x216,
    MAP_INDEX_FROM_CELL = 0x220,
    MAP_INDEX_DEFAULT = 0x221,
    MAP_SHIFT_FROM_CELL = 0x222,
    MAP_SHIFT_STEP_DEFAULT = 0x223,
    MAP_SHIFT_DEFAULT = 0x224,
    MAP_LIFT = 0x226,
    MAP_SHIFT_CELLS = 0x26c,
    MAP_INDEX_CELLS = 0x270,
    MAP_MASK_CELLS = 0x274
};

/* Surface kinds and clip kinds. */
enum
{
    SURFACE_KIND_UNSUPPORTED = 3,
    CLIP_SURFACE_A = 0,
    CLIP_SURFACE_B = 1,
    CLIP_NONE = 2,
    CLIP_ACTOR = 3,
    INDEX_UNSCALED = 0x10,
    POWER_NO_FLAG = 0x64
};

#define DECLARE(type, name, address) type name;
typedef struct
{
    GATE_GLOBALS(DECLARE)
    uint16_t mask[MASK_WORDS];
} Globals;

typedef struct
{
    Globals g;
    uint8_t actor[VERTRIX_ACTOR_BASE_SIZE];
    VertrixMemoryRead read;
    void *context;
    int failed;
    uint32_t mode;
    uint16_t si;
    uint16_t di;
    uint32_t result;
} Run;

static uint32_t block_get(const uint8_t *block, uint32_t address, unsigned width)
{
    uint32_t value = 0;
    for (unsigned i = 0; i < width; ++i)
    {
        value |= (uint32_t)block[address - VERTRIX_GATE_BASE + i] << (8 * i);
    }
    return value;
}

static void block_put(uint8_t *block, uint32_t address, unsigned width, uint32_t value)
{
    for (unsigned i = 0; i < width; ++i)
    {
        block[address - VERTRIX_GATE_BASE + i] = (uint8_t)(value >> (8 * i));
    }
}

#define UNPACK(type, name, address) g->name = (type)block_get(block, address, sizeof g->name);
#define PACK(type, name, address) block_put(block, address, sizeof g->name, g->name);

static void globals_unpack(Globals *g, const uint8_t *block)
{
    GATE_GLOBALS(UNPACK)
    for (unsigned i = 0; i < MASK_WORDS; ++i)
    {
        g->mask[i] = (uint16_t)block_get(block, MASK_ARRAY + 2 * i, 2);
    }
}

static void globals_pack(const Globals *g, uint8_t *block)
{
    GATE_GLOBALS(PACK)
    for (unsigned i = 0; i < MASK_WORDS; ++i)
    {
        block_put(block, MASK_ARRAY + 2 * i, 2, g->mask[i]);
    }
}

static int in_globals(uint32_t address, unsigned width)
{
    return (uint64_t)address < (uint64_t)VERTRIX_GATE_BASE + VERTRIX_GATE_SIZE &&
           (uint64_t)address + width > VERTRIX_GATE_BASE;
}

/* Read original memory outside the globals. Pointers into the globals are only followed through
 * mask_slot. */
static uint32_t load(Run *r, uint32_t address, unsigned width)
{
    uint32_t value = 0;
    if (in_globals(address, width) || !r->read || !r->read(address, width, &value, r->context))
    {
        r->failed = 1;
        return 0;
    }
    return value;
}

static uint32_t u8(Run *r, uint32_t address)
{
    return load(r, address, 1);
}

static uint32_t u16(Run *r, uint32_t address)
{
    return load(r, address, 2);
}

static uint32_t u32(Run *r, uint32_t address)
{
    return load(r, address, 4);
}

static uint32_t actor_load(Run *r, size_t offset, unsigned width)
{
    uint32_t value = 0;
    if (!vertrix_actor_storage_read(r->actor, sizeof r->actor, offset, width, &value))
    {
        r->failed = 1;
    }
    return value;
}

/* Word of the per-column mask array addressed by an original pointer. */
static uint16_t *mask_slot(Run *r, uint32_t address)
{
    uint32_t offset = address - MASK_ARRAY;
    if (address < MASK_ARRAY || offset % 2 != 0 || offset / 2 >= MASK_WORDS)
    {
        r->failed = 1;
        return &r->g.mask[0];
    }
    return &r->g.mask[offset / 2];
}

static int32_t sword(uint16_t value)
{
    return (int16_t)value;
}

static uint16_t word(int32_t value)
{
    return (uint16_t)value;
}

static int finish(Run *r, uint32_t result)
{
    r->result = result;
    return 0;
}

/* Original0x4ae110: record the visible rectangle in actor words 128/12a and dwords 12c/130. */
static void set_rectangle(Run *r, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    vertrix_actor_storage_write(r->actor, sizeof r->actor, 0x128, 2, x);
    vertrix_actor_storage_write(r->actor, sizeof r->actor, 0x12a, 2, y);
    vertrix_actor_storage_write(r->actor, sizeof r->actor, 0x12c, 4, width);
    vertrix_actor_storage_write(r->actor, sizeof r->actor, 0x130, 4, height);
}

/* Original0x478eb0: address of pixel (x, y) in a surface descriptor. */
static uint32_t pixel_address(Run *r, uint32_t surface, int32_t x, int32_t y)
{
    uint32_t base = u32(r, surface + SURFACE_PIXELS);
    uint32_t row = (uint32_t)y * u32(r, surface + SURFACE_PITCH);
    return base + row + u8(r, surface + SURFACE_DEPTH) * (uint32_t)x;
}

/* 0x4ae3e0..0x4ae5db: capture actor, image and surface fields. Returns 0 when finished. */
static int capture(Run *r)
{
    Globals *g = &r->g;
    if (actor_load(r, ACTOR_RECTANGLE_LOCKED, 4) == 0)
    {
        set_rectangle(r, 0, 0, 0, 0);
    }
    r->di = g->saved_di;
    uint32_t image = actor_load(r, ACTOR_IMAGE, 4);
    r->si = g->saved_si;
    g->image = image;
    if (image == 0 || g->surface == 0)
    {
        return finish(r, 0);
    }
    g->image_flag = (uint8_t)u8(r, image + IMAGE_FLAG);
    g->depth = (uint8_t)u8(r, g->surface + SURFACE_DEPTH);
    g->surface_kind = (uint8_t)u8(r, g->surface + SURFACE_KIND);
    if (g->surface_kind == SURFACE_KIND_UNSUPPORTED)
    {
        return finish(r, 0);
    }
    g->origin_x = (uint16_t)actor_load(r, ACTOR_X, 2);
    g->cell_x = g->origin_x;
    g->origin_y = (uint16_t)actor_load(r, ACTOR_Y, 2);
    g->cell_y = g->origin_y;
    g->x = g->origin_x;
    g->y = g->origin_y;
    g->lift = (uint16_t)actor_load(r, ACTOR_LIFT, 2);
    g->anchor_x = (uint16_t)u16(r, image + IMAGE_ANCHOR_X);
    g->anchor_y = (uint16_t)u16(r, image + IMAGE_ANCHOR_Y);
    g->image_width = (uint16_t)u16(r, image + IMAGE_WIDTH);
    uint16_t image_height = (uint16_t)u16(r, image + IMAGE_HEIGHT);
    g->image_mask = (uint8_t)u8(r, image + IMAGE_MASK);
    g->actor_93 = (uint8_t)actor_load(r, ACTOR_FLAG_93, 1);
    g->skip = 0;
    g->image_height = image_height;
    g->actor_94 = (uint8_t)actor_load(r, ACTOR_FLAG_94, 1);
    g->no_mask = (uint8_t)actor_load(r, ACTOR_NO_MASK, 1);
    g->actor_95 = (uint8_t)actor_load(r, ACTOR_FLAG_95, 1);
    g->clip_kind = (uint8_t)actor_load(r, ACTOR_CLIP_KIND, 1);
    g->power = (uint8_t)actor_load(r, ACTOR_POWER, 1);
    if (g->power == POWER_NO_FLAG)
    {
        g->actor_93 = 0;
    }
    g->actor_8c = (uint8_t)actor_load(r, ACTOR_FLAG_8C, 1);
    g->actor_80 = (uint8_t)actor_load(r, ACTOR_FLAG_80, 1);
    if (r->mode == 0)
    {
        uint32_t object = u32(r, OBJECT_POINTER);
        g->map_width = (uint16_t)u16(r, object + MAP_WIDTH);
        g->map_height = (uint16_t)u16(r, object + MAP_HEIGHT);
        g->x = word((int32_t)g->x - (int32_t)u16(r, object + MAP_ORIGIN_X));
        g->y = word((int32_t)g->y - (int32_t)u16(r, object + MAP_ORIGIN_Y));
        g->lift = word((int32_t)g->lift + (int32_t)u16(r, object + MAP_LIFT));
    }
    return 1;
}

/* Clamp one map cell coordinate to 0..size-1 as the original does (signed word compares). */
static uint16_t clamp_cell(uint16_t value, uint16_t size)
{
    if (sword(value) < 0)
    {
        value = 0;
    }
    return sword(value) >= sword(size) ? word((int32_t)size - 1) : value;
}

/* 0x4ae5db..0x4ae6b5, mode 0: clamp the map cell and compute its linear index. */
static void locate_cell(Run *r)
{
    Globals *g = &r->g;
    g->cell_x = clamp_cell(g->cell_x, g->map_width);
    g->cell_y = clamp_cell(g->cell_y, g->map_height);
    g->cell = (uint32_t)(sword(g->map_width) * sword(g->cell_y) + sword(g->cell_x));
}

/* Image index: actor byte, map default, or the byte of the map's index cells (plus one). */
static uint8_t choose_index(Run *r)
{
    if (r->mode == 1 || actor_load(r, ACTOR_MAP_INDEX, 1) == 0)
    {
        return (uint8_t)actor_load(r, ACTOR_INDEX, 1);
    }
    uint32_t object = u32(r, OBJECT_POINTER);
    if (u8(r, object + MAP_INDEX_FROM_CELL) == 0)
    {
        return (uint8_t)u8(r, object + MAP_INDEX_DEFAULT);
    }
    uint32_t cells = u32(r, u32(r, object + MAP_INDEX_CELLS));
    return (uint8_t)(u8(r, cells + r->g.cell) + 1);
}

/* Shift fields: actor values, map default, or decoded from the map's shift cells. */
static void choose_shift(Run *r)
{
    Globals *g = &r->g;
    if (r->mode == 1 || actor_load(r, ACTOR_MAP_SHIFT, 1) == 0)
    {
        g->shift = (uint8_t)actor_load(r, ACTOR_SHIFT, 1);
        g->shift_step = (uint16_t)actor_load(r, ACTOR_SHIFT_STEP, 2);
        return;
    }
    uint32_t object = u32(r, OBJECT_POINTER);
    if (u8(r, object + MAP_SHIFT_FROM_CELL) == 0)
    {
        g->shift_step = word((int32_t)(int8_t)u8(r, object + MAP_SHIFT_STEP_DEFAULT));
        g->shift = (uint8_t)u8(r, object + MAP_SHIFT_DEFAULT);
        return;
    }
    uint32_t cells = u32(r, u32(r, object + MAP_SHIFT_CELLS));
    g->shift_code = (uint8_t)u8(r, cells + g->cell);
    g->shift = g->shift_code >> 3;
    int32_t step = (int8_t)(uint8_t)((g->shift_code & 7) - 5);
    g->shift_step = word(step * (step >= 0 ? 0x28 : 0x14));
}

static void select_index(Run *r)
{
    Globals *g = &r->g;
    g->layer = FLAG_CLEAR_LAYER;
    if (r->mode == 0)
    {
        locate_cell(r);
    }
    g->index = choose_index(r);
    g->indexed = g->index != INDEX_UNSCALED;
    choose_shift(r);
}

/* 0x4aed56: scaled size from the 16-entry table, in units of 1/16 image size.
 * Returns 0 for a zero image size (a divide fault in the original). */
static int scale_size(Run *r)
{
    Globals *g = &r->g;
    uint32_t row = (uint32_t)g->index << 4;
    uint32_t width = g->image_width;
    uint32_t height = g->image_height;
    g->scaled_width =
        word((int32_t)((width >> 4) * g->index + u8(r, SCALE_TABLE + row + (width & 0xf))));
    g->scaled_height =
        word((int32_t)((height >> 4) * g->index + u8(r, SCALE_TABLE + row + (height & 0xf))));
    if (width == 0 || height == 0)
    {
        r->failed = 1;
        return 0;
    }
    g->anchor_x = word((sword(g->anchor_x) * sword(g->scaled_width)) / (int32_t)width);
    g->anchor_y = word((sword(g->scaled_height) * sword(g->anchor_y)) / (int32_t)height);
    return 1;
}

/* Clip rectangle for the clip kind: the surface, the actor limits, none, or stale values. */
static void load_limits(Run *r)
{
    Globals *g = &r->g;
    if (g->clip_kind == CLIP_SURFACE_A || g->clip_kind == CLIP_SURFACE_B)
    {
        g->limit_left = 0;
        g->limit_top = 0;
        g->limit_right = word((int32_t)u16(r, g->surface + SURFACE_WIDTH) - 1);
        g->limit_bottom = word((int32_t)u16(r, g->surface + SURFACE_HEIGHT) - 1);
    }
    else if (g->clip_kind == CLIP_ACTOR)
    {
        g->limit_left = (uint16_t)actor_load(r, ACTOR_LIMIT_LEFT, 2);
        g->limit_right = (uint16_t)actor_load(r, ACTOR_LIMIT_RIGHT, 2);
        g->limit_top = (uint16_t)actor_load(r, ACTOR_LIMIT_TOP, 2);
        g->limit_bottom = (uint16_t)actor_load(r, ACTOR_LIMIT_BOTTOM, 2);
    }
}

/* 0x4ae6c2..0x4ae80a: image rectangle in surface coordinates and its trivial-reject test. */
static int place_rectangle(Run *r)
{
    Globals *g = &r->g;
    if (g->indexed == 0)
    {
        g->scaled_width = g->image_width;
        g->scaled_height = g->image_height;
    }
    else if (!scale_size(r))
    {
        return 0;
    }
    if (g->scaled_width == 0 || g->scaled_height == 0)
    {
        return finish(r, 0);
    }
    g->clip_width = g->scaled_width;
    g->clip_height = g->scaled_height;
    g->x = word((int32_t)g->x - g->anchor_x);
    uint16_t y = word((int32_t)g->y - g->anchor_y);
    g->y = word((int32_t)y - g->lift);
    g->right = word((int32_t)g->x + g->scaled_width - 1);
    g->start_y = g->y;
    g->bottom = word((int32_t)g->y + g->scaled_height - 1);
    g->start_x = g->x;
    if (g->clip_kind == CLIP_NONE)
    {
        return 1;
    }
    load_limits(r);
    if (sword(g->x) > sword(g->limit_right) || sword(g->right) < sword(g->limit_left) ||
        sword(g->y) > sword(g->limit_bottom) || sword(g->bottom) < sword(g->limit_top))
    {
        return finish(r, 0);
    }
    return 1;
}

/* 0x4ae80a..0x4ae967: clip to the limits, accumulating skipped image data (unscaled images). */
static int clip(Run *r)
{
    Globals *g = &r->g;
    g->clipped = 0;
    if (g->clip_kind != CLIP_NONE)
    {
        if (sword(g->y) < sword(g->limit_top))
        {
            if (g->indexed == 0)
            {
                int32_t rows = sword(g->limit_top) - sword(g->y);
                g->skip += (uint32_t)(sword(g->scaled_width) * rows);
            }
            g->y = g->limit_top;
            g->clipped = 1;
        }
        if (sword(g->x) < sword(g->limit_left))
        {
            if (g->indexed == 0)
            {
                g->skip += (uint32_t)(sword(g->limit_left) - sword(g->x));
            }
            g->x = g->limit_left;
            g->clipped = 1;
        }
        if (sword(g->bottom) > sword(g->limit_bottom))
        {
            g->bottom = g->limit_bottom;
            g->clipped = 1;
        }
        if (sword(g->right) > sword(g->limit_right))
        {
            g->right = g->limit_right;
            g->clipped = 1;
        }
    }
    g->skipped_columns = 0;
    if (g->clipped)
    {
        g->clip_width = word((int32_t)g->right - g->x + 1);
        g->clip_height = word((int32_t)g->bottom - g->y + 1);
        g->skipped_columns = (uint32_t)(sword(g->scaled_width) - sword(g->clip_width));
        if (g->clip_width == 0 || g->clip_height == 0)
        {
            return finish(r, 0);
        }
    }
    return 1;
}

/* Sum count bytes of the skip table starting at *cursor; counter lives in the shared count word. */
static uint16_t sum_table(Run *r, uint32_t *cursor, uint16_t count)
{
    uint16_t sum = 0;
    r->g.count = count;
    while (count != 0 && !r->failed)
    {
        sum = word((int32_t)sum + (int32_t)u8(r, *cursor));
        *cursor += 1;
        count = word((int32_t)count - 1);
        r->g.count = count;
    }
    return sum;
}

/* 0x4ae967..0x4aeab0: indexed images read their skipped rows/columns from the skip table. */
static void skip_table(Run *r)
{
    Globals *g = &r->g;
    uint32_t table = SKIP_TABLE + ((uint32_t)g->index << 10);
    g->table_a = table;
    g->table_b = table;
    if (g->clipped)
    {
        uint16_t rows = word((int32_t)g->y - g->start_y);
        g->count = rows;
        if (rows != 0)
        {
            g->sum = 0;
            uint16_t sum = sum_table(r, &g->table_a, rows);
            g->sum = sum;
            g->skip += (uint32_t)g->image_width * sum;
        }
        uint16_t columns = word((int32_t)g->x - g->start_x);
        g->count = columns;
        while (columns != 0 && !r->failed)
        {
            g->skip += u8(r, g->table_b);
            g->table_b += 1;
            columns = word((int32_t)columns - 1);
            g->count = columns;
        }
    }
    g->cursor = g->table_a;
    g->row_sum = 0;
    g->row_sum = sum_table(r, &g->cursor, word((int32_t)g->clip_height - 1));
}

/* Clamp a mask row index to the map height as the original does. */
static void clamp_mask_rows(Run *r)
{
    Globals *g = &r->g;
    g->mask_bottom = clamp_cell(g->mask_bottom, g->map_height);
    g->mask_top = clamp_cell(g->mask_top, g->map_height);
}

/* Start of the mask data for the given row. */
static uint32_t mask_row_start(Run *r, int32_t row)
{
    Globals *g = &r->g;
    uint32_t object = u32(r, OBJECT_POINTER);
    uint32_t cells = u32(r, u32(r, object + MAP_MASK_CELLS));
    return cells + (uint32_t)sword(g->x) + u16(r, object + MAP_ORIGIN_X) +
           (uint32_t)(row * sword(g->map_width));
}

/* Rows whose mask bits stay set when scanning upward from the cursor; returns the remaining count.
 */
static uint16_t scan_up(Run *r, uint32_t cursor)
{
    Globals *g = &r->g;
    g->scan = cursor;
    r->si = g->mask_rows;
    while (r->si != 0 && !r->failed)
    {
        uint32_t scan = g->scan;
        if ((u8(r, scan) & 3) == 0)
        {
            break;
        }
        g->scan = scan - (uint32_t)sword(g->map_width);
        r->si = word((int32_t)r->si - 1);
    }
    return r->si;
}

/* 0x4aead0..0x4aef74: mark the columns of the transparent image whose mask is fully covered. */
static void mask_columns(Run *r)
{
    Globals *g = &r->g;
    int32_t bytes = 2 * sword(g->clip_width);
    if (bytes < 0 || bytes > (int32_t)(2 * MASK_WORDS))
    {
        r->failed = 1;
        return;
    }
    memset(g->mask, 0, (size_t)bytes);
    g->mask_bottom = word((int32_t)g->origin_y - g->anchor_y + g->scaled_height - 1);
    g->mask_top = word((int32_t)g->mask_bottom - g->lift);
    if (sword(g->origin_y) < sword(g->mask_bottom))
    {
        g->mask_bottom = g->origin_y;
    }
    r->di = g->saved_di;
    r->si = g->saved_si;
    clamp_mask_rows(r);
    g->mask_rows = word((int32_t)g->mask_bottom - g->mask_top + 1);
    g->columns = 0;
    g->count = 0;
    g->cursor = mask_row_start(r, sword(g->mask_bottom));
    while (sword(g->count) < sword(g->clip_width) && !r->failed)
    {
        uint32_t cursor = g->cursor;
        int covered = (u8(r, cursor) & 3) != 0;
        if (covered && sword(g->mask_rows) > 1 && scan_up(r, cursor) != 0)
        {
            covered = 0;
        }
        if (covered)
        {
            g->columns = word((int32_t)g->columns + 1);
            *mask_slot(r, MASK_ARRAY + 2 * (uint32_t)sword(g->count)) = 1;
        }
        g->cursor += 1;
        g->count = word((int32_t)g->count + 1);
    }
    g->saved_si = r->si;
    g->saved_di = r->di;
    if (g->columns == g->clip_width || g->columns != 0)
    {
        g->mask_flag = 1;
    }
    r->di = g->saved_di;
    r->si = g->saved_si;
}

/* 0x4aefae..0x4af0e8: count mask rows per marked column, walking upward through the mask data. */
static void mask_rows(Run *r)
{
    Globals *g = &r->g;
    uint32_t object = u32(r, OBJECT_POINTER);
    int32_t bottom = sword(g->bottom) + (int32_t)u16(r, object + MAP_ORIGIN_Y);
    g->mask_source = mask_row_start(r, bottom);
    g->mask_cursor = MASK_ARRAY;
    g->columns = g->clip_width;
    while (g->columns != 0 && !r->failed)
    {
        uint16_t *slot = mask_slot(r, g->mask_cursor);
        if (*slot != 0)
        {
            r->di = g->clip_height;
            *slot = 0;
            g->mask_scan = g->mask_source;
            while (r->di != 0 && !r->failed)
            {
                uint32_t row = g->mask_scan;
                if ((u8(r, row) & 3) == 0)
                {
                    break;
                }
                g->mask_scan = row - (uint32_t)sword(g->map_width);
                *slot = word((int32_t)*slot + 1);
                r->di = word((int32_t)r->di - 1);
            }
        }
        g->mask_source += 1;
        g->mask_cursor += 2;
        g->columns = word((int32_t)g->columns - 1);
    }
}

/* 0x4af09a..0x4af0e8: first mask row for the drawn rectangle. */
static void mask_start(Run *r)
{
    Globals *g = &r->g;
    uint32_t object = u32(r, OBJECT_POINTER);
    int32_t top = sword(g->y) + (int32_t)u16(r, object + MAP_ORIGIN_Y);
    g->mask_source = mask_row_start(r, top);
    g->mask_scan = g->mask_source;
}

/* Surface pixel address for the surface depth, stored in the matching global pair. */
static void locate_pixel(Run *r)
{
    Globals *g = &r->g;
    if (g->depth != 1 && g->depth != 2 && g->depth != 4)
    {
        return;
    }
    uint32_t address = pixel_address(r, g->surface, sword(g->x), sword(g->y));
    if (g->depth == 4)
    {
        g->pixel_32_a = address;
        g->pixel_32_b = address;
    }
    else if (g->depth == 2)
    {
        g->pixel_16_a = address;
        g->pixel_16_b = address;
    }
    else
    {
        g->pixel_8_a = address;
        g->pixel_8_b = address;
    }
}

/* 0x4af0ee..0x4af212: publish cursors and pitch, and the actor rectangle when not locked. */
static void publish(Run *r)
{
    Globals *g = &r->g;
    uint32_t surface = g->surface;
    uint32_t pixels = u32(r, g->image + IMAGE_PIXELS) + (g->skip << 2);
    g->destination_a = pixels;
    g->destination_b = pixels;
    g->surface_width = (uint16_t)u16(r, surface + SURFACE_WIDTH);
    g->source_width = g->image_width;
    g->surface_columns = (uint32_t)sword(g->surface_width);
    int32_t slack = sword(g->surface_width) - sword(g->clip_width);
    g->surface_pitch = u32(r, surface + SURFACE_PITCH);
    g->slack = (uint32_t)slack;
    g->row_base = g->depth * (uint32_t)slack + u32(r, surface + SURFACE_OFFSET);
    g->saved_si = r->si;
    g->saved_di = r->di;
    locate_pixel(r);
    if (actor_load(r, ACTOR_RECTANGLE_LOCKED, 4) == 0)
    {
        set_rectangle(r, g->x, g->y, (uint32_t)sword(g->clip_width),
                      (uint32_t)sword(g->clip_height));
    }
    r->di = g->saved_di;
    r->si = g->saved_si;
    r->result = 1;
}

static void run_gate(Run *r)
{
    Globals *g = &r->g;
    if (!capture(r))
    {
        return;
    }
    select_index(r);
    if (!place_rectangle(r) || r->failed || !clip(r))
    {
        return;
    }
    if (g->indexed == 1)
    {
        skip_table(r);
    }
    g->saved_si = r->si;
    g->mask_flag = 0;
    g->saved_di = r->di;
    if (r->mode == 0 && u32(r, u32(r, OBJECT_POINTER) + MAP_MASK_CELLS) != 0 && g->no_mask == 0)
    {
        mask_columns(r);
    }
    r->di = g->saved_di;
    r->si = g->saved_si;
    if (g->mask_flag != 0)
    {
        mask_rows(r);
        mask_start(r);
    }
    publish(r);
}

int vertrix_actor_gate(uint8_t *globals, void *actor, size_t actor_size, uint32_t mode,
                       VertrixMemoryRead read, void *context, uint32_t *result)
{
    Run run;
    uint8_t block[VERTRIX_GATE_SIZE];
    if (!globals || !actor || !result || actor_size < VERTRIX_ACTOR_BASE_SIZE || !read)
    {
        return 0;
    }
    memcpy(block, globals, sizeof block);
    globals_unpack(&run.g, block);
    memcpy(run.actor, actor, sizeof run.actor);
    run.read = read;
    run.context = context;
    run.failed = 0;
    run.mode = mode;
    run.result = 0;
    run.si = 0;
    run.di = 0;
    run_gate(&run);
    run.g.saved_di = run.di;
    run.g.saved_si = run.si;
    if (run.failed)
    {
        return 0;
    }
    globals_pack(&run.g, block);
    memcpy(globals, block, sizeof block);
    memcpy(actor, run.actor, sizeof run.actor);
    *result = run.result;
    return 1;
}

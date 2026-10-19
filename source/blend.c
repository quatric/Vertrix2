#include "blend.h"

enum
{
    SOURCE_PIXEL = 0x5bb764,
    TARGET_PIXEL = 0x5bb768,
    COLOUR_ENTRIES = 0x54b800,
    CHANNEL_MAPS = 0x54cdc8,
    ENTRY = 0x54d5d4,
    MAP = 0x54d5d0,
    TINT_RED = 0x54d5dc,
    TINT_GREEN = 0x54d5de,
    TINT_BLUE = 0x54d5e0,
    REMAPPED = 0x5bc018,
    RAW_SUM = 0x54d624,
    ROW_COUNT = 0x5bc016,
    PIXEL_OPERATION = 0x5bb72c,
    PIXEL_SIZE = 4,
    SOURCE_LEVELS = 0x55f1f0,
    ROWS = 0x5bb750,
    WIDTH = 0x5bb752,
    MASK_STRIDE = 0x5bb742,
    SOURCE_STRIDE = 0x5bb74a,
    TARGET_STRIDE = 0x5bb7c4,
    MASK_ROW = 0x5bb7e8,
    SOURCE_ROW = 0x5bb76c,
    TARGET_ROW = 0x5bb770,
    MASK_PIXEL = 0x5bb7e4,
    ROW_STARTS = 0x5bb7ec,
    ROW_START = 0x5bbfec,
    SHADE_LEVELS = 0x5785f8,
    SHADE_STEPS = 0x5785fc,
    SAMPLE_STEPS = 0x5bb7dc,
    ROW_INDEX = 0x5bb7d4,
    ROW_SCALE = 0x5bb7c0,
    NEXT_SAMPLE_STEPS = 0x5bb7d8,
    TARGET_LEVELS = 0x55f1f4,
    CHANNELS = 0xffffff,
    LOW_BITS_CLEAR = 0xfefeff,
    CARRIES = 0x1010100,
    HALF = 0x7f7f7f,
    SOURCE_SKIP = 0x5bb79c,
    TARGET_SKIP = 0x5bb7c8,
    KEY_SHIFT = 24,
    TARGET_PIXEL_16 = 0x5bb780,
    WIDE_TARGET = 0x5bb774,
    GLOBALS_LOW = 0x544000,
    GLOBALS_HIGH = 0x5bc100
};

/* The globals the ports below read and write, reached in place where the host maps the image
 * (port_window); any access outside the window, or without one, takes the usual path. Every port
 * here opens it again after port_open. The image never moves, so the window stays valid across
 * the calls a port makes. */
static PortWindow blend_globals;

/* The flat blocks in place for the routines below that make no call (port_windows_flat), set while
 * one of them runs and NULL otherwise; blend_u8 to blend_set32 go through it when it is set. */
static const PortWindows *blend_reach;

__attribute__((noinline)) static uint32_t reach_get(Port *port, uint32_t base, uint32_t offset,
                                                    unsigned size)
{
    return port_windows_get(port, blend_reach, base, offset, size);
}

__attribute__((noinline)) static void reach_put(Port *port, uint32_t base, uint32_t offset,
                                                unsigned size, uint32_t value)
{
    port_windows_put(port, blend_reach, base, offset, size, value);
}

static inline uint32_t blend_get(Port *port, uint32_t base, uint32_t offset, unsigned size)
{
    return blend_reach != NULL ? reach_get(port, base, offset, size)
                               : lift_load(&port->env, base, offset, size);
}

static inline void blend_put(Port *port, uint32_t base, uint32_t offset, unsigned size,
                             uint32_t value)
{
    if (blend_reach != NULL)
    {
        reach_put(port, base, offset, size, value);
    }
    else
    {
        lift_store(&port->env, base, offset, size, value);
    }
}

static inline uint32_t blend_u8(Port *port, uint32_t base, uint32_t offset)
{
    return blend_get(port, base, offset, 1);
}

static inline uint32_t blend_u16(Port *port, uint32_t base, uint32_t offset)
{
    return blend_get(port, base, offset, 2);
}

static inline uint32_t blend_u32(Port *port, uint32_t base, uint32_t offset)
{
    return blend_get(port, base, offset, 4);
}

static inline void blend_set8(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    blend_put(port, base, offset, 1, value);
}

static inline void blend_set16(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    blend_put(port, base, offset, 2, value);
}

static inline void blend_set32(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    blend_put(port, base, offset, 4, value);
}

/* The entry index of a colour: the top six bits of each channel, red highest. */
static uint32_t entry_index(uint32_t colour)
{
    return (((colour & 0xfc0000) >> 4) | ((colour & 0xfc00) >> 2) | (colour & 0xfc)) >> 2;
}

/* The remapped colour of a colour entry (both tables described in blend.h). */
static uint32_t remap_entry(Port *port, uint32_t entry)
{
    uint32_t map;
    uint32_t red;
    uint32_t green;
    port_window_set32(port, &blend_globals, 0, ENTRY, entry);
    map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), (entry & 0xff) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    red = blend_u8(port, map, entry >> 24) << 16;
    green = blend_u8(port, map, (entry >> 16) & 0xff) << 8;
    return red | green | blend_u8(port, map, (entry >> 8) & 0xff);
}

static uint32_t remap(Port *port, uint32_t colour)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    return remap_entry(port, blend_u32(port, entries, entry_index(colour) * 4));
}

static uint32_t remap_tint(Port *port, uint32_t colour)
{
    uint32_t select = blend_u8(port, port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES),
                               entry_index(colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    uint32_t red = blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_RED)) << 16;
    uint32_t green;
    port_window_set32(port, &blend_globals, 0, MAP, map);
    green = blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_GREEN)) << 8;
    return red | green | blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_BLUE));
}

static uint32_t source_colour(Port *port)
{
    return blend_u32(port, port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL), 0);
}

/* The sum of two colours with each channel saturating at 0xff (the raw sum goes to 0x54d624). */
static uint32_t add_saturated(Port *port, uint32_t first, uint32_t second)
{
    uint32_t sum = (first & LOW_BITS_CLEAR) + (second & LOW_BITS_CLEAR);
    uint32_t full = CARRIES - ((sum & CARRIES) >> 7);
    port_window_set32(port, &blend_globals, 0, RAW_SUM, sum);
    return full | sum;
}

/* `first` less `second` with each channel stopping at 0 (the raw difference goes to 0x54d624). */
static uint32_t subtract_saturated(Port *port, uint32_t first, uint32_t second)
{
    uint32_t difference = (first & LOW_BITS_CLEAR) - (second & LOW_BITS_CLEAR);
    uint32_t keep = ((difference & CARRIES) >> 7) - 0x1010101;
    port_window_set32(port, &blend_globals, 0, RAW_SUM, difference);
    return keep & difference;
}

/* Add `colour` to the target pixel at `target`, each channel saturating at 0xff. */
static void add_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t sum = add_saturated(port, blend_u32(port, target, 0), colour);
    blend_set32(port, target, 0, sum & CHANNELS);
}

/* Subtract `colour` from the target pixel at `target`, each channel stopping at 0. */
static void subtract_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t difference = subtract_saturated(port, blend_u32(port, target, 0), colour);
    blend_set32(port, target, 0, difference & CHANNELS);
}

static uint32_t average(uint32_t first, uint32_t second)
{
    return ((first >> 1) & HALF) + ((second >> 1) & HALF);
}

static uint32_t blend_copy_body(Port *port)
{
    uint32_t colour;
    colour = source_colour(port);
    blend_set32(port, port_window_u32(port, &blend_globals, 0, TARGET_PIXEL), 0, colour);
    return colour;
}

uint32_t vertrix_port_blend_copy(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_copy_body(&port), entry->edx);
}

static uint32_t blend_remap_body(Port *port)
{
    uint32_t colour;
    colour = remap(port, source_colour(port));
    blend_set32(port, port_window_u32(port, &blend_globals, 0, TARGET_PIXEL), 0, colour);
    return colour;
}

uint32_t vertrix_port_blend_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_body(&port), entry->edx);
}

static uint32_t blend_add_body(Port *port)
{
    uint32_t target;
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    add_saturate(port, target, source_colour(port));
    return target;
}

uint32_t vertrix_port_blend_add(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_add_body(&port), entry->edx);
}

static uint32_t blend_subtract_body(Port *port)
{
    uint32_t target;
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    subtract_saturate(port, target, source_colour(port));
    return target;
}

uint32_t vertrix_port_blend_subtract(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_subtract_body(&port), entry->edx);
}

static uint32_t blend_average_remap_body(Port *port)
{
    uint32_t source;
    uint32_t target;
    uint32_t mixed;
    source = port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL);
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    mixed = average(blend_u32(port, source, 0), blend_u32(port, target, 0));
    blend_set32(port, target, 0, mixed);
    blend_set32(port, target, 0, remap(port, blend_u32(port, target, 0)));
    return target;
}

uint32_t vertrix_port_blend_average_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_average_remap_body(&port), entry->edx);
}

static uint32_t blend_remap_add_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    add_saturate(port, target, colour);
    return target;
}

uint32_t vertrix_port_blend_remap_add(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_add_body(&port), entry->edx);
}

static uint32_t blend_remap_subtract_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    subtract_saturate(port, target, colour);
    return target;
}

uint32_t vertrix_port_blend_remap_subtract(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_subtract_body(&port), entry->edx);
}

static uint32_t blend_tint_average_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap_tint(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    blend_set32(port, target, 0, average(blend_u32(port, target, 0), colour));
    return target;
}

uint32_t vertrix_port_blend_tint_average(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_tint_average_body(&port), entry->edx);
}

static uint32_t blend_tint_add_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap_tint(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    add_saturate(port, target, colour);
    return target;
}

uint32_t vertrix_port_blend_tint_add(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_tint_add_body(&port), entry->edx);
}

/* A colour remapped half way to the fixed channels (described at 0x48d8c0 in blend.h). */
static uint32_t half_tint(Port *port, uint32_t colour)
{
    uint32_t entry_value;
    uint32_t map;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    entry_value = blend_u32(port, port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES),
                            entry_index(colour) * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, entry_value);
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS),
                    (entry_value & 0xff) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    red = blend_u8(port, map,
                   ((entry_value >> 24) + port_window_u16(port, &blend_globals, 0, TINT_RED)) >> 1);
    green = blend_u8(
        port, map,
        (((entry_value >> 16) & 0xff) + port_window_u16(port, &blend_globals, 0, TINT_GREEN)) >> 1);
    blue = blend_u8(
        port, map,
        (((entry_value >> 8) & 0xff) + port_window_u16(port, &blend_globals, 0, TINT_BLUE)) >> 1);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t blend_half_tint_body(Port *port)
{
    uint32_t colour;
    colour = half_tint(port, source_colour(port));
    blend_set32(port, port_window_u32(port, &blend_globals, 0, TARGET_PIXEL), 0, colour);
    return colour;
}

uint32_t vertrix_port_blend_half_tint(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_half_tint_body(&port), entry->edx);
}

/* A row loop's per-pixel operation, the routine at [0x5bb72c]. When the dispatcher would run one
 * of the blend ports below for it, the loop runs that port's own C on its own Port: the blend
 * reads and writes only globals and pixels, which resolve the same from either frame, and the call
 * boundary cost more than the blend. Anything else is called as before. */
typedef uint32_t (*PixelBody)(Port *port);

typedef struct PixelOperation
{
    uint32_t target; /* the routine looked up last (0: none yet) */
    PixelBody body;
    unsigned index; /* the frame index the dispatcher would set for it */
} PixelOperation;

static PixelBody pixel_body(LiftRoutine routine);

static uint32_t pixel_call(Port *port, PixelOperation *operation, uint32_t eax, uint32_t edx,
                           uint32_t ebx, uint32_t ecx)
{
    uint32_t target = port_window_u32(port, &blend_globals, 0, PIXEL_OPERATION);
    if (target != operation->target)
    {
        LiftRoutine routine =
            vertrix_lift_routine_hook != NULL
                ? vertrix_lift_routine_hook(port->env.calls, target, &operation->index)
                : NULL;
        operation->target = target;
        operation->body = routine != NULL ? pixel_body(routine) : NULL;
    }
    if (operation->body != NULL)
    {
        vertrix_lift_frame_index = operation->index;
        eax = operation->body(port);
        vertrix_lift_edx = edx; /* as the blend's port_return leaves it */
        return eax;
    }
    {
        /* The call may allocate or release: the flat windows are opened again after it. */
        PortWindows *reach = (PortWindows *)blend_reach;
        blend_reach = NULL;
        eax = port_call(port, target, eax, edx, ebx, ecx);
        if (reach != NULL)
        {
            port_windows_flat(port, reach);
            blend_reach = reach;
        }
        return eax;
    }
}

/* 0x492400's row with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t render_row32_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT);
    while (count != 0)
    {
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        eax = pixel_call(&port, &operation, eax, (edx & 0xffff0000u) | count, ebx, ecx);
        edx = vertrix_lift_edx;
        count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT);
        ecx = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) + PIXEL_SIZE;
        ebx = port_window_u32(&port, &blend_globals, 0, target_pixel) + step;
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, ecx);
        port_window_set32(&port, &blend_globals, 0, target_pixel, ebx);
        count = (count - 1) & 0xffff;
    }
    port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_row32(PORT_SIGNATURE)
{
    return render_row32_at(calls, services, globals, entry, TARGET_PIXEL, PIXEL_SIZE);
}

uint32_t vertrix_port_render_row32_49a120(PORT_SIGNATURE)
{
    return render_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

uint32_t vertrix_port_render_row32_4a21e0(PORT_SIGNATURE)
{
    return render_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

/* The two-table sum of 0x490560 and 0x4902a0: each channel of the source looked up in the byte
 * table at [0x55f1f0] plus the target's in the table at [0x55f1f4]. The sums can reach 0x1fe:
 * they are or-ed into place, not added. */
static uint32_t levels_mix_values(Port *port, uint32_t source, uint32_t target)
{
    uint32_t source_levels = port_window_u32(port, &blend_globals, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_window_u32(port, &blend_globals, 0, TARGET_LEVELS);
    uint32_t red = blend_u8(port, source_levels, (source >> 16) & 0xff) +
                   blend_u8(port, target_levels, (target >> 16) & 0xff);
    uint32_t green = blend_u8(port, source_levels, (source >> 8) & 0xff) +
                     blend_u8(port, target_levels, (target >> 8) & 0xff);
    uint32_t blue =
        blend_u8(port, source_levels, source & 0xff) + blend_u8(port, target_levels, target & 0xff);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t levels_mix(Port *port, uint32_t source, uint32_t target)
{
    return levels_mix_values(port, blend_u32(port, source, 0), blend_u32(port, target, 0));
}

static uint32_t blend_levels_remap_body(Port *port)
{
    uint32_t target;
    uint32_t mixed;
    uint32_t entries;
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    mixed = levels_mix(port, port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL), target);
    entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    blend_set32(port, target, 0, mixed);
    blend_set32(port, target, 0,
                remap_entry(port, blend_u32(port, entries, entry_index(mixed) * 4)));
    return target;
}

uint32_t vertrix_port_blend_levels_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_levels_remap_body(&port), entry->edx);
}

static uint32_t blend_levels_body(Port *port)
{
    uint32_t target;
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    blend_set32(port, target, 0,
                levels_mix(port, port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL), target));
    return target;
}

uint32_t vertrix_port_blend_levels(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_levels_body(&port), entry->edx);
}

static uint32_t blend_shade_body(Port *port)
{
    uint32_t entries;
    uint32_t colour_entry;
    uint32_t target;
    uint32_t shade;
    uint32_t level;
    uint32_t map;
    uint32_t red;
    uint32_t green;
    entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    colour_entry = blend_u32(port, entries, entry_index(source_colour(port)) * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, colour_entry);
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    shade = blend_u8(port, entries, entry_index(blend_u32(port, target, 0)) * 4);
    level = blend_u16(port, port_window_u32(port, &blend_globals, 0, SHADE_LEVELS),
                      (colour_entry & 0xff) * 2) +
            blend_u16(port, port_window_u32(port, &blend_globals, 0, SHADE_STEPS), shade * 2);
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS),
                    (uint32_t)((int32_t)(int16_t)level * 4));
    port_window_set32(port, &blend_globals, 0, MAP, map);
    red = blend_u8(port, map, colour_entry >> 24) << 16;
    green = blend_u8(port, map, (colour_entry >> 16) & 0xff) << 8;
    blend_set32(port, target, 0, red | green | blend_u8(port, map, (colour_entry >> 8) & 0xff));
    return target;
}

uint32_t vertrix_port_blend_shade(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_shade_body(&port), entry->edx);
}

/* 0x492550's row with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t render_sampled_row32_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t source;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT);
    do
    {
        eax = blend_u32(&port, source, 0);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
        eax >>= 24;
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        if (eax != 0)
        {
            eax =
                pixel_call(&port, &operation, eax, edx, (entry->ebx & 0xffff0000u) | count, source);
        }
        eax = port_window_u32(&port, &blend_globals, 0, SAMPLE_STEPS);
        source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) +
                 (blend_u8(&port, eax, 0) << 2);
        count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT);
        edx = port_window_u32(&port, &blend_globals, 0, target_pixel) + step;
        eax++;
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, eax);
        port_window_set32(&port, &blend_globals, 0, target_pixel, edx);
        count = (count - 1) & 0xffff;
    } while (count != 0);
    port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
    port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_sampled_row32(PORT_SIGNATURE)
{
    return render_sampled_row32_at(calls, services, globals, entry, TARGET_PIXEL, PIXEL_SIZE);
}

uint32_t vertrix_port_render_sampled_row32_49a270(PORT_SIGNATURE)
{
    return render_sampled_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

uint32_t vertrix_port_render_sampled_row32_4a2330(PORT_SIGNATURE)
{
    return render_sampled_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

/* 0x492280's row with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t render_keyed_row32_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t source;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT);
    while (count != 0)
    {
        eax = blend_u32(&port, source, 0);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        eax >>= 24;
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
        if (eax != 0)
        {
            eax =
                pixel_call(&port, &operation, eax, (edx & 0xffff0000u) | count, entry->ebx, source);
        }
        edx = port_window_u32(&port, &blend_globals, 0, target_pixel) + step;
        source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
        port_window_set32(&port, &blend_globals, 0, target_pixel, edx);
        count = (port_window_u16(&port, &blend_globals, 0, ROW_COUNT) - 1) & 0xffff;
        source += PIXEL_SIZE;
    }
    port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
    port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_keyed_row32(PORT_SIGNATURE)
{
    return render_keyed_row32_at(calls, services, globals, entry, TARGET_PIXEL, PIXEL_SIZE);
}

uint32_t vertrix_port_render_keyed_row32_499fb0(PORT_SIGNATURE)
{
    return render_keyed_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

uint32_t vertrix_port_render_keyed_row32_4a2070(PORT_SIGNATURE)
{
    return render_keyed_row32_at(calls, services, globals, entry, 0x5bb780, 2);
}

/* The signed high word of a dword global: the original reads the dword and shifts it right. */
static uint32_t high_word(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_window_u32(port, &blend_globals, 0, address) >> 16);
}

/* 0x492980's rows with the target pixel and row at `target_pixel` and `row_global`, `step` bytes
 * each. */
static uint32_t render_image_rows_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t row_global,
                                     uint32_t step)
{
    Port port;
    uint32_t routine = entry->eax;
    uint32_t last;
    uint32_t mask;
    uint32_t source_step;
    uint32_t eax;
    uint32_t start = ROW_STARTS;
    uint32_t target_row;
    uint32_t rows;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    last = high_word(&port, ROWS) - 1;
    mask =
        port_window_u32(&port, &blend_globals, 0, MASK_ROW) + high_word(&port, MASK_STRIDE) * last;
    source_step = high_word(&port, SOURCE_STRIDE) * last;
    eax = last * port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
    source_step = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW) + (source_step << 2);
    target_row = port_window_u32(&port, &blend_globals, 0, row_global);
    port_window_set32(&port, &blend_globals, 0, MASK_ROW, mask);
    port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, source_step);
    port_window_set32(&port, &blend_globals, 0, row_global, target_row + eax);
    rows = port_window_u16(&port, &blend_globals, 0, ROWS);
    while (rows != 0)
    {
        uint32_t width = port_window_u16(&port, &blend_globals, 0, WIDTH);
        uint32_t target = port_window_u32(&port, &blend_globals, 0, row_global);
        uint32_t source;
        port_window_set32(&port, &blend_globals, 0, ROW_START, start);
        width -= blend_u16(&port, start, 0);
        port_window_set32(&port, &blend_globals, 0, target_pixel, target);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, width);
        mask = port_window_u32(&port, &blend_globals, 0, MASK_ROW);
        target += step;
        source = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW);
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, mask);
        port_window_set32(&port, &blend_globals, 0, row_global, target);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
        mask++;
        source += 4;
        port_window_set32(&port, &blend_globals, 0, MASK_ROW, mask);
        port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, source);
        eax = port_call(&port, routine, source, target, routine, mask);
        start = port_window_u32(&port, &blend_globals, 0, ROW_START) + 2;
        rows = (port_window_u16(&port, &blend_globals, 0, ROWS) - 1) & 0xffff;
        port_window_set16(&port, &blend_globals, 0, ROWS, rows);
    }
    port_window_set32(&port, &blend_globals, 0, ROW_START, start);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_image_rows(PORT_SIGNATURE)
{
    return render_image_rows_at(calls, services, globals, entry, TARGET_PIXEL, TARGET_ROW, 4);
}

uint32_t vertrix_port_render_image_rows_49a690(PORT_SIGNATURE)
{
    return render_image_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784, 2);
}

uint32_t vertrix_port_render_image_rows_4a2750(PORT_SIGNATURE)
{
    return render_image_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784, 2);
}

/* 0x4928f0's rows with the target pixel and row at `target_pixel` and `target_row`. */
static uint32_t render_indexed_rows_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t target_row)
{
    Port port;
    uint32_t routine = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    ebx = port_window_u32(&port, &blend_globals, 0, target_row);
    esi = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW);
    do
    {
        uint32_t index = port_window_u32(&port, &blend_globals, 0, ROW_INDEX);
        edi = port_window_u32(&port, &blend_globals, 0, ROW_SCALE);
        edx = blend_u8(&port, index, 0) * edi;
        port_window_set32(&port, &blend_globals, 0, ROW_INDEX, index + 1);
        ebx += port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
        eax = port_window_u32(&port, &blend_globals, 0, NEXT_SAMPLE_STEPS);
        port_window_set32(&port, &blend_globals, 0, target_row, ebx);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, eax);
        edx <<= 2;
        eax = (eax & 0xffff0000u) | port_window_u16(&port, &blend_globals, 0, ROWS);
        esi += edx;
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, eax);
        port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, esi);
        eax = port_call_with(&port, routine, eax, edx, ebx, routine, esi, edi, entry->ebp);
        esi = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW);
        ebx = port_window_u32(&port, &blend_globals, 0, target_row);
        count = port_window_u16(&port, &blend_globals, 0, WIDTH);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, esi);
        port_window_set32(&port, &blend_globals, 0, target_pixel, ebx);
        count = (count - 1) & 0xffff;
        port_window_set16(&port, &blend_globals, 0, WIDTH, count);
    } while (count != 0);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_indexed_rows(PORT_SIGNATURE)
{
    return render_indexed_rows_at(calls, services, globals, entry, TARGET_PIXEL, TARGET_ROW);
}

uint32_t vertrix_port_render_indexed_rows_49a600(PORT_SIGNATURE)
{
    return render_indexed_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784);
}

uint32_t vertrix_port_render_indexed_rows_4a26c0(PORT_SIGNATURE)
{
    return render_indexed_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784);
}

uint32_t vertrix_port_render_indexed_rows_4aa3c0(PORT_SIGNATURE)
{
    return render_indexed_rows_at(calls, services, globals, entry, 0x5bb778, 0x5bb77c);
}

/* The step back of a masked row's skipped part (0x492499 and 0x492386): the source and target
 * pixel and the mask move back one pixel, and the start word at [0x5bbfec] counts down. */
static void mask_skip_step(Port *port, MaskRegisters *r, uint32_t target_pixel)
{
    uint32_t start;
    r->edx = port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL) -
             (high_word(port, SOURCE_STRIDE) << 2);
    r->ecx = port_window_u32(port, &blend_globals, 0, target_pixel);
    port_window_set32(port, &blend_globals, 0, SOURCE_PIXEL, r->edx);
    r->ecx -= port_window_u32(port, &blend_globals, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    r->edx = port_window_u32(port, &blend_globals, 0, MASK_PIXEL) - r->eax;
    start = port_window_u32(port, &blend_globals, 0, ROW_START);
    port_window_set32(port, &blend_globals, 0, target_pixel, r->ecx);
    blend_set16(port, start, 0, blend_u16(port, start, 0) - 1);
    r->eax = start;
}

/* The step back after a drawn pixel (0x4924f3 and 0x49232c): the same moves, with the pixel count
 * at 0x5bc016 counting down. */
static void mask_draw_step(Port *port, MaskRegisters *r, uint32_t target_pixel)
{
    uint32_t target;
    r->edx = port_window_u32(port, &blend_globals, 0, MASK_PIXEL);
    r->ebx = port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL) -
             (high_word(port, SOURCE_STRIDE) << 2);
    target = port_window_u32(port, &blend_globals, 0, target_pixel);
    port_window_set16(port, &blend_globals, 0, ROW_COUNT,
                      port_window_u16(port, &blend_globals, 0, ROW_COUNT) - 1);
    target -= port_window_u32(port, &blend_globals, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    port_window_set32(port, &blend_globals, 0, SOURCE_PIXEL, r->ebx);
    port_window_set32(port, &blend_globals, 0, target_pixel, target);
    r->edx -= r->eax;
}

/* The source pixel's alpha (top) byte. */
static uint32_t source_alpha(Port *port)
{
    return blend_u32(port, port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL), 0) >> 24;
}

static uint32_t mask_row(Port *port, const LiftEntry *entry, int alpha, uint32_t target_pixel)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    MaskRegisters r = {entry->eax, 0, entry->ebx, entry->ecx};
    port_windows_flat(port, &flat);
    blend_reach = &flat;
    r.edx = port_window_u32(port, &blend_globals, 0, MASK_PIXEL);
    for (;;)
    {
        r.eax = port_window_u32(port, &blend_globals, 0, ROW_START);
        if (blend_u16(port, r.eax, 0) == 0)
        {
            break;
        }
        r.ebx = (r.ebx & 0xffffff00u) | blend_u8(port, r.edx, 0);
        port_window_set32(port, &blend_globals, 0, MASK_PIXEL, r.edx);
        if ((r.ebx & 1) == 0)
        {
            if (alpha)
            {
                r.eax = source_alpha(port);
            }
            if (!alpha || r.eax != 0)
            {
                r.eax = pixel_call(port, &operation, r.eax, r.edx, r.ebx, r.ecx);
            }
        }
        mask_skip_step(port, &r, target_pixel);
    }
    while (port_window_u16(port, &blend_globals, 0, ROW_COUNT) != 0)
    {
        if (alpha)
        {
            r.eax = source_alpha(port);
        }
        port_window_set32(port, &blend_globals, 0, MASK_PIXEL, r.edx);
        if (!alpha || r.eax != 0)
        {
            r.eax = pixel_call(port, &operation, r.eax, r.edx, r.ebx, r.ecx);
        }
        mask_draw_step(port, &r, target_pixel);
    }
    port_window_set32(port, &blend_globals, 0, MASK_PIXEL, r.edx);
    blend_reach = NULL;
    return r.eax;
}

/* 0x492460's row with the target pixel at `target_pixel`. */
static uint32_t render_mask_row_at(PORT_SIGNATURE, uint32_t target_pixel)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    eax = mask_row(&port, entry, 0, target_pixel);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_mask_row(PORT_SIGNATURE)
{
    return render_mask_row_at(calls, services, globals, entry, TARGET_PIXEL);
}

uint32_t vertrix_port_render_mask_row_49a180(PORT_SIGNATURE)
{
    return render_mask_row_at(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_mask_row_4a2240(PORT_SIGNATURE)
{
    return render_mask_row_at(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_mask_row_4a9f40(PORT_SIGNATURE)
{
    return render_mask_row_at(calls, services, globals, entry, 0x5bb778);
}

uint32_t vertrix_port_render_mask_alpha_row(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    eax = mask_row(&port, entry, 1, TARGET_PIXEL);
    return port_return(&port, eax, entry->edx);
}

/* 0x492770's masked row drawn backwards, the target pixel at `target_pixel`: first the row start's
 * skipped part (pixels whose mask byte has bit 0 clear are drawn), then the row count's pixels;
 * each step moves the source back by a sampled step (0x5bb7dc, scaled by 0x5bb7c0), the target by
 * the stride and the mask by its stride. */
static uint32_t mask_row_back(PORT_SIGNATURE, uint32_t target_pixel)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL);
    for (;;)
    {
        uint32_t steps;
        uint32_t target;
        uint32_t start;
        eax = port_window_u32(&port, &blend_globals, 0, ROW_START);
        if (blend_u16(&port, eax, 0) == 0)
        {
            break;
        }
        edx = (edx & 0xffffff00u) | blend_u8(&port, ecx, 0);
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
        if ((edx & 1) == 0)
        {
            eax = pixel_call(&port, &operation, eax, edx, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        steps = port_window_u32(&port, &blend_globals, 0, SAMPLE_STEPS);
        edx = blend_u8(&port, steps, 0) * port_window_u32(&port, &blend_globals, 0, ROW_SCALE);
        target = port_window_u32(&port, &blend_globals, 0, target_pixel);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, steps - 1);
        target -= port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
        ebx = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) - (edx << 2);
        edx <<= 2;
        ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL) - high_word(&port, MASK_STRIDE);
        start = port_window_u32(&port, &blend_globals, 0, ROW_START);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, ebx);
        ebx = ((ebx & 0xffff0000u) | blend_u16(&port, start, 0)) - 1;
        port_window_set32(&port, &blend_globals, 0, target_pixel, target);
        blend_set16(&port, start, 0, ebx);
    }
    while (port_window_u16(&port, &blend_globals, 0, ROW_COUNT) != 0)
    {
        uint32_t steps;
        uint32_t count;
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
        eax = pixel_call(&port, &operation, eax, edx, ebx, ecx);
        steps = port_window_u32(&port, &blend_globals, 0, SAMPLE_STEPS);
        edx = blend_u8(&port, steps, 0) * port_window_u32(&port, &blend_globals, 0, ROW_SCALE);
        ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, steps - 1);
        eax = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) - (edx << 2);
        count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT) - 1;
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, eax);
        edx = port_window_u32(&port, &blend_globals, 0, target_pixel) -
              port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
        eax = high_word(&port, MASK_STRIDE);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        port_window_set32(&port, &blend_globals, 0, target_pixel, edx);
        ecx -= eax;
    }
    port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_mask_row_back_492770(PORT_SIGNATURE)
{
    return mask_row_back(calls, services, globals, entry, TARGET_PIXEL);
}

uint32_t vertrix_port_render_mask_row_back_49a480(PORT_SIGNATURE)
{
    return mask_row_back(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_mask_row_back_4a2540(PORT_SIGNATURE)
{
    return mask_row_back(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_mask_row_back_4aa240(PORT_SIGNATURE)
{
    return mask_row_back(calls, services, globals, entry, 0x5bb778);
}

static uint32_t blend_average_body(Port *port)
{
    uint32_t target;
    uint32_t source;
    source = port_window_u32(port, &blend_globals, 0, SOURCE_PIXEL);
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    blend_set32(port, target, 0, average(blend_u32(port, source, 0), blend_u32(port, target, 0)));
    return target;
}

uint32_t vertrix_port_blend_average(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_average_body(&port), entry->edx);
}

uint32_t vertrix_port_blit_copy(PORT_SIGNATURE)
{
    Port port;
    uint32_t run;
    uint32_t runs;
    uint32_t source;
    uint32_t target;
    uint32_t target_skip;
    uint32_t source_skip;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    run = port_window_u16(&port, &blend_globals, 0, ROWS);
    runs = port_window_u16(&port, &blend_globals, 0, WIDTH);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    target = port_window_u32(&port, &blend_globals, 0, TARGET_PIXEL);
    target_skip = port_window_u32(&port, &blend_globals, 0, TARGET_SKIP);
    source_skip = port_window_u32(&port, &blend_globals, 0, SOURCE_SKIP) << 2;
    for (; runs != 0; runs = (runs - 1) & 0xffff)
    {
        uint32_t left;
        for (left = run; left != 0; left = (left - 1) & 0xffff)
        {
            target += PIXEL_SIZE;
            blend_set32(&port, target, -4u, blend_u32(&port, source, 0));
            source += PIXEL_SIZE;
        }
        source += source_skip;
        target += target_skip;
    }
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blit_keyed(PORT_SIGNATURE)
{
    Port port;
    uint32_t run;
    uint32_t runs;
    uint32_t source;
    uint32_t target;
    uint32_t source_skip;
    uint32_t target_skip;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    run = port_window_u16(&port, &blend_globals, 0, ROWS);
    runs = port_window_u16(&port, &blend_globals, 0, WIDTH);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    target = port_window_u32(&port, &blend_globals, 0, TARGET_PIXEL);
    source_skip = port_window_u32(&port, &blend_globals, 0, SOURCE_SKIP) << 2;
    target_skip = port_window_u32(&port, &blend_globals, 0, TARGET_SKIP);
    for (; runs != 0; runs = (runs - 1) & 0xffff)
    {
        /* Each row's pixels in place where they can be. */
        PortWindow from = port_window(&port, source, (uint64_t)run * PIXEL_SIZE);
        PortWindow to = port_window(&port, target, (uint64_t)run * PIXEL_SIZE);
        uint32_t left;
        for (left = run; left != 0; left = (left - 1) & 0xffff)
        {
            uint32_t pixel = port_window_u32(&port, &from, source, 0);
            if ((pixel >> KEY_SHIFT) != 0)
            {
                port_window_set32(&port, &to, target, 0, pixel);
            }
            source += PIXEL_SIZE;
            target += PIXEL_SIZE;
        }
        target += target_skip;
        source += source_skip;
    }
    return port_return(&port, source, entry->edx);
}

/* levels_mix of a colour already in hand (the remapped one at 0x5bc018) over the target pixel. */
static uint32_t levels_mix_colour(Port *port, uint32_t colour, uint32_t target)
{
    return levels_mix_values(port, colour, blend_u32(port, target, 0));
}

static uint32_t blend_remap_levels_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    blend_set32(
        port, target, 0,
        levels_mix_colour(port, port_window_u32(port, &blend_globals, 0, REMAPPED), target));
    return target;
}

uint32_t vertrix_port_blend_remap_levels(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_levels_body(&port), entry->edx);
}

static uint32_t blend_tint_levels_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = remap_tint(port, source_colour(port));
    target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    blend_set32(
        port, target, 0,
        levels_mix_colour(port, port_window_u32(port, &blend_globals, 0, REMAPPED), target));
    return target;
}

uint32_t vertrix_port_blend_tint_levels(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_tint_levels_body(&port), entry->edx);
}

uint32_t vertrix_port_rectangle_half32(PORT_SIGNATURE)
{
    PortWindows flat;
    enum
    {
        COUNT = 0x5bc016,
        PIXEL = 0x5bb768,
        COLOR = 0x54d5ec,
        WIDTH = 0x5bb750,
        HEIGHT = 0x5bb752,
        PITCH_SKIP = 0x5bb7c8
    };
    Port port;
    uint32_t eax = entry->eax;
    uint32_t count;
    uint32_t pixel;
    uint32_t color;
    uint32_t width;
    uint32_t rows;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    count = port_window_u16(&port, &blend_globals, 0, COUNT);
    pixel = port_window_u32(&port, &blend_globals, 0, PIXEL);
    color = port_window_u32(&port, &blend_globals, 0, COLOR);
    width = port_window_u16(&port, &blend_globals, 0, WIDTH);
    rows = port_window_u16(&port, &blend_globals, 0, HEIGHT);
    /* Each pixel becomes half itself plus the colour (already halved). */
    for (; rows != 0; rows = (rows - 1) & 0xffff)
    {
        for (count = width; count != 0; count = (count - 1) & 0xffff)
        {
            eax = pixel;
            blend_set32(&port, pixel, 0, ((blend_u32(&port, pixel, 0) >> 1) & 0x7f7f7f) + color);
            pixel += 4;
        }
        eax = port_window_u32(&port, &blend_globals, 0, PITCH_SKIP);
        pixel += eax;
    }
    port_window_set16(&port, &blend_globals, 0, WIDTH, width);
    port_window_set16(&port, &blend_globals, 0, HEIGHT, rows);
    port_window_set32(&port, &blend_globals, 0, COLOR, color);
    port_window_set32(&port, &blend_globals, 0, PIXEL, pixel);
    port_window_set16(&port, &blend_globals, 0, COUNT, count);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_surface_mask32(PORT_SIGNATURE)
{
    PortWindows flat;
    enum
    {
        BELOW = 0x1c,
        DISPLAY = 0x544070,
        SOURCE = 0x5bb764,
        SOURCE_PITCH = 0x5bb79c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t width = entry->ebx;
    uint32_t rows = entry->ecx;
    uint32_t mask;
    uint32_t source;
    uint32_t pitch;
    uint32_t skip;
    uint32_t edx;
    uint32_t count;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    blend_set32(&port, ebp, -0xcu, (uint32_t)(int32_t)(int16_t)entry->eax);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE);
    /* The mask bytes at the position (0x478eb0 on the display's mask surface +0x274). */
    mask = port_call(&port, 0x478eb0,
                     blend_u32(&port, port_window_u32(&port, &blend_globals, 0, DISPLAY), 0x274),
                     (uint32_t)(int32_t)(int16_t)entry->eax, (uint32_t)(int32_t)(int16_t)entry->edx,
                     source);
    pitch = port_window_u32(&port, &blend_globals, 0, SOURCE_PITCH);
    blend_set32(&port, ebp, -0x18u, pitch);
    blend_set32(&port, ebp, -0xcu, (uint32_t)(int32_t)(int16_t)width);
    skip =
        blend_u32(&port,
                  blend_u32(&port, port_window_u32(&port, &blend_globals, 0, DISPLAY), 0x274), 4) -
        (uint32_t)(int32_t)(int16_t)width;
    blend_set32(&port, ebp, -0x10u, skip);
    edx = skip;
    if ((rows & 0xffff) == 0)
    {
        return port_return(&port, mask, edx);
    }
    blend_set32(&port, ebp, -0x14u, pitch << 2);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    /* Each source pixel with alpha sets bit 0 of its mask byte. */
    for (rows &= 0xffff; rows != 0; rows = (rows - 1) & 0xffff)
    {
        for (count = width & 0xffff; count != 0; count = (count - 1) & 0xffff)
        {
            uint32_t alpha = blend_u32(&port, source, 0) >> 24;
            blend_set32(&port, ebp, -0xcu, alpha);
            if (alpha != 0)
            {
                blend_set8(&port, mask, 0, blend_u8(&port, mask, 0) | 1);
            }
            source += 4;
            mask++;
        }
        edx = blend_u32(&port, ebp, -0x14u);
        source += edx;
        mask += blend_u32(&port, ebp, -0x10u);
    }
    blend_reach = NULL;
    return port_return(&port, mask, edx);
}

/* The narrow pixel formats: 16-bit 5-5-5 and 5-6-5 pixels at [0x5bb780] and 8-bit 3-3-2 pixels at
 * [0x5bb778]. Each family of narrow pixel operations has the same routines in the same order: the
 * 5-5-5 ones from 0x4933e0, the 5-6-5 ones from 0x49b4a0 and the 3-3-2 ones from 0x4a3540. */
enum
{
    PIXEL_555 = 0,
    PIXEL_565 = 1,
    PIXEL_332 = 2,
    TARGET_PIXEL_8 = 0x5bb778
};

/* A narrow pixel spread to eight bits a channel; and a colour narrowed back the same way (0x4974c0,
 * 0x49f580 and 0x4a73b0). */
static uint32_t widen16(uint32_t pixel, int format)
{
    if (format == PIXEL_332)
    {
        return ((pixel & 0xe0) << 16) | ((pixel & 0x1c) << 11) | ((pixel & 3) << 6);
    }
    if (format == PIXEL_565)
    {
        return ((pixel & 0xf800) << 8) | ((pixel & 0x7e0) << 5) | ((pixel & 0x1f) << 3);
    }
    return ((pixel & 0x7c00) << 9) | ((pixel & 0x3e0) << 6) | ((pixel & 0x1f) << 3);
}

static uint32_t narrow16(uint32_t colour, int format)
{
    if (format == PIXEL_332)
    {
        return (((colour & 0xe00000) >> 10) | ((colour & 0xe000) >> 5) | (colour & 0xc0)) >> 6;
    }
    if (format == PIXEL_565)
    {
        return (((colour & 0xf80000) >> 5) | ((colour & 0xfc00) >> 2) | (colour & 0xf8)) >> 3;
    }
    return (((colour & 0xf80000) >> 6) | ((colour & 0xf800) >> 3) | (colour & 0xf8)) >> 3;
}

/* The address of the narrow target pixel. */
static uint32_t target_pointer(Port *port, int format)
{
    return port_window_u32(port, &blend_globals, 0,
                           format == PIXEL_332 ? TARGET_PIXEL_8 : TARGET_PIXEL_16);
}

static uint32_t read_narrow(Port *port, uint32_t address, int format)
{
    if (format == PIXEL_332)
    {
        return blend_u8(port, address, 0);
    }
    return blend_u16(port, address, 0);
}

static void write_narrow(Port *port, uint32_t address, int format, uint32_t pixel)
{
    if (format == PIXEL_332)
    {
        blend_set8(port, address, 0, pixel);
    }
    else
    {
        blend_set16(port, address, 0, pixel);
    }
}

/* The 16-bit form of blend_levels: the target pixel at [0x5bb780] is widened into 0x5bb774, mixed
 * with the 32-bit source pixel by the two level tables, kept at 0x5bb774 and narrowed back. */
static uint32_t blend_levels16(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t mixed;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target_pointer(&port, format);
    mixed = levels_mix_values(
        &port, blend_u32(&port, port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL), 0),
        widen16(read_narrow(&port, target, format), format));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, mixed);
    write_narrow(&port, target, format, narrow16(mixed, format));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_levels16_4974c0(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_blend_levels16_4977c0(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_blend_levels16_49f580(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_blend_levels16_49f880(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, 1);
}

enum
{
    ADDED_COLOUR = 0x54d5ec
};

/* Store a colour narrowed to the 16-bit target pixel at [0x5bb780]; the narrowed pixel. */
static uint32_t put16(Port *port, uint32_t colour, int format)
{
    uint32_t pixel = narrow16(colour, format);
    write_narrow(port, target_pointer(port, format), format, pixel);
    return pixel;
}

/* A colour halved (each channel's low bit dropped) plus the colour at 0x54d5ec. */
static uint32_t half_plus(Port *port, uint32_t colour)
{
    return ((colour >> 1) & HALF) + port_window_u32(port, &blend_globals, 0, ADDED_COLOUR);
}

static uint32_t pixel16_copy(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    pixel = put16(&port, source_colour(&port), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_invert(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~source_colour(&port);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour & CHANNELS);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_invert_half_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~source_colour(&port) & CHANNELS;
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = half_plus(&port, colour);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_copy_4933e0(PORT_SIGNATURE)
{
    return pixel16_copy(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_copy_49b4a0(PORT_SIGNATURE)
{
    return pixel16_copy(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_4935c0(PORT_SIGNATURE)
{
    return pixel16_half_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_49b680(PORT_SIGNATURE)
{
    return pixel16_half_plus(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_493e70(PORT_SIGNATURE)
{
    return pixel16_invert(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_49bf30(PORT_SIGNATURE)
{
    return pixel16_invert(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_half_plus_495ac0(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_half_plus_49db80(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus(calls, services, globals, entry, 1);
}

/* The 16-bit target pixel at [0x5bb780] widened to eight bits a channel. */
static uint32_t target16(Port *port, int format)
{
    return widen16(read_narrow(port, target_pointer(port, format), format), format);
}

/* Keep a colour at 0x5bb774 and store it narrowed to the target pixel; the target's address. */
static uint32_t keep16(Port *port, uint32_t colour, int format)
{
    port_window_set32(port, &blend_globals, 0, WIDE_TARGET, colour);
    put16(port, colour, format);
    return target_pointer(port, format);
}

static uint32_t pixel16_average(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ((target16(&port, format) >> 1) & HALF) + ((source_colour(&port) >> 1) & HALF);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_invert_target(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour & CHANNELS);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_quarters_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ((source_colour(&port) >> 2) & 0x3f3f3f) + ((target16(&port, format) >> 2) & 0x3f3f3f);
    colour += port_window_u32(&port, &blend_globals, 0, ADDED_COLOUR);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_invert_target_half_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~target16(&port, format) & CHANNELS;
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), format), entry->edx);
}

uint32_t vertrix_port_pixel16_average_493970(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_average_49ba30(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_average_493ba0(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_average_49bc60(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_target_493ec0(PORT_SIGNATURE)
{
    return pixel16_invert_target(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_target_49bf80(PORT_SIGNATURE)
{
    return pixel16_invert_target(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_quarters_plus_494bc0(PORT_SIGNATURE)
{
    return pixel16_quarters_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_quarters_plus_49cc80(PORT_SIGNATURE)
{
    return pixel16_quarters_plus(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_target_half_plus_495d50(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_target_half_plus_49de10(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus(calls, services, globals, entry, 1);
}

static uint32_t pixel16_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

/* Keep the low 24 bits of a colour at 0x5bb774 and store it narrowed; the target's address. */
static uint32_t keep16_channels(Port *port, uint32_t colour, int format)
{
    port_window_set32(port, &blend_globals, 0, WIDE_TARGET, colour & CHANNELS);
    put16(port, colour, format);
    return target_pointer(port, format);
}

static uint32_t pixel16_add(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = add_saturated(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16_channels(&port, colour, format), entry->edx);
}

static uint32_t pixel16_subtract(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = subtract_saturated(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16_channels(&port, colour, format), entry->edx);
}

static uint32_t pixel16_subtract_from(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = subtract_saturated(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16_channels(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_tint_493500(PORT_SIGNATURE)
{
    return pixel16_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_49b5c0(PORT_SIGNATURE)
{
    return pixel16_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_add_493c30(PORT_SIGNATURE)
{
    return pixel16_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_add_49bcf0(PORT_SIGNATURE)
{
    return pixel16_add(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_subtract_493cf0(PORT_SIGNATURE)
{
    return pixel16_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_subtract_49bdb0(PORT_SIGNATURE)
{
    return pixel16_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_subtract_from_493db0(PORT_SIGNATURE)
{
    return pixel16_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_subtract_from_49be70(PORT_SIGNATURE)
{
    return pixel16_subtract_from(calls, services, globals, entry, 1);
}

/* keep16_channels returning the narrowed pixel instead. */
static uint32_t put16_channels(Port *port, uint32_t colour, int format)
{
    port_window_set32(port, &blend_globals, 0, WIDE_TARGET, colour & CHANNELS);
    return put16(port, colour, format);
}

static uint32_t pixel16_half_plus_add(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = add_saturated(&port, target16(&port, format), colour);
    pixel = put16_channels(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_subtract(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = subtract_saturated(&port, target16(&port, format), colour);
    pixel = put16_channels(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_subtract_from(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = subtract_saturated(&port, colour, target16(&port, format));
    pixel = put16_channels(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_half_plus_add_495060(PORT_SIGNATURE)
{
    return pixel16_half_plus_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_add_49d120(PORT_SIGNATURE)
{
    return pixel16_half_plus_add(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_subtract_4953f0(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_subtract_49d4b0(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_subtract_from_495780(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_subtract_from_49d840(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract_from(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_remap_493420(PORT_SIGNATURE)
{
    return pixel16_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_49b4e0(PORT_SIGNATURE)
{
    return pixel16_remap(calls, services, globals, entry, 1);
}

static uint32_t pixel16_invert_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~source_colour(&port);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, remap_tint(&port, colour), format), entry->edx);
}

static uint32_t pixel16_half_plus_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap(&port, half_plus(&port, source_colour(&port)));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

enum
{
    FIXED_ENTRIES = 0x54cdcc,
    FIXED_ENTRY = 0x54d5f0
};

/* The map `colour`'s entry selects (stored at 0x54d5d0) applied to the bytes 3, 2 and 1 of the
 * dword the pointer at entry [0x54d5f0] of the table at [0x54cdcc] points to (stored at 0x54d5d4).
 */
static uint32_t fixed_entry_remap(Port *port, uint32_t colour)
{
    uint32_t select = blend_u8(port, port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES),
                               entry_index(colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    uint32_t fixed;
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES),
                      port_window_u8(port, &blend_globals, 0, FIXED_ENTRY) * 4);
    fixed = blend_u32(port, fixed, 0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    return (blend_u8(port, map, fixed >> 24) << 16) |
           (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           blend_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_fixed_entry(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = fixed_entry_remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_invert_tint_4959e0(PORT_SIGNATURE)
{
    return pixel16_invert_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_tint_49daa0(PORT_SIGNATURE)
{
    return pixel16_invert_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_remap_493720(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_remap_49b7e0(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_fixed_entry_498570(PORT_SIGNATURE)
{
    return pixel16_fixed_entry(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_fixed_entry_4a0630(PORT_SIGNATURE)
{
    return pixel16_fixed_entry(calls, services, globals, entry, 1);
}

static uint32_t pixel16_remap_invert(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, ~colour & CHANNELS);
    put16(&port, ~colour, format);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

enum
{
    ENTRY_INDEX = 0x54d5e4,
    FIXED_SELECTS = 0x54b804
};

/* A colour remapped through its entry index twice (described at 0x498470 in blend.h). */
static uint32_t paired_remap(Port *port, uint32_t colour)
{
    uint32_t index = entry_index(colour);
    uint32_t map;
    uint32_t fixed;
    port_window_set32(port, &blend_globals, 0, ENTRY_INDEX, index);
    map = blend_u8(port, port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES), index * 4);
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), map * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS), index);
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    colour = blend_u8(port, map, fixed >> 24) << 16;
    colour |= blend_u8(port, map, (fixed >> 16) & 0xff) << 8;
    return colour | blend_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_paired_entry(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = paired_remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_remap_invert_494840(PORT_SIGNATURE)
{
    return pixel16_remap_invert(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_invert_49c900(PORT_SIGNATURE)
{
    return pixel16_remap_invert(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_entry_498470(PORT_SIGNATURE)
{
    return pixel16_paired_entry(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_entry_4a0530(PORT_SIGNATURE)
{
    return pixel16_paired_entry(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_tint_493610(PORT_SIGNATURE)
{
    return pixel16_half_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_tint_49b6d0(PORT_SIGNATURE)
{
    return pixel16_half_tint(calls, services, globals, entry, 1);
}

static uint32_t pixel16_invert_target_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, remap_tint(&port, colour), format), entry->edx);
}

static uint32_t pixel16_half_plus_paired(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = paired_remap(&port, colour);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_paired_invert(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = paired_remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, ~colour, format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_invert_target_tint_495c40(PORT_SIGNATURE)
{
    return pixel16_invert_target_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_target_tint_49dd00(PORT_SIGNATURE)
{
    return pixel16_invert_target_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_paired_498660(PORT_SIGNATURE)
{
    return pixel16_half_plus_paired(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_paired_4a0720(PORT_SIGNATURE)
{
    return pixel16_half_plus_paired(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_invert_499350(PORT_SIGNATURE)
{
    return pixel16_paired_invert(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_invert_4a1410(PORT_SIGNATURE)
{
    return pixel16_paired_invert(calls, services, globals, entry, 1);
}

static uint32_t pixel16_tint_average(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), format), entry->edx);
}

static uint32_t pixel16_invert_half_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~source_colour(&port);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, half_tint(&port, colour), format), entry->edx);
}

static uint32_t pixel16_invert_half_plus_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, ~source_colour(&port) & CHANNELS);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, remap(&port, colour), format), entry->edx);
}

uint32_t vertrix_port_pixel16_tint_average_494e10(PORT_SIGNATURE)
{
    return pixel16_tint_average(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_average_49ced0(PORT_SIGNATURE)
{
    return pixel16_tint_average(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_half_tint_495b20(PORT_SIGNATURE)
{
    return pixel16_invert_half_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_half_tint_49dbe0(PORT_SIGNATURE)
{
    return pixel16_invert_half_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_half_plus_remap_496cd0(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_half_plus_remap_49ed90(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus_remap(calls, services, globals, entry, 1);
}

/* The fixed channels remapped through the map selected by the entry of `map_colour` (stored at
 * 0x54d5d0); the entry of `entry_colour` is stored at 0x54d5d4. */
static uint32_t cross_tint(Port *port, uint32_t map_colour, uint32_t entry_colour)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t select = blend_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    port_window_set32(port, &blend_globals, 0, ENTRY,
                      blend_u32(port, entries, entry_index(entry_colour) * 4));
    return (blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_RED)) << 16) |
           (blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_GREEN)) << 8) |
           blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_BLUE));
}

static uint32_t pixel16_tint_add(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, add_saturated(&port, target, colour), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_tint_subtract(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, target, colour), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_tint_subtract_from(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, colour, target), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_target_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_tint(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_tint_add_494f30(PORT_SIGNATURE)
{
    return pixel16_tint_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_add_49cff0(PORT_SIGNATURE)
{
    return pixel16_tint_add(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_tint_subtract_4952c0(PORT_SIGNATURE)
{
    return pixel16_tint_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_subtract_49d380(PORT_SIGNATURE)
{
    return pixel16_tint_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_tint_subtract_from_495650(PORT_SIGNATURE)
{
    return pixel16_tint_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_subtract_from_49d710(PORT_SIGNATURE)
{
    return pixel16_tint_subtract_from(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_tint_496350(PORT_SIGNATURE)
{
    return pixel16_target_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_tint_49e410(PORT_SIGNATURE)
{
    return pixel16_target_tint(calls, services, globals, entry, 1);
}

/* The colour entry of `entry_colour` (stored at 0x54d5d4) remapped through the map selected by the
 * entry of `map_colour` (stored at 0x54d5d0). */
static uint32_t cross_remap(Port *port, uint32_t map_colour, uint32_t entry_colour)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t select = blend_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    uint32_t value;
    port_window_set32(port, &blend_globals, 0, MAP, map);
    value = blend_u32(port, entries, entry_index(entry_colour) * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    return (blend_u8(port, map, value >> 24) << 16) |
           (blend_u8(port, map, (value >> 16) & 0xff) << 8) |
           blend_u8(port, map, (value >> 8) & 0xff);
}

static uint32_t pixel16_cross_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_remap(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_average_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap(&port, average(target16(&port, format), source_colour(&port)));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_remap_average(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), format), entry->edx);
}

uint32_t vertrix_port_pixel16_cross_remap_493f40(PORT_SIGNATURE)
{
    return pixel16_cross_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_cross_remap_49c000(PORT_SIGNATURE)
{
    return pixel16_cross_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_average_remap_4941d0(PORT_SIGNATURE)
{
    return pixel16_average_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_average_remap_49c290(PORT_SIGNATURE)
{
    return pixel16_average_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_remap_average_494310(PORT_SIGNATURE)
{
    return pixel16_remap_average(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_average_49c3d0(PORT_SIGNATURE)
{
    return pixel16_remap_average(calls, services, globals, entry, 1);
}

static uint32_t pixel16_target_remap_invert(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = remap(&port, target16(&port, format));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, ~colour & CHANNELS);
    put16(&port, ~colour, format);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

static uint32_t pixel16_mean_map_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t entries;
    uint32_t select;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    entries = port_window_u32(&port, &blend_globals, 0, COLOUR_ENTRIES);
    select = blend_u8(&port, entries, entry_index(source_colour(&port)) * 4);
    select += blend_u8(&port, entries, entry_index(target16(&port, format)) * 4);
    map = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, CHANNEL_MAPS),
                    (select >> 1) * 4);
    port_window_set32(&port, &blend_globals, 0, MAP, map);
    colour = (blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_RED)) << 16) |
             (blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_GREEN)) << 8) |
             blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_BLUE));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_source_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_tint(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_target_remap_invert_494940(PORT_SIGNATURE)
{
    return pixel16_target_remap_invert(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_remap_invert_49ca00(PORT_SIGNATURE)
{
    return pixel16_target_remap_invert(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_mean_map_tint_494a80(PORT_SIGNATURE)
{
    return pixel16_mean_map_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_mean_map_tint_49cb40(PORT_SIGNATURE)
{
    return pixel16_mean_map_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_source_tint_495f40(PORT_SIGNATURE)
{
    return pixel16_source_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_source_tint_49e000(PORT_SIGNATURE)
{
    return pixel16_source_tint(calls, services, globals, entry, 1);
}

enum
{
    LEVEL_BIAS = 0x54d5e8
};

/* Each channel half the sum of the source's level, the target's level and the channel's byte at
 * 0x54d5e8, 0x54d5e9 or 0x54d5ea (the halves or-ed into place). */
static uint32_t levels_bias_values(Port *port, uint32_t source, uint32_t target)
{
    uint32_t source_levels = port_window_u32(port, &blend_globals, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_window_u32(port, &blend_globals, 0, TARGET_LEVELS);
    uint32_t red = blend_u8(port, source_levels, (source >> 16) & 0xff) +
                   blend_u8(port, target_levels, (target >> 16) & 0xff) +
                   port_window_u8(port, &blend_globals, 0, LEVEL_BIAS);
    uint32_t green = blend_u8(port, source_levels, (source >> 8) & 0xff) +
                     blend_u8(port, target_levels, (target >> 8) & 0xff) +
                     port_window_u8(port, &blend_globals, 0, LEVEL_BIAS + 1);
    uint32_t blue = blend_u8(port, source_levels, source & 0xff) +
                    blend_u8(port, target_levels, target & 0xff) +
                    port_window_u8(port, &blend_globals, 0, LEVEL_BIAS + 2);
    return ((red >> 1) << 16) | ((green >> 1) << 8) | (blue >> 1);
}

static uint32_t pixel16_levels_bias(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = levels_bias_values(&port, source_colour(&port),
                                port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_target_paired_invert(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = paired_remap(&port, target16(&port, format));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, ~colour, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_target_cross_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_remap(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_levels_bias_497da0(PORT_SIGNATURE)
{
    return pixel16_levels_bias(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_levels_bias_49fe60(PORT_SIGNATURE)
{
    return pixel16_levels_bias(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_paired_invert_499460(PORT_SIGNATURE)
{
    return pixel16_target_paired_invert(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_paired_invert_4a1520(PORT_SIGNATURE)
{
    return pixel16_target_paired_invert(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_cross_remap_494080(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_cross_remap_49c140(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap(calls, services, globals, entry, 1);
}

static uint32_t pixel16_remap_add(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, add_saturated(&port, target, colour), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap_subtract(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, target, colour), format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap_subtract_from(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, colour, target), format);
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_pixel16_remap_add_494450(PORT_SIGNATURE)
{
    return pixel16_remap_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_add_49c510(PORT_SIGNATURE)
{
    return pixel16_remap_add(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_remap_subtract_4945a0(PORT_SIGNATURE)
{
    return pixel16_remap_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_subtract_49c660(PORT_SIGNATURE)
{
    return pixel16_remap_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_remap_subtract_from_4946f0(PORT_SIGNATURE)
{
    return pixel16_remap_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_subtract_from_49c7b0(PORT_SIGNATURE)
{
    return pixel16_remap_subtract_from(calls, services, globals, entry, 1);
}

static uint32_t pixel16_invert_target_half_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, half_tint(&port, colour), format), entry->edx);
}

static uint32_t pixel16_quarters_plus_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ((target16(&port, format) >> 2) & 0x3f3f3f) + ((source_colour(&port) >> 2) & 0x3f3f3f);
    colour = remap(&port, colour + port_window_u32(&port, &blend_globals, 0, ADDED_COLOUR));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_invert_target_half_plus_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_plus(&port, ~target16(&port, format) & CHANNELS);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, remap(&port, colour), format), entry->edx);
}

static uint32_t pixel16_shade_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t entries;
    uint32_t level;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    entries = port_window_u32(&port, &blend_globals, 0, COLOUR_ENTRIES);
    level = blend_u8(&port, entries, entry_index(source_colour(&port)) * 4);
    level = blend_u16(&port, port_window_u32(&port, &blend_globals, 0, SHADE_LEVELS), level * 2);
    level += blend_u16(&port, port_window_u32(&port, &blend_globals, 0, SHADE_STEPS),
                       blend_u8(&port, entries, entry_index(target16(&port, format)) * 4) * 2);
    map = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, CHANNEL_MAPS),
                    (uint32_t)((int32_t)(int16_t)level * 4));
    port_window_set32(&port, &blend_globals, 0, MAP, map);
    colour = (blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_RED)) << 16) |
             (blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_GREEN)) << 8) |
             blend_u8(&port, map, port_window_u16(&port, &blend_globals, 0, TINT_BLUE));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_invert_target_half_tint_495df0(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_target_half_tint_49deb0(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_quarters_plus_remap_496750(PORT_SIGNATURE)
{
    return pixel16_quarters_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_quarters_plus_remap_49e810(PORT_SIGNATURE)
{
    return pixel16_quarters_plus_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_invert_target_half_plus_remap_496df0(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_invert_target_half_plus_remap_49eeb0(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_shade_tint_497c50(PORT_SIGNATURE)
{
    return pixel16_shade_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_shade_tint_49fd10(PORT_SIGNATURE)
{
    return pixel16_shade_tint(calls, services, globals, entry, 1);
}

static uint32_t pixel16_mean_map_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t entries;
    uint32_t value;
    uint32_t select;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    entries = port_window_u32(&port, &blend_globals, 0, COLOUR_ENTRIES);
    value = blend_u32(&port, entries, entry_index(source_colour(&port)) * 4);
    port_window_set32(&port, &blend_globals, 0, ENTRY, value);
    select = blend_u8(&port, entries, entry_index(target16(&port, format)) * 4);
    map = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, CHANNEL_MAPS),
                    (((value & 0xff) + select) >> 1) * 4);
    port_window_set32(&port, &blend_globals, 0, MAP, map);
    colour = (blend_u8(&port, map, value >> 24) << 16) |
             (blend_u8(&port, map, (value >> 16) & 0xff) << 8) |
             blend_u8(&port, map, (value >> 8) & 0xff);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_cross_remap_half_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_remap(&port, source_colour(&port), target16(&port, format));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), format), entry->edx);
}

static uint32_t pixel16_target_cross_remap_half_plus(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_remap(&port, target16(&port, format), source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), format), entry->edx);
}

uint32_t vertrix_port_pixel16_mean_map_remap_493810(PORT_SIGNATURE)
{
    return pixel16_mean_map_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_mean_map_remap_49b8d0(PORT_SIGNATURE)
{
    return pixel16_mean_map_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_cross_remap_half_plus_496080(PORT_SIGNATURE)
{
    return pixel16_cross_remap_half_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_cross_remap_half_plus_49e140(PORT_SIGNATURE)
{
    return pixel16_cross_remap_half_plus(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_cross_remap_half_plus_496480(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap_half_plus(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_cross_remap_half_plus_49e540(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap_half_plus(calls, services, globals, entry, 1);
}

enum
{
    MIX_ADD,
    MIX_SUBTRACT,
    MIX_SUBTRACT_FROM
};

/* Keep `colour` at 0x5bc018 and store the target mixed with it (`mix`), its low 24 bits kept at
 * 0x5bb774; the narrowed pixel. */
static uint32_t mix16(Port *port, uint32_t target, uint32_t colour, int mix, int format)
{
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    if (mix == MIX_ADD)
    {
        colour = add_saturated(port, target, colour);
    }
    else if (mix == MIX_SUBTRACT)
    {
        colour = subtract_saturated(port, target, colour);
    }
    else
    {
        colour = subtract_saturated(port, colour, target);
    }
    return put16_channels(port, colour, format);
}

static uint32_t half_plus_remap_mix(PORT_SIGNATURE, int mix, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = remap(&port, half_plus(&port, source_colour(&port)));
    pixel = mix16(&port, target, colour, mix, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t paired_mix(PORT_SIGNATURE, int mix, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = paired_remap(&port, source_colour(&port));
    pixel = mix16(&port, target, colour, mix, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_remap_subtract(PORT_SIGNATURE, int format)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_SUBTRACT, format);
}

static uint32_t pixel16_half_plus_remap_subtract_from(PORT_SIGNATURE, int format)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, format);
}

static uint32_t pixel16_paired_subtract(PORT_SIGNATURE, int format)
{
    return paired_mix(calls, services, globals, entry, MIX_SUBTRACT, format);
}

uint32_t vertrix_port_pixel16_half_plus_remap_subtract_496a10(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_remap_subtract_49ead0(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_remap_subtract_from_496b70(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_remap_subtract_from_49ec30(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract_from(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_subtract_499090(PORT_SIGNATURE)
{
    return pixel16_paired_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_subtract_4a1150(PORT_SIGNATURE)
{
    return pixel16_paired_subtract(calls, services, globals, entry, 1);
}

static uint32_t pixel16_paired_subtract_from(PORT_SIGNATURE, int format)
{
    return paired_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, format);
}

/* paired_remap with the map selected by the entry of `map_colour` and the dword picked through the
 * entry index of `fixed_colour`; the entry index is not stored. */
static uint32_t paired_cross(Port *port, uint32_t map_colour, uint32_t fixed_colour)
{
    uint32_t map = blend_u8(port, port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES),
                            entry_index(map_colour) * 4);
    uint32_t fixed;
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), map * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS),
                     entry_index(fixed_colour));
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    return (blend_u8(port, map, fixed >> 24) << 16) |
           (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           blend_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_paired_cross(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = paired_cross(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_target_paired_cross(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = paired_cross(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_paired_subtract_from_4991f0(PORT_SIGNATURE)
{
    return pixel16_paired_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_subtract_from_4a12b0(PORT_SIGNATURE)
{
    return pixel16_paired_subtract_from(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_cross_4995a0(PORT_SIGNATURE)
{
    return pixel16_paired_cross(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_cross_4a1660(PORT_SIGNATURE)
{
    return pixel16_paired_cross(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_paired_cross_499700(PORT_SIGNATURE)
{
    return pixel16_target_paired_cross(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_paired_cross_4a17c0(PORT_SIGNATURE)
{
    return pixel16_target_paired_cross(calls, services, globals, entry, 1);
}

/* half_tint with the map selected by the entry of `map_colour` (stored at 0x54d5d0) applied to the
 * entry of `entry_colour` (stored at 0x54d5d4). */
static uint32_t cross_half_tint(Port *port, uint32_t map_colour, uint32_t entry_colour)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t select = blend_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    uint32_t value;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_window_set32(port, &blend_globals, 0, MAP, map);
    value = blend_u32(port, entries, entry_index(entry_colour) * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    red = blend_u8(port, map,
                   ((value >> 24) + port_window_u16(port, &blend_globals, 0, TINT_RED)) >> 1);
    green = blend_u8(
        port, map,
        (((value >> 16) & 0xff) + port_window_u16(port, &blend_globals, 0, TINT_GREEN)) >> 1);
    blue = blend_u8(port, map,
                    (((value >> 8) & 0xff) + port_window_u16(port, &blend_globals, 0, TINT_BLUE)) >>
                        1);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t pixel16_cross_half_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_half_tint(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_target_cross_half_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = cross_half_tint(&port, target16(&port, format), source_colour(&port));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_half_plus_remap_add(PORT_SIGNATURE, int format)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_ADD, format);
}

uint32_t vertrix_port_pixel16_cross_half_tint_4961e0(PORT_SIGNATURE)
{
    return pixel16_cross_half_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_cross_half_tint_49e2a0(PORT_SIGNATURE)
{
    return pixel16_cross_half_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_cross_half_tint_4965e0(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_cross_half_tint_49e6a0(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_plus_remap_add_4968a0(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_plus_remap_add_49e960(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_add(calls, services, globals, entry, 1);
}

/* The map numbered by the mean (rounded down) of the source's and the target's entry bytes (the
 * source's entry stored at 0x54d5d4 first, the map at 0x54d5d0) applied to the dword picked as
 * paired_remap picks it from the source's entry index (the dword stored at 0x54d5d4, the index at
 * 0x54d5e4). */
static uint32_t mean_map_paired(Port *port, uint32_t source, uint32_t target)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t index = entry_index(source);
    uint32_t value = blend_u32(port, entries, index * 4);
    uint32_t select;
    uint32_t map;
    uint32_t fixed;
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    select = blend_u8(port, entries, entry_index(target) * 4);
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS),
                    ((select + (value & 0xff)) >> 1) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS), index);
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    port_window_set32(port, &blend_globals, 0, ENTRY_INDEX, index);
    return (blend_u8(port, map, fixed >> 24) << 16) |
           (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           blend_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_mean_map_paired(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = mean_map_paired(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_average_paired(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = average(target16(&port, format), source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, paired_remap(&port, colour), format), entry->edx);
}

static uint32_t pixel16_paired_average(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = paired_remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), format), entry->edx);
}

static uint32_t pixel16_paired_add(PORT_SIGNATURE, int format)
{
    return paired_mix(calls, services, globals, entry, MIX_ADD, format);
}

uint32_t vertrix_port_pixel16_mean_map_paired_498910(PORT_SIGNATURE)
{
    return pixel16_mean_map_paired(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_mean_map_paired_4a09d0(PORT_SIGNATURE)
{
    return pixel16_mean_map_paired(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_average_paired_498a80(PORT_SIGNATURE)
{
    return pixel16_average_paired(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_average_paired_4a0b40(PORT_SIGNATURE)
{
    return pixel16_average_paired(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_average_498db0(PORT_SIGNATURE)
{
    return pixel16_paired_average(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_average_4a0e70(PORT_SIGNATURE)
{
    return pixel16_paired_average(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_add_498f20(PORT_SIGNATURE)
{
    return pixel16_paired_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_add_4a0fe0(PORT_SIGNATURE)
{
    return pixel16_paired_add(calls, services, globals, entry, 1);
}

static uint32_t pixel16_shade(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t entries;
    uint32_t value;
    uint32_t level;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    entries = port_window_u32(&port, &blend_globals, 0, COLOUR_ENTRIES);
    value = blend_u32(&port, entries, entry_index(source_colour(&port)) * 4);
    port_window_set32(&port, &blend_globals, 0, ENTRY, value);
    level = blend_u8(&port, entries, entry_index(target16(&port, format)) * 4);
    level = blend_u16(&port, port_window_u32(&port, &blend_globals, 0, SHADE_LEVELS),
                      (value & 0xff) * 2) +
            blend_u16(&port, port_window_u32(&port, &blend_globals, 0, SHADE_STEPS), level * 2);
    map = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, CHANNEL_MAPS),
                    (uint32_t)((int32_t)(int16_t)level * 4));
    port_window_set32(&port, &blend_globals, 0, MAP, map);
    colour = (blend_u8(&port, map, value >> 24) << 16) |
             (blend_u8(&port, map, (value >> 16) & 0xff) << 8) |
             blend_u8(&port, map, (value >> 8) & 0xff);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t half_tint_mix(PORT_SIGNATURE, int mix, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    colour = half_tint(&port, source_colour(&port));
    pixel = mix16(&port, target, colour, mix, format);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_tint_add(PORT_SIGNATURE, int format)
{
    return half_tint_mix(calls, services, globals, entry, MIX_ADD, format);
}

uint32_t vertrix_port_pixel16_shade_497340(PORT_SIGNATURE)
{
    return pixel16_shade(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_shade_49f400(PORT_SIGNATURE)
{
    return pixel16_shade(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_tint_add_495130(PORT_SIGNATURE)
{
    return pixel16_half_tint_add(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_tint_add_49d1f0(PORT_SIGNATURE)
{
    return pixel16_half_tint_add(calls, services, globals, entry, 1);
}

static uint32_t pixel16_half_tint_subtract(PORT_SIGNATURE, int format)
{
    return half_tint_mix(calls, services, globals, entry, MIX_SUBTRACT, format);
}

static uint32_t pixel16_half_tint_subtract_from(PORT_SIGNATURE, int format)
{
    return half_tint_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, format);
}

uint32_t vertrix_port_pixel16_half_tint_subtract_4954c0(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_tint_subtract_49d580(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_tint_subtract_from_495850(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract_from(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_tint_subtract_from_49d910(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract_from(calls, services, globals, entry, 1);
}

static uint32_t pixel16_tint_levels(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = remap_tint(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour =
        levels_mix_values(&port, colour, port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

/* The map numbered as blend_shade numbers it (the source's entry stored at 0x54d5d4 first, the
 * map at 0x54d5d0) applied to the dword picked as paired_remap picks it from the source's entry
 * index (the dword stored at 0x54d5d4, the index at 0x54d5e4). */
static uint32_t shade_paired(Port *port, uint32_t source, uint32_t target)
{
    uint32_t entries;
    uint32_t index;
    uint32_t value;
    uint32_t level;
    uint32_t map;
    uint32_t fixed;
    uint32_t colour;
    entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    index = entry_index(source);
    value = blend_u32(port, entries, index * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    level = blend_u8(port, entries, entry_index(target) * 4);
    level = blend_u16(port, port_window_u32(port, &blend_globals, 0, SHADE_LEVELS),
                      (value & 0xff) * 2) +
            blend_u16(port, port_window_u32(port, &blend_globals, 0, SHADE_STEPS), level * 2);
    map = blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS),
                    (uint32_t)((int32_t)(int16_t)level * 4));
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS), index);
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    colour = (blend_u8(port, map, fixed >> 24) << 16) |
             (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
             blend_u8(port, map, (fixed >> 8) & 0xff);
    port_window_set32(port, &blend_globals, 0, ENTRY_INDEX, index);
    return colour;
}

static uint32_t pixel16_shade_paired(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = shade_paired(&port, source_colour(&port), target16(&port, format));
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

uint32_t vertrix_port_pixel16_tint_levels_4980f0(PORT_SIGNATURE)
{
    return pixel16_tint_levels(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_tint_levels_4a01b0(PORT_SIGNATURE)
{
    return pixel16_tint_levels(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_shade_paired_499860(PORT_SIGNATURE)
{
    return pixel16_shade_paired(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_shade_paired_4a1920(PORT_SIGNATURE)
{
    return pixel16_shade_paired(calls, services, globals, entry, 1);
}

enum
{
    TARGET_ENTRY = 0x54d5d8
};

/* The source's colour entry and the widened target's (the entry stored at 0x54d5d4, the target's
 * at 0x54d5d8) and the map of the source's (stored at 0x54d5d0) for the entry means; `target` is
 * the target's colour. */
static uint32_t entry_pair(Port *port, uint32_t target, uint32_t *other)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t value = blend_u32(port, entries, entry_index(source_colour(port)) * 4);
    uint32_t map;
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    *other = blend_u32(port, entries, entry_index(target) * 4);
    port_window_set32(port, &blend_globals, 0, TARGET_ENTRY, *other);
    return map;
}

static uint32_t pixel16_entry_mean(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t value;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    map = entry_pair(&port, target16(&port, format), &other);
    value = port_window_u32(&port, &blend_globals, 0, ENTRY);
    colour = blend_u8(&port, map, ((value >> 24) + (other >> 24)) >> 1) << 16;
    colour |= blend_u8(&port, map, (((value >> 16) & 0xff) + ((other >> 16) & 0xff)) >> 1) << 8;
    colour |= blend_u8(&port, map, (((value >> 8) & 0xff) + ((other >> 8) & 0xff)) >> 1);
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

/* `colour` remapped half way to the fixed channels; the map used is applied again to the dword
 * picked as paired_remap picks it from that colour's entry index (stored at 0x54d5d4). */
static uint32_t half_tint_fixed(Port *port, uint32_t colour)
{
    uint32_t map;
    uint32_t fixed;
    colour = half_tint(port, colour);
    map = port_window_u32(port, &blend_globals, 0, MAP);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS),
                     entry_index(colour));
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    return (blend_u8(port, map, fixed >> 24) << 16) |
           (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           blend_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_half_tint_fixed(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = half_tint_fixed(&port, source_colour(&port));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_entry_mean_493a00(PORT_SIGNATURE)
{
    return pixel16_entry_mean(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_entry_mean_49bac0(PORT_SIGNATURE)
{
    return pixel16_entry_mean(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_half_tint_fixed_498770(PORT_SIGNATURE)
{
    return pixel16_half_tint_fixed(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_half_tint_fixed_4a0830(PORT_SIGNATURE)
{
    return pixel16_half_tint_fixed(calls, services, globals, entry, 1);
}

/* The map applied to the means of the entries' bytes 3, 2 and 1 each meaned again with the fixed
 * channel. */
static uint32_t entry_mean_tint(Port *port, uint32_t map, uint32_t value, uint32_t other)
{
    uint32_t red = ((value >> 24) + (other >> 24)) >> 1;
    uint32_t green = (((value >> 16) & 0xff) + ((other >> 16) & 0xff)) >> 1;
    uint32_t blue = (((value >> 8) & 0xff) + ((other >> 8) & 0xff)) >> 1;
    uint32_t colour =
        blend_u8(port, map, (red + port_window_u16(port, &blend_globals, 0, TINT_RED)) >> 1) << 16;
    colour |=
        blend_u8(port, map, (green + port_window_u16(port, &blend_globals, 0, TINT_GREEN)) >> 1)
        << 8;
    return colour |
           blend_u8(port, map, (blue + port_window_u16(port, &blend_globals, 0, TINT_BLUE)) >> 1);
}

static uint32_t pixel16_entry_mean_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    map = entry_pair(&port, target16(&port, format), &other);
    colour = entry_mean_tint(&port, map, port_window_u32(&port, &blend_globals, 0, ENTRY), other);
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

static uint32_t pixel16_levels_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = levels_mix_values(&port, source_colour(&port),
                               port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    colour = remap(&port, colour);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_entry_mean_tint_494c60(PORT_SIGNATURE)
{
    return pixel16_entry_mean_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_entry_mean_tint_49cd20(PORT_SIGNATURE)
{
    return pixel16_entry_mean_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_levels_remap_4978d0(PORT_SIGNATURE)
{
    return pixel16_levels_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_levels_remap_49f990(PORT_SIGNATURE)
{
    return pixel16_levels_remap(calls, services, globals, entry, 1);
}

static uint32_t pixel16_remap_levels(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour =
        levels_mix_values(&port, colour, port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

/* The map of the source's colour entry (the entry stored at 0x54d5d4 first, the map at 0x54d5d0)
 * applied to the means of the bytes 3, 2 and 1 of the dword picked as paired_remap picks it
 * (stored at 0x54d5d4; the index at 0x54d5e4) and of the target's entry (stored at 0x54d5d8). */
static uint32_t fixed_entry_mean(Port *port, uint32_t source, uint32_t target)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t index = entry_index(source);
    uint32_t value = blend_u32(port, entries, index * 4);
    uint32_t map;
    uint32_t fixed;
    uint32_t other;
    uint32_t colour;
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS), index);
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    other = blend_u32(port, entries, entry_index(target) * 4);
    port_window_set32(port, &blend_globals, 0, TARGET_ENTRY, other);
    colour = blend_u8(port, map, ((fixed >> 24) + (other >> 24)) >> 1) << 16;
    colour |= blend_u8(port, map, (((fixed >> 16) & 0xff) + ((other >> 16) & 0xff)) >> 1) << 8;
    colour |= blend_u8(port, map, (((fixed >> 8) & 0xff) + ((other >> 8) & 0xff)) >> 1);
    port_window_set32(port, &blend_globals, 0, ENTRY_INDEX, index);
    return colour;
}

static uint32_t pixel16_fixed_entry_mean(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = fixed_entry_mean(&port, source_colour(&port), target16(&port, format));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_remap_levels_497a90(PORT_SIGNATURE)
{
    return pixel16_remap_levels(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_remap_levels_49fb50(PORT_SIGNATURE)
{
    return pixel16_remap_levels(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_fixed_entry_mean_498bf0(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_mean(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_fixed_entry_mean_4a0cb0(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_mean(calls, services, globals, entry, 1);
}

/* cross_remap without storing the map's address. */
static uint32_t cross_remap_unstored(Port *port, uint32_t map_colour, uint32_t entry_colour)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t select = blend_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), select * 4);
    uint32_t value = blend_u32(port, entries, entry_index(entry_colour) * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    return (blend_u8(port, map, value >> 24) << 16) |
           (blend_u8(port, map, (value >> 16) & 0xff) << 8) |
           blend_u8(port, map, (value >> 8) & 0xff);
}

static uint32_t cross_half_plus_remap(PORT_SIGNATURE, int target_map, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    if (target_map)
    {
        colour = cross_remap_unstored(&port, target, source_colour(&port));
    }
    else
    {
        colour = cross_remap_unstored(&port, source_colour(&port), target);
    }
    colour = half_plus(&port, colour);
    keep16(&port, remap(&port, colour), format);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

static uint32_t pixel16_cross_half_plus_remap(PORT_SIGNATURE, int format)
{
    return cross_half_plus_remap(calls, services, globals, entry, 0, format);
}

static uint32_t pixel16_target_cross_half_plus_remap(PORT_SIGNATURE, int format)
{
    return cross_half_plus_remap(calls, services, globals, entry, 1, format);
}

static uint32_t pixel16_entry_levels(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t value;
    uint32_t map;
    uint32_t other;
    uint32_t source_levels;
    uint32_t target_levels;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    map = entry_pair(&port, target16(&port, format), &other);
    value = port_window_u32(&port, &blend_globals, 0, ENTRY);
    source_levels = port_window_u32(&port, &blend_globals, 0, SOURCE_LEVELS);
    target_levels = port_window_u32(&port, &blend_globals, 0, TARGET_LEVELS);
    colour = blend_u8(&port, map,
                      blend_u8(&port, source_levels, value >> 24) +
                          blend_u8(&port, target_levels, other >> 24))
             << 16;
    colour |= blend_u8(&port, map,
                       blend_u8(&port, source_levels, (value >> 16) & 0xff) +
                           blend_u8(&port, target_levels, (other >> 16) & 0xff))
              << 8;
    colour |= blend_u8(&port, map,
                       blend_u8(&port, source_levels, (value >> 8) & 0xff) +
                           blend_u8(&port, target_levels, (other >> 8) & 0xff));
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

uint32_t vertrix_port_pixel16_cross_half_plus_remap_496f40(PORT_SIGNATURE)
{
    return pixel16_cross_half_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_cross_half_plus_remap_49f000(PORT_SIGNATURE)
{
    return pixel16_cross_half_plus_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_target_cross_half_plus_remap_497140(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_plus_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_target_cross_half_plus_remap_49f200(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_plus_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_entry_levels_4975d0(PORT_SIGNATURE)
{
    return pixel16_entry_levels(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_entry_levels_49f690(PORT_SIGNATURE)
{
    return pixel16_entry_levels(calls, services, globals, entry, 1);
}

static uint32_t pixel16_levels_paired(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = levels_mix_values(&port, source_colour(&port),
                               port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    colour = paired_remap(&port, colour);
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

static uint32_t pixel16_paired_levels(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = paired_remap(&port, source_colour(&port));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour =
        levels_mix_values(&port, colour, port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, format), entry->edx);
}

uint32_t vertrix_port_pixel16_levels_paired_4999f0(PORT_SIGNATURE)
{
    return pixel16_levels_paired(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_levels_paired_4a1ab0(PORT_SIGNATURE)
{
    return pixel16_levels_paired(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_paired_levels_499dd0(PORT_SIGNATURE)
{
    return pixel16_paired_levels(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_paired_levels_4a1e90(PORT_SIGNATURE)
{
    return pixel16_paired_levels(calls, services, globals, entry, 1);
}

static uint32_t pixel16_levels_bias_remap(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    target = target16(&port, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, target);
    colour = levels_bias_values(&port, source_colour(&port),
                                port_window_u32(&port, &blend_globals, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, remap(&port, colour), format), entry->edx);
}

/* The map applied to the level sums of the entries' bytes 3, 2 and 1 (the source's through
 * [0x55f1f0], the target's through [0x55f1f4]) each meaned with the fixed channel. */
static uint32_t entry_levels_tint(Port *port, uint32_t map, uint32_t value, uint32_t other)
{
    uint32_t source_levels = port_window_u32(port, &blend_globals, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_window_u32(port, &blend_globals, 0, TARGET_LEVELS);
    uint32_t red =
        blend_u8(port, source_levels, value >> 24) + blend_u8(port, target_levels, other >> 24);
    uint32_t green = blend_u8(port, source_levels, (value >> 16) & 0xff) +
                     blend_u8(port, target_levels, (other >> 16) & 0xff);
    uint32_t blue = blend_u8(port, source_levels, (value >> 8) & 0xff) +
                    blend_u8(port, target_levels, (other >> 8) & 0xff);
    uint32_t colour =
        blend_u8(port, map, (red + port_window_u16(port, &blend_globals, 0, TINT_RED)) >> 1) << 16;
    colour |=
        blend_u8(port, map, (green + port_window_u16(port, &blend_globals, 0, TINT_GREEN)) >> 1)
        << 8;
    return colour |
           blend_u8(port, map, (blue + port_window_u16(port, &blend_globals, 0, TINT_BLUE)) >> 1);
}

static uint32_t pixel16_entry_levels_tint(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    map = entry_pair(&port, target16(&port, format), &other);
    colour = entry_levels_tint(&port, map, port_window_u32(&port, &blend_globals, 0, ENTRY), other);
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

/* As 0x4975d0 with the source's entry replaced by the dword picked as paired_remap picks it
 * (the index stored at 0x54d5e4, the dword at 0x54d5d4); the map stays that of the source's own
 * entry. */
static uint32_t fixed_entry_levels(Port *port, uint32_t source, uint32_t target)
{
    uint32_t entries;
    uint32_t index;
    uint32_t value;
    uint32_t map;
    uint32_t fixed;
    uint32_t other;
    uint32_t source_levels;
    uint32_t target_levels;
    uint32_t colour;
    entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    index = entry_index(source);
    port_window_set32(port, &blend_globals, 0, ENTRY_INDEX, index);
    value = blend_u32(port, entries, index * 4);
    port_window_set32(port, &blend_globals, 0, ENTRY, value);
    map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS), index);
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    other = blend_u32(port, entries, entry_index(target) * 4);
    port_window_set32(port, &blend_globals, 0, TARGET_ENTRY, other);
    source_levels = port_window_u32(port, &blend_globals, 0, SOURCE_LEVELS);
    target_levels = port_window_u32(port, &blend_globals, 0, TARGET_LEVELS);
    colour = blend_u8(port, map,
                      blend_u8(port, source_levels, fixed >> 24) +
                          blend_u8(port, target_levels, other >> 24))
             << 16;
    colour |= blend_u8(port, map,
                       blend_u8(port, source_levels, (fixed >> 16) & 0xff) +
                           blend_u8(port, target_levels, (other >> 16) & 0xff))
              << 8;
    colour |= blend_u8(port, map,
                       blend_u8(port, source_levels, (fixed >> 8) & 0xff) +
                           blend_u8(port, target_levels, (other >> 8) & 0xff));
    return colour;
}

static uint32_t pixel16_fixed_entry_levels(PORT_SIGNATURE, int format)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = fixed_entry_levels(&port, source_colour(&port), target16(&port, format));
    put16(&port, colour, format);
    port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    return port_return(&port, target_pointer(&port, format), entry->edx);
}

uint32_t vertrix_port_pixel16_levels_bias_remap_498280(PORT_SIGNATURE)
{
    return pixel16_levels_bias_remap(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_levels_bias_remap_4a0340(PORT_SIGNATURE)
{
    return pixel16_levels_bias_remap(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_entry_levels_tint_497ee0(PORT_SIGNATURE)
{
    return pixel16_entry_levels_tint(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_entry_levels_tint_49ffa0(PORT_SIGNATURE)
{
    return pixel16_entry_levels_tint(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_pixel16_fixed_entry_levels_499bc0(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_levels(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_pixel16_fixed_entry_levels_4a1c80(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_levels(calls, services, globals, entry, 1);
}

/* The 32-bit target pixel at [0x5bb768], and a store to it returning its address. */
static uint32_t target32(Port *port)
{
    return blend_u32(port, port_window_u32(port, &blend_globals, 0, TARGET_PIXEL), 0);
}

static uint32_t put32(Port *port, uint32_t colour)
{
    uint32_t target = port_window_u32(port, &blend_globals, 0, TARGET_PIXEL);
    blend_set32(port, target, 0, colour);
    return target;
}

static uint32_t blend_subtract_from_body(Port *port)
{
    uint32_t colour;
    colour = subtract_saturated(port, source_colour(port), target32(port));
    return put32(port, colour & CHANNELS);
}

uint32_t vertrix_port_blend_subtract_from(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_subtract_from_body(&port), entry->edx);
}

static uint32_t blend_invert_body(Port *port)
{
    uint32_t colour;
    colour = ~source_colour(port) & CHANNELS;
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_invert_body(&port), entry->edx);
}

static uint32_t blend_invert_target_body(Port *port)
{
    return put32(port, ~target32(port) & CHANNELS);
}

uint32_t vertrix_port_blend_invert_target(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_invert_target_body(&port), entry->edx);
}

static uint32_t blend_half_plus_body(Port *port)
{
    uint32_t colour;
    colour = half_plus(port, source_colour(port));
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_half_plus(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_half_plus_body(&port), entry->edx);
}

static uint32_t blend_half_plus_remap_body(Port *port)
{
    uint32_t colour;
    colour = half_plus(port, source_colour(port));
    put32(port, colour);
    colour = remap(port, target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_half_plus_remap_body(&port), entry->edx);
}

static uint32_t blend_target_cross_remap_body(Port *port)
{
    uint32_t colour;
    colour = cross_remap(port, target32(port), source_colour(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_target_cross_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_target_cross_remap_body(&port), entry->edx);
}

static uint32_t blend_remap_average_body(Port *port)
{
    uint32_t colour;
    colour = remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = average(target32(port), colour);
    return put32(port, colour);
}

uint32_t vertrix_port_blend_remap_average(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_average_body(&port), entry->edx);
}

static uint32_t blend_remap_subtract_from_body(Port *port)
{
    uint32_t colour;
    colour = remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = subtract_saturated(port, colour, target32(port));
    return put32(port, colour & CHANNELS);
}

uint32_t vertrix_port_blend_remap_subtract_from(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_subtract_from_body(&port), entry->edx);
}

static uint32_t blend_remap_invert_body(Port *port)
{
    uint32_t colour;
    colour = remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    put32(port, ~colour & CHANNELS);
    return ~colour & CHANNELS;
}

uint32_t vertrix_port_blend_remap_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_remap_invert_body(&port), entry->edx);
}

static uint32_t blend_target_remap_invert_body(Port *port)
{
    uint32_t colour;
    colour = remap(port, target32(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    return put32(port, ~colour & CHANNELS);
}

uint32_t vertrix_port_blend_target_remap_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_target_remap_invert_body(&port), entry->edx);
}

/* The fixed channels through the map numbered by the mean of two colours' entry bytes (the map
 * stored at 0x54d5d0). */
static uint32_t mean_map_tint(Port *port, uint32_t first, uint32_t second)
{
    uint32_t entries = port_window_u32(port, &blend_globals, 0, COLOUR_ENTRIES);
    uint32_t select = blend_u8(port, entries, entry_index(first) * 4) +
                      blend_u8(port, entries, entry_index(second) * 4);
    uint32_t map =
        blend_u32(port, port_window_u32(port, &blend_globals, 0, CHANNEL_MAPS), (select >> 1) * 4);
    port_window_set32(port, &blend_globals, 0, MAP, map);
    return (blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_RED)) << 16) |
           (blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_GREEN)) << 8) |
           blend_u8(port, map, port_window_u16(port, &blend_globals, 0, TINT_BLUE));
}

static uint32_t blend_mean_map_tint_body(Port *port)
{
    uint32_t colour;
    colour = mean_map_tint(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_mean_map_tint(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_mean_map_tint_body(&port), entry->edx);
}

static uint32_t blend_quarters_plus_body(Port *port)
{
    uint32_t colour;
    colour = ((source_colour(port) >> 2) & 0x3f3f3f) + ((target32(port) >> 2) & 0x3f3f3f);
    colour += port_window_u32(port, &blend_globals, 0, ADDED_COLOUR);
    return put32(port, colour);
}

uint32_t vertrix_port_blend_quarters_plus(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_quarters_plus_body(&port), entry->edx);
}

static uint32_t blend_entry_mean_tint_body(Port *port)
{
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    map = entry_pair(port, target32(port), &other);
    colour = entry_mean_tint(port, map, port_window_u32(port, &blend_globals, 0, ENTRY), other);
    return put32(port, colour);
}

uint32_t vertrix_port_blend_entry_mean_tint(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_entry_mean_tint_body(&port), entry->edx);
}

enum
{
    COLOUR_HALF_PLUS,
    COLOUR_TINT,
    COLOUR_HALF_TINT,
    COLOUR_REMAP,
    COLOUR_HALF_PLUS_REMAP,
    COLOUR_PAIRED
};

/* `colour` halved plus 0x54d5ec, remapped through fixed channels, remapped half way to them,
 * remapped, halved plus 0x54d5ec and remapped, or remapped as paired_remap does, as `kind` names.
 */
static uint32_t made_from(Port *port, uint32_t colour, int kind)
{
    if (kind == COLOUR_HALF_PLUS)
    {
        return half_plus(port, colour);
    }
    if (kind == COLOUR_TINT)
    {
        return remap_tint(port, colour);
    }
    if (kind == COLOUR_HALF_TINT)
    {
        return half_tint(port, colour);
    }
    if (kind == COLOUR_HALF_PLUS_REMAP)
    {
        return remap(port, half_plus(port, colour));
    }
    if (kind == COLOUR_PAIRED)
    {
        return paired_remap(port, colour);
    }
    return remap(port, colour);
}

/* The 32-bit target mixed (`mix`) with the source made as `kind` names (kept at 0x5bc018), the low
 * 24 bits stored; the target's address. */
static uint32_t made_mix32(PORT_SIGNATURE, int kind, int mix)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = made_from(&port, source_colour(&port), kind);
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    target = target32(&port);
    if (mix == MIX_ADD)
    {
        colour = add_saturated(&port, target, colour);
    }
    else if (mix == MIX_SUBTRACT)
    {
        colour = subtract_saturated(&port, target, colour);
    }
    else
    {
        colour = subtract_saturated(&port, colour, target);
    }
    return port_return(&port, put32(&port, colour & CHANNELS), entry->edx);
}

uint32_t vertrix_port_blend_half_plus_add(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS, MIX_ADD);
}

uint32_t vertrix_port_blend_tint_subtract(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_TINT, MIX_SUBTRACT);
}

uint32_t vertrix_port_blend_half_plus_subtract(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS, MIX_SUBTRACT);
}

uint32_t vertrix_port_blend_tint_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_TINT, MIX_SUBTRACT_FROM);
}

uint32_t vertrix_port_blend_half_plus_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS, MIX_SUBTRACT_FROM);
}

uint32_t vertrix_port_blend_half_tint_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_TINT, MIX_SUBTRACT_FROM);
}

/* The 32-bit target becomes the inverted source or target (low 24 bits, kept at 0x5bc018) made as
 * `kind` names; returns that colour or, with `address`, the target's address. */
static uint32_t inverted_made32(PORT_SIGNATURE, int of_target, int kind, int address)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    colour = ~(of_target ? target32(&port) : source_colour(&port)) & CHANNELS;
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    colour = made_from(&port, colour, kind);
    target = put32(&port, colour);
    return port_return(&port, address ? target : colour, entry->edx);
}

uint32_t vertrix_port_blend_invert_tint(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 0, COLOUR_TINT, 1);
}

uint32_t vertrix_port_blend_invert_half_plus(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 0, COLOUR_HALF_PLUS, 0);
}

uint32_t vertrix_port_blend_invert_half_tint(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 0, COLOUR_HALF_TINT, 0);
}

uint32_t vertrix_port_blend_invert_target_tint(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 1, COLOUR_TINT, 0);
}

uint32_t vertrix_port_blend_invert_target_half_plus(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 1, COLOUR_HALF_PLUS, 1);
}

uint32_t vertrix_port_blend_invert_target_half_tint(PORT_SIGNATURE)
{
    return inverted_made32(calls, services, globals, entry, 1, COLOUR_HALF_TINT, 0);
}

enum
{
    CROSS_TINT,
    CROSS_REMAP_HALF_PLUS,
    CROSS_HALF_TINT
};

/* The 32-bit target becomes the colour that the cross remap named by `kind` makes, with the map
 * from the target (`target_map`) or the source and the entry from the other; the target's address.
 */
static uint32_t cross32(PORT_SIGNATURE, int kind, int target_map)
{
    Port port;
    uint32_t map_colour;
    uint32_t entry_colour;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    map_colour = target_map ? target32(&port) : source_colour(&port);
    entry_colour = target_map ? source_colour(&port) : target32(&port);
    if (kind == CROSS_TINT)
    {
        colour = cross_tint(&port, map_colour, entry_colour);
    }
    else if (kind == CROSS_HALF_TINT)
    {
        colour = cross_half_tint(&port, map_colour, entry_colour);
    }
    else
    {
        colour = cross_remap(&port, map_colour, entry_colour);
        port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
        colour = half_plus(&port, colour);
    }
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_source_tint(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_TINT, 0);
}

uint32_t vertrix_port_blend_cross_remap_half_plus(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_REMAP_HALF_PLUS, 0);
}

uint32_t vertrix_port_blend_cross_half_tint(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_HALF_TINT, 0);
}

uint32_t vertrix_port_blend_target_tint(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_TINT, 1);
}

uint32_t vertrix_port_blend_target_cross_remap_half_plus(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_REMAP_HALF_PLUS, 1);
}

uint32_t vertrix_port_blend_target_cross_half_tint(PORT_SIGNATURE)
{
    return cross32(calls, services, globals, entry, CROSS_HALF_TINT, 1);
}

static uint32_t blend_quarters_plus_remap_body(Port *port)
{
    uint32_t colour;
    colour = ((source_colour(port) >> 2) & 0x3f3f3f) + ((target32(port) >> 2) & 0x3f3f3f);
    put32(port, colour + port_window_u32(port, &blend_globals, 0, ADDED_COLOUR));
    colour = remap(port, target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_quarters_plus_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_quarters_plus_remap_body(&port), entry->edx);
}

uint32_t vertrix_port_blend_half_plus_remap_add(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS_REMAP, MIX_ADD);
}

uint32_t vertrix_port_blend_half_plus_remap_subtract(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS_REMAP, MIX_SUBTRACT);
}

uint32_t vertrix_port_blend_half_plus_remap_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_HALF_PLUS_REMAP, MIX_SUBTRACT_FROM);
}

static uint32_t blend_invert_half_plus_remap_body(Port *port)
{
    uint32_t colour;
    colour = half_plus(port, ~source_colour(port) & CHANNELS);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = remap(port, colour);
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_invert_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_invert_half_plus_remap_body(&port), entry->edx);
}

static uint32_t blend_invert_target_half_plus_remap_body(Port *port)
{
    uint32_t colour;
    colour = half_plus(port, ~target32(port) & CHANNELS);
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = remap(port, colour);
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_invert_target_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_invert_target_half_plus_remap_body(&port), entry->edx);
}

static uint32_t cross_half_plus_remap32(PORT_SIGNATURE, int target_map)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    if (target_map)
    {
        colour = cross_remap_unstored(&port, target32(&port), source_colour(&port));
    }
    else
    {
        colour = cross_remap_unstored(&port, source_colour(&port), target32(&port));
    }
    colour = half_plus(&port, colour);
    put32(&port, remap(&port, colour));
    port_window_set32(&port, &blend_globals, 0, REMAPPED, colour);
    return port_return(&port, port_window_u32(&port, &blend_globals, 0, TARGET_PIXEL), entry->edx);
}

uint32_t vertrix_port_blend_cross_half_plus_remap(PORT_SIGNATURE)
{
    return cross_half_plus_remap32(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_blend_target_cross_half_plus_remap(PORT_SIGNATURE)
{
    return cross_half_plus_remap32(calls, services, globals, entry, 1);
}

static uint32_t blend_levels_bias_body(Port *port)
{
    uint32_t colour;
    colour = levels_bias_values(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_levels_bias(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_levels_bias_body(&port), entry->edx);
}

static uint32_t blend_entry_levels_tint_body(Port *port)
{
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    map = entry_pair(port, target32(port), &other);
    colour = entry_levels_tint(port, map, port_window_u32(port, &blend_globals, 0, ENTRY), other);
    return put32(port, colour);
}

uint32_t vertrix_port_blend_entry_levels_tint(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_entry_levels_tint_body(&port), entry->edx);
}

static uint32_t blend_paired_body(Port *port)
{
    uint32_t colour;
    colour = paired_remap(port, source_colour(port));
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_paired_body(&port), entry->edx);
}

static uint32_t blend_fixed_entry_body(Port *port)
{
    uint32_t colour;
    colour = fixed_entry_remap(port, source_colour(port));
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_fixed_entry(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_fixed_entry_body(&port), entry->edx);
}

static uint32_t blend_half_plus_paired_body(Port *port)
{
    uint32_t colour;
    colour = half_plus(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    return put32(port, paired_remap(port, colour));
}

uint32_t vertrix_port_blend_half_plus_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_half_plus_paired_body(&port), entry->edx);
}

static uint32_t blend_half_tint_fixed_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    uint32_t map;
    uint32_t fixed;
    colour = half_tint(port, source_colour(port));
    map = port_window_u32(port, &blend_globals, 0, MAP);
    target = put32(port, colour);
    /* The entry index is taken from the stored pixel but for its red bits. */
    colour = (colour & 0xfc0000) | (blend_u32(port, target, 0) & 0xfcfc);
    fixed = blend_u8(port, port_window_u32(port, &blend_globals, 0, FIXED_SELECTS),
                     entry_index(colour));
    fixed = blend_u32(
        port, blend_u32(port, port_window_u32(port, &blend_globals, 0, FIXED_ENTRIES), fixed * 4),
        0);
    port_window_set32(port, &blend_globals, 0, ENTRY, fixed);
    colour = (blend_u8(port, map, fixed >> 24) << 16) |
             (blend_u8(port, map, (fixed >> 16) & 0xff) << 8) |
             blend_u8(port, map, (fixed >> 8) & 0xff);
    blend_set32(port, target, 0, colour);
    return colour;
}

uint32_t vertrix_port_blend_half_tint_fixed(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_half_tint_fixed_body(&port), entry->edx);
}

static uint32_t blend_mean_map_paired_body(Port *port)
{
    uint32_t colour;
    colour = mean_map_paired(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_mean_map_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_mean_map_paired_body(&port), entry->edx);
}

static uint32_t blend_average_paired_body(Port *port)
{
    uint32_t colour;
    colour = average(source_colour(port), target32(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = paired_remap(port, colour);
    put32(port, colour);
    return colour;
}

uint32_t vertrix_port_blend_average_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_average_paired_body(&port), entry->edx);
}

static uint32_t blend_fixed_entry_mean_body(Port *port)
{
    uint32_t colour;
    colour = fixed_entry_mean(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_fixed_entry_mean(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_fixed_entry_mean_body(&port), entry->edx);
}

static uint32_t blend_paired_average_body(Port *port)
{
    uint32_t colour;
    colour = paired_remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    return put32(port, average(target32(port), colour));
}

uint32_t vertrix_port_blend_paired_average(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_paired_average_body(&port), entry->edx);
}

uint32_t vertrix_port_blend_paired_subtract(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_PAIRED, MIX_SUBTRACT);
}

uint32_t vertrix_port_blend_paired_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_PAIRED, MIX_SUBTRACT_FROM);
}

static uint32_t blend_paired_invert_body(Port *port)
{
    uint32_t colour;
    colour = paired_remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    put32(port, ~colour & CHANNELS);
    return ~colour & CHANNELS;
}

uint32_t vertrix_port_blend_paired_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_paired_invert_body(&port), entry->edx);
}

static uint32_t blend_target_paired_invert_body(Port *port)
{
    uint32_t colour;
    colour = paired_remap(port, target32(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    return put32(port, ~colour & CHANNELS);
}

uint32_t vertrix_port_blend_target_paired_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_target_paired_invert_body(&port), entry->edx);
}

static uint32_t blend_paired_cross_body(Port *port)
{
    uint32_t colour;
    colour = paired_cross(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_paired_cross(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_paired_cross_body(&port), entry->edx);
}

static uint32_t blend_target_paired_cross_body(Port *port)
{
    uint32_t colour;
    colour = paired_cross(port, target32(port), source_colour(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_target_paired_cross(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_target_paired_cross_body(&port), entry->edx);
}

static uint32_t blend_shade_paired_body(Port *port)
{
    uint32_t colour;
    colour = shade_paired(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_shade_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_shade_paired_body(&port), entry->edx);
}

static uint32_t blend_levels_paired_body(Port *port)
{
    uint32_t colour;
    uint32_t target;
    colour = levels_mix_values(port, source_colour(port), target32(port));
    target = put32(port, colour);
    /* The entry index is taken from the stored pixel for its blue bits. */
    colour = (colour & 0xfcfc00) | (blend_u32(port, target, 0) & 0xfc);
    blend_set32(port, target, 0, paired_remap(port, colour));
    return target;
}

uint32_t vertrix_port_blend_levels_paired(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_levels_paired_body(&port), entry->edx);
}

static uint32_t blend_fixed_entry_levels_body(Port *port)
{
    uint32_t colour;
    colour = fixed_entry_levels(port, source_colour(port), target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_fixed_entry_levels(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_fixed_entry_levels_body(&port), entry->edx);
}

static uint32_t blend_paired_levels_body(Port *port)
{
    uint32_t colour;
    colour = paired_remap(port, source_colour(port));
    port_window_set32(port, &blend_globals, 0, REMAPPED, colour);
    colour = levels_mix_values(port, colour, target32(port));
    return put32(port, colour);
}

uint32_t vertrix_port_blend_paired_levels(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    return port_return(&port, blend_paired_levels_body(&port), entry->edx);
}

enum
{
    FIRST_ROW = 0x5bb7e0
};

/* 0x492a70's rows with the target pixel and row at `target_pixel` and `row_global`, the target
 * moving `step` bytes a row. */
static uint32_t render_sampled_rows_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t row_global,
                                       uint32_t step)
{
    Port port;
    uint32_t routine = entry->eax;
    uint32_t eax;
    uint32_t rows;
    uint32_t last;
    uint32_t source;
    uint32_t start = ROW_STARTS;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    rows = (uint32_t)((int32_t)port_window_u32(&port, &blend_globals, 0, ROWS) >> 16);
    last = rows - 1;
    port_window_set32(&port, &blend_globals, 0, ROW_INDEX,
                      port_window_u32(&port, &blend_globals, 0, ROW_INDEX) + rows - 2);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) +
             ((port_window_u16(&port, &blend_globals, 0, FIRST_ROW) *
               port_window_u32(&port, &blend_globals, 0, ROW_SCALE))
              << 2);
    port_window_set32(&port, &blend_globals, 0, row_global,
                      port_window_u32(&port, &blend_globals, 0, row_global) +
                          port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE) * last);
    port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
    port_window_set32(
        &port, &blend_globals, 0, MASK_ROW,
        port_window_u32(&port, &blend_globals, 0, MASK_ROW) +
            last *
                (uint32_t)((int32_t)port_window_u32(&port, &blend_globals, 0, MASK_STRIDE) >> 16));
    do
    {
        uint32_t steps;
        uint32_t target;
        uint32_t mask;
        count = port_window_u16(&port, &blend_globals, 0, WIDTH) - blend_u16(&port, start, 0);
        port_window_set32(&port, &blend_globals, 0, ROW_START, start);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        steps = port_window_u32(&port, &blend_globals, 0, NEXT_SAMPLE_STEPS);
        source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) +
                 (blend_u8(&port, steps, 0) << 2);
        port_window_set32(&port, &blend_globals, 0, NEXT_SAMPLE_STEPS, steps + 1);
        port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, source);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS,
                          port_window_u32(&port, &blend_globals, 0, ROW_INDEX));
        target = port_window_u32(&port, &blend_globals, 0, row_global);
        mask = port_window_u32(&port, &blend_globals, 0, MASK_ROW);
        port_window_set32(&port, &blend_globals, 0, target_pixel, target);
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, mask);
        port_window_set32(&port, &blend_globals, 0, row_global, target + step);
        port_window_set32(&port, &blend_globals, 0, MASK_ROW, mask + 1);
        port_call(&port, routine, mask + 1, target + step, routine, source);
        start = port_window_u32(&port, &blend_globals, 0, ROW_START);
        eax = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, eax);
        start += 2;
        count = (port_window_u16(&port, &blend_globals, 0, ROWS) - 1) & 0xffff;
        port_window_set16(&port, &blend_globals, 0, ROWS, count);
    } while (count != 0);
    port_window_set32(&port, &blend_globals, 0, ROW_START, start);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_sampled_rows(PORT_SIGNATURE)
{
    return render_sampled_rows_at(calls, services, globals, entry, TARGET_PIXEL, TARGET_ROW, 4);
}

uint32_t vertrix_port_render_sampled_rows_49a780(PORT_SIGNATURE)
{
    return render_sampled_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784, 2);
}

uint32_t vertrix_port_render_sampled_rows_4a2840(PORT_SIGNATURE)
{
    return render_sampled_rows_at(calls, services, globals, entry, 0x5bb780, 0x5bb784, 2);
}

/* The alpha byte of the source pixel. */
static uint32_t source_alpha_byte(Port *port)
{
    return source_colour(port) >> 24;
}

/* 0x4925d0's keyed masked row with the target pixel at `target_pixel`. */
static uint32_t keyed_mask_row_back(PORT_SIGNATURE, uint32_t target_pixel)
{
    PortWindows flat;
    PixelOperation operation = {0, NULL, 0};
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL);
    for (;;)
    {
        uint32_t steps;
        uint32_t target;
        uint32_t start;
        eax = port_window_u32(&port, &blend_globals, 0, ROW_START);
        if (blend_u16(&port, eax, 0) == 0)
        {
            break;
        }
        edx = (edx & 0xffffff00u) | blend_u8(&port, ecx, 0);
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
        if ((edx & 1) == 0)
        {
            eax = source_alpha_byte(&port);
            if ((eax & 0xff) != 0)
            {
                eax = pixel_call(&port, &operation, eax, edx, ebx, ecx);
                edx = vertrix_lift_edx;
            }
        }
        steps = port_window_u32(&port, &blend_globals, 0, SAMPLE_STEPS);
        edx = blend_u8(&port, steps, 0) * port_window_u32(&port, &blend_globals, 0, ROW_SCALE);
        target = port_window_u32(&port, &blend_globals, 0, target_pixel);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, steps - 1);
        target -= port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
        ebx = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) - (edx << 2);
        edx <<= 2;
        ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL) - high_word(&port, MASK_STRIDE);
        start = port_window_u32(&port, &blend_globals, 0, ROW_START);
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, ebx);
        ebx = ((ebx & 0xffff0000u) | blend_u16(&port, start, 0)) - 1;
        port_window_set32(&port, &blend_globals, 0, target_pixel, target);
        blend_set16(&port, start, 0, ebx);
    }
    while (port_window_u16(&port, &blend_globals, 0, ROW_COUNT) != 0)
    {
        uint32_t steps;
        uint32_t count;
        eax = source_alpha_byte(&port);
        port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
        if ((eax & 0xff) != 0)
        {
            eax = pixel_call(&port, &operation, eax, edx, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        steps = port_window_u32(&port, &blend_globals, 0, SAMPLE_STEPS);
        edx = blend_u8(&port, steps, 0) * port_window_u32(&port, &blend_globals, 0, ROW_SCALE);
        ecx = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL);
        port_window_set32(&port, &blend_globals, 0, SAMPLE_STEPS, steps - 1);
        eax = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL) - (edx << 2);
        edx <<= 2;
        count = port_window_u16(&port, &blend_globals, 0, ROW_COUNT) - 1;
        port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, eax);
        edx = port_window_u32(&port, &blend_globals, 0, target_pixel) -
              port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
        eax = high_word(&port, MASK_STRIDE);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT, count);
        port_window_set32(&port, &blend_globals, 0, target_pixel, edx);
        ecx -= eax;
    }
    port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, ecx);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_keyed_mask_row_back(PORT_SIGNATURE)
{
    return keyed_mask_row_back(calls, services, globals, entry, TARGET_PIXEL);
}

uint32_t vertrix_port_render_keyed_mask_row_back_49a2f0(PORT_SIGNATURE)
{
    return keyed_mask_row_back(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_keyed_mask_row_back_4a23b0(PORT_SIGNATURE)
{
    return keyed_mask_row_back(calls, services, globals, entry, 0x5bb780);
}

static uint32_t render_mask_alpha_row_at(PORT_SIGNATURE, uint32_t target_pixel)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    eax = mask_row(&port, entry, 1, target_pixel);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_mask_alpha_row_49a020(PORT_SIGNATURE)
{
    return render_mask_alpha_row_at(calls, services, globals, entry, 0x5bb780);
}

uint32_t vertrix_port_render_mask_alpha_row_4a20e0(PORT_SIGNATURE)
{
    return render_mask_alpha_row_at(calls, services, globals, entry, 0x5bb780);
}

enum
{
    RECTANGLE_ACROSS = 0x5bb750,
    RECTANGLE_ROWS = 0x5bb752,
    RECTANGLE_REMAP = 0,
    RECTANGLE_TINT,
    RECTANGLE_HALF_PLUS,
    RECTANGLE_HALF_TINT,
    RECTANGLE_HALF_PLUS_REMAP,
    /* What each original leaves in eax once a row is done: the pixel pointer at the row's end or
     * the row skip, whole or with its low half replaced by the row count (zero at the end). */
    LEFT_ROW_END = 0,
    LEFT_ROW_END_HIGH,
    LEFT_SKIP,
    LEFT_SKIP_HIGH
};

static uint32_t rectangle_colour(Port *port, int kind, uint32_t colour)
{
    switch (kind)
    {
        case RECTANGLE_REMAP:
            return remap(port, colour);
        case RECTANGLE_TINT:
            return remap_tint(port, colour);
        case RECTANGLE_HALF_PLUS:
            return half_plus(port, colour);
        case RECTANGLE_HALF_TINT:
            return half_tint(port, colour);
        default:
            return remap(port, half_plus(port, colour));
    }
}

/* The rectangle fills: each pixel of a rectangle at the target pointer (0x5bb768 for 32-bit
 * pixels, 0x5bb780 for 16-bit ones) is recoloured in place, 0x5bb750 pixels across and 0x5bb752
 * rows (counted down to zero in place), with 0x5bb7c8 bytes skipped after each row; the 8-bit
 * forms use the pointer at 0x5bb778. The pointer is left past the last row and 0x5bc016 at zero;
 * the narrow forms widen each pixel first and leave the last colour at 0x5bb774. */
static uint32_t rectangle_fill(PORT_SIGNATURE, int kind, int narrow, int format, int left)
{
    PortWindows flat;
    Port port;
    uint32_t eax = entry->eax;
    uint32_t pointer_global = TARGET_PIXEL;
    uint32_t pixel;
    uint32_t rows;
    uint32_t across;
    uint32_t colour;
    uint32_t map;
    if (narrow)
    {
        pointer_global = format == PIXEL_332 ? TARGET_PIXEL_8 : TARGET_PIXEL_16;
    }
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    pixel = port_window_u32(&port, &blend_globals, 0, pointer_global);
    map = port_window_u32(&port, &blend_globals, 0, MAP);
    rows = port_window_u16(&port, &blend_globals, 0, RECTANGLE_ROWS);
    if (rows == 0)
    {
        blend_reach = NULL;
        return port_return(&port, eax, entry->edx);
    }
    colour = port_window_u32(&port, &blend_globals, 0, WIDE_TARGET);
    for (; rows != 0; rows = (rows - 1) & 0xffff)
    {
        uint32_t skip;
        for (across = port_window_u16(&port, &blend_globals, 0, RECTANGLE_ACROSS); across != 0;
             across--)
        {
            if (narrow)
            {
                colour = rectangle_colour(&port, kind,
                                          widen16(read_narrow(&port, pixel, format), format));
                write_narrow(&port, pixel, format, narrow16(colour, format));
                pixel += format == PIXEL_332 ? 1 : 2;
            }
            else if (kind == RECTANGLE_HALF_PLUS_REMAP)
            {
                /* The half plus is stored first and its green and blue index bits read back; the
                 * map stays in hand until the end. */
                colour = half_plus(&port, blend_u32(&port, pixel, 0));
                blend_set32(&port, pixel, 0, colour);
                colour = (colour & 0xfc0000) | (blend_u32(&port, pixel, 0) & 0xfcfc);
                colour = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, COLOUR_ENTRIES),
                                   entry_index(colour) * 4);
                port_window_set32(&port, &blend_globals, 0, ENTRY, colour);
                map = blend_u32(&port, port_window_u32(&port, &blend_globals, 0, CHANNEL_MAPS),
                                port_window_u8(&port, &blend_globals, 0, ENTRY) * 4);
                colour = port_window_u32(&port, &blend_globals, 0, ENTRY);
                colour = (blend_u8(&port, map, colour >> 24) << 16) |
                         (blend_u8(&port, map, (colour >> 16) & 0xff) << 8) |
                         blend_u8(&port, map,
                                  (port_window_u16(&port, &blend_globals, 0, ENTRY) >> 8) & 0xff);
                blend_set32(&port, pixel, 0, colour);
                pixel += 4;
            }
            else
            {
                blend_set32(&port, pixel, 0,
                            rectangle_colour(&port, kind, blend_u32(&port, pixel, 0)));
                pixel += 4;
            }
        }
        skip = port_window_u32(&port, &blend_globals, 0, TARGET_SKIP);
        switch (left)
        {
            case LEFT_ROW_END:
                eax = pixel;
                break;
            case LEFT_ROW_END_HIGH:
                eax = pixel & 0xffff0000;
                break;
            case LEFT_SKIP:
                eax = skip;
                break;
            default:
                eax = skip & 0xffff0000;
                break;
        }
        pixel += skip;
        port_window_set16(&port, &blend_globals, 0, RECTANGLE_ROWS, rows - 1);
    }
    if (!narrow && kind == RECTANGLE_HALF_PLUS_REMAP)
    {
        port_window_set32(&port, &blend_globals, 0, MAP, map);
    }
    port_window_set32(&port, &blend_globals, 0, pointer_global, pixel);
    port_window_set16(&port, &blend_globals, 0, ROW_COUNT, 0);
    if (narrow)
    {
        port_window_set32(&port, &blend_globals, 0, WIDE_TARGET, colour);
    }
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_rectangle_remap32_492b90(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_REMAP, 0, 0, LEFT_SKIP);
}

uint32_t vertrix_port_rectangle_tint32_492cc0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_TINT, 0, 0, LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_half_tint32_492e40(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_TINT, 0, 0, LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_half_plus_remap32_492f90(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS_REMAP, 0, 0,
                          LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_remap16_49a8a0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_REMAP, 1, 0, LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_remap16_4a2960(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_REMAP, 1, 1, LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_tint16_49aa40(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_TINT, 1, 0, LEFT_SKIP_HIGH);
}

uint32_t vertrix_port_rectangle_tint16_4a2af0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_TINT, 1, 1, LEFT_SKIP_HIGH);
}

uint32_t vertrix_port_rectangle_half_plus16_49abb0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS, 1, 0,
                          LEFT_ROW_END_HIGH);
}

uint32_t vertrix_port_rectangle_half_plus16_4a2c60(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS, 1, 1,
                          LEFT_ROW_END_HIGH);
}

uint32_t vertrix_port_rectangle_half_tint16_49aca0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_TINT, 1, 0, LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_half_tint16_4a2d50(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_TINT, 1, 1, LEFT_SKIP);
}

uint32_t vertrix_port_rectangle_half_plus_remap16_49ae50(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS_REMAP, 1, 0,
                          LEFT_SKIP_HIGH);
}

uint32_t vertrix_port_rectangle_half_plus_remap16_4a2ef0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS_REMAP, 1, 1,
                          LEFT_ROW_END);
}

uint32_t vertrix_port_pixel8_copy_4a3540(PORT_SIGNATURE)
{
    return pixel16_copy(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_4a3580(PORT_SIGNATURE)
{
    return pixel16_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_4a3660(PORT_SIGNATURE)
{
    return pixel16_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_4a3720(PORT_SIGNATURE)
{
    return pixel16_half_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_tint_4a3770(PORT_SIGNATURE)
{
    return pixel16_half_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_remap_4a3880(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_mean_map_remap_4a3970(PORT_SIGNATURE)
{
    return pixel16_mean_map_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_average_4a3ac0(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_entry_mean_4a3b50(PORT_SIGNATURE)
{
    return pixel16_entry_mean(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_average_4a3ce0(PORT_SIGNATURE)
{
    return pixel16_average(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_add_4a3d70(PORT_SIGNATURE)
{
    return pixel16_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_subtract_4a3e20(PORT_SIGNATURE)
{
    return pixel16_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_subtract_from_4a3ed0(PORT_SIGNATURE)
{
    return pixel16_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_4a3f80(PORT_SIGNATURE)
{
    return pixel16_invert(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_target_4a3fd0(PORT_SIGNATURE)
{
    return pixel16_invert_target(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_cross_remap_4a4040(PORT_SIGNATURE)
{
    return pixel16_cross_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_cross_remap_4a4170(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_average_remap_4a42b0(PORT_SIGNATURE)
{
    return pixel16_average_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_average_4a43e0(PORT_SIGNATURE)
{
    return pixel16_remap_average(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_add_4a4520(PORT_SIGNATURE)
{
    return pixel16_remap_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_subtract_4a4660(PORT_SIGNATURE)
{
    return pixel16_remap_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_subtract_from_4a47a0(PORT_SIGNATURE)
{
    return pixel16_remap_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_invert_4a48e0(PORT_SIGNATURE)
{
    return pixel16_remap_invert(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_remap_invert_4a49e0(PORT_SIGNATURE)
{
    return pixel16_target_remap_invert(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_mean_map_tint_4a4b10(PORT_SIGNATURE)
{
    return pixel16_mean_map_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_quarters_plus_4a4c40(PORT_SIGNATURE)
{
    return pixel16_quarters_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_entry_mean_tint_4a4cd0(PORT_SIGNATURE)
{
    return pixel16_entry_mean_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_average_4a4e80(PORT_SIGNATURE)
{
    return pixel16_tint_average(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_add_4a4f90(PORT_SIGNATURE)
{
    return pixel16_tint_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_add_4a50c0(PORT_SIGNATURE)
{
    return pixel16_half_plus_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_tint_add_4a5180(PORT_SIGNATURE)
{
    return pixel16_half_tint_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_subtract_4a5300(PORT_SIGNATURE)
{
    return pixel16_tint_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_subtract_4a5420(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_tint_subtract_4a54e0(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_subtract_from_4a5660(PORT_SIGNATURE)
{
    return pixel16_tint_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_subtract_from_4a5780(PORT_SIGNATURE)
{
    return pixel16_half_plus_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_tint_subtract_from_4a5840(PORT_SIGNATURE)
{
    return pixel16_half_tint_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_tint_4a59c0(PORT_SIGNATURE)
{
    return pixel16_invert_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_half_plus_4a5aa0(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_half_tint_4a5b00(PORT_SIGNATURE)
{
    return pixel16_invert_half_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_target_tint_4a5c20(PORT_SIGNATURE)
{
    return pixel16_invert_target_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_target_half_plus_4a5d20(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_target_half_tint_4a5db0(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_source_tint_4a5ef0(PORT_SIGNATURE)
{
    return pixel16_source_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_cross_remap_half_plus_4a6020(PORT_SIGNATURE)
{
    return pixel16_cross_remap_half_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_cross_half_tint_4a6170(PORT_SIGNATURE)
{
    return pixel16_cross_half_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_tint_4a62d0(PORT_SIGNATURE)
{
    return pixel16_target_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_cross_remap_half_plus_4a6400(PORT_SIGNATURE)
{
    return pixel16_target_cross_remap_half_plus(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_cross_half_tint_4a6550(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_quarters_plus_remap_4a66b0(PORT_SIGNATURE)
{
    return pixel16_quarters_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_remap_add_4a67f0(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_remap_subtract_4a6950(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_remap_subtract_from_4a6aa0(PORT_SIGNATURE)
{
    return pixel16_half_plus_remap_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_half_plus_remap_4a6bf0(PORT_SIGNATURE)
{
    return pixel16_invert_half_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_invert_target_half_plus_remap_4a6d10(PORT_SIGNATURE)
{
    return pixel16_invert_target_half_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_cross_half_plus_remap_4a6e60(PORT_SIGNATURE)
{
    return pixel16_cross_half_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_cross_half_plus_remap_4a7050(PORT_SIGNATURE)
{
    return pixel16_target_cross_half_plus_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_shade_4a7240(PORT_SIGNATURE)
{
    return pixel16_shade(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_blend_levels8_4a73b0(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_entry_levels_4a74b0(PORT_SIGNATURE)
{
    return pixel16_entry_levels(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_blend_levels8_4a7690(PORT_SIGNATURE)
{
    return blend_levels16(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_levels_remap_4a7790(PORT_SIGNATURE)
{
    return pixel16_levels_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_remap_levels_4a7940(PORT_SIGNATURE)
{
    return pixel16_remap_levels(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_shade_tint_4a7af0(PORT_SIGNATURE)
{
    return pixel16_shade_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_levels_bias_4a7c30(PORT_SIGNATURE)
{
    return pixel16_levels_bias(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_entry_levels_tint_4a7d60(PORT_SIGNATURE)
{
    return pixel16_entry_levels_tint(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_tint_levels_4a7f60(PORT_SIGNATURE)
{
    return pixel16_tint_levels(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_levels_bias_remap_4a80e0(PORT_SIGNATURE)
{
    return pixel16_levels_bias_remap(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_entry_4a82c0(PORT_SIGNATURE)
{
    return pixel16_paired_entry(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_fixed_entry_4a83c0(PORT_SIGNATURE)
{
    return pixel16_fixed_entry(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_plus_paired_4a84b0(PORT_SIGNATURE)
{
    return pixel16_half_plus_paired(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_half_tint_fixed_4a85c0(PORT_SIGNATURE)
{
    return pixel16_half_tint_fixed(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_mean_map_paired_4a8760(PORT_SIGNATURE)
{
    return pixel16_mean_map_paired(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_average_paired_4a88d0(PORT_SIGNATURE)
{
    return pixel16_average_paired(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_fixed_entry_mean_4a8a30(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_mean(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_average_4a8be0(PORT_SIGNATURE)
{
    return pixel16_paired_average(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_add_4a8d40(PORT_SIGNATURE)
{
    return pixel16_paired_add(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_subtract_4a8ea0(PORT_SIGNATURE)
{
    return pixel16_paired_subtract(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_subtract_from_4a8ff0(PORT_SIGNATURE)
{
    return pixel16_paired_subtract_from(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_invert_4a9140(PORT_SIGNATURE)
{
    return pixel16_paired_invert(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_paired_invert_4a9250(PORT_SIGNATURE)
{
    return pixel16_target_paired_invert(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_cross_4a9390(PORT_SIGNATURE)
{
    return pixel16_paired_cross(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_target_paired_cross_4a94f0(PORT_SIGNATURE)
{
    return pixel16_target_paired_cross(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_shade_paired_4a9640(PORT_SIGNATURE)
{
    return pixel16_shade_paired(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_levels_paired_4a97d0(PORT_SIGNATURE)
{
    return pixel16_levels_paired(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_fixed_entry_levels_4a99a0(PORT_SIGNATURE)
{
    return pixel16_fixed_entry_levels(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_pixel8_paired_levels_4a9ba0(PORT_SIGNATURE)
{
    return pixel16_paired_levels(calls, services, globals, entry, PIXEL_332);
}

uint32_t vertrix_port_render_keyed_row8_4a9d70(PORT_SIGNATURE)
{
    return render_keyed_row32_at(calls, services, globals, entry, 0x5bb778, 1);
}

uint32_t vertrix_port_render_mask_alpha_row8_4a9de0(PORT_SIGNATURE)
{
    return render_mask_alpha_row_at(calls, services, globals, entry, 0x5bb778);
}

uint32_t vertrix_port_render_row8_4a9ee0(PORT_SIGNATURE)
{
    return render_row32_at(calls, services, globals, entry, 0x5bb778, 1);
}

uint32_t vertrix_port_render_sampled_row8_4aa030(PORT_SIGNATURE)
{
    return render_sampled_row32_at(calls, services, globals, entry, 0x5bb778, 1);
}

uint32_t vertrix_port_render_keyed_mask_row_back8_4aa0b0(PORT_SIGNATURE)
{
    return keyed_mask_row_back(calls, services, globals, entry, 0x5bb778);
}

uint32_t vertrix_port_render_image_rows8_4aa450(PORT_SIGNATURE)
{
    return render_image_rows_at(calls, services, globals, entry, 0x5bb778, 0x5bb77c, 1);
}

uint32_t vertrix_port_render_sampled_rows8_4aa540(PORT_SIGNATURE)
{
    return render_sampled_rows_at(calls, services, globals, entry, 0x5bb778, 0x5bb77c, 1);
}

uint32_t vertrix_port_rectangle_remap8_4aa660(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_REMAP, 1, PIXEL_332,
                          LEFT_ROW_END);
}

uint32_t vertrix_port_rectangle_tint8_4aa7f0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_TINT, 1, PIXEL_332,
                          LEFT_SKIP_HIGH);
}

uint32_t vertrix_port_rectangle_half_plus8_4aa950(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS, 1, PIXEL_332,
                          LEFT_ROW_END_HIGH);
}

uint32_t vertrix_port_rectangle_half_tint8_4aaa40(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_TINT, 1, PIXEL_332,
                          LEFT_SKIP);
}

uint32_t vertrix_port_rectangle_half_plus_remap8_4aabe0(PORT_SIGNATURE)
{
    return rectangle_fill(calls, services, globals, entry, RECTANGLE_HALF_PLUS_REMAP, 1, PIXEL_332,
                          LEFT_ROW_END);
}

enum
{
    PIXEL_32 = 3,
    ALPHA_TABLES = 0x588600,
    COLUMNS = 0x5bb750,
    COLUMN_HEIGHT = 0x5bb752
};

/* A source colour over a target colour by the source's alpha: each target channel looked up in the
 * alpha's 256-byte table (from 0x588600, kept at 0x55f1f4) plus the source channel, the three sums
 * or-ed together unmasked. */
static uint32_t alpha_over(Port *port, uint32_t source, uint32_t target)
{
    uint32_t table = ALPHA_TABLES + (source >> 24) * 0x100;
    uint32_t red;
    uint32_t green;
    port_window_set32(port, &blend_globals, 0, TARGET_LEVELS, table);
    red = (blend_u8(port, table, (target >> 16) & 0xff) + ((source >> 16) & 0xff)) << 16;
    green = (blend_u8(port, table, (target >> 8) & 0xff) + ((source >> 8) & 0xff)) << 8;
    return red | green | (blend_u8(port, table, target & 0xff) + (source & 0xff));
}

/* One source pixel over the target: copied when opaque, skipped when clear and blended by
 * alpha_over otherwise; a narrow target is widened through 0x5bb774, which keeps the blend. */
static void alpha_pixel(Port *port, uint32_t source, uint32_t target, int format)
{
    uint32_t colour = blend_u32(port, source, 0);
    uint32_t wide;
    if (colour >> 24 == 0xff)
    {
        if (format == PIXEL_32)
        {
            blend_set32(port, target, 0, colour);
        }
        else
        {
            write_narrow(port, target, format, narrow16(colour, format));
        }
    }
    else if (colour >> 24 != 0)
    {
        if (format == PIXEL_32)
        {
            blend_set32(port, target, 0, alpha_over(port, colour, blend_u32(port, target, 0)));
        }
        else
        {
            wide = widen16(read_narrow(port, target, format), format);
            port_window_set32(port, &blend_globals, 0, WIDE_TARGET, wide);
            wide = alpha_over(port, colour, wide);
            port_window_set32(port, &blend_globals, 0, WIDE_TARGET, wide);
            write_narrow(port, target, format, narrow16(wide, format));
        }
    }
}

/* The masked alpha blits by columns: 0x5bb750 columns of the 0x5bb752-row image, each drawn from
 * its bottom row up. The mask, source and target rows (0x5bb7e8, 0x5bb76c and the target row) are
 * first moved to the bottom row and then step one column along; each column's count from the row
 * starts at 0x5bb7ec (walked by 0x5bbfec) is counted down first and the rest of the column in
 * 0x5bc016. Pixels whose mask byte has its low bit set are skipped. */
static uint32_t alpha_columns(PORT_SIGNATURE, int format)
{
    PortWindows flat;
    Port port;
    uint32_t eax;
    uint32_t target_global = TARGET_PIXEL;
    uint32_t row_global = TARGET_ROW;
    uint32_t step = 4;
    uint32_t below;
    uint32_t mask;
    uint32_t source;
    uint32_t target;
    uint32_t columns;
    uint32_t start;
    if (format == PIXEL_332)
    {
        target_global = TARGET_PIXEL_8;
        row_global = TARGET_PIXEL_8 + 4;
        step = 1;
    }
    else if (format != PIXEL_32)
    {
        target_global = TARGET_PIXEL_16;
        row_global = TARGET_PIXEL_16 + 4;
        step = 2;
    }
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    target = port_window_u32(&port, &blend_globals, 0, target_global);
    mask = port_window_u32(&port, &blend_globals, 0, MASK_PIXEL);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    below = ((int32_t)port_window_u32(&port, &blend_globals, 0, COLUMNS) >> 16) - 1;
    port_window_set32(&port, &blend_globals, 0, MASK_ROW,
                      port_window_u32(&port, &blend_globals, 0, MASK_ROW) +
                          ((int32_t)port_window_u32(&port, &blend_globals, 0, MASK_STRIDE) >> 16) *
                              below);
    eax = below * port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
    below = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW) +
            ((int32_t)port_window_u32(&port, &blend_globals, 0, SOURCE_STRIDE) >> 16) * below * 4;
    port_window_set32(&port, &blend_globals, 0, ROW_START, ROW_STARTS);
    port_window_set32(&port, &blend_globals, 0, row_global,
                      port_window_u32(&port, &blend_globals, 0, row_global) + eax);
    port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, below);
    for (columns = port_window_u16(&port, &blend_globals, 0, COLUMNS); columns != 0;
         columns = port_window_u16(&port, &blend_globals, 0, COLUMNS))
    {
        start = port_window_u32(&port, &blend_globals, 0, ROW_START);
        mask = port_window_u32(&port, &blend_globals, 0, MASK_ROW);
        port_window_set32(&port, &blend_globals, 0, MASK_ROW, mask + 1);
        port_window_set16(&port, &blend_globals, 0, ROW_COUNT,
                          port_window_u16(&port, &blend_globals, 0, COLUMN_HEIGHT) -
                              blend_u16(&port, start, 0));
        source = port_window_u32(&port, &blend_globals, 0, SOURCE_ROW);
        target = port_window_u32(&port, &blend_globals, 0, row_global);
        port_window_set32(&port, &blend_globals, 0, SOURCE_ROW, source + 4);
        port_window_set32(&port, &blend_globals, 0, row_global, target + step);
        for (eax = port_window_u32(&port, &blend_globals, 0, ROW_START);
             blend_u16(&port, eax, 0) != 0;
             eax = port_window_u32(&port, &blend_globals, 0, ROW_START))
        {
            if ((blend_u8(&port, mask, 0) & 1) == 0)
            {
                alpha_pixel(&port, source, target, format);
            }
            source -= ((int32_t)port_window_u32(&port, &blend_globals, 0, SOURCE_STRIDE) >> 16) * 4;
            target -= port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
            start = port_window_u32(&port, &blend_globals, 0, ROW_START);
            blend_set16(&port, start, 0, blend_u16(&port, start, 0) - 1);
            mask -= (int32_t)port_window_u32(&port, &blend_globals, 0, MASK_STRIDE) >> 16;
        }
        while (port_window_u16(&port, &blend_globals, 0, ROW_COUNT) != 0)
        {
            if ((blend_u8(&port, mask, 0) & 1) == 0)
            {
                alpha_pixel(&port, source, target, format);
            }
            source -= ((int32_t)port_window_u32(&port, &blend_globals, 0, SOURCE_STRIDE) >> 16) * 4;
            target -= port_window_u32(&port, &blend_globals, 0, TARGET_STRIDE);
            port_window_set16(&port, &blend_globals, 0, ROW_COUNT,
                              port_window_u16(&port, &blend_globals, 0, ROW_COUNT) - 1);
            eax = (int32_t)port_window_u32(&port, &blend_globals, 0, MASK_STRIDE) >> 16;
            mask -= eax;
        }
        port_window_set32(&port, &blend_globals, 0, ROW_START,
                          port_window_u32(&port, &blend_globals, 0, ROW_START) + 2);
        port_window_set16(&port, &blend_globals, 0, COLUMNS,
                          port_window_u16(&port, &blend_globals, 0, COLUMNS) - 1);
    }
    port_window_set32(&port, &blend_globals, 0, SOURCE_PIXEL, source);
    port_window_set32(&port, &blend_globals, 0, MASK_PIXEL, mask);
    port_window_set32(&port, &blend_globals, 0, target_global, target);
    blend_reach = NULL;
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_alpha_columns32_4930c0(PORT_SIGNATURE)
{
    return alpha_columns(calls, services, globals, entry, PIXEL_32);
}

uint32_t vertrix_port_alpha_columns16_49b000(PORT_SIGNATURE)
{
    return alpha_columns(calls, services, globals, entry, PIXEL_555);
}

uint32_t vertrix_port_alpha_columns16_4a30a0(PORT_SIGNATURE)
{
    return alpha_columns(calls, services, globals, entry, PIXEL_565);
}

uint32_t vertrix_port_alpha_columns8_4aad90(PORT_SIGNATURE)
{
    return alpha_columns(calls, services, globals, entry, PIXEL_332);
}

enum
{
    IMAGE_COPY,
    IMAGE_KEYED,
    IMAGE_ALPHA
};

/* The image blits: a 0x5bb750 by 0x5bb752 image of 32-bit source pixels at [0x5bb764] onto the
 * target, the source rows 0x5bb79c pixels and the target rows 0x5bb7c8 bytes apart past their ends;
 * none of the pointers is kept. A copy stores every pixel, a keyed blit only those with any alpha
 * and an alpha blit copies the opaque ones and blends the rest over the target by alpha_over. The
 * 32-bit alpha blit (0x4ab380) adds to the red channel the low byte of ebp, which holds the
 * previous blend (at first the caller's ebp), in place of the source red; the source pointer is
 * left in eax, but the target pointer by the 32-bit blit. */
static uint32_t image_blit(PORT_SIGNATURE, int kind, int format)
{
    PortWindows flat;
    Port port;
    uint32_t target_global = TARGET_PIXEL;
    uint32_t step = 4;
    uint32_t width;
    uint32_t rows;
    uint32_t across;
    uint32_t source;
    uint32_t target;
    uint32_t source_skip;
    uint32_t target_skip;
    uint32_t colour;
    uint32_t alpha;
    uint32_t wide;
    if (format == PIXEL_332)
    {
        target_global = TARGET_PIXEL_8;
        step = 1;
    }
    else if (format != PIXEL_32)
    {
        target_global = TARGET_PIXEL_16;
        step = 2;
    }
    port_open(&port, calls, services, globals, entry);
    blend_globals = port_window(&port, GLOBALS_LOW, GLOBALS_HIGH - GLOBALS_LOW);
    port_windows_flat(&port, &flat);
    blend_reach = &flat;
    width = port_window_u16(&port, &blend_globals, 0, COLUMNS);
    rows = port_window_u16(&port, &blend_globals, 0, COLUMN_HEIGHT);
    target = port_window_u32(&port, &blend_globals, 0, target_global);
    source_skip = port_window_u32(&port, &blend_globals, 0, SOURCE_SKIP) * 4;
    target_skip = port_window_u32(&port, &blend_globals, 0, TARGET_SKIP);
    source = port_window_u32(&port, &blend_globals, 0, SOURCE_PIXEL);
    for (; rows != 0; rows--)
    {
        for (across = width; across != 0; across--)
        {
            colour = blend_u32(&port, source, 0);
            alpha = colour >> 24;
            if (kind == IMAGE_COPY || alpha == 0xff || (kind == IMAGE_KEYED && alpha != 0))
            {
                if (format == PIXEL_32)
                {
                    blend_set32(&port, target, 0, colour);
                }
                else
                {
                    write_narrow(&port, target, format, narrow16(colour, format));
                }
            }
            else if (alpha != 0 && format == PIXEL_32)
            {
                blend_set32(&port, target, 0,
                            alpha_over(&port, colour, blend_u32(&port, target, 0)));
            }
            else if (alpha != 0)
            {
                wide = widen16(read_narrow(&port, target, format), format);
                write_narrow(&port, target, format,
                             narrow16(alpha_over(&port, colour, wide), format));
            }
            source += 4;
            target += step;
        }
        source += source_skip;
        target += target_skip;
    }
    blend_reach = NULL;
    return port_return(&port, format == PIXEL_32 ? target : source, entry->edx);
}

uint32_t vertrix_port_image_alpha32_4ab380(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_ALPHA, PIXEL_32);
}

uint32_t vertrix_port_image_keyed16_4ab4a0(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_KEYED, PIXEL_555);
}

uint32_t vertrix_port_image_copy16_4ab540(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_COPY, PIXEL_555);
}

uint32_t vertrix_port_image_alpha16_4ab5e0(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_ALPHA, PIXEL_555);
}

uint32_t vertrix_port_image_keyed16_4ab790(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_KEYED, PIXEL_565);
}

uint32_t vertrix_port_image_copy16_4ab830(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_COPY, PIXEL_565);
}

uint32_t vertrix_port_image_alpha16_4ab8d0(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_ALPHA, PIXEL_565);
}

uint32_t vertrix_port_image_keyed8_4aba80(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_KEYED, PIXEL_332);
}

uint32_t vertrix_port_image_copy8_4abb30(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_COPY, PIXEL_332);
}

uint32_t vertrix_port_image_alpha8_4abbd0(PORT_SIGNATURE)
{
    return image_blit(calls, services, globals, entry, IMAGE_ALPHA, PIXEL_332);
}

static PixelBody pixel_body(LiftRoutine routine)
{
    static const struct
    {
        LiftRoutine routine;
        PixelBody body;
    } bodies[] = {
        {vertrix_port_blend_copy, blend_copy_body},
        {vertrix_port_blend_remap, blend_remap_body},
        {vertrix_port_blend_add, blend_add_body},
        {vertrix_port_blend_subtract, blend_subtract_body},
        {vertrix_port_blend_average_remap, blend_average_remap_body},
        {vertrix_port_blend_remap_add, blend_remap_add_body},
        {vertrix_port_blend_remap_subtract, blend_remap_subtract_body},
        {vertrix_port_blend_tint_average, blend_tint_average_body},
        {vertrix_port_blend_tint_add, blend_tint_add_body},
        {vertrix_port_blend_half_tint, blend_half_tint_body},
        {vertrix_port_blend_levels_remap, blend_levels_remap_body},
        {vertrix_port_blend_levels, blend_levels_body},
        {vertrix_port_blend_shade, blend_shade_body},
        {vertrix_port_blend_average, blend_average_body},
        {vertrix_port_blend_remap_levels, blend_remap_levels_body},
        {vertrix_port_blend_tint_levels, blend_tint_levels_body},
        {vertrix_port_blend_subtract_from, blend_subtract_from_body},
        {vertrix_port_blend_invert, blend_invert_body},
        {vertrix_port_blend_invert_target, blend_invert_target_body},
        {vertrix_port_blend_half_plus, blend_half_plus_body},
        {vertrix_port_blend_half_plus_remap, blend_half_plus_remap_body},
        {vertrix_port_blend_target_cross_remap, blend_target_cross_remap_body},
        {vertrix_port_blend_remap_average, blend_remap_average_body},
        {vertrix_port_blend_remap_subtract_from, blend_remap_subtract_from_body},
        {vertrix_port_blend_remap_invert, blend_remap_invert_body},
        {vertrix_port_blend_target_remap_invert, blend_target_remap_invert_body},
        {vertrix_port_blend_mean_map_tint, blend_mean_map_tint_body},
        {vertrix_port_blend_quarters_plus, blend_quarters_plus_body},
        {vertrix_port_blend_entry_mean_tint, blend_entry_mean_tint_body},
        {vertrix_port_blend_quarters_plus_remap, blend_quarters_plus_remap_body},
        {vertrix_port_blend_invert_half_plus_remap, blend_invert_half_plus_remap_body},
        {vertrix_port_blend_invert_target_half_plus_remap,
         blend_invert_target_half_plus_remap_body},
        {vertrix_port_blend_levels_bias, blend_levels_bias_body},
        {vertrix_port_blend_entry_levels_tint, blend_entry_levels_tint_body},
        {vertrix_port_blend_paired, blend_paired_body},
        {vertrix_port_blend_fixed_entry, blend_fixed_entry_body},
        {vertrix_port_blend_half_plus_paired, blend_half_plus_paired_body},
        {vertrix_port_blend_half_tint_fixed, blend_half_tint_fixed_body},
        {vertrix_port_blend_mean_map_paired, blend_mean_map_paired_body},
        {vertrix_port_blend_average_paired, blend_average_paired_body},
        {vertrix_port_blend_fixed_entry_mean, blend_fixed_entry_mean_body},
        {vertrix_port_blend_paired_average, blend_paired_average_body},
        {vertrix_port_blend_paired_invert, blend_paired_invert_body},
        {vertrix_port_blend_target_paired_invert, blend_target_paired_invert_body},
        {vertrix_port_blend_paired_cross, blend_paired_cross_body},
        {vertrix_port_blend_target_paired_cross, blend_target_paired_cross_body},
        {vertrix_port_blend_shade_paired, blend_shade_paired_body},
        {vertrix_port_blend_levels_paired, blend_levels_paired_body},
        {vertrix_port_blend_fixed_entry_levels, blend_fixed_entry_levels_body},
        {vertrix_port_blend_paired_levels, blend_paired_levels_body},
    };
    unsigned i;
    for (i = 0; i < sizeof bodies / sizeof bodies[0]; i++)
    {
        if (bodies[i].routine == routine)
        {
            return bodies[i].body;
        }
    }
    return NULL;
}

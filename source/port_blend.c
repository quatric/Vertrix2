#include "port_blend.h"

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
    KEY_SHIFT = 24
};

/* The entry index of a colour: the top six bits of each channel, red highest. */
static uint32_t entry_index(uint32_t colour)
{
    return (((colour & 0xfc0000) >> 4) | ((colour & 0xfc00) >> 2) | (colour & 0xfc)) >> 2;
}

/* The remapped colour of a colour entry (both tables described in port_blend.h). */
static uint32_t remap_entry(Port *port, uint32_t entry)
{
    uint32_t map;
    uint32_t red;
    uint32_t green;
    port_set32(port, 0, ENTRY, entry);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (entry & 0xff) * 4);
    port_set32(port, 0, MAP, map);
    red = port_u8(port, map, entry >> 24) << 16;
    green = port_u8(port, map, (entry >> 16) & 0xff) << 8;
    return red | green | port_u8(port, map, (entry >> 8) & 0xff);
}

static uint32_t remap(Port *port, uint32_t colour)
{
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    return remap_entry(port, port_u32(port, entries, entry_index(colour) * 4));
}

static uint32_t remap_tint(Port *port, uint32_t colour)
{
    uint32_t select = port_u8(port, port_u32(port, 0, COLOUR_ENTRIES), entry_index(colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    uint32_t red = port_u8(port, map, port_u16(port, 0, TINT_RED)) << 16;
    uint32_t green;
    port_set32(port, 0, MAP, map);
    green = port_u8(port, map, port_u16(port, 0, TINT_GREEN)) << 8;
    return red | green | port_u8(port, map, port_u16(port, 0, TINT_BLUE));
}

static uint32_t source_colour(Port *port)
{
    return port_u32(port, port_u32(port, 0, SOURCE_PIXEL), 0);
}

/* Add `colour` to the target pixel at `target`, each channel saturating at 0xff. */
static void add_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t sum = (port_u32(port, target, 0) & LOW_BITS_CLEAR) + (colour & LOW_BITS_CLEAR);
    uint32_t full = CARRIES - ((sum & CARRIES) >> 7);
    port_set32(port, 0, RAW_SUM, sum);
    port_set32(port, target, 0, (full | sum) & CHANNELS);
}

/* Subtract `colour` from the target pixel at `target`, each channel stopping at 0. */
static void subtract_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t difference = (port_u32(port, target, 0) & LOW_BITS_CLEAR) - (colour & LOW_BITS_CLEAR);
    uint32_t keep = ((difference & CARRIES) >> 7) - 0x1010101;
    port_set32(port, 0, RAW_SUM, difference);
    port_set32(port, target, 0, keep & difference & CHANNELS);
}

static uint32_t average(uint32_t first, uint32_t second)
{
    return ((first >> 1) & HALF) + ((second >> 1) & HALF);
}

uint32_t vertrix_port_blend_copy(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = source_colour(&port);
    port_set32(&port, port_u32(&port, 0, TARGET_PIXEL), 0, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, port_u32(&port, 0, TARGET_PIXEL), 0, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    target = port_u32(&port, 0, TARGET_PIXEL);
    add_saturate(&port, target, source_colour(&port));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_subtract(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    target = port_u32(&port, 0, TARGET_PIXEL);
    subtract_saturate(&port, target, source_colour(&port));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_average_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t source;
    uint32_t target;
    uint32_t mixed;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    target = port_u32(&port, 0, TARGET_PIXEL);
    mixed = average(port_u32(&port, source, 0), port_u32(&port, target, 0));
    port_set32(&port, target, 0, mixed);
    port_set32(&port, target, 0, remap(&port, port_u32(&port, target, 0)));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_remap_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    add_saturate(&port, target, colour);
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_remap_subtract(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    subtract_saturate(&port, target, colour);
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_tint_average(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap_tint(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    port_set32(&port, target, 0, average(port_u32(&port, target, 0), colour));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_tint_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap_tint(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    add_saturate(&port, target, colour);
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_half_tint(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t entry_value;
    uint32_t map;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_open(&port, calls, services, globals, entry);
    colour = source_colour(&port);
    entry_value = port_u32(&port, port_u32(&port, 0, COLOUR_ENTRIES), entry_index(colour) * 4);
    port_set32(&port, 0, ENTRY, entry_value);
    map = port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (entry_value & 0xff) * 4);
    port_set32(&port, 0, MAP, map);
    red = port_u8(&port, map, ((entry_value >> 24) + port_u16(&port, 0, TINT_RED)) >> 1);
    green =
        port_u8(&port, map, (((entry_value >> 16) & 0xff) + port_u16(&port, 0, TINT_GREEN)) >> 1);
    blue = port_u8(&port, map, (((entry_value >> 8) & 0xff) + port_u16(&port, 0, TINT_BLUE)) >> 1);
    colour = (red << 16) | (green << 8) | blue;
    port_set32(&port, port_u32(&port, 0, TARGET_PIXEL), 0, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_render_row32(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    count = port_u16(&port, 0, ROW_COUNT);
    while (count != 0)
    {
        port_set16(&port, 0, ROW_COUNT, count);
        eax = port_call(&port, port_u32(&port, 0, PIXEL_OPERATION), eax,
                        (edx & 0xffff0000u) | count, ebx, ecx);
        edx = vertrix_lift_edx;
        count = port_u16(&port, 0, ROW_COUNT);
        ecx = port_u32(&port, 0, SOURCE_PIXEL) + PIXEL_SIZE;
        ebx = port_u32(&port, 0, TARGET_PIXEL) + PIXEL_SIZE;
        port_set32(&port, 0, SOURCE_PIXEL, ecx);
        port_set32(&port, 0, TARGET_PIXEL, ebx);
        count = (count - 1) & 0xffff;
    }
    port_set16(&port, 0, ROW_COUNT, count);
    return port_return(&port, eax, entry->edx);
}

/* The two-table sum of 0x490560 and 0x4902a0: each channel of the source looked up in the byte
 * table at [0x55f1f0] plus the target's in the table at [0x55f1f4]. The sums can reach 0x1fe:
 * they are or-ed into place, not added. */
static uint32_t levels_mix(Port *port, uint32_t source, uint32_t target)
{
    uint32_t source_levels = port_u32(port, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_u32(port, 0, TARGET_LEVELS);
    uint32_t red = port_u8(port, source_levels, (port_u32(port, source, 0) >> 16) & 0xff) +
                   port_u8(port, target_levels, (port_u32(port, target, 0) >> 16) & 0xff);
    uint32_t green = port_u8(port, source_levels, port_u16(port, source, 0) >> 8) +
                     port_u8(port, target_levels, port_u16(port, target, 0) >> 8);
    uint32_t blue = port_u8(port, source_levels, port_u8(port, source, 0)) +
                    port_u8(port, target_levels, port_u8(port, target, 0));
    return (red << 16) | (green << 8) | blue;
}

uint32_t vertrix_port_blend_levels_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    uint32_t mixed;
    uint32_t entries;
    port_open(&port, calls, services, globals, entry);
    target = port_u32(&port, 0, TARGET_PIXEL);
    mixed = levels_mix(&port, port_u32(&port, 0, SOURCE_PIXEL), target);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    port_set32(&port, target, 0, mixed);
    port_set32(&port, target, 0,
               remap_entry(&port, port_u32(&port, entries, entry_index(mixed) * 4)));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_levels(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, target, 0, levels_mix(&port, port_u32(&port, 0, SOURCE_PIXEL), target));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_shade(PORT_SIGNATURE)
{
    Port port;
    uint32_t entries;
    uint32_t colour_entry;
    uint32_t target;
    uint32_t shade;
    uint32_t level;
    uint32_t map;
    uint32_t red;
    uint32_t green;
    port_open(&port, calls, services, globals, entry);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    colour_entry = port_u32(&port, entries, entry_index(source_colour(&port)) * 4);
    port_set32(&port, 0, ENTRY, colour_entry);
    target = port_u32(&port, 0, TARGET_PIXEL);
    shade = port_u8(&port, entries, entry_index(port_u32(&port, target, 0)) * 4);
    level = port_u16(&port, port_u32(&port, 0, SHADE_LEVELS), (colour_entry & 0xff) * 2) +
            port_u16(&port, port_u32(&port, 0, SHADE_STEPS), shade * 2);
    map =
        port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (uint32_t)((int32_t)(int16_t)level * 4));
    port_set32(&port, 0, MAP, map);
    red = port_u8(&port, map, colour_entry >> 24) << 16;
    green = port_u8(&port, map, (colour_entry >> 16) & 0xff) << 8;
    port_set32(&port, target, 0, red | green | port_u8(&port, map, (colour_entry >> 8) & 0xff));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_render_sampled_row32(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t source;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    count = port_u16(&port, 0, ROW_COUNT);
    do
    {
        eax = port_u32(&port, source, 0);
        port_set32(&port, 0, SOURCE_PIXEL, source);
        eax >>= 24;
        port_set16(&port, 0, ROW_COUNT, count);
        if (eax != 0)
        {
            eax = port_call(&port, port_u32(&port, 0, PIXEL_OPERATION), eax, edx,
                            (entry->ebx & 0xffff0000u) | count, source);
        }
        eax = port_u32(&port, 0, SAMPLE_STEPS);
        source = port_u32(&port, 0, SOURCE_PIXEL) + (port_u8(&port, eax, 0) << 2);
        count = port_u16(&port, 0, ROW_COUNT);
        edx = port_u32(&port, 0, TARGET_PIXEL) + PIXEL_SIZE;
        eax++;
        port_set32(&port, 0, SAMPLE_STEPS, eax);
        port_set32(&port, 0, TARGET_PIXEL, edx);
        count = (count - 1) & 0xffff;
    } while (count != 0);
    port_set16(&port, 0, ROW_COUNT, count);
    port_set32(&port, 0, SOURCE_PIXEL, source);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_keyed_row32(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t source;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    count = port_u16(&port, 0, ROW_COUNT);
    while (count != 0)
    {
        eax = port_u32(&port, source, 0);
        port_set16(&port, 0, ROW_COUNT, count);
        eax >>= 24;
        port_set32(&port, 0, SOURCE_PIXEL, source);
        if (eax != 0)
        {
            eax = port_call(&port, port_u32(&port, 0, PIXEL_OPERATION), eax,
                            (edx & 0xffff0000u) | count, entry->ebx, source);
        }
        edx = port_u32(&port, 0, TARGET_PIXEL) + PIXEL_SIZE;
        source = port_u32(&port, 0, SOURCE_PIXEL);
        port_set32(&port, 0, TARGET_PIXEL, edx);
        count = (port_u16(&port, 0, ROW_COUNT) - 1) & 0xffff;
        source += PIXEL_SIZE;
    }
    port_set32(&port, 0, SOURCE_PIXEL, source);
    port_set16(&port, 0, ROW_COUNT, count);
    return port_return(&port, eax, entry->edx);
}

/* The signed high word of a dword global: the original reads the dword and shifts it right. */
static uint32_t high_word(Port *port, uint32_t address)
{
    return (uint32_t)((int32_t)port_u32(port, 0, address) >> 16);
}

uint32_t vertrix_port_render_image_rows(PORT_SIGNATURE)
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
    last = high_word(&port, ROWS) - 1;
    mask = port_u32(&port, 0, MASK_ROW) + high_word(&port, MASK_STRIDE) * last;
    source_step = high_word(&port, SOURCE_STRIDE) * last;
    eax = last * port_u32(&port, 0, TARGET_STRIDE);
    source_step = port_u32(&port, 0, SOURCE_ROW) + (source_step << 2);
    target_row = port_u32(&port, 0, TARGET_ROW);
    port_set32(&port, 0, MASK_ROW, mask);
    port_set32(&port, 0, SOURCE_ROW, source_step);
    port_set32(&port, 0, TARGET_ROW, target_row + eax);
    rows = port_u16(&port, 0, ROWS);
    while (rows != 0)
    {
        uint32_t width = port_u16(&port, 0, WIDTH);
        uint32_t target = port_u32(&port, 0, TARGET_ROW);
        uint32_t source;
        port_set32(&port, 0, ROW_START, start);
        width -= port_u16(&port, start, 0);
        port_set32(&port, 0, TARGET_PIXEL, target);
        port_set16(&port, 0, ROW_COUNT, width);
        mask = port_u32(&port, 0, MASK_ROW);
        target += 4;
        source = port_u32(&port, 0, SOURCE_ROW);
        port_set32(&port, 0, MASK_PIXEL, mask);
        port_set32(&port, 0, TARGET_ROW, target);
        port_set32(&port, 0, SOURCE_PIXEL, source);
        mask++;
        source += 4;
        port_set32(&port, 0, MASK_ROW, mask);
        port_set32(&port, 0, SOURCE_ROW, source);
        eax = port_call(&port, routine, source, target, routine, mask);
        start = port_u32(&port, 0, ROW_START) + 2;
        rows = (port_u16(&port, 0, ROWS) - 1) & 0xffff;
        port_set16(&port, 0, ROWS, rows);
    }
    port_set32(&port, 0, ROW_START, start);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_indexed_rows(PORT_SIGNATURE)
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
    ebx = port_u32(&port, 0, TARGET_ROW);
    esi = port_u32(&port, 0, SOURCE_ROW);
    do
    {
        uint32_t index = port_u32(&port, 0, ROW_INDEX);
        edi = port_u32(&port, 0, ROW_SCALE);
        edx = port_u8(&port, index, 0) * edi;
        port_set32(&port, 0, ROW_INDEX, index + 1);
        ebx += port_u32(&port, 0, TARGET_STRIDE);
        eax = port_u32(&port, 0, NEXT_SAMPLE_STEPS);
        port_set32(&port, 0, TARGET_ROW, ebx);
        port_set32(&port, 0, SAMPLE_STEPS, eax);
        edx <<= 2;
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, ROWS);
        esi += edx;
        port_set16(&port, 0, ROW_COUNT, eax);
        port_set32(&port, 0, SOURCE_ROW, esi);
        eax = port_call_with(&port, routine, eax, edx, ebx, routine, esi, edi, entry->ebp);
        esi = port_u32(&port, 0, SOURCE_ROW);
        ebx = port_u32(&port, 0, TARGET_ROW);
        count = port_u16(&port, 0, WIDTH);
        port_set32(&port, 0, SOURCE_PIXEL, esi);
        port_set32(&port, 0, TARGET_PIXEL, ebx);
        count = (count - 1) & 0xffff;
        port_set16(&port, 0, WIDTH, count);
    } while (count != 0);
    return port_return(&port, eax, entry->edx);
}

/* The step back of a masked row's skipped part (0x492499 and 0x492386): the source and target
 * pixel and the mask move back one pixel, and the start word at [0x5bbfec] counts down. */
static void mask_skip_step(Port *port, MaskRegisters *r)
{
    uint32_t start;
    r->edx = port_u32(port, 0, SOURCE_PIXEL) - (high_word(port, SOURCE_STRIDE) << 2);
    r->ecx = port_u32(port, 0, TARGET_PIXEL);
    port_set32(port, 0, SOURCE_PIXEL, r->edx);
    r->ecx -= port_u32(port, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    r->edx = port_u32(port, 0, MASK_PIXEL) - r->eax;
    start = port_u32(port, 0, ROW_START);
    port_set32(port, 0, TARGET_PIXEL, r->ecx);
    port_set16(port, start, 0, port_u16(port, start, 0) - 1);
    r->eax = start;
}

/* The step back after a drawn pixel (0x4924f3 and 0x49232c): the same moves, with the pixel count
 * at 0x5bc016 counting down. */
static void mask_draw_step(Port *port, MaskRegisters *r)
{
    uint32_t target;
    r->edx = port_u32(port, 0, MASK_PIXEL);
    r->ebx = port_u32(port, 0, SOURCE_PIXEL) - (high_word(port, SOURCE_STRIDE) << 2);
    target = port_u32(port, 0, TARGET_PIXEL);
    port_set16(port, 0, ROW_COUNT, port_u16(port, 0, ROW_COUNT) - 1);
    target -= port_u32(port, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    port_set32(port, 0, SOURCE_PIXEL, r->ebx);
    port_set32(port, 0, TARGET_PIXEL, target);
    r->edx -= r->eax;
}

/* The source pixel's alpha (top) byte. */
static uint32_t source_alpha(Port *port)
{
    return port_u32(port, port_u32(port, 0, SOURCE_PIXEL), 0) >> 24;
}

static uint32_t mask_row(Port *port, const LiftEntry *entry, int alpha)
{
    MaskRegisters r = {entry->eax, 0, entry->ebx, entry->ecx};
    r.edx = port_u32(port, 0, MASK_PIXEL);
    for (;;)
    {
        r.eax = port_u32(port, 0, ROW_START);
        if (port_u16(port, r.eax, 0) == 0)
        {
            break;
        }
        r.ebx = (r.ebx & 0xffffff00u) | port_u8(port, r.edx, 0);
        port_set32(port, 0, MASK_PIXEL, r.edx);
        if ((r.ebx & 1) == 0)
        {
            if (alpha)
            {
                r.eax = source_alpha(port);
            }
            if (!alpha || r.eax != 0)
            {
                r.eax =
                    port_call(port, port_u32(port, 0, PIXEL_OPERATION), r.eax, r.edx, r.ebx, r.ecx);
            }
        }
        mask_skip_step(port, &r);
    }
    while (port_u16(port, 0, ROW_COUNT) != 0)
    {
        if (alpha)
        {
            r.eax = source_alpha(port);
        }
        port_set32(port, 0, MASK_PIXEL, r.edx);
        if (!alpha || r.eax != 0)
        {
            r.eax = port_call(port, port_u32(port, 0, PIXEL_OPERATION), r.eax, r.edx, r.ebx, r.ecx);
        }
        mask_draw_step(port, &r);
    }
    port_set32(port, 0, MASK_PIXEL, r.edx);
    return r.eax;
}

uint32_t vertrix_port_render_mask_row(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = mask_row(&port, entry, 0);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_render_mask_alpha_row(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = mask_row(&port, entry, 1);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_blend_average(PORT_SIGNATURE)
{
    Port port;
    uint32_t target;
    uint32_t source;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, target, 0, average(port_u32(&port, source, 0), port_u32(&port, target, 0)));
    return port_return(&port, target, entry->edx);
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
    run = port_u16(&port, 0, ROWS);
    runs = port_u16(&port, 0, WIDTH);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    target = port_u32(&port, 0, TARGET_PIXEL);
    target_skip = port_u32(&port, 0, TARGET_SKIP);
    source_skip = port_u32(&port, 0, SOURCE_SKIP) << 2;
    for (; runs != 0; runs = (runs - 1) & 0xffff)
    {
        uint32_t left;
        for (left = run; left != 0; left = (left - 1) & 0xffff)
        {
            target += PIXEL_SIZE;
            port_set32(&port, target, -4u, port_u32(&port, source, 0));
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
    run = port_u16(&port, 0, ROWS);
    runs = port_u16(&port, 0, WIDTH);
    source = port_u32(&port, 0, SOURCE_PIXEL);
    target = port_u32(&port, 0, TARGET_PIXEL);
    source_skip = port_u32(&port, 0, SOURCE_SKIP) << 2;
    target_skip = port_u32(&port, 0, TARGET_SKIP);
    for (; runs != 0; runs = (runs - 1) & 0xffff)
    {
        uint32_t left;
        for (left = run; left != 0; left = (left - 1) & 0xffff)
        {
            uint32_t pixel = port_u32(&port, source, 0);
            if ((pixel >> KEY_SHIFT) != 0)
            {
                port_set32(&port, target, 0, pixel);
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
    uint32_t source_levels = port_u32(port, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_u32(port, 0, TARGET_LEVELS);
    uint32_t red = port_u8(port, target_levels, (port_u32(port, target, 0) >> 16) & 0xff) +
                   port_u8(port, source_levels, (colour >> 16) & 0xff);
    uint32_t green = port_u8(port, target_levels, port_u16(port, target, 0) >> 8) +
                     port_u8(port, source_levels, (colour & 0xffff) >> 8);
    uint32_t blue = port_u8(port, target_levels, port_u8(port, target, 0)) +
                    port_u8(port, source_levels, colour & 0xff);
    return (red << 16) | (green << 8) | blue;
}

uint32_t vertrix_port_blend_remap_levels(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    port_set32(&port, target, 0, levels_mix_colour(&port, port_u32(&port, 0, REMAPPED), target));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_tint_levels(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = remap_tint(&port, source_colour(&port));
    target = port_u32(&port, 0, TARGET_PIXEL);
    port_set32(&port, 0, REMAPPED, colour);
    port_set32(&port, target, 0, levels_mix_colour(&port, port_u32(&port, 0, REMAPPED), target));
    return port_return(&port, target, entry->edx);
}

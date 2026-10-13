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

/* 0x492400's row with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t render_row32_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
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
        ebx = port_u32(&port, 0, target_pixel) + step;
        port_set32(&port, 0, SOURCE_PIXEL, ecx);
        port_set32(&port, 0, target_pixel, ebx);
        count = (count - 1) & 0xffff;
    }
    port_set16(&port, 0, ROW_COUNT, count);
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

/* 0x492550's row with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t render_sampled_row32_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
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
        edx = port_u32(&port, 0, target_pixel) + step;
        eax++;
        port_set32(&port, 0, SAMPLE_STEPS, eax);
        port_set32(&port, 0, target_pixel, edx);
        count = (count - 1) & 0xffff;
    } while (count != 0);
    port_set16(&port, 0, ROW_COUNT, count);
    port_set32(&port, 0, SOURCE_PIXEL, source);
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
        edx = port_u32(&port, 0, target_pixel) + step;
        source = port_u32(&port, 0, SOURCE_PIXEL);
        port_set32(&port, 0, target_pixel, edx);
        count = (port_u16(&port, 0, ROW_COUNT) - 1) & 0xffff;
        source += PIXEL_SIZE;
    }
    port_set32(&port, 0, SOURCE_PIXEL, source);
    port_set16(&port, 0, ROW_COUNT, count);
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
    return (uint32_t)((int32_t)port_u32(port, 0, address) >> 16);
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
    last = high_word(&port, ROWS) - 1;
    mask = port_u32(&port, 0, MASK_ROW) + high_word(&port, MASK_STRIDE) * last;
    source_step = high_word(&port, SOURCE_STRIDE) * last;
    eax = last * port_u32(&port, 0, TARGET_STRIDE);
    source_step = port_u32(&port, 0, SOURCE_ROW) + (source_step << 2);
    target_row = port_u32(&port, 0, row_global);
    port_set32(&port, 0, MASK_ROW, mask);
    port_set32(&port, 0, SOURCE_ROW, source_step);
    port_set32(&port, 0, row_global, target_row + eax);
    rows = port_u16(&port, 0, ROWS);
    while (rows != 0)
    {
        uint32_t width = port_u16(&port, 0, WIDTH);
        uint32_t target = port_u32(&port, 0, row_global);
        uint32_t source;
        port_set32(&port, 0, ROW_START, start);
        width -= port_u16(&port, start, 0);
        port_set32(&port, 0, target_pixel, target);
        port_set16(&port, 0, ROW_COUNT, width);
        mask = port_u32(&port, 0, MASK_ROW);
        target += step;
        source = port_u32(&port, 0, SOURCE_ROW);
        port_set32(&port, 0, MASK_PIXEL, mask);
        port_set32(&port, 0, row_global, target);
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
    ebx = port_u32(&port, 0, target_row);
    esi = port_u32(&port, 0, SOURCE_ROW);
    do
    {
        uint32_t index = port_u32(&port, 0, ROW_INDEX);
        edi = port_u32(&port, 0, ROW_SCALE);
        edx = port_u8(&port, index, 0) * edi;
        port_set32(&port, 0, ROW_INDEX, index + 1);
        ebx += port_u32(&port, 0, TARGET_STRIDE);
        eax = port_u32(&port, 0, NEXT_SAMPLE_STEPS);
        port_set32(&port, 0, target_row, ebx);
        port_set32(&port, 0, SAMPLE_STEPS, eax);
        edx <<= 2;
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, ROWS);
        esi += edx;
        port_set16(&port, 0, ROW_COUNT, eax);
        port_set32(&port, 0, SOURCE_ROW, esi);
        eax = port_call_with(&port, routine, eax, edx, ebx, routine, esi, edi, entry->ebp);
        esi = port_u32(&port, 0, SOURCE_ROW);
        ebx = port_u32(&port, 0, target_row);
        count = port_u16(&port, 0, WIDTH);
        port_set32(&port, 0, SOURCE_PIXEL, esi);
        port_set32(&port, 0, target_pixel, ebx);
        count = (count - 1) & 0xffff;
        port_set16(&port, 0, WIDTH, count);
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
    r->edx = port_u32(port, 0, SOURCE_PIXEL) - (high_word(port, SOURCE_STRIDE) << 2);
    r->ecx = port_u32(port, 0, target_pixel);
    port_set32(port, 0, SOURCE_PIXEL, r->edx);
    r->ecx -= port_u32(port, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    r->edx = port_u32(port, 0, MASK_PIXEL) - r->eax;
    start = port_u32(port, 0, ROW_START);
    port_set32(port, 0, target_pixel, r->ecx);
    port_set16(port, start, 0, port_u16(port, start, 0) - 1);
    r->eax = start;
}

/* The step back after a drawn pixel (0x4924f3 and 0x49232c): the same moves, with the pixel count
 * at 0x5bc016 counting down. */
static void mask_draw_step(Port *port, MaskRegisters *r, uint32_t target_pixel)
{
    uint32_t target;
    r->edx = port_u32(port, 0, MASK_PIXEL);
    r->ebx = port_u32(port, 0, SOURCE_PIXEL) - (high_word(port, SOURCE_STRIDE) << 2);
    target = port_u32(port, 0, target_pixel);
    port_set16(port, 0, ROW_COUNT, port_u16(port, 0, ROW_COUNT) - 1);
    target -= port_u32(port, 0, TARGET_STRIDE);
    r->eax = high_word(port, MASK_STRIDE);
    port_set32(port, 0, SOURCE_PIXEL, r->ebx);
    port_set32(port, 0, target_pixel, target);
    r->edx -= r->eax;
}

/* The source pixel's alpha (top) byte. */
static uint32_t source_alpha(Port *port)
{
    return port_u32(port, port_u32(port, 0, SOURCE_PIXEL), 0) >> 24;
}

static uint32_t mask_row(Port *port, const LiftEntry *entry, int alpha, uint32_t target_pixel)
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
        mask_skip_step(port, &r, target_pixel);
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
        mask_draw_step(port, &r, target_pixel);
    }
    port_set32(port, 0, MASK_PIXEL, r.edx);
    return r.eax;
}

/* 0x492460's row with the target pixel at `target_pixel`. */
static uint32_t render_mask_row_at(PORT_SIGNATURE, uint32_t target_pixel)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
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
    eax = mask_row(&port, entry, 1, TARGET_PIXEL);
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

uint32_t vertrix_port_rectangle_half32(PORT_SIGNATURE)
{
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
    count = port_u16(&port, 0, COUNT);
    pixel = port_u32(&port, 0, PIXEL);
    color = port_u32(&port, 0, COLOR);
    width = port_u16(&port, 0, WIDTH);
    rows = port_u16(&port, 0, HEIGHT);
    /* Each pixel becomes half itself plus the colour (already halved). */
    for (; rows != 0; rows = (rows - 1) & 0xffff)
    {
        for (count = width; count != 0; count = (count - 1) & 0xffff)
        {
            eax = pixel;
            port_set32(&port, pixel, 0, ((port_u32(&port, pixel, 0) >> 1) & 0x7f7f7f) + color);
            pixel += 4;
        }
        eax = port_u32(&port, 0, PITCH_SKIP);
        pixel += eax;
    }
    port_set16(&port, 0, WIDTH, width);
    port_set16(&port, 0, HEIGHT, rows);
    port_set32(&port, 0, COLOR, color);
    port_set32(&port, 0, PIXEL, pixel);
    port_set16(&port, 0, COUNT, count);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_surface_mask32(PORT_SIGNATURE)
{
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
    port_set32(&port, ebp, -0xcu, (uint32_t)(int32_t)(int16_t)entry->eax);
    source = port_u32(&port, 0, SOURCE);
    /* The mask bytes at the position (0x478eb0 on the display's mask surface +0x274). */
    mask = port_call(&port, 0x478eb0, port_u32(&port, port_u32(&port, 0, DISPLAY), 0x274),
                     (uint32_t)(int32_t)(int16_t)entry->eax, (uint32_t)(int32_t)(int16_t)entry->edx,
                     source);
    pitch = port_u32(&port, 0, SOURCE_PITCH);
    port_set32(&port, ebp, -0x18u, pitch);
    port_set32(&port, ebp, -0xcu, (uint32_t)(int32_t)(int16_t)width);
    skip = port_u32(&port, port_u32(&port, port_u32(&port, 0, DISPLAY), 0x274), 4) -
           (uint32_t)(int32_t)(int16_t)width;
    port_set32(&port, ebp, -0x10u, skip);
    edx = skip;
    if ((rows & 0xffff) == 0)
    {
        return port_return(&port, mask, edx);
    }
    port_set32(&port, ebp, -0x14u, pitch << 2);
    /* Each source pixel with alpha sets bit 0 of its mask byte. */
    for (rows &= 0xffff; rows != 0; rows = (rows - 1) & 0xffff)
    {
        for (count = width & 0xffff; count != 0; count = (count - 1) & 0xffff)
        {
            uint32_t alpha = port_u32(&port, source, 0) >> 24;
            port_set32(&port, ebp, -0xcu, alpha);
            if (alpha != 0)
            {
                port_set8(&port, mask, 0, port_u8(&port, mask, 0) | 1);
            }
            source += 4;
            mask++;
        }
        edx = port_u32(&port, ebp, -0x14u);
        source += edx;
        mask += port_u32(&port, ebp, -0x10u);
    }
    return port_return(&port, mask, edx);
}

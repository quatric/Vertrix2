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
    KEY_SHIFT = 24,
    TARGET_PIXEL_16 = 0x5bb780,
    WIDE_TARGET = 0x5bb774
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

/* The sum of two colours with each channel saturating at 0xff (the raw sum goes to 0x54d624). */
static uint32_t add_saturated(Port *port, uint32_t first, uint32_t second)
{
    uint32_t sum = (first & LOW_BITS_CLEAR) + (second & LOW_BITS_CLEAR);
    uint32_t full = CARRIES - ((sum & CARRIES) >> 7);
    port_set32(port, 0, RAW_SUM, sum);
    return full | sum;
}

/* `first` less `second` with each channel stopping at 0 (the raw difference goes to 0x54d624). */
static uint32_t subtract_saturated(Port *port, uint32_t first, uint32_t second)
{
    uint32_t difference = (first & LOW_BITS_CLEAR) - (second & LOW_BITS_CLEAR);
    uint32_t keep = ((difference & CARRIES) >> 7) - 0x1010101;
    port_set32(port, 0, RAW_SUM, difference);
    return keep & difference;
}

/* Add `colour` to the target pixel at `target`, each channel saturating at 0xff. */
static void add_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t sum = add_saturated(port, port_u32(port, target, 0), colour);
    port_set32(port, target, 0, sum & CHANNELS);
}

/* Subtract `colour` from the target pixel at `target`, each channel stopping at 0. */
static void subtract_saturate(Port *port, uint32_t target, uint32_t colour)
{
    uint32_t difference = subtract_saturated(port, port_u32(port, target, 0), colour);
    port_set32(port, target, 0, difference & CHANNELS);
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

/* A colour remapped half way to the fixed channels (described at 0x48d8c0 in port_blend.h). */
static uint32_t half_tint(Port *port, uint32_t colour)
{
    uint32_t entry_value;
    uint32_t map;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    entry_value = port_u32(port, port_u32(port, 0, COLOUR_ENTRIES), entry_index(colour) * 4);
    port_set32(port, 0, ENTRY, entry_value);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (entry_value & 0xff) * 4);
    port_set32(port, 0, MAP, map);
    red = port_u8(port, map, ((entry_value >> 24) + port_u16(port, 0, TINT_RED)) >> 1);
    green = port_u8(port, map, (((entry_value >> 16) & 0xff) + port_u16(port, 0, TINT_GREEN)) >> 1);
    blue = port_u8(port, map, (((entry_value >> 8) & 0xff) + port_u16(port, 0, TINT_BLUE)) >> 1);
    return (red << 16) | (green << 8) | blue;
}

uint32_t vertrix_port_blend_half_tint(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_tint(&port, source_colour(&port));
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
static uint32_t levels_mix_values(Port *port, uint32_t source, uint32_t target)
{
    uint32_t source_levels = port_u32(port, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_u32(port, 0, TARGET_LEVELS);
    uint32_t red = port_u8(port, source_levels, (source >> 16) & 0xff) +
                   port_u8(port, target_levels, (target >> 16) & 0xff);
    uint32_t green = port_u8(port, source_levels, (source >> 8) & 0xff) +
                     port_u8(port, target_levels, (target >> 8) & 0xff);
    uint32_t blue =
        port_u8(port, source_levels, source & 0xff) + port_u8(port, target_levels, target & 0xff);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t levels_mix(Port *port, uint32_t source, uint32_t target)
{
    return levels_mix_values(port, port_u32(port, source, 0), port_u32(port, target, 0));
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

/* 0x492770's masked row drawn backwards, the target pixel at `target_pixel`: first the row start's
 * skipped part (pixels whose mask byte has bit 0 clear are drawn), then the row count's pixels;
 * each step moves the source back by a sampled step (0x5bb7dc, scaled by 0x5bb7c0), the target by
 * the stride and the mask by its stride. */
static uint32_t mask_row_back(PORT_SIGNATURE, uint32_t target_pixel)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    ecx = port_u32(&port, 0, MASK_PIXEL);
    for (;;)
    {
        uint32_t steps;
        uint32_t target;
        uint32_t start;
        eax = port_u32(&port, 0, ROW_START);
        if (port_u16(&port, eax, 0) == 0)
        {
            break;
        }
        edx = (edx & 0xffffff00u) | port_u8(&port, ecx, 0);
        port_set32(&port, 0, MASK_PIXEL, ecx);
        if ((edx & 1) == 0)
        {
            eax = port_call(&port, port_u32(&port, 0, PIXEL_OPERATION), eax, edx, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        steps = port_u32(&port, 0, SAMPLE_STEPS);
        edx = port_u8(&port, steps, 0) * port_u32(&port, 0, ROW_SCALE);
        target = port_u32(&port, 0, target_pixel);
        port_set32(&port, 0, SAMPLE_STEPS, steps - 1);
        target -= port_u32(&port, 0, TARGET_STRIDE);
        ebx = port_u32(&port, 0, SOURCE_PIXEL) - (edx << 2);
        edx <<= 2;
        ecx = port_u32(&port, 0, MASK_PIXEL) - high_word(&port, MASK_STRIDE);
        start = port_u32(&port, 0, ROW_START);
        port_set32(&port, 0, SOURCE_PIXEL, ebx);
        ebx = ((ebx & 0xffff0000u) | port_u16(&port, start, 0)) - 1;
        port_set32(&port, 0, target_pixel, target);
        port_set16(&port, start, 0, ebx);
    }
    while (port_u16(&port, 0, ROW_COUNT) != 0)
    {
        uint32_t steps;
        uint32_t count;
        port_set32(&port, 0, MASK_PIXEL, ecx);
        eax = port_call(&port, port_u32(&port, 0, PIXEL_OPERATION), eax, edx, ebx, ecx);
        steps = port_u32(&port, 0, SAMPLE_STEPS);
        edx = port_u8(&port, steps, 0) * port_u32(&port, 0, ROW_SCALE);
        ecx = port_u32(&port, 0, MASK_PIXEL);
        port_set32(&port, 0, SAMPLE_STEPS, steps - 1);
        eax = port_u32(&port, 0, SOURCE_PIXEL) - (edx << 2);
        count = port_u16(&port, 0, ROW_COUNT) - 1;
        port_set32(&port, 0, SOURCE_PIXEL, eax);
        edx = port_u32(&port, 0, target_pixel) - port_u32(&port, 0, TARGET_STRIDE);
        eax = high_word(&port, MASK_STRIDE);
        port_set16(&port, 0, ROW_COUNT, count);
        port_set32(&port, 0, target_pixel, edx);
        ecx -= eax;
    }
    port_set32(&port, 0, MASK_PIXEL, ecx);
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
    return levels_mix_values(port, colour, port_u32(port, target, 0));
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

/* A 16-bit pixel spread to eight bits a channel, 5-5-5 or, with six green bits, 5-6-5; and a colour
 * narrowed back the same way (0x4974c0 and 0x49f580). */
static uint32_t widen16(uint32_t pixel, int green6)
{
    if (green6)
    {
        return ((pixel & 0xf800) << 8) | ((pixel & 0x7e0) << 5) | ((pixel & 0x1f) << 3);
    }
    return ((pixel & 0x7c00) << 9) | ((pixel & 0x3e0) << 6) | ((pixel & 0x1f) << 3);
}

static uint32_t narrow16(uint32_t colour, int green6)
{
    if (green6)
    {
        return (((colour & 0xf80000) >> 5) | ((colour & 0xfc00) >> 2) | (colour & 0xf8)) >> 3;
    }
    return (((colour & 0xf80000) >> 6) | ((colour & 0xf800) >> 3) | (colour & 0xf8)) >> 3;
}

/* The 16-bit form of blend_levels: the target pixel at [0x5bb780] is widened into 0x5bb774, mixed
 * with the 32-bit source pixel by the two level tables, kept at 0x5bb774 and narrowed back. */
static uint32_t blend_levels16(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t mixed;
    port_open(&port, calls, services, globals, entry);
    target = port_u32(&port, 0, TARGET_PIXEL_16);
    mixed = levels_mix_values(&port, port_u32(&port, port_u32(&port, 0, SOURCE_PIXEL), 0),
                              widen16(port_u16(&port, target, 0), green6));
    port_set32(&port, 0, WIDE_TARGET, mixed);
    port_set16(&port, target, 0, narrow16(mixed, green6));
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
static uint32_t put16(Port *port, uint32_t colour, int green6)
{
    uint32_t pixel = narrow16(colour, green6);
    port_set16(port, port_u32(port, 0, TARGET_PIXEL_16), 0, pixel);
    return pixel;
}

/* A colour halved (each channel's low bit dropped) plus the colour at 0x54d5ec. */
static uint32_t half_plus(Port *port, uint32_t colour)
{
    return ((colour >> 1) & HALF) + port_u32(port, 0, ADDED_COLOUR);
}

static uint32_t pixel16_copy(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    pixel = put16(&port, source_colour(&port), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_invert(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = ~source_colour(&port);
    port_set32(&port, 0, WIDE_TARGET, colour & CHANNELS);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_invert_half_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = ~source_colour(&port) & CHANNELS;
    port_set32(&port, 0, REMAPPED, colour);
    colour = half_plus(&port, colour);
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
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
static uint32_t target16(Port *port, int green6)
{
    return widen16(port_u16(port, port_u32(port, 0, TARGET_PIXEL_16), 0), green6);
}

/* Keep a colour at 0x5bb774 and store it narrowed to the target pixel; the target's address. */
static uint32_t keep16(Port *port, uint32_t colour, int green6)
{
    port_set32(port, 0, WIDE_TARGET, colour);
    put16(port, colour, green6);
    return port_u32(port, 0, TARGET_PIXEL_16);
}

static uint32_t pixel16_average(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ((target16(&port, green6) >> 1) & HALF) + ((source_colour(&port) >> 1) & HALF);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_invert_target(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = ~target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, colour & CHANNELS);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_quarters_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ((source_colour(&port) >> 2) & 0x3f3f3f) + ((target16(&port, green6) >> 2) & 0x3f3f3f);
    colour += port_u32(&port, 0, ADDED_COLOUR);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_invert_target_half_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~target16(&port, green6) & CHANNELS;
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), green6), entry->edx);
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

static uint32_t pixel16_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

/* Keep the low 24 bits of a colour at 0x5bb774 and store it narrowed; the target's address. */
static uint32_t keep16_channels(Port *port, uint32_t colour, int green6)
{
    port_set32(port, 0, WIDE_TARGET, colour & CHANNELS);
    put16(port, colour, green6);
    return port_u32(port, 0, TARGET_PIXEL_16);
}

static uint32_t pixel16_add(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = add_saturated(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16_channels(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_subtract(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = subtract_saturated(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16_channels(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_subtract_from(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = subtract_saturated(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16_channels(&port, colour, green6), entry->edx);
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
static uint32_t put16_channels(Port *port, uint32_t colour, int green6)
{
    port_set32(port, 0, WIDE_TARGET, colour & CHANNELS);
    return put16(port, colour, green6);
}

static uint32_t pixel16_half_plus_add(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = add_saturated(&port, target16(&port, green6), colour);
    pixel = put16_channels(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_subtract(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = subtract_saturated(&port, target16(&port, green6), colour);
    pixel = put16_channels(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_subtract_from(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = subtract_saturated(&port, colour, target16(&port, green6));
    pixel = put16_channels(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
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

static uint32_t pixel16_invert_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~source_colour(&port);
    port_set32(&port, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, remap_tint(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_half_plus_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, half_plus(&port, source_colour(&port)));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

enum
{
    FIXED_ENTRIES = 0x54cdcc,
    FIXED_ENTRY = 0x54d5f0
};

static uint32_t pixel16_fixed_entry(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t select;
    uint32_t map;
    uint32_t fixed;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    select =
        port_u8(&port, port_u32(&port, 0, COLOUR_ENTRIES), entry_index(source_colour(&port)) * 4);
    map = port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), select * 4);
    port_set32(&port, 0, MAP, map);
    fixed = port_u32(&port, port_u32(&port, 0, FIXED_ENTRIES), port_u8(&port, 0, FIXED_ENTRY) * 4);
    fixed = port_u32(&port, fixed, 0);
    port_set32(&port, 0, ENTRY, fixed);
    colour = port_u8(&port, map, fixed >> 24) << 16;
    colour |= port_u8(&port, map, (fixed >> 16) & 0xff) << 8;
    colour |= port_u8(&port, map, (fixed >> 8) & 0xff);
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
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

static uint32_t pixel16_remap_invert(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, ~colour & CHANNELS);
    put16(&port, ~colour, green6);
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
}

enum
{
    ENTRY_INDEX = 0x54d5e4,
    FIXED_SELECTS = 0x54b804
};

/* A colour remapped through its entry index twice (described at 0x498470 in port_blend.h). */
static uint32_t paired_remap(Port *port, uint32_t colour)
{
    uint32_t index = entry_index(colour);
    uint32_t map;
    uint32_t fixed;
    port_set32(port, 0, ENTRY_INDEX, index);
    map = port_u8(port, port_u32(port, 0, COLOUR_ENTRIES), index * 4);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), map * 4);
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), index);
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    colour = port_u8(port, map, fixed >> 24) << 16;
    colour |= port_u8(port, map, (fixed >> 16) & 0xff) << 8;
    return colour | port_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_paired_entry(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_tint(&port, source_colour(&port));
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
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

static uint32_t pixel16_invert_target_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~target16(&port, green6);
    port_set32(&port, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, remap_tint(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_half_plus_paired(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = paired_remap(&port, colour);
    port_set32(&port, 0, WIDE_TARGET, colour);
    pixel = put16(&port, colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_paired_invert(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, ~colour, green6);
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

static uint32_t pixel16_tint_average(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), green6), entry->edx);
}

static uint32_t pixel16_invert_half_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~source_colour(&port);
    port_set32(&port, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, half_tint(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_invert_half_plus_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, ~source_colour(&port) & CHANNELS);
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, remap(&port, colour), green6), entry->edx);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t select = port_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    port_set32(port, 0, MAP, map);
    port_set32(port, 0, ENTRY, port_u32(port, entries, entry_index(entry_colour) * 4));
    return (port_u8(port, map, port_u16(port, 0, TINT_RED)) << 16) |
           (port_u8(port, map, port_u16(port, 0, TINT_GREEN)) << 8) |
           port_u8(port, map, port_u16(port, 0, TINT_BLUE));
}

static uint32_t pixel16_tint_add(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, add_saturated(&port, target, colour), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_tint_subtract(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, target, colour), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_tint_subtract_from(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, colour, target), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_target_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_tint(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t select = port_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    uint32_t value;
    port_set32(port, 0, MAP, map);
    value = port_u32(port, entries, entry_index(entry_colour) * 4);
    port_set32(port, 0, ENTRY, value);
    return (port_u8(port, map, value >> 24) << 16) |
           (port_u8(port, map, (value >> 16) & 0xff) << 8) |
           port_u8(port, map, (value >> 8) & 0xff);
}

static uint32_t pixel16_cross_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_remap(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_average_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, average(target16(&port, green6), source_colour(&port)));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_remap_average(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), green6), entry->edx);
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

static uint32_t pixel16_target_remap_invert(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, target16(&port, green6));
    port_set32(&port, 0, REMAPPED, colour);
    port_set32(&port, 0, WIDE_TARGET, ~colour & CHANNELS);
    put16(&port, ~colour, green6);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
}

static uint32_t pixel16_mean_map_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t entries;
    uint32_t select;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    select = port_u8(&port, entries, entry_index(source_colour(&port)) * 4);
    select += port_u8(&port, entries, entry_index(target16(&port, green6)) * 4);
    map = port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (select >> 1) * 4);
    port_set32(&port, 0, MAP, map);
    colour = (port_u8(&port, map, port_u16(&port, 0, TINT_RED)) << 16) |
             (port_u8(&port, map, port_u16(&port, 0, TINT_GREEN)) << 8) |
             port_u8(&port, map, port_u16(&port, 0, TINT_BLUE));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_source_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_tint(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

static uint32_t pixel16_levels_bias(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t source;
    uint32_t source_levels;
    uint32_t target_levels;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    source = source_colour(&port);
    source_levels = port_u32(&port, 0, SOURCE_LEVELS);
    target_levels = port_u32(&port, 0, TARGET_LEVELS);
    red = port_u8(&port, source_levels, (source >> 16) & 0xff) +
          port_u8(&port, target_levels, (target >> 16) & 0xff) + port_u8(&port, 0, LEVEL_BIAS);
    green = port_u8(&port, source_levels, (source >> 8) & 0xff) +
            port_u8(&port, target_levels, (target >> 8) & 0xff) + port_u8(&port, 0, LEVEL_BIAS + 1);
    blue = port_u8(&port, source_levels, source & 0xff) +
           port_u8(&port, target_levels, target & 0xff) + port_u8(&port, 0, LEVEL_BIAS + 2);
    target = ((red >> 1) << 16) | ((green >> 1) << 8) | (blue >> 1);
    return port_return(&port, keep16(&port, target, green6), entry->edx);
}

static uint32_t pixel16_target_paired_invert(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, target16(&port, green6));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, ~colour, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_target_cross_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_remap(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

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

/* The map `colour`'s entry selects (stored at 0x54d5d0) applied to the bytes 3, 2 and 1 of the
 * dword the pointer at entry [0x54d5f0] of the table at [0x54cdcc] points to (stored at 0x54d5d4).
 */
static uint32_t fixed_entry_remap(Port *port, uint32_t colour)
{
    uint32_t select = port_u8(port, port_u32(port, 0, COLOUR_ENTRIES), entry_index(colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    uint32_t fixed;
    port_set32(port, 0, MAP, map);
    fixed = port_u32(port, port_u32(port, 0, FIXED_ENTRIES), port_u8(port, 0, FIXED_ENTRY) * 4);
    fixed = port_u32(port, fixed, 0);
    port_set32(port, 0, ENTRY, fixed);
    return (port_u8(port, map, fixed >> 24) << 16) |
           (port_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           port_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_fixed_entry(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_remap(&port, source_colour(&port));
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

/* Each channel half the sum of the source's level, the target's level and the channel's byte at
 * 0x54d5e8, 0x54d5e9 or 0x54d5ea (the halves or-ed into place). */
static uint32_t levels_bias_values(Port *port, uint32_t source, uint32_t target)
{
    uint32_t source_levels = port_u32(port, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_u32(port, 0, TARGET_LEVELS);
    uint32_t red = port_u8(port, source_levels, (source >> 16) & 0xff) +
                   port_u8(port, target_levels, (target >> 16) & 0xff) +
                   port_u8(port, 0, LEVEL_BIAS);
    uint32_t green = port_u8(port, source_levels, (source >> 8) & 0xff) +
                     port_u8(port, target_levels, (target >> 8) & 0xff) +
                     port_u8(port, 0, LEVEL_BIAS + 1);
    uint32_t blue = port_u8(port, source_levels, source & 0xff) +
                    port_u8(port, target_levels, target & 0xff) + port_u8(port, 0, LEVEL_BIAS + 2);
    return ((red >> 1) << 16) | ((green >> 1) << 8) | (blue >> 1);
}

static uint32_t pixel16_levels_bias(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = levels_bias_values(&port, source_colour(&port), port_u32(&port, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

static uint32_t pixel16_remap_add(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, add_saturated(&port, target, colour), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap_subtract(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, target, colour), green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_remap_subtract_from(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    pixel = put16_channels(&port, subtract_saturated(&port, colour, target), green6);
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

static uint32_t pixel16_invert_target_half_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~target16(&port, green6);
    port_set32(&port, 0, REMAPPED, colour & CHANNELS);
    return port_return(&port, keep16(&port, half_tint(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_quarters_plus_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ((target16(&port, green6) >> 2) & 0x3f3f3f) + ((source_colour(&port) >> 2) & 0x3f3f3f);
    colour = remap(&port, colour + port_u32(&port, 0, ADDED_COLOUR));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_invert_target_half_plus_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, ~target16(&port, green6) & CHANNELS);
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, remap(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_shade_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t entries;
    uint32_t level;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    level = port_u8(&port, entries, entry_index(source_colour(&port)) * 4);
    level = port_u16(&port, port_u32(&port, 0, SHADE_LEVELS), level * 2);
    level += port_u16(&port, port_u32(&port, 0, SHADE_STEPS),
                      port_u8(&port, entries, entry_index(target16(&port, green6)) * 4) * 2);
    map =
        port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (uint32_t)((int32_t)(int16_t)level * 4));
    port_set32(&port, 0, MAP, map);
    colour = (port_u8(&port, map, port_u16(&port, 0, TINT_RED)) << 16) |
             (port_u8(&port, map, port_u16(&port, 0, TINT_GREEN)) << 8) |
             port_u8(&port, map, port_u16(&port, 0, TINT_BLUE));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

static uint32_t pixel16_mean_map_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t entries;
    uint32_t value;
    uint32_t select;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    value = port_u32(&port, entries, entry_index(source_colour(&port)) * 4);
    port_set32(&port, 0, ENTRY, value);
    select = port_u8(&port, entries, entry_index(target16(&port, green6)) * 4);
    map = port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (((value & 0xff) + select) >> 1) * 4);
    port_set32(&port, 0, MAP, map);
    colour = (port_u8(&port, map, value >> 24) << 16) |
             (port_u8(&port, map, (value >> 16) & 0xff) << 8) |
             port_u8(&port, map, (value >> 8) & 0xff);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_cross_remap_half_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_remap(&port, source_colour(&port), target16(&port, green6));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_target_cross_remap_half_plus(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_remap(&port, target16(&port, green6), source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, half_plus(&port, colour), green6), entry->edx);
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
static uint32_t mix16(Port *port, uint32_t target, uint32_t colour, int mix, int green6)
{
    port_set32(port, 0, REMAPPED, colour);
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
    return put16_channels(port, colour, green6);
}

static uint32_t half_plus_remap_mix(PORT_SIGNATURE, int mix, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = remap(&port, half_plus(&port, source_colour(&port)));
    pixel = mix16(&port, target, colour, mix, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t paired_mix(PORT_SIGNATURE, int mix, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = paired_remap(&port, source_colour(&port));
    pixel = mix16(&port, target, colour, mix, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_plus_remap_subtract(PORT_SIGNATURE, int green6)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_SUBTRACT, green6);
}

static uint32_t pixel16_half_plus_remap_subtract_from(PORT_SIGNATURE, int green6)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, green6);
}

static uint32_t pixel16_paired_subtract(PORT_SIGNATURE, int green6)
{
    return paired_mix(calls, services, globals, entry, MIX_SUBTRACT, green6);
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

static uint32_t pixel16_paired_subtract_from(PORT_SIGNATURE, int green6)
{
    return paired_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, green6);
}

/* paired_remap with the map selected by the entry of `map_colour` and the dword picked through the
 * entry index of `fixed_colour`; the entry index is not stored. */
static uint32_t paired_cross(Port *port, uint32_t map_colour, uint32_t fixed_colour)
{
    uint32_t map = port_u8(port, port_u32(port, 0, COLOUR_ENTRIES), entry_index(map_colour) * 4);
    uint32_t fixed;
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), map * 4);
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), entry_index(fixed_colour));
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    return (port_u8(port, map, fixed >> 24) << 16) |
           (port_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           port_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_paired_cross(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_cross(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_target_paired_cross(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_cross(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t select = port_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    uint32_t value;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    port_set32(port, 0, MAP, map);
    value = port_u32(port, entries, entry_index(entry_colour) * 4);
    port_set32(port, 0, ENTRY, value);
    red = port_u8(port, map, ((value >> 24) + port_u16(port, 0, TINT_RED)) >> 1);
    green = port_u8(port, map, (((value >> 16) & 0xff) + port_u16(port, 0, TINT_GREEN)) >> 1);
    blue = port_u8(port, map, (((value >> 8) & 0xff) + port_u16(port, 0, TINT_BLUE)) >> 1);
    return (red << 16) | (green << 8) | blue;
}

static uint32_t pixel16_cross_half_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_half_tint(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_target_cross_half_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_half_tint(&port, target16(&port, green6), source_colour(&port));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_half_plus_remap_add(PORT_SIGNATURE, int green6)
{
    return half_plus_remap_mix(calls, services, globals, entry, MIX_ADD, green6);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t index = entry_index(source);
    uint32_t value = port_u32(port, entries, index * 4);
    uint32_t select;
    uint32_t map;
    uint32_t fixed;
    port_set32(port, 0, ENTRY, value);
    select = port_u8(port, entries, entry_index(target) * 4);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), ((select + (value & 0xff)) >> 1) * 4);
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), index);
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    port_set32(port, 0, ENTRY_INDEX, index);
    return (port_u8(port, map, fixed >> 24) << 16) |
           (port_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           port_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_mean_map_paired(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = mean_map_paired(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_average_paired(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = average(target16(&port, green6), source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, paired_remap(&port, colour), green6), entry->edx);
}

static uint32_t pixel16_paired_average(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, keep16(&port, average(target, colour), green6), entry->edx);
}

static uint32_t pixel16_paired_add(PORT_SIGNATURE, int green6)
{
    return paired_mix(calls, services, globals, entry, MIX_ADD, green6);
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

static uint32_t pixel16_shade(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t entries;
    uint32_t value;
    uint32_t level;
    uint32_t map;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    entries = port_u32(&port, 0, COLOUR_ENTRIES);
    value = port_u32(&port, entries, entry_index(source_colour(&port)) * 4);
    port_set32(&port, 0, ENTRY, value);
    level = port_u8(&port, entries, entry_index(target16(&port, green6)) * 4);
    level = port_u16(&port, port_u32(&port, 0, SHADE_LEVELS), (value & 0xff) * 2) +
            port_u16(&port, port_u32(&port, 0, SHADE_STEPS), level * 2);
    map =
        port_u32(&port, port_u32(&port, 0, CHANNEL_MAPS), (uint32_t)((int32_t)(int16_t)level * 4));
    port_set32(&port, 0, MAP, map);
    colour = (port_u8(&port, map, value >> 24) << 16) |
             (port_u8(&port, map, (value >> 16) & 0xff) << 8) |
             port_u8(&port, map, (value >> 8) & 0xff);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t half_tint_mix(PORT_SIGNATURE, int mix, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    uint32_t pixel;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    colour = half_tint(&port, source_colour(&port));
    pixel = mix16(&port, target, colour, mix, green6);
    return port_return(&port, pixel, entry->edx);
}

static uint32_t pixel16_half_tint_add(PORT_SIGNATURE, int green6)
{
    return half_tint_mix(calls, services, globals, entry, MIX_ADD, green6);
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

static uint32_t pixel16_half_tint_subtract(PORT_SIGNATURE, int green6)
{
    return half_tint_mix(calls, services, globals, entry, MIX_SUBTRACT, green6);
}

static uint32_t pixel16_half_tint_subtract_from(PORT_SIGNATURE, int green6)
{
    return half_tint_mix(calls, services, globals, entry, MIX_SUBTRACT_FROM, green6);
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

static uint32_t pixel16_tint_levels(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = remap_tint(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = levels_mix_values(&port, colour, port_u32(&port, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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
    entries = port_u32(port, 0, COLOUR_ENTRIES);
    index = entry_index(source);
    value = port_u32(port, entries, index * 4);
    port_set32(port, 0, ENTRY, value);
    level = port_u8(port, entries, entry_index(target) * 4);
    level = port_u16(port, port_u32(port, 0, SHADE_LEVELS), (value & 0xff) * 2) +
            port_u16(port, port_u32(port, 0, SHADE_STEPS), level * 2);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (uint32_t)((int32_t)(int16_t)level * 4));
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), index);
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    colour = (port_u8(port, map, fixed >> 24) << 16) |
             (port_u8(port, map, (fixed >> 16) & 0xff) << 8) |
             port_u8(port, map, (fixed >> 8) & 0xff);
    port_set32(port, 0, ENTRY_INDEX, index);
    return colour;
}

static uint32_t pixel16_shade_paired(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = shade_paired(&port, source_colour(&port), target16(&port, green6));
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t value = port_u32(port, entries, entry_index(source_colour(port)) * 4);
    uint32_t map;
    port_set32(port, 0, ENTRY, value);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_set32(port, 0, MAP, map);
    *other = port_u32(port, entries, entry_index(target) * 4);
    port_set32(port, 0, TARGET_ENTRY, *other);
    return map;
}

static uint32_t pixel16_entry_mean(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t value;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target16(&port, green6), &other);
    value = port_u32(&port, 0, ENTRY);
    colour = port_u8(&port, map, ((value >> 24) + (other >> 24)) >> 1) << 16;
    colour |= port_u8(&port, map, (((value >> 16) & 0xff) + ((other >> 16) & 0xff)) >> 1) << 8;
    colour |= port_u8(&port, map, (((value >> 8) & 0xff) + ((other >> 8) & 0xff)) >> 1);
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
}

/* `colour` remapped half way to the fixed channels; the map used is applied again to the dword
 * picked as paired_remap picks it from that colour's entry index (stored at 0x54d5d4). */
static uint32_t half_tint_fixed(Port *port, uint32_t colour)
{
    uint32_t map;
    uint32_t fixed;
    colour = half_tint(port, colour);
    map = port_u32(port, 0, MAP);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), entry_index(colour));
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    return (port_u8(port, map, fixed >> 24) << 16) |
           (port_u8(port, map, (fixed >> 16) & 0xff) << 8) |
           port_u8(port, map, (fixed >> 8) & 0xff);
}

static uint32_t pixel16_half_tint_fixed(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_tint_fixed(&port, source_colour(&port));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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
    uint32_t colour = port_u8(port, map, (red + port_u16(port, 0, TINT_RED)) >> 1) << 16;
    colour |= port_u8(port, map, (green + port_u16(port, 0, TINT_GREEN)) >> 1) << 8;
    return colour | port_u8(port, map, (blue + port_u16(port, 0, TINT_BLUE)) >> 1);
}

static uint32_t pixel16_entry_mean_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target16(&port, green6), &other);
    colour = entry_mean_tint(&port, map, port_u32(&port, 0, ENTRY), other);
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
}

static uint32_t pixel16_levels_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = levels_mix_values(&port, source_colour(&port), port_u32(&port, 0, WIDE_TARGET));
    colour = remap(&port, colour);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

static uint32_t pixel16_remap_levels(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = levels_mix_values(&port, colour, port_u32(&port, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

/* The map of the source's colour entry (the entry stored at 0x54d5d4 first, the map at 0x54d5d0)
 * applied to the means of the bytes 3, 2 and 1 of the dword picked as paired_remap picks it
 * (stored at 0x54d5d4; the index at 0x54d5e4) and of the target's entry (stored at 0x54d5d8). */
static uint32_t fixed_entry_mean(Port *port, uint32_t source, uint32_t target)
{
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t index = entry_index(source);
    uint32_t value = port_u32(port, entries, index * 4);
    uint32_t map;
    uint32_t fixed;
    uint32_t other;
    uint32_t colour;
    port_set32(port, 0, ENTRY, value);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), index);
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    other = port_u32(port, entries, entry_index(target) * 4);
    port_set32(port, 0, TARGET_ENTRY, other);
    colour = port_u8(port, map, ((fixed >> 24) + (other >> 24)) >> 1) << 16;
    colour |= port_u8(port, map, (((fixed >> 16) & 0xff) + ((other >> 16) & 0xff)) >> 1) << 8;
    colour |= port_u8(port, map, (((fixed >> 8) & 0xff) + ((other >> 8) & 0xff)) >> 1);
    port_set32(port, 0, ENTRY_INDEX, index);
    return colour;
}

static uint32_t pixel16_fixed_entry_mean(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_mean(&port, source_colour(&port), target16(&port, green6));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t select = port_u8(port, entries, entry_index(map_colour) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), select * 4);
    uint32_t value = port_u32(port, entries, entry_index(entry_colour) * 4);
    port_set32(port, 0, ENTRY, value);
    return (port_u8(port, map, value >> 24) << 16) |
           (port_u8(port, map, (value >> 16) & 0xff) << 8) |
           port_u8(port, map, (value >> 8) & 0xff);
}

static uint32_t cross_half_plus_remap(PORT_SIGNATURE, int target_map, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    if (target_map)
    {
        colour = cross_remap_unstored(&port, target, source_colour(&port));
    }
    else
    {
        colour = cross_remap_unstored(&port, source_colour(&port), target);
    }
    colour = half_plus(&port, colour);
    keep16(&port, remap(&port, colour), green6);
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
}

static uint32_t pixel16_cross_half_plus_remap(PORT_SIGNATURE, int green6)
{
    return cross_half_plus_remap(calls, services, globals, entry, 0, green6);
}

static uint32_t pixel16_target_cross_half_plus_remap(PORT_SIGNATURE, int green6)
{
    return cross_half_plus_remap(calls, services, globals, entry, 1, green6);
}

static uint32_t pixel16_entry_levels(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t value;
    uint32_t map;
    uint32_t other;
    uint32_t source_levels;
    uint32_t target_levels;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target16(&port, green6), &other);
    value = port_u32(&port, 0, ENTRY);
    source_levels = port_u32(&port, 0, SOURCE_LEVELS);
    target_levels = port_u32(&port, 0, TARGET_LEVELS);
    colour = port_u8(&port, map,
                     port_u8(&port, source_levels, value >> 24) +
                         port_u8(&port, target_levels, other >> 24))
             << 16;
    colour |= port_u8(&port, map,
                      port_u8(&port, source_levels, (value >> 16) & 0xff) +
                          port_u8(&port, target_levels, (other >> 16) & 0xff))
              << 8;
    colour |= port_u8(&port, map,
                      port_u8(&port, source_levels, (value >> 8) & 0xff) +
                          port_u8(&port, target_levels, (other >> 8) & 0xff));
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
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

static uint32_t pixel16_levels_paired(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = levels_mix_values(&port, source_colour(&port), port_u32(&port, 0, WIDE_TARGET));
    port_set32(&port, 0, WIDE_TARGET, colour);
    colour = paired_remap(&port, colour);
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
}

static uint32_t pixel16_paired_levels(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = levels_mix_values(&port, colour, port_u32(&port, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, colour, green6), entry->edx);
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

static uint32_t pixel16_levels_bias_remap(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t target;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    target = target16(&port, green6);
    port_set32(&port, 0, WIDE_TARGET, target);
    colour = levels_bias_values(&port, source_colour(&port), port_u32(&port, 0, WIDE_TARGET));
    return port_return(&port, keep16(&port, remap(&port, colour), green6), entry->edx);
}

/* The map applied to the level sums of the entries' bytes 3, 2 and 1 (the source's through
 * [0x55f1f0], the target's through [0x55f1f4]) each meaned with the fixed channel. */
static uint32_t entry_levels_tint(Port *port, uint32_t map, uint32_t value, uint32_t other)
{
    uint32_t source_levels = port_u32(port, 0, SOURCE_LEVELS);
    uint32_t target_levels = port_u32(port, 0, TARGET_LEVELS);
    uint32_t red =
        port_u8(port, source_levels, value >> 24) + port_u8(port, target_levels, other >> 24);
    uint32_t green = port_u8(port, source_levels, (value >> 16) & 0xff) +
                     port_u8(port, target_levels, (other >> 16) & 0xff);
    uint32_t blue = port_u8(port, source_levels, (value >> 8) & 0xff) +
                    port_u8(port, target_levels, (other >> 8) & 0xff);
    uint32_t colour = port_u8(port, map, (red + port_u16(port, 0, TINT_RED)) >> 1) << 16;
    colour |= port_u8(port, map, (green + port_u16(port, 0, TINT_GREEN)) >> 1) << 8;
    return colour | port_u8(port, map, (blue + port_u16(port, 0, TINT_BLUE)) >> 1);
}

static uint32_t pixel16_entry_levels_tint(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target16(&port, green6), &other);
    colour = entry_levels_tint(&port, map, port_u32(&port, 0, ENTRY), other);
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
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
    entries = port_u32(port, 0, COLOUR_ENTRIES);
    index = entry_index(source);
    port_set32(port, 0, ENTRY_INDEX, index);
    value = port_u32(port, entries, index * 4);
    port_set32(port, 0, ENTRY, value);
    map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (value & 0xff) * 4);
    port_set32(port, 0, MAP, map);
    fixed = port_u8(port, port_u32(port, 0, FIXED_SELECTS), index);
    fixed = port_u32(port, port_u32(port, port_u32(port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(port, 0, ENTRY, fixed);
    other = port_u32(port, entries, entry_index(target) * 4);
    port_set32(port, 0, TARGET_ENTRY, other);
    source_levels = port_u32(port, 0, SOURCE_LEVELS);
    target_levels = port_u32(port, 0, TARGET_LEVELS);
    colour = port_u8(port, map,
                     port_u8(port, source_levels, fixed >> 24) +
                         port_u8(port, target_levels, other >> 24))
             << 16;
    colour |= port_u8(port, map,
                      port_u8(port, source_levels, (fixed >> 16) & 0xff) +
                          port_u8(port, target_levels, (other >> 16) & 0xff))
              << 8;
    colour |= port_u8(port, map,
                      port_u8(port, source_levels, (fixed >> 8) & 0xff) +
                          port_u8(port, target_levels, (other >> 8) & 0xff));
    return colour;
}

static uint32_t pixel16_fixed_entry_levels(PORT_SIGNATURE, int green6)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_levels(&port, source_colour(&port), target16(&port, green6));
    put16(&port, colour, green6);
    port_set32(&port, 0, WIDE_TARGET, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL_16), entry->edx);
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
    return port_u32(port, port_u32(port, 0, TARGET_PIXEL), 0);
}

static uint32_t put32(Port *port, uint32_t colour)
{
    uint32_t target = port_u32(port, 0, TARGET_PIXEL);
    port_set32(port, target, 0, colour);
    return target;
}

uint32_t vertrix_port_blend_subtract_from(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = subtract_saturated(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour & CHANNELS), entry->edx);
}

uint32_t vertrix_port_blend_invert(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ~source_colour(&port) & CHANNELS;
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_invert_target(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, put32(&port, ~target32(&port) & CHANNELS), entry->edx);
}

uint32_t vertrix_port_blend_half_plus(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    put32(&port, colour);
    colour = remap(&port, target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_target_cross_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = cross_remap(&port, target32(&port), source_colour(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_remap_average(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = average(target32(&port), colour);
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_remap_subtract_from(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = subtract_saturated(&port, colour, target32(&port));
    return port_return(&port, put32(&port, colour & CHANNELS), entry->edx);
}

uint32_t vertrix_port_blend_remap_invert(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    put32(&port, ~colour & CHANNELS);
    return port_return(&port, ~colour & CHANNELS, entry->edx);
}

uint32_t vertrix_port_blend_target_remap_invert(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = remap(&port, target32(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, put32(&port, ~colour & CHANNELS), entry->edx);
}

/* The fixed channels through the map numbered by the mean of two colours' entry bytes (the map
 * stored at 0x54d5d0). */
static uint32_t mean_map_tint(Port *port, uint32_t first, uint32_t second)
{
    uint32_t entries = port_u32(port, 0, COLOUR_ENTRIES);
    uint32_t select = port_u8(port, entries, entry_index(first) * 4) +
                      port_u8(port, entries, entry_index(second) * 4);
    uint32_t map = port_u32(port, port_u32(port, 0, CHANNEL_MAPS), (select >> 1) * 4);
    port_set32(port, 0, MAP, map);
    return (port_u8(port, map, port_u16(port, 0, TINT_RED)) << 16) |
           (port_u8(port, map, port_u16(port, 0, TINT_GREEN)) << 8) |
           port_u8(port, map, port_u16(port, 0, TINT_BLUE));
}

uint32_t vertrix_port_blend_mean_map_tint(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = mean_map_tint(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_quarters_plus(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ((source_colour(&port) >> 2) & 0x3f3f3f) + ((target32(&port) >> 2) & 0x3f3f3f);
    colour += port_u32(&port, 0, ADDED_COLOUR);
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_entry_mean_tint(PORT_SIGNATURE)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target32(&port), &other);
    colour = entry_mean_tint(&port, map, port_u32(&port, 0, ENTRY), other);
    return port_return(&port, put32(&port, colour), entry->edx);
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
    colour = made_from(&port, source_colour(&port), kind);
    port_set32(&port, 0, REMAPPED, colour);
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
    colour = ~(of_target ? target32(&port) : source_colour(&port)) & CHANNELS;
    port_set32(&port, 0, REMAPPED, colour);
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
        port_set32(&port, 0, REMAPPED, colour);
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

uint32_t vertrix_port_blend_quarters_plus_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = ((source_colour(&port) >> 2) & 0x3f3f3f) + ((target32(&port) >> 2) & 0x3f3f3f);
    put32(&port, colour + port_u32(&port, 0, ADDED_COLOUR));
    colour = remap(&port, target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
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

uint32_t vertrix_port_blend_invert_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, ~source_colour(&port) & CHANNELS);
    port_set32(&port, 0, REMAPPED, colour);
    colour = remap(&port, colour);
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_invert_target_half_plus_remap(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, ~target32(&port) & CHANNELS);
    port_set32(&port, 0, REMAPPED, colour);
    colour = remap(&port, colour);
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

static uint32_t cross_half_plus_remap32(PORT_SIGNATURE, int target_map)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
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
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, port_u32(&port, 0, TARGET_PIXEL), entry->edx);
}

uint32_t vertrix_port_blend_cross_half_plus_remap(PORT_SIGNATURE)
{
    return cross_half_plus_remap32(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_blend_target_cross_half_plus_remap(PORT_SIGNATURE)
{
    return cross_half_plus_remap32(calls, services, globals, entry, 1);
}

uint32_t vertrix_port_blend_levels_bias(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = levels_bias_values(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_entry_levels_tint(PORT_SIGNATURE)
{
    Port port;
    uint32_t map;
    uint32_t other;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    map = entry_pair(&port, target32(&port), &other);
    colour = entry_levels_tint(&port, map, port_u32(&port, 0, ENTRY), other);
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_fixed_entry(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_remap(&port, source_colour(&port));
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_half_plus_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = half_plus(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, put32(&port, paired_remap(&port, colour)), entry->edx);
}

uint32_t vertrix_port_blend_half_tint_fixed(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    uint32_t map;
    uint32_t fixed;
    port_open(&port, calls, services, globals, entry);
    colour = half_tint(&port, source_colour(&port));
    map = port_u32(&port, 0, MAP);
    target = put32(&port, colour);
    /* The entry index is taken from the stored pixel but for its red bits. */
    colour = (colour & 0xfc0000) | (port_u32(&port, target, 0) & 0xfcfc);
    fixed = port_u8(&port, port_u32(&port, 0, FIXED_SELECTS), entry_index(colour));
    fixed = port_u32(&port, port_u32(&port, port_u32(&port, 0, FIXED_ENTRIES), fixed * 4), 0);
    port_set32(&port, 0, ENTRY, fixed);
    colour = (port_u8(&port, map, fixed >> 24) << 16) |
             (port_u8(&port, map, (fixed >> 16) & 0xff) << 8) |
             port_u8(&port, map, (fixed >> 8) & 0xff);
    port_set32(&port, target, 0, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_mean_map_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = mean_map_paired(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_average_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = average(source_colour(&port), target32(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = paired_remap(&port, colour);
    put32(&port, colour);
    return port_return(&port, colour, entry->edx);
}

uint32_t vertrix_port_blend_fixed_entry_mean(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_mean(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_paired_average(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, put32(&port, average(target32(&port), colour)), entry->edx);
}

uint32_t vertrix_port_blend_paired_subtract(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_PAIRED, MIX_SUBTRACT);
}

uint32_t vertrix_port_blend_paired_subtract_from(PORT_SIGNATURE)
{
    return made_mix32(calls, services, globals, entry, COLOUR_PAIRED, MIX_SUBTRACT_FROM);
}

uint32_t vertrix_port_blend_paired_invert(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    put32(&port, ~colour & CHANNELS);
    return port_return(&port, ~colour & CHANNELS, entry->edx);
}

uint32_t vertrix_port_blend_target_paired_invert(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, target32(&port));
    port_set32(&port, 0, REMAPPED, colour);
    return port_return(&port, put32(&port, ~colour & CHANNELS), entry->edx);
}

uint32_t vertrix_port_blend_paired_cross(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_cross(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_target_paired_cross(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_cross(&port, target32(&port), source_colour(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_shade_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = shade_paired(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_levels_paired(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    uint32_t target;
    port_open(&port, calls, services, globals, entry);
    colour = levels_mix_values(&port, source_colour(&port), target32(&port));
    target = put32(&port, colour);
    /* The entry index is taken from the stored pixel for its blue bits. */
    colour = (colour & 0xfcfc00) | (port_u32(&port, target, 0) & 0xfc);
    port_set32(&port, target, 0, paired_remap(&port, colour));
    return port_return(&port, target, entry->edx);
}

uint32_t vertrix_port_blend_fixed_entry_levels(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = fixed_entry_levels(&port, source_colour(&port), target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
}

uint32_t vertrix_port_blend_paired_levels(PORT_SIGNATURE)
{
    Port port;
    uint32_t colour;
    port_open(&port, calls, services, globals, entry);
    colour = paired_remap(&port, source_colour(&port));
    port_set32(&port, 0, REMAPPED, colour);
    colour = levels_mix_values(&port, colour, target32(&port));
    return port_return(&port, put32(&port, colour), entry->edx);
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
    rows = (uint32_t)((int32_t)port_u32(&port, 0, ROWS) >> 16);
    last = rows - 1;
    port_set32(&port, 0, ROW_INDEX, port_u32(&port, 0, ROW_INDEX) + rows - 2);
    source = port_u32(&port, 0, SOURCE_PIXEL) +
             ((port_u16(&port, 0, FIRST_ROW) * port_u32(&port, 0, ROW_SCALE)) << 2);
    port_set32(&port, 0, row_global,
               port_u32(&port, 0, row_global) + port_u32(&port, 0, TARGET_STRIDE) * last);
    port_set32(&port, 0, SOURCE_PIXEL, source);
    port_set32(&port, 0, MASK_ROW,
               port_u32(&port, 0, MASK_ROW) +
                   last * (uint32_t)((int32_t)port_u32(&port, 0, MASK_STRIDE) >> 16));
    do
    {
        uint32_t steps;
        uint32_t target;
        uint32_t mask;
        count = port_u16(&port, 0, WIDTH) - port_u16(&port, start, 0);
        port_set32(&port, 0, ROW_START, start);
        port_set16(&port, 0, ROW_COUNT, count);
        steps = port_u32(&port, 0, NEXT_SAMPLE_STEPS);
        source = port_u32(&port, 0, SOURCE_PIXEL) + (port_u8(&port, steps, 0) << 2);
        port_set32(&port, 0, NEXT_SAMPLE_STEPS, steps + 1);
        port_set32(&port, 0, SOURCE_ROW, source);
        port_set32(&port, 0, SAMPLE_STEPS, port_u32(&port, 0, ROW_INDEX));
        target = port_u32(&port, 0, row_global);
        mask = port_u32(&port, 0, MASK_ROW);
        port_set32(&port, 0, target_pixel, target);
        port_set32(&port, 0, MASK_PIXEL, mask);
        port_set32(&port, 0, row_global, target + step);
        port_set32(&port, 0, MASK_ROW, mask + 1);
        port_call(&port, routine, mask + 1, target + step, routine, source);
        start = port_u32(&port, 0, ROW_START);
        eax = port_u32(&port, 0, SOURCE_ROW);
        port_set32(&port, 0, SOURCE_PIXEL, eax);
        start += 2;
        count = (port_u16(&port, 0, ROWS) - 1) & 0xffff;
        port_set16(&port, 0, ROWS, count);
    } while (count != 0);
    port_set32(&port, 0, ROW_START, start);
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

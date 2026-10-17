#include "rtljpegcolorselects.h"

/* libjpeg's finish_pass1 (jquant2.c) with select_colors, median_cut and compute_color inlined.
 * Median cut splits the histogram into the desired number of boxes, taking the most populous
 * splittable box while that at most doubles the count and the largest one after, and cutting it
 * at the midpoint of its longest scaled axis. Each box's mean colour then fills the colormap. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_ACTUAL_NUMBER_OF_COLORS = 0x84,
    CINFO_COLORMAP = 0x88,
    CINFO_CQUANTIZE = 0x1cc,
    MEM_ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    JTRC_QUANT_SELECTED = 0x60,
    TRACE_LEVEL = 1,

    CQUANTIZE_SV_COLORMAP = 0x10,
    CQUANTIZE_DESIRED = 0x14,
    CQUANTIZE_HISTOGRAM = 0x18,
    CQUANTIZE_NEEDS_ZEROED = 0x1c,

    /* A box: each component's inclusive range (minimum then maximum, 8 bytes per component), its
     * volume and its population. */
    BOX_SIZE = 0x20,
    BOX_C0MIN = 0,
    BOX_C0MAX = 4,
    BOX_C1MIN = 8,
    BOX_C1MAX = 0xc,
    BOX_C2MIN = 0x10,
    BOX_C2MAX = 0x14,
    BOX_VOLUME = 0x18,
    BOX_COLORCOUNT = 0x1c,
    BOX_AXIS = 8,

    /* histogram[c0] points to 64 rows of c1, each 32 word cells of c2. The cells drop 3, 2 and 3
     * bits of the samples. */
    ROW_BYTES = 64,
    CELL_BYTES = 2,
    C0_SHIFT = 3,
    C1_SHIFT = 2,
    C2_SHIFT = 3,

    UPDATE_BOX = 0x4c70f0
};

/* The loops step their indices with wraparound, as the compiled ones do. */
static int32_t next(int32_t index)
{
    return (int32_t)((uint32_t)index + 1u);
}

/* The sample value at the centre of histogram cell `index` along an axis that drops `shift`
 * bits. */
static uint32_t centre(int32_t index, unsigned shift)
{
    return ((uint32_t)index << shift) + ((1u << shift) >> 1);
}

/* compute_color's c1 and c2 loops run on the centre values rather than the indices, so a bound
 * that overflows ends them where it ends the original. */
static int within(int32_t index, int32_t max, unsigned shift)
{
    return (int32_t)centre(index, shift) <= (int32_t)centre(max, shift);
}

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend in eax, as the lifted runtime
 * does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

static uint32_t box_at(uint32_t boxlist, int32_t index)
{
    return boxlist + (uint32_t)index * BOX_SIZE;
}

/* The box with the largest population among those with a nonzero volume, or 0. */
static uint32_t biggest_population(Port *port, uint32_t boxlist, int32_t numboxes)
{
    uint32_t which = 0;
    int32_t most = 0;
    for (int32_t i = 0; i < numboxes && !port->env.failed; i++)
    {
        const uint32_t box = box_at(boxlist, i);
        const int32_t count = (int32_t)port_u32(port, box, BOX_COLORCOUNT);
        if (count > most && (int32_t)port_u32(port, box, BOX_VOLUME) > 0)
        {
            which = box;
            most = count;
        }
    }
    return which;
}

/* The box with the largest volume, or 0. */
static uint32_t biggest_volume(Port *port, uint32_t boxlist, int32_t numboxes)
{
    uint32_t which = 0;
    int32_t most = 0;
    for (int32_t i = 0; i < numboxes && !port->env.failed; i++)
    {
        const uint32_t box = box_at(boxlist, i);
        const int32_t volume = (int32_t)port_u32(port, box, BOX_VOLUME);
        if (volume > most)
        {
            which = box;
            most = volume;
        }
    }
    return which;
}

/* Copy b1's bounds to b2, then cut b1 at the midpoint of its longest scaled axis (ties go to c1,
 * then c0) and give the upper part to b2. */
static void split(Port *port, uint32_t b1, uint32_t b2)
{
    static const uint32_t bounds[] = {BOX_C0MAX, BOX_C1MAX, BOX_C2MAX,
                                      BOX_C0MIN, BOX_C1MIN, BOX_C2MIN};
    for (size_t i = 0; i < sizeof bounds / sizeof bounds[0]; i++)
    {
        port_set32(port, b2, bounds[i], port_u32(port, b1, bounds[i]));
    }

    /* The axis lengths in sample units, with the distance scales 2, 3 and 1. */
    const int32_t c0 =
        (int32_t)((port_u32(port, b1, BOX_C0MAX) - port_u32(port, b1, BOX_C0MIN)) << 4);
    const int32_t c1 =
        (int32_t)((port_u32(port, b1, BOX_C1MAX) - port_u32(port, b1, BOX_C1MIN)) * 12u);
    const int32_t c2 =
        (int32_t)((port_u32(port, b1, BOX_C2MAX) - port_u32(port, b1, BOX_C2MIN)) << 3);
    int32_t longest = c1;
    uint32_t axis = 1;
    if (c0 > longest)
    {
        longest = c0;
        axis = 0;
    }
    if (c2 > longest)
    {
        axis = 2;
    }

    const uint32_t min = BOX_C0MIN + axis * BOX_AXIS;
    const uint32_t max = BOX_C0MAX + axis * BOX_AXIS;
    const int32_t lower = (int32_t)(port_u32(port, b1, max) + port_u32(port, b1, min)) / 2;
    port_set32(port, b1, max, (uint32_t)lower);
    port_set32(port, b2, min, (uint32_t)lower + 1u);
}

/* Colormap entry `icolor` from the population-weighted mean of the box's cell centres. */
static void compute_color(Port *port, uint32_t cinfo, uint32_t box, uint32_t icolor)
{
    const int32_t c0min = (int32_t)port_u32(port, box, BOX_C0MIN);
    const int32_t c0max = (int32_t)port_u32(port, box, BOX_C0MAX);
    const int32_t c1min = (int32_t)port_u32(port, box, BOX_C1MIN);
    const int32_t c1max = (int32_t)port_u32(port, box, BOX_C1MAX);
    const int32_t c2min = (int32_t)port_u32(port, box, BOX_C2MIN);
    const int32_t c2max = (int32_t)port_u32(port, box, BOX_C2MAX);
    const uint32_t histogram =
        port_u32(port, port_u32(port, cinfo, CINFO_CQUANTIZE), CQUANTIZE_HISTOGRAM);

    uint32_t total = 0;
    uint32_t c0total = 0;
    uint32_t c1total = 0;
    uint32_t c2total = 0;
    for (int32_t c0 = c0min; c0 <= c0max && !port->env.failed; c0 = next(c0))
    {
        if (c1min > c1max)
        {
            continue;
        }
        const uint32_t row = port_u32(port, histogram + (uint32_t)c0 * 4u, 0);
        int32_t c1 = c1min;
        do
        {
            if (c2min <= c2max)
            {
                uint32_t at = row + (uint32_t)c1 * ROW_BYTES + (uint32_t)c2min * CELL_BYTES;
                int32_t c2 = c2min;
                do
                {
                    const uint32_t count = port_u16(port, at, 0);
                    if (count != 0)
                    {
                        total += count;
                        c0total += centre(c0, C0_SHIFT) * count;
                        c1total += centre(c1, C1_SHIFT) * count;
                        c2total += centre(c2, C2_SHIFT) * count;
                    }
                    at += CELL_BYTES;
                    c2 = next(c2);
                } while (within(c2, c2max, C2_SHIFT) && !port->env.failed);
            }
            c1 = next(c1);
        } while (within(c1, c1max, C1_SHIFT) && !port->env.failed);
    }

    const uint32_t half = (uint32_t)((int32_t)total >> 1);
    const uint32_t totals[] = {c0total, c1total, c2total};
    for (uint32_t component = 0; component < 3; component++)
    {
        const uint32_t samples =
            port_u32(port, port_u32(port, cinfo, CINFO_COLORMAP), component * 4u);
        port_set8(port, samples + icolor, 0,
                  (uint32_t)quotient((int32_t)(totals[component] + half), (int32_t)total));
    }
}

uint32_t vertrix_port_jpeg_quant2_select_colors_4c90e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t cquantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    port_set32(&port, cinfo, CINFO_COLORMAP, port_u32(&port, cquantize, CQUANTIZE_SV_COLORMAP));
    const int32_t desired = (int32_t)port_u32(&port, cquantize, CQUANTIZE_DESIRED);

    /* One box over the whole space, shrunk to the cells in use. */
    const uint32_t mem = port_u32(&port, cinfo, CINFO_MEM);
    const uint32_t boxlist = port_call(&port, port_u32(&port, mem, MEM_ALLOC_SMALL), cinfo,
                                       JPOOL_IMAGE, (uint32_t)desired << 5, mem);
    port_set32(&port, boxlist, BOX_C0MIN, 0);
    port_set32(&port, boxlist, BOX_C0MAX, 0xff >> C0_SHIFT);
    port_set32(&port, boxlist, BOX_C1MIN, 0);
    port_set32(&port, boxlist, BOX_C1MAX, 0xff >> C1_SHIFT);
    port_set32(&port, boxlist, BOX_C2MIN, 0);
    port_set32(&port, boxlist, BOX_C2MAX, 0xff >> C2_SHIFT);
    port_call(&port, UPDATE_BOX, cinfo, boxlist, 0, 0);

    int32_t numboxes = 1;
    while (numboxes < desired && !port.env.failed)
    {
        const uint32_t b1 = (int32_t)((uint32_t)numboxes * 2u) <= desired
                                ? biggest_population(&port, boxlist, numboxes)
                                : biggest_volume(&port, boxlist, numboxes);
        if (b1 == 0)
        {
            break;
        }
        const uint32_t b2 = box_at(boxlist, numboxes);
        split(&port, b1, b2);
        port_call(&port, UPDATE_BOX, cinfo, b1, 0, 0);
        port_call(&port, UPDATE_BOX, cinfo, b2, 0, 0);
        numboxes++;
    }

    for (int32_t i = 0; i < numboxes && !port.env.failed; i++)
    {
        compute_color(&port, cinfo, box_at(boxlist, i), (uint32_t)i);
    }
    port_set32(&port, cinfo, CINFO_ACTUAL_NUMBER_OF_COLORS, (uint32_t)numboxes);

    /* TRACEMS1(cinfo, 1, JTRC_QUANT_SELECTED, numboxes); ebx is left past the last box. */
    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JTRC_QUANT_SELECTED);
    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM, (uint32_t)numboxes);
    const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
    port_call(&port, port_u32(&port, err, ERR_EMIT_MESSAGE), cinfo, TRACE_LEVEL,
              box_at(boxlist, numboxes), err);

    /* A method, called through cquantize->finish_pass: eax is left at cquantize and edx is saved.
     */
    port_set32(&port, cquantize, CQUANTIZE_NEEDS_ZEROED, 1);
    return port_return(&port, cquantize, entry->edx);
}

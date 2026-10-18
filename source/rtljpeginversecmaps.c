#include "rtljpeginversecmaps.h"

/* libjpeg's fill_inverse_cmap (jquant2.c) with find_nearby_colors and find_best_colors inlined:
 * the two-pass quantizer's inverse colormap for one update box of the histogram. */

enum
{
    /* The frame under the return slot: three saved registers and 0x84c bytes of locals, whose low
     * end S holds the colours' minimum distances (S), the best distances (S+0x400), the colour list
     * (S+0x600) and the best colours (S+0x700). */
    BELOW = 0x858,
    MINDIST = 0,
    BESTDIST = 0x400,
    COLORLIST = 0x600,
    BESTCOLOR = 0x700,

    CINFO_ACTUAL_NUMBER_OF_COLORS = 0x84,
    CINFO_COLORMAP = 0x88,
    CINFO_CQUANTIZE = 0x1cc,
    QUANTIZE_HISTOGRAM = 0x18,

    BOX_C0_LOG = 2,
    BOX_C1_LOG = 3,
    BOX_C2_LOG = 2,
    BOX_C0_ELEMS = 4,
    BOX_C1_ELEMS = 8,
    BOX_C2_ELEMS = 4,
    BOX_SHIFT = 5,
    C0_SHIFT = 3,
    C1_SHIFT = 2,
    C2_SHIFT = 3,
    C0_SCALE = 2,
    C1_SCALE = 3,
    C2_SCALE = 1,
    STEP_C0 = (1 << C0_SHIFT) * C0_SCALE,
    STEP_C1 = (1 << C1_SHIFT) * C1_SCALE,
    STEP_C2 = (1 << C2_SHIFT) * C2_SCALE,
    BOX_SPAN = 1 << BOX_SHIFT,
    BEST_COUNT = BOX_C0_ELEMS * BOX_C1_ELEMS * BOX_C2_ELEMS,
    FAR_AWAY = 0x7fffffff,

    /* A histogram plane: 64 rows of 32 16-bit cells. */
    HIST_C2_ELEMS = 32,
    CELL_SIZE = 2,

    /* What the original leaves in eax: the innermost loop's count. */
    RESULT = BOX_C2_ELEMS
};

/* The minimum and maximum squared distances, scaled, from one colour component x to the box's
 * range [minc, maxc] (centre centerc). */
static void distances(uint32_t x, uint32_t minc, uint32_t maxc, uint32_t centerc, uint32_t scale,
                      uint32_t *min_dist, uint32_t *max_dist)
{
    const uint32_t below = (x - minc) * scale;
    const uint32_t above = (x - maxc) * scale;
    if ((int32_t)x < (int32_t)minc)
    {
        *min_dist += below * below;
        *max_dist += above * above;
    }
    else if ((int32_t)x > (int32_t)maxc)
    {
        *min_dist += above * above;
        *max_dist += below * below;
    }
    else if ((int32_t)x <= (int32_t)centerc)
    {
        *max_dist += above * above;
    }
    else
    {
        *max_dist += below * below;
    }
}

/* Original 0x4c8500 (eax = cinfo, edx, ebx, ecx = the cell's c0, c1 and c2): fill_inverse_cmap.
 * The update box holding the cell is 4 x 8 x 4 cells; the colours that may be nearest to a point
 * of it (those whose minimum distance is at most the least maximum distance) are listed, the
 * nearest of them is found for every cell incrementally, and each cell gets that colour + 1. */
uint32_t vertrix_port_jpeg_fill_inverse_cmap_4c8500(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - BELOW;
    const uint32_t cinfo = entry->eax;
    const uint32_t histogram =
        port_u32(&port, port_u32(&port, cinfo, CINFO_CQUANTIZE), QUANTIZE_HISTOGRAM);
    const int32_t c0 = (int32_t)entry->edx >> BOX_C0_LOG;
    const int32_t c1 = (int32_t)entry->ebx >> BOX_C1_LOG;
    const int32_t c2 = (int32_t)entry->ecx >> BOX_C2_LOG;
    const uint32_t minc0 = port_shl((uint32_t)c0, BOX_SHIFT) + ((1 << C0_SHIFT) >> 1);
    const uint32_t minc1 = port_shl((uint32_t)c1, BOX_SHIFT) + ((1 << C1_SHIFT) >> 1);
    const uint32_t minc2 = port_shl((uint32_t)c2, BOX_SHIFT) + ((1 << C2_SHIFT) >> 1);

    /* find_nearby_colors */
    const uint32_t maxc0 = minc0 + (BOX_SPAN - (1 << C0_SHIFT));
    const uint32_t maxc1 = minc1 + (BOX_SPAN - (1 << C1_SHIFT));
    const uint32_t maxc2 = minc2 + (BOX_SPAN - (1 << C2_SHIFT));
    const uint32_t centerc0 = (uint32_t)((int32_t)(minc0 + maxc0) >> 1);
    const uint32_t centerc1 = (uint32_t)((int32_t)(minc1 + maxc1) >> 1);
    const uint32_t centerc2 = (uint32_t)((int32_t)(minc2 + maxc2) >> 1);
    const uint32_t colormap = port_u32(&port, cinfo, CINFO_COLORMAP);
    const int32_t numcolors = (int32_t)port_u32(&port, cinfo, CINFO_ACTUAL_NUMBER_OF_COLORS);
    int32_t minmaxdist = FAR_AWAY;
    for (int32_t i = 0; i < numcolors && !port.env.failed; i++)
    {
        uint32_t min_dist = 0;
        uint32_t max_dist = 0;
        distances(port_u8(&port, port_u32(&port, colormap, 0), (uint32_t)i), minc0, maxc0, centerc0,
                  C0_SCALE, &min_dist, &max_dist);
        distances(port_u8(&port, port_u32(&port, colormap, 4), (uint32_t)i), minc1, maxc1, centerc1,
                  C1_SCALE, &min_dist, &max_dist);
        distances(port_u8(&port, port_u32(&port, colormap, 8), (uint32_t)i), minc2, maxc2, centerc2,
                  C2_SCALE, &min_dist, &max_dist);
        port_set32(&port, frame + MINDIST, 4 * (uint32_t)i, min_dist);
        if ((int32_t)max_dist < minmaxdist)
        {
            minmaxdist = (int32_t)max_dist;
        }
    }
    uint32_t ncolors = 0;
    for (int32_t i = 0; i < numcolors && !port.env.failed; i++)
    {
        if (minmaxdist >= (int32_t)port_u32(&port, frame + MINDIST, 4 * (uint32_t)i))
        {
            port_set8(&port, frame + COLORLIST, ncolors, (uint32_t)i);
            ncolors++;
        }
    }

    /* find_best_colors */
    for (uint32_t i = 0; i < BEST_COUNT; i++)
    {
        port_set32(&port, frame + BESTDIST, 4 * i, FAR_AWAY);
    }
    for (uint32_t i = 0; i < ncolors && !port.env.failed; i++)
    {
        const uint32_t icolor = port_u8(&port, frame + COLORLIST, i);
        uint32_t inc0 = (minc0 - port_u8(&port, port_u32(&port, colormap, 0), icolor)) * C0_SCALE;
        uint32_t dist0 = inc0 * inc0;
        uint32_t inc1 = (minc1 - port_u8(&port, port_u32(&port, colormap, 4), icolor)) * C1_SCALE;
        dist0 += inc1 * inc1;
        uint32_t inc2 = (minc2 - port_u8(&port, port_u32(&port, colormap, 8), icolor)) * C2_SCALE;
        dist0 += inc2 * inc2;
        inc0 = inc0 * (2 * STEP_C0) + STEP_C0 * STEP_C0;
        inc1 = inc1 * (2 * STEP_C1) + STEP_C1 * STEP_C1;
        inc2 = inc2 * (2 * STEP_C2) + STEP_C2 * STEP_C2;
        uint32_t cell = 0;
        uint32_t xx0 = inc0;
        for (int ic0 = BOX_C0_ELEMS - 1; ic0 >= 0; ic0--)
        {
            uint32_t dist1 = dist0;
            uint32_t xx1 = inc1;
            for (int ic1 = BOX_C1_ELEMS - 1; ic1 >= 0; ic1--)
            {
                uint32_t dist2 = dist1;
                uint32_t xx2 = inc2;
                for (int ic2 = BOX_C2_ELEMS - 1; ic2 >= 0; ic2--)
                {
                    if ((int32_t)dist2 < (int32_t)port_u32(&port, frame + BESTDIST, 4 * cell))
                    {
                        port_set32(&port, frame + BESTDIST, 4 * cell, dist2);
                        port_set8(&port, frame + BESTCOLOR, cell, icolor);
                    }
                    dist2 += xx2;
                    xx2 += 2 * STEP_C2 * STEP_C2;
                    cell++;
                }
                dist1 += xx1;
                xx1 += 2 * STEP_C1 * STEP_C1;
            }
            dist0 += xx0;
            xx0 += 2 * STEP_C0 * STEP_C0;
        }
    }

    /* The cells of the box get their best colour + 1. */
    const uint32_t base0 = port_shl((uint32_t)c0, BOX_C0_LOG);
    const uint32_t base1 = port_shl((uint32_t)c1, BOX_C1_LOG);
    const uint32_t base2 = port_shl((uint32_t)c2, BOX_C2_LOG);
    uint32_t cell = 0;
    for (uint32_t ic0 = 0; ic0 < BOX_C0_ELEMS; ic0++)
    {
        for (uint32_t ic1 = 0; ic1 < BOX_C1_ELEMS; ic1++)
        {
            /* The plane pointer is read again for every row, as the original does. */
            const uint32_t plane = port_u32(&port, histogram, 4 * (base0 + ic0));
            const uint32_t row = plane + ((base1 + ic1) * HIST_C2_ELEMS + base2) * CELL_SIZE;
            for (uint32_t ic2 = 0; ic2 < BOX_C2_ELEMS; ic2++)
            {
                port_set16(&port, row, CELL_SIZE * ic2,
                           port_u8(&port, frame + BESTCOLOR, cell) + 1);
                cell++;
            }
        }
    }
    return port_return(&port, RESULT, entry->edx);
}

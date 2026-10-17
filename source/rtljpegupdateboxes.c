#include "rtljpegupdateboxes.h"

/* libjpeg's update_box (jquant2.c): shrinks a median-cut box to the histogram cells in use, then
 * stores its scaled 2-norm as the volume and counts the nonzero cells inside it. */

enum
{
    CINFO_CQUANTIZE = 0x1cc,
    CQUANTIZE_HISTOGRAM = 0x18,

    /* The box: inclusive ranges of the three components, its volume and its population. */
    BOX_C0MIN = 0,
    BOX_C0MAX = 4,
    BOX_C1MIN = 8,
    BOX_C1MAX = 0xc,
    BOX_C2MIN = 0x10,
    BOX_C2MAX = 0x14,
    BOX_VOLUME = 0x18,
    BOX_COLORCOUNT = 0x1c,

    /* histogram[c0] points to 64 rows of c1, each 32 word cells of c2. */
    ROW_BYTES = 64,
    CELL_BYTES = 2
};

typedef struct
{
    Port *port;
    uint32_t histogram;
    int32_t c0min;
    int32_t c0max;
    int32_t c1min;
    int32_t c1max;
    int32_t c2min;
    int32_t c2max;
} Box;

/* The loops step their indices with wraparound, as the compiled ones do. */
static int32_t next(int32_t index)
{
    return (int32_t)((uint32_t)index + 1u);
}

static int32_t prev(int32_t index)
{
    return (int32_t)((uint32_t)index - 1u);
}

/* The c1 and c2 scans bound their outer loops by the byte offsets (c1 * 64, c2 * 2) rather than
 * by the indices, so a bound that overflows ends them where it ends the original. */
static int32_t scaled(int32_t index, uint32_t size)
{
    return (int32_t)((uint32_t)index * size);
}

static int failed(const Box *box)
{
    return box->port->env.failed;
}

/* The address of histogram[c0][c1][c2]. */
static uint32_t cell(const Box *box, int32_t c0, int32_t c1, int32_t c2)
{
    const uint32_t row = port_u32(box->port, box->histogram + (uint32_t)c0 * 4u, 0);
    return row + (uint32_t)c1 * ROW_BYTES + (uint32_t)c2 * CELL_BYTES;
}

static int used(const Box *box, uint32_t at)
{
    return port_u16(box->port, at, 0) != 0;
}

/* Whether any of histogram[c0][c1][c2min..c2max] is in use. */
static int c2_run_used(const Box *box, int32_t c0, int32_t c1)
{
    uint32_t at = cell(box, c0, c1, box->c2min);
    for (int32_t c2 = box->c2min; c2 <= box->c2max && !failed(box); c2 = next(c2))
    {
        if (used(box, at))
        {
            return 1;
        }
        at += CELL_BYTES;
    }
    return 0;
}

/* Whether any of histogram[c0][c1min..c1max][c2] is in use. */
static int c1_run_used(const Box *box, int32_t c0, int32_t c2)
{
    uint32_t at = cell(box, c0, box->c1min, c2);
    for (int32_t c1 = box->c1min; c1 <= box->c1max && !failed(box); c1 = next(c1))
    {
        if (used(box, at))
        {
            return 1;
        }
        at += ROW_BYTES;
    }
    return 0;
}

/* Whether any cell of the box with this c0 is in use. */
static int c0_plane_used(const Box *box, int32_t c0)
{
    for (int32_t c1 = box->c1min; c1 <= box->c1max && !failed(box); c1 = next(c1))
    {
        if (c2_run_used(box, c0, c1))
        {
            return 1;
        }
    }
    return 0;
}

/* Whether any cell of the box with this c1 is in use. */
static int c1_plane_used(const Box *box, int32_t c1)
{
    for (int32_t c0 = box->c0min; c0 <= box->c0max && !failed(box); c0 = next(c0))
    {
        if (c2_run_used(box, c0, c1))
        {
            return 1;
        }
    }
    return 0;
}

/* Whether any cell of the box with this c2 is in use. */
static int c2_plane_used(const Box *box, int32_t c2)
{
    for (int32_t c0 = box->c0min; c0 <= box->c0max && !failed(box); c0 = next(c0))
    {
        if (c1_run_used(box, c0, c2))
        {
            return 1;
        }
    }
    return 0;
}

/* The number of cells in use inside the box. */
static uint32_t population(const Box *box)
{
    uint32_t count = 0;
    for (int32_t c0 = box->c0min; c0 <= box->c0max && !failed(box); c0 = next(c0))
    {
        for (int32_t c1 = box->c1min; c1 <= box->c1max && !failed(box); c1 = next(c1))
        {
            uint32_t at = cell(box, c0, c1, box->c2min);
            for (int32_t c2 = box->c2min; c2 <= box->c2max && !failed(box); c2 = next(c2))
            {
                if (used(box, at))
                {
                    count++;
                }
                at += CELL_BYTES;
            }
        }
    }
    return count;
}

uint32_t vertrix_port_jpeg_update_box_4c70f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t boxp = entry->edx;

    Box box = {0};
    box.port = &port;
    box.histogram = port_u32(&port, port_u32(&port, cinfo, CINFO_CQUANTIZE), CQUANTIZE_HISTOGRAM);
    box.c0min = (int32_t)port_u32(&port, boxp, BOX_C0MIN);
    box.c0max = (int32_t)port_u32(&port, boxp, BOX_C0MAX);
    box.c1min = (int32_t)port_u32(&port, boxp, BOX_C1MIN);
    box.c1max = (int32_t)port_u32(&port, boxp, BOX_C1MAX);
    box.c2min = (int32_t)port_u32(&port, boxp, BOX_C2MIN);
    box.c2max = (int32_t)port_u32(&port, boxp, BOX_C2MAX);

    if (box.c0max > box.c0min)
    {
        for (int32_t c0 = box.c0min; c0 <= box.c0max && !port.env.failed; c0 = next(c0))
        {
            if (c0_plane_used(&box, c0))
            {
                box.c0min = c0;
                port_set32(&port, boxp, BOX_C0MIN, (uint32_t)c0);
                break;
            }
        }
    }
    if (box.c0max > box.c0min)
    {
        for (int32_t c0 = box.c0max; c0 >= box.c0min && !port.env.failed; c0 = prev(c0))
        {
            if (c0_plane_used(&box, c0))
            {
                box.c0max = c0;
                port_set32(&port, boxp, BOX_C0MAX, (uint32_t)c0);
                break;
            }
        }
    }
    if (box.c1max > box.c1min)
    {
        int32_t c1 = box.c1min;
        do
        {
            if (c1_plane_used(&box, c1))
            {
                box.c1min = c1;
                port_set32(&port, boxp, BOX_C1MIN, (uint32_t)c1);
                break;
            }
            c1 = next(c1);
        } while (scaled(c1, ROW_BYTES) <= scaled(box.c1max, ROW_BYTES) && !port.env.failed);
    }
    if (box.c1max > box.c1min)
    {
        int32_t c1 = box.c1max;
        do
        {
            if (c1_plane_used(&box, c1))
            {
                box.c1max = c1;
                port_set32(&port, boxp, BOX_C1MAX, (uint32_t)c1);
                break;
            }
            c1 = prev(c1);
        } while (scaled(c1, ROW_BYTES) >= scaled(box.c1min, ROW_BYTES) && !port.env.failed);
    }
    if (box.c2max > box.c2min)
    {
        int32_t c2 = box.c2min;
        do
        {
            if (c2_plane_used(&box, c2))
            {
                box.c2min = c2;
                port_set32(&port, boxp, BOX_C2MIN, (uint32_t)c2);
                break;
            }
            c2 = next(c2);
        } while (scaled(c2, CELL_BYTES) <= scaled(box.c2max, CELL_BYTES) && !port.env.failed);
    }
    if (box.c2max > box.c2min)
    {
        int32_t c2 = box.c2max;
        do
        {
            if (c2_plane_used(&box, c2))
            {
                box.c2max = c2;
                port_set32(&port, boxp, BOX_C2MAX, (uint32_t)c2);
                break;
            }
            c2 = prev(c2);
        } while (scaled(c2, CELL_BYTES) >= scaled(box.c2min, CELL_BYTES) && !port.env.failed);
    }

    /* The 2-norm in sample units, with the distance scales 2, 3 and 1: (c0 << 3) * 2,
     * (c1 << 2) * 3 and c2 << 3. */
    const uint32_t dist0 = ((uint32_t)box.c0max - (uint32_t)box.c0min) << 4;
    const uint32_t dist1 = ((uint32_t)box.c1max - (uint32_t)box.c1min) * 12u;
    const uint32_t dist2 = ((uint32_t)box.c2max - (uint32_t)box.c2min) << 3;
    port_set32(&port, boxp, BOX_VOLUME, dist0 * dist0 + dist1 * dist1 + dist2 * dist2);
    port_set32(&port, boxp, BOX_COLORCOUNT, population(&box));
    return port_return(&port, 0, 0);
}

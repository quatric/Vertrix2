#include "rtlbufsteps.h"

/* libjpeg's process_data_context_main (jdmainct.c), with set_bottom_pointers and
 * set_wraparound_pointers inlined: the main buffer controller for upsampling that needs the row
 * groups around each one. It reads an iMCU row into one of its two pointer lists and hands the row
 * groups to the postprocessor, the last one of each iMCU row postponed until the next row is in. */

enum
{
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_COMP_INFO = 0xd8,
    CINFO_MIN_DCT_SCALED_SIZE = 0x13c,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_MAIN = 0x1a8,
    CINFO_COEF = 0x1ac,
    CINFO_POST = 0x1b0,
    COEF_DECOMPRESS_DATA = 0xc,
    POST_POST_PROCESS_DATA = 4,

    /* jpeg_component_info: 0x54 bytes. */
    COMPONENT_BYTES = 0x54,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_DOWNSAMPLED_HEIGHT = 0x2c,

    /* The main controller: whether its buffer holds an iMCU row, the row groups handed on and
     * available, the two pointer lists and which one is in use (its low byte flipped), the
     * context state, and the iMCU rows read. */
    MAIN_BUFFER_FULL = 0x30,
    MAIN_ROWGROUP_CTR = 0x34,
    MAIN_XBUFFER = 0x38,
    MAIN_WHICHPTR = 0x40,
    MAIN_CONTEXT_STATE = 0x44,
    MAIN_ROWGROUPS_AVAIL = 0x48,
    MAIN_IMCU_ROW_CTR = 0x4c,

    CTX_PREPARE_FOR_IMCU = 0,
    CTX_PROCESS_IMCU = 1,
    CTX_POSTPONED_ROW = 2
};

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend in eax, as the lifted runtime
 * does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

/* div: an invalid one (by 0) leaves the 0 the original puts in edx as the remainder. */
static uint32_t remainder_of(uint32_t a, uint32_t b)
{
    return b != 0 ? a % b : 0;
}

static uint32_t field(Port *port, uint32_t base, uint32_t offset)
{
    return port_u32(port, base, offset);
}

/* The pointer list in use. */
static uint32_t current_xbuffer(Port *port, uint32_t main)
{
    return port_u32(port, main + field(port, main, MAIN_WHICHPTR) * 4, MAIN_XBUFFER);
}

/* A row's pointer in a component's list: `row` may be negative (the lists have room above), and
 * wraps as the original's 32-bit arithmetic does. */
static uint32_t row_at(uint32_t list, uint32_t row)
{
    return list + row * 4;
}

/* The height of a row group of the component: its iMCU row's sample rows over min_DCT_scaled_size.
 */
static int32_t row_group(Port *port, uint32_t cinfo, uint32_t component)
{
    const uint32_t imcu_height = port_u32(port, component, COMPONENT_V_SAMP_FACTOR) *
                                 port_u32(port, component, COMPONENT_DCT_SCALED_SIZE);
    return quotient((int32_t)imcu_height, (int32_t)field(port, cinfo, CINFO_MIN_DCT_SCALED_SIZE));
}

/* set_bottom_pointers: at the last iMCU row, the last real sample row is repeated twice a row group
 * further, and (from the first component) only the row groups holding real rows are available. */
static void set_bottom_pointers(Port *port, uint32_t cinfo)
{
    const uint32_t main = field(port, cinfo, CINFO_MAIN);
    uint32_t component = field(port, cinfo, CINFO_COMP_INFO);
    for (int32_t ci = 0;
         ci < (int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) && !port->env.failed; ci++)
    {
        const uint32_t imcu_height = port_u32(port, component, COMPONENT_V_SAMP_FACTOR) *
                                     port_u32(port, component, COMPONENT_DCT_SCALED_SIZE);
        const int32_t rgroup =
            quotient((int32_t)imcu_height, (int32_t)field(port, cinfo, CINFO_MIN_DCT_SCALED_SIZE));
        uint32_t rows_left =
            remainder_of(port_u32(port, component, COMPONENT_DOWNSAMPLED_HEIGHT), imcu_height);
        if (rows_left == 0)
        {
            rows_left = imcu_height;
        }
        if (ci == 0)
        {
            port_set32(port, main, MAIN_ROWGROUPS_AVAIL,
                       (uint32_t)quotient((int32_t)(rows_left - 1), rgroup) + 1);
        }
        const uint32_t xbuf = port_u32(port, current_xbuffer(port, main), (uint32_t)ci * 4);
        const uint32_t last = row_at(xbuf, rows_left);
        const int32_t copies = (int32_t)((uint32_t)rgroup * 2);
        for (int32_t i = 0; i < copies && !port->env.failed; i++)
        {
            port_set32(port, last + (uint32_t)i * 4, 0, port_u32(port, last, (uint32_t)-4));
        }
        component += COMPONENT_BYTES;
    }
}

/* set_wraparound_pointers: after the first iMCU row, each list's row group above its start points
 * at the one after its M+1 groups, and the group after its M+2 groups at its first. */
static void set_wraparound_pointers(Port *port, uint32_t cinfo)
{
    const uint32_t main = field(port, cinfo, CINFO_MAIN);
    const uint32_t m = field(port, cinfo, CINFO_MIN_DCT_SCALED_SIZE);
    uint32_t component = field(port, cinfo, CINFO_COMP_INFO);
    for (int32_t ci = 0;
         ci < (int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) && !port->env.failed; ci++)
    {
        const int32_t rgroup = row_group(port, cinfo, component);
        const uint32_t xbuf0 = port_u32(port, field(port, main, MAIN_XBUFFER), (uint32_t)ci * 4);
        const uint32_t xbuf1 =
            port_u32(port, field(port, main, MAIN_XBUFFER + 4), (uint32_t)ci * 4);
        for (int32_t i = 0; i < rgroup && !port->env.failed; i++)
        {
            const uint32_t row = (uint32_t)i;
            const uint32_t above = row - (uint32_t)rgroup;
            const uint32_t after = (uint32_t)rgroup * (m + 1) + row;
            const uint32_t wrap = (uint32_t)rgroup * (m + 2) + row;
            port_set32(port, row_at(xbuf0, above), 0, port_u32(port, row_at(xbuf0, after), 0));
            port_set32(port, row_at(xbuf1, above), 0, port_u32(port, row_at(xbuf1, after), 0));
            port_set32(port, row_at(xbuf0, wrap), 0, port_u32(port, row_at(xbuf0, row), 0));
            port_set32(port, row_at(xbuf1, wrap), 0, port_u32(port, row_at(xbuf1, row), 0));
        }
        component += COMPONENT_BYTES;
    }
}

/* post_process_data, a method, on the pointer list in use from the next row group. Returns the
 * list it handed over. */
static uint32_t post_process(Port *port, uint32_t cinfo, uint32_t main, const uint32_t output[3])
{
    const uint32_t post = field(port, cinfo, CINFO_POST);
    const uint32_t xbuffer = current_xbuffer(port, main);
    port_call_stack(port, port_u32(port, post, POST_POST_PROCESS_DATA), cinfo, xbuffer,
                    main + MAIN_ROWGROUP_CTR, field(port, main, MAIN_ROWGROUPS_AVAIL), output, 3);
    return xbuffer;
}

/* Original 0x4bd9e0 (eax = cinfo, edx = output_buf, ebx = out_row_ctr, ecx = out_rows_avail).
 * Reached through a method pointer, so its eax and edx are compared. It returns:
 * - when decompress_data suspends: 0 and the list it was handed;
 * - for an unknown context state: the state, and the buffer_full flag (or with a row read, the list
 *   decompress_data got);
 * - while the postponed row group is not done: the row group counter and the list handed to the
 *   postprocessor; when the output is full after it: out_row_ctr and that list;
 * - while the iMCU row's groups are not done: the row group counter and the main controller; after
 *   them: min_DCT_scaled_size + 2 and the main controller. */
uint32_t vertrix_port_staged_buffer_step_wrap_pad_4bd9e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t out_row_ctr = entry->ebx;
    const uint32_t out_rows_avail = entry->ecx;
    /* post_process_data's stack arguments: output_buf, out_row_ctr, out_rows_avail. */
    const uint32_t output[3] = {entry->edx, out_row_ctr, out_rows_avail};
    const uint32_t main = field(&port, cinfo, CINFO_MAIN);

    uint32_t edx = field(&port, main, MAIN_BUFFER_FULL);
    if (edx == 0)
    {
        /* Read an iMCU row; decompress_data, a method, gets the main controller in ebx and the
         * coefficient controller in ecx. */
        const uint32_t coef = field(&port, cinfo, CINFO_COEF);
        edx = current_xbuffer(&port, main);
        if (port_call(&port, port_u32(&port, coef, COEF_DECOMPRESS_DATA), cinfo, edx, main, coef) ==
            0)
        {
            return port_return(&port, 0, edx);
        }
        port_set32(&port, main, MAIN_BUFFER_FULL, 1);
        port_set32(&port, main, MAIN_IMCU_ROW_CTR, field(&port, main, MAIN_IMCU_ROW_CTR) + 1);
    }

    const uint32_t state = field(&port, main, MAIN_CONTEXT_STATE);
    if (state > CTX_POSTPONED_ROW)
    {
        return port_return(&port, state, edx);
    }
    if (state == CTX_POSTPONED_ROW)
    {
        /* The last row group of the previous iMCU row. */
        const uint32_t xbuffer = post_process(&port, cinfo, main, output);
        const uint32_t done = field(&port, main, MAIN_ROWGROUP_CTR);
        if (done < field(&port, main, MAIN_ROWGROUPS_AVAIL))
        {
            return port_return(&port, done, xbuffer);
        }
        port_set32(&port, main, MAIN_CONTEXT_STATE, CTX_PREPARE_FOR_IMCU);
        if (out_rows_avail <= port_u32(&port, out_row_ctr, 0))
        {
            return port_return(&port, out_row_ctr, xbuffer);
        }
    }
    if (state != CTX_PROCESS_IMCU)
    {
        /* The first M-1 row groups of this iMCU row; at the bottom of the image only the real
         * ones. */
        port_set32(&port, main, MAIN_ROWGROUP_CTR, 0);
        port_set32(&port, main, MAIN_ROWGROUPS_AVAIL,
                   field(&port, cinfo, CINFO_MIN_DCT_SCALED_SIZE) - 1);
        if (field(&port, main, MAIN_IMCU_ROW_CTR) == field(&port, cinfo, CINFO_TOTAL_IMCU_ROWS))
        {
            set_bottom_pointers(&port, cinfo);
        }
        port_set32(&port, main, MAIN_CONTEXT_STATE, CTX_PROCESS_IMCU);
    }

    post_process(&port, cinfo, main, output);
    const uint32_t done = field(&port, main, MAIN_ROWGROUP_CTR);
    if (done < field(&port, main, MAIN_ROWGROUPS_AVAIL))
    {
        return port_return(&port, done, main);
    }
    if (field(&port, main, MAIN_IMCU_ROW_CTR) == 1)
    {
        set_wraparound_pointers(&port, cinfo);
    }
    /* Load the next iMCU row into the other list; its row group M+1 is the postponed one. */
    port_set8(&port, main, MAIN_WHICHPTR, port_u8(&port, main, MAIN_WHICHPTR) ^ 1);
    port_set32(&port, main, MAIN_BUFFER_FULL, 0);
    port_set32(&port, main, MAIN_ROWGROUP_CTR, field(&port, cinfo, CINFO_MIN_DCT_SCALED_SIZE) + 1);
    const uint32_t avail = field(&port, cinfo, CINFO_MIN_DCT_SCALED_SIZE) + 2;
    port_set32(&port, main, MAIN_CONTEXT_STATE, CTX_POSTPONED_ROW);
    port_set32(&port, main, MAIN_ROWGROUPS_AVAIL, avail);
    return port_return(&port, avail, main);
}

#include "rtlsurfacefilters.h"

/* libjpeg's decompress_smooth_data (jdcoefct.c): decodes one iMCU row of a progressive JPEG,
 * estimating the missing low-frequency AC coefficients of each block from the DC values of its
 * eight neighbours (block smoothing). */

enum
{
    /* The frame below the saved ebp: the workspace block handed to jcopy_block_row and the IDCT. */
    BELOW = 0x184,
    WORKSPACE = 0x180,

    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_INPUT_SCAN = 0x90,
    CINFO_INPUT_IMCU_ROW = 0x94,
    CINFO_OUTPUT_SCAN = 0x98,
    CINFO_OUTPUT_IMCU_ROW = 0x9c,
    CINFO_COMP_INFO = 0xd8,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_SS = 0x190,
    CINFO_COEF = 0x1ac,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_IDCT = 0x1c0,
    CINFO_MEM = 4,
    MEM_ACCESS_VIRT_BARRAY = 0x20,
    INPUTCTL_CONSUME_INPUT = 0,
    INPUTCTL_EOI_REACHED = 0x14,
    IDCT_INVERSE_DCT = 4,

    COEF_WHOLE_IMAGE = 0x48,
    COEF_BITS_LATCH = 0x70,
    SAVED_COEFS_BYTES = 6 * 4,

    COMPONENT_BYTES = 0x54,
    COMPONENT_V_SAMP = 0xc,
    COMPONENT_WIDTH_IN_BLOCKS = 0x1c,
    COMPONENT_HEIGHT_IN_BLOCKS = 0x20,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_NEEDED = 0x30,
    COMPONENT_QUANT_TABLE = 0x4c,

    BLOCK_BYTES = 0x80,
    JCOPY_BLOCK_ROW = 0x4c98d0,

    JPEG_SUSPENDED = 0,
    JPEG_ROW_COMPLETED = 3,
    JPEG_SCAN_COMPLETED = 4
};

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend in eax, as the lifted runtime
 * does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

/* One estimated coefficient: unless its bits are known (Al == 0) or it is already nonzero, the
 * prediction num / (Q << 8) rounded, limited to below 1 << Al. */
static void estimate(Port *port, uint32_t coefficient, int32_t al, int32_t num, uint32_t q)
{
    if (al == 0 || port_u16(port, coefficient, 0) != 0)
    {
        return;
    }
    const int32_t limit = (int32_t)(1u << (al & 31));
    const int32_t half = (int32_t)(q << 7);
    const int32_t whole = (int32_t)(q << 8);
    int32_t pred;
    if (num >= 0)
    {
        pred = quotient((int32_t)((uint32_t)half + (uint32_t)num), whole);
        if (al > 0 && pred >= limit)
        {
            pred = limit - 1;
        }
    }
    else
    {
        pred = quotient((int32_t)((uint32_t)half - (uint32_t)num), whole);
        if (al > 0 && pred >= limit)
        {
            pred = limit - 1;
        }
        pred = (int32_t)(0u - (uint32_t)pred);
    }
    port_set16(port, coefficient, 0, (uint32_t)pred);
}

static int32_t dc(Port *port, uint32_t block)
{
    return (int16_t)port_u16(port, block, 0);
}

/* The products (int32) with the DC quantizer, as the original keeps them. */
static int32_t times(int32_t a, uint32_t b)
{
    return (int32_t)((uint32_t)a * b);
}

static void smooth_component(Port *port, uint32_t cinfo, uint32_t ci, uint32_t component,
                             uint32_t output_ptr, uint32_t workspace)
{
    const uint32_t coef = port_u32(port, cinfo, CINFO_COEF);
    const uint32_t last_imcu_row = port_u32(port, cinfo, CINFO_TOTAL_IMCU_ROWS) - 1;
    const uint32_t row = port_u32(port, cinfo, CINFO_OUTPUT_IMCU_ROW);
    const uint32_t v_samp = port_u32(port, component, COMPONENT_V_SAMP);
    int32_t block_rows;
    uint32_t access_rows;
    int last_row;
    if (row < last_imcu_row)
    {
        block_rows = (int32_t)v_samp;
        access_rows = v_samp * 2;
        last_row = 0;
    }
    else
    {
        /* div: by 0 it leaves the remainder 0. */
        const uint32_t height = port_u32(port, component, COMPONENT_HEIGHT_IN_BLOCKS);
        uint32_t rest = v_samp != 0 ? height % v_samp : 0;
        block_rows = (int32_t)(rest != 0 ? rest : v_samp);
        access_rows = (uint32_t)block_rows;
        last_row = 1;
    }
    const uint32_t mem = port_u32(port, cinfo, CINFO_MEM);
    const uint32_t access = port_u32(port, mem, MEM_ACCESS_VIRT_BARRAY);
    const uint32_t whole_image = port_u32(port, coef, COEF_WHOLE_IMAGE + 4 * ci);
    const uint32_t no = 0;
    uint32_t buffer;
    int first_row;
    if (row > 0)
    {
        access_rows += v_samp;
        buffer = port_call_stack(port, access, cinfo, whole_image, (row - 1) * v_samp, access_rows,
                                 &no, 1);
        buffer += 4 * v_samp;
        first_row = 0;
    }
    else
    {
        buffer = port_call_stack(port, access, cinfo, whole_image, 0, access_rows, &no, 1);
        first_row = 1;
    }
    const uint32_t coef_bits = port_u32(port, coef, COEF_BITS_LATCH) + ci * SAVED_COEFS_BYTES;
    const uint32_t quant = port_u32(port, component, COMPONENT_QUANT_TABLE);
    const uint32_t q00 = port_u16(port, quant, 0);
    const uint32_t q01 = port_u16(port, quant, 2);
    const uint32_t q02 = port_u16(port, quant, 4);
    const uint32_t q10 = port_u16(port, quant, 0x10);
    const uint32_t q11 = port_u16(port, quant, 0x12);
    const uint32_t q20 = port_u16(port, quant, 0x20);
    const uint32_t inverse_dct =
        port_u32(port, port_u32(port, cinfo, CINFO_IDCT), IDCT_INVERSE_DCT + 4 * ci);
    for (int32_t block_row = 0; block_row < block_rows && !port->env.failed; block_row++)
    {
        const uint32_t rows = buffer + 4 * (uint32_t)block_row;
        uint32_t current = port_u32(port, rows, 0);
        uint32_t prev = first_row && block_row == 0 ? current : port_u32(port, rows - 4, 0);
        uint32_t next =
            last_row && block_row == block_rows - 1 ? current : port_u32(port, rows + 4, 0);
        int32_t dc1, dc2, dc3, dc4, dc5, dc6, dc7, dc8, dc9;
        dc1 = dc2 = dc3 = dc(port, prev);
        dc4 = dc5 = dc6 = dc(port, current);
        dc7 = dc8 = dc9 = dc(port, next);
        uint32_t output_col = 0;
        const uint32_t last_column = port_u32(port, component, COMPONENT_WIDTH_IN_BLOCKS) - 1;
        for (uint32_t block = 0; block <= last_column && !port->env.failed; block++)
        {
            port_call(port, JCOPY_BLOCK_ROW, current, workspace, 1, 0);
            if (block < last_column)
            {
                dc3 = dc(port, prev + BLOCK_BYTES);
                dc6 = dc(port, current + BLOCK_BYTES);
                dc9 = dc(port, next + BLOCK_BYTES);
            }
            /* AC01, AC10, AC20, AC11 and AC02. */
            estimate(port, workspace + 2, (int32_t)port_u32(port, coef_bits, 4),
                     times(dc4 - dc6, q00 * 36), q01);
            estimate(port, workspace + 0x10, (int32_t)port_u32(port, coef_bits, 8),
                     times(dc2 - dc8, q00 * 36), q10);
            estimate(port, workspace + 0x20, (int32_t)port_u32(port, coef_bits, 0xc),
                     times(dc2 + dc8 - 2 * dc5, q00 * 9), q20);
            estimate(port, workspace + 0x12, (int32_t)port_u32(port, coef_bits, 0x10),
                     times(dc1 - dc3 - dc7 + dc9, q00 * 5), q11);
            estimate(port, workspace + 4, (int32_t)port_u32(port, coef_bits, 0x14),
                     times(dc4 + dc6 - 2 * dc5, q00 * 9), q02);
            port_call_stack(port, inverse_dct, cinfo, component, workspace, output_ptr, &output_col,
                            1);
            dc1 = dc2;
            dc2 = dc3;
            dc4 = dc5;
            dc5 = dc6;
            dc7 = dc8;
            dc8 = dc9;
            current += BLOCK_BYTES;
            prev += BLOCK_BYTES;
            next += BLOCK_BYTES;
            output_col += port_u32(port, component, COMPONENT_DCT_SCALED_SIZE);
        }
        output_ptr += 4 * port_u32(port, component, COMPONENT_DCT_SCALED_SIZE);
    }
}

/* Original 0x4ba7b0. While the input is not ahead of the output it consumes input, which sees in
 * ebx the output scan number, or the input iMCU row when it compared that, and in ecx output_buf.
 */
uint32_t vertrix_port_surface_filter_rows_4ba7b0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t workspace = frame - WORKSPACE;
    const uint32_t cinfo = entry->eax;
    const uint32_t output_buf = entry->edx;
    uint32_t ebx = port_u32(&port, cinfo, CINFO_OUTPUT_SCAN);
    if ((int32_t)ebx >= (int32_t)port_u32(&port, cinfo, CINFO_INPUT_SCAN))
    {
        for (;;)
        {
            const uint32_t inputctl = port_u32(&port, cinfo, CINFO_INPUTCTL);
            if (port_u32(&port, inputctl, INPUTCTL_EOI_REACHED) != 0 || port.env.failed)
            {
                break;
            }
            if (port_u32(&port, cinfo, CINFO_INPUT_SCAN) ==
                port_u32(&port, cinfo, CINFO_OUTPUT_SCAN))
            {
                const uint32_t delta = port_u32(&port, cinfo, CINFO_SS) == 0;
                ebx = port_u32(&port, cinfo, CINFO_INPUT_IMCU_ROW);
                if (delta + port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW) < ebx)
                {
                    break;
                }
            }
            const uint32_t consume = port_u32(&port, inputctl, INPUTCTL_CONSUME_INPUT);
            if (port_call(&port, consume, cinfo, inputctl, ebx, output_buf) == JPEG_SUSPENDED)
            {
                return port_return(&port, JPEG_SUSPENDED, JPEG_SUSPENDED);
            }
            if ((int32_t)port_u32(&port, cinfo, CINFO_INPUT_SCAN) >
                (int32_t)port_u32(&port, cinfo, CINFO_OUTPUT_SCAN))
            {
                break;
            }
        }
    }
    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    for (uint32_t ci = 0;
         (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) && !port.env.failed;
         ci++, component += COMPONENT_BYTES)
    {
        if (port_u32(&port, component, COMPONENT_NEEDED) != 0)
        {
            smooth_component(&port, cinfo, ci, component, port_u32(&port, output_buf, 4 * ci),
                             workspace);
        }
    }
    const uint32_t row = port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW) + 1;
    port_set32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW, row);
    const uint32_t status = row < port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS)
                                ? JPEG_ROW_COMPLETED
                                : JPEG_SCAN_COMPLETED;
    return port_return(&port, status, status);
}

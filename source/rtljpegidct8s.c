#include "rtljpegidct8s.h"

/* libjpeg's jpeg_idct_islow (jidctint.c): the accurate integer inverse DCT of an 8x8 block, with
 * dequantisation, a shortcut for rows and columns whose AC terms are zero, and range limiting. */

enum
{
    CINFO_SAMPLE_RANGE_LIMIT = 0x144,
    CENTERJSAMPLE = 0x80,
    RANGE_MASK = 0x3ff,
    COMPONENT_DCT_TABLE = 0x50,
    ARGUMENT_OUTPUT_COL = 4,
    DCTSIZE = 8,
    CONST_BITS = 13,
    PASS1_BITS = 2,
    /* Where the original's workspace ends, below its return slot: eax on return. */
    WORKSPACE_END = 0x58
};

#define FIX_0_298631336 2446u
#define FIX_0_390180644 3196u
#define FIX_0_541196100 4433u
#define FIX_0_765366865 6270u
#define FIX_0_899976223 7373u
#define FIX_1_175875602 9633u
#define FIX_1_501321110 12299u
#define FIX_1_847759065 15137u
#define FIX_1_961570560 16069u
#define FIX_2_053119869 16819u
#define FIX_2_562915447 20995u
#define FIX_3_072711026 25172u

/* One 1-D pass over in[0..7]: out[0..7] before descaling. */
static void idct8(const uint32_t in[DCTSIZE], uint32_t out[DCTSIZE])
{
    /* Even part. */
    uint32_t z2 = in[2];
    uint32_t z3 = in[6];
    uint32_t z1 = (z2 + z3) * FIX_0_541196100;
    const uint32_t tmp2 = z1 + z3 * (0u - FIX_1_847759065);
    const uint32_t tmp3 = z1 + z2 * FIX_0_765366865;
    const uint32_t tmp0 = (in[0] + in[4]) << CONST_BITS;
    const uint32_t tmp1 = (in[0] - in[4]) << CONST_BITS;
    const uint32_t tmp10 = tmp0 + tmp3;
    const uint32_t tmp13 = tmp0 - tmp3;
    const uint32_t tmp11 = tmp1 + tmp2;
    const uint32_t tmp12 = tmp1 - tmp2;

    /* Odd part. */
    uint32_t odd0 = in[7];
    uint32_t odd1 = in[5];
    uint32_t odd2 = in[3];
    uint32_t odd3 = in[1];
    z1 = odd0 + odd3;
    z2 = odd1 + odd2;
    z3 = odd0 + odd2;
    uint32_t z4 = odd1 + odd3;
    const uint32_t z5 = (z3 + z4) * FIX_1_175875602;
    odd0 *= FIX_0_298631336;
    odd1 *= FIX_2_053119869;
    odd2 *= FIX_3_072711026;
    odd3 *= FIX_1_501321110;
    z1 *= 0u - FIX_0_899976223;
    z2 *= 0u - FIX_2_562915447;
    z3 = z3 * (0u - FIX_1_961570560) + z5;
    z4 = z4 * (0u - FIX_0_390180644) + z5;
    odd0 += z1 + z3;
    odd1 += z2 + z4;
    odd2 += z2 + z3;
    odd3 += z1 + z4;

    out[0] = tmp10 + odd3;
    out[7] = tmp10 - odd3;
    out[1] = tmp11 + odd2;
    out[6] = tmp11 - odd2;
    out[2] = tmp12 + odd1;
    out[5] = tmp12 - odd1;
    out[3] = tmp13 + odd0;
    out[4] = tmp13 - odd0;
}

static uint32_t descale(uint32_t x, unsigned n)
{
    return (uint32_t)((int32_t)(x + (1u << (n - 1))) >> n);
}

/* Original 0x4c4000 (eax = cinfo, edx = compptr, ebx = coef_block, ecx = output_buf, stack:
 * output_col). Reached through a method pointer, so its registers on return are compared: eax is
 * the end of its workspace on the stack, edx the last output row's start. */
uint32_t vertrix_port_jpeg_idct_8x8_4c4000(PORT_SIGNATURE)
{
    uint8_t stack[8 + 4];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    const uint32_t coef = entry->ebx;
    const uint32_t output_buf = entry->ecx;
    const uint32_t output_col = port_u32(&port, entry->esp, ARGUMENT_OUTPUT_COL);
    const uint32_t range_limit =
        port_u32(&port, entry->eax, CINFO_SAMPLE_RANGE_LIMIT) + CENTERJSAMPLE;
    const uint32_t quant = port_u32(&port, entry->edx, COMPONENT_DCT_TABLE);
    uint32_t workspace[DCTSIZE][DCTSIZE];

    /* Pass 1: columns from the input into the workspace. */
    for (unsigned column = 0; column < DCTSIZE && !port.env.failed; column++)
    {
        uint32_t in[DCTSIZE];
        int ac = 0;
        for (unsigned row = 1; row < DCTSIZE; row++)
        {
            ac |= port_u16(&port, coef, (row * DCTSIZE + column) * 2) != 0;
        }
        for (unsigned row = 0; row < DCTSIZE; row++)
        {
            const unsigned at = row * DCTSIZE + column;
            in[row] = (uint32_t)(int32_t)(int16_t)port_u16(&port, coef, at * 2) *
                      port_u32(&port, quant, at * 4);
            if (!ac)
            {
                break;
            }
        }
        if (!ac)
        {
            for (unsigned row = 0; row < DCTSIZE; row++)
            {
                workspace[row][column] = in[0] << PASS1_BITS;
            }
            continue;
        }
        uint32_t out[DCTSIZE];
        idct8(in, out);
        for (unsigned row = 0; row < DCTSIZE; row++)
        {
            workspace[row][column] = descale(out[row], CONST_BITS - PASS1_BITS);
        }
    }

    /* Pass 2: the workspace's rows to the output. */
    uint32_t outptr = 0;
    for (unsigned row = 0; row < DCTSIZE && !port.env.failed; row++)
    {
        const uint32_t *ws = workspace[row];
        outptr = port_u32(&port, output_buf, row * 4) + output_col;
        if ((ws[1] | ws[2] | ws[3] | ws[4] | ws[5] | ws[6] | ws[7]) == 0)
        {
            const uint32_t value =
                port_u8(&port, range_limit, descale(ws[0], PASS1_BITS + 3) & RANGE_MASK);
            for (unsigned column = 0; column < DCTSIZE; column++)
            {
                port_set8(&port, outptr, column, value);
            }
            continue;
        }
        uint32_t out[DCTSIZE];
        idct8(ws, out);
        for (unsigned column = 0; column < DCTSIZE; column++)
        {
            port_set8(&port, outptr, column,
                      port_u8(&port, range_limit,
                              descale(out[column], CONST_BITS + PASS1_BITS + 3) & RANGE_MASK));
        }
    }
    return port_return(&port, entry->esp - WORKSPACE_END, outptr);
}

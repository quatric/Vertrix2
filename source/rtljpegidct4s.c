#include "rtljpegidct4s.h"

/* libjpeg's jpeg_idct_4x4 (jidctred.c): the inverse DCT giving a 4x4 block from the 8x8
 * coefficients, with dequantisation, for 1/2 scaled decoding. */

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
    WORKSPACE_END = 0x34
};

/* The FIX() constants of jidctred.c. */
#define FIX_0_211164243 1730u
#define FIX_0_509795579 4176u
#define FIX_0_601344887 4926u
#define FIX_0_765366865 6270u
#define FIX_0_899976223 7373u
#define FIX_1_061594337 8697u
#define FIX_1_451774981 11893u
#define FIX_1_847759065 15137u
#define FIX_2_172734803 17799u
#define FIX_2_562915447 20995u

/* The even and odd parts of one row or column: out[0..3] before descaling. */
static void idct4(uint32_t in0, uint32_t in1, uint32_t in2, uint32_t in3, uint32_t in5,
                  uint32_t in6, uint32_t in7, uint32_t out[4])
{
    const uint32_t tmp0 = in0 << (CONST_BITS + 1);
    const uint32_t tmp2 = in2 * FIX_1_847759065 + in6 * (0u - FIX_0_765366865);
    const uint32_t tmp10 = tmp0 + tmp2;
    const uint32_t tmp12 = tmp0 - tmp2;
    const uint32_t odd0 = in7 * (0u - FIX_0_211164243) + in5 * FIX_1_451774981 +
                          in3 * (0u - FIX_2_172734803) + in1 * FIX_1_061594337;
    const uint32_t odd2 = in7 * (0u - FIX_0_509795579) + in5 * (0u - FIX_0_601344887) +
                          in3 * FIX_0_899976223 + in1 * FIX_2_562915447;
    out[0] = tmp10 + odd2;
    out[3] = tmp10 - odd2;
    out[1] = tmp12 + odd0;
    out[2] = tmp12 - odd0;
}

static uint32_t descale(uint32_t x, unsigned n)
{
    return (uint32_t)((int32_t)(x + (1u << (n - 1))) >> n);
}

/* A coefficient times its quantisation multiplier. */
static uint32_t dequantize(Port *port, uint32_t coef, uint32_t quant, unsigned row, unsigned column)
{
    const unsigned at = row * DCTSIZE + column;
    return (uint32_t)(int32_t)(int16_t)port_u16(port, coef, at * 2) * port_u32(port, quant, at * 4);
}

/* Original 0x4c4730 (eax = cinfo, edx = compptr, ebx = coef_block, ecx = output_buf, stack:
 * output_col). Reached through a method pointer, so its registers on return are compared: eax is
 * the end of its workspace on the stack, edx the last output row's start. */
uint32_t vertrix_port_jpeg_idct_4x4_4c4730(PORT_SIGNATURE)
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
    uint32_t workspace[4][DCTSIZE] = {{0}};

    /* Pass 1: columns from the input into the workspace; column 4 is not needed. */
    for (unsigned column = 0; column < DCTSIZE && !port.env.failed; column++)
    {
        if (column == 4)
        {
            continue;
        }
        static const unsigned AC_ROWS[] = {1, 2, 3, 5, 6, 7};
        int ac = 0;
        for (unsigned index = 0; index < 6; index++)
        {
            ac |= port_u16(&port, coef, (AC_ROWS[index] * DCTSIZE + column) * 2) != 0;
        }
        if (!ac)
        {
            const uint32_t dc = dequantize(&port, coef, quant, 0, column) << PASS1_BITS;
            for (unsigned row = 0; row < 4; row++)
            {
                workspace[row][column] = dc;
            }
            continue;
        }
        uint32_t out[4];
        idct4(dequantize(&port, coef, quant, 0, column), dequantize(&port, coef, quant, 1, column),
              dequantize(&port, coef, quant, 2, column), dequantize(&port, coef, quant, 3, column),
              dequantize(&port, coef, quant, 5, column), dequantize(&port, coef, quant, 6, column),
              dequantize(&port, coef, quant, 7, column), out);
        for (unsigned row = 0; row < 4; row++)
        {
            workspace[row][column] = descale(out[row], CONST_BITS - PASS1_BITS + 1);
        }
    }

    /* Pass 2: the workspace's rows to the output. */
    uint32_t outptr = 0;
    for (unsigned row = 0; row < 4 && !port.env.failed; row++)
    {
        const uint32_t *ws = workspace[row];
        outptr = port_u32(&port, output_buf, row * 4) + output_col;
        if ((ws[1] | ws[2] | ws[3] | ws[5] | ws[6] | ws[7]) == 0)
        {
            const uint32_t value =
                port_u8(&port, range_limit, descale(ws[0], PASS1_BITS + 3) & RANGE_MASK);
            for (unsigned column = 0; column < 4; column++)
            {
                port_set8(&port, outptr, column, value);
            }
            continue;
        }
        uint32_t out[4];
        idct4(ws[0], ws[1], ws[2], ws[3], ws[5], ws[6], ws[7], out);
        for (unsigned column = 0; column < 4; column++)
        {
            port_set8(&port, outptr, column,
                      port_u8(&port, range_limit,
                              descale(out[column], CONST_BITS + PASS1_BITS + 3 + 1) & RANGE_MASK));
        }
    }
    return port_return(&port, entry->esp - WORKSPACE_END, outptr);
}

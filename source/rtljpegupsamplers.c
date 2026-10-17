#include "rtljpegupsamplers.h"

/* libjpeg's jinit_upsampler (jdsample.c): makes the upsampler and picks each component's method by
 * how its sampling relates to the largest, with a colour buffer for those that need one. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_DO_FANCY_UPSAMPLING = 0x4c,
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_COMP_INFO = 0xd8,
    CINFO_CCIR601_SAMPLING = 0x12c,
    CINFO_MAX_H_SAMP_FACTOR = 0x134,
    CINFO_MAX_V_SAMP_FACTOR = 0x138,
    CINFO_MIN_DCT_SCALED_SIZE = 0x13c,
    CINFO_UPSAMPLE = 0x1c4,
    ERR_MSG_CODE = 0x14,
    MEM_ALLOC_SMALL = 0,
    MEM_ALLOC_SARRAY = 8,
    JPOOL_IMAGE = 1,
    JERR_CCIR601_NOTIMPL = 0x19,
    JERR_FRACT_SAMPLE_NOTIMPL = 0x26,

    COMPONENT_BYTES = 0x54,
    COMPONENT_H_SAMP_FACTOR = 8,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_DOWNSAMPLED_WIDTH = 0x28,
    COMPONENT_NEEDED = 0x30,

    /* The upsampler: its methods, colour buffers, per-component methods, row group heights and
     * integral expansion factors. */
    UPSAMPLER_BYTES = 0xa0,
    UPSAMPLER_START_PASS = 0,
    UPSAMPLER_UPSAMPLE = 4,
    UPSAMPLER_NEED_CONTEXT_ROWS = 8,
    UPSAMPLER_COLOR_BUF = 0xc,
    UPSAMPLER_METHODS = 0x34,
    UPSAMPLER_ROWGROUP_HEIGHT = 0x64,
    UPSAMPLER_H_EXPAND = 0x8c,
    UPSAMPLER_V_EXPAND = 0x96,

    START_PASS_UPSAMPLE = 0x4c35f0,
    SEP_UPSAMPLE = 0x4c3610,
    FULLSIZE_UPSAMPLE = 0x4c3760,
    NOOP_UPSAMPLE = 0x4c3770,
    INT_UPSAMPLE = 0x4c3780,
    H2V1_UPSAMPLE = 0x4c3850,
    H2V2_UPSAMPLE = 0x4c38b0,
    H2V1_FANCY_UPSAMPLE = 0x4c3950,
    H2V2_FANCY_UPSAMPLE = 0x4c3a30,
    JROUND_UP = 0x4c9840
};

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend and its sign in eax and edx, as
 * the lifted runtime does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

static int32_t remainder_of(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? (a < 0 ? -1 : 0) : a % b;
}

/* ERREXIT through error_exit, a method, with what the original leaves in ebx and ecx. */
static void error_exit(Port *port, uint32_t cinfo, uint32_t code, uint32_t ebx, uint32_t ecx)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, 0), cinfo, err, ebx, ecx);
}

/* Original 0x4c3be0 (eax = cinfo). The memory manager's methods get cinfo, the pool and the size,
 * with the manager (alloc_small) or the largest vertical factor (alloc_sarray) in ecx as the
 * original leaves them. */
uint32_t vertrix_port_jpeg_init_upsampler_4c3be0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
    const uint32_t upsample = port_call(&port, port_u32(&port, memory, MEM_ALLOC_SMALL), cinfo,
                                        JPOOL_IMAGE, UPSAMPLER_BYTES, memory);
    port_set32(&port, cinfo, CINFO_UPSAMPLE, upsample);
    port_set32(&port, upsample, UPSAMPLER_START_PASS, START_PASS_UPSAMPLE);
    port_set32(&port, upsample, UPSAMPLER_UPSAMPLE, SEP_UPSAMPLE);
    port_set32(&port, upsample, UPSAMPLER_NEED_CONTEXT_ROWS, 0);
    if (port_u32(&port, cinfo, CINFO_CCIR601_SAMPLING) != 0)
    {
        error_exit(&port, cinfo, JERR_CCIR601_NOTIMPL, UPSAMPLER_BYTES, memory);
    }
    const int do_fancy = port_u32(&port, cinfo, CINFO_DO_FANCY_UPSAMPLING) != 0 &&
                         (int32_t)port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED_SIZE) > 1;

    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    for (uint32_t ci = 0;
         (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) && !port.env.failed;
         ci++, component += COMPONENT_BYTES)
    {
        /* The sizes of a row group in this component and in the output. */
        const int32_t min_size = (int32_t)port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED_SIZE);
        const int32_t h_in =
            quotient((int32_t)(port_u32(&port, component, COMPONENT_H_SAMP_FACTOR) *
                               port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE)),
                     min_size);
        const int32_t v_in =
            quotient((int32_t)(port_u32(&port, component, COMPONENT_V_SAMP_FACTOR) *
                               port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE)),
                     min_size);
        const int32_t h_out = (int32_t)port_u32(&port, cinfo, CINFO_MAX_H_SAMP_FACTOR);
        const int32_t v_out = (int32_t)port_u32(&port, cinfo, CINFO_MAX_V_SAMP_FACTOR);
        const uint32_t method = upsample + ci * 4 + UPSAMPLER_METHODS;
        port_set32(&port, upsample + ci * 4, UPSAMPLER_ROWGROUP_HEIGHT, (uint32_t)v_in);

        if (port_u32(&port, component, COMPONENT_NEEDED) == 0)
        {
            port_set32(&port, method, 0, NOOP_UPSAMPLE);
            continue;
        }
        if (h_in == h_out && v_in == v_out)
        {
            port_set32(&port, method, 0, FULLSIZE_UPSAMPLE);
            continue;
        }
        if ((uint32_t)h_in * 2 == (uint32_t)h_out && v_in == v_out)
        {
            port_set32(&port, method, 0,
                       do_fancy && port_u32(&port, component, COMPONENT_DOWNSAMPLED_WIDTH) > 2
                           ? H2V1_FANCY_UPSAMPLE
                           : H2V1_UPSAMPLE);
        }
        else if ((uint32_t)h_in * 2 == (uint32_t)h_out && (uint32_t)v_in * 2 == (uint32_t)v_out)
        {
            if (do_fancy && port_u32(&port, component, COMPONENT_DOWNSAMPLED_WIDTH) > 2)
            {
                port_set32(&port, method, 0, H2V2_FANCY_UPSAMPLE);
                port_set32(&port, upsample, UPSAMPLER_NEED_CONTEXT_ROWS, 1);
            }
            else
            {
                port_set32(&port, method, 0, H2V2_UPSAMPLE);
            }
        }
        else if (remainder_of(h_out, h_in) == 0 && remainder_of(v_out, v_in) == 0)
        {
            port_set32(&port, method, 0, INT_UPSAMPLE);
            port_set8(&port, upsample + ci, UPSAMPLER_H_EXPAND, (uint32_t)quotient(h_out, h_in));
            port_set8(&port, upsample + ci, UPSAMPLER_V_EXPAND, (uint32_t)quotient(v_out, v_in));
        }
        else
        {
            error_exit(&port, cinfo, JERR_FRACT_SAMPLE_NOTIMPL, (uint32_t)v_out, (uint32_t)h_out);
        }

        const uint32_t manager = port_u32(&port, cinfo, CINFO_MEM);
        const uint32_t max_h = port_u32(&port, cinfo, CINFO_MAX_H_SAMP_FACTOR);
        const uint32_t width = port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH);
        const uint32_t max_v = port_u32(&port, cinfo, CINFO_MAX_V_SAMP_FACTOR);
        const uint32_t rounded = port_call(&port, JROUND_UP, width, max_h, 0, 0);
        port_set32(&port, upsample + ci * 4, UPSAMPLER_COLOR_BUF,
                   port_call(&port, port_u32(&port, manager, MEM_ALLOC_SARRAY), cinfo, JPOOL_IMAGE,
                             rounded, max_v));
    }
    return port_return(&port, 0, 0);
}

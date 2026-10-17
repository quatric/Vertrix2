#include "rtljpegquantpasses.h"

/* libjpeg's start_pass_2_quant (jquant2.c): sets up the two-pass colour quantizer for its
 * histogram pre-scan or its output pass. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_DITHER_MODE = 0x58,
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_ACTUAL_NUMBER_OF_COLORS = 0x84,
    CINFO_CQUANTIZE = 0x1cc,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    MEM_ALLOC_LARGE = 4,
    JPOOL_IMAGE = 1,
    JDITHER_FS = 2,
    JERR_QUANT_FEW_COLORS = 0x38,
    JERR_QUANT_MANY_COLORS = 0x39,
    MAXNUMCOLORS = 256,

    /* The quantizer: its pass methods, the histogram, whether it needs zeroing, the error
     * array, the odd row flag and the error limit table. */
    QUANTIZE_COLOR_QUANTIZE = 4,
    QUANTIZE_FINISH_PASS = 8,
    QUANTIZE_HISTOGRAM = 0x18,
    QUANTIZE_NEEDS_ZEROED = 0x1c,
    QUANTIZE_FSERRORS = 0x20,
    QUANTIZE_ON_ODD_ROW = 0x24,
    QUANTIZE_ERROR_LIMITER = 0x28,
    /* 32 rows of 64 x 32 histogram cells, two bytes each. */
    HISTOGRAM_ROWS = 32,
    HISTOGRAM_ROW_BYTES = 0x1000,

    PRESCAN_QUANTIZE = 0x4c6ff0,
    FINISH_PASS1 = 0x4c90e0,
    PASS2_FS_DITHER = 0x4c8cd0,
    PASS2_NO_DITHER = 0x4c8be0,
    FINISH_PASS2 = 0x4c93c0,
    JZERO_FAR = 0x4c98f0,
    INIT_ERROR_LIMIT = 0x4c9030
};

/* ERREXIT1 through the error manager's error_exit, a method: the original leaves the colour count
 * in ebx and cinfo in ecx. Returns the error manager, the edx it is handed. */
static uint32_t error_exit(Port *port, uint32_t cinfo, uint32_t code, uint32_t parameter,
                           uint32_t colors)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM, parameter);
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, 0), cinfo, err, colors, cinfo);
    return err;
}

/* Original 0x4c9550 (eax = cinfo, edx = is_pre_scan). Reached through a method pointer, so the eax
 * and edx it leaves are compared: the last callee's eax and the edx it was handed (they keep edx),
 * or with no call the dither mode and is_pre_scan. */
uint32_t vertrix_port_jpeg_quant2_start_pass_4c9550(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t quantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    const uint32_t histogram = port_u32(&port, quantize, QUANTIZE_HISTOGRAM);
    uint32_t eax = 0;
    uint32_t edx = entry->edx;

    if (port_u32(&port, cinfo, CINFO_DITHER_MODE) != 0)
    {
        /* Only Floyd-Steinberg dithering is supported. */
        port_set32(&port, cinfo, CINFO_DITHER_MODE, JDITHER_FS);
    }
    if (entry->edx != 0)
    {
        port_set32(&port, quantize, QUANTIZE_COLOR_QUANTIZE, PRESCAN_QUANTIZE);
        port_set32(&port, quantize, QUANTIZE_FINISH_PASS, FINISH_PASS1);
        port_set32(&port, quantize, QUANTIZE_NEEDS_ZEROED, 1);
    }
    else
    {
        port_set32(&port, quantize, QUANTIZE_COLOR_QUANTIZE,
                   port_u32(&port, cinfo, CINFO_DITHER_MODE) == JDITHER_FS ? PASS2_FS_DITHER
                                                                           : PASS2_NO_DITHER);
        port_set32(&port, quantize, QUANTIZE_FINISH_PASS, FINISH_PASS2);
        const int32_t colors = (int32_t)port_u32(&port, cinfo, CINFO_ACTUAL_NUMBER_OF_COLORS);
        if (colors < 1)
        {
            edx = error_exit(&port, cinfo, JERR_QUANT_FEW_COLORS, 1, (uint32_t)colors);
        }
        if (colors > MAXNUMCOLORS)
        {
            edx = error_exit(&port, cinfo, JERR_QUANT_MANY_COLORS, MAXNUMCOLORS, (uint32_t)colors);
        }
        eax = port_u32(&port, cinfo, CINFO_DITHER_MODE);
        if (eax == JDITHER_FS)
        {
            const uint32_t size = (port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH) + 2) * 6;
            if (port_u32(&port, quantize, QUANTIZE_FSERRORS) == 0)
            {
                /* alloc_large, a method: the original leaves cinfo in ecx. */
                const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
                port_set32(&port, quantize, QUANTIZE_FSERRORS,
                           port_call(&port, port_u32(&port, memory, MEM_ALLOC_LARGE), cinfo,
                                     JPOOL_IMAGE, size, cinfo));
            }
            eax = port_call(&port, JZERO_FAR, port_u32(&port, quantize, QUANTIZE_FSERRORS), size, 0,
                            0);
            edx = size;
            if (port_u32(&port, quantize, QUANTIZE_ERROR_LIMITER) == 0)
            {
                eax = port_call(&port, INIT_ERROR_LIMIT, cinfo, 0, 0, 0);
            }
            port_set32(&port, quantize, QUANTIZE_ON_ODD_ROW, 0);
        }
    }
    if (port_u32(&port, quantize, QUANTIZE_NEEDS_ZEROED) != 0)
    {
        for (uint32_t row = 0; row < HISTOGRAM_ROWS && !port.env.failed; row++)
        {
            eax = port_call(&port, JZERO_FAR, port_u32(&port, histogram, row * 4),
                            HISTOGRAM_ROW_BYTES, 0, 0);
            edx = HISTOGRAM_ROW_BYTES;
        }
        port_set32(&port, quantize, QUANTIZE_NEEDS_ZEROED, 0);
    }
    return port_return(&port, eax, edx);
}

#include "rtljpegquantizers.h"

/* libjpeg's jinit_1pass_quantizer (jquant1.c), with select_ncolors and create_colormap inlined:
 * allocates the one-pass colour quantizer, picks how many values each component gets, builds the
 * colormap, then the colour index table (0x4c6020) and, for Floyd-Steinberg dithering, its
 * workspace (0x4c69c0). */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_OUT_COLOR_SPACE = 0x2c,
    CINFO_DITHER_MODE = 0x58,
    CINFO_DESIRED_NUMBER_OF_COLORS = 0x60,
    CINFO_OUT_COLOR_COMPONENTS = 0x78,
    CINFO_CQUANTIZE = 0x1cc,
    ERR_ERROR_EXIT = 0,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    MEM_ALLOC_SMALL = 0,
    MEM_ALLOC_SARRAY = 8,
    JPOOL_IMAGE = 1,
    JCS_RGB = 2,
    JDITHER_FS = 2,
    MAX_Q_COMPS = 4,
    MAXJSAMPLE = 255,
    JERR_QUANT_COMPONENTS = 0x37,
    JERR_QUANT_FEW_COLORS = 0x38,
    JERR_QUANT_MANY_COLORS = 0x39,
    JTRC_QUANT_3_NCOLORS = 0x5e,
    JTRC_QUANT_NCOLORS = 0x5f,
    TRACE_LEVEL = 1,

    /* The quantizer: its methods, the colormap and its size kept for later passes, the number of
     * values of each component, and the first ordered-dither and Floyd-Steinberg arrays (null:
     * not made yet). */
    QUANTIZE_BYTES = 0x58,
    QUANTIZE_START_PASS = 0,
    QUANTIZE_FINISH_PASS = 8,
    QUANTIZE_NEW_COLOR_MAP = 0xc,
    QUANTIZE_SV_COLORMAP = 0x10,
    QUANTIZE_SV_ACTUAL = 0x14,
    QUANTIZE_NCOLORS = 0x20,
    QUANTIZE_ODITHER = 0x34,
    QUANTIZE_FSERRORS = 0x44,

    /* The components an RGB image adds values to first: green, red, blue. */
    RGB_ORDER = 0x4fffc0,

    START_PASS_1_QUANT = 0x4c6a20,
    FINISH_PASS_1_QUANT = 0x4c6a80,
    NEW_COLOR_MAP_1_QUANT = 0x4c6c70,
    CREATE_COLORINDEX = 0x4c6020,
    ALLOC_FS_WORKSPACE = 0x4c69c0
};

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend in eax, as the lifted runtime
 * does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

/* ERREXIT1 through error_exit, a method, with what the original leaves in ebx and ecx. The lifted
 * error_exit may return; the routine then goes on. */
static void error_exit(Port *port, uint32_t cinfo, uint32_t code, uint32_t parameter, uint32_t ebx,
                       uint32_t ecx)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM, parameter);
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, err, ebx, ecx);
}

static int32_t components_of(Port *port, uint32_t cinfo)
{
    return (int32_t)port_u32(port, cinfo, CINFO_OUT_COLOR_COMPONENTS);
}

/* Original 0x4c6c80 (eax = cinfo). The methods it calls get all four registers compared:
 * alloc_small the size in ebx and the memory manager in ecx; the trace message the component's
 * offset where the last pass stopped in ebx (0, or iroot with no components) and the error
 * manager in ecx; alloc_sarray the number of components in ecx. */
uint32_t vertrix_port_jpeg_one_pass_quantizer_init_4c6c80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;

    const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
    const uint32_t quantize = port_call(&port, port_u32(&port, memory, MEM_ALLOC_SMALL), cinfo,
                                        JPOOL_IMAGE, QUANTIZE_BYTES, memory);
    port_set32(&port, cinfo, CINFO_CQUANTIZE, quantize);
    port_set32(&port, quantize, QUANTIZE_START_PASS, START_PASS_1_QUANT);
    port_set32(&port, quantize, QUANTIZE_FINISH_PASS, FINISH_PASS_1_QUANT);
    port_set32(&port, quantize, QUANTIZE_NEW_COLOR_MAP, NEW_COLOR_MAP_1_QUANT);
    port_set32(&port, quantize, QUANTIZE_FSERRORS, 0);
    port_set32(&port, quantize, QUANTIZE_ODITHER, 0);
    if (components_of(&port, cinfo) > MAX_Q_COMPS)
    {
        error_exit(&port, cinfo, JERR_QUANT_COMPONENTS, MAX_Q_COMPS, QUANTIZE_BYTES, memory);
    }
    if ((int32_t)port_u32(&port, cinfo, CINFO_DESIRED_NUMBER_OF_COLORS) > MAXJSAMPLE + 1)
    {
        error_exit(&port, cinfo, JERR_QUANT_MANY_COLORS, MAXJSAMPLE + 1, QUANTIZE_BYTES, memory);
    }

    /* select_ncolors: iroot is the largest count whose power of the component count stays within
     * the colours asked for, at least 2. */
    const uint32_t quantizer = port_u32(&port, cinfo, CINFO_CQUANTIZE);
    const int32_t components = components_of(&port, cinfo);
    const int32_t max_colors = (int32_t)port_u32(&port, cinfo, CINFO_DESIRED_NUMBER_OF_COLORS);
    uint32_t iroot = 1;
    uint32_t temp;
    do
    {
        iroot++;
        temp = iroot;
        for (int32_t i = 1; i < components; i++)
        {
            temp *= iroot;
        }
    } while ((int32_t)temp <= max_colors);
    iroot--;
    if ((int32_t)iroot < 2)
    {
        error_exit(&port, cinfo, JERR_QUANT_FEW_COLORS, temp, iroot, 1);
    }

    uint32_t total = 1;
    for (int32_t i = 0; i < components && !port.env.failed; i++)
    {
        port_set32(&port, quantizer, QUANTIZE_NCOLORS + i * 4, iroot);
        total *= iroot;
    }
    /* Then one more value for each component in turn (green, red, blue for RGB) while the total
     * stays within the colours asked for. A pass that adds none ends the search, stopping at its
     * first component. */
    int changed = 0;
    do
    {
        changed = 0;
        for (int32_t i = 0; i < components && !port.env.failed; i++)
        {
            const uint32_t j = port_u32(&port, cinfo, CINFO_OUT_COLOR_SPACE) == JCS_RGB
                                   ? port_u32(&port, RGB_ORDER, i * 4)
                                   : (uint32_t)i;
            const uint32_t count = port_u32(&port, quantizer, QUANTIZE_NCOLORS + j * 4);
            const uint32_t more = (uint32_t)quotient((int32_t)total, (int32_t)count) * (count + 1);
            if ((int32_t)more > max_colors)
            {
                break;
            }
            port_set32(&port, quantizer, QUANTIZE_NCOLORS + j * 4, count + 1);
            total = more;
            changed = 1;
        }
    } while (changed && !port.env.failed);

    if (components_of(&port, cinfo) == 3)
    {
        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
        port_set32(&port, err, ERR_MSG_PARM, total);
        port_set32(&port, err, ERR_MSG_PARM + 4, port_u32(&port, quantizer, QUANTIZE_NCOLORS));
        port_set32(&port, err, ERR_MSG_PARM + 8, port_u32(&port, quantizer, QUANTIZE_NCOLORS + 4));
        port_set32(&port, err, ERR_MSG_PARM + 12, port_u32(&port, quantizer, QUANTIZE_NCOLORS + 8));
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JTRC_QUANT_3_NCOLORS);
    }
    else
    {
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JTRC_QUANT_NCOLORS);
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM, total);
    }
    const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
    port_call(&port, port_u32(&port, err, ERR_EMIT_MESSAGE), cinfo, TRACE_LEVEL,
              components > 0 ? 0 : iroot, err);

    /* create_colormap: a row per component, the rightmost component changing fastest. */
    const uint32_t memory_now = port_u32(&port, cinfo, CINFO_MEM);
    const uint32_t colormap =
        port_call(&port, port_u32(&port, memory_now, MEM_ALLOC_SARRAY), cinfo, JPOOL_IMAGE, total,
                  port_u32(&port, cinfo, CINFO_OUT_COLOR_COMPONENTS));
    int32_t blkdist = (int32_t)total;
    for (int32_t i = 0; i < components_of(&port, cinfo) && !port.env.failed; i++)
    {
        const int32_t nci = (int32_t)port_u32(&port, quantizer, QUANTIZE_NCOLORS + i * 4);
        const int32_t blksize = quotient(blkdist, nci);
        if (nci > 0)
        {
            /* output_value: (j * MAXJSAMPLE + maxj / 2) / maxj, kept as a running numerator. */
            const int32_t maxj = nci - 1;
            uint32_t numerator = (uint32_t)(maxj / 2);
            for (int32_t j = 0; j < nci && !port.env.failed; j++, numerator += MAXJSAMPLE)
            {
                const uint32_t value = (uint32_t)quotient((int32_t)numerator, maxj) & 0xff;
                for (int32_t ptr = (int32_t)((uint32_t)j * (uint32_t)blksize);
                     ptr < (int32_t)total && !port.env.failed;
                     ptr = (int32_t)((uint32_t)ptr + (uint32_t)blkdist))
                {
                    for (int32_t k = 0; k < blksize && !port.env.failed; k++)
                    {
                        port_set8(&port, port_u32(&port, colormap, i * 4), (uint32_t)(ptr + k),
                                  value);
                    }
                }
            }
        }
        blkdist = blksize;
    }
    port_set32(&port, quantizer, QUANTIZE_SV_COLORMAP, colormap);
    port_set32(&port, quantizer, QUANTIZE_SV_ACTUAL, total);

    port_call(&port, CREATE_COLORINDEX, cinfo, 0, 0, 0);
    if (port_u32(&port, cinfo, CINFO_DITHER_MODE) == JDITHER_FS)
    {
        port_call(&port, ALLOC_FS_WORKSPACE, cinfo, 0, 0, 0);
    }
    return port_return(&port, 0, 0);
}

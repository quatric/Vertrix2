#include "rtljpegquant1starts.h"

/* libjpeg's start_pass_1_quant (jquant1.c), with create_odither_tables and make_odither_array
 * inlined: installs the one-pass quantizer's colormap and picks its quantize routine by the dither
 * mode, building the ordered-dither tables or clearing the Floyd-Steinberg errors. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_DITHER_MODE = 0x58,
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_OUT_COLOR_COMPONENTS = 0x78,
    CINFO_ACTUAL_NUMBER_OF_COLORS = 0x84,
    CINFO_COLORMAP = 0x88,
    CINFO_CQUANTIZE = 0x1cc,
    ERR_ERROR_EXIT = 0,
    ERR_MSG_CODE = 0x14,
    MEM_ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,
    JDITHER_NONE = 0,
    JDITHER_ORDERED = 1,
    JDITHER_FS = 2,
    JERR_NOT_COMPILED = 0x30,
    MAXJSAMPLE = 255,

    /* The quantizer: its quantize method, the colormap and its size kept for later passes, whether
     * the colour index has the ordered dither's padding, the values per component, the ordered
     * dither's row and tables, and the Floyd-Steinberg errors and row parity. */
    QUANTIZE_COLOR_QUANTIZE = 4,
    QUANTIZE_SV_COLORMAP = 0x10,
    QUANTIZE_SV_ACTUAL = 0x14,
    QUANTIZE_IS_PADDED = 0x1c,
    QUANTIZE_NCOLORS = 0x20,
    QUANTIZE_ROW_INDEX = 0x30,
    QUANTIZE_ODITHER = 0x34,
    QUANTIZE_FSERRORS = 0x44,
    QUANTIZE_ON_ODD_ROW = 0x54,

    /* The 16 x 16 ordered-dither matrix: an int per cell, and the cells' fill order (bytes). */
    ODITHER_CELLS = 256,
    ODITHER_BYTES = ODITHER_CELLS * 4,
    BASE_DITHER_MATRIX = 0x4fffd0,
    FSERROR_BYTES = 2,

    COLOR_QUANTIZE = 0x4c63a0,
    COLOR_QUANTIZE3 = 0x4c6460,
    QUANTIZE_ORD_DITHER = 0x4c6510,
    QUANTIZE3_ORD_DITHER = 0x4c6640,
    QUANTIZE_FS_DITHER = 0x4c67a0,
    CREATE_COLORINDEX = 0x4c6020,
    ALLOC_FS_WORKSPACE = 0x4c69c0,
    JZERO_FAR = 0x4c98f0
};

/* idiv: an invalid one (by 0, or overflowing) leaves the dividend in eax, as the lifted runtime
 * does. */
static int32_t quotient(int32_t a, int32_t b)
{
    return b == 0 || (a == INT32_MIN && b == -1) ? a : a / b;
}

static int32_t components_of(Port *port, uint32_t cinfo)
{
    return (int32_t)port_u32(port, cinfo, CINFO_OUT_COLOR_COMPONENTS);
}

/* make_odither_array: the dither value of each cell for a component of `ncolors` values,
 * (255 - 2 * its fill order) * 255 / (512 * (ncolors - 1)), rounded towards zero. alloc_small, a
 * method, gets ncolors in ecx as the original leaves it. */
static uint32_t make_odither_array(Port *port, uint32_t cinfo, uint32_t ncolors)
{
    const uint32_t memory = port_u32(port, cinfo, CINFO_MEM);
    const uint32_t odither = port_call(port, port_u32(port, memory, MEM_ALLOC_SMALL), cinfo,
                                       JPOOL_IMAGE, ODITHER_BYTES, ncolors);
    const int32_t den = (int32_t)((ncolors - 1) << 9);
    for (uint32_t cell = 0; cell < ODITHER_CELLS && !port->env.failed; cell++)
    {
        const int32_t num =
            (int32_t)(ODITHER_CELLS - 1 - 2 * port_u8(port, BASE_DITHER_MATRIX, cell)) * MAXJSAMPLE;
        const int32_t value = num < 0 ? -quotient(-num, den) : quotient(num, den);
        port_set32(port, odither, cell * 4, (uint32_t)value);
    }
    return odither;
}

/* Original 0x4c6a20 (eax = cinfo, edx = is_pre_scan, unused). Reached through a method pointer,
 * so the eax and edx it leaves are compared:
 * - no dither: the mode (0) and the caller's edx;
 * - ordered dither with its tables made: the mode or 0x4c6020's eax, and the caller's edx; with
 *   tables to make, the last component's slot in the quantizer (the quantizer without
 *   components, edx then the component count) and cinfo;
 * - Floyd-Steinberg: the component count, and the bytes cleared per component (the first error
 *   array without components);
 * - another mode: error_exit's eax (it gets the quantizer in ebx and the caller's ecx) and the
 *   error manager. */
uint32_t vertrix_port_jpeg_quant1_start_pass_4c6a20(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t quantize = port_u32(&port, cinfo, CINFO_CQUANTIZE);

    port_set32(&port, cinfo, CINFO_COLORMAP, port_u32(&port, quantize, QUANTIZE_SV_COLORMAP));
    port_set32(&port, cinfo, CINFO_ACTUAL_NUMBER_OF_COLORS,
               port_u32(&port, quantize, QUANTIZE_SV_ACTUAL));
    const uint32_t mode = port_u32(&port, cinfo, CINFO_DITHER_MODE);

    if (mode == JDITHER_NONE)
    {
        port_set32(&port, quantize, QUANTIZE_COLOR_QUANTIZE,
                   components_of(&port, cinfo) == 3 ? COLOR_QUANTIZE3 : COLOR_QUANTIZE);
        return port_return(&port, mode, entry->edx);
    }

    if (mode == JDITHER_ORDERED)
    {
        port_set32(&port, quantize, QUANTIZE_COLOR_QUANTIZE,
                   components_of(&port, cinfo) == 3 ? QUANTIZE3_ORD_DITHER : QUANTIZE_ORD_DITHER);
        port_set32(&port, quantize, QUANTIZE_ROW_INDEX, 0);
        uint32_t eax = mode;
        if (port_u32(&port, quantize, QUANTIZE_IS_PADDED) == 0)
        {
            /* The colour index was made without padding: make it again with it. */
            eax = port_call(&port, CREATE_COLORINDEX, cinfo, 0, 0, 0);
        }
        if (port_u32(&port, quantize, QUANTIZE_ODITHER) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }

        /* create_odither_tables: a component shares the table of the first one before it with as
         * many values. */
        const uint32_t quantizer = port_u32(&port, cinfo, CINFO_CQUANTIZE);
        const int32_t components = components_of(&port, cinfo);
        if (components <= 0)
        {
            return port_return(&port, quantizer, (uint32_t)components);
        }
        uint32_t slot = quantizer;
        for (int32_t i = 0; i < components_of(&port, cinfo) && !port.env.failed; i++)
        {
            slot = quantizer + (uint32_t)i * 4;
            const uint32_t ncolors = port_u32(&port, slot, QUANTIZE_NCOLORS);
            uint32_t odither = 0;
            for (int32_t j = 0; j < i && !port.env.failed; j++)
            {
                if (port_u32(&port, quantizer + (uint32_t)j * 4, QUANTIZE_NCOLORS) == ncolors)
                {
                    odither = port_u32(&port, quantizer + (uint32_t)j * 4, QUANTIZE_ODITHER);
                    break;
                }
            }
            if (odither == 0)
            {
                odither = make_odither_array(&port, cinfo, ncolors);
            }
            port_set32(&port, slot, QUANTIZE_ODITHER, odither);
        }
        return port_return(&port, slot, cinfo);
    }

    if (mode == JDITHER_FS)
    {
        port_set32(&port, quantize, QUANTIZE_COLOR_QUANTIZE, QUANTIZE_FS_DITHER);
        const uint32_t first = port_u32(&port, quantize, QUANTIZE_FSERRORS);
        port_set32(&port, quantize, QUANTIZE_ON_ODD_ROW, 0);
        if (first == 0)
        {
            port_call(&port, ALLOC_FS_WORKSPACE, cinfo, 0, 0, 0);
        }
        /* The errors of a row with a column on each side, cleared for every component. */
        const uint32_t bytes = (port_u32(&port, cinfo, CINFO_OUTPUT_WIDTH) + 2) * FSERROR_BYTES;
        uint32_t edx = first;
        for (int32_t i = 0; i < components_of(&port, cinfo) && !port.env.failed; i++)
        {
            port_call(&port, JZERO_FAR, port_u32(&port, quantize, QUANTIZE_FSERRORS + i * 4), bytes,
                      0, 0);
            edx = bytes;
        }
        return port_return(&port, (uint32_t)components_of(&port, cinfo), edx);
    }

    /* ERREXIT(JERR_NOT_COMPILED) through error_exit, a method. */
    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_NOT_COMPILED);
    const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
    const uint32_t result =
        port_call(&port, port_u32(&port, err, ERR_ERROR_EXIT), cinfo, err, quantize, entry->ecx);
    return port_return(&port, result, err);
}

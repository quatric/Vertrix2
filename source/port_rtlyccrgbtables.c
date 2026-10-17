#include "port_rtlyccrgbtables.h"

/* libjpeg's build_ycc_rgb_table (jdcolor.c): the YCbCr to RGB lookups of the colour deconverter. */

enum
{
    /* The decompressor: its memory manager and its colour deconverter. */
    CINFO_MEM = 4,
    CINFO_CCONVERT = 0x1c8,
    /* The memory manager's first method, alloc_small(cinfo, pool, size). */
    ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,
    /* The deconverter's tables. */
    CR_R_TAB = 8,
    CB_B_TAB = 0xc,
    CR_G_TAB = 0x10,
    CB_G_TAB = 0x14,

    MAXJSAMPLE = 255,
    CENTERJSAMPLE = 128,
    TABLE_BYTES = (MAXJSAMPLE + 1) * 4,
    SCALEBITS = 16,
    ONE_HALF = 1 << (SCALEBITS - 1),
    /* FIX(1.40200), FIX(1.77200), FIX(0.71414) and FIX(0.34414). */
    FIX_1_40200 = 0x166e9,
    FIX_1_77200 = 0x1c5a2,
    FIX_0_71414 = 0xb6d2,
    FIX_0_34414 = 0x581a
};

/* alloc_small(cinfo, JPOOL_IMAGE, 256 dwords). A method call: like the original it leaves the
 * size in ebx and the deconverter in ecx. */
static uint32_t alloc_table(Port *port, uint32_t cinfo, uint32_t cconvert)
{
    const uint32_t mem = port_u32(port, cinfo, CINFO_MEM);
    return port_call(port, port_u32(port, mem, ALLOC_SMALL), cinfo, JPOOL_IMAGE, TABLE_BYTES,
                     cconvert);
}

/* Original 0x4bb170 (eax = cinfo): allocate the deconverter's four tables and fill them for every
 * sample x - 128: Cr_r = (1.402 x + 0.5) >> 16 and Cb_b = (1.772 x + 0.5) >> 16 (in 16.16 fixed
 * point, arithmetic shifts), Cr_g = -0.71414 x and Cb_g = -0.34414 x + 0.5, left scaled. The table
 * pointers are read from the deconverter for every entry, as the original does. */
uint32_t vertrix_port_jpeg_build_ycc_rgb_table_4bb170(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t cconvert = port_u32(&port, cinfo, CINFO_CCONVERT);
    port_set32(&port, cconvert, CR_R_TAB, alloc_table(&port, cinfo, cconvert));
    port_set32(&port, cconvert, CB_B_TAB, alloc_table(&port, cinfo, cconvert));
    port_set32(&port, cconvert, CR_G_TAB, alloc_table(&port, cinfo, cconvert));
    port_set32(&port, cconvert, CB_G_TAB, alloc_table(&port, cinfo, cconvert));
    for (uint32_t i = 0; i <= MAXJSAMPLE && !port.env.failed; i++)
    {
        const int32_t x = (int32_t)i - CENTERJSAMPLE;
        port_set32(&port, port_u32(&port, cconvert, CR_R_TAB) + i * 4, 0,
                   (uint32_t)((FIX_1_40200 * x + ONE_HALF) >> SCALEBITS));
        port_set32(&port, port_u32(&port, cconvert, CB_B_TAB) + i * 4, 0,
                   (uint32_t)((FIX_1_77200 * x + ONE_HALF) >> SCALEBITS));
        port_set32(&port, port_u32(&port, cconvert, CR_G_TAB) + i * 4, 0,
                   (uint32_t)(-FIX_0_71414 * x));
        port_set32(&port, port_u32(&port, cconvert, CB_G_TAB) + i * 4, 0,
                   (uint32_t)(-FIX_0_34414 * x + ONE_HALF));
    }
    return port_return(&port, 0, 0);
}

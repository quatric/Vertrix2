#include "rtljpegidctpasses.h"

/* libjpeg's start_pass of the inverse DCT manager (jddctmgr.c): picks each component's IDCT by its
 * scaled DCT size and, when its method changes, builds the component's multiplier table from its
 * quantisation table. */

enum
{
    CINFO_ERR = 0,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_DCT_METHOD = 0x48,
    CINFO_COMP_INFO = 0xd8,
    CINFO_IDCT = 0x1c0,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    JERR_BAD_DCTSIZE = 7,
    JERR_NOT_COMPILED = 0x30,

    COMPONENT_BYTES = 0x54,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_NEEDED = 0x30,
    COMPONENT_QUANT_TABLE = 0x4c,
    COMPONENT_DCT_TABLE = 0x50,
    DCTSIZE2 = 64,

    /* The manager: each component's inverse_DCT, then its current method. */
    IDCT_INVERSE_DCT = 4,
    IDCT_CUR_METHOD = 0x2c,

    JDCT_ISLOW = 0,
    IDCT_1X1 = 0x4c4cc0,
    IDCT_2X2 = 0x4c4b00,
    IDCT_4X4 = 0x4c4730,
    IDCT_ISLOW = 0x4c4000
};

/* ERREXIT through error_exit, a method: the original leaves its loop registers in ebx and ecx. */
static void error_exit(Port *port, uint32_t cinfo, uint32_t ebx, uint32_t ecx)
{
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, 0), cinfo, err, ebx, ecx);
}

/* Original 0x4bb870 (eax = cinfo). An unsupported size or method is an error, and the component
 * keeps the previous component's choice (none for the first). Only the slow integer method is
 * built in, so the method is always it. Reached through a method pointer, so its eax and edx are
 * compared: edx is the caller's (saved), eax the last component's IDCT, or the end of the table
 * it copied (the manager with no components). In ebx and ecx the error exit gets the caller's for
 * the first component, then the index and the manager's slot. */
uint32_t vertrix_port_jpeg_idct_start_pass_4bb870(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t idct = port_u32(&port, cinfo, CINFO_IDCT);
    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    uint32_t method_ptr = 0;
    const uint32_t method = JDCT_ISLOW;
    uint32_t eax = idct;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;

    for (uint32_t ci = 0;
         (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) && !port.env.failed;
         ci++, component += COMPONENT_BYTES)
    {
        const uint32_t slot = idct + ci * 4;
        switch (port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE))
        {
            case 1:
                method_ptr = IDCT_1X1;
                break;
            case 2:
                method_ptr = IDCT_2X2;
                break;
            case 4:
                method_ptr = IDCT_4X4;
                break;
            case 8:
                if (port_u32(&port, cinfo, CINFO_DCT_METHOD) == JDCT_ISLOW)
                {
                    method_ptr = IDCT_ISLOW;
                }
                else
                {
                    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE,
                               JERR_NOT_COMPILED);
                    error_exit(&port, cinfo, ebx, ecx);
                }
                break;
            default:
                port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE,
                           JERR_BAD_DCTSIZE);
                port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM,
                           port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE));
                error_exit(&port, cinfo, ebx, ecx);
                break;
        }
        port_set32(&port, slot, IDCT_INVERSE_DCT, method_ptr);
        eax = method_ptr;
        ebx = ci + 1;
        ecx = slot + 4;

        /* Components not needed in this scan, and those whose method is unchanged, keep their
         * table; so does one without a quantisation table yet. */
        if (port_u32(&port, component, COMPONENT_NEEDED) == 0 ||
            port_u32(&port, slot, IDCT_CUR_METHOD) == method)
        {
            continue;
        }
        const uint32_t qtbl = port_u32(&port, component, COMPONENT_QUANT_TABLE);
        if (qtbl == 0)
        {
            continue;
        }
        port_set32(&port, slot, IDCT_CUR_METHOD, method);
        const uint32_t table = port_u32(&port, component, COMPONENT_DCT_TABLE);
        for (uint32_t i = 0; i < DCTSIZE2 && !port.env.failed; i++)
        {
            port_set32(&port, table, i * 4, port_u16(&port, qtbl, i * 2));
        }
        eax = qtbl + DCTSIZE2 * 2;
    }
    return port_return(&port, eax, entry->edx);
}

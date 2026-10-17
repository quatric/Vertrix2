#include "rtljpegprogressivestarts.h"

/* libjpeg's start_pass_phuff_decoder (jdphuff.c): checks a progressive scan's parameters, updates
 * the progression status of its components, picks the MCU decoder and builds the Huffman tables
 * the scan uses. */

enum
{
    CINFO_ERR = 0,
    CINFO_COEF_BITS = 0xa0,
    CINFO_RESTART_INTERVAL = 0x114,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_CUR_COMP_INFO = 0x14c,
    CINFO_SS = 0x190,
    CINFO_SE = 0x194,
    CINFO_AH = 0x198,
    CINFO_AL = 0x19c,
    CINFO_ENTROPY = 0x1bc,
    ERR_ERROR_EXIT = 0,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    JERR_BAD_PROGRESSION = 0x10,
    JWRN_BOGUS_PROGRESSION = 0x73,
    WARNING_LEVEL = 0xffffffffu,
    DCTSIZE2 = 64,
    MAX_AL = 13,
    /* coef_bits: 64 ints per component. */
    COEF_BITS_ROW = DCTSIZE2 * 4,

    COMPONENT_INDEX = 4,
    COMPONENT_DC_TBL_NO = 0x14,
    COMPONENT_AC_TBL_NO = 0x18,

    /* The progressive entropy decoder: its MCU decoder, the insufficient data flag, the bit
     * buffer, the end-of-band run, the DC predictions, the restart count, the derived tables and
     * the AC scan's one table. */
    ENTROPY_DECODE_MCU = 4,
    ENTROPY_INSUFFICIENT_DATA = 8,
    ENTROPY_GET_BUFFER = 0xc,
    ENTROPY_BITS_LEFT = 0x10,
    ENTROPY_EOBRUN = 0x14,
    ENTROPY_LAST_DC_VAL = 0x18,
    ENTROPY_RESTARTS_TO_GO = 0x28,
    ENTROPY_DERIVED_TBLS = 0x2c,
    ENTROPY_AC_DERIVED_TBL = 0x3c,

    DECODE_MCU_DC_FIRST = 0x4c2780,
    DECODE_MCU_AC_FIRST = 0x4c29c0,
    DECODE_MCU_DC_REFINE = 0x4c2c50,
    DECODE_MCU_AC_REFINE = 0x4c2d60,
    MAKE_D_DERIVED_TBL = 0x4bbc00
};

static uint32_t field(Port *port, uint32_t cinfo, uint32_t offset)
{
    return port_u32(port, cinfo, offset);
}

/* WARNMS2(JWRN_BOGUS_PROGRESSION) through emit_message, a method, with what the original leaves in
 * ebx and ecx (the error manager, or for a coefficient its coef_bits entry's address). */
static void bogus_progression(Port *port, uint32_t cinfo, uint32_t cindex, uint32_t coefi,
                              uint32_t ebx, int at_entry, uint32_t at)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, JWRN_BOGUS_PROGRESSION);
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM, cindex);
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM + 4, coefi);
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, ERR_EMIT_MESSAGE), cinfo, WARNING_LEVEL, ebx,
              at_entry ? at : err);
}

/* Original 0x4c23f0 (eax = cinfo). Reached through a method pointer, so the eax and edx it leaves
 * are compared: the restart interval and the caller's edx. The methods it calls get what the
 * original leaves in the registers: error_exit Ss in edx and Ah in ebx; the warning for an AC scan
 * without a DC scan before it the component count in ebx for the first component, for a later one
 * the coefficient where the last one's loop ended; the warning for a coefficient the coefficient in
 * ebx and its coef_bits entry's address in ecx. The lifted error_exit may return; the routine then
 * goes on. */
uint32_t vertrix_port_jpeg_progressive_huff_start_pass_4c23f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t entropy = field(&port, cinfo, CINFO_ENTROPY);
    const uint32_t ss = field(&port, cinfo, CINFO_SS);
    const int is_dc_band = ss == 0;

    /* Validate the scan's parameters. */
    int bad = 0;
    if (is_dc_band)
    {
        bad = field(&port, cinfo, CINFO_SE) != 0;
    }
    else
    {
        const int32_t se = (int32_t)field(&port, cinfo, CINFO_SE);
        bad = (int32_t)ss > se || se >= (int32_t)DCTSIZE2;
        /* AC scans may have only one component. */
        if (field(&port, cinfo, CINFO_COMPS_IN_SCAN) != 1)
        {
            bad = 1;
        }
    }
    const uint32_t ah = field(&port, cinfo, CINFO_AH);
    if (ah != 0 && ah - 1 != field(&port, cinfo, CINFO_AL))
    {
        bad = 1;
    }
    if ((int32_t)field(&port, cinfo, CINFO_AL) > (int32_t)MAX_AL || bad)
    {
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_BAD_PROGRESSION);
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM, ss);
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM + 4,
                   field(&port, cinfo, CINFO_SE));
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM + 8,
                   field(&port, cinfo, CINFO_AH));
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM + 12,
                   field(&port, cinfo, CINFO_AL));
        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
        port_call(&port, port_u32(&port, err, ERR_ERROR_EXIT), cinfo, ss, ah, err);
    }

    /* Update the progression status, warning when the scan order is not legal. */
    uint32_t ebx = field(&port, cinfo, CINFO_COMPS_IN_SCAN);
    for (int32_t ci = 0; ci < (int32_t)field(&port, cinfo, CINFO_COMPS_IN_SCAN) && !port.env.failed;
         ci++)
    {
        const uint32_t component = port_u32(&port, cinfo, CINFO_CUR_COMP_INFO + ci * 4);
        const uint32_t cindex = port_u32(&port, component, COMPONENT_INDEX);
        const uint32_t coef_bits = field(&port, cinfo, CINFO_COEF_BITS) + (cindex << 8);
        if (!is_dc_band && (int32_t)port_u32(&port, coef_bits, 0) < 0)
        {
            /* An AC scan without a DC scan before it. */
            bogus_progression(&port, cinfo, cindex, 0, ebx, 0, 0);
        }
        int32_t coefi = (int32_t)field(&port, cinfo, CINFO_SS);
        for (; coefi <= (int32_t)field(&port, cinfo, CINFO_SE) && !port.env.failed; coefi++)
        {
            const uint32_t at = coef_bits + (uint32_t)coefi * 4;
            const int32_t bits = (int32_t)port_u32(&port, at, 0);
            const uint32_t expected = bits < 0 ? 0 : (uint32_t)bits;
            if (expected != field(&port, cinfo, CINFO_AH))
            {
                bogus_progression(&port, cinfo, cindex, (uint32_t)coefi, (uint32_t)coefi, 1, at);
            }
            port_set32(&port, at, 0, field(&port, cinfo, CINFO_AL));
        }
        ebx = (uint32_t)coefi;
    }

    uint32_t decode_mcu;
    if (field(&port, cinfo, CINFO_AH) == 0)
    {
        decode_mcu = is_dc_band ? DECODE_MCU_DC_FIRST : DECODE_MCU_AC_FIRST;
    }
    else
    {
        decode_mcu = is_dc_band ? DECODE_MCU_DC_REFINE : DECODE_MCU_AC_REFINE;
    }
    port_set32(&port, entropy, ENTROPY_DECODE_MCU, decode_mcu);

    /* The derived tables the scan needs (DC refinement needs none), and DC predictions of 0. */
    for (int32_t ci = 0; ci < (int32_t)field(&port, cinfo, CINFO_COMPS_IN_SCAN) && !port.env.failed;
         ci++)
    {
        const uint32_t component = port_u32(&port, cinfo, CINFO_CUR_COMP_INFO + ci * 4);
        if (!is_dc_band)
        {
            const uint32_t tbl = port_u32(&port, component, COMPONENT_AC_TBL_NO);
            port_call(&port, MAKE_D_DERIVED_TBL, cinfo, 0, tbl,
                      entropy + ENTROPY_DERIVED_TBLS + tbl * 4);
            port_set32(&port, entropy, ENTROPY_AC_DERIVED_TBL,
                       port_u32(&port, entropy + tbl * 4, ENTROPY_DERIVED_TBLS));
        }
        else if (field(&port, cinfo, CINFO_AH) == 0)
        {
            const uint32_t tbl = port_u32(&port, component, COMPONENT_DC_TBL_NO);
            port_call(&port, MAKE_D_DERIVED_TBL, cinfo, 1, tbl,
                      entropy + ENTROPY_DERIVED_TBLS + tbl * 4);
        }
        port_set32(&port, entropy + ci * 4, ENTROPY_LAST_DC_VAL, 0);
    }

    port_set32(&port, entropy, ENTROPY_BITS_LEFT, 0);
    port_set32(&port, entropy, ENTROPY_GET_BUFFER, 0);
    port_set32(&port, entropy, ENTROPY_INSUFFICIENT_DATA, 0);
    port_set32(&port, entropy, ENTROPY_EOBRUN, 0);
    const uint32_t restart_interval = field(&port, cinfo, CINFO_RESTART_INTERVAL);
    port_set32(&port, entropy, ENTROPY_RESTARTS_TO_GO, restart_interval);
    return port_return(&port, restart_interval, entry->edx);
}

#include "rtljpegscansetups.h"

/* libjpeg's start_input_pass (jdinput.c), with per_scan_setup and latch_quant_tables inlined:
 * computes the scan's MCU layout, saves each component's quantisation table, starts the entropy
 * decoder's and the coefficient controller's passes and makes the coefficient controller consume
 * the input. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_IMAGE_WIDTH = 0x1c,
    CINFO_IMAGE_HEIGHT = 0x20,
    CINFO_QUANT_TBL_PTRS = 0xa4,
    CINFO_MAX_H_SAMP_FACTOR = 0x134,
    CINFO_MAX_V_SAMP_FACTOR = 0x138,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_CUR_COMP_INFO = 0x14c,
    CINFO_MCUS_PER_ROW = 0x15c,
    CINFO_MCU_ROWS_IN_SCAN = 0x160,
    CINFO_BLOCKS_IN_MCU = 0x164,
    CINFO_MCU_MEMBERSHIP = 0x168,
    CINFO_COEF = 0x1ac,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_ENTROPY = 0x1bc,
    ERR_ERROR_EXIT = 0,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    MEM_ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,

    /* jpeg_component_info. */
    COMPONENT_H_SAMP_FACTOR = 8,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_QUANT_TBL_NO = 0x10,
    COMPONENT_WIDTH_IN_BLOCKS = 0x1c,
    COMPONENT_HEIGHT_IN_BLOCKS = 0x20,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_MCU_WIDTH = 0x34,
    COMPONENT_MCU_HEIGHT = 0x38,
    COMPONENT_MCU_BLOCKS = 0x3c,
    COMPONENT_MCU_SAMPLE_WIDTH = 0x40,
    COMPONENT_LAST_COL_WIDTH = 0x44,
    COMPONENT_LAST_ROW_HEIGHT = 0x48,
    COMPONENT_QUANT_TABLE = 0x4c,

    /* The entropy decoder's and the coefficient controller's start_pass, the coefficient
     * controller's consume_data and the input controller's consume_input. */
    ENTROPY_START_PASS = 0,
    COEF_START_INPUT_PASS = 0,
    COEF_CONSUME_DATA = 4,
    INPUTCTL_CONSUME_INPUT = 0,

    DCTSIZE = 8,
    MAX_COMPS_IN_SCAN = 4,
    D_MAX_BLOCKS_IN_MCU = 10,
    NUM_QUANT_TBLS = 4,
    JQUANT_TBL_BYTES = 0x84,
    JERR_BAD_MCU_SIZE = 0xd,
    JERR_COMPONENT_COUNT = 0x1a,
    JERR_NO_QUANT_TABLE = 0x34,

    JDIV_ROUND_UP = 0x4c9820
};

static uint32_t field(Port *port, uint32_t cinfo, uint32_t offset)
{
    return port_u32(port, cinfo, offset);
}

/* div: an invalid one (by 0) leaves the 0 the original puts in edx as the remainder. */
static uint32_t remainder_of(uint32_t a, uint32_t b)
{
    return b != 0 ? a % b : 0;
}

/* A remainder of the blocks over the factor, the factor itself when there is none. */
static uint32_t last_blocks(uint32_t blocks, uint32_t factor)
{
    const uint32_t rest = remainder_of(blocks, factor);
    return rest != 0 ? rest : factor;
}

/* per_scan_setup. The error exits (error_exit, a method, which in the lifted runtime may return:
 * the routine then goes on) get the error manager in edx and the caller's ebx for a bad component
 * count, the MCU's block count in edx and the error manager in ebx for too many blocks. */
static void per_scan_setup(Port *port, uint32_t cinfo, uint32_t caller_ebx)
{
    const int32_t comps_in_scan = (int32_t)field(port, cinfo, CINFO_COMPS_IN_SCAN);
    if (comps_in_scan == 1)
    {
        /* A noninterleaved scan: one block per MCU. */
        const uint32_t component = field(port, cinfo, CINFO_CUR_COMP_INFO);
        port_set32(port, cinfo, CINFO_MCUS_PER_ROW,
                   port_u32(port, component, COMPONENT_WIDTH_IN_BLOCKS));
        port_set32(port, cinfo, CINFO_MCU_ROWS_IN_SCAN,
                   port_u32(port, component, COMPONENT_HEIGHT_IN_BLOCKS));
        port_set32(port, component, COMPONENT_MCU_SAMPLE_WIDTH,
                   port_u32(port, component, COMPONENT_DCT_SCALED_SIZE));
        const uint32_t v = port_u32(port, component, COMPONENT_V_SAMP_FACTOR);
        const uint32_t last_row =
            last_blocks(port_u32(port, component, COMPONENT_HEIGHT_IN_BLOCKS), v);
        port_set32(port, component, COMPONENT_MCU_WIDTH, 1);
        port_set32(port, component, COMPONENT_MCU_HEIGHT, 1);
        port_set32(port, component, COMPONENT_MCU_BLOCKS, 1);
        port_set32(port, component, COMPONENT_LAST_COL_WIDTH, 1);
        port_set32(port, component, COMPONENT_LAST_ROW_HEIGHT, last_row);
        port_set32(port, cinfo, CINFO_BLOCKS_IN_MCU, 1);
        port_set32(port, cinfo, CINFO_MCU_MEMBERSHIP, 0);
        return;
    }

    if (comps_in_scan <= 0 || comps_in_scan > (int32_t)MAX_COMPS_IN_SCAN)
    {
        port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_COMPONENT_COUNT);
        port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM,
                   field(port, cinfo, CINFO_COMPS_IN_SCAN));
        port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM + 4, MAX_COMPS_IN_SCAN);
        const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
        port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, err, caller_ebx, cinfo);
    }
    port_set32(port, cinfo, CINFO_MCUS_PER_ROW,
               port_call(port, JDIV_ROUND_UP, field(port, cinfo, CINFO_IMAGE_WIDTH),
                         field(port, cinfo, CINFO_MAX_H_SAMP_FACTOR) * DCTSIZE, 0, 0));
    const uint32_t mcu_rows =
        port_call(port, JDIV_ROUND_UP, field(port, cinfo, CINFO_IMAGE_HEIGHT),
                  field(port, cinfo, CINFO_MAX_V_SAMP_FACTOR) * DCTSIZE, 0, 0);
    port_set32(port, cinfo, CINFO_BLOCKS_IN_MCU, 0);
    port_set32(port, cinfo, CINFO_MCU_ROWS_IN_SCAN, mcu_rows);

    for (int32_t ci = 0; ci < (int32_t)field(port, cinfo, CINFO_COMPS_IN_SCAN) && !port->env.failed;
         ci++)
    {
        /* The sampling factors give the component's blocks in each MCU. */
        const uint32_t component = port_u32(port, cinfo, CINFO_CUR_COMP_INFO + ci * 4);
        port_set32(port, component, COMPONENT_MCU_WIDTH,
                   port_u32(port, component, COMPONENT_H_SAMP_FACTOR));
        port_set32(port, component, COMPONENT_MCU_HEIGHT,
                   port_u32(port, component, COMPONENT_V_SAMP_FACTOR));
        const uint32_t width = port_u32(port, component, COMPONENT_MCU_WIDTH);
        const uint32_t height = port_u32(port, component, COMPONENT_MCU_HEIGHT);
        port_set32(port, component, COMPONENT_MCU_BLOCKS, width * height);
        port_set32(port, component, COMPONENT_MCU_SAMPLE_WIDTH,
                   port_u32(port, component, COMPONENT_MCU_WIDTH) *
                       port_u32(port, component, COMPONENT_DCT_SCALED_SIZE));
        port_set32(port, component, COMPONENT_LAST_COL_WIDTH,
                   last_blocks(port_u32(port, component, COMPONENT_WIDTH_IN_BLOCKS),
                               port_u32(port, component, COMPONENT_MCU_WIDTH)));
        port_set32(port, component, COMPONENT_LAST_ROW_HEIGHT,
                   last_blocks(port_u32(port, component, COMPONENT_HEIGHT_IN_BLOCKS),
                               port_u32(port, component, COMPONENT_MCU_HEIGHT)));

        /* The MCU's blocks, each marked with its component. */
        const uint32_t blocks = port_u32(port, component, COMPONENT_MCU_BLOCKS);
        if ((int32_t)(field(port, cinfo, CINFO_BLOCKS_IN_MCU) + blocks) >
            (int32_t)D_MAX_BLOCKS_IN_MCU)
        {
            port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_BAD_MCU_SIZE);
            const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
            port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, blocks, err, cinfo);
        }
        for (int32_t left = (int32_t)blocks; left > 0 && !port->env.failed; left--)
        {
            const uint32_t index = field(port, cinfo, CINFO_BLOCKS_IN_MCU);
            port_set32(port, cinfo, CINFO_BLOCKS_IN_MCU, index + 1);
            port_set32(port, cinfo + index * 4, CINFO_MCU_MEMBERSHIP, (uint32_t)ci);
        }
    }
}

/* latch_quant_tables: a copy of each component's quantisation table, made once. The error exit for
 * a missing table gets 0 in ebx and the table number in ecx, and the table is copied all the same;
 * alloc_small, a method, gets the table number in ecx. Sets *ebx and *ecx to what the original
 * leaves there: the component count and 0 without components; else the last component's saved
 * table, or 0x84 when one was made, and the component count. */
static void latch_quant_tables(Port *port, uint32_t cinfo, uint32_t *ebx, uint32_t *ecx)
{
    *ebx = field(port, cinfo, CINFO_COMPS_IN_SCAN);
    *ecx = 0;
    for (int32_t ci = 0; ci < (int32_t)field(port, cinfo, CINFO_COMPS_IN_SCAN) && !port->env.failed;
         ci++)
    {
        const uint32_t component = port_u32(port, cinfo, CINFO_CUR_COMP_INFO + ci * 4);
        *ebx = port_u32(port, component, COMPONENT_QUANT_TABLE);
        if (*ebx == 0)
        {
            const uint32_t qtblno = port_u32(port, component, COMPONENT_QUANT_TBL_NO);
            if ((int32_t)qtblno < 0 || (int32_t)qtblno >= (int32_t)NUM_QUANT_TBLS ||
                port_u32(port, cinfo + qtblno * 4, CINFO_QUANT_TBL_PTRS) == 0)
            {
                port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE,
                           JERR_NO_QUANT_TABLE);
                port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM, qtblno);
                const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
                port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, err, 0, qtblno);
            }
            const uint32_t memory = field(port, cinfo, CINFO_MEM);
            const uint32_t qtbl = port_call(port, port_u32(port, memory, MEM_ALLOC_SMALL), cinfo,
                                            JPOOL_IMAGE, JQUANT_TBL_BYTES, qtblno);
            port_copy(port, qtbl, port_u32(port, cinfo + qtblno * 4, CINFO_QUANT_TBL_PTRS),
                      JQUANT_TBL_BYTES);
            port_set32(port, component, COMPONENT_QUANT_TABLE, qtbl);
            *ebx = JQUANT_TBL_BYTES;
        }
        *ecx = field(port, cinfo, CINFO_COMPS_IN_SCAN);
    }
}

/* Original 0x4bcbc0 (eax = cinfo). Reached through a method pointer, so its eax and edx are
 * compared: the coefficient controller's consume_data and the caller's edx. The two start_pass
 * methods get the entropy decoder or the coefficient controller in edx, and in ebx and ecx what
 * latch_quant_tables leaves. */
uint32_t vertrix_port_jpeg_per_scan_setup_4bcbc0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;

    per_scan_setup(&port, cinfo, entry->ebx);
    uint32_t ebx;
    uint32_t ecx;
    latch_quant_tables(&port, cinfo, &ebx, &ecx);

    const uint32_t entropy = field(&port, cinfo, CINFO_ENTROPY);
    port_call(&port, port_u32(&port, entropy, ENTROPY_START_PASS), cinfo, entropy, ebx, ecx);
    const uint32_t coef = field(&port, cinfo, CINFO_COEF);
    port_call(&port, port_u32(&port, coef, COEF_START_INPUT_PASS), cinfo, coef, ebx, ecx);
    const uint32_t consume_data =
        port_u32(&port, field(&port, cinfo, CINFO_COEF), COEF_CONSUME_DATA);
    port_set32(&port, field(&port, cinfo, CINFO_INPUTCTL), INPUTCTL_CONSUME_INPUT, consume_data);
    return port_return(&port, consume_data, entry->edx);
}

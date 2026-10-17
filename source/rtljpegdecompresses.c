#include "rtljpegdecompresses.h"

/* libjpeg's decompress_onepass (jdcoefct.c): decodes one iMCU row's MCUs and runs the inverse DCT
 * of each block straight into the output, for single-pass decompression. */

enum
{
    CINFO_INPUT_IMCU_ROW = 0x94,
    CINFO_OUTPUT_IMCU_ROW = 0x9c,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_CUR_COMP_INFO = 0x14c,
    CINFO_MCUS_PER_ROW = 0x15c,
    CINFO_BLOCKS_IN_MCU = 0x164,
    CINFO_COEF = 0x1ac,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_ENTROPY = 0x1bc,
    CINFO_IDCT = 0x1c0,
    INPUTCTL_FINISH_INPUT_PASS = 0xc,
    ENTROPY_DECODE_MCU = 4,
    IDCT_INVERSE_DCT = 4,

    /* The coefficient controller: the MCU it stopped at, the rows of MCUs per iMCU row, and the
     * MCU's blocks. */
    COEF_MCU_CTR = 0x14,
    COEF_MCU_VERT_OFFSET = 0x18,
    COEF_MCU_ROWS_PER_IMCU_ROW = 0x1c,
    COEF_MCU_BUFFER = 0x20,

    COMPONENT_INDEX = 4,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_NEEDED = 0x30,
    COMPONENT_MCU_WIDTH = 0x34,
    COMPONENT_MCU_HEIGHT = 0x38,
    COMPONENT_MCU_BLOCKS = 0x3c,
    COMPONENT_MCU_SAMPLE_WIDTH = 0x40,
    COMPONENT_LAST_COL_WIDTH = 0x44,
    COMPONENT_LAST_ROW_HEIGHT = 0x48,
    BLOCK_BYTES = 0x80,

    JPEG_SUSPENDED = 0,
    JPEG_ROW_COMPLETED = 3,
    JPEG_SCAN_COMPLETED = 4,

    JZERO_FAR = 0x4c98f0,
    START_IMCU_ROW = 0x4b9d70
};

/* Original 0x4b9f70 (eax = cinfo, edx = output_buf). Returns JPEG_SUSPENDED (keeping the MCU it
 * stopped at), else JPEG_ROW_COMPLETED, or JPEG_SCAN_COMPLETED after finishing the input pass.
 * Reached through a method pointer, so its edx is compared: the coefficient controller when it
 * suspends, else what the last callee was handed (they keep edx). The methods it calls get all four
 * registers compared: decode_mcu gets the entropy decoder in ebx and in ecx the original's
 * leftover, the rows per iMCU row at first, then the last needed component's MCU row count (0 when
 * it has none); finish_input_pass gets the last MCU row number in ebx (the caller's when there was
 * none) and the same ecx. */
uint32_t vertrix_port_jpeg_decompress_onepass_4b9f70(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t output_buf = entry->edx;
    const uint32_t coef = port_u32(&port, cinfo, CINFO_COEF);
    const uint32_t last_mcu_col = port_u32(&port, cinfo, CINFO_MCUS_PER_ROW) - 1;
    const uint32_t last_imcu_row = port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS) - 1;
    uint32_t yoffset = port_u32(&port, coef, COEF_MCU_VERT_OFFSET);
    uint32_t ebx = entry->ebx;
    uint32_t ecx = port_u32(&port, coef, COEF_MCU_ROWS_PER_IMCU_ROW);

    for (; (int32_t)yoffset < (int32_t)port_u32(&port, coef, COEF_MCU_ROWS_PER_IMCU_ROW) &&
           !port.env.failed;
         yoffset++)
    {
        for (uint32_t col = port_u32(&port, coef, COEF_MCU_CTR);
             col <= last_mcu_col && !port.env.failed; col++)
        {
            port_call(&port, JZERO_FAR, port_u32(&port, coef, COEF_MCU_BUFFER),
                      port_u32(&port, cinfo, CINFO_BLOCKS_IN_MCU) << 7, 0, 0);
            const uint32_t entropy = port_u32(&port, cinfo, CINFO_ENTROPY);
            if (port_call(&port, port_u32(&port, entropy, ENTROPY_DECODE_MCU), cinfo,
                          coef + COEF_MCU_BUFFER, entropy, ecx) == 0)
            {
                /* Suspension: remember where to resume. */
                port_set32(&port, coef, COEF_MCU_VERT_OFFSET, yoffset);
                port_set32(&port, coef, COEF_MCU_CTR, col);
                return port_return(&port, JPEG_SUSPENDED, coef);
            }

            uint32_t blkn = 0;
            for (uint32_t ci = 0;
                 (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_COMPS_IN_SCAN) &&
                 !port.env.failed;
                 ci++)
            {
                const uint32_t component = port_u32(&port, cinfo + ci * 4, CINFO_CUR_COMP_INFO);
                if (port_u32(&port, component, COMPONENT_NEEDED) == 0)
                {
                    blkn += port_u32(&port, component, COMPONENT_MCU_BLOCKS);
                    continue;
                }
                const uint32_t index = port_u32(&port, component, COMPONENT_INDEX);
                const uint32_t inverse_dct = port_u32(
                    &port, port_u32(&port, cinfo, CINFO_IDCT) + index * 4, IDCT_INVERSE_DCT);
                const uint32_t useful_width =
                    col < last_mcu_col ? port_u32(&port, component, COMPONENT_MCU_WIDTH)
                                       : port_u32(&port, component, COMPONENT_LAST_COL_WIDTH);
                uint32_t output_ptr =
                    port_u32(&port, output_buf + index * 4, 0) +
                    yoffset * port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE) * 4;
                const uint32_t start_col =
                    col * port_u32(&port, component, COMPONENT_MCU_SAMPLE_WIDTH);
                uint32_t yindex = 0;
                for (;
                     (int32_t)yindex < (int32_t)port_u32(&port, component, COMPONENT_MCU_HEIGHT) &&
                     !port.env.failed;
                     yindex++)
                {
                    if (port_u32(&port, cinfo, CINFO_INPUT_IMCU_ROW) < last_imcu_row ||
                        (int32_t)(yoffset + yindex) <
                            (int32_t)port_u32(&port, component, COMPONENT_LAST_ROW_HEIGHT))
                    {
                        uint32_t output_col = start_col;
                        for (uint32_t xindex = 0;
                             (int32_t)xindex < (int32_t)useful_width && !port.env.failed; xindex++)
                        {
                            const uint32_t block =
                                port_u32(&port, coef + (blkn + xindex) * 4, COEF_MCU_BUFFER);
                            port_call_stack(&port, inverse_dct, cinfo, component, block, output_ptr,
                                            &output_col, 1);
                            output_col += port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE);
                        }
                    }
                    blkn += port_u32(&port, component, COMPONENT_MCU_WIDTH);
                    output_ptr += port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE) * 4;
                }
                ecx = yindex;
            }
        }
        /* Completed an MCU row, but perhaps not an iMCU row. */
        port_set32(&port, coef, COEF_MCU_CTR, 0);
        ebx = yoffset + 1;
    }

    port_set32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW,
               port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW) + 1);
    const uint32_t input_row = port_u32(&port, cinfo, CINFO_INPUT_IMCU_ROW) + 1;
    port_set32(&port, cinfo, CINFO_INPUT_IMCU_ROW, input_row);
    if (input_row < port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS))
    {
        port_call(&port, START_IMCU_ROW, cinfo, 0, 0, 0);
        return port_return(&port, JPEG_ROW_COMPLETED, cinfo);
    }
    const uint32_t inputctl = port_u32(&port, cinfo, CINFO_INPUTCTL);
    port_call(&port, port_u32(&port, inputctl, INPUTCTL_FINISH_INPUT_PASS), cinfo, inputctl, ebx,
              ecx);
    return port_return(&port, JPEG_SCAN_COMPLETED, inputctl);
}

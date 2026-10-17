#include "rtljpegcoefrows.h"

/* libjpeg's decompress_data (jdcoefct.c) for buffered-image mode: consumes input until it is ahead
 * of the output, then runs the inverse DCT over one iMCU row of every needed component from the
 * whole-image coefficient arrays. */

enum
{
    CINFO_MEM = 4,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_INPUT_SCAN_NUMBER = 0x90,
    CINFO_INPUT_IMCU_ROW = 0x94,
    CINFO_OUTPUT_SCAN_NUMBER = 0x98,
    CINFO_OUTPUT_IMCU_ROW = 0x9c,
    CINFO_COMP_INFO = 0xd8,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_COEF = 0x1ac,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_IDCT = 0x1c0,
    MEM_ACCESS_VIRT_BARRAY = 0x20,
    INPUTCTL_CONSUME_INPUT = 0,
    COEF_WHOLE_IMAGE = 0x48,
    IDCT_INVERSE_DCT = 4,

    COMPONENT_BYTES = 0x54,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_WIDTH_IN_BLOCKS = 0x1c,
    COMPONENT_HEIGHT_IN_BLOCKS = 0x20,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_NEEDED = 0x30,
    BLOCK_BYTES = 0x80,

    JPEG_SUSPENDED = 0,
    JPEG_ROW_COMPLETED = 3,
    JPEG_SCAN_COMPLETED = 4
};

/* Original 0x4ba470 (eax = cinfo, edx = output_buf). Returns JPEG_SUSPENDED when the input
 * suspends, else JPEG_ROW_COMPLETED, or JPEG_SCAN_COMPLETED after the last iMCU row. The calls are
 * methods: consume_input gets the input controller in edx, the coefficient controller in ebx and
 * output_buf in ecx, as the original leaves them. Reached through a method pointer, so its edx is
 * compared: the input controller when it suspends, else cinfo (the component count when there are
 * none). */
uint32_t vertrix_port_jpeg_decompress_coef_rows_4ba470(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t output_buf = entry->edx;
    const uint32_t coef = port_u32(&port, cinfo, CINFO_COEF);
    const uint32_t last_imcu_row = port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS) - 1;

    /* Force some input to be done if the output is getting ahead of it. */
    for (;;)
    {
        const int32_t output_scan = (int32_t)port_u32(&port, cinfo, CINFO_OUTPUT_SCAN_NUMBER);
        if ((int32_t)port_u32(&port, cinfo, CINFO_INPUT_SCAN_NUMBER) >= output_scan &&
            ((uint32_t)output_scan != port_u32(&port, cinfo, CINFO_INPUT_SCAN_NUMBER) ||
             port_u32(&port, cinfo, CINFO_INPUT_IMCU_ROW) >
                 port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW)))
        {
            break;
        }
        const uint32_t inputctl = port_u32(&port, cinfo, CINFO_INPUTCTL);
        if (port_call(&port, port_u32(&port, inputctl, INPUTCTL_CONSUME_INPUT), cinfo, inputctl,
                      coef, output_buf) == JPEG_SUSPENDED ||
            port.env.failed)
        {
            return port_return(&port, JPEG_SUSPENDED, inputctl);
        }
    }

    uint32_t edx = port_u32(&port, cinfo, CINFO_NUM_COMPONENTS);
    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    for (uint32_t ci = 0;
         (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) && !port.env.failed;
         ci++, component += COMPONENT_BYTES)
    {
        edx = cinfo;
        if (port_u32(&port, component, COMPONENT_NEEDED) == 0)
        {
            continue;
        }
        const uint32_t v_samp_factor = port_u32(&port, component, COMPONENT_V_SAMP_FACTOR);
        const uint32_t output_row = port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW);
        const uint32_t whole_image = port_u32(&port, coef + ci * 4, COEF_WHOLE_IMAGE);
        const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
        const uint32_t writable = 0;
        const uint32_t buffer =
            port_call_stack(&port, port_u32(&port, memory, MEM_ACCESS_VIRT_BARRAY), cinfo,
                            whole_image, output_row * v_samp_factor, v_samp_factor, &writable, 1);

        uint32_t block_rows;
        if (last_imcu_row > port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW))
        {
            block_rows = port_u32(&port, component, COMPONENT_V_SAMP_FACTOR);
        }
        else
        {
            /* The last iMCU row may be short. A factor of 0 leaves 0, as the lifted div does. */
            const uint32_t factor = port_u32(&port, component, COMPONENT_V_SAMP_FACTOR);
            const uint32_t height = port_u32(&port, component, COMPONENT_HEIGHT_IN_BLOCKS);
            block_rows = factor != 0 ? height % factor : 0;
            if (block_rows == 0)
            {
                block_rows = factor;
            }
        }
        const uint32_t inverse_dct =
            port_u32(&port, port_u32(&port, cinfo, CINFO_IDCT) + ci * 4, IDCT_INVERSE_DCT);
        uint32_t output_ptr = port_u32(&port, output_buf + ci * 4, 0);
        for (uint32_t block_row = 0; (int32_t)block_row < (int32_t)block_rows && !port.env.failed;
             block_row++)
        {
            uint32_t block = port_u32(&port, buffer + block_row * 4, 0);
            uint32_t output_col = 0;
            for (uint32_t block_num = 0;
                 block_num < port_u32(&port, component, COMPONENT_WIDTH_IN_BLOCKS) &&
                 !port.env.failed;
                 block_num++)
            {
                port_call_stack(&port, inverse_dct, cinfo, component, block, output_ptr,
                                &output_col, 1);
                block += BLOCK_BYTES;
                output_col += port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE);
            }
            output_ptr += port_u32(&port, component, COMPONENT_DCT_SCALED_SIZE) * 4;
        }
    }

    const uint32_t next_row = port_u32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW) + 1;
    port_set32(&port, cinfo, CINFO_OUTPUT_IMCU_ROW, next_row);
    return port_return(&port,
                       next_row < port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS)
                           ? JPEG_ROW_COMPLETED
                           : JPEG_SCAN_COMPLETED,
                       edx);
}

#include "rtljpeginputs.h"

/* libjpeg's consume_markers (jdinput.c), with initial_setup inlined: reads markers up to the next
 * scan or the end of the image; at the first scan it checks the frame and computes the component
 * dimensions, at a later one it starts the scan's input pass. */

enum
{
    CINFO_ERR = 0,
    CINFO_IMAGE_WIDTH = 0x1c,
    CINFO_IMAGE_HEIGHT = 0x20,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_INPUT_SCAN_NUMBER = 0x90,
    CINFO_OUTPUT_SCAN_NUMBER = 0x98,
    CINFO_DATA_PRECISION = 0xd4,
    CINFO_COMP_INFO = 0xd8,
    CINFO_PROGRESSIVE_MODE = 0xdc,
    CINFO_MAX_H_SAMP_FACTOR = 0x134,
    CINFO_MAX_V_SAMP_FACTOR = 0x138,
    CINFO_MIN_DCT_SCALED_SIZE = 0x13c,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_COMPS_IN_SCAN = 0x148,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_MARKER = 0x1b8,
    ERR_ERROR_EXIT = 0,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,

    INPUTCTL_HAS_MULTIPLE_SCANS = 0x10,
    INPUTCTL_EOI_REACHED = 0x14,
    INPUTCTL_INHEADERS = 0x18,
    MARKER_READ_MARKERS = 4,
    MARKER_SAW_SOF = 0x10,

    /* jpeg_component_info: 0x54 bytes. */
    COMPONENT_BYTES = 0x54,
    COMPONENT_H_SAMP_FACTOR = 8,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_WIDTH_IN_BLOCKS = 0x1c,
    COMPONENT_HEIGHT_IN_BLOCKS = 0x20,
    COMPONENT_DCT_SCALED_SIZE = 0x24,
    COMPONENT_DOWNSAMPLED_WIDTH = 0x28,
    COMPONENT_DOWNSAMPLED_HEIGHT = 0x2c,
    COMPONENT_NEEDED = 0x30,
    COMPONENT_QUANT_TABLE = 0x4c,

    JPEG_SUSPENDED = 0,
    JPEG_REACHED_SOS = 1,
    JPEG_REACHED_EOI = 2,
    JPEG_MAX_DIMENSION = 0xffdc,
    BITS_IN_JSAMPLE = 8,
    MAX_COMPONENTS = 10,
    MAX_SAMP_FACTOR = 4,
    DCTSIZE = 8,
    JERR_BAD_PRECISION = 0xf,
    JERR_BAD_SAMPLING = 0x12,
    JERR_COMPONENT_COUNT = 0x1a,
    JERR_EOI_EXPECTED = 0x23,
    JERR_IMAGE_TOO_BIG = 0x29,
    JERR_SOF_NO_SOS = 0x3b,

    JDIV_ROUND_UP = 0x4c9820,
    START_INPUT_PASS = 0x4bcbc0
};

static uint32_t field(Port *port, uint32_t cinfo, uint32_t offset)
{
    return port_u32(port, cinfo, offset);
}

/* ERREXIT: sets the message code and returns the error manager. Its error_exit, a method, is then
 * called with what the original leaves in edx, ebx and ecx. The lifted error_exit may return; the
 * routine then goes on. */
static uint32_t error_code(Port *port, uint32_t cinfo, uint32_t code)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    return port_u32(port, cinfo, CINFO_ERR);
}

static void error_exit(Port *port, uint32_t cinfo, uint32_t err, uint32_t edx, uint32_t ebx,
                       uint32_t ecx)
{
    port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, edx, ebx, ecx);
}

/* ERREXIT with parameters: error_exit gets the error manager in edx, the image height in ebx and
 * cinfo in ecx. */
static void error_exit_with(Port *port, uint32_t cinfo, uint32_t code, const uint32_t *parameters,
                            unsigned count, uint32_t height)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    for (unsigned k = 0; k < count; k++)
    {
        port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_PARM + k * 4, parameters[k]);
    }
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, err, height, cinfo);
}

static uint32_t div_round_up(Port *port, uint32_t a, uint32_t b)
{
    return port_call(port, JDIV_ROUND_UP, a, b, 0, 0);
}

/* initial_setup: the frame's checks, the largest sampling factors, each component's size in
 * blocks and samples, the iMCU row count, and whether there are several scans. */
static void initial_setup(Port *port, uint32_t cinfo)
{
    const uint32_t height = field(port, cinfo, CINFO_IMAGE_HEIGHT);
    if ((int32_t)height > (int32_t)JPEG_MAX_DIMENSION ||
        (int32_t)field(port, cinfo, CINFO_IMAGE_WIDTH) > (int32_t)JPEG_MAX_DIMENSION)
    {
        const uint32_t limit = JPEG_MAX_DIMENSION;
        error_exit_with(port, cinfo, JERR_IMAGE_TOO_BIG, &limit, 1, height);
    }
    if (field(port, cinfo, CINFO_DATA_PRECISION) != BITS_IN_JSAMPLE)
    {
        const uint32_t precision = field(port, cinfo, CINFO_DATA_PRECISION);
        error_exit_with(port, cinfo, JERR_BAD_PRECISION, &precision, 1, height);
    }
    if ((int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) > (int32_t)MAX_COMPONENTS)
    {
        const uint32_t counts[2] = {field(port, cinfo, CINFO_NUM_COMPONENTS), MAX_COMPONENTS};
        error_exit_with(port, cinfo, JERR_COMPONENT_COUNT, counts, 2, height);
    }

    port_set32(port, cinfo, CINFO_MAX_H_SAMP_FACTOR, 1);
    port_set32(port, cinfo, CINFO_MAX_V_SAMP_FACTOR, 1);
    uint32_t component = field(port, cinfo, CINFO_COMP_INFO);
    for (int32_t ci = 0;
         ci < (int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) && !port->env.failed; ci++)
    {
        const int32_t h = (int32_t)port_u32(port, component, COMPONENT_H_SAMP_FACTOR);
        const int32_t v = (int32_t)port_u32(port, component, COMPONENT_V_SAMP_FACTOR);
        if (h <= 0 || h > (int32_t)MAX_SAMP_FACTOR || v <= 0 || v > (int32_t)MAX_SAMP_FACTOR)
        {
            /* The original leaves the component's index in edx. */
            const uint32_t err = error_code(port, cinfo, JERR_BAD_SAMPLING);
            error_exit(port, cinfo, err, (uint32_t)ci, component, cinfo);
        }
        const uint32_t h_now = port_u32(port, component, COMPONENT_H_SAMP_FACTOR);
        if ((int32_t)field(port, cinfo, CINFO_MAX_H_SAMP_FACTOR) <= (int32_t)h_now)
        {
            port_set32(port, cinfo, CINFO_MAX_H_SAMP_FACTOR, h_now);
        }
        const uint32_t v_now = port_u32(port, component, COMPONENT_V_SAMP_FACTOR);
        if ((int32_t)field(port, cinfo, CINFO_MAX_V_SAMP_FACTOR) <= (int32_t)v_now)
        {
            port_set32(port, cinfo, CINFO_MAX_V_SAMP_FACTOR, v_now);
        }
        component += COMPONENT_BYTES;
    }

    port_set32(port, cinfo, CINFO_MIN_DCT_SCALED_SIZE, DCTSIZE);
    component = field(port, cinfo, CINFO_COMP_INFO);
    for (int32_t ci = 0;
         ci < (int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) && !port->env.failed; ci++)
    {
        port_set32(port, component, COMPONENT_DCT_SCALED_SIZE, DCTSIZE);
        port_set32(port, component, COMPONENT_WIDTH_IN_BLOCKS,
                   div_round_up(port,
                                field(port, cinfo, CINFO_IMAGE_WIDTH) *
                                    port_u32(port, component, COMPONENT_H_SAMP_FACTOR),
                                field(port, cinfo, CINFO_MAX_H_SAMP_FACTOR) * DCTSIZE));
        port_set32(port, component, COMPONENT_HEIGHT_IN_BLOCKS,
                   div_round_up(port,
                                field(port, cinfo, CINFO_IMAGE_HEIGHT) *
                                    port_u32(port, component, COMPONENT_V_SAMP_FACTOR),
                                field(port, cinfo, CINFO_MAX_V_SAMP_FACTOR) * DCTSIZE));
        port_set32(port, component, COMPONENT_DOWNSAMPLED_WIDTH,
                   div_round_up(port,
                                field(port, cinfo, CINFO_IMAGE_WIDTH) *
                                    port_u32(port, component, COMPONENT_H_SAMP_FACTOR),
                                field(port, cinfo, CINFO_MAX_H_SAMP_FACTOR)));
        const uint32_t downsampled_height =
            div_round_up(port,
                         field(port, cinfo, CINFO_IMAGE_HEIGHT) *
                             port_u32(port, component, COMPONENT_V_SAMP_FACTOR),
                         field(port, cinfo, CINFO_MAX_V_SAMP_FACTOR));
        port_set32(port, component, COMPONENT_NEEDED, 1);
        port_set32(port, component, COMPONENT_QUANT_TABLE, 0);
        port_set32(port, component, COMPONENT_DOWNSAMPLED_HEIGHT, downsampled_height);
        component += COMPONENT_BYTES;
    }

    port_set32(port, cinfo, CINFO_TOTAL_IMCU_ROWS,
               div_round_up(port, field(port, cinfo, CINFO_IMAGE_HEIGHT),
                            field(port, cinfo, CINFO_MAX_V_SAMP_FACTOR) * DCTSIZE));
    const int multiple = (int32_t)field(port, cinfo, CINFO_NUM_COMPONENTS) >
                             (int32_t)field(port, cinfo, CINFO_COMPS_IN_SCAN) ||
                         field(port, cinfo, CINFO_PROGRESSIVE_MODE) != 0;
    port_set32(port, field(port, cinfo, CINFO_INPUTCTL), INPUTCTL_HAS_MULTIPLE_SCANS,
               multiple ? 1 : 0);
}

/* Original 0x4bcea0 (eax = cinfo). Reached through a method pointer, so its eax and edx are
 * compared: the read_markers result (2 when the end of the image was reached before) and the
 * caller's edx. read_markers, a method, gets cinfo in edx, the caller's ebx and the marker reader
 * in ecx; the error exits get the error manager or (for a bad sampling factor) the component's
 * index in edx, and in ebx the caller's, the image height, the component or the inheaders flag. */
uint32_t vertrix_port_jpeg_input_consume_markers_4bcea0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t inputctl = field(&port, cinfo, CINFO_INPUTCTL);

    /* After the end of the image, read no further. */
    if (port_u32(&port, inputctl, INPUTCTL_EOI_REACHED) != 0)
    {
        return port_return(&port, JPEG_REACHED_EOI, entry->edx);
    }
    const uint32_t marker = field(&port, cinfo, CINFO_MARKER);
    const uint32_t val = port_call(&port, port_u32(&port, marker, MARKER_READ_MARKERS), cinfo,
                                   cinfo, entry->ebx, marker);

    if (val == JPEG_REACHED_SOS)
    {
        if (port_u32(&port, inputctl, INPUTCTL_INHEADERS) != 0)
        {
            /* The first scan. */
            initial_setup(&port, cinfo);
            port_set32(&port, inputctl, INPUTCTL_INHEADERS, 0);
        }
        else
        {
            if (port_u32(&port, inputctl, INPUTCTL_HAS_MULTIPLE_SCANS) == 0)
            {
                const uint32_t err = error_code(&port, cinfo, JERR_EOI_EXPECTED);
                error_exit(&port, cinfo, err, cinfo, entry->ebx, err);
            }
            port_call(&port, START_INPUT_PASS, cinfo, 0, entry->ebx, 0);
        }
    }
    else if (val == JPEG_REACHED_EOI)
    {
        const uint32_t inheaders = port_u32(&port, inputctl, INPUTCTL_INHEADERS);
        port_set32(&port, inputctl, INPUTCTL_EOI_REACHED, 1);
        if (inheaders != 0)
        {
            /* A tables-only datastream; a frame without a scan is an error. */
            if (port_u32(&port, field(&port, cinfo, CINFO_MARKER), MARKER_SAW_SOF) != 0)
            {
                const uint32_t err = error_code(&port, cinfo, JERR_SOF_NO_SOS);
                error_exit(&port, cinfo, err, cinfo, inheaders, err);
            }
        }
        else if ((int32_t)field(&port, cinfo, CINFO_OUTPUT_SCAN_NUMBER) >
                 (int32_t)field(&port, cinfo, CINFO_INPUT_SCAN_NUMBER))
        {
            port_set32(&port, cinfo, CINFO_OUTPUT_SCAN_NUMBER,
                       field(&port, cinfo, CINFO_INPUT_SCAN_NUMBER));
        }
    }
    return port_return(&port, val, entry->edx);
}

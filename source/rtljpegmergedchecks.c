#include "rtljpegmergedchecks.h"

/* libjpeg's use_merged_upsample (jdmaster.c): whether upsampling and colour conversion can be
 * merged (jdmerge.c). */

enum
{
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_JPEG_COLOR_SPACE = 0x28,
    CINFO_OUT_COLOR_SPACE = 0x2c,
    CINFO_DO_FANCY_UPSAMPLING = 0x4c,
    CINFO_OUT_COLOR_COMPONENTS = 0x78,
    CINFO_COMP_INFO = 0xd8,
    CINFO_CCIR601_SAMPLING = 0x12c,
    CINFO_MIN_DCT_SCALED_SIZE = 0x13c,
    /* jpeg_component_info. */
    COMPONENT_BYTES = 0x54,
    COMPONENT_H_SAMP_FACTOR = 8,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_DCT_SCALED_SIZE = 0x24,

    JCS_RGB = 2,
    JCS_YCbCr = 3,
    RGB_PIXELSIZE = 3
};

static uint32_t component(Port *port, uint32_t comp_info, uint32_t index, uint32_t field)
{
    return port_u32(port, comp_info + index * COMPONENT_BYTES, field);
}

static int merged(Port *port, uint32_t cinfo)
{
    /* Merging is the equivalent of plain box-filter upsampling. */
    if (port_u32(port, cinfo, CINFO_DO_FANCY_UPSAMPLING) != 0 ||
        port_u32(port, cinfo, CINFO_CCIR601_SAMPLING) != 0)
    {
        return 0;
    }
    /* jdmerge.c only supports YCC to RGB colour conversion. */
    if (port_u32(port, cinfo, CINFO_JPEG_COLOR_SPACE) != JCS_YCbCr ||
        port_u32(port, cinfo, CINFO_NUM_COMPONENTS) != 3 ||
        port_u32(port, cinfo, CINFO_OUT_COLOR_SPACE) != JCS_RGB ||
        port_u32(port, cinfo, CINFO_OUT_COLOR_COMPONENTS) != RGB_PIXELSIZE)
    {
        return 0;
    }
    /* And it only handles 2h1v or 2h2v sampling ratios. */
    const uint32_t comp = port_u32(port, cinfo, CINFO_COMP_INFO);
    if (component(port, comp, 0, COMPONENT_H_SAMP_FACTOR) != 2 ||
        component(port, comp, 1, COMPONENT_H_SAMP_FACTOR) != 1 ||
        component(port, comp, 2, COMPONENT_H_SAMP_FACTOR) != 1 ||
        (int32_t)component(port, comp, 0, COMPONENT_V_SAMP_FACTOR) > 2 ||
        component(port, comp, 1, COMPONENT_V_SAMP_FACTOR) != 1 ||
        component(port, comp, 2, COMPONENT_V_SAMP_FACTOR) != 1)
    {
        return 0;
    }
    /* Furthermore, it doesn't work if the IDCTs are scaled differently. */
    const uint32_t size = port_u32(port, cinfo, CINFO_MIN_DCT_SCALED_SIZE);
    for (uint32_t index = 0; index < 3; index++)
    {
        if (component(port, comp, index, COMPONENT_DCT_SCALED_SIZE) != size)
        {
            return 0;
        }
    }
    return 1;
}

/* Original 0x4c0b51 (eax = cinfo): 1 when the merged path can be used, else 0. */
uint32_t vertrix_port_jpeg_use_merged_upsample_4c0b51(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, (uint32_t)merged(&port, entry->eax), 0);
}

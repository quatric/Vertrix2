#include "rtljpegsofmarkers.h"

/* libjpeg's get_sof (jdmarker.c): reads a start-of-frame marker (precision, image size, components
 * and their sampling factors and quantisation tables). */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_SRC = 0x18,
    CINFO_IMAGE_WIDTH = 0x1c,
    CINFO_IMAGE_HEIGHT = 0x20,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_DATA_PRECISION = 0xd4,
    CINFO_COMP_INFO = 0xd8,
    CINFO_PROGRESSIVE_MODE = 0xdc,
    CINFO_ARITH_CODE = 0xe0,
    CINFO_UNREAD_MARKER = 0x1a0,
    CINFO_MARKER = 0x1b8,
    ERR_ERROR_EXIT = 0,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    MEM_ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,
    TRACE_LEVEL = 1,
    MARKER_SAW_SOF = 0x10,
    SOURCE_NEXT_INPUT_BYTE = 0,
    SOURCE_BYTES_IN_BUFFER = 4,
    SOURCE_FILL_INPUT_BUFFER = 0xc,

    /* jpeg_component_info: 0x54 bytes. */
    COMPONENT_BYTES = 0x54,
    COMPONENT_ID = 0,
    COMPONENT_INDEX = 4,
    COMPONENT_H_SAMP_FACTOR = 8,
    COMPONENT_V_SAMP_FACTOR = 0xc,
    COMPONENT_QUANT_TBL_NO = 0x10,

    JERR_BAD_LENGTH = 0xb,
    JERR_EMPTY_IMAGE = 0x20,
    JERR_SOF_DUPLICATE = 0x3a,
    JTRC_SOF = 0x64,
    JTRC_SOF_COMPONENT = 0x65,
    /* The marker's length counts itself, the precision, the size and the component count. */
    SOF_HEADER_BYTES = 8
};

/* The marker reader's copy of the source's input position (INPUT_VARS). */
typedef struct
{
    Port *port;
    uint32_t cinfo;
    uint32_t source;
    uint32_t next;
    uint32_t left;
} Input;

/* INPUT_BYTE: refills an empty buffer through fill_input_buffer, a method, which gets the source in
 * edx and the ebx the original leaves. Returns 0 when the source suspends. */
static int input_byte(Input *in, uint32_t ebx, uint32_t *value)
{
    if (in->left == 0)
    {
        if (port_call(in->port, port_u32(in->port, in->source, SOURCE_FILL_INPUT_BUFFER), in->cinfo,
                      in->source, ebx, in->cinfo) == 0)
        {
            return 0;
        }
        in->next = port_u32(in->port, in->source, SOURCE_NEXT_INPUT_BYTE);
        in->left = port_u32(in->port, in->source, SOURCE_BYTES_IN_BUFFER);
    }
    in->left--;
    *value = port_u8(in->port, in->next, 0);
    in->next++;
    return 1;
}

/* INPUT_2BYTES into a field of cinfo: the high byte is stored before the low one is read. */
static int input_field(Input *in, uint32_t ebx, uint32_t offset)
{
    uint32_t byte;
    if (!input_byte(in, ebx, &byte))
    {
        return 0;
    }
    port_set32(in->port, in->cinfo, offset, byte << 8);
    if (!input_byte(in, ebx, &byte))
    {
        return 0;
    }
    port_set32(in->port, in->cinfo, offset, port_u32(in->port, in->cinfo, offset) + byte);
    return 1;
}

/* ERREXIT through error_exit, a method, with the ebx the original leaves (cinfo in ecx). The lifted
 * error_exit may return; the routine then goes on. */
static void error_exit(Port *port, uint32_t cinfo, uint32_t code, uint32_t ebx)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, err, ERR_ERROR_EXIT), cinfo, err, ebx, cinfo);
}

/* TRACEMS4 through emit_message, a method, with the ebx the original leaves. */
static void trace4(Port *port, uint32_t cinfo, uint32_t code, const uint32_t parameters[4],
                   uint32_t ebx)
{
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    for (unsigned k = 0; k < 4; k++)
    {
        port_set32(port, err, ERR_MSG_PARM + k * 4, parameters[k]);
    }
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    const uint32_t emitter = port_u32(port, cinfo, CINFO_ERR);
    port_call(port, port_u32(port, emitter, ERR_EMIT_MESSAGE), cinfo, TRACE_LEVEL, ebx, cinfo);
}

/* Original 0x4be0b0 (eax = cinfo, edx = is_prog, ebx = is_arith). Returns 1 with the source's
 * position updated and edx the next input byte, or 0 (the position not stored) with edx the source
 * when it suspends. The methods it calls get cinfo in ecx and in ebx what the original keeps there:
 * is_arith, then the length read so far (less 8 once the header is read), the size of the component
 * array to allocate, then the component being read. The error exits may return; the routine then
 * goes on with what it has. */
uint32_t vertrix_port_jpeg_get_sof_4be0b0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    Input in = {&port, cinfo, port_u32(&port, cinfo, CINFO_SRC), 0, 0};
    in.next = port_u32(&port, in.source, SOURCE_NEXT_INPUT_BYTE);
    in.left = port_u32(&port, in.source, SOURCE_BYTES_IN_BUFFER);
    port_set32(&port, cinfo, CINFO_PROGRESSIVE_MODE, entry->edx);
    port_set32(&port, cinfo, CINFO_ARITH_CODE, entry->ebx);

    uint32_t high;
    uint32_t low;
    uint32_t byte;
    if (!input_byte(&in, entry->ebx, &high) || !input_byte(&in, high << 8, &low))
    {
        return port_return(&port, 0, in.source);
    }
    uint32_t length = high << 8 | low;
    if (!input_byte(&in, length, &byte))
    {
        return port_return(&port, 0, in.source);
    }
    port_set32(&port, cinfo, CINFO_DATA_PRECISION, byte);
    if (!input_field(&in, length, CINFO_IMAGE_HEIGHT) ||
        !input_field(&in, length, CINFO_IMAGE_WIDTH) || !input_byte(&in, length, &byte))
    {
        return port_return(&port, 0, in.source);
    }
    port_set32(&port, cinfo, CINFO_NUM_COMPONENTS, byte);

    const uint32_t sof[4] = {
        port_u32(&port, cinfo, CINFO_UNREAD_MARKER),
        port_u32(&port, cinfo, CINFO_IMAGE_WIDTH),
        port_u32(&port, cinfo, CINFO_IMAGE_HEIGHT),
        port_u32(&port, cinfo, CINFO_NUM_COMPONENTS),
    };
    trace4(&port, cinfo, JTRC_SOF, sof, length);
    length -= SOF_HEADER_BYTES;
    if (port_u32(&port, port_u32(&port, cinfo, CINFO_MARKER), MARKER_SAW_SOF) != 0)
    {
        error_exit(&port, cinfo, JERR_SOF_DUPLICATE, length);
    }
    /* The size is unsigned, the component count signed. */
    if (port_u32(&port, cinfo, CINFO_IMAGE_HEIGHT) == 0 ||
        port_u32(&port, cinfo, CINFO_IMAGE_WIDTH) == 0 ||
        (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) <= 0)
    {
        error_exit(&port, cinfo, JERR_EMPTY_IMAGE, length);
    }
    if (length != port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) * 3)
    {
        error_exit(&port, cinfo, JERR_BAD_LENGTH, length);
    }
    if (port_u32(&port, cinfo, CINFO_COMP_INFO) == 0)
    {
        /* Allocated once, even when the marker is read again after a suspension. */
        const uint32_t bytes = port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) * COMPONENT_BYTES;
        const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
        port_set32(&port, cinfo, CINFO_COMP_INFO,
                   port_call(&port, port_u32(&port, memory, MEM_ALLOC_SMALL), cinfo, JPOOL_IMAGE,
                             bytes, cinfo));
    }

    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    for (int32_t ci = 0;
         ci < (int32_t)port_u32(&port, cinfo, CINFO_NUM_COMPONENTS) && !port.env.failed; ci++)
    {
        port_set32(&port, component, COMPONENT_INDEX, (uint32_t)ci);
        if (!input_byte(&in, component, &byte))
        {
            return port_return(&port, 0, in.source);
        }
        port_set32(&port, component, COMPONENT_ID, byte);
        if (!input_byte(&in, component, &byte))
        {
            return port_return(&port, 0, in.source);
        }
        port_set32(&port, component, COMPONENT_V_SAMP_FACTOR, byte & 0xf);
        port_set32(&port, component, COMPONENT_H_SAMP_FACTOR, byte >> 4 & 0xf);
        if (!input_byte(&in, component, &byte))
        {
            return port_return(&port, 0, in.source);
        }
        port_set32(&port, component, COMPONENT_QUANT_TBL_NO, byte);
        const uint32_t parameters[4] = {
            port_u32(&port, component, COMPONENT_ID),
            port_u32(&port, component, COMPONENT_H_SAMP_FACTOR),
            port_u32(&port, component, COMPONENT_V_SAMP_FACTOR),
            port_u32(&port, component, COMPONENT_QUANT_TBL_NO),
        };
        trace4(&port, cinfo, JTRC_SOF_COMPONENT, parameters, component);
        component += COMPONENT_BYTES;
    }

    port_set32(&port, port_u32(&port, cinfo, CINFO_MARKER), MARKER_SAW_SOF, 1);
    /* INPUT_SYNC. */
    port_set32(&port, in.source, SOURCE_NEXT_INPUT_BYTE, in.next);
    port_set32(&port, in.source, SOURCE_BYTES_IN_BUFFER, in.left);
    return port_return(&port, 1, in.next);
}

#include "rtljpegmarkerskips.h"

/* libjpeg's skip_variable (jdmarker.c): skip a marker the decoder does not use. */

enum
{
    CINFO_ERR = 0,
    CINFO_SRC = 0x18,
    CINFO_UNREAD_MARKER = 0x1a0,
    /* The source manager. */
    SRC_NEXT_INPUT_BYTE = 0,
    SRC_BYTES_IN_BUFFER = 4,
    SRC_FILL_INPUT_BUFFER = 0xc,
    SRC_SKIP_INPUT_DATA = 0x10,
    /* The error manager: its emit_message(cinfo, level) and the message with two parameters. */
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    JTRC_MISC_MARKER = 0x5b,
    TRACE_LEVEL = 1
};

typedef struct
{
    uint32_t next;
    uint32_t bytes;
} Input;

/* A method of the source or error manager: like the original, it leaves the source manager in
 * ebx and cinfo in ecx. */
static uint32_t method(Port *port, uint32_t function, uint32_t cinfo, uint32_t edx, uint32_t src)
{
    return port_call(port, function, cinfo, edx, src, cinfo);
}

/* The next byte (INPUT_BYTE): refill an empty buffer first; 0 when that fails. */
static int input_byte(Port *port, const LiftEntry *entry, uint32_t cinfo, uint32_t src,
                      Input *input, uint32_t *byte)
{
    if (input->bytes == 0)
    {
        if (method(port, port_u32(port, src, SRC_FILL_INPUT_BUFFER), cinfo, entry->edx, src) == 0)
        {
            return 0;
        }
        input->next = port_u32(port, src, SRC_NEXT_INPUT_BYTE);
        input->bytes = port_u32(port, src, SRC_BYTES_IN_BUFFER);
    }
    input->bytes--;
    *byte = port_u8(port, input->next, 0);
    input->next++;
    return 1;
}

/* Original 0x4bf6a0 (eax = cinfo): read the marker's big-endian length, trace it with the
 * unread marker (JTRC_MISC_MARKER, level 1), hand the source manager back its place and skip
 * the length less its own 2 bytes when that is positive. Returns 1, or 0 when the source cannot
 * be refilled. edx is kept as it came (the original saves it). */
uint32_t vertrix_port_jpeg_skip_variable_marker_4bf6a0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t src = port_u32(&port, cinfo, CINFO_SRC);
    Input input = {port_u32(&port, src, SRC_NEXT_INPUT_BYTE),
                   port_u32(&port, src, SRC_BYTES_IN_BUFFER)};
    uint32_t high;
    uint32_t low;
    if (!input_byte(&port, entry, cinfo, src, &input, &high) ||
        !input_byte(&port, entry, cinfo, src, &input, &low))
    {
        return port_return(&port, 0, entry->edx);
    }
    const uint32_t length = (high << 8) + low - 2;

    const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
    port_set32(&port, err, ERR_MSG_CODE, JTRC_MISC_MARKER);
    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM,
               port_u32(&port, cinfo, CINFO_UNREAD_MARKER));
    port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM + 4, length);
    const uint32_t emit = port_u32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_EMIT_MESSAGE);
    method(&port, emit, cinfo, TRACE_LEVEL, src);

    port_set32(&port, src, SRC_NEXT_INPUT_BYTE, input.next);
    port_set32(&port, src, SRC_BYTES_IN_BUFFER, input.bytes);
    if ((int32_t)length > 0)
    {
        const uint32_t now = port_u32(&port, cinfo, CINFO_SRC);
        method(&port, port_u32(&port, now, SRC_SKIP_INPUT_DATA), cinfo, length, now);
    }
    return port_return(&port, 1, entry->edx);
}

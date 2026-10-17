#include "rtljpegbitbuffers.h"

/* libjpeg's jpeg_fill_bit_buffer (jdhuff.c): loads whole bytes into the Huffman decoder's bit
 * buffer until it holds 25 bits, refilling the source as needed and stopping at a marker. */

enum
{
    /* The bit reader's working state. */
    STATE_NEXT_INPUT_BYTE = 0,
    STATE_BYTES_IN_BUFFER = 4,
    STATE_GET_BUFFER = 8,
    STATE_BITS_LEFT = 0xc,
    STATE_CINFO = 0x10,

    CINFO_ERR = 0,
    CINFO_SRC = 0x18,
    CINFO_UNREAD_MARKER = 0x1a0,
    CINFO_ENTROPY = 0x1bc,
    SRC_NEXT_INPUT_BYTE = 0,
    SRC_BYTES_IN_BUFFER = 4,
    SRC_FILL_INPUT_BUFFER = 0xc,
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ENTROPY_INSUFFICIENT_DATA = 8,
    JWRN_HIT_MARKER = 0x75,

    MIN_GET_BITS = 25,
    MARKER_PREFIX = 0xff
};

typedef struct
{
    Port *port;
    uint32_t cinfo;
    uint32_t next_input_byte;
    uint32_t bytes_in_buffer;
    /* What the original holds in edx: 0 until the first byte goes into the buffer, then the
     * buffer. */
    uint32_t edx;
} Source;

/* The source's fill_input_buffer, a method: the original leaves the source in ebx and cinfo in
 * ecx. Returns 0 when it suspends. */
static int refill(Source *source)
{
    Port *port = source->port;
    const uint32_t src = port_u32(port, source->cinfo, CINFO_SRC);
    if (port_call(port, port_u32(port, src, SRC_FILL_INPUT_BUFFER), source->cinfo, source->edx, src,
                  source->cinfo) == 0)
    {
        return 0;
    }
    const uint32_t refilled = port_u32(port, source->cinfo, CINFO_SRC);
    source->next_input_byte = port_u32(port, refilled, SRC_NEXT_INPUT_BYTE);
    source->bytes_in_buffer = port_u32(port, refilled, SRC_BYTES_IN_BUFFER);
    return 1;
}

/* The next byte, refilling first when none is left; -1 when the source suspends. */
static int32_t next_byte(Source *source)
{
    if (source->bytes_in_buffer == 0 && !refill(source))
    {
        return -1;
    }
    source->bytes_in_buffer--;
    return (int32_t)port_u8(source->port, source->next_input_byte++, 0);
}

/* Original 0x4bbf30 (eax = the state, edx = get_buffer, ebx = bits_left, ecx = nbits): returns 1
 * with the state updated, or 0 (nothing stored) when the source suspends. At a marker it records
 * the marker; when fewer than nbits bits are then left, it warns once (JWRN_HIT_MARKER, marking
 * the data insufficient) and pads the buffer with zeros to 25 bits. */
uint32_t vertrix_port_jpeg_fill_bit_buffer_4bbf30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t state = entry->eax;
    uint32_t get_buffer = entry->edx;
    int32_t bits_left = (int32_t)entry->ebx;
    const int32_t nbits = (int32_t)entry->ecx;
    Source source = {&port, port_u32(&port, state, STATE_CINFO),
                     port_u32(&port, state, STATE_NEXT_INPUT_BYTE), 0, 0};
    const uint32_t cinfo = source.cinfo;
    source.edx = port_u32(&port, cinfo, CINFO_UNREAD_MARKER);
    source.bytes_in_buffer = port_u32(&port, state, STATE_BYTES_IN_BUFFER);

    int at_marker = source.edx != 0;
    while (!at_marker && bits_left < MIN_GET_BITS && !port.env.failed)
    {
        int32_t c = next_byte(&source);
        if (c < 0)
        {
            return port_return(&port, 0, 0);
        }
        if (c == MARKER_PREFIX)
        {
            /* Fill bytes, then a stuffed zero or a marker. */
            do
            {
                c = next_byte(&source);
                if (c < 0)
                {
                    return port_return(&port, 0, 0);
                }
            } while (c == MARKER_PREFIX && !port.env.failed);
            if (c != 0)
            {
                port_set32(&port, cinfo, CINFO_UNREAD_MARKER, (uint32_t)c);
                at_marker = 1;
                break;
            }
            c = MARKER_PREFIX;
        }
        get_buffer = get_buffer << 8 | (uint32_t)c;
        source.edx = get_buffer;
        bits_left += 8;
    }

    if (at_marker && nbits > bits_left)
    {
        if (port_u32(&port, port_u32(&port, cinfo, CINFO_ENTROPY), ENTROPY_INSUFFICIENT_DATA) == 0)
        {
            /* WARNMS through emit_message, a method: the original leaves bytes_in_buffer in ebx
             * and cinfo in ecx. */
            port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JWRN_HIT_MARKER);
            const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
            port_call(&port, port_u32(&port, err, ERR_EMIT_MESSAGE), cinfo, 0xffffffffu,
                      source.bytes_in_buffer, cinfo);
            port_set32(&port, port_u32(&port, cinfo, CINFO_ENTROPY), ENTROPY_INSUFFICIENT_DATA, 1);
        }
        get_buffer = port_shl(get_buffer, (uint32_t)(MIN_GET_BITS - bits_left));
        bits_left = MIN_GET_BITS;
    }
    port_set32(&port, state, STATE_NEXT_INPUT_BYTE, source.next_input_byte);
    port_set32(&port, state, STATE_BYTES_IN_BUFFER, source.bytes_in_buffer);
    port_set32(&port, state, STATE_GET_BUFFER, get_buffer);
    port_set32(&port, state, STATE_BITS_LEFT, (uint32_t)bits_left);
    return port_return(&port, 1, 0);
}

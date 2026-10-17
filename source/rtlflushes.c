#include "rtlflushes.h"

/* The runtime's fputc. */

enum
{
    STREAM_POINTER = 0,
    STREAM_COUNT = 4,
    STREAM_INFO = 8,
    STREAM_FLAGS = 0xc,
    STREAM_FLAGS_HIGH = 0xd,
    STREAM_LOCK = 0x10,
    STREAM_SIZE = 0x14,
    /* Flag bits: 2 writable, 0x20 error, 0x40 binary; in the high byte 0x10 written. Any of
     * 0x400 (line buffered) or, after a newline, 0x200 (unbuffered) flushes. */
    FLAG_WRITE = 2,
    FLAG_ERROR = 0x20,
    FLAG_BINARY = 0x40,
    FLAG_WRITTEN = 0x10,
    FLUSH_ALWAYS = 0x400,
    FLUSH_NEWLINE = 0x600,
    /* The stream's info: its buffer, then the orientation (0 not yet set, 1 bytes). */
    INFO_BUFFER = 8,
    INFO_ORIENTATION = 0xc,

    /* Procedure variables holding the stream lock and unlock (no-ops here). */
    LOCK_SLOT = 0x507ca0,
    UNLOCK_SLOT = 0x507ca4,
    SET_ERRNO = 0x4dae70,
    EBADF = 4,
    BUFFER_ALLOCATE = 0x4e3b60,
    FLUSH = 0x4e3ce0,
    END_OF_FILE = 0xffffffffu
};

/* The lock and unlock go through procedure variables, so they get what the original leaves in
 * edx, ebx and ecx: the stream, the character and its ecx at that point. */
static void call_lock(Port *port, uint32_t slot, uint32_t stream, uint32_t character, uint32_t ecx)
{
    port_call(port, port_u32(port, slot, 0), port_u32(port, stream, STREAM_LOCK), stream, character,
              ecx);
}

/* Store one byte in the buffer and count it. Returns the new count. */
static uint32_t put_byte(Port *port, uint32_t stream, uint32_t byte)
{
    port_set8(port, stream, STREAM_FLAGS_HIGH,
              port_u8(port, stream, STREAM_FLAGS_HIGH) | FLAG_WRITTEN);
    const uint32_t pointer = port_u32(port, stream, STREAM_POINTER);
    port_set8(port, pointer, 0, byte);
    /* The pointer is read again after the store, as the original does. */
    port_set32(port, stream, STREAM_POINTER, port_u32(port, stream, STREAM_POINTER) + 1);
    const uint32_t count = port_u32(port, stream, STREAM_COUNT) + 1;
    port_set32(port, stream, STREAM_COUNT, count);
    return count;
}

/* Original 0x4e3e00 (eax = the character, edx = the stream): returns the character as a byte, or
 * -1 when the stream is not byte oriented or not writable (errno EBADF and the error flag) or a
 * flush fails. The buffer is made on first use (0x4e3b60, which also gets the character and the
 * orientation the original leaves in ebx and ecx). */
uint32_t vertrix_port_rtl_put_char_4e3e00(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t character = entry->eax;
    const uint32_t stream = entry->edx;

    call_lock(&port, LOCK_SLOT, stream, character, entry->ecx);
    const uint32_t info = port_u32(&port, stream, STREAM_INFO);
    const uint32_t orientation = port_u32(&port, info, INFO_ORIENTATION);
    if (orientation == 0)
    {
        port_set32(&port, info, INFO_ORIENTATION, 1);
    }
    else if (orientation != 1)
    {
        call_lock(&port, UNLOCK_SLOT, stream, character, orientation);
        return port_return(&port, END_OF_FILE, 0);
    }
    if ((port_u8(&port, stream, STREAM_FLAGS) & FLAG_WRITE) == 0)
    {
        port_call(&port, SET_ERRNO, EBADF, 0, 0, 0);
        port_set8(&port, stream, STREAM_FLAGS, port_u8(&port, stream, STREAM_FLAGS) | FLAG_ERROR);
        call_lock(&port, UNLOCK_SLOT, stream, character, orientation);
        return port_return(&port, END_OF_FILE, 0);
    }
    if (port_u32(&port, port_u32(&port, stream, STREAM_INFO), INFO_BUFFER) == 0)
    {
        port_call(&port, BUFFER_ALLOCATE, stream, 0, character, orientation);
    }

    uint32_t flush_when = FLUSH_ALWAYS;
    if (character == '\n')
    {
        flush_when = FLUSH_NEWLINE;
        if ((port_u8(&port, stream, STREAM_FLAGS) & FLAG_BINARY) == 0 &&
            put_byte(&port, stream, '\r') == port_u32(&port, stream, STREAM_SIZE) &&
            port_call(&port, FLUSH, stream, 0, character, 0) != 0)
        {
            call_lock(&port, UNLOCK_SLOT, stream, character, flush_when);
            return port_return(&port, END_OF_FILE, 0);
        }
    }
    const uint32_t count = put_byte(&port, stream, character);
    if (((port_u32(&port, stream, STREAM_FLAGS) & flush_when) != 0 ||
         count == port_u32(&port, stream, STREAM_SIZE)) &&
        port_call(&port, FLUSH, stream, 0, character, 0) != 0)
    {
        call_lock(&port, UNLOCK_SLOT, stream, character, flush_when);
        return port_return(&port, END_OF_FILE, 0);
    }
    call_lock(&port, UNLOCK_SLOT, stream, character, flush_when);
    return port_return(&port, character & 0xff, 0);
}

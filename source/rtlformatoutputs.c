#include "rtlformatoutputs.h"

enum
{
    /* The stream: its extension, its flags (dword, the error bits 0x30 in the low byte and the
     * unbuffered bit 4 of the second byte), and its lock handle. */
    STREAM_EXTENSION = 8,
    STREAM_FLAGS = 0xc,
    STREAM_MODE = 0xd,
    STREAM_LOCK = 0x10,
    EXTENSION_BUFFER = 8,
    EXTENSION_ORIENTATION = 0xc,
    BYTE_ORIENTED = 1,

    /* _SFEOF and _SFERR, cleared for the call and put back after it. */
    ERROR_BITS = 0x30,
    STREAM_ERROR = 0x20,
    /* The mode byte: unbuffered (4), which the call swaps for buffered (1) and back. */
    UNBUFFERED = 4,
    BUFFERED = 1,
    BUFFER_BITS = 0x05,

    /* The runtime's lock and unlock procedure variables. */
    LOCK = 0x507ca0,
    UNLOCK = 0x507ca4,

    ALLOCATE_BUFFER = 0x4e3b60,
    PRINT = 0x4df320,
    STREAM_WRITE = 0x4e2420,
    FLUSH = 0x4e3ce0
};

/* Original 0x4e2434 (eax = the stream, edx = the format, ebx = the arguments): the stream printf.
 * Locks the stream and, unless it is already wide-oriented, makes it byte-oriented; clears its
 * error bits for the call and gives it a buffer if it has none. An unbuffered stream is buffered
 * for the call and flushed (0x4e3ce0) after it. Prints through 0x4df320 with the stream writer
 * 0x4e2420; the count, or -1 when the stream took an error, goes to the unlock in edx. The lock
 * and unlock are procedure variables, which get all four registers as the original leaves them.
 * Callers read neither eax nor edx. */
uint32_t vertrix_port_rtl_format_output_4e2434(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t stream = entry->eax;

    port_call(&port, port_u32(&port, LOCK, 0), port_u32(&port, stream, STREAM_LOCK), entry->edx,
              entry->ebx, entry->ecx);
    const uint32_t format = vertrix_lift_edx;
    uint32_t extension = port_u32(&port, stream, STREAM_EXTENSION);
    const uint32_t orientation = port_u32(&port, extension, EXTENSION_ORIENTATION);
    if (orientation != BYTE_ORIENTED)
    {
        if (orientation != 0)
        {
            port_call(&port, port_u32(&port, UNLOCK, 0), port_u32(&port, stream, STREAM_LOCK),
                      format, entry->ebx, orientation);
            return port_return(&port, 0, 0);
        }
        port_set32(&port, extension, EXTENSION_ORIENTATION, BYTE_ORIENTED);
    }

    const uint32_t flags = port_u32(&port, stream, STREAM_FLAGS);
    port_set8(&port, stream, STREAM_FLAGS, flags & ~ERROR_BITS);
    const uint32_t errors = flags & ERROR_BITS;
    extension = port_u32(&port, stream, STREAM_EXTENSION);
    if (port_u32(&port, extension, EXTENSION_BUFFER) == 0)
    {
        port_call(&port, ALLOCATE_BUFFER, stream, 0, 0, 0);
    }

    const int unbuffered = (port_u8(&port, stream, STREAM_MODE) & UNBUFFERED) != 0;
    if (unbuffered)
    {
        port_set8(&port, stream, STREAM_MODE,
                  (port_u8(&port, stream, STREAM_MODE) & ~BUFFER_BITS) | BUFFERED);
    }
    uint32_t count = port_call(&port, PRINT, stream, format, entry->ebx, STREAM_WRITE);
    uint32_t unlock_ebx = entry->ebx;
    if (unbuffered)
    {
        /* bl carries the mode byte the original builds in it. */
        const uint32_t mode = (port_u8(&port, stream, STREAM_MODE) & ~BUFFER_BITS) | UNBUFFERED;
        port_set8(&port, stream, STREAM_MODE, mode);
        unlock_ebx = (unlock_ebx & 0xffffff00u) | mode;
        port_call(&port, FLUSH, stream, 0, 0, 0);
    }
    if (port_u8(&port, stream, STREAM_FLAGS) & STREAM_ERROR)
    {
        count = 0xffffffffu;
    }
    const uint32_t lock = port_u32(&port, stream, STREAM_LOCK);
    port_set32(&port, stream, STREAM_FLAGS, port_u32(&port, stream, STREAM_FLAGS) | errors);
    port_call(&port, port_u32(&port, UNLOCK, 0), lock, count, unlock_ebx, STREAM_WRITE);
    return port_return(&port, 0, 0);
}

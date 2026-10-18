#include "rtlstreamcloses.h"

enum
{
    /* The frame under the return slot: five saved registers, then the temporary file's name. */
    BELOW = 0x128,
    NAME = 0x128,

    /* A stream: its buffer record (+8: the buffer; +0x14: the temporary file's number), its flags
     * (+0xc: 0 when closed, bit 3 an allocated buffer; +0xd: bit 4 writing, bit 3 temporary) and
     * its handle. */
    STREAM_BUFFER = 8,
    STREAM_FLAGS = 0xc,
    STREAM_MODE = 0xd,
    STREAM_HANDLE = 0x10,
    BUFFER_BASE = 8,
    BUFFER_TEMPORARY = 0x14,

    FLAG_ALLOCATED = 8,
    MODE_WRITING = 0x10,
    MODE_TEMPORARY = 8,
    FAILED = 0xffffffffu,
    SEEK_START = 0,

    LOCK = 0x507ca0,
    UNLOCK = 0x507ca4,
    RELEASE = 0x507cac,
    FLUSH = 0x4e3ce0,
    TELL = 0x4ebe60,
    SEEK = 0x4e0150,
    CLOSE_HANDLE = 0x4e0fc0,
    FREE = 0x4ea190,
    TEMPORARY_NAME = 0x4e7f18,
    REMOVE = 0x4e9f00
};

/* Original 0x4e7fc4 (eax = the stream, edx = whether to close its handle): the runtime's stream
 * close. A closed stream (+0xc 0) returns -1. A stream being written is flushed (0x4e3ce0) first;
 * then, under the lock routines 0x507ca0 and 0x507ca4, the handle is sought back to the stream's
 * place (0x4ebe60, 0x4e0150 from the start) unless that is -1, closed when asked (0x4e0fc0), an
 * allocated buffer freed (0x4ea190) and a temporary file removed by its name (0x4e7f18 into the
 * frame, then 0x4e9f00); a closed handle is also released (0x507cac). Returns the flush's result
 * or'd with the close's. */
uint32_t vertrix_port_rtl_stream_close_4e7fc4(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t stream = entry->eax;
    const uint32_t close_handle = entry->edx;
    const uint32_t name = entry->esp - NAME;
    if (port_u32(&port, stream, STREAM_FLAGS) == 0)
    {
        return port_return(&port, FAILED, entry->edx);
    }
    uint32_t ebx = entry->ebx;
    uint32_t result = 0;
    uint32_t edx = close_handle;
    if ((port_u8(&port, stream, STREAM_MODE) & MODE_WRITING) != 0)
    {
        result = port_call(&port, FLUSH, stream, edx, ebx, stream);
        edx = vertrix_lift_edx;
    }
    port_call(&port, port_u32(&port, LOCK, 0), port_u32(&port, stream, STREAM_HANDLE), edx, ebx,
              stream);
    const uint32_t place = port_call(&port, TELL, stream, vertrix_lift_edx, ebx, stream);
    edx = vertrix_lift_edx;
    if (place != FAILED)
    {
        ebx = SEEK_START;
        port_call(&port, SEEK, port_u32(&port, stream, STREAM_HANDLE), place, ebx, stream);
        edx = vertrix_lift_edx;
    }
    if (close_handle != 0)
    {
        result |= port_call(&port, CLOSE_HANDLE, port_u32(&port, stream, STREAM_HANDLE), edx, ebx,
                            stream);
        edx = vertrix_lift_edx;
    }
    if ((port_u8(&port, stream, STREAM_FLAGS) & FLAG_ALLOCATED) != 0)
    {
        port_call(&port, FREE, port_u32(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_BASE),
                  edx, ebx, stream);
        edx = vertrix_lift_edx;
        port_set32(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_BASE, 0);
    }
    if ((port_u8(&port, stream, STREAM_MODE) & MODE_TEMPORARY) != 0)
    {
        edx = port_u8(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_TEMPORARY);
        port_call(&port, TEMPORARY_NAME, name, edx, ebx, stream);
        port_call(&port, REMOVE, name, vertrix_lift_edx, ebx, stream);
        edx = vertrix_lift_edx;
    }
    port_call(&port, port_u32(&port, UNLOCK, 0), port_u32(&port, stream, STREAM_HANDLE), edx, ebx,
              stream);
    if (close_handle != 0)
    {
        port_call(&port, port_u32(&port, RELEASE, 0), port_u32(&port, stream, STREAM_HANDLE),
                  vertrix_lift_edx, ebx, stream);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

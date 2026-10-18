#include "rtlstreamflushes.h"

enum
{
    /* A stream: the next byte, the bytes buffered, its buffer record (+8: the buffer; +0x10: the
     * commit flag), its flags (+0xc, +0xd) and its handle. */
    STREAM_NEXT = 0,
    STREAM_COUNT = 4,
    STREAM_BUFFER = 8,
    STREAM_FLAGS = 0xc,
    STREAM_MODE = 0xd,
    STREAM_HANDLE = 0x10,
    BUFFER_BASE = 8,
    BUFFER_FLAGS = 0x10,

    FLAG_WRITE = 2,
    FLAG_ERROR = 0x20,
    MODE_WRITING = 0x10,
    MODE_DIRTY = 0x20,
    BUFFER_COMMIT = 1,
    FAILED = 0xffffffffu,
    ENOSPC_CODE = 0xc,
    SEEK_CURRENT = 1,

    LOCK = 0x507ca0,
    UNLOCK = 0x507ca4,
    WRITE = 0x4e3bf0,
    SET_ERRNO = 0x4dae70,
    SEEK = 0x4e0150,
    COMMIT = 0x4e7c30
};

static uint32_t with_low_byte(uint32_t value, uint32_t byte)
{
    return (value & 0xffffff00u) | (byte & 0xff);
}

/* Original 0x4e3ce0 (eax = the stream): the runtime's stream flush, under the lock routines
 * 0x507ca0 and 0x507ca4. A stream being written (+0xd bit 4, cleared) writes its buffered bytes
 * (0x4e3bf0) until none are left or one write fails (-1, or 0 with errno 0xc), marking an error
 * (+0xc bit 5). A stream being read that is not dirty seeks back over its buffered bytes (0x4e0150
 * from the current place), an error on -1. The buffer is then reset and, when nothing failed and
 * the buffer asks for it, the handle committed (0x4e7c30). Returns 0 or -1 and keeps edx. ebx and
 * edx are handed on as the original leaves them. */
uint32_t vertrix_port_rtl_stream_flush_4e3ce0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t stream = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result = 0;
    port_call(&port, port_u32(&port, LOCK, 0), port_u32(&port, stream, STREAM_HANDLE), entry->edx,
              ebx, stream);
    uint32_t edx = vertrix_lift_edx;
    const uint32_t mode = port_u8(&port, stream, STREAM_MODE);
    if ((mode & MODE_WRITING) != 0)
    {
        ebx = (ebx & 0xffff00ffu) | ((mode & ~MODE_WRITING & 0xff) << 8);
        port_set8(&port, stream, STREAM_MODE, mode & ~MODE_WRITING);
        if ((port_u8(&port, stream, STREAM_FLAGS) & FLAG_WRITE) != 0)
        {
            ebx = port_u32(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_BASE);
            uint32_t left = ebx != 0 ? port_u32(&port, stream, STREAM_COUNT) : 0;
            uint32_t next = ebx;
            while (left != 0 && result == 0 && !port.env.failed)
            {
                ebx = left;
                uint32_t written = port_call(&port, WRITE, port_u32(&port, stream, STREAM_HANDLE),
                                             next, ebx, stream);
                edx = written;
                if (written == FAILED)
                {
                    ebx = with_low_byte(ebx, port_u8(&port, stream, STREAM_FLAGS) | FLAG_ERROR);
                    port_set8(&port, stream, STREAM_FLAGS, ebx);
                    result = FAILED;
                }
                else if (written == 0)
                {
                    port_call(&port, SET_ERRNO, ENOSPC_CODE, edx, ebx, stream);
                    edx = vertrix_lift_edx;
                    port_set8(&port, stream, STREAM_FLAGS,
                              port_u8(&port, stream, STREAM_FLAGS) | FLAG_ERROR);
                    result = FAILED;
                }
                next += edx;
                left -= edx;
            }
        }
    }
    else if (port_u32(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_BASE) != 0)
    {
        port_set8(&port, stream, STREAM_FLAGS,
                  port_u8(&port, stream, STREAM_FLAGS) & ~MODE_WRITING);
        if ((port_u8(&port, stream, STREAM_MODE) & MODE_DIRTY) == 0)
        {
            const uint32_t count = port_u32(&port, stream, STREAM_COUNT);
            uint32_t sought = count;
            if (count != 0)
            {
                ebx = SEEK_CURRENT;
                edx = count;
                sought = port_call(&port, SEEK, port_u32(&port, stream, STREAM_HANDLE), edx, ebx,
                                   stream);
                edx = vertrix_lift_edx;
            }
            if (sought == FAILED)
            {
                ebx = with_low_byte(ebx, port_u8(&port, stream, STREAM_FLAGS) | FLAG_ERROR);
                port_set8(&port, stream, STREAM_FLAGS, ebx);
                result = FAILED;
            }
        }
    }
    const uint32_t base = port_u32(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_BASE);
    port_set32(&port, stream, STREAM_COUNT, 0);
    port_set32(&port, stream, STREAM_NEXT, base);
    if (result == 0 &&
        (port_u8(&port, port_u32(&port, stream, STREAM_BUFFER), BUFFER_FLAGS) & BUFFER_COMMIT) != 0)
    {
        if (port_call(&port, COMMIT, port_u32(&port, stream, STREAM_HANDLE), edx, ebx, stream) ==
            FAILED)
        {
            result = FAILED;
        }
        edx = vertrix_lift_edx;
    }
    port_call(&port, port_u32(&port, UNLOCK, 0), port_u32(&port, stream, STREAM_HANDLE), edx, ebx,
              stream);
    return port_return(&port, result, entry->edx);
}

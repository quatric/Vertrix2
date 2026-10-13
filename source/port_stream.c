#include "port_stream.h"

enum
{
    STREAM_POSITION = 0x04,
    STREAM_END = 0x08,
    WANTED = 0x5bb234,
    LEFT = 0x5bb238,
    COMPLETE = 0x5bb230,
    COPIED = 0x5bb22c,
    SKIPPED = 0x5bb24c
};

uint32_t vertrix_port_stream_read_exact(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t to = entry->edx;
    uint32_t wanted = entry->ebx * entry->ecx;
    uint32_t left;
    uint32_t count;
    uint32_t complete;
    uint32_t from;
    uint32_t i;
    port_open(&port, calls, services, globals, entry);
    left = port_u32(&port, stream, STREAM_END);
    port_set32(&port, 0, WANTED, wanted);
    left -= port_u32(&port, stream, STREAM_POSITION);
    port_set32(&port, 0, LEFT, left);
    wanted = port_u32(&port, 0, WANTED);
    left = port_u32(&port, 0, LEFT);
    complete = wanted <= left;
    count = complete ? wanted : left;
    port_set32(&port, 0, COMPLETE, complete);
    port_set32(&port, 0, COPIED, count);
    if (count == 0)
    {
        return port_return(&port, port_u32(&port, 0, COMPLETE), entry->edx);
    }
    from = port_u32(&port, stream, STREAM_POSITION);
    /* rep movsd and rep movsb: each element addressed through the moving pointers. */
    for (i = 0; i < count / 4; i++, from += 4, to += 4)
    {
        port_set32(&port, to, 0, port_u32(&port, from, 0));
    }
    for (i = 0; i < (count & 3); i++, from++, to++)
    {
        port_set8(&port, to, 0, port_u8(&port, from, 0));
    }
    count = port_u32(&port, 0, COPIED);
    port_set32(&port, stream, STREAM_POSITION, port_u32(&port, stream, STREAM_POSITION) + count);
    complete = port_u32(&port, 0, COMPLETE);
    port_set32(&port, 0, COPIED, count);
    return port_return(&port, complete, stream);
}

uint32_t vertrix_port_stream_skip(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t count = entry->edx;
    uint32_t step;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)count < 0)
    {
        step = 0u - count;
    }
    else
    {
        uint32_t left =
            port_u32(&port, stream, STREAM_END) - port_u32(&port, stream, STREAM_POSITION);
        if (count >= left)
        {
            count = left;
        }
        step = count;
    }
    port_set32(&port, stream, STREAM_POSITION, port_u32(&port, stream, STREAM_POSITION) + step);
    port_set32(&port, 0, SKIPPED, step);
    return port_return(&port, stream, count);
}

uint32_t vertrix_port_stream_done(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t position;
    port_open(&port, calls, services, globals, entry);
    position = port_u32(&port, stream, STREAM_POSITION);
    return port_return(&port, position >= port_u32(&port, stream, STREAM_END), entry->edx);
}

uint32_t vertrix_port_stream_done_475df0(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t position;
    port_open(&port, calls, services, globals, entry);
    position = port_u32(&port, stream, 0x44);
    return port_return(&port, position >= port_u32(&port, stream, 0x48), entry->edx);
}

uint32_t vertrix_port_stream_position(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, STREAM_POSITION), entry->edx);
}

uint32_t vertrix_port_stream_read_token(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->edx;
    uint32_t text = entry->ebx;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ca370, text, 0x510a59, ebx, stream);
    edx = vertrix_lift_edx;
    for (;;)
    {
        uint32_t byte;
        eax = port_call(&port, 0x48a910, stream, edx, ebx, stream);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            break;
        }
        eax = port_call(&port, 0x48aa80, stream, 1, ebx, stream);
        byte = port_u8(&port, eax, 0);
        ebx = (ebx & 0xffffff00u) | byte;
        port_call(&port, 0x48aa90, stream, vertrix_lift_edx, ebx, stream);
        edx = vertrix_lift_edx;
        if (byte == '\\' || byte == '\n' || byte == '\r')
        {
            break;
        }
        port_call(&port, 0x4ca630, text, byte, ebx, stream);
        edx = vertrix_lift_edx;
    }
    port_call(&port, 0x4ce030, text, edx, ebx, stream);
    eax = port_call(&port, 0x4cdfe0, text, vertrix_lift_edx, ebx, stream);
    return port_return(&port, eax, vertrix_lift_edx);
}

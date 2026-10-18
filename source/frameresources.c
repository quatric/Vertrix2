#include "frameresources.h"

enum
{
    RESOURCE_FRAMES = 0x00,
    RESOURCE_CHILDREN = 0x0c,
    RESOURCE_CHILD_INDEXES = 0x10,
    RESOURCE_KIND = 0x14,
    KIND_COMPOSITE = 1,
    ACTOR_RESOURCE = 0xb0,
    ACTOR_IMAGE = 0xb4,
    ACTOR_FRAME = 0xb8,
    RESOURCE_KIND_CALL = 0x4877e0,
    FRAME_RESOURCE_GET = 0x4877f0
};

uint32_t vertrix_port_resource_kind(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, RESOURCE_KIND), entry->edx);
}

uint32_t vertrix_port_frame_resource_get(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t index = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t frames;
    port_open(&port, calls, services, globals, entry);
    while (port_call(&port, RESOURCE_KIND_CALL, record, edx, index, record) == KIND_COMPOSITE)
    {
        uint32_t child_index =
            port_u32(&port, port_u32(&port, record, RESOURCE_CHILD_INDEXES), index * 4);
        edx = port_u32(&port, record, RESOURCE_CHILDREN);
        record = port_u32(&port, edx, index * 4);
        index = child_index;
    }
    frames = port_u32(&port, record, RESOURCE_FRAMES);
    return port_return(&port, port_u32(&port, frames, index * 4), frames);
}

uint32_t vertrix_port_actor_lookup_image(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t image;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, actor, ACTOR_RESOURCE) == 0)
    {
        return port_return(&port, actor, entry->edx);
    }
    image = port_call(&port, FRAME_RESOURCE_GET, port_u32(&port, actor, ACTOR_RESOURCE),
                      port_u32(&port, actor, ACTOR_FRAME), entry->ebx, actor);
    port_set32(&port, actor, ACTOR_IMAGE, image);
    return port_return(&port, image, entry->edx);
}

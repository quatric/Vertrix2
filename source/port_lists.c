#include "port_lists.h"

/* List, text, pool and runtime string helpers. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords (the nearest to
 * the stack pointer first). */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* A guard record (the chain, 0x4ec1ec, `guard`, 0) at `record`. */
static void guard_at(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x4b6fa0: the item edx of the list eax (+4, count +8), or 0 past the end. */
uint32_t vertrix_port_list_item_4b6fa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx < port_u32(&port, list, 8))
    {
        result = port_u32(&port, port_u32(&port, list, 4), entry->edx * 4);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4b5f50: each item of the list eax whose 0x4ac900 is edx removed by the list's
 * method +0x14 (with its index); the count +8. */
uint32_t vertrix_port_object_list_prune_4b5f50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t wanted = entry->edx;
    uint32_t index = 0;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, wanted);
    port_set32(&port, ebp, -0x14u, 0);
    while (index < port_u32(&port, list, 8))
    {
        uint32_t item;
        ebx = port_u32(&port, ebp, -0x14u);
        item = port_u32(&port, port_u32(&port, list, 4) + ebx, 0);
        edi = port_u32(&port, ebp, -0x18u);
        if (call_frame(&port, 0x4ac900, item, edx, ebx, list, index, edi, ebp, NULL, 0) == edi)
        {
            ebx = 1;
            edi = port_u32(&port, list, 0);
            call_frame(&port, port_u32(&port, edi, 0x14), list, index, ebx, list, index, edi, ebp,
                       NULL, 0);
        }
        else
        {
            index++;
            port_set32(&port, ebp, -0x14u, ebx + 4);
        }
        edx = vertrix_lift_edx;
    }
    return port_return(&port, port_u32(&port, list, 8), edx);
}

/* Original 0x4b73a0: the text eax of the item ebx of the list eax (0x4b6fa0) put in the string
 * edx: the empty text 0x5110c1 by 0x4ca280, then the item's (+0x14) by 0x4ca310 when there is one;
 * the string. Under the guard record 0x518540. */
uint32_t vertrix_port_list_text_name_4b73a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t text = entry->edx;
    uint32_t item;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_at(&port, ebp - 0x20, 0x518540);
    item = call_frame(&port, 0x4b6fa0, list, entry->ebx, entry->ebx, text, list, 0x518540, ebp,
                      NULL, 0);
    call_frame(&port, 0x4ca280, text, 0x5110c1, item, text, list, 0x518540, ebp, NULL, 0);
    if (item != 0)
    {
        call_frame(&port, 0x4ca310, text, item + 0x14, item, text, list, 0x518540, ebp, NULL, 0);
    }
    return port_return(&port, text, vertrix_lift_edx);
}

/* Original 0x4b4700: the index (from -1) of the text (the owner's +0x160, its +0x15c) whose place
 * (0x4b46e0, with the owner's signed word +0xe) is nearest edx, within 20000; -1 for none. edx the
 * sign of the last distance. */
uint32_t vertrix_port_object_text_nearest_4b4700(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t text;
    int32_t length = 0;
    int32_t index;
    uint32_t best = 0x4e20;
    uint32_t edx = 0xffffffffu;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->edx);
    text = port_u32(&port, port_u32(&port, object, 0x160), 0x15c);
    port_set32(&port, ebp, -0x10u, 0xffffffffu);
    while (port_u8(&port, text, (uint32_t)length) != 0)
    {
        length++;
    }
    port_set32(&port, ebp, -0x14u, (uint32_t)length);
    for (index = -1; index < length; index++)
    {
        uint32_t owner = port_u32(&port, object, 0x160);
        uint32_t edi = port_u32(&port, owner, 0xc);
        int32_t distance;
        distance = (int32_t)call_frame(&port, 0x4b46e0, object, (uint32_t)index, best,
                                       (uint32_t)index, object, edi, ebp, NULL, 0);
        distance = distance - (int32_t)port_u32(&port, ebp, -0x18u) + ((int32_t)edi >> 16);
        edx = distance < 0 ? 0xffffffffu : 0;
        distance = distance < 0 ? -distance : distance;
        if ((int32_t)distance < (int32_t)best)
        {
            port_set32(&port, ebp, -0x10u, (uint32_t)index);
            best = (uint32_t)distance;
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x10u), edx);
}

/* Original 0x4b9cf0: the stream's buffer record +0x18 (allocated when missing: 40 bytes and a 4096
 * byte buffer at its +0x20, by the pool's (+4) method +0) given the reader methods 0x4b9c10,
 * 0x4b9c20, 0x4b9cb0, 0x4c0860 and 0x4b9ce0, empty, and the source edx at +0x1c. */
uint32_t vertrix_port_stream_reader_setup_4b9cf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t source = entry->edx;
    uint32_t record;
    uint32_t result = entry->eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    edx = port_u32(&port, stream, 0x18);
    if (edx == 0)
    {
        uint32_t pool = port_u32(&port, stream, 4);
        record = call_frame(&port, port_u32(&port, pool, 0), stream, 0, 0x28, stream, source, pool,
                            ebp, NULL, 0);
        port_set32(&port, ebp, -0x14u, record);
        pool = port_u32(&port, stream, 4);
        port_set32(&port, stream, 0x18, record);
        result = call_frame(&port, port_u32(&port, pool, 0), stream, 0, 0x1000, stream, source,
                            pool, ebp, NULL, 0);
        port_set32(&port, port_u32(&port, ebp, -0x14u), 0x20, result);
        edx = vertrix_lift_edx;
    }
    record = port_u32(&port, stream, 0x18);
    port_set32(&port, record, 8, 0x4b9c10);
    port_set32(&port, record, 0xc, 0x4b9c20);
    port_set32(&port, record, 0x10, 0x4b9cb0);
    port_set32(&port, record, 0x14, 0x4c0860);
    port_set32(&port, record, 0x18, 0x4b9ce0);
    port_set32(&port, record, 4, 0);
    port_set32(&port, record, 0, 0);
    port_set32(&port, record, 0x1c, source);
    return port_return(&port, result, edx);
}

/* The pool blocks of 0x4c5120 and 0x4c5190: for a kind other than 1 the error 14 (the handler's
 * +0x14 and +0x18 the kind, its method +0) first; then a 128-byte block (0x4c4d20) with +0 and
 * +0x28 0, +8 ecx, +4 and +0xc the two stack arguments and +0x20 ebx, put first on the list `head`
 * of the pool (+4). The block, edx the list's old head. */
static uint32_t pool_block(PORT_SIGNATURE, uint32_t head)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t owner = entry->eax;
    uint32_t pool;
    uint32_t block;
    uint32_t edx = entry->edx;
    uint32_t old;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    pool = port_u32(&port, owner, 4);
    if (entry->edx != 1)
    {
        uint32_t handler = port_u32(&port, owner, 0);
        port_set32(&port, handler, 0x14, 0xe);
        port_set32(&port, port_u32(&port, owner, 0), 0x18, entry->edx);
        handler = port_u32(&port, owner, 0);
        call_frame(&port, port_u32(&port, handler, 0), owner, entry->edx, handler, entry->ecx,
                   owner, pool, ebp, NULL, 0);
        edx = vertrix_lift_edx;
    }
    block = call_frame(&port, 0x4c4d20, owner, edx, 0x80, entry->ecx, owner, pool, ebp, NULL, 0);
    port_set32(&port, block, 0, 0);
    port_set32(&port, block, 0x28, 0);
    port_set32(&port, block, 8, entry->ecx);
    port_set32(&port, block, 4, port_u32(&port, entry->esp, 4));
    port_set32(&port, block, 0xc, port_u32(&port, entry->esp, 8));
    port_set32(&port, block, 0x20, port_u32(&port, ebp, -0xcu));
    old = port_u32(&port, pool, head);
    port_set32(&port, block, 0x2c, old);
    port_set32(&port, pool, head, block);
    return port_return(&port, block, old);
}

/* Original 0x4c5120: the list +0x44. */
uint32_t vertrix_port_pool_block_4c5120(PORT_SIGNATURE)
{
    return pool_block(calls, services, globals, entry, 0x44);
}

/* Original 0x4c5190: the list +0x48. */
uint32_t vertrix_port_pool_block_4c5190(PORT_SIGNATURE)
{
    return pool_block(calls, services, globals, entry, 0x48);
}

/* Original 0x4cda12: 0x4cd8b0 on eax with a local holding 0x4e0f8b's answer and the guard chain
 * in ebx. */
uint32_t vertrix_port_rtl_local_chain_call_4cda12(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t local = entry->esp - BELOW;
    uint32_t object = entry->eax;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    result = call_frame(&port, 0x4e0f8b, object, entry->edx, entry->ebx, object, entry->esi,
                        entry->edi, entry->ebp, NULL, 0);
    port_set32(&port, local, 0, result);
    result = call_frame(&port, 0x4cd8b0, object, local, port.env.chain, object, entry->esi,
                        entry->edi, entry->ebp, NULL, 0);
    return port_return(&port, result, entry->edx);
}

/* The tails of 0x4cdaf0 and 0x4cdb70: the count ebx kept within 0 and the length of the string
 * eax (-0xc +4), then 0x4ca070 on the string edx and 0x4ca240 copying into it the characters of
 * eax from that count to the end (`from_count`) or the first ones; the string edx. */
static uint32_t string_part(Port *port, const LiftEntry *entry, uint32_t ebp, int from_count,
                            uint32_t esi, uint32_t edi)
{
    uint32_t source = entry->eax;
    uint32_t target = entry->edx;
    int32_t count = (int32_t)entry->ebx;
    uint32_t zero[1] = {0};
    int32_t length = (int32_t)port_u32(port, port_u32(port, source, 0) - 0xc, 4);
    if (count < 0)
    {
        count = 0;
    }
    else if (count > length)
    {
        count = length;
    }
    call_frame(port, 0x4ca070, target, entry->edx, (uint32_t)count, entry->ecx, esi, edi, ebp, NULL,
               0);
    length = (int32_t)port_u32(port, port_u32(port, source, 0) - 0xc, 4);
    call_frame(port, 0x4ca240, source, target, (uint32_t)count,
               from_count ? (uint32_t)(length - count) : 0, esi, edi, ebp, zero, 1);
    return target;
}

/* Original 0x4cdaf0: the characters from the count on, under the guard record 0x518f5c. */
uint32_t vertrix_port_rtl_string_tail_4cdaf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 0x10;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_at(&port, ebp - 0x14, 0x518f5c);
    result = string_part(&port, entry, ebp, 1, entry->eax, entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4cdb70: the first count characters, under the guard record 0x518f60. */
uint32_t vertrix_port_rtl_string_head_4cdb70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_at(&port, entry->esp - BELOW, 0x518f60);
    result = string_part(&port, entry, entry->ebp, 0, entry->edx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

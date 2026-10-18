#include "records.h"

/* Array list release, the file text read, text list steps, the menu item builder, the object text
 * value, the decoder's start and its message format, buffer setup and pool allocation. */

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4874f0: the array list's release: with +0x14 its three blocks (+8, +0xc, +0x10)
 * are freed (0x4ea190) and the list emptied; otherwise each item (0x4830f0, the offset stepping
 * by 4 from the edx the call leaves) and the items block (+0) are. */
uint32_t vertrix_port_array_list_release_4874f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t eax = list;
    uint32_t edx = entry->edx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, list, 0x14) != 0)
    {
        uint32_t ecx = port_u32(&port, list, 8);
        if (ecx != 0)
        {
            eax = port_call_with(&port, 0x4ea190, ecx, edx, list, ecx, esi, edi, entry->ebp);
            edx = vertrix_lift_edx;
            port_set32(&port, list, 8, 0);
        }
        esi = port_u32(&port, list, 0xc);
        if (esi != 0)
        {
            eax = port_call_with(&port, 0x4ea190, esi, edx, list, ecx, esi, edi, entry->ebp);
            edx = vertrix_lift_edx;
            port_set32(&port, list, 0xc, 0);
        }
        edi = port_u32(&port, list, 0x10);
        if (edi != 0)
        {
            eax = port_call_with(&port, 0x4ea190, edi, edx, list, ecx, esi, edi, entry->ebp);
            port_set32(&port, list, 0x10, 0);
        }
        port_set32(&port, list, 0x14, 0);
        port_set32(&port, list, 4, 0);
        return port_return(&port, eax, entry->edx);
    }
    if (port_u32(&port, list, 0) != 0)
    {
        uint32_t ecx = 0;
        edx = port_u32(&port, list, 4);
        if (edx != 0)
        {
            edx = 0;
            do
            {
                uint32_t item = port_u32(&port, port_u32(&port, list, 0), edx);
                ecx++;
                port_call_with(&port, 0x4830f0, item, edx, list, ecx, esi, edi, entry->ebp);
                esi = port_u32(&port, list, 4);
                edx = vertrix_lift_edx + 4;
            } while (ecx < esi);
        }
        eax = port_call_with(&port, 0x4ea190, port_u32(&port, list, 0), edx, list, ecx, esi, edi,
                             entry->ebp);
        port_set32(&port, list, 0, 0);
    }
    port_set32(&port, list, 4, 0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4893c0: the file's text (guarded 0x517190): 0x489230 gives its size into the frame,
 * a buffer one longer (0x4ec160) is read by 0x489230 and ended with a nul; 0 when either read
 * fails (the buffer freed by 0x4ea190). */
uint32_t vertrix_port_file_text_read_4893c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t file = entry->eax;
    uint32_t buffer;
    uint32_t size;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, 0x517190);
    if (port_call_with(&port, 0x489230, file, ebp - 0x1c, 1, 4, entry->esi, file, ebp) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    buffer = port_call_with(&port, 0x4ec160, port_u32(&port, ebp, -0x1cu) + 1, 1, 1, 1, entry->esi,
                            file, ebp);
    port_set32(&port, ebp, -0x18u, buffer);
    size = port_u32(&port, ebp, -0x1cu);
    if (port_call_with(&port, 0x489230, file, buffer, size, 1, buffer, file, ebp) == 1)
    {
        port_set8(&port, buffer + port_u32(&port, ebp, -0x1cu), 0, 0);
        return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
    }
    port_call_with(&port, 0x4ea190, buffer, vertrix_lift_edx, size, 1, 0, file, ebp);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, 0, entry->edx);
}

/* The text list step of 0x4b3880 and 0x4b3940: the last of the list's texts (+0x170, +0x174)
 * that 0x4ccfe0 finds equal to the shown text (+0x160 +0x15c) is stepped back or on (wrapping)
 * into the shown text (0x4ca370); 1 when one was found, otherwise 0. */
static uint32_t text_list_step(PORT_SIGNATURE, int forward)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t found = 0xffffffffu;
    uint32_t index = 0;
    uint32_t esi;
    uint32_t count;
    uint32_t texts;
    uint32_t shown;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    esi = port_u32(&port, object, 0x174);
    port_set32(&port, ebp, -0x18u, 0);
    if (esi != 0)
    {
        esi = 0;
        do
        {
            uint32_t text = port_u32(&port, port_u32(&port, object, 0x160), 0x15c);
            uint32_t item = port_u32(&port, port_u32(&port, object, 0x170), esi);
            if (port_call_with(&port, 0x4ccfe0, item, text, object, index, esi, found, ebp) == 0)
            {
                found = index;
            }
            index++;
            esi += 4;
        } while (index < port_u32(&port, object, 0x174));
    }
    if (found == 0xffffffffu)
    {
        return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
    }
    count = port_u32(&port, object, 0x174);
    texts = port_u32(&port, object, 0x170);
    shown = port_u32(&port, object, 0x160) + 0x15c;
    if (!forward)
    {
        if ((int32_t)found <= 0)
        {
            port_call_with(&port, 0x4ca370, shown, port_u32(&port, texts, (count - 1) * 4), object,
                           index, esi, found, ebp);
            port_set32(&port, ebp, -0x18u, 1);
            return port_return(&port, 1, entry->edx);
        }
        port_set32(&port, ebp, -0x18u, 1);
        port_call_with(&port, 0x4ca370, shown, port_u32(&port, texts, found * 4 - 4), object, 1,
                       esi, found - 1, ebp);
        return port_return(&port, port_u32(&port, ebp, -0x18u), entry->edx);
    }
    if (found >= count - 1)
    {
        port_call_with(&port, 0x4ca370, shown, port_u32(&port, texts, 0), object, index, esi, found,
                       ebp);
        port_set32(&port, ebp, -0x18u, 1);
        return port_return(&port, 1, entry->edx);
    }
    port_call_with(&port, 0x4ca370, shown, port_u32(&port, texts, found * 4 + 4), object, 1, esi,
                   found, ebp);
    port_set32(&port, ebp, -0x18u, 1);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4b3880: back. */
uint32_t vertrix_port_text_list_back_4b3880(PORT_SIGNATURE)
{
    return text_list_step(calls, services, globals, entry, 0);
}

/* Original 0x4b3940: on. */
uint32_t vertrix_port_text_list_forward_4b3940(PORT_SIGNATURE)
{
    return text_list_step(calls, services, globals, entry, 1);
}

/* Original 0x4b5580: the menu item (guarded 0x5181b0): 0x4b6350 builds it with the methods
 * 0x518244 and a 0x160-byte child (0x4ca000, 0x4b5400); the item the edx left gives has +0x180,
 * +0x184 and +0x188 0, +0x190 1 and the child +0x18c, and is returned. */
uint32_t vertrix_port_menu_item_build_4b5580(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t owner = entry->eax;
    uint32_t item;
    uint32_t child;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x34, 0x5181b0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, owner);
    item = port_call_with(&port, 0x4b6350, owner, owner, 0x5181b0, 0x4ec1ec, 0, 1, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    port_set32(&port, item, 0x158, 0x518244);
    child = port_call_with(&port, 0x4ca000, 0x160, item, 0x5181b0, 0x4ec1ec, 0, 1, ebp);
    if (child != 0)
    {
        child =
            port_call_with(&port, 0x4b5400, child, vertrix_lift_edx, 0x5181b0, 0x4ec1ec, 0, 1, ebp);
    }
    item = vertrix_lift_edx;
    port_set32(&port, item, 0x184, 0);
    port_set32(&port, item, 0x188, 0);
    port_set32(&port, item, 0x180, 0);
    port_set32(&port, item, 0x190, 1);
    port_set32(&port, item, 0x18c, child);
    return port_return(&port, item, entry->edx);
}

/* Original 0x4b6930: the object's text value (guarded 0x51839c): its text (+0x15c, 0x4cdb70 into
 * the frame) when not empty is read by 0x440610 with its signed byte +0x160 and the byte +0x44
 * into the frame; the text is released (0x4ca210). The value, or 0. */
uint32_t vertrix_port_object_text_value_4b6930(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t value;
    uint32_t ebx;
    uint32_t pointer[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, 0x51839c);
    port_call_with(&port, 0x4cdb70, object + 0x15c, ebp - 0x1c, entry->edx, object, 0x51839c, 0,
                   ebp);
    port_set32(&port, ebp, -0x24u, 1);
    if (port_u32(&port, port_u32(&port, ebp, -0x1cu) - 0xc, 4) == 0)
    {
        port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, entry->edx, object, 0x51839c, 0, ebp);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    ebx = port_u8(&port, object, 0x44);
    pointer[0] = ebp - 0x14;
    call_frame(&port, 0x440610, (uint32_t)(int32_t)(int8_t)port_u8(&port, object, 0x160),
               port_u32(&port, ebp, -0x1cu), ebx, ebp - 0x18, 0x51839c, 0, ebp, pointer, 1);
    value = port_u32(&port, ebp, -0x18u);
    port_set32(&port, ebp, -0x24u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x1c, 0, ebx, value, 0x51839c, 0, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    return port_return(&port, value, vertrix_lift_edx);
}

/* Original 0x4b9710: the decoder's start (+0x14 the state): from 205 or 206 without the header
 * read (+0x40) a short image (+0x8c below +0x74) is error 0x43, then the master method +4
 * (+0x1a4) and the state 207; 207 becomes 210 and any other state but 210 error 0x14; then the
 * pass method (+0x1b4 +0) runs until it gives 0, unless its +0x14 is set: then the source's
 * method +0x18 (+0x18) and 0x4b9170 give 1. */
uint32_t vertrix_port_decoder_start_4b9710(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->eax;
    uint32_t state;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    state = port_u32(&port, edx, 0x14);
    if ((state == 0xcd || state == 0xce) && port_u32(&port, edx, 0x40) == 0)
    {
        uint32_t methods;
        if (port_u32(&port, edx, 0x8c) < port_u32(&port, edx, 0x74))
        {
            port_set32(&port, port_u32(&port, edx, 0), 0x14, 0x43);
            methods = port_u32(&port, edx, 0);
            port_forward(&port, entry, port_u32(&port, methods, 0), edx, edx, entry->ebx, methods);
            edx = vertrix_lift_edx;
        }
        methods = port_u32(&port, edx, 0x1a4);
        port_forward(&port, entry, port_u32(&port, methods, 4), edx, edx, entry->ebx, methods);
        edx = vertrix_lift_edx;
        port_set32(&port, edx, 0x14, 0xd2);
    }
    else
    {
        state = port_u32(&port, edx, 0x14);
        if (state == 0xcf)
        {
            port_set32(&port, edx, 0x14, 0xd2);
        }
        else if (state != 0xd2)
        {
            uint32_t methods;
            port_set32(&port, port_u32(&port, edx, 0), 0x14, 0x14);
            port_set32(&port, port_u32(&port, edx, 0), 0x18, port_u32(&port, edx, 0x14));
            methods = port_u32(&port, edx, 0);
            port_forward(&port, entry, port_u32(&port, methods, 0), edx, edx, entry->ebx, methods);
            edx = vertrix_lift_edx;
        }
    }
    for (;;)
    {
        uint32_t pass = port_u32(&port, edx, 0x1b4);
        if (port_u32(&port, pass, 0x14) != 0)
        {
            uint32_t source = port_u32(&port, edx, 0x18);
            port_forward(&port, entry, port_u32(&port, source, 0x18), edx, edx, entry->ebx, source);
            port_forward(&port, entry, 0x4b9170, vertrix_lift_edx, vertrix_lift_edx, entry->ebx,
                         source);
            return port_return(&port, 1, entry->edx);
        }
        result = port_forward(&port, entry, port_u32(&port, pass, 0), edx, edx, entry->ebx, pass);
        edx = vertrix_lift_edx;
        if (result == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
}

/* Original 0x4c3540: the decoder's coefficient buffer (0x1c bytes from the pool method +0,
 * +0x1b0, methods 0x4c3220): with +0x54 its block count is +0x138 and edx asks for a virtual
 * array (method +0x10 with 0x4c9840 of +0x74 and the block count, +0x70 times +0x78) into +8,
 * otherwise a plain one (method +8) into +0xc. */
uint32_t vertrix_port_decoder_coefficients_4c3540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t info = entry->eax;
    uint32_t virtual_array = entry->edx;
    uint32_t pool;
    uint32_t buffer;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    pool = port_u32(&port, info, 4);
    buffer = port_call_with(&port, port_u32(&port, pool, 0), info, 1, 0x1c, virtual_array, info,
                            pool, ebp);
    port_set32(&port, info, 0x1b0, buffer);
    port_set32(&port, buffer, 0, 0x4c3220);
    port_set32(&port, buffer, 8, 0);
    port_set32(&port, buffer, 0xc, 0);
    if (port_u32(&port, info, 0x54) == 0)
    {
        return port_return(&port, buffer, 0);
    }
    port_set32(&port, buffer, 0x10, port_u32(&port, info, 0x138));
    pool = port_u32(&port, info, 4);
    port_set32(&port, ebp, -0x14u, pool);
    if (virtual_array == 0)
    {
        result = port_call_with(&port, port_u32(&port, pool, 8), info, 1,
                                port_u32(&port, info, 0x78) * port_u32(&port, info, 0x70),
                                port_u32(&port, buffer, 0x10), pool, buffer, ebp);
        port_set32(&port, buffer, 0xc, result);
    }
    else
    {
        uint32_t stack[2];
        uint32_t blocks = port_u32(&port, buffer, 0x10);
        stack[1] = blocks;
        stack[0] = call_frame(&port, 0x4c9840, port_u32(&port, info, 0x74), blocks, 0x1c,
                              virtual_array, info, buffer, ebp, &stack[1], 1);
        result = call_frame(&port, port_u32(&port, pool, 0x10), info, 1, 0,
                            port_u32(&port, info, 0x70) * port_u32(&port, info, 0x78), pool, buffer,
                            ebp, stack, 2);
        port_set32(&port, buffer, 8, result);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4c3ed0: the decoder's message (its error manager +0: the code +0x14 names a text in
 * the standard table +0x70 below +0x74, or the added one +0x78 from +0x7c to +0x80, else the
 * table's first with the code kept in +0x18) is formatted into edx (0x4dac10) with the string
 * +0x18 for a leading %s, otherwise the eight parameters +0x18 to +0x34. */
uint32_t vertrix_port_decoder_message_format_4c3ed0(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer = entry->edx;
    uint32_t manager;
    uint32_t code;
    uint32_t text = 0;
    uint32_t edx = entry->edx;
    uint32_t scan;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    manager = port_u32(&port, entry->eax, 0);
    code = port_u32(&port, manager, 0x14);
    if ((int32_t)code > 0 && (int32_t)code <= (int32_t)port_u32(&port, manager, 0x74))
    {
        edx = port_u32(&port, manager, 0x70);
        text = port_u32(&port, edx, code * 4);
    }
    else if (port_u32(&port, manager, 0x78) != 0)
    {
        edx = port_u32(&port, manager, 0x7c);
        if ((int32_t)code >= (int32_t)edx &&
            (int32_t)code <= (int32_t)port_u32(&port, manager, 0x80))
        {
            text = port_u32(&port, port_u32(&port, manager, 0x78), (code - edx) * 4);
            edx = port_u32(&port, manager, 0x78);
        }
    }
    if (text == 0)
    {
        port_set32(&port, manager, 0x18, code);
        text = port_u32(&port, port_u32(&port, manager, 0x70), 0);
    }
    scan = text;
    for (;;)
    {
        uint32_t letter = port_u8(&port, scan, 0);
        scan++;
        edx = (edx & 0xffffff00u) | letter;
        if (letter == 0)
        {
            break;
        }
        if (letter == 0x25)
        {
            if (port_u8(&port, scan, 0) == 0x73)
            {
                uint32_t stack[3] = {buffer, text, manager + 0x18};
                result = call_frame(&port, 0x4dac10, scan, edx, text, manager + 0x18, buffer, 0,
                                    entry->ebp, stack, 3);
                return port_return(&port, result, vertrix_lift_edx);
            }
            break;
        }
    }
    {
        uint32_t stack[10];
        unsigned i;
        stack[0] = buffer;
        stack[1] = text;
        for (i = 0; i < 8; i++)
        {
            stack[2 + i] = port_u32(&port, manager, 0x18 + i * 4);
        }
        result = call_frame(&port, 0x4dac10, port_u32(&port, manager, 0x18),
                            port_u32(&port, manager, 0x20), text, manager, buffer,
                            port_u32(&port, manager, 0x1c), entry->ebp, stack, 10);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4c4ea0: a small pool block of ebx bytes (above 999999984 error 3 by 0x4c4d00;
 * rounded up to 8) from the pool edx (not 0 or 1: error 14 by the error method): 0x4c5bd0 gives
 * it with its 16-byte head (none: 0x4c4d00 with 4), the memory manager's (+4) total +0x4c grows
 * and the block heads the pool list (+0x3c): next, size, used 0. The space after the head. */
uint32_t vertrix_port_pool_small_alloc_4c4ea0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t info = entry->eax;
    uint32_t pool = entry->edx;
    uint32_t size = entry->ebx;
    uint32_t memory;
    uint32_t block;
    uint32_t head;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    memory = port_u32(&port, info, 4);
    port_set32(&port, ebp, -0x10u, memory);
    if (size > 0x3b9ac9f0)
    {
        port_call_with(&port, 0x4c4d00, info, 3, size, info, entry->esi, pool, ebp);
    }
    if ((size & 7) != 0)
    {
        size += 8 - (size & 7);
    }
    if ((int32_t)pool < 0 || (int32_t)pool >= 2)
    {
        uint32_t error = port_u32(&port, info, 0);
        port_set32(&port, error, 0x14, 0xe);
        port_set32(&port, port_u32(&port, info, 0), 0x18, pool);
        error = port_u32(&port, info, 0);
        port_call_with(&port, port_u32(&port, error, 0), info, error, size, info, entry->esi, pool,
                       ebp);
    }
    block = port_call_with(&port, 0x4c5bd0, info, size + 0x10, size, info, entry->esi, pool, ebp);
    if (block == 0)
    {
        port_call_with(&port, 0x4c4d00, info, 4, size, info, block, pool, ebp);
    }
    memory = port_u32(&port, ebp, -0x10u);
    port_set32(&port, memory, 0x4c, port_u32(&port, memory, 0x4c) + size + 0x10);
    head = port_u32(&port, memory + pool * 4, 0x3c);
    port_set32(&port, block, 8, 0);
    port_set32(&port, block, 0, head);
    port_set32(&port, block, 4, size);
    port_set32(&port, memory + pool * 4, 0x3c, block);
    return port_return(&port, block + 0x10, head);
}

#include "port_cstd.h"

/* The C runtime's pointer release, the system colours and brushes, the handle table slot, the
 * map walk, the fatal exit, the type record, and the low level write. */

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

/* Original 0x4dc190: the pointer at eax is released to the heap 0x5c77e8 (0x4dbc60) when both
 * are set, and cleared. */
uint32_t vertrix_port_heap_pointer_release_4dc190(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = entry->eax;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, slot, 0) != 0 && port_u32(&port, 0, 0x5c77e8) != 0)
    {
        port_forward(&port, entry, 0x4dbc60, port_u32(&port, 0, 0x5c77e8), port_u32(&port, slot, 0),
                     entry->ebx, slot);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, slot, 0, 0);
    return port_return(&port, slot, edx);
}

/* Original 0x4de810: the system colours 15, 16, 20, 18 and 6 (slot 0x4f19e0) into +0x44 to
 * +0x54, the brushes +0x2c, +0x30, +0x28, +0x34 released (0x4dc400) and made of the colours
 * (slot 0x4f17d8), the pens +0x3c, +0x38, +0x40 released and made (slot 0x4f17d0, solid, width 0)
 * of the colours 16, 20 and 18. */
uint32_t vertrix_port_system_colours_load_4de810(PORT_SIGNATURE)
{
    static const uint32_t indices[5] = {0xf, 0x10, 0x14, 0x12, 6};
    static const uint32_t brushes[4] = {0x2c, 0x30, 0x28, 0x34};
    static const uint32_t brush_colours[4] = {0x44, 0x48, 0x4c, 0x54};
    static const uint32_t pens[3] = {0x3c, 0x38, 0x40};
    static const uint32_t pen_colours[3] = {0x48, 0x4c, 0x50};
    Port port;
    uint32_t table = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t args[3];
    unsigned index;
    port_open(&port, calls, services, globals, entry);
    for (index = 0; index < 5; index++)
    {
        args[0] = indices[index];
        eax = call_frame(&port, 0x4f19e0, eax, edx, table, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, table, 0x44 + index * 4, eax);
    }
    for (index = 0; index < 4; index++)
    {
        args[0] = table + brushes[index];
        eax = call_frame(&port, 0x4dc400, args[0], edx, table, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
    }
    for (index = 0; index < 4; index++)
    {
        args[0] = port_u32(&port, table, brush_colours[index]);
        eax = call_frame(&port, 0x4f17d8, eax, edx, table, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, table, brushes[index], eax);
    }
    for (index = 0; index < 3; index++)
    {
        args[0] = table + pens[index];
        eax = call_frame(&port, 0x4dc400, args[0], edx, table, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
    }
    for (index = 0; index < 3; index++)
    {
        args[0] = 0;
        args[1] = 0;
        args[2] = port_u32(&port, table, pen_colours[index]);
        eax = call_frame(&port, 0x4f17d0, eax, edx, table, entry->ecx, entry->esi, entry->edi,
                         entry->ebp, args, 3);
        edx = vertrix_lift_edx;
        port_set32(&port, table, pens[index], eax);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ded70: the handle table's slot for the key dx (0 for none): a known key (0x4df140
 * on the table or on its map +0x1c) gives its slot, the map's one stored with the key (+0x3c on,
 * twice for kind 2 at +0x40); a new key takes a fresh slot (0x4d3040 of +0x38) entered in the map
 * (0x4df160). */
uint32_t vertrix_port_handle_table_slot_4ded70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t frame = entry->esp - 0x18;
    uint32_t table = entry->eax;
    uint32_t key = entry->edx;
    uint32_t slot;
    uint32_t place;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (key == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_call_with(&port, 0x4df140, table, key, frame, table, key, entry->edi, entry->ebp) != 0)
    {
        return port_return(&port, port_u32(&port, frame, 0), vertrix_lift_edx);
    }
    if (port_call_with(&port, 0x4df140, table + 0x1c, key, frame, table, key, table + 0x1c,
                       entry->ebp) != 0)
    {
        place = port_u32(&port, frame, 0) + port_u32(&port, table, 0x3c);
        port_set32(&port, place, 0, key);
        if (port_u32(&port, table, 0x40) == 2)
        {
            port_set32(&port, place, 4, key);
        }
        return port_return(&port, port_u32(&port, frame, 0), vertrix_lift_edx);
    }
    slot = port_call_with(&port, 0x4d3040, port_u32(&port, table, 0x38), vertrix_lift_edx, frame,
                          table, key, table + 0x1c, entry->ebp);
    port_set32(&port, frame, 4, slot);
    place = port_call_with(&port, 0x4df160, table + 0x1c, key, slot, table, key, table + 0x1c,
                           entry->ebp);
    port_set32(&port, place, 0, slot);
    place = slot + port_u32(&port, table, 0x3c);
    port_set32(&port, place, 0, key);
    if (port_u32(&port, table, 0x40) == 2)
    {
        port_set32(&port, place, 4, key);
    }
    return port_return(&port, port_u32(&port, frame, 4), vertrix_lift_edx);
}

/* Original 0x4df220: the map eax's walk: the entry at [edx] (the first used bucket of +4 by +8
 * for -1) gives its key (+8) to [ebx] and value (+0xc) to [ecx], and [edx] moves to the next
 * entry (its chain +0, or the next used bucket after its bucket +4, 0 at the end). */
uint32_t vertrix_port_map_iterate_4df220(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t frame = entry->esp - 0x10;
    uint32_t map = entry->eax;
    uint32_t cursor = entry->edx;
    uint32_t node;
    uint32_t next;
    uint32_t count;
    uint32_t bucket;
    uint32_t index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, frame, 0, entry->ebx);
    node = port_u32(&port, cursor, 0);
    if (node == 0xffffffffu && port_u32(&port, map, 8) != 0)
    {
        bucket = port_u32(&port, map, 4);
        for (index = 0;;)
        {
            node = port_u32(&port, bucket, 0);
            if (node != 0)
            {
                break;
            }
            index++;
            bucket += 4;
            if (index >= port_u32(&port, map, 8))
            {
                break;
            }
        }
    }
    next = port_u32(&port, node, 0);
    if (next == 0)
    {
        index = port_u32(&port, node, 4) + 1;
        count = port_u32(&port, map, 8);
        if (index < count)
        {
            bucket = index * 4 + port_u32(&port, map, 4);
            for (;;)
            {
                next = port_u32(&port, bucket, 0);
                if (next != 0)
                {
                    break;
                }
                index++;
                bucket += 4;
                if (index >= port_u32(&port, map, 8))
                {
                    break;
                }
            }
        }
    }
    port_set32(&port, cursor, 0, next);
    port_set32(&port, port_u32(&port, frame, 0), 0, port_u32(&port, node, 8));
    port_set32(&port, entry->ecx, 0, port_u32(&port, node, 0xc));
    return port_return(&port, port_u32(&port, node, 0xc), port_u32(&port, frame, 0));
}

/* Original 0x4e0738: the fatal exit with the message eax and code edx: the module (slot
 * 0x4f1bcc of 0) and the message box (0x4e0508), the hooks (0x507c9c with 0x50970c), the
 * shutdown (0x4e6630), the message (0x4e6ae0), the exit codes 0x21 and 0xff (0x4e6b5c) around
 * 0x507cdc. */
uint32_t vertrix_port_runtime_fatal_exit_4e0738(PORT_SIGNATURE)
{
    static const uint32_t zero[1] = {0};
    Port port;
    uint32_t message = entry->eax;
    uint32_t code = entry->edx;
    uint32_t module;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    module = call_frame(&port, 0x4f1bcc, message, code, entry->ebx, entry->ecx, message, code,
                        entry->ebp, zero, 1);
    eax = port_call_with(&port, 0x4e0508, 0, code, module, entry->ecx, message, code, entry->ebp);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), eax, 0x50970c, module, entry->ecx,
                         message, code, entry->ebp);
    eax = port_call_with(&port, 0x4e6630, eax, vertrix_lift_edx, module, entry->ecx, message, code,
                         entry->ebp);
    port_call_with(&port, 0x4e6ae0, message, vertrix_lift_edx, module, entry->ecx, message, code,
                   entry->ebp);
    eax = port_call_with(&port, 0x4e6b5c, 0x21, vertrix_lift_edx, module, entry->ecx, message, code,
                         entry->ebp);
    port_call_with(&port, port_u32(&port, 0, 0x507cdc), eax, vertrix_lift_edx, module, entry->ecx,
                   message, code, entry->ebp);
    eax = port_call_with(&port, 0x4e6b5c, 0xff, vertrix_lift_edx, module, entry->ecx, message, code,
                         entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e37fe: the type record of eax: a kind 2 record whose base (two back) has bit 0 of
 * +3 set gives its +4, otherwise the base; other kinds themselves. */
uint32_t vertrix_port_type_record_base_4e37fe(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, record, 0) == 2)
    {
        record -= 2;
        if ((port_u8(&port, record, 3) & 1) != 0)
        {
            record = port_u32(&port, record, 4);
        }
    }
    return port_return(&port, record, entry->edx);
}

/* Original 0x4e3bf0: the low level write of ebx bytes from dx to the file eax: a bad file is error
 * 4 (0x4dae70) and -1; under the file lock (0x507ca0, 0x507ca4) an append file seeks to the end
 * (slot 0x4f1ca8) first; a file with its own writer (0x507cfc, 0x507d28) uses it; otherwise
 * WriteFile (slot 0x4f1d08), a short write being error 12; failures set the error (0x4e0884). The
 * count written. */
uint32_t vertrix_port_file_write_raw_4e3bf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t frame = entry->esp - 0x14;
    uint32_t file = entry->eax;
    uint32_t data = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t handle;
    uint32_t eax;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((int32_t)file < 0 || file > port_u32(&port, 0, 0x507c34))
    {
        port_call_with(&port, 0x4dae70, 4, data, count, ecx, file, data, entry->ebp);
        return port_return(&port, 0xffffffffu, vertrix_lift_edx);
    }
    handle = port_u32(&port, port_u32(&port, 0, 0x507c8c) + file * 4, 0);
    port_call_with(&port, port_u32(&port, 0, 0x507ca0), file, data, count, ecx, file, data, handle);
    eax = port_call_with(&port, 0x4e01d0, file, vertrix_lift_edx, count, ecx, file, data, handle);
    if ((eax & 0x80) != 0)
    {
        args[0] = handle;
        args[1] = 0;
        args[2] = 0;
        args[3] = 2;
        eax = call_frame(&port, 0x4f1ca8, eax, vertrix_lift_edx, count, ecx, file, data, handle,
                         args, 4);
        if (eax == 0xffffffffu)
        {
            eax = port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, count,
                                 ecx, file, data, handle);
            eax = port_call_with(&port, 0x4e0884, eax, vertrix_lift_edx, count, ecx, file, data,
                                 handle);
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    if (port_u32(&port, 0, 0x507d28) != 0)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x507cfc), file, vertrix_lift_edx, count,
                             ecx, file, data, handle);
        if (eax != 0)
        {
            uint32_t written = port_call_with(&port, port_u32(&port, 0, 0x507d28), eax, data, count,
                                              ecx, file, data, handle);
            port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, written,
                           ecx, file, data, handle);
            return port_return(&port, written, vertrix_lift_edx);
        }
    }
    args[0] = handle;
    args[1] = data;
    args[2] = count;
    args[3] = frame;
    args[4] = 0;
    eax = call_frame(&port, 0x4f1d08, frame, vertrix_lift_edx, count, ecx, file, data, handle, args,
                     5);
    if (eax == 0)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, count,
                             ecx, file, data, handle);
        eax =
            port_call_with(&port, 0x4e0884, eax, vertrix_lift_edx, count, ecx, file, data, handle);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (count != port_u32(&port, frame, 0))
    {
        port_call_with(&port, 0x4dae70, 0xc, vertrix_lift_edx, count, ecx, file, data, handle);
    }
    port_call_with(&port, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, count, ecx, file,
                   data, handle);
    return port_return(&port, port_u32(&port, frame, 0), vertrix_lift_edx);
}

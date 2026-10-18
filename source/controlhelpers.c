#include "controlhelpers.h"

/* The image record's start, the decoder's input step, the control helpers (the outer parent,
 * the status, the record forward, the command notes) and the list's removal. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4b74c0: the image record eax's start under a guard record: its text +0x14 made
 * (0x4ca070), the methods 0x5185f4 at +0x24, +0 to +0x10 cleared, the text set to 0x5110c9
 * (0x4ca370) and +0x18 to +0x20 cleared. The record. */
uint32_t vertrix_port_image_record_start_4b74c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x518590);
    port_set32(&port, ebp, -0x20u, entry->eax);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x28u, 0);
    record = port_call_with(&port, 0x4ca070, entry->eax + 0x14, 0x4ec1ec, 0x518590, entry->eax, 0,
                            1, ebp) -
             0x14;
    port_set32(&port, ebp, -0x28u, 1);
    port_set32(&port, record, 0x24, 0x5185f4);
    port_set32(&port, record, 0, 0);
    port_set32(&port, record, 4, 0);
    port_set32(&port, record, 8, 0);
    port_set32(&port, record, 0xc, 0);
    port_set32(&port, record, 0x10, 0);
    port_call_with(&port, 0x4ca370, record + 0x14, 0x5110c9, 0x518590, record, 0, 1, ebp);
    port_set32(&port, record, 0x18, 0);
    port_set32(&port, record, 0x1c, 0);
    port_set32(&port, record, 0x20, 0);
    return port_return(&port, record, entry->edx);
}

/* Original 0x4b95e0: the decoder eax's input step by its state +0x14: 200 starts the input
 * (+0x1b4 method +4, then the source's method +8 of +0x18) and becomes 201; 201 reads (+0x1b4
 * method +0), a reading of 1 finishing the header (0x4b9330) into 202; 202 gives 1; 203 to 208
 * and 210 read; any other state is error 20 (the error method +0 of +0). Each step follows the
 * register its last call leaves in edx. */
uint32_t vertrix_port_decoder_input_step_4b95e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t state;
    uint32_t edx = decoder;
    uint32_t ecx = 0;
    uint32_t methods;
    uint32_t error;
    port_open(&port, calls, services, globals, entry);
    state = port_u32(&port, decoder, 0x14) - 0xc8;
    if (state > 10 || state == 9)
    {
        error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0x14);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, port_u32(&port, decoder, 0x14));
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, decoder, error, 0, entry->esi,
                       entry->edi, entry->ebp);
        return port_return(&port, 0, entry->edx);
    }
    if (state == 2)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (state >= 3)
    {
        methods = port_u32(&port, edx, 0x1b4);
        ecx = port_call_with(&port, port_u32(&port, methods, 0), edx, edx, entry->ebx, methods,
                             entry->esi, entry->edi, entry->ebp);
        return port_return(&port, ecx, entry->edx);
    }
    if (state == 0)
    {
        methods = port_u32(&port, edx, 0x1b4);
        port_call_with(&port, port_u32(&port, methods, 4), edx, edx, entry->ebx, methods,
                       entry->esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        methods = port_u32(&port, edx, 0x18);
        port_call_with(&port, port_u32(&port, methods, 8), edx, edx, entry->ebx, methods,
                       entry->esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, edx, 0x14, 0xc9);
    }
    methods = port_u32(&port, edx, 0x1b4);
    ecx = port_call_with(&port, port_u32(&port, methods, 0), edx, edx, entry->ebx, methods,
                         entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (ecx == 1)
    {
        port_call_with(&port, 0x4b9330, edx, edx, entry->ebx, ecx, entry->esi, entry->edi,
                       entry->ebp);
        port_set32(&port, vertrix_lift_edx, 0x14, 0xca);
    }
    return port_return(&port, ecx, entry->edx);
}

/* Original 0x4d1930: the control eax's outermost owner: none without a handle +0x1c; its method
 * +0xb4, or else 0x4d1840, then 0x4d1840 again while it gives one; the last register the walk
 * leaves in edx. */
uint32_t vertrix_port_control_outer_owner_4d1930(PORT_SIGNATURE)
{
    Port port;
    uint32_t control = entry->eax;
    uint32_t methods;
    uint32_t owner;
    uint32_t next;
    port_open(&port, calls, services, globals, entry);
    if (control == 0 || port_u32(&port, control, 0x1c) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    methods = port_u32(&port, control, 0);
    if (port_call_with(&port, port_u32(&port, methods, 0xb4), control, control, methods, control,
                       entry->esi, entry->edi, entry->ebp) != 0)
    {
        owner = vertrix_lift_edx;
    }
    else
    {
        owner = port_call_with(&port, 0x4d1840, control, vertrix_lift_edx, methods, control,
                               entry->esi, entry->edi, entry->ebp);
    }
    while (owner != 0)
    {
        next = port_call_with(&port, 0x4d1840, owner, owner, methods, control, entry->esi,
                              entry->edi, entry->ebp);
        if (next == 0)
        {
            return port_return(&port, vertrix_lift_edx, entry->edx);
        }
        owner = next;
    }
    return port_return(&port, owner, entry->edx);
}

/* Original 0x4d25e0: 0xffff. */
uint32_t vertrix_port_return_constant_ffff_4d25e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, 0xffff, entry->edx);
}

/* Original 0x4d2d70: 1 when the control eax's command +0x90 is set and neither 0xe001 nor
 * 0xe002, otherwise 0. */
uint32_t vertrix_port_object_status_active_4d2d70(PORT_SIGNATURE)
{
    Port port;
    uint32_t command;
    port_open(&port, calls, services, globals, entry);
    command = port_u32(&port, entry->eax, 0x90);
    if (command == 0 || command == 0xe002 || command == 0xe001)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4d4060: the record eax forwarded to the thread state's list (0x4ce780 +8;
 * 0x4dba20). */
uint32_t vertrix_port_rtl_record_forward_4d4060(PORT_SIGNATURE)
{
    Port port;
    uint32_t state;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    state = port_call_with(&port, 0x4ce780, entry->eax, entry->edx, entry->eax, entry->ecx,
                           entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4dba20, state + 8, entry->eax, entry->eax, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d5660: the control eax's command note for the id edx and flags ebx: 0xffff takes
 * 0xe001 (or 0xe002 with the owner's +0x50; 0x4d1930) into +0x90, clears bit 0x40 of +0x24, sends
 * it (0x362; slot 0x4f1a94) and updates the frame (method +0xd8; slot 0x4f1b14); otherwise the id
 * (0 without one or with flags 0x810, 0xf000 to 0xf1ef as 0xef00 plus a sixteenth, 0xff00 up as
 * 0xef1f) goes to +0x90 and the owner's +0x24 gets bit 0x40. A change from +0x94 is posted to the
 * parent (slot 0x4f19c8, 0x4cf8e0; 0x36a by slot 0x4f1a60). */
uint32_t vertrix_port_control_command_note_4d5660(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint32_t control = entry->eax;
    uint32_t flags = entry->ebx;
    uint32_t owner;
    uint32_t id;
    uint32_t command;
    uint32_t methods;
    uint32_t frame;
    uint32_t eax;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    owner = port_call_with(&port, 0x4d1930, control, entry->edx, flags, entry->ecx, control,
                           entry->edi, entry->ebp);
    id = vertrix_lift_edx;
    if (flags == 0xffff)
    {
        port_set8(&port, control, 0x24, port_u8(&port, control, 0x24) & 0xbf);
        command = (port_u32(&port, owner, 0x50) != 0 ? 1 : 0) + 0xe001;
        port_set32(&port, control, 0x90, command);
        args[0] = port_u32(&port, control, 0x1c);
        args[1] = 0x362;
        args[2] = command;
        args[3] = 0;
        call_frame(&port, 0x4f1a94, command, id, flags, owner, control, entry->edi, entry->ebp,
                   args, 4);
        methods = port_u32(&port, control, 0);
        frame = port_call_with(&port, port_u32(&port, methods, 0xd8), control, methods, flags,
                               owner, control, entry->edi, entry->ebp);
        if (frame != 0)
        {
            args[0] = port_u32(&port, frame, 0x1c);
            call_frame(&port, 0x4f1b14, frame, vertrix_lift_edx, flags, owner, control, entry->edi,
                       entry->ebp, args, 1);
        }
    }
    else
    {
        if (id == 0 || (flags & 0x810) != 0)
        {
            command = 0;
        }
        else if (id >= 0xf000 && id < 0xf1f0)
        {
            command = ((id - 0xf000) >> 4) + 0xef00;
        }
        else if (id >= 0xff00)
        {
            command = 0xef1f;
        }
        else
        {
            command = id;
        }
        port_set32(&port, control, 0x90, command);
        port_set8(&port, owner, 0x24, port_u8(&port, owner, 0x24) | 0x40);
    }
    eax = port_u32(&port, control, 0x90);
    if (eax == port_u32(&port, control, 0x94))
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    args[0] = port_u32(&port, control, 0x1c);
    eax = call_frame(&port, 0x4f19c8, eax, vertrix_lift_edx, flags, owner, control, entry->edi,
                     entry->ebp, args, 1);
    args[0] = eax;
    eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, flags, owner, control, entry->edi,
                     entry->ebp, args, 1);
    if (eax == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    args[0] = port_u32(&port, control, 0x1c);
    args[1] = 0x36a;
    args[2] = 0;
    args[3] = 0;
    eax = call_frame(&port, 0x4f1a60, eax, vertrix_lift_edx, flags, owner, control, entry->edi,
                     entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d57a0: the control eax's command note sent (0x362 with edx and ebx; slot
 * 0x4f1a94) unless bit 0x40 of +0x24 holds it back (0). */
uint32_t vertrix_port_control_send_note_4d57a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint32_t eax;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((port_u8(&port, entry->eax, 0x24) & 0x40) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = port_u32(&port, entry->eax, 0x1c);
    args[1] = 0x362;
    args[2] = entry->edx;
    args[3] = entry->ebx;
    eax = call_frame(&port, 0x4f1a94, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d8950: the list eax's removal of ebx words at edx: the words after them move down
 * (0x4eb5e0) and the count +8 drops. */
uint32_t vertrix_port_list_remove_range_4d8950(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t index = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t end = index + count;
    uint32_t rest;
    uint32_t items;
    uint32_t eax = end;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    rest = port_u32(&port, list, 8) - end;
    if (rest != 0)
    {
        items = port_u32(&port, list, 4);
        eax = port_call_with(&port, 0x4eb5e0, items + index * 4, items + end * 4, rest * 4, list,
                             count, items + index * 4, entry->ebp);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, list, 8, port_u32(&port, list, 8) - count);
    return port_return(&port, eax, edx);
}

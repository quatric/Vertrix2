#include "port_crt.h"

/* C runtime file, stream, error, number and string helpers. */

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

/* The runtime lock (0x507ca0) or unlock (0x507ca4) hook on eax. */
static uint32_t crt_hook(Port *port, const LiftEntry *entry, uint32_t hook, uint32_t eax,
                         uint32_t edx, uint32_t ecx)
{
    return port_forward(port, entry, port_u32(port, 0, hook), eax, edx, entry->ebx, ecx);
}

/* Original 0x4e7e44: the record of the stream eax unlinked from the open list 0x5c7760 and put
 * first on the closed list 0x5c7764, the stream's flags (+0xc) given bits 0 and 1; the record,
 * or 0. */
uint32_t vertrix_port_crt_stream_retire_4e7e44(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t link = 0x5c7760;
    uint32_t node;
    port_open(&port, calls, services, globals, entry);
    for (node = port_u32(&port, link, 0); node != 0; node = port_u32(&port, link, 0))
    {
        if (port_u32(&port, node, 4) == stream)
        {
            port_set8(&port, stream, 0xc, port_u8(&port, stream, 0xc) | 3);
            uint32_t closed;
            port_set32(&port, link, 0, port_u32(&port, node, 0));
            closed = port_u32(&port, 0, 0x5c7764);
            port_set32(&port, 0, 0x5c7764, node);
            port_set32(&port, node, 0, closed);
            return port_return(&port, node, entry->edx);
        }
        link = node;
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4e8b24: 0 when the modes of the handles 4 and 7 (0x4e8a58) are both 2 or 3,
 * otherwise 1. */
uint32_t vertrix_port_crt_console_both_4e8b24(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    first = port_forward(&port, entry, 0x4e8a58, 4, entry->edx, entry->ebx, entry->ecx);
    second = port_forward(&port, entry, 0x4e8a58, 7, first, entry->ebx, entry->ecx);
    if ((first == 2 || first == 3) && (second == 2 || second == 3))
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4e8abc: for the stack argument 0 or 1 the handle 4 or 7: 0 when 0x4e8a58 gives none;
 * otherwise 0x4e8cc8 with it and 0 when the edx it leaves is 2 or 3, else 1. 0 for other
 * arguments. */
uint32_t vertrix_port_crt_console_check_4e8abc(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t which;
    uint32_t handle;
    uint32_t mode;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    which = port_u32(&port, entry->esp, 4);
    if (which > 1)
    {
        return port_return(&port, 0, entry->edx);
    }
    handle = which == 0 ? 4 : 7;
    mode = port_forward(&port, entry, 0x4e8a58, handle, entry->edx, entry->ebx, entry->ecx);
    if (mode == 0)
    {
        return port_return(&port, 0, 0);
    }
    port_forward(&port, entry, 0x4e8cc8, handle, mode, entry->ebx, entry->ecx);
    mode = vertrix_lift_edx;
    return port_return(&port, mode == 2 || mode == 3 ? 0 : 1, mode);
}

/* Original 0x4e8978: under the runtime lock, the console input 0x50af14 ("CONIN$" 0x513070, read,
 * shared for reading) and output 0x50af18 (0x513078, write, shared for writing) opened by
 * CreateFileA (0x4f1b34) when they are -1. */
uint32_t vertrix_port_crt_console_open_4e8978(PORT_SIGNATURE)
{
    Port port;
    uint32_t input[7] = {0x513070, 0x80000000, 1, 0, 3, 0x80, 0};
    uint32_t output[7] = {0x513078, 0x40000000, 2, 0, 3, 0x80, 0};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = crt_hook(&port, entry, 0x507ca0, 0, entry->edx, entry->ecx);
    if (port_u32(&port, 0, 0x50af14) == 0xffffffffu)
    {
        result = port_forward_stack(&port, entry, 0x4f1b34, result, vertrix_lift_edx, entry->ebx,
                                    entry->ecx, entry->esi, input, 7);
        port_set32(&port, 0, 0x50af14, result);
    }
    if (port_u32(&port, 0, 0x50af18) == 0xffffffffu)
    {
        result = port_forward_stack(&port, entry, 0x4f1b34, result, vertrix_lift_edx, entry->ebx,
                                    entry->ecx, entry->esi, output, 7);
        port_set32(&port, 0, 0x50af18, result);
    }
    result = crt_hook(&port, entry, 0x507ca4, 0, vertrix_lift_edx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0a30: under the lock of the file eax, 1 when the hook 0x507cfc (when set) holds for
 * it or its handle (0x507c8c) is of type 2 (GetFileType 0x4f1bb4), otherwise 0. */
uint32_t vertrix_port_crt_file_is_device_4e0a30(PORT_SIGNATURE)
{
    Port port;
    uint32_t file = entry->eax;
    uint32_t handle[1];
    uint32_t hook;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, port_u32(&port, 0, 0x507ca0), file, entry->edx, file, entry->ecx);
    hook = port_u32(&port, 0, 0x507cfc);
    if (hook != 0 &&
        port_forward(&port, entry, hook, file, vertrix_lift_edx, file, entry->ecx) != 0)
    {
        port_forward(&port, entry, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, file,
                     entry->ecx);
        return port_return(&port, 1, entry->edx);
    }
    handle[0] = port_u32(&port, port_u32(&port, 0, 0x507c8c), file * 4);
    result = port_forward_stack(&port, entry, 0x4f1bb4, handle[0], vertrix_lift_edx, file,
                                entry->ecx, entry->esi, handle, 1);
    port_forward(&port, entry, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx, file,
                 entry->ecx);
    return port_return(&port, result == 2 ? 1 : 0, entry->edx);
}

/* Original 0x4dd360: the list eax constructed (the tables 0x517454, then 0x51b5d4, and +4, +8 and
 * +0xc 0) under the guard record 0x51afdc. */
uint32_t vertrix_port_rtl_construct_list_4dd360(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t record = entry->esp - BELOW;
    uint32_t list = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_at(&port, record, 0x51afdc);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, list);
    port_set32(&port, list, 0, 0x517454);
    port_set32(&port, record, 0xc, 1);
    port_set32(&port, list, 0, 0x51b5d4);
    port_set32(&port, list, 4, 0);
    port_set32(&port, list, 8, 0);
    port_set32(&port, list, 0xc, 0);
    return port_return(&port, list, entry->edx);
}

/* Original 0x4cf320: the buffer stream eax constructed by 0x4cb460 (with 0 and 32), the table
 * 0x519664, and its buffer +0x1c by 0x4eb5c0; under the guard record 0x5194a0. */
uint32_t vertrix_port_rtl_construct_buffer_stream_4cf320(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t record = entry->esp - BELOW;
    uint32_t stream = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_at(&port, record, 0x5194a0);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, stream);
    stream = call_frame(&port, 0x4cb460, stream, 0, 0x20, stream, entry->esi, entry->edi,
                        entry->ebp, NULL, 0);
    port_set32(&port, record, 0xc, 1);
    port_set32(&port, stream, 0, 0x519664);
    call_frame(&port, 0x4eb5c0, stream + 0x1c, vertrix_lift_edx, 0x20, stream, entry->esi,
               entry->edi, entry->ebp, NULL, 0);
    return port_return(&port, stream, entry->edx);
}

/* Original 0x4e64a0: the unsigned eax written in the radix ebx (digits 0x5097c4) into the string
 * edx through a reversed buffer on the stack; the string, edx the last remainder. */
uint32_t vertrix_port_crt_unsigned_text_4e64a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t buffer = entry->esp - BELOW;
    uint32_t value = entry->eax;
    uint32_t remainder = 0;
    uint32_t cursor = buffer + 1;
    uint32_t out = entry->edx;
    uint32_t digit;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set8(&port, buffer, 0, 0);
    do
    {
        LiftFlags flags = {0, 0, 0, 0, 0, 0};
        port_set32(&port, buffer, 0x24, entry->ebx);
        remainder = 0;
        lift_div1(32, port_u32(&port, buffer, 0x24), &value, &remainder, &flags);
        port_set32(&port, buffer, 0x24, remainder);
        cursor++;
        port_set8(&port, cursor, -1u, port_u8(&port, remainder, 0x5097c4));
    } while (value != 0);
    do
    {
        out++;
        digit = port_u8(&port, cursor, -1u);
        cursor--;
        port_set8(&port, out, -1u, digit);
    } while (digit != 0);
    return port_return(&port, entry->edx, remainder);
}

/* Original 0x4dbc60: inside the critical section +0x20 of eax, the slot edx of each table on the
 * chain +0x18 (link +4, count +8, slots +0xc) destroyed by its method +0 with 2 and cleared, and
 * bit 0 of the slot's flags (+0x14, 8 bytes a slot) cleared. */
uint32_t vertrix_port_rtl_slot_release_4dbc60(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t slot = entry->edx;
    uint32_t section[1] = {owner + 0x20};
    uint32_t node;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->esi;
    uint32_t flags;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    call_frame(&port, 0x4f1b48, owner + 0x20, slot, ebx, entry->ecx, esi, slot, owner, section, 1);
    edx = vertrix_lift_edx;
    node = port_u32(&port, owner, 0x18);
    if (node != 0)
    {
        esi = slot * 4;
    }
    for (; node != 0; node = port_u32(&port, node, 4))
    {
        if ((int32_t)slot < (int32_t)port_u32(&port, node, 8))
        {
            uint32_t item = port_u32(&port, port_u32(&port, node, 0xc), esi);
            if (item != 0)
            {
                ebx = port_u32(&port, item, 0);
                call_frame(&port, port_u32(&port, ebx, 0), item, 2, ebx, node, esi, slot, owner,
                           NULL, 0);
                edx = vertrix_lift_edx;
            }
            port_set32(&port, port_u32(&port, node, 0xc), esi, 0);
        }
    }
    flags = port_u32(&port, owner, 0x14);
    port_set8(&port, flags + slot * 8, 0, port_u8(&port, flags + slot * 8, 0) & 0xfe);
    result =
        call_frame(&port, 0x4f1c40, flags, edx, ebx, node, esi, slot, owner + 0x20, section, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d94a0: +0xc 1, and +0x10 whether 0x4db950 fills the 128 bytes at +0x14 from
 * +0x94. */
uint32_t vertrix_port_rtl_probe_call_4d94a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t arguments[3];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, object, 0xc, 1);
    arguments[0] = port_u32(&port, object, 0x94);
    arguments[1] = object + 0x14;
    arguments[2] = 0x80;
    result = port_forward_stack(&port, entry, 0x4db950, object + 0x14, entry->edx, object,
                                entry->ecx, entry->esi, arguments, 3);
    result = result != 0;
    port_set32(&port, object, 0x10, result);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e0150: for a valid file eax (0 to 0x507c34) under its lock: its mode (0x4e01d0)
 * given bit 15 by 0x4e0228 when edx is positive and bit 7 is clear, then SetFilePointer-like
 * 0x4f1ca8 on its handle (0x507c8c) with edx, 0 and ebx; the answer (0x4e0884 for -1). An
 * invalid file sets the error 4 (0x4dae70) and gives -1. */
uint32_t vertrix_port_crt_file_seek_4e0150(PORT_SIGNATURE)
{
    Port port;
    uint32_t file = entry->eax;
    uint32_t distance = entry->edx;
    uint32_t arguments[4];
    uint32_t mode;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)file < 0 || file > port_u32(&port, 0, 0x507c34))
    {
        port_forward_esi(&port, entry, 0x4dae70, 4, entry->edx, entry->ebx, distance, file);
        return port_return(&port, 0xffffffffu, vertrix_lift_edx);
    }
    port_forward_esi(&port, entry, port_u32(&port, 0, 0x507ca0), file, entry->edx, entry->ebx,
                     distance, file);
    mode = port_forward_esi(&port, entry, 0x4e01d0, file, vertrix_lift_edx, entry->ebx, distance,
                            file);
    if ((int32_t)distance > 0 && (mode & 0x80) == 0)
    {
        port_forward_esi(&port, entry, 0x4e0228, file, mode | 0x8000, entry->ebx, distance, file);
    }
    arguments[0] = port_u32(&port, port_u32(&port, 0, 0x507c8c), file * 4);
    arguments[1] = distance;
    arguments[2] = 0;
    arguments[3] = entry->ebx;
    result = port_forward_stack(&port, entry, 0x4f1ca8, arguments[0], port_u32(&port, 0, 0x507c8c),
                                entry->ebx, distance, file, arguments, 4);
    mode = port_forward_esi(&port, entry, port_u32(&port, 0, 0x507ca4), file, vertrix_lift_edx,
                            entry->ebx, result, file);
    if (result == 0xffffffffu)
    {
        port_forward_esi(&port, entry, 0x4e0884, mode, vertrix_lift_edx, entry->ebx, result, file);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e081c: the system error eax (as 0x4daeb8 leaves it in edx) made the runtime error by
 * 0x4dae70: 123 to 1, 206 to 9, 183 to 7, the rest by the byte table 0x507ce8 (past 19 as 19);
 * -1. */
uint32_t vertrix_port_crt_map_error_4e081c(PORT_SIGNATURE)
{
    Port port;
    uint32_t code;
    uint32_t error;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, 0x4daeb8, entry->eax, entry->eax, entry->ebx, entry->ecx);
    code = vertrix_lift_edx;
    if (code == 0x7b)
    {
        error = 1;
    }
    else if (code == 0xce)
    {
        error = 9;
    }
    else if (code == 0xb7)
    {
        error = 7;
    }
    else
    {
        if (code > 0x13)
        {
            code = 0x13;
        }
        error = (uint32_t)(int32_t)(int8_t)port_u8(&port, code, 0x507ce8);
    }
    port_forward(&port, entry, 0x4dae70, error, code, entry->ebx, entry->ecx);
    return port_return(&port, 0xffffffffu, entry->edx);
}

/* Original 0x4d2310: unless the window eax is disabled (0x4cccc0 bit 30), when the application's
 * (0x4cbe80) main window (method +0x78) exists and none of shift, control and alt is down
 * (GetKeyState 0x4f1998), command 0xe146 (WM_COMMAND, PostMessageA 0x4f1a94) to it and 1;
 * otherwise 0x4cf850. */
uint32_t vertrix_port_rtl_window_context_help_4d2310(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t esi = entry->esi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_forward_esi(&port, entry, 0x4cccc0, window, entry->edx, window, entry->ecx, esi);
    if ((result & 0x40000000) == 0)
    {
        result = port_forward_esi(&port, entry, 0x4cbe80, result, vertrix_lift_edx, window,
                                  entry->ecx, esi);
        if (result != 0)
        {
            uint32_t application = port_forward_esi(&port, entry, 0x4cbe80, result,
                                                    vertrix_lift_edx, window, entry->ecx, esi);
            esi = port_u32(&port, application, 0);
            esi = port_forward_esi(&port, entry, port_u32(&port, esi, 0x78), application,
                                   vertrix_lift_edx, window, entry->ecx, esi);
            if (esi != 0)
            {
                uint32_t key[1];
                uint32_t message[4];
                unsigned k;
                result = esi;
                for (k = 0; k < 3; k++)
                {
                    key[0] = 0x10 + k;
                    result = port_forward_stack(&port, entry, 0x4f1998, result, vertrix_lift_edx,
                                                window, entry->ecx, esi, key, 1);
                    result = (uint32_t)(int32_t)(int16_t)result;
                    if ((int32_t)result < 0)
                    {
                        break;
                    }
                }
                if (k == 3)
                {
                    message[0] = port_u32(&port, esi, 0x1c);
                    message[1] = 0x111;
                    message[2] = 0xe146;
                    message[3] = 0;
                    port_forward_stack(&port, entry, 0x4f1a94, result, vertrix_lift_edx, window,
                                       entry->ecx, esi, message, 4);
                    return port_return(&port, 1, vertrix_lift_edx);
                }
            }
        }
    }
    result =
        port_forward_esi(&port, entry, 0x4cf850, window, vertrix_lift_edx, window, entry->ecx, esi);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4ca430: the string (first stack argument) emptied by 0x4ca070 with the third, then
 * 0x4ca3f0 joins the second and third (their lengths at -0xc +4); under the guard record
 * 0x518880. The string. */
uint32_t vertrix_port_rtl_string_concat_4ca430(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t ebp = entry->esp - 0xc;
    uint32_t text;
    uint32_t first;
    uint32_t second;
    uint32_t pushed[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    text = port_u32(&port, entry->esp, 4);
    first = port_u32(&port, entry->esp, 8);
    guard_at(&port, ebp - 0x14, 0x518880);
    call_frame(&port, 0x4ca070, text, port_u32(&port, entry->esp, 0xc), entry->ebx, entry->ecx,
               text, entry->edi, ebp, NULL, 0);
    second = vertrix_lift_edx;
    pushed[0] = port_u32(&port, second, 0);
    first = port_u32(&port, first, 0);
    call_frame(&port, 0x4ca3f0, text, port_u32(&port, first - 0xc, 4), first,
               port_u32(&port, port_u32(&port, second, 0) - 0xc, 4), text, entry->edi, ebp, pushed,
               1);
    return port_return(&port, text, vertrix_lift_edx);
}

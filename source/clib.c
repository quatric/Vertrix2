#include "clib.h"

/* C runtime stream, thread, heap, number and text helpers. */

/* A call handing the callee esi, edi and ebp as given, and `count` stack arguments (the nearest
 * to the stack pointer first). */
static uint32_t call_registers(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                               uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                               const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* The routine through the pointer at `slot`. */
static uint32_t pointer_at(Port *port, uint32_t slot)
{
    return port_u32(port, 0, slot);
}

/* Original 0x4e36e4: release the block +0x10 (cleared) from the heap +4 by 0x4e0e69, then
 * 0x4e36c4 with 1. */
uint32_t vertrix_port_rtl_stream_release_4e36e4(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, stream, 0x10) != 0)
    {
        uint32_t block = port_u32(&port, stream, 0x10);
        port_set32(&port, stream, 0x10, 0);
        port_forward(&port, entry, 0x4e0e69, port_u32(&port, stream, 4), block, entry->ebx, stream);
    }
    result = port_forward(&port, entry, 0x4e36c4, stream, 1, entry->ebx, stream);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e3f28: under the stream lock (0x507cb0, 0x507cb4), the count of the streams of the
 * chain 0x5c7760 whose flags (+0xc) meet the mask eax, flushing (0x4e3ce0) those with bit 12.
 * The chain goes on from the edx a flush leaves. */
uint32_t vertrix_port_rtl_streams_count_4e3f28(PORT_SIGNATURE)
{
    Port port;
    uint32_t mask = entry->eax;
    uint32_t count = 0;
    uint32_t node;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax =
        port_forward(&port, entry, pointer_at(&port, 0x507cb0), mask, entry->edx, entry->ebx, mask);
    for (node = port_u32(&port, 0, 0x5c7760); node != 0; node = port_u32(&port, node, 0))
    {
        uint32_t stream = port_u32(&port, node, 4);
        eax = stream;
        if (port_u32(&port, stream, 0xc) & mask)
        {
            count++;
            if (port_u8(&port, stream, 0xd) & 0x10)
            {
                eax = port_forward(&port, entry, 0x4e3ce0, stream, node, count, mask);
                node = vertrix_lift_edx;
            }
        }
    }
    port_forward(&port, entry, pointer_at(&port, 0x507cb4), eax, 0, count, mask);
    return port_return(&port, count, entry->edx);
}

/* Original 0x4e5024: the message eax (0x5096c4), 0x5129b9 and the text edx written by 0x4e8330 to
 * the stream 0x4e8310 gives for 2, then a new line by 0x4e3e00. */
uint32_t vertrix_port_rtl_print_message_4e5024(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->eax;
    uint32_t text = entry->edx;
    uint32_t stream;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    stream = port_forward_esi(&port, entry, 0x4e8310, 2, entry->edx, entry->ebx, text, index);
    port_forward_esi(&port, entry, 0x4e8330, port_u32(&port, index * 4, 0x5096c4), stream, stream,
                     text, index);
    port_forward_esi(&port, entry, 0x4e8330, 0x5129b9, stream, stream, text, index);
    port_forward_esi(&port, entry, 0x4e8330, text, stream, stream, text, index);
    result = port_forward_esi(&port, entry, 0x4e3e00, 0xa, stream, stream, text, index);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4e56a8: close (the import 0x4f1b3c) and free (0x4ea190) each of the 0x5c8944
 * handles of 0x5c8948, then free that table. */
uint32_t vertrix_port_rtl_handles_close_4e56a8(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t index = 0;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t table;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, 0, 0x5c8944);
    edx = count;
    if ((int32_t)count > 0)
    {
        do
        {
            uint32_t pushed[1];
            ebx = index * 4;
            ecx = port_u32(&port, port_u32(&port, 0, 0x5c8948), ebx);
            pushed[0] = ecx;
            call_registers(&port, 0x4f1b3c, port_u32(&port, 0, 0x5c8948), edx, ebx, ecx, index, edi,
                           entry->ebp, pushed, 1);
            index++;
            eax =
                call_registers(&port, 0x4ea190, port_u32(&port, port_u32(&port, 0, 0x5c8948), ebx),
                               vertrix_lift_edx, ebx, ecx, index, edi, entry->ebp, NULL, 0);
            edx = vertrix_lift_edx;
            edi = port_u32(&port, 0, 0x5c8944);
            ebx += 4;
        } while ((int32_t)index < (int32_t)edi);
    }
    table = port_u32(&port, 0, 0x5c8948);
    if (table != 0)
    {
        eax = call_registers(&port, 0x4ea190, table, edx, ebx, ecx, index, edi, table, NULL, 0);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e5918: the thread data from 0x4e587c set as the thread's value (the import 0x4f1ce0
 * on the slot 0x507c98) once 0x4e8510 takes it; freed by 0x4ea190 when it does not. 1 when set. */
uint32_t vertrix_port_rtl_thread_attach_4e5918(PORT_SIGNATURE)
{
    Port port;
    uint32_t data;
    uint32_t taken;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x507c98) == 0xffffffffu)
    {
        return port_return(&port, 0, entry->edx);
    }
    data = port_forward(&port, entry, 0x4e587c, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (data == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    taken =
        port_forward(&port, entry, 0x4e8510, port_u32(&port, data, 0xda), data, data, entry->ecx);
    if (taken == 0)
    {
        port_forward(&port, entry, 0x4ea190, data, vertrix_lift_edx, data, entry->ecx);
        return port_return(&port, 0, entry->edx);
    }
    pushed[0] = port_u32(&port, 0, 0x507c98);
    pushed[1] = data;
    port_forward_stack(&port, entry, 0x4f1ce0, taken, vertrix_lift_edx, pushed[0], entry->ecx,
                       entry->esi, pushed, 2);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4e596c: the thread's data (the import 0x4f1cdc on the slot 0x507c98) released: its
 * table +0xda by 0x4e8574, the value cleared (0x4f1ce0) and, with eax set, its handle +0xde
 * closed (0x4f1b2c). */
uint32_t vertrix_port_rtl_thread_detach_4e596c(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot;
    uint32_t data;
    uint32_t handle;
    uint32_t pushed[2];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    slot = port_u32(&port, 0, 0x507c98);
    if (slot == 0xffffffffu)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    pushed[0] = slot;
    data = call_registers(&port, 0x4f1cdc, entry->eax, slot, entry->eax, entry->ecx, entry->esi,
                          entry->edi, entry->ebp, pushed, 1);
    if (data == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    handle = port_u32(&port, data, 0xde);
    result = call_registers(&port, 0x4e8574, port_u32(&port, data, 0xda), vertrix_lift_edx,
                            entry->eax, entry->ecx, handle, entry->edi, entry->ebp, NULL, 0);
    pushed[0] = port_u32(&port, 0, 0x507c98);
    pushed[1] = 0;
    result = call_registers(&port, 0x4f1ce0, result, vertrix_lift_edx, entry->eax, entry->ecx,
                            handle, pushed[0], entry->ebp, pushed, 2);
    if (handle != 0 && entry->eax != 0)
    {
        pushed[0] = handle;
        result = call_registers(&port, 0x4f1b2c, result, vertrix_lift_edx, entry->eax, entry->ecx,
                                handle, port_u32(&port, 0, 0x507c98), entry->ebp, pushed, 1);
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e6320: the unsigned eax in the radix ebx (digits 0x50976c) written to edx; eax the
 * text, edx the last remainder. */
uint32_t vertrix_port_rtl_utoa_4e6320(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t buffer = entry->esp - 0x38;
    uint32_t value = entry->eax;
    uint32_t radix = entry->ebx;
    uint32_t at = buffer + 1;
    uint32_t target = entry->edx;
    uint32_t remainder = 0;
    uint32_t digit;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set8(&port, buffer, 0, 0);
    if (radix == 0)
    {
        return port_return(&port, entry->edx, 0);
    }
    do
    {
        remainder = value % radix;
        value /= radix;
        port_set32(&port, buffer, 0x24, value);
        port_set8(&port, at, 0, port_u8(&port, remainder, 0x50976c));
        at++;
    } while (value != 0);
    do
    {
        at--;
        digit = port_u8(&port, at, 0);
        port_set8(&port, target, 0, digit);
        target++;
    } while (digit != 0);
    return port_return(&port, entry->edx, remainder);
}

/* Original 0x4e636c: eax written by 0x4e6320 to edx in the radix ebx, with a '-' first for a
 * negative value in radix 10; eax the text. */
uint32_t vertrix_port_rtl_itoa_4e636c(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t target = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (entry->ebx == 10 && (int32_t)value < 0)
    {
        value = 0 - value;
        port_set8(&port, target, 0, 0x2d);
        target++;
    }
    port_forward(&port, entry, 0x4e6320, value, target, entry->ebx, entry->edx);
    return port_return(&port, entry->edx, vertrix_lift_edx);
}

/* Original 0x4e66dc: append the text edx to the text eax; with a "0x" in it and ebx set, ebx in
 * hexadecimal (0x5097f4) written back from the eighth place after the "0x". */
uint32_t vertrix_port_rtl_append_hex_4e66dc(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t source = entry->edx;
    uint32_t value = entry->ebx;
    uint32_t mark = 0;
    uint32_t place;
    uint32_t edx;
    uint32_t character;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, at, 0) != 0)
    {
        do
        {
            character = port_u8(&port, at, 1);
            at++;
        } while (character != 0);
    }
    place = at + 9;
    for (;;)
    {
        character = port_u8(&port, source, 0);
        port_set8(&port, at, 0, character);
        if (character == 0)
        {
            break;
        }
        if (character == 0x30 && port_u8(&port, source, 1) == 0x78)
        {
            mark = place;
        }
        place++;
        at++;
        source++;
    }
    edx = source;
    if (mark == 0)
    {
        return port_return(&port, at, edx);
    }
    if (value == 0)
    {
        return port_return(&port, 0, edx);
    }
    do
    {
        edx = port_u8(&port, value & 0xf, 0x5097f4);
        mark--;
        value >>= 4;
        port_set8(&port, mark, 1, edx);
    } while (value != 0);
    return port_return(&port, 0, edx);
}

/* Original 0x4e70d0: for a lead byte (0x4e9020) whether the character edx is one of 0x824f to
 * 0x8258; otherwise bit 5 of its class (0x507d58). */
uint32_t vertrix_port_rtl_char_is_digit_4e70d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t character = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_forward(&port, entry, 0x4e9020, character, character, entry->ebx, entry->ecx) != 0)
    {
        return port_return(&port, character >= 0x824f && character <= 0x8258, entry->edx);
    }
    return port_return(&port, port_u8(&port, (character + 1) & 0xff, 0x507d58) & 0x20, entry->edx);
}

/* Original 0x4e7eb0: under the stream lock, -1 when eax is not in the stream chain 0x5c7760;
 * otherwise 0x4e7ef4 on it with 1. */
uint32_t vertrix_port_rtl_stream_close_4e7eb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t node;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_forward(&port, entry, pointer_at(&port, 0x507cb0), stream, entry->edx, stream, entry->ecx);
    for (node = port_u32(&port, 0, 0x5c7760); node != 0; node = port_u32(&port, node, 0))
    {
        if (stream == port_u32(&port, node, 4))
        {
            break;
        }
    }
    port_forward(&port, entry, pointer_at(&port, 0x507cb4), node, vertrix_lift_edx, stream,
                 entry->ecx);
    if (node == 0)
    {
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    result = port_forward(&port, entry, 0x4e7ef4, stream, 1, stream, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4e8574: under the lock (0x507cc8, 0x507ccc), unlink the entry for eax from the chain
 * 0x5c8aa0 and free it (and its buffer +8 when +0xc is set) by 0x4ea190. */
uint32_t vertrix_port_rtl_table_remove_4e8574(PORT_SIGNATURE)
{
    Port port;
    uint32_t key = entry->eax;
    uint32_t node;
    uint32_t link = 0x5c8aa0;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    eax = port_forward(&port, entry, pointer_at(&port, 0x507cc8), key, entry->edx, key, entry->ecx);
    for (node = port_u32(&port, 0, 0x5c8aa0); node != 0; node = port_u32(&port, node, 0))
    {
        if (key == port_u32(&port, node, 4))
        {
            break;
        }
        link = node;
    }
    edx = node;
    if (node != 0)
    {
        if (port_u32(&port, node, 0xc) != 0)
        {
            port_forward(&port, entry, 0x4ea190, port_u32(&port, node, 8), node, key, link);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, link, 0, port_u32(&port, edx, 0));
        eax = port_forward(&port, entry, 0x4ea190, edx, edx, key, link);
        edx = vertrix_lift_edx;
    }
    eax = port_forward(&port, entry, pointer_at(&port, 0x507ccc), eax, edx, key, link);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e869c: free the block eax by the import 0x4f1cf0 (0x8000); -1 when that fails.
 * When it was the current block 0x50af00 its successor +8 (or, at the end, 0x50aefc with 0x50af04
 * cleared) takes its place, and 0x5c8ad0 forgets it. */
uint32_t vertrix_port_rtl_heap_free_block_4e869c(PORT_SIGNATURE)
{
    Port port;
    uint32_t block = entry->eax;
    uint32_t next;
    uint32_t pushed[3];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = block;
    pushed[1] = 0;
    pushed[2] = 0x8000;
    next = port_u32(&port, block, 8);
    if (call_registers(&port, 0x4f1cf0, block, entry->edx, block, entry->ecx, next, entry->edi,
                       entry->ebp, pushed, 3) == 0)
    {
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    if (block == port_u32(&port, 0, 0x50af00))
    {
        if (next != 0)
        {
            port_set32(&port, 0, 0x50af00, next);
        }
        else
        {
            port_set32(&port, 0, 0x50af04, next);
            port_set32(&port, 0, 0x50af00, port_u32(&port, 0, 0x50aefc));
        }
    }
    if (block == port_u32(&port, 0, 0x5c8ad0))
    {
        port_set32(&port, 0, 0x5c8ad0, 0);
    }
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4e8730: compare the first characters of eax and edx, both bytes of a double-byte
 * character (0x5c8950 set and bit 0 of its class 0x5c8961); the difference. */
uint32_t vertrix_port_rtl_char_compare_4e8730(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    uint32_t second;
    port_open(&port, calls, services, globals, entry);
    first = port_u8(&port, entry->eax, 0);
    if (first != port_u8(&port, entry->edx, 0))
    {
        return port_return(&port, first - port_u8(&port, entry->edx, 0), entry->edx);
    }
    if (port_u32(&port, 0, 0x5c8950) == 0 || (port_u8(&port, first, 0x5c8961) & 1) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    first = port_u8(&port, entry->eax, 1);
    second = port_u8(&port, entry->edx, 1);
    if (first == second)
    {
        return port_return(&port, 0, entry->edx);
    }
    return port_return(&port, first - second, second);
}

/* Original 0x4e8a10: install the handler edx for the signal eax and give the old one: the
 * process table 0x50af1c for 4 and 7, otherwise the thread's (0x507c9c, +0x58). */
uint32_t vertrix_port_rtl_signal_set_4e8a10(PORT_SIGNATURE)
{
    Port port;
    uint32_t signal = entry->eax;
    uint32_t old;
    uint32_t data;
    port_open(&port, calls, services, globals, entry);
    if (signal == 7 || signal == 4)
    {
        old = port_u32(&port, signal * 8, 0x50af1c);
        port_set32(&port, signal * 8, 0x50af1c, entry->edx);
        return port_return(&port, old, entry->edx);
    }
    data = port_forward(&port, entry, pointer_at(&port, 0x507c9c), signal, entry->edx, signal,
                        signal * 8);
    old = port_u32(&port, signal * 8 + data, 0x58);
    data = port_forward(&port, entry, pointer_at(&port, 0x507c9c), data, vertrix_lift_edx, old,
                        signal * 8);
    port_set32(&port, signal * 8 + data, 0x58, vertrix_lift_edx);
    return port_return(&port, old, vertrix_lift_edx);
}

/* Original 0x4e8b8c: with the console handler on (0x50af84), remove it (the import 0x4f1c88 on
 * 0x4e8abc with 0) and clear the flag when that works; whether it is off. */
uint32_t vertrix_port_rtl_console_handler_off_4e8b8c(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[2] = {0x4e8abc, 0};
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, 0x50af84) != 0 &&
        port_forward_stack(&port, entry, 0x4f1c88, entry->eax, entry->edx, entry->ebx, entry->ecx,
                           entry->esi, pushed, 2) != 0)
    {
        port_set8(&port, 0, 0x50af84, 0);
    }
    return port_return(&port, port_u8(&port, 0, 0x50af84) == 0, entry->edx);
}

/* Original 0x4ebe60: the position of the stream eax: flushed (0x4dabd0) when writing (bits 7 and
 * 12 of +0xc), the handle's position (0x4ec380 on +0x10) moved by the buffered count +4 under the
 * handle lock (0x507ca0, 0x507ca4); -1 on failure. The stream is the edx each call leaves. */
uint32_t vertrix_port_rtl_stream_tell_4ebe60(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t position;
    uint32_t result;
    uint32_t buffered;
    port_open(&port, calls, services, globals, entry);
    if ((port_u8(&port, stream, 0xc) & 0x80) && (port_u8(&port, stream, 0xd) & 0x10))
    {
        port_forward(&port, entry, 0x4dabd0, stream, stream, entry->ebx, entry->ecx);
        stream = vertrix_lift_edx;
    }
    position = port_forward(&port, entry, 0x4ec380, port_u32(&port, stream, 0x10), stream,
                            entry->ebx, entry->ecx);
    if (position == 0xffffffffu)
    {
        return port_return(&port, position, entry->edx);
    }
    stream = vertrix_lift_edx;
    port_forward(&port, entry, pointer_at(&port, 0x507ca0), port_u32(&port, stream, 0x10), stream,
                 position, position);
    stream = vertrix_lift_edx;
    buffered = port_u32(&port, stream, 4);
    result = position;
    if (buffered != 0)
    {
        if (port_u8(&port, stream, 0xd) & 0x10)
        {
            result = buffered + position;
        }
        else
        {
            result = position - buffered;
        }
    }
    port_forward_esi(&port, entry, pointer_at(&port, 0x507ca4), port_u32(&port, stream, 0x10),
                     stream, position, result, buffered);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4ec380: the file position of the handle eax (the import 0x4f1ca8 with 0, 0, 1 on its
 * system handle 0x507c8c) under the handle lock; -1 (error 4 by 0x4dae70) for a bad handle, and
 * 0x4e0884 when it fails (the position the edx the unlock leaves). */
uint32_t vertrix_port_rtl_handle_tell_4ec380(PORT_SIGNATURE)
{
    Port port;
    uint32_t handle = entry->eax;
    uint32_t pushed[4];
    uint32_t position;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)handle < 0 || handle > port_u32(&port, 0, 0x507c34))
    {
        port_forward(&port, entry, 0x4dae70, 4, entry->edx, handle, entry->ecx);
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    result =
        port_forward(&port, entry, pointer_at(&port, 0x507ca0), handle,
                     port_u32(&port, port_u32(&port, 0, 0x507c8c), handle * 4), handle, entry->ecx);
    pushed[0] = vertrix_lift_edx;
    pushed[1] = 0;
    pushed[2] = 0;
    pushed[3] = 1;
    position = port_forward_stack(&port, entry, 0x4f1ca8, result, vertrix_lift_edx, handle,
                                  entry->ecx, entry->esi, pushed, 4);
    result = port_forward(&port, entry, pointer_at(&port, 0x507ca4), handle, position, handle,
                          entry->ecx);
    position = vertrix_lift_edx;
    if (position == 0xffffffffu)
    {
        port_forward(&port, entry, 0x4e0884, result, position, handle, entry->ecx);
        position = vertrix_lift_edx;
    }
    return port_return(&port, position, entry->edx);
}

/* Original 0x4ecba9: multiply the extended value at eax by ten to the power edx (at most 0x2000)
 * by 0x4edb48 with the powers 10^(2^i) of the table 0x50b9e8 (10 bytes each, copied to a local)
 * for the set bits. */
uint32_t vertrix_port_rtl_scale_power_ten_4ecba9(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t value = entry->eax;
    uint32_t power = entry->edx;
    uint32_t table = 0x50b9e8;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((int32_t)power >= 0x2000)
    {
        power = 0x2000;
    }
    for (; (int32_t)power > 0; power = (uint32_t)((int32_t)power >> 1), table += 10)
    {
        if (power & 1)
        {
            port_set16(&port, ebp, -0x14u, port_u16(&port, table, 8));
            port_set32(&port, ebp, -0x18u, port_u32(&port, table, 4));
            port_set32(&port, ebp, -0x1cu, port_u32(&port, table, 0));
            eax = call_registers(&port, 0x4edb48, value, ebp - 0x1c, value, table, power, value,
                                 ebp, NULL, 0);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4ecc03: scale the extended value at eax by ten to the power edx: the power of ten
 * built from 1.0 by 0x4ecba9 in a local, then multiplied in (0x4edb48) or, for a negative power,
 * divided in (0x4edd24). */
uint32_t vertrix_port_rtl_scale_ten_4ecc03(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t value = entry->eax;
    uint32_t power = entry->edx;
    uint32_t local = ebp - 0x18;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (power == 0)
    {
        return port_return(&port, entry->eax, 0);
    }
    port_set16(&port, ebp, -0x10u, 0x3fff);
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0x14u, 0x80000000u);
    if ((int32_t)power < 0)
    {
        call_registers(&port, 0x4ecba9, local, 0 - power, 0x80000000u, value, 0, entry->edi, ebp,
                       NULL, 0);
        result = call_registers(&port, 0x4edd24, value, local, value, value, 0, entry->edi, ebp,
                                NULL, 0);
    }
    else
    {
        call_registers(&port, 0x4ecba9, local, power, 0x80000000u, value, 0, entry->edi, ebp, NULL,
                       0);
        result = call_registers(&port, 0x4edb48, value, local, value, value, 0, entry->edi, ebp,
                                NULL, 0);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4ecc60: 0x4ecc03 in steps of at most 0x1000 either way (one step, then the rest). */
uint32_t vertrix_port_rtl_scale_ten_steps_4ecc60(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t power = entry->edx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)power > 0x1000)
    {
        port_forward(&port, entry, 0x4ecc03, value, 0x1000, power, value);
        power -= 0x1000;
    }
    else if ((int32_t)power < -0x1000)
    {
        port_forward(&port, entry, 0x4ecc03, value, 0xfffff000u, power, value);
        power += 0x1000;
    }
    result = port_forward(&port, entry, 0x4ecc03, value, power, power, value);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4ee094: the signed eax as an extended value at edx (mantissa normalised to bit 63,
 * exponent with the bias 0x3fff and the sign); eax 0, edx the mantissa's high dword. */
uint32_t vertrix_port_rtl_int_to_extended_4ee094(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t target = entry->edx;
    uint32_t exponent = 0x3fff;
    uint32_t mantissa = 0;
    uint32_t top;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)value < 0)
    {
        value = 0 - value;
        exponent = 0xbfff;
    }
    if (value == 0)
    {
        exponent = 0;
    }
    else
    {
        top = 31;
        while ((value >> top) == 0)
        {
            top--;
        }
        mantissa = value << (31 - top);
        exponent += top;
    }
    port_set32(&port, target, 0, 0);
    port_set32(&port, target, 4, mantissa);
    port_set16(&port, target, 8, exponent);
    return port_return(&port, 0, mantissa);
}

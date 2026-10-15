#include "port_items.h"

/* The menu item makers on their stack arguments, the overlay spawn, the input acknowledge and the
 * paired sound cue. */

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
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The stack word at ebp + `offset` as a dword, a signed word and a byte either way. */
static uint32_t arg32(Port *port, uint32_t ebp, uint32_t offset)
{
    return port_u32(port, ebp, offset);
}

static uint32_t arg16(Port *port, uint32_t ebp, uint32_t offset)
{
    return sign16(port_u16(port, ebp, offset));
}

static uint32_t arg8(Port *port, uint32_t ebp, uint32_t offset)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(port, ebp, offset);
}

/* The end of the item makers: the item takes the state 0x443460 (0x4ac8f0), the press `press`
 * (0x4ac930), the hover 0x4486f0 (0x4ac910), its motion (0x471820 with the two words `moves`)
 * and joins the list 0x54671c (0x4b5e70). The registers between are the routine's. */
static void item_finish(Port *port, uint32_t item, uint32_t press, uint32_t ebx, uint32_t ecx,
                        uint32_t press_ebx, uint32_t hover_ecx, uint32_t edi, uint32_t ebp,
                        uint32_t move, uint32_t move_ebx, uint32_t move_ecx, uint32_t move_edi,
                        const uint32_t *moves)
{
    port_call_with(port, 0x4ac8f0, item, 0x443460, ebx, ecx, item, edi, ebp);
    port_call_with(port, 0x4ac930, item, press, press_ebx, ecx, item, edi, ebp);
    port_call_with(port, 0x4ac910, item, 0x4486f0, press_ebx, hover_ecx, item, edi, ebp);
    call_frame(port, 0x471820, item, move, move_ebx, move_ecx, item, move_edi, ebp, moves, 2);
    port_call_with(port, 0x4b5e70, 0x54671c, item, move_ebx, move_ecx, item, move_edi, ebp);
}

/* Original 0x4601c0: the item from 0x45ffb0 (ax, dx, bx, cx and nine stack words) with the press
 * of the tenth word, moved by the last ones less the place. ret 0x3c. */
uint32_t vertrix_port_menu_item_make_4601c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x3c];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx = sign16(entry->ebx);
    uint32_t ecx = sign16(entry->ecx);
    uint32_t edi = entry->edx;
    uint32_t item;
    uint32_t make[9];
    uint32_t moves[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 15);
    port_set16(&port, ebp, -0xcu, entry->eax);
    guard_record(&port, ebp - 0x20, 0x5157a4);
    make[0] = arg32(&port, ebp, 8);
    make[1] = arg32(&port, ebp, 0xc);
    make[2] = arg8(&port, ebp, 0x10);
    make[3] = port_u8(&port, ebp, 0x14);
    make[4] = arg16(&port, ebp, 0x18);
    make[5] = arg32(&port, ebp, 0x1c);
    make[6] = arg32(&port, ebp, 0x20);
    make[7] = arg32(&port, ebp, 0x24);
    make[8] = arg32(&port, ebp, 0x28);
    item = call_frame(&port, 0x45ffb0, arg16(&port, ebp, -0xcu), sign16(edi), ebx, ecx,
                      arg32(&port, ebp, 0xc), edi, ebp, make, 9);
    edi -= arg32(&port, ebp, 0x3c);
    moves[0] = sign16(port_u32(&port, ebp, -0xcu) - arg32(&port, ebp, 0x38));
    moves[1] = sign16(edi);
    item_finish(&port, item, arg32(&port, ebp, 0x2c), ebx, ecx, ebx, ecx, entry->edx, ebp,
                arg32(&port, ebp, 0x40), arg16(&port, ebp, 0x30), arg16(&port, ebp, 0x34), edi,
                moves);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460b60: the item from 0x45fc80 (the place words and five stack words, the owner eax)
 * with +0x14c the signed dx, +0x15c the word bx and the press 0x45c3c0, moved by the place less
 * the stack words 0x1c and 0x20. ret 0x30. */
uint32_t vertrix_port_menu_item_make_460b60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x30];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx = sign16(entry->ecx);
    uint32_t ecx;
    uint32_t edi = entry->ebx;
    uint32_t item;
    uint32_t make[5];
    uint32_t moves[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 12);
    ecx = arg16(&port, ebp, 8);
    port_set16(&port, ebp, -0xcu, entry->edx);
    guard_record(&port, ebp - 0x20, 0x515818);
    make[0] = entry->eax;
    make[1] = arg8(&port, ebp, 0x28);
    make[2] = port_u8(&port, ebp, 0x2c);
    make[3] = arg16(&port, ebp, 0x30);
    make[4] = arg32(&port, ebp, 0x34);
    item = call_frame(&port, 0x45fc80, arg16(&port, ebp, 0xc), arg16(&port, ebp, 0x10), ebx, ecx,
                      entry->eax, edi, ebp, make, 5);
    port_set32(&port, item, 0x14c, arg16(&port, ebp, -0xcu));
    port_set16(&port, item, 0x15c, edi);
    moves[0] = sign16(arg32(&port, ebp, 0xc) - arg32(&port, ebp, 0x1c));
    moves[1] = sign16(arg32(&port, ebp, 0x10) - arg32(&port, ebp, 0x20));
    item_finish(&port, item, 0x45c3c0, ebx, ecx, ebx, ecx, edi, ebp, arg32(&port, ebp, 0x24),
                arg16(&port, ebp, 0x14), arg16(&port, ebp, 0x18), edi, moves);
    return port_return(&port, item, vertrix_lift_edx);
}

/* The makers of 0x460df0, 0x460ed0 and 0x460fa0: the item from `maker` (eax, dx, bx, cx and the
 * stack words `make`, esi `esi`) with the press of the word `press` at bx the word `base` + 0x0c,
 * moved by eax less that word and dx less the word after. */
static uint32_t item_make_offset(PORT_SIGNATURE, uint32_t guard, uint32_t maker,
                                 const uint32_t *offsets, const uint8_t *kinds, unsigned count,
                                 unsigned words, uint32_t esi_offset, uint32_t press, uint32_t base)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x44];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx = sign16(entry->ebx);
    uint32_t ecx = sign16(entry->ecx);
    uint32_t edi = entry->eax;
    uint32_t item;
    uint32_t make[11];
    uint32_t moves[2];
    uint32_t press_ebx;
    unsigned index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, words);
    port_set16(&port, ebp, -0xcu, entry->edx);
    guard_record(&port, ebp - 0x20, guard);
    for (index = 0; index < count; index++)
    {
        uint32_t offset = offsets[index];
        make[index] = kinds[index] == 1   ? arg8(&port, ebp, offset)
                      : kinds[index] == 2 ? port_u8(&port, ebp, offset)
                      : kinds[index] == 3 ? arg16(&port, ebp, offset)
                                          : arg32(&port, ebp, offset);
    }
    item = call_frame(&port, maker, sign16(edi), arg16(&port, ebp, -0xcu), ebx, ecx,
                      arg32(&port, ebp, esi_offset), edi, ebp, make, count);
    press_ebx = arg32(&port, ebp, base + 8);
    edi -= press_ebx;
    moves[0] = sign16(edi);
    moves[1] = sign16(port_u32(&port, ebp, -0xcu) - arg32(&port, ebp, base + 0xc));
    item_finish(&port, item, arg32(&port, ebp, press), ebx, ecx, press_ebx,
                arg32(&port, ebp, base + 2), entry->eax, ebp, arg32(&port, ebp, base + 0x10),
                arg16(&port, ebp, base), arg16(&port, ebp, base + 4), edi, moves);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460df0: the item from 0x4602a0 (six stack words), the press of the word at 0x18. ret
 * 0x30. */
uint32_t vertrix_port_menu_item_make_460df0(PORT_SIGNATURE)
{
    static const uint32_t offsets[6] = {8, 0xc, 0x10, 0x14, 0x1c, 0x20};
    static const uint8_t kinds[6] = {0, 0, 1, 2, 3, 0};
    return item_make_offset(calls, services, globals, entry, 0x515820, 0x4602a0, offsets, kinds, 6,
                            12, 0xc, 0x18, 0x24);
}

/* Original 0x460ed0: the item from 0x460630 (six stack words), the press of the word at 0x20. ret
 * 0x30. */
uint32_t vertrix_port_menu_item_make_460ed0(PORT_SIGNATURE)
{
    static const uint32_t offsets[6] = {8, 0xc, 0x10, 0x14, 0x18, 0x1c};
    static const uint8_t kinds[6] = {0, 0, 0, 0, 0, 0};
    return item_make_offset(calls, services, globals, entry, 0x515824, 0x460630, offsets, kinds, 6,
                            12, 0xc, 0x20, 0x24);
}

/* Original 0x460fa0: the item from 0x460440 (eleven stack words), the press of the word at 0x24.
 * ret 0x44. */
uint32_t vertrix_port_menu_item_make_460fa0(PORT_SIGNATURE)
{
    static const uint32_t offsets[11] = {8,    0xc,  0x10, 0x14, 0x18, 0x1c,
                                         0x20, 0x28, 0x2c, 0x30, 0x34};
    static const uint8_t kinds[11] = {0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0};
    return item_make_offset(calls, services, globals, entry, 0x515828, 0x460440, offsets, kinds, 11,
                            17, 8, 0x24, 0x38);
}

/* Original 0x461090: the item from 0x460840 (ax, dx, bx, cx and ten stack words) with the press
 * of the word at 0x30, moved by the last ones less the place. ret 0x40. */
uint32_t vertrix_port_menu_item_make_461090(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x40];
    uint32_t ebp = entry->esp - 4;
    uint32_t ebx = sign16(entry->ebx);
    uint32_t ecx = sign16(entry->ecx);
    uint32_t edi = entry->edx;
    uint32_t item;
    uint32_t make[10];
    uint32_t moves[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 16);
    port_set16(&port, ebp, -0xcu, entry->eax);
    guard_record(&port, ebp - 0x20, 0x51582c);
    make[0] = arg32(&port, ebp, 8);
    make[1] = arg32(&port, ebp, 0xc);
    make[2] = arg32(&port, ebp, 0x10);
    make[3] = arg32(&port, ebp, 0x14);
    make[4] = arg32(&port, ebp, 0x18);
    make[5] = arg32(&port, ebp, 0x1c);
    make[6] = arg8(&port, ebp, 0x20);
    make[7] = port_u8(&port, ebp, 0x24);
    make[8] = arg16(&port, ebp, 0x28);
    make[9] = arg32(&port, ebp, 0x2c);
    item = call_frame(&port, 0x460840, arg16(&port, ebp, -0xcu), sign16(edi), ebx, ecx,
                      arg32(&port, ebp, 0x10), edi, ebp, make, 10);
    edi -= arg32(&port, ebp, 0x40);
    moves[0] = sign16(port_u32(&port, ebp, -0xcu) - arg32(&port, ebp, 0x3c));
    moves[1] = sign16(edi);
    item_finish(&port, item, arg32(&port, ebp, 0x30), ebx, ecx, ebx, ecx, entry->edx, ebp,
                arg32(&port, ebp, 0x44), arg16(&port, ebp, 0x34), arg16(&port, ebp, 0x38), edi,
                moves);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x472c10: the overlay of the record eax: a frame object (0x160 bytes, 0x4ca000,
 * 0x4b5400) placed (0x4adf20) and sized to the record's +4 by +8 (0x4b54d0), +0x94 0, height 0,
 * look 0, set up from the record (method +8) and started (method +0 with 2). */
uint32_t vertrix_port_overlay_spawn_472c10(PORT_SIGNATURE)
{
    static const uint32_t zeros[5] = {0, 0, 0, 0, 0};
    Port port;
    uint32_t record = entry->eax;
    uint32_t overlay;
    uint32_t methods;
    uint32_t ecx;
    uint32_t size[1];
    port_open(&port, calls, services, globals, entry);
    overlay = port_call_with(&port, 0x4ca000, 0x160, entry->edx, entry->ebx, entry->ecx, entry->esi,
                             record, entry->ebp);
    if (overlay != 0)
    {
        overlay = port_call_with(&port, 0x4b5400, overlay, vertrix_lift_edx, entry->ebx, entry->ecx,
                                 entry->esi, record, entry->ebp);
    }
    call_frame(&port, 0x4adf20, overlay, 0, 0, 0, overlay, record, entry->ebp, zeros, 5);
    size[0] = port_u16(&port, record, 8);
    ecx = port_u16(&port, record, 4);
    call_frame(&port, 0x4b54d0, overlay, 0, 0, ecx, overlay, record, entry->ebp, size, 1);
    port_set8(&port, overlay, 0x94, 0);
    port_set16(&port, overlay, 0x48, 0);
    port_set8(&port, overlay, 0x52, 0);
    methods = port_u32(&port, overlay, 0x158);
    port_call_with(&port, port_u32(&port, methods, 8), overlay, record, 0, methods, overlay, record,
                   entry->ebp);
    methods = port_u32(&port, overlay, 0x158);
    return port_return(&port,
                       port_call_with(&port, port_u32(&port, methods, 0), overlay, 2, 0, methods,
                                      overlay, record, entry->ebp),
                       entry->edx);
}

/* Original 0x476320: the input queue's record dx (96 bytes each from eax) becomes the current one
 * 0x54d634 and is acknowledged (0x475790 at +4). */
uint32_t vertrix_port_input_queue_acknowledge_full_476320(PORT_SIGNATURE)
{
    static const uint32_t zero[1] = {0};
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = entry->eax + (entry->edx & 0xffff) * 0x60;
    port_set32(&port, 0, 0x54d634, record);
    return port_return(&port,
                       call_frame(&port, 0x475790, record + 4, 0, 0, 0, entry->esi, entry->edi,
                                  entry->ebp, zero, 1),
                       vertrix_lift_edx);
}

/* Original 0x476720: the sound cue dx of the channel set eax on both sides (0x4761d0, 0x476280). */
uint32_t vertrix_port_sound_cue_both_476720(PORT_SIGNATURE)
{
    static const uint32_t zero[1] = {0};
    Port port;
    uint32_t cue = entry->edx & 0xffff;
    port_open(&port, calls, services, globals, entry);
    call_frame(&port, 0x4761d0, entry->eax, cue, 0, 0, entry->eax, cue, entry->ebp, zero, 1);
    return port_return(
        &port,
        call_frame(&port, 0x476280, entry->eax, cue, 0, 0, entry->eax, cue, entry->ebp, zero, 1),
        vertrix_lift_edx);
}

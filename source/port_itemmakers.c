#include "port_itemmakers.h"

/* The menu item constructors on their stack arguments. */

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

/* Original 0x45ffb0: the menu item at ax, dx sized bx by cx (guarded 0x515788): a 0x190 byte
 * object (0x4ca000; 0x4b42e0 makes it with esi 1) placed (0x4adf20) inset by 2 at each side
 * (0x4b54d0), shown (0x4ac7b0 with 2), +0x52 9, +0x94, +0x95 and +0x110 1, depth 0x7f (0x4ac4e0)
 * and +0x180 3; its label, a 0x180 byte box (0x4b6350 with 3), placed (0x4adf20) with the text of
 * the first stack word and the signed byte of the third (0x4b65d0), shown with the sixth
 * (0x4ac7b0), +0x44 the fourth byte, is put on it (0x4b3210 at the fourth word's word with the
 * sixth and 1). Its +0x17c is shown (0x4ac7b0), +0x94, +0x95 1, depth 0x7f (0x4ac4e0), +0x52 1
 * and +0x48 0x32; the mode is the seventh word (0x4b4510), +0x178 the eighth, +0x18c the text of
 * the ninth (0x4ca370) and +0x184 the second when set. Returns the item. ret 0x24. */
uint32_t vertrix_port_menu_item_construct_45ffb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x24];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 9);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x18u, entry->eax);
    port_set16(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    guard_record(&port, ebp - 0x30, 0x515788);
    esi = entry->ecx - 4;
    item = port_call_with(&port, 0x4ca000, 0x190, 0x4ec1ec, 0, 0x515788, esi, edi, ebp);
    edx = port_u32(&port, ebp, -0x18u) + 2;
    ebx = port_u32(&port, ebp, -0x10u) + 2;
    ecx = port_u32(&port, ebp, -0x14u) - 4;
    port_set32(&port, ebp, -0xcu, esi);
    port_set16(&port, ebp, -0x18u, edx);
    port_set16(&port, ebp, -0x10u, ebx);
    port_set32(&port, ebp, -0x14u, ecx);
    if (item != 0)
    {
        port_set32(&port, ebp, -0x1cu, item);
        edi = 0;
        port_set32(&port, ebp, -0x24u, 1);
        item = port_call_with(&port, 0x4b42e0, item, edx, ebx, ecx, 1, edi, ebp);
        port_set32(&port, ebp, -0x24u, edi);
    }
    esi = item;
    call_frame(&port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x10u));
    ecx = port_u16(&port, ebp, -0x14u);
    pushed[0] = port_u16(&port, ebp, -0xcu);
    call_frame(&port, 0x4b54d0, item, sign16(port_u16(&port, ebp, -0x18u)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    port_call_with(&port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, item, 0x52, 9);
    edi = item;
    port_set8(&port, item, 0x94, 1);
    port_set8(&port, item, 0x95, 1);
    port_set8(&port, item, 0x110, 1);
    port_set8(&port, item, 0x94, 1);
    port_call_with(&port, 0x4ac4e0, item, 0x7f, 0, ecx, esi, edi, ebp);
    port_set32(&port, item, 0x180, 3);
    memory = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, 0, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x1cu, memory);
        port_set32(&port, ebp, -0x24u, 3);
        label = port_call_with(&port, 0x4b6350, memory, 3, 0, 0, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = label;
    call_frame(&port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    call_frame(&port, 0x4b65d0, label, port_u32(&port, ebp, 8),
               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x10), 0, esi, edi, ebp, zeros, 3);
    ebx = port_u32(&port, ebp, 0x1c);
    port_call_with(&port, 0x4ac7b0, label, 2, ebx, 0, esi, edi, ebp);
    port_set8(&port, label, 0x44, port_u8(&port, ebp, 0x14));
    pushed[0] = ebx;
    pushed[1] = 1;
    call_frame(&port, 0x4b3210, item, label, port_u16(&port, ebp, 0x18), 0, esi, edi, ebp, pushed,
               2);
    esi = port_u32(&port, item, 0x17c);
    port_call_with(&port, 0x4ac7b0, esi, 2, 0, 0, esi, edi, ebp);
    port_set8(&port, esi, 0x94, 1);
    port_set8(&port, esi, 0x95, 1);
    port_call_with(&port, 0x4ac4e0, esi, 0x7f, 0, 0, esi, edi, ebp);
    port_set8(&port, esi, 0x52, 1);
    port_set16(&port, esi, 0x48, 0x32);
    port_call_with(&port, 0x4b4510, item, port_u32(&port, ebp, 0x20), 0, 0, esi, edi, ebp);
    port_set32(&port, item, 0x178, port_u32(&port, ebp, 0x24));
    esi = port_u32(&port, ebp, 0xc);
    port_call_with(&port, 0x4ca370, item + 0x18c, port_u32(&port, ebp, 0x28), 0, 0, esi, edi, ebp);
    if (esi != 0)
    {
        port_set32(&port, item, 0x184, esi);
    }
    return port_return(&port, item, vertrix_lift_edx);
}

/* The frame slots and stack words of an item maker in the manner of 0x4602a0. */
typedef struct ItemLayout
{
    uint32_t guard;
    uint32_t size;
    uint32_t maker;
    /* The words ax and dx and the dwords bx and cx at ebp less these. */
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    /* The stack words: the label's text, its signed byte, its show word, its depth byte and its
     * place word. */
    uint32_t text;
    uint32_t text_byte;
    uint32_t show;
    uint32_t depth;
    uint32_t place;
} ItemLayout;

/* The item at ax, dx sized bx by cx (guarded): a `size` byte object (0x4ca000; `maker` makes it
 * with esi 1) placed (0x4adf20) inset by 2 at each side (0x4b54d0), shown (0x4ac7b0 with 2),
 * +0x110 1, +0x52 9, +0x94, +0x95 1 and depth 0x7f (0x4ac4e0); its label, a 0x180 byte box
 * (0x4b6350 with 3), placed (0x4adf20) with the text and signed byte (0x4b65d0), shown (0x4ac7b0),
 * +0x44 the depth byte, is put on it (0x4b3210 at the place word with the show word and 1, esi
 * `place_esi` or the label for 0). Returns the item; *label the label. */
static uint32_t item_open(Port *port, const LiftEntry *entry, uint32_t ebp, const ItemLayout *at,
                          uint32_t place_esi, uint32_t *label_out)
{
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    port_set32(port, ebp, 0, entry->ebp);
    port_set32(port, ebp, -4u, entry->esi);
    port_set32(port, ebp, -8u, entry->edi);
    port_set16(port, ebp, -at->x, entry->eax);
    port_set16(port, ebp, -at->y, entry->edx);
    port_set32(port, ebp, -at->width, entry->ebx);
    port_set32(port, ebp, -at->height, entry->ecx);
    guard_record(port, ebp - 0x30, at->guard);
    esi = entry->ecx - 4;
    item = port_call_with(port, 0x4ca000, at->size, 0x4ec1ec, 0, at->guard, esi, edi, ebp);
    edx = port_u32(port, ebp, -at->x) + 2;
    ebx = port_u32(port, ebp, -at->y) + 2;
    ecx = port_u32(port, ebp, -at->width) - 4;
    port_set32(port, ebp, -at->height, esi);
    port_set16(port, ebp, -at->x, edx);
    port_set16(port, ebp, -at->y, ebx);
    port_set32(port, ebp, -at->width, ecx);
    if (item != 0)
    {
        port_set32(port, ebp, -0x1cu, item);
        edi = 0;
        port_set32(port, ebp, -0x24u, 1);
        item = port_call_with(port, at->maker, item, edx, ebx, ecx, 1, edi, ebp);
        port_set32(port, ebp, -0x24u, edi);
    }
    esi = item;
    call_frame(port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(port, ebp, -at->y));
    ecx = port_u16(port, ebp, -at->width);
    pushed[0] = port_u16(port, ebp, -at->height);
    call_frame(port, 0x4b54d0, item, sign16(port_u16(port, ebp, -at->x)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    port_call_with(port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(port, item, 0x110, 1);
    port_set8(port, item, 0x52, 9);
    port_set8(port, item, 0x94, 1);
    port_set8(port, item, 0x95, 1);
    port_call_with(port, 0x4ac4e0, item, 0x7f, 0, ecx, esi, edi, ebp);
    edi = item;
    memory = port_call_with(port, 0x4ca000, 0x180, vertrix_lift_edx, 0, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(port, ebp, -0x1cu, memory);
        port_set32(port, ebp, -0x24u, 3);
        label = port_call_with(port, 0x4b6350, memory, 3, 0, 0, esi, edi, ebp);
        port_set32(port, ebp, -0x24u, 0);
    }
    esi = label;
    call_frame(port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    call_frame(port, 0x4b65d0, label, port_u32(port, ebp, at->text),
               (uint32_t)(int32_t)(int8_t)port_u8(port, ebp, at->text_byte), 0, esi, edi, ebp,
               zeros, 3);
    ebx = port_u32(port, ebp, at->show);
    port_call_with(port, 0x4ac7b0, label, 2, ebx, 0, esi, edi, ebp);
    port_set8(port, label, 0x44, port_u8(port, ebp, at->depth));
    pushed[0] = ebx;
    pushed[1] = 1;
    call_frame(port, 0x4b3210, item, label, port_u16(port, ebp, at->place), 0,
               place_esi != 0 ? port_u32(port, ebp, place_esi) : label, edi, ebp, pushed, 2);
    *label_out = label;
    return item;
}

/* Original 0x4602a0: the item (guarded 0x5157a8, 0x17c bytes, made by 0x4b34d0) with its label
 * (item_open) and +0x178 the second word when set. Returns the item. ret 0x18. */
uint32_t vertrix_port_menu_item_construct_4602a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    static const ItemLayout at = {0x5157a8, 0x17c, 0x4b34d0, 0xc,  0x14, 0x18,
                                  0x10,     8,     0x10,     0x1c, 0x14, 0x18};
    Port port;
    uint8_t stack[BELOW + 8 + 0x18];
    uint32_t ebp = entry->esp - 4;
    uint32_t item;
    uint32_t label;
    uint32_t text;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
    item = item_open(&port, entry, ebp, &at, 0xc, &label);
    text = port_u32(&port, ebp, 0xc);
    if (text != 0)
    {
        port_set32(&port, item, 0x178, text);
    }
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460440: the item (guarded 0x5157c4, 0x188 bytes, made by 0x4b3fb0) with its label
 * (item_open), its range the second and third words (0x4b35b0), +0x178 the sixth and +0x184 the
 * seventh word when set, and two arrows (0x471920 and 0x471940, +0x10c the item, +0x70 the fourth
 * and fifth words) at +0x17c and +0x180. Returns the item. ret 0x2c. */
uint32_t vertrix_port_menu_item_construct_460440(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    static const ItemLayout at = {0x5157c4, 0x188, 0x4b3fb0, 0x10, 0x14, 0xc,
                                  0x18,     8,     0x24,     0x30, 0x28, 0x2c};
    Port port;
    uint8_t stack[BELOW + 8 + 0x2c];
    uint32_t ebp = entry->esp - 4;
    uint32_t item;
    uint32_t label;
    uint32_t esi;
    uint32_t ebx;
    uint32_t value;
    uint32_t left;
    uint32_t right;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 11);
    item = item_open(&port, entry, ebp, &at, 0, &label);
    ebx = port_u32(&port, ebp, 0x10);
    esi = port_u32(&port, ebp, 0x1c);
    port_call_with(&port, 0x4b35b0, item, port_u32(&port, ebp, 0xc), ebx, 0, esi, item, ebp);
    if (esi != 0)
    {
        port_set32(&port, item, 0x178, esi);
    }
    value = port_u32(&port, ebp, 0x20);
    if (value != 0)
    {
        port_set32(&port, item, 0x184, value);
    }
    left = port_call_with(&port, 0x471920, value, vertrix_lift_edx, ebx, 0, esi, item, ebp);
    port_set32(&port, left, 0x10c, item);
    port_set32(&port, left, 0x70, port_u32(&port, ebp, 0x14));
    right = port_call_with(&port, 0x471940, port_u32(&port, ebp, 0x14), port_u32(&port, ebp, 0x18),
                           ebx, 0, left, item, ebp);
    port_set32(&port, right, 0x10c, item);
    port_set32(&port, right, 0x70, vertrix_lift_edx);
    port_set32(&port, item, 0x17c, left);
    port_set32(&port, item, 0x180, right);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460630: the item at ax, dx sized bx by cx (guarded 0x5157e0): a 0x190 byte object
 * (0x4ca000 asked with the inset place in edx, ebx and ecx; 0x4b3a00 makes it with esi 1) placed
 * (0x4adf20) inset by 2 at each side (0x4b54d0), shown (0x4ac7b0 with 2), +0x52 9, +0x94 1; its
 * label, a 0x180 byte box (0x4b6350 with 3), placed (0x4adf20) with the text 0x50e29e and the
 * font byte 0x4f9bfd (0x4b65d0), shown (0x4ac7b0 with 2 and 2), +0x44 0x10, is put on it
 * (0x4b3210 at 2 with 1 and 1). Its range is the fourth and fifth words (0x4b3c30) and its step
 * the sixth (0x4b3c40); its +0x17c takes +0x52 0xa and +0x180 9, both +0x94 1; +0x178 is the
 * third word when set; two arrows (0x471920, 0x471940; +0x10c the item, +0x70 the first and
 * second words, the state 0x446c10) at +0x170 and +0x174. Returns the item. ret 0x18. */
uint32_t vertrix_port_menu_item_construct_460630(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x18];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    uint32_t left;
    uint32_t right;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x14u, entry->eax);
    port_set16(&port, ebp, -0x18u, entry->edx);
    port_set32(&port, ebp, -0x1cu, entry->ebx);
    port_set32(&port, ebp, -0x20u, entry->ecx);
    guard_record(&port, ebp - 0x38, 0x5157e0);
    esi = entry->ecx - 4;
    edx = port_u32(&port, ebp, -0x14u) + 2;
    ebx = port_u32(&port, ebp, -0x18u) + 2;
    ecx = port_u32(&port, ebp, -0x1cu) - 4;
    port_set8(&port, ebp, -0xcu, 0x10);
    port_set32(&port, ebp, -0x20u, esi);
    port_set8(&port, ebp, -0x10u, port_u8(&port, 0, 0x4f9bfd));
    port_set16(&port, ebp, -0x14u, edx);
    port_set16(&port, ebp, -0x18u, ebx);
    port_set32(&port, ebp, -0x1cu, ecx);
    item = port_call_with(&port, 0x4ca000, 0x190, edx, ebx, ecx, esi, edi, ebp);
    if (item != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x24u, item);
        edi = 0;
        port_set32(&port, ebp, -0x2cu, 1);
        item = port_call_with(&port, 0x4b3a00, item, edx, ebx, ecx, esi, edi, ebp);
        port_set32(&port, ebp, -0x2cu, edi);
    }
    edi = item;
    call_frame(&port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x18u));
    ecx = port_u16(&port, ebp, -0x1cu);
    pushed[0] = port_u16(&port, ebp, -0x20u);
    call_frame(&port, 0x4b54d0, item, sign16(port_u16(&port, ebp, -0x14u)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    esi = item;
    port_call_with(&port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, item, 0x52, 9);
    port_set8(&port, item, 0x94, 1);
    memory = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x24u, memory);
        port_set32(&port, ebp, -0x2cu, 3);
        label = port_call_with(&port, 0x4b6350, memory, 3, ebx, 0, esi, edi, ebp);
        port_set32(&port, ebp, -0x2cu, 0);
    }
    edi = label;
    call_frame(&port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    call_frame(&port, 0x4b65d0, label, 0x50e29e,
               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0x10u), 0, esi, edi, ebp, zeros, 3);
    port_call_with(&port, 0x4ac7b0, label, 2, 2, 0, esi, edi, ebp);
    port_set8(&port, label, 0x44, port_u8(&port, ebp, -0xcu));
    pushed[0] = 1;
    pushed[1] = 1;
    call_frame(&port, 0x4b3210, item, label, 2, 0, esi, edi, ebp, pushed, 2);
    ebx = port_u32(&port, ebp, 0x18);
    port_call_with(&port, 0x4b3c30, item, port_u32(&port, ebp, 0x14), ebx, 0, esi, edi, ebp);
    port_call_with(&port, 0x4b3c40, item, port_u32(&port, ebp, 0x1c), ebx, 0, esi, edi, ebp);
    eax = port_u32(&port, item, 0x17c);
    edx = port_u32(&port, item, 0x180);
    port_set8(&port, eax, 0x52, 0xa);
    port_set8(&port, eax, 0x94, 1);
    port_set8(&port, edx, 0x52, 9);
    ebx = port_u32(&port, ebp, 0x10);
    port_set8(&port, edx, 0x94, 1);
    if (ebx != 0)
    {
        port_set32(&port, item, 0x178, ebx);
    }
    left = port_call_with(&port, 0x471920, eax, edx, ebx, 0, esi, edi, ebp);
    edi = left;
    port_set32(&port, left, 0x10c, item);
    port_set32(&port, left, 0x70, port_u32(&port, ebp, 8));
    eax = port_call_with(&port, 0x4ac8f0, left, 0x446c10, ebx, 0, esi, edi, ebp);
    right = port_call_with(&port, 0x471940, eax, vertrix_lift_edx, ebx, 0, esi, edi, ebp);
    port_set32(&port, right, 0x10c, item);
    port_set32(&port, right, 0x70, port_u32(&port, ebp, 0xc));
    port_call_with(&port, 0x4ac8f0, right, 0x446c10, ebx, right, esi, edi, ebp);
    port_set32(&port, item, 0x170, left);
    port_set32(&port, item, 0x174, right);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460840: the item at ax, dx sized bx by cx (guarded 0x5157fc): a 0x198 byte object
 * (0x4ca000; 0x4b4cf0 makes it with esi 1) placed (0x4adf20) and sized (0x4b54d0), shown
 * (0x4ac7b0 with 2), +0x52 9, +0x94 1, +0x194 4; its label, a 0x180 byte box (0x4b6350 with 3),
 * placed (0x4adf20) with the text 0x50e29f and the signed byte of the seventh word (0x4b65d0),
 * shown with the tenth (0x4ac7b0), +0x44 the eighth byte, is put on it (0x4b3210 at the ninth
 * word's word with 1 and the tenth). Its range is the first and second words (0x4b4fa0) and its
 * step the third (0x4b4fb0); its +0x17c, +0x180 and +0x184 take +0x52 9, 7 and 9 and +0x94 1;
 * +0x178 is the sixth word when set; two arrows (0x471960, 0x471980; the state 0x446fe0, +0x10c
 * the item, +0x70 the fourth and fifth words) at +0x170 and +0x174. Returns the item. ret 0x28. */
uint32_t vertrix_port_menu_item_construct_460840(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x28];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    uint32_t left;
    uint32_t right;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 10);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x18u, entry->eax);
    port_set16(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    guard_record(&port, ebp - 0x30, 0x5157fc);
    item = port_call_with(&port, 0x4ca000, 0x198, 0x4ec1ec, 0, 0x5157fc, esi, edi, ebp);
    if (item != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x1cu, item);
        port_set32(&port, ebp, -0x24u, 1);
        item = port_call_with(&port, 0x4b4cf0, item, vertrix_lift_edx, 0, 0x5157fc, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    edi = item;
    call_frame(&port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x10u));
    ecx = port_u16(&port, ebp, -0x14u);
    pushed[0] = port_u16(&port, ebp, -0xcu);
    call_frame(&port, 0x4b54d0, item, sign16(port_u16(&port, ebp, -0x18u)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    port_call_with(&port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, item, 0x52, 9);
    esi = item;
    port_set8(&port, item, 0x94, 1);
    port_set32(&port, item, 0x194, 4);
    memory = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x1cu, memory);
        port_set32(&port, ebp, -0x24u, 3);
        label = port_call_with(&port, 0x4b6350, memory, 3, ebx, 0, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    edi = label;
    call_frame(&port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    call_frame(&port, 0x4b65d0, label, 0x50e29f,
               (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x20), 0, esi, edi, ebp, zeros, 3);
    ebx = port_u32(&port, ebp, 0x2c);
    port_call_with(&port, 0x4ac7b0, label, 2, ebx, 0, esi, edi, ebp);
    port_set8(&port, label, 0x44, port_u8(&port, ebp, 0x24));
    pushed[0] = 1;
    pushed[1] = ebx;
    call_frame(&port, 0x4b3210, item, label, port_u16(&port, ebp, 0x28), 0, esi, edi, ebp, pushed,
               2);
    ebx = port_u32(&port, ebp, 0xc);
    port_call_with(&port, 0x4b4fa0, item, port_u32(&port, ebp, 8), ebx, 0, esi, edi, ebp);
    port_call_with(&port, 0x4b4fb0, item, port_u32(&port, ebp, 0x10), ebx, 0, esi, edi, ebp);
    first = port_u32(&port, item, 0x17c);
    second = port_u32(&port, item, 0x180);
    third = port_u32(&port, item, 0x184);
    port_set8(&port, first, 0x52, 9);
    port_set8(&port, first, 0x94, 1);
    port_set8(&port, second, 0x52, 7);
    port_set8(&port, second, 0x94, 1);
    port_set8(&port, third, 0x52, 9);
    edi = port_u32(&port, ebp, 0x1c);
    port_set8(&port, third, 0x94, 1);
    if (edi != 0)
    {
        port_set32(&port, item, 0x178, edi);
    }
    left = port_call_with(&port, 0x471960, first, second, ebx, third, esi, edi, ebp);
    port_call_with(&port, 0x4ac8f0, left, 0x446fe0, ebx, left, esi, edi, ebp);
    port_set32(&port, left, 0x10c, item);
    port_set32(&port, left, 0x70, port_u32(&port, ebp, 0x14));
    right = port_call_with(&port, 0x471980, port_u32(&port, ebp, 0x14), 0x446fe0, ebx, left, esi,
                           edi, ebp);
    edi = right;
    port_call_with(&port, 0x4ac8f0, right, vertrix_lift_edx, ebx, left, esi, edi, ebp);
    port_set32(&port, right, 0x10c, item);
    port_set32(&port, right, 0x70, port_u32(&port, ebp, 0x18));
    port_set32(&port, item, 0x170, left);
    port_set32(&port, item, 0x174, right);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x460c50: two items from 0x45fb00 for the owner eax, both at cx, the first word, dx
 * and bx with the sixth word's word, the seventh word, the owner, the colour (0xe for a ninth
 * byte of 0xa, 0xd for 5, else the frame's byte) and the tenth byte. The first is nudged (+0xe 3,
 * +0x16 2) and takes the press 0x444be0; the second takes none (0x4ac930 with 0) and is
 * returned. Each takes the state 0x443460, the hover 0x4486f0 (0x4ac910 with ecx the fifth word),
 * its motion (0x471820 at the second and third words' words with the eighth, by the first word
 * less the fifth and cx less the fourth) and joins the list 0x54671c (0x4b5e70). ret 0x2c. */
uint32_t vertrix_port_menu_item_pair_460c50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x2c];
    uint32_t ebp = entry->esp - 4;
    uint32_t make[5];
    uint32_t moves[2];
    uint32_t owner = entry->eax;
    uint32_t across = sign16(entry->edx);
    uint32_t edi = sign16(entry->ebx);
    uint32_t down;
    uint32_t first;
    uint32_t kind;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t item;
    uint32_t pair;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 11);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x1cu, owner);
    port_set16(&port, ebp, -0x10u, entry->ecx);
    guard_record(&port, ebp - 0x4c, 0x51581c);
    kind = port_u8(&port, ebp, 0x28);
    if (kind == 0xa)
    {
        port_set8(&port, ebp, -0xcu, 0xe);
    }
    else if (kind == 5)
    {
        port_set8(&port, ebp, -0xcu, 0xd);
    }
    port_set32(&port, ebp, -0x38u, port_u8(&port, ebp, 0x2c));
    make[0] = sign16(port_u16(&port, ebp, 0x1c));
    make[1] = port_u32(&port, ebp, 0x20);
    make[2] = owner;
    make[3] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, -0xcu);
    make[4] = port_u32(&port, ebp, -0x38u);
    port_set32(&port, ebp, -0x34u, make[0]);
    port_set32(&port, ebp, -0x30u, across);
    first = sign16(port_u16(&port, ebp, 8));
    port_set32(&port, ebp, -0x2cu, first);
    down = sign16(port_u16(&port, ebp, -0x10u));
    port_set32(&port, ebp, -0x28u, down);
    item = call_frame(&port, 0x45fb00, down, first, across, edi, make[1], edi, ebp, make, 5);
    port_set16(&port, item, 0xe, port_u16(&port, item, 0xe) + 3);
    ebx = ((across & 0xffff0000u) | port_u16(&port, item, 0x16)) + 2;
    port_set16(&port, item, 0x16, ebx);
    port_call_with(&port, 0x4ac8f0, item, 0x443460, ebx, edi, item, edi, ebp);
    port_call_with(&port, 0x4ac930, item, 0x444be0, ebx, edi, item, edi, ebp);
    ecx = port_u32(&port, ebp, 0x18);
    port_call_with(&port, 0x4ac910, item, 0x4486f0, ebx, ecx, item, edi, ebp);
    moves[1] = sign16(port_u32(&port, ebp, 8) - ecx);
    port_set32(&port, ebp, -0x18u, moves[1]);
    moves[0] = sign16(port_u32(&port, ebp, -0x10u) - port_u32(&port, ebp, 0x14));
    port_set32(&port, ebp, -0x24u, moves[0]);
    ecx = sign16(port_u16(&port, ebp, 0x10));
    port_set32(&port, ebp, -0x20u, ecx);
    ebx = sign16(port_u16(&port, ebp, 0xc));
    port_set32(&port, ebp, -0x14u, ebx);
    call_frame(&port, 0x471820, item, port_u32(&port, ebp, 0x24), ebx, ecx, item, edi, ebp, moves,
               2);
    ecx = port_u32(&port, ebp, -0x38u);
    port_call_with(&port, 0x4b5e70, 0x54671c, item, ebx, ecx, item, edi, ebp);
    make[0] = port_u32(&port, ebp, -0x34u);
    make[1] = port_u32(&port, ebp, 0x20);
    make[2] = port_u32(&port, ebp, -0x1cu);
    make[3] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x28);
    make[4] = ecx;
    ebx = port_u32(&port, ebp, -0x30u);
    pair = call_frame(&port, 0x45fb00, port_u32(&port, ebp, -0x28u), port_u32(&port, ebp, -0x2cu),
                      ebx, edi, make[1], edi, ebp, make, 5);
    port_call_with(&port, 0x4ac8f0, pair, 0x443460, ebx, edi, pair, edi, ebp);
    port_call_with(&port, 0x4ac930, pair, 0, ebx, edi, pair, edi, ebp);
    port_call_with(&port, 0x4ac910, pair, 0x4486f0, ebx, edi, pair, edi, ebp);
    moves[0] = port_u32(&port, ebp, -0x24u);
    moves[1] = port_u32(&port, ebp, -0x18u);
    ebx = port_u32(&port, ebp, -0x14u);
    ecx = port_u32(&port, ebp, -0x20u);
    call_frame(&port, 0x471820, pair, port_u32(&port, ebp, 0x24), ebx, ecx, pair, edi, ebp, moves,
               2);
    port_call_with(&port, 0x4b5e70, 0x54671c, pair, ebx, ecx, pair, edi, ebp);
    return port_return(&port, pair, vertrix_lift_edx);
}

/* Original 0x461180: the menu of eax items (guarded 0x515830): item i of the owners at edx, the
 * place words at ebx and ecx and the kinds at the first stack word is, for kind 1, a toggle
 * (0x460b60 with the owner, the place, the second word's word, the third, fourth and fifth words'
 * words, the running place, the fifth word plus eax times the third less 1, the colour 0x4f9bfc,
 * 0x10, 0 and 1) and otherwise a labelled pair (0x460a40, then 0x460c50 with the colour
 * 0x4f9bf8); the running place starts at the fifth word and steps by the third less 1, the
 * toggle word alternates 1 and 0. Then a 0x15c byte object (0x4ca000, 0x4abd70 makes it) takes
 * the state 0x45c7b0 (0x4ac8f0) and joins the list 0x54671c (0x4b5e70), and 0x532a48 is
 * cleared. Returns the guard's link. ret 0x18. */
uint32_t vertrix_port_menu_items_build_461180(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x50
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x18];
    uint32_t ebp = entry->esp - 4;
    uint32_t args[12];
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = entry->edi;
    uint32_t step;
    uint32_t last;
    uint32_t index;
    uint32_t owner;
    uint32_t toggle;
    uint32_t object;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 6);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x10u, entry->eax);
    port_set32(&port, ebp, -0x28u, entry->edx);
    port_set32(&port, ebp, -0x2cu, entry->ebx);
    port_set32(&port, ebp, -0x30u, entry->ecx);
    guard_record(&port, ebp - 0x4c, 0x515830);
    step = port_u32(&port, ebp, 0x10) - 1;
    port_set16(&port, ebp, -0xcu, 0);
    edx = port_u32(&port, ebp, -0x10u) * step;
    port_set32(&port, ebp, -0x1cu, step);
    ecx = 0x515830;
    esi = 1;
    ebx = port_u32(&port, ebp, 0x18);
    port_set32(&port, ebp, -0x24u, 1);
    port_set32(&port, ebp, -0x18u, edx);
    port_set16(&port, ebp, -0x14u, ebx);
    for (;;)
    {
        index = sign16(port_u16(&port, ebp, -0xcu));
        edx = port_u16(&port, ebp, -0x10u);
        if ((int32_t)index >= (int32_t)edx)
        {
            break;
        }
        owner = port_u32(&port, ebp, -0x28u) + index * 4;
        port_set32(&port, ebp, -0x20u, owner);
        last = sign16(port_u32(&port, ebp, 0x18) + port_u32(&port, ebp, -0x18u));
        toggle = port_u32(&port, ebp, -0x24u);
        if (port_u32(&port, port_u32(&port, ebp, 8), index * 4) == 1)
        {
            args[11] = 1;
            args[10] = 0;
            args[9] = 0x10;
            args[8] = (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9bf9) >> 24);
            args[7] = toggle;
            args[6] = sign16(port_u16(&port, ebp, 0x18));
            args[5] = sign16(port_u16(&port, ebp, 0x14));
            args[4] = last;
            ecx = sign16(port_u16(&port, ebp, 0xc));
            args[3] = ecx;
            args[2] = sign16(port_u16(&port, ebp, -0x14u));
            args[1] = args[5];
            args[0] = sign16(port_u16(&port, ebp, 0x10));
            esi = port_u32(&port, ebp, -0x2cu);
            ebx = sign16(port_u16(&port, port_u32(&port, ebp, -0x30u), index * 2));
            call_frame(&port, 0x460b60, port_u32(&port, owner, 0),
                       sign16(port_u16(&port, index * 2 + esi, 0)), ebx, ecx, esi, 1, ebp, args,
                       12);
        }
        else
        {
            esi = sign16(port_u16(&port, ebp, 0x14));
            edi = sign16(port_u16(&port, ebp, 0xc));
            port_set32(&port, ebp, -0x38u, sign16(port_u16(&port, ebp, 0x18)));
            port_set32(&port, ebp, -0x34u, last);
            args[4] = toggle;
            args[3] = port_u32(&port, ebp, -0x38u);
            args[2] = esi;
            args[1] = last;
            args[0] = edi;
            call_frame(&port, 0x460a40, edi, sign16(port_u16(&port, ebp, 0x1c)), esi,
                       sign16(port_u32(&port, ebp, -0x14u) + port_u32(&port, ebp, 0x10) -
                              port_u32(&port, ebp, 0x1c)),
                       esi, edi, ebp, args, 5);
            args[10] = 1;
            args[9] = 0x10;
            args[8] = (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9bf5) >> 24);
            args[7] = port_u32(&port, ebp, -0x24u);
            args[6] = 1;
            args[5] = 0;
            args[4] = port_u32(&port, ebp, -0x38u);
            args[3] = esi;
            args[2] = port_u32(&port, ebp, -0x34u);
            args[1] = edi;
            args[0] = sign16(port_u16(&port, ebp, -0x14u));
            ebx = sign16(port_u16(&port, ebp, 0x10));
            call_frame(&port, 0x460c50, port_u32(&port, owner, 0), edi, ebx, esi, esi, edi, ebp,
                       args, 11);
        }
        edi = port_u32(&port, ebp, -0x24u);
        ecx = port_u32(&port, ebp, -0x14u) + port_u32(&port, ebp, -0x1cu);
        esi = port_u32(&port, ebp, -0xcu) + 1;
        port_set32(&port, ebp, -0x24u, 1 - edi);
        port_set16(&port, ebp, -0xcu, esi);
        port_set16(&port, ebp, -0x14u, ecx);
    }
    object = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, edi, ebp);
    if (object != 0)
    {
        object = port_call_with(&port, 0x4abd70, object, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    }
    port_call_with(&port, 0x4ac8f0, object, 0x45c7b0, ebx, object, esi, edi, ebp);
    port_call_with(&port, 0x4b5e70, 0x54671c, object, ebx, object, esi, edi, ebp);
    port_set32(&port, 0, 0x532a48, 0);
    return port_return(&port, port_u32(&port, ebp, -0x4cu), vertrix_lift_edx);
}

/* Original 0x461790: the options menu (guarded 0x515888, the six texts' finaliser 0x513e60 at
 * ebp-0x1c): the texts at ebp-0x7c start from 0x5467e8 and are OPTIONS, GAME, SOUND, KEYS, HIGHS
 * and RETURN (0x4ca280, the count of those made at ebp-0x18); the across words at ebp-0x38 are
 * 0x546800's first with 0x4f7b7c, 0x4f7b80, 0x4f7b98, 0x4f7b84 and 0x4f7b88 after it, the down
 * words at ebp-0x2c 0x4fd4e0's and the kinds at ebp-0x64 0x4fd4ec's.
 * The six items are built (0x461180) 0xab wide at the screen's (0x558c7c) centre less 0xab,
 * spaced 0x1a, from its height less 0xbf, and the texts are released (0x418570). Returns the
 * guard's link; the registers kept. */
uint32_t vertrix_port_options_menu_461790(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x80
    };
    static const uint32_t texts[6] = {0x50e30d, 0x50e315, 0x50e31a, 0x50e320, 0x50e325, 0x50e32b};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t args[6];
    uint32_t screen;
    uint32_t i;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x4cu, port.env.chain);
    port_set32(&port, ebp, -0x48u, 0x4ec1ec);
    port_set32(&port, ebp, -0x44u, 0x515888);
    port_set32(&port, ebp, -0x1cu, 0x513e60);
    port_set32(&port, ebp, -0x40u, 1);
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0x20u, ebp - 0x7c);
    for (i = 0; i < 6; i++)
    {
        port_set32(&port, ebp, -0x7cu + i * 4, port_u32(&port, 0, 0x5467e8 + i * 4));
    }
    port_call_with(&port, 0x4ca280, ebp - 0x7c, texts[0], 4, 0, 0x546800, ebp - 0x64, ebp);
    port_set32(&port, ebp, -0x18u, 1);
    port_call_with(&port, 0x4ca280, ebp - 0x78, texts[1], 4, 3, 5, ebp - 0x64, ebp);
    for (i = 2; i < 6; i++)
    {
        port_set32(&port, ebp, -0x18u, i);
        port_call_with(&port, 0x4ca280, ebp - 0x7c + i * 4, texts[i], 4, 3, 5, 6, ebp);
    }
    port_set32(&port, ebp, -0x18u, 6);
    port_set32(&port, ebp, -0x40u, 3);
    for (i = 0; i < 3; i++)
    {
        port_set32(&port, ebp, -0x38u + i * 4, port_u32(&port, 0, 0x546800 + i * 4));
    }
    port_set16(&port, ebp, -0x36u, port_u16(&port, 0, 0x4f7b7c));
    port_set16(&port, ebp, -0x34u, port_u16(&port, 0, 0x4f7b80));
    for (i = 0; i < 3; i++)
    {
        port_set32(&port, ebp, -0x2cu + i * 4, port_u32(&port, 0, 0x4fd4e0 + i * 4));
    }
    port_set16(&port, ebp, -0x32u, port_u16(&port, 0, 0x4f7b98));
    port_set16(&port, ebp, -0x30u, port_u16(&port, 0, 0x4f7b84));
    port_set16(&port, ebp, -0x2eu, port_u16(&port, 0, 0x4f7b88));
    screen = port_u32(&port, 0, 0x558c7c);
    for (i = 0; i < 6; i++)
    {
        port_set32(&port, ebp, -0x64u + i * 4, port_u32(&port, 0, 0x4fd4ec + i * 4));
    }
    args[0] = ebp - 0x64;
    args[1] = 0xab;
    args[2] = 0x1a;
    args[3] = sign16(port_shr(port_u32(&port, screen, 4) - 0xab, 1));
    args[4] = sign16(((screen & 0xffff0000u) | port_u16(&port, screen, 8)) - 0xbf);
    args[5] = 0x1a;
    call_frame(&port, 0x461180, 6, ebp - 0x7c, ebp - 0x38, ebp - 0x2c, 0x4fd504, ebp - 0x4c, ebp,
               args, 6);
    port_set32(&port, ebp, -0x40u, 0);
    port_call_with(&port, 0x418570, ebp - 0x7c, 0, ebp - 0x38, 0, 0x4fd504, ebp - 0x4c, ebp);
    port_set32(&port, ebp, -0x40u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x4cu), entry->edx);
}

/* Original 0x470960: the item at ax, dx sized bx by cx (guarded 0x516210): a 0x190 byte object
 * (0x4ca000; 0x4b42e0 makes it with esi 1) placed (0x4adf20) and sized (0x4b54d0), shown
 * (0x4ac7b0 with 2), +0x52 9, +0x94, +0x95 and +0x110 1, depth 0x7f (0x4ac4e0) and +0x180 3; its
 * label, a 0x180 byte box (0x4b6350 with 3), placed (0x4adf20) with the text of the second
 * stack word and the signed byte of the fourth (0x4b65d0), +0x52 7, shown (0x4ac7b0), +0x44 the
 * first byte, is put on it (0x4b3210 at the third word's word with 0 and 1). Its +0x17c is shown
 * (0x4ac7b0), +0x94, +0x95 1, depth 0x7f (0x4ac4e0), +0x52 1 and +0x48 0x32. Returns the item.
 * ret 0x10. */
uint32_t vertrix_port_menu_item_construct_470960(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0x10];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    uint32_t part;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x10u, entry->eax);
    port_set16(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0x18u, entry->ebx);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    guard_record(&port, ebp - 0x30, 0x516210);
    item = port_call_with(&port, 0x4ca000, 0x190, 0x4ec1ec, 0, 0x516210, esi, edi, ebp);
    if (item != 0)
    {
        port_set32(&port, ebp, -0x1cu, item);
        port_set32(&port, ebp, -0x24u, 1);
        item = port_call_with(&port, 0x4b42e0, item, vertrix_lift_edx, 0, 0x516210, 1, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = item;
    call_frame(&port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x14u));
    ecx = port_u16(&port, ebp, -0x18u);
    pushed[0] = port_u16(&port, ebp, -0xcu);
    call_frame(&port, 0x4b54d0, item, sign16(port_u16(&port, ebp, -0x10u)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    port_call_with(&port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, item, 0x52, 9);
    edi = item;
    port_set8(&port, item, 0x94, 1);
    port_set8(&port, item, 0x95, 1);
    port_set8(&port, item, 0x110, 1);
    port_set8(&port, item, 0x94, 1);
    port_call_with(&port, 0x4ac4e0, item, 0x7f, 0, ecx, esi, edi, ebp);
    port_set32(&port, item, 0x180, 3);
    memory = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, 0, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x1cu, memory);
        port_set32(&port, ebp, -0x24u, 3);
        label = port_call_with(&port, 0x4b6350, memory, 3, 0, 0, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = label;
    call_frame(&port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x14);
    call_frame(&port, 0x4b65d0, label, port_u32(&port, ebp, 0xc), ebx, 0, esi, edi, ebp, zeros, 3);
    port_set8(&port, label, 0x52, 7);
    port_call_with(&port, 0x4ac7b0, label, 2, ebx, 0, esi, edi, ebp);
    port_set8(&port, label, 0x44, port_u8(&port, ebp, 8));
    pushed[0] = 0;
    pushed[1] = 1;
    call_frame(&port, 0x4b3210, item, label, port_u16(&port, ebp, 0x10), 0, esi, edi, ebp, pushed,
               2);
    part = port_u32(&port, item, 0x17c);
    port_call_with(&port, 0x4ac7b0, part, 2, 0, 0, part, edi, ebp);
    port_set8(&port, part, 0x94, 1);
    port_set8(&port, part, 0x95, 1);
    port_call_with(&port, 0x4ac4e0, part, 0x7f, 0, 0, part, edi, ebp);
    port_set8(&port, part, 0x52, 1);
    port_set16(&port, part, 0x48, 0x32);
    return port_return(&port, item, vertrix_lift_edx);
}

/* Original 0x470b20: the label of the row al with the text edx (guarded 0x51622c): a 0x170 byte
 * object (0x4ca000; 0x4b3100 makes it with edi 1) at 2 across and 0x16 times the row plus
 * 0x4f88ac plus 1 down, 0xdc by 0x16 (0x4adf20, 0x4b54d0), shown (0x4ac7b0 with 2), +0x52 9,
 * +0x48 0, +0x44 0x10, +0x94 1, +0x95 0, clipped to 0..0x27f by 0x4f88ac..0x1df (+0xa8..+0xae)
 * and +0x8e 3; its text, a 0x180 byte box (0x4b6350 with 3), placed (0x4adf20) with the text and
 * the font byte 0x4f9c0b (0x4b65d0), shown (0x4ac7b0), +0x44 0x10, +0x4e 0x32, +0x93 0, +0x95
 * 4, is put on it (0x4b3210 at 0 with 1 and 1) and clipped likewise. Returns the object; ebx,
 * ecx, esi and edi kept. */
uint32_t vertrix_port_row_label_470b20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x40
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t ebx = (entry->ebx & 0xffffff00u) | (entry->eax & 0xffu);
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi = 0x16;
    uint32_t item;
    uint32_t label;
    uint32_t memory;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x24u, entry->edx);
    guard_record(&port, ebp - 0x3c, 0x51622c);
    port_set32(&port, ebp, -0x14u, 0x16);
    esi = port_u16(&port, 0, 0x4f88ac);
    port_set16(&port, ebp, -0x20u, 2);
    port_set16(&port, ebp, -0x1cu, (uint32_t)(int32_t)(int8_t)entry->eax * 0x16 + esi + 1);
    ecx = 0xdc;
    port_set32(&port, ebp, -0x18u, ecx);
    item = port_call_with(&port, 0x4ca000, 0x170, 2, ebx, ecx, esi, edi, ebp);
    if (item != 0)
    {
        edi = 1;
        port_set32(&port, ebp, -0x28u, item);
        port_set32(&port, ebp, -0x30u, 1);
        item = port_call_with(&port, 0x4b3100, item, 0, ebx, ecx, esi, edi, ebp);
        port_set32(&port, ebp, -0x30u, vertrix_lift_edx);
    }
    esi = item;
    call_frame(&port, 0x4adf20, item, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = sign16(port_u16(&port, ebp, -0x1cu));
    ecx = port_u16(&port, ebp, -0x18u);
    pushed[0] = port_u16(&port, ebp, -0x14u);
    call_frame(&port, 0x4b54d0, item, sign16(port_u16(&port, ebp, -0x20u)), ebx, ecx, esi, edi, ebp,
               pushed, 1);
    port_call_with(&port, 0x4ac7b0, item, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, item, 0x52, 9);
    port_set16(&port, item, 0x48, 0);
    port_set8(&port, item, 0x44, 0x10);
    port_set8(&port, item, 0x94, 1);
    port_set8(&port, item, 0x95, 0);
    port_set16(&port, item, 0xa8, 0);
    port_set16(&port, item, 0xaa, 0x27f);
    port_set16(&port, item, 0xae, 0x1df);
    edi = item;
    port_set16(&port, item, 0xac, port_u16(&port, 0, 0x4f88ac));
    port_set8(&port, item, 0x8e, 3);
    memory = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
    label = 0;
    if (memory != 0)
    {
        port_set32(&port, ebp, -0x28u, memory);
        port_set32(&port, ebp, -0x30u, 3);
        label = port_call_with(&port, 0x4b6350, memory, vertrix_lift_edx, 0, 3, esi, edi, ebp);
        port_set32(&port, ebp, -0x30u, 0);
    }
    esi = label;
    call_frame(&port, 0x4adf20, label, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)((int32_t)port_u32(&port, 0, 0x4f9c08) >> 24);
    call_frame(&port, 0x4b65d0, label, port_u32(&port, ebp, -0x24u), ebx, 0, esi, edi, ebp, zeros,
               3);
    port_call_with(&port, 0x4ac7b0, label, 2, ebx, 0, esi, edi, ebp);
    port_set8(&port, label, 0x44, 0x10);
    port_set8(&port, label, 0x4e, 0x32);
    port_set8(&port, label, 0x93, 0);
    port_set8(&port, label, 0x95, 4);
    pushed[0] = 1;
    pushed[1] = 1;
    call_frame(&port, 0x4b3210, item, label, 0, 0, esi, edi, ebp, pushed, 2);
    port_set16(&port, label, 0xa8, 0);
    port_set16(&port, label, 0xaa, 0x27f);
    port_set16(&port, label, 0xae, 0x1df);
    port_set8(&port, label, 0x8e, 3);
    port_set16(&port, label, 0xac, port_u16(&port, 0, 0x4f88ac));
    return port_return(&port, item, vertrix_lift_edx);
}

#include "choices.h"

/* The choice dialogs: four or five captions, their keys and positions, shown by 0x461180. */

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

static void copy_bytes(Port *port, uint32_t target, uint32_t source, uint32_t count)
{
    uint32_t index;
    for (index = 0; index < count; ++index)
    {
        port_set8(port, target, index, port_u8(port, source, index));
    }
}

/* The dialog's place: the screen 0x558c7c's half spare width past `width` and its height less
 * `height`, as words, after the sizes `width` and 0x1a. */
static void place_arguments(Port *port, uint32_t *args, uint32_t layout, uint32_t width,
                            uint32_t height)
{
    uint32_t screen = port_u32(port, 0, 0x558c7c);
    args[0] = layout;
    args[1] = width;
    args[2] = 0x1a;
    args[3] = (uint32_t)(int32_t)(int16_t)((port_u32(port, screen, 4) - width) >> 1);
    args[4] = (uint32_t)(int32_t)(int16_t)(port_u16(port, screen, 8) - height);
    args[5] = 0x1a;
}

/* The four caption dialog shared by 0x461360 and 0x4614c0: under the guard record `guard` the
 * four texts at ebp-0x50 (copied from `captions`, then set by 0x4ca280 to `text`), the keys of 8
 * bytes after the captions at `key_slot` with `words` words from `word_from` (a dword apart) at
 * `word_slot`, the positions of 8 bytes from `points` at `point_slot`, and the layout of 16 bytes
 * from `layout` at ebp-0x40 are shown (0x461180, 4 entries, `width` wide) and released
 * (0x473cd0). The slots are offsets below ebp. */
typedef struct
{
    uint32_t guard;
    uint32_t captions;
    uint32_t text[4];
    uint32_t key_slot;
    uint32_t word_slot;
    uint32_t word_from;
    uint32_t words;
    uint32_t points;
    uint32_t point_slot;
    uint32_t layout;
    uint32_t width;
} Four;

static uint32_t four_choices(const Four *four, PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t keys = four->captions + 0x10;
    uint32_t key_slot = ebp - four->key_slot;
    uint32_t point_slot = ebp - four->point_slot;
    uint32_t args[6];
    uint32_t index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x64, four->guard);
    port_set32(&port, ebp, -0x58u, 1);
    port_set32(&port, ebp, -0x2cu, 0x513e60);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x30u, ebp - 0x50);
    copy_bytes(&port, ebp - 0x50, four->captions, 0x10);
    port_call_with(&port, 0x4ca280, ebp - 0x50, four->text[0], 4, 3, keys, ebp - 0x40, ebp);
    for (index = 1; index < 4; ++index)
    {
        port_set32(&port, ebp, -0x28u, index);
        port_call_with(&port, 0x4ca280, ebp - 0x50 + index * 4, four->text[index], 4, 3, keys,
                       key_slot, ebp);
    }
    port_set32(&port, ebp, -0x28u, 4);
    copy_bytes(&port, key_slot, keys, 8);
    port_set32(&port, ebp, -0x58u, 3);
    for (index = 0; index < four->words; ++index)
    {
        port_set16(&port, ebp - four->word_slot, index * 2,
                   port_u16(&port, 0, four->word_from + index * 4));
    }
    copy_bytes(&port, point_slot, four->points, 8);
    copy_bytes(&port, ebp - 0x40, four->layout, 0x10);
    place_arguments(&port, args, ebp - 0x40, four->width, 0x8d);
    call_frame(&port, 0x461180, 4, ebp - 0x50, key_slot, point_slot, four->layout + 0x10, 0, ebp,
               args, 6);
    port_set32(&port, ebp, -0x58u, 0);
    port_call_with(&port, 0x473cd0, ebp - 0x50, 0, key_slot, point_slot, four->layout + 0x10, 0,
                   ebp);
    port_set32(&port, ebp, -0x58u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x64u), entry->edx);
}

/* Original 0x461360: the four choice dialog of the texts 0x50e2a0, 0x50e2a8, 0x50e2b1 and
 * 0x50e2b9 with the key words 0x4f7b44 to 0x4f7b50 over the keys, 0xab wide. */
uint32_t vertrix_port_choice_dialog_461360(PORT_SIGNATURE)
{
    static const Four four = {0x515834, 0x546798, {0x50e2a0, 0x50e2a8, 0x50e2b1, 0x50e2b9},
                              0x24,     0x24,     0x4f7b44,
                              4,        0x4fd490, 0x1c,
                              0x4fd498, 0xab};
    return four_choices(&four, calls, services, globals, entry);
}

/* Original 0x4614c0: the four choice dialog of the texts 0x50e2be, 0x50e2c6, 0x50e2d1 and
 * 0x50e2da with the key words 0x4f7b54 to 0x4f7b5c over all but the first key, 0xcc wide. */
uint32_t vertrix_port_choice_dialog_4614c0(PORT_SIGNATURE)
{
    static const Four four = {0x515850, 0x5467b0, {0x50e2be, 0x50e2c6, 0x50e2d1, 0x50e2da},
                              0x1c,     0x1a,     0x4f7b54,
                              3,        0x4fd4a8, 0x24,
                              0x4fd4b0, 0xcc};
    return four_choices(&four, calls, services, globals, entry);
}

/* Original 0x461610: the five choice dialog: under the guard record 0x51586c the five texts at
 * ebp-0x60 (copied from 0x5467c8, set to 0x50e2e1, 0x50e2ea, 0x50e2f5, 0x50e2fe and 0x50e306),
 * the keys of 10 bytes from 0x5467dc with the word 0x4f7b64 second, the positions of 10 bytes
 * from 0x4fd4c0 with the words 0x4f7b60, 0x4f7b68 and 0x4f7b6c after, and the layout of 20 bytes
 * from 0x4fd4cc are shown (0x461180, 5 entries, 0xcc wide) and released (0x418550). */
uint32_t vertrix_port_choice_dialog_461610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x78
    };
    static const uint32_t text[5] = {0x50e2e1, 0x50e2ea, 0x50e2f5, 0x50e2fe, 0x50e306};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t args[6];
    uint32_t index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x4c, 0x51586c);
    port_set32(&port, ebp, -0x40u, 1);
    port_set32(&port, ebp, -0x34u, 0x513e60);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x38u, ebp - 0x60);
    copy_bytes(&port, ebp - 0x60, 0x5467c8, 0x14);
    port_call_with(&port, 0x4ca280, ebp - 0x60, text[0], 4, 3, 0x5467dc, ebp - 0x4c, ebp);
    port_set32(&port, ebp, -0x30u, 1);
    port_call_with(&port, 0x4ca280, ebp - 0x5c, text[1], 4, 3, 5, ebp - 0x4c, ebp);
    for (index = 2; index < 5; ++index)
    {
        port_set32(&port, ebp, -0x30u, index);
        port_call_with(&port, 0x4ca280, ebp - 0x60 + index * 4, text[index], 4, 3, 5, ebp - 0x20,
                       ebp);
    }
    port_set32(&port, ebp, -0x30u, 5);
    copy_bytes(&port, ebp - 0x20, 0x5467dc, 10);
    port_set32(&port, ebp, -0x40u, 3);
    port_set16(&port, ebp, -0x1eu, port_u16(&port, 0, 0x4f7b64));
    copy_bytes(&port, ebp - 0x2c, 0x4fd4c0, 10);
    port_set16(&port, ebp, -0x1cu, port_u16(&port, 0, 0x4f7b60));
    port_set16(&port, ebp, -0x1au, port_u16(&port, 0, 0x4f7b68));
    port_set16(&port, ebp, -0x18u, port_u16(&port, 0, 0x4f7b6c));
    copy_bytes(&port, ebp - 0x74, 0x4fd4cc, 0x14);
    place_arguments(&port, args, ebp - 0x74, 0xcc, 0xa6);
    call_frame(&port, 0x461180, 5, ebp - 0x60, ebp - 0x20, ebp - 0x2c, 0x4fd4e0, ebp - 0x60, ebp,
               args, 6);
    port_set32(&port, ebp, -0x40u, 0);
    port_call_with(&port, 0x418550, ebp - 0x60, 0, ebp - 0x20, ebp - 0x2c, 0x4fd4e0, ebp - 0x60,
                   ebp);
    port_set32(&port, ebp, -0x40u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x4cu), entry->edx);
}

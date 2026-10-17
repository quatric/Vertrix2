#include "port_rtlheadsanims.h"

/* Loads a set's head images and animations (the sets of 0x53969c: one per level, 19 in all). */

enum
{
    /* The routine's frame under its return slot: a settings list, two paths and two strings
     * that its callees fill by address. */
    BELOW = 0x27c,
    LIST = 0x70,
    FIRST_VALUE = 0x44,
    SECOND_VALUE = 0x40,
    IMAGE_PATH = 0x174,
    MASK_PATH = 0x278,

    /* Per set: the count of heads plus one, a dword table index, and rows of 0xf0 bytes in the
     * name tables (heads start at +4) and the tables passed on with each head. */
    SET_COUNTS = 0x53969c,
    SET_HEAD_KIND = 0x5347f0,
    SET_ROW_BYTES = 0xf0,
    HEAD_IMAGES = 0x534f5c,
    HEAD_MASKS = 0x53612c,
    HEAD_FIRSTS = 0x537300,
    HEAD_SECONDS = 0x5384d0,
    /* Per set: the animation count, and names in rows 0x4c bytes apart from 0x534920. */
    SET_ANIMATION_COUNTS = 0x534f10,
    ANIMATION_NAMES = 0x534920,
    ANIMATION_NAME_STRIDE = 0x4c,
    /* The animation banks, 0x1c bytes per set. */
    BANKS = 0x544d7c,
    BANK_BYTES = 0x1c,

    NO_HEAD = 0x50dd31,
    HEADS_DIRECTORY = 0x4fc9c8,
    ANIM_DIRECTORY = 0x4fd100,

    LIST_INIT = 0x489f90,
    LIST_DONE = 0x489fa0,
    LIST_LOAD = 0x48a050,
    LIST_COUNT = 0x48a2e0,
    LIST_CLEAR = 0x48a2d0,
    LIST_VALUE = 0x48a300,
    HEADS_ALLOCATE = 0x45ea60,
    HEAD_STORE = 0x45e9e0,
    BANK_ALLOCATE = 0x45e950,
    BANK_STORE = 0x45e990,
    STRING_COMPARE = 0x4ccfe0,
    STRING_FREE = 0x4ca210,
    TO_INTEGER = 0x4d6710,
    PATH_JOIN = 0x45f540,
    IMAGE_OPEN = 0x423dc0,
    IMAGE_FREE = 0x478d80
};

static void path_join(Port *port, uint32_t to, uint32_t directory, uint32_t name)
{
    port_call(port, PATH_JOIN, to, directory, name, 0);
}

/* The number in the list's line, through the string `value`. 0x48a300 and 0x4d6710 get the ecx
 * and edx the original leaves (0 or 1, and 0 or what 0x48a300 left in edx). */
static uint32_t list_number(Port *port, uint32_t list, uint32_t value, uint32_t line, uint32_t ecx,
                            int keep_edx)
{
    const uint32_t text = port_call(port, LIST_VALUE, list, value, line, ecx);
    const uint32_t edx = keep_edx ? vertrix_lift_edx : 0;
    const uint32_t number = port_call(port, TO_INTEGER, port_u32(port, text, 0), edx, 1, ecx);
    port_call(port, STRING_FREE, value, 0, 0, 0);
    return number;
}

/* Original 0x41e310 (eax = the set): with more than one entry in 0x53969c, allocates the heads
 * (0x45ea60) and opens each named one from .\IMAGE\HEADS\ with its mask (0x423dc0), stores it
 * (0x45e9e0) and frees the image. Then for each of the set's animations reads .\ANIM\<name> as a
 * list of number pairs into a bank (0x45e950, 0x45e990). Keeps the caller's edx; the original's
 * try/finally frame is left out. */
uint32_t vertrix_port_heads_anims_load_41e310(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t list = frame - LIST;
    const uint32_t image_path = frame - IMAGE_PATH;
    const uint32_t mask_path = frame - MASK_PATH;
    const uint32_t set = entry->eax;

    port_call(&port, LIST_INIT, list, 0, 0, 0);
    const uint32_t count = port_u32(&port, SET_COUNTS, set * 4);
    if (count <= 1)
    {
        port_call(&port, LIST_DONE, list, 0, 0, 0);
        return port_return(&port, 0, entry->edx);
    }
    const uint32_t heads = count - 1;
    port_call(&port, HEADS_ALLOCATE, set, heads, 0, 0);
    const uint32_t row = set * SET_ROW_BYTES;
    for (uint32_t head = 0; head < heads && !port.env.failed; head++)
    {
        const uint32_t slot = row + head * 4;
        if (port_call(&port, STRING_COMPARE, port_u32(&port, HEAD_IMAGES + 4, slot), NO_HEAD, 0,
                      0) == 0)
        {
            continue;
        }
        path_join(&port, image_path, HEADS_DIRECTORY, port_u32(&port, HEAD_IMAGES + 4, slot));
        path_join(&port, mask_path, HEADS_DIRECTORY, port_u32(&port, HEAD_MASKS + 4, slot));
        const uint32_t image = port_call(&port, IMAGE_OPEN, image_path, mask_path,
                                         port_u32(&port, SET_HEAD_KIND, set * 4), 0);
        if (image != 0)
        {
            const uint32_t second = port_u32(&port, HEAD_SECONDS, slot);
            port_call_stack(&port, HEAD_STORE, set, head, image, port_u32(&port, HEAD_FIRSTS, slot),
                            &second, 1);
            port_call(&port, IMAGE_FREE, image, 0, 0, 0);
        }
    }

    const uint32_t animations = port_u32(&port, SET_ANIMATION_COUNTS, set * 4);
    const uint32_t bank = BANKS + set * BANK_BYTES;
    uint32_t name = ANIMATION_NAMES + set * 4;
    for (uint32_t animation = 0; animation < animations && !port.env.failed; animation++)
    {
        path_join(&port, image_path, ANIM_DIRECTORY, port_u32(&port, name, 0));
        port_call(&port, LIST_LOAD, list, image_path, 0, 0);
        port_call(&port, BANK_ALLOCATE, set, animation, port_call(&port, LIST_COUNT, list, 0, 0, 0),
                  0);
        for (uint32_t line = 0;
             line < port_call(&port, LIST_COUNT, list, 0, 0, 0) && !port.env.failed; line++)
        {
            const uint32_t pair[2] = {
                list_number(&port, list, frame - FIRST_VALUE, line, 0, 0),
                list_number(&port, list, frame - SECOND_VALUE, line, 1, 1),
            };
            port_call_stack(&port, BANK_STORE, set, animation, line, bank, pair, 2);
        }
        port_call(&port, LIST_CLEAR, list, 0, 0, 0);
        name += ANIMATION_NAME_STRIDE;
    }
    port_call(&port, LIST_DONE, list, 0, 0, 0);
    return port_return(&port, 0, entry->edx);
}

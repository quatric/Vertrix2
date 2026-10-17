#include "rtlactornumbers.h"

/* Sets a number actor's value and shows it as text: plain or zero-padded to a width, with 0 shown
 * as nothing unless the actor asks for it. */

enum
{
    /* The routine's frame under its return slot: its two strings are passed by address. */
    BELOW = 0x30,
    TEXT = 0x18,
    PADDED = 0x14,

    ACTOR_COLOR = 0x160,
    ACTOR_X = 0x162,
    ACTOR_Y = 0x164,
    ACTOR_WIDTH = 0x166,
    ACTOR_HEIGHT = 0x168,
    ACTOR_NUMBER = 0x180,
    ACTOR_ZERO_PADDED = 0x184,
    ACTOR_DIGITS = 0x188,
    ACTOR_SHOW_ZERO = 0x190,

    /* A Delphi string's length, before its characters. */
    STRING_LENGTH = -8,

    FORMAT_UNSIGNED = 0x5110a8,
    FORMAT_UNSIGNED_PADDED = 0x5110a2,
    EMPTY = 0x5110a5,
    ZERO = 0x5110a6,
    EMPTY_FOR_ZERO = 0x5110ab,

    /* The exception handler the original's frame names; it is still in ecx at the second print. */
    HANDLER = 0x4ec1ec,

    STRING_INIT = 0x4ca070,
    STRING_FREE = 0x4ca210,
    STRING_ASSIGN = 0x4ca370,
    STRING_APPEND = 0x4ca600,
    STRING_CONCAT = 0x4ca650,
    PRINT = 0x4cdfb0,
    SET_TEXT = 0x4b65d0
};

/* 0x4cdfb0: Format(text, format, number), cdecl. Its callee reads ecx, so the original's ecx is
 * handed over. */
static void print(Port *port, uint32_t text, uint32_t format, uint32_t number, uint32_t ecx)
{
    const uint32_t stack[3] = {text, format, number};
    port_call_stack(port, PRINT, 0, 0, 0, ecx, stack, 3);
}

static uint32_t signed_word(Port *port, uint32_t actor, uint32_t offset)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, actor, offset);
}

/* Original 0x4b58a0 (eax = actor, edx = number): stores the number at +0x180 and formats it with
 * %u. With +0x184 set, the digits are padded with zeros to +0x188 characters. A 0 is shown as no
 * text unless +0x190 is set. The text goes to 0x4b65d0 with the actor's colour (+0x160, a signed
 * byte) and rectangle (+0x162..+0x168, signed words). The original's try/finally frame is left
 * out. */
uint32_t vertrix_port_actor_set_number_text_4b58a0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t text = frame - TEXT;
    const uint32_t padded = frame - PADDED;
    const uint32_t actor = entry->eax;

    port_call(&port, STRING_INIT, text, 0, 0, 0);
    port_set32(&port, actor, ACTOR_NUMBER, entry->edx);
    if (port_u32(&port, actor, ACTOR_ZERO_PADDED) != 1)
    {
        print(&port, text, FORMAT_UNSIGNED, port_u32(&port, actor, ACTOR_NUMBER),
              port_u32(&port, actor, ACTOR_NUMBER));
    }
    else
    {
        port_call(&port, STRING_INIT, padded, 0, 0, 0);
        print(&port, padded, FORMAT_UNSIGNED_PADDED, port_u32(&port, actor, ACTOR_NUMBER), HANDLER);
        port_call(&port, STRING_ASSIGN, text, EMPTY, 0, 0);
        const uint32_t length = port_u32(&port, port_u32(&port, padded, 0), STRING_LENGTH);
        for (uint32_t digits = port_u32(&port, actor, ACTOR_DIGITS);
             digits > length && !port.env.failed; digits--)
        {
            port_call(&port, STRING_APPEND, text, ZERO, 0, 0);
        }
        port_call(&port, STRING_CONCAT, text, padded, 0, 0);
        port_call(&port, STRING_FREE, padded, 0, 0, 0);
    }
    if (port_u32(&port, actor, ACTOR_SHOW_ZERO) == 0 && port_u32(&port, actor, ACTOR_NUMBER) == 0)
    {
        port_call(&port, STRING_ASSIGN, text, EMPTY_FOR_ZERO, 0, 0);
    }
    const uint32_t rectangle[3] = {signed_word(&port, actor, ACTOR_Y),
                                   signed_word(&port, actor, ACTOR_WIDTH),
                                   signed_word(&port, actor, ACTOR_HEIGHT)};
    port_call_stack(&port, SET_TEXT, actor, port_u32(&port, text, 0),
                    (uint32_t)(int32_t)(int8_t)port_u8(&port, actor, ACTOR_COLOR),
                    signed_word(&port, actor, ACTOR_X), rectangle, 3);
    port_call(&port, STRING_FREE, text, 0, 0, 0);
    return port_return(&port, 0, 0);
}

#include "rtltextfieldkeys.h"

/* The text fields' key loops. Each reads the key queue until it is empty: editing keys move the
 * cursor or delete, Enter and Escape close the field (with the field's change handler), and a
 * character is inserted when the field takes it. Rejecting a character throws (0x4cda10), which the
 * loop's own try block catches; the lifted runtime returns from the throw, and the loop goes on. */

enum
{
    BELOW = 0x3c, /* the locals, down to the exception record at ebp - 0x38 */

    KEYS = 0x54d640,
    KEY_READ = 0x476530,
    KEY_FLUSH = 0x4766b0,
    KEY_ESCAPE = 1,
    KEY_ENTER = 0x1c,
    KEY_PAD_ENTER = 0x56,
    KEY_BACKSPACE = 0xe,
    KEY_HOME = 0x5c,
    KEY_LEFT = 0x5f,
    KEY_RIGHT = 0x60,
    KEY_END = 0x61,
    KEY_DELETE = 0x65,

    FIELD_KIND = 0,
    FIELD_STATE = 0x52,
    FIELD_OWNER = 0x160,
    OWNER_TEXT = 0x15c,
    FIELD_ON_CHANGE = 0x184,
    NUMBER_FIELD = 0x1f5,
    STATE_CLOSED = 9,

    STRING_ASSIGN = 0x4ca280,
    STRING_SET = 0x4ca370,
    STRING_RELEASE = 0x4ca210,
    STRING_EQUAL = 0x4ccfe0,
    STRING_OF_CHAR = 0x4cda90,
    THROW = 0x4cda10,

    FIELD_FOCUS = 0x4b4510,
    FIELD_HANDLER = 0x4ac8f0,
    FIELD_CLOSE = 0x4b4c90,
    FIELD_COMMIT = 0x4b4cd0,
    FIELD_LEFT = 0x4b4600,
    FIELD_RIGHT = 0x4b4610,
    FIELD_HOME = 0x4b4620,
    FIELD_END = 0x4b4630,
    FIELD_FULL = 0x4b4660,
    FIELD_INSERT = 0x4b4790,
    FIELD_BACKSPACE = 0x4b4950,
    FIELD_DELETE = 0x4b4af0,
    FIELD_TAKES = 0x4b4cb0,
    CURSOR = 0x5588f8,
    CURSOR_HIDE = 0x477ed0,

    NO_AT_SIGN = 0x532b3c,
    MENU = 0x532d88,
    MENU_CLOSE = 0x417260,
    MENU_REFRESH = 0x417290,
    KEY_HANDLER = 0x532a4c,
    MENU_KEY_HANDLER = 0x4f7ba0
};

/* The locals each loop keeps at its own offsets below ebp: the character read, the field's text
 * copied for a key, the text copied for a character and the character as a string. */
typedef struct
{
    uint32_t event, text, char_text, char_string;
} Locals;

typedef struct
{
    Port *port;
    uint32_t field;
    uint32_t frame;
    Locals at;
    /* What the last callee left in edx, which the throw and the callees that do not take edx see.
     */
    uint32_t edx;
} Field;

static uint32_t call(Field *f, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx)
{
    const uint32_t result = port_call(f->port, target, eax, edx, ebx, f->field);
    f->edx = vertrix_lift_edx;
    return result;
}

/* A callee that takes the field alone. */
static uint32_t on_field(Field *f, uint32_t target)
{
    return call(f, target, f->field, f->edx, 0);
}

static uint32_t local(Field *f, uint32_t offset)
{
    return f->frame - offset;
}

static uint32_t text_slot(Field *f)
{
    return port_u32(f->port, f->field, FIELD_OWNER) + OWNER_TEXT;
}

static uint32_t text(Field *f)
{
    return port_u32(f->port, text_slot(f), 0);
}

static uint32_t event(Field *f)
{
    return port_u32(f->port, local(f, f->at.event), 0);
}

/* The field's change handler, a procedure variable: it sees the text, the field, ebx and ecx the
 * field. */
static void on_change(Field *f, uint32_t ebx)
{
    const uint32_t handler = port_u32(f->port, f->field, FIELD_ON_CHANGE);
    if (handler != 0)
    {
        call(f, handler, text(f), f->field, ebx);
    }
}

static void throw_reject(Field *f)
{
    port_call(f->port, THROW, 0, f->edx, 0, f->field);
}

/* The next key: 0 for a character (or none). */
static uint32_t read_key(Field *f)
{
    return call(f, KEY_READ, KEYS, local(f, f->at.event), 0) & 0xffff;
}

/* Copies the field's text for a character and makes the character a string; whether the field
 * might take it (no '@' where they are barred, and the field's own test unless it is a space). */
static int character_allowed(Field *f)
{
    call(f, STRING_ASSIGN, local(f, f->at.char_text), text(f), 0);
    call(f, STRING_OF_CHAR, local(f, f->at.char_string), event(f) & 0xff, 1);
    const uint32_t c = event(f);
    if (port_u32(f->port, NO_AT_SIGN, 0) == 0 && c == '@')
    {
        return 0;
    }
    return c == ' ' || call(f, FIELD_TAKES, f->field, c & 0xff, 1) != 0;
}

/* Inserts the character: the cursor moves right when it went in. */
static void insert(Field *f)
{
    if (call(f, FIELD_INSERT, f->field, port_u32(f->port, local(f, f->at.char_string), 0), 1) == 1)
    {
        on_field(f, FIELD_RIGHT);
    }
}

/* The editing keys; anything else is ignored. */
static void edit_key(Field *f, uint32_t key)
{
    switch (key)
    {
        case KEY_LEFT:
            on_field(f, FIELD_LEFT);
            break;
        case KEY_RIGHT:
            on_field(f, FIELD_RIGHT);
            break;
        case KEY_HOME:
            on_field(f, FIELD_HOME);
            break;
        case KEY_END:
            on_field(f, FIELD_END);
            break;
        case KEY_DELETE:
            on_field(f, FIELD_DELETE);
            break;
        case KEY_BACKSPACE:
            if (on_field(f, FIELD_BACKSPACE) == 1)
            {
                on_field(f, FIELD_LEFT);
            }
            break;
        default:
            break;
    }
    call(f, STRING_RELEASE, local(f, f->at.text), 0, 0);
}

static void open_field(Field *f, Port *port, const LiftEntry *entry, Locals at)
{
    f->port = port;
    f->field = entry->eax;
    f->frame = entry->esp - 4;
    f->at = at;
    f->edx = entry->edx;
    port_set32(port, f->frame, 0, entry->ebp);
}

/* Closes the field and hands the keys back: the cursor hidden, the field unfocused, its handler
 * 0x4ac8f0 set and its state closed. */
static void close_field(Field *f, uint32_t handler)
{
    call(f, CURSOR_HIDE, CURSOR, f->edx, 0);
    call(f, FIELD_FOCUS, f->field, 0, 0);
    call(f, FIELD_HANDLER, f->field, handler, 0);
    port_set8(f->port, f->field, FIELD_STATE, STATE_CLOSED);
}

static void finish(Field *f)
{
    call(f, KEY_FLUSH, KEYS, 0, 0);
    call(f, STRING_RELEASE, local(f, f->at.text), 0, 0);
}

/* Original 0x444e00 (the name field). Enter commits the text unless it is empty; a number field
 * takes digits only. Returns the caller's exception chain, as the original leaves it. */
uint32_t vertrix_port_text_field_key_handler_444e00(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    Field f;
    open_field(&f, &port, entry, (Locals){0x1c, 0x24, 0x18, 0x20});
    for (;;)
    {
        const uint32_t key = read_key(&f);
        if (key == 0)
        {
            if (event(&f) == 0 || port.env.failed)
            {
                return port_return(&port, port.env.chain, entry->edx);
            }
            if (character_allowed(&f) && !(port_u32(&port, f.field, FIELD_KIND) == NUMBER_FIELD &&
                                           (event(&f) < '0' || event(&f) > '9')))
            {
                insert(&f);
            }
            throw_reject(&f);
            continue;
        }
        call(&f, STRING_ASSIGN, local(&f, f.at.text), text(&f), key);
        if (key == KEY_ESCAPE)
        {
            close_field(&f, 0x444c80);
            on_field(&f, FIELD_CLOSE);
            finish(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        if (key == KEY_ENTER || key == KEY_PAD_ENTER)
        {
            close_field(&f, 0x444c80);
            if (call(&f, STRING_EQUAL, port_u32(&port, local(&f, f.at.text), 0), 0x50e16a, 0) == 0)
            {
                on_field(&f, FIELD_COMMIT);
            }
            on_change(&f, port_u32(&port, f.field, FIELD_ON_CHANGE));
            finish(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        edit_key(&f, key);
    }
}

/* Original 0x445350 (the password field). Enter clears the shown text to 0x50e16b; when a character
 * does not fit, a full field (0x4b4660) runs the change handler, starts over with 0x50e16c and
 * inserts it there. */
uint32_t vertrix_port_text_field_key_handler_445350(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    Field f;
    open_field(&f, &port, entry, (Locals){0x20, 0x1c, 0x18, 0x24});
    for (;;)
    {
        const uint32_t key = read_key(&f);
        if (key == 0)
        {
            if (event(&f) == 0 || port.env.failed)
            {
                return port_return(&port, port.env.chain, entry->edx);
            }
            if (character_allowed(&f))
            {
                const uint32_t string = port_u32(&port, local(&f, f.at.char_string), 0);
                if (call(&f, FIELD_INSERT, f.field, string, 1) == 1)
                {
                    on_field(&f, FIELD_RIGHT);
                }
                else if (on_field(&f, FIELD_FULL) == 1)
                {
                    on_change(&f, port_u32(&port, f.field, FIELD_ON_CHANGE));
                    call(&f, STRING_SET, text_slot(&f), 0x50e16c, 1);
                    on_field(&f, FIELD_HOME);
                    insert(&f);
                }
            }
            throw_reject(&f);
            continue;
        }
        call(&f, STRING_ASSIGN, local(&f, f.at.text), text(&f), key);
        if (key == KEY_ESCAPE)
        {
            close_field(&f, 0x4451d0);
            on_field(&f, FIELD_CLOSE);
            finish(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        if (key == KEY_ENTER || key == KEY_PAD_ENTER)
        {
            close_field(&f, 0x4451d0);
            on_change(&f, key);
            call(&f, STRING_SET, text_slot(&f), 0x50e16b, key);
            finish(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        edit_key(&f, key);
    }
}

/* The menu's close: the field unfocused, the menu closed and redrawn, its key handler back. */
static void close_menu_field(Field *f)
{
    call(f, FIELD_FOCUS, f->field, 0, 0);
    const uint32_t menu = port_u32(f->port, MENU, 0);
    call(f, MENU_CLOSE, menu, f->edx, 0);
    call(f, MENU_REFRESH, port_u32(f->port, MENU, 0), f->edx, 0);
    port_set32(f->port, KEY_HANDLER, 0, port_u32(f->port, MENU_KEY_HANDLER, 0));
    call(f, STRING_RELEASE, local(f, f->at.text), 0, 0);
}

/* Original 0x45c9a0 (a menu's text field). Escape commits the field and closes the menu; Enter
 * commits it unless empty and stores the text first. */
uint32_t vertrix_port_text_field_key_input_45c9a0(PORT_SIGNATURE)
{
    Port port;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    Field f;
    open_field(&f, &port, entry, (Locals){0x24, 0x20, 0x1c, 0x18});
    for (;;)
    {
        const uint32_t key = read_key(&f);
        if (key == 0)
        {
            if (event(&f) == 0 || port.env.failed)
            {
                return port_return(&port, port.env.chain, entry->edx);
            }
            if (character_allowed(&f))
            {
                insert(&f);
            }
            throw_reject(&f);
            continue;
        }
        call(&f, STRING_ASSIGN, local(&f, f.at.text), text(&f), key);
        if (key == KEY_ESCAPE)
        {
            on_field(&f, FIELD_COMMIT);
            on_change(&f, key);
            close_menu_field(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        if (key == KEY_ENTER || key == KEY_PAD_ENTER)
        {
            if (call(&f, STRING_EQUAL, port_u32(&port, local(&f, f.at.text), 0), 0x50e22e, key) ==
                0)
            {
                on_field(&f, FIELD_COMMIT);
            }
            call(&f, STRING_SET, text_slot(&f), port_u32(&port, local(&f, f.at.text), 0), key);
            on_change(&f, port_u32(&port, f.field, FIELD_ON_CHANGE));
            close_menu_field(&f);
            return port_return(&port, port.env.chain, entry->edx);
        }
        edit_key(&f, key);
    }
}

#include "port_rtlgamedialogs.h"

/* The game settings dialog. */

typedef struct
{
    Port *port;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Dialog;

/* A call (with count stack arguments, nearest first) of the tracked registers. */
static void dialog_call(Dialog *d, uint32_t target, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = d->esi;
    vertrix_lift_in_edi = d->edi;
    vertrix_lift_in_ebp = d->ebp;
    d->eax =
        lift_call_arguments(&d->port->env, target, d->eax, d->edx, d->ebx, d->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    d->edx = vertrix_lift_edx;
}

static uint32_t local(Dialog *d, uint32_t offset)
{
    return port_u32(d->port, d->ebp, offset);
}

/* The word at ebp + offset, sign-extended. */
static uint32_t word(Dialog *d, uint32_t offset)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(d->port, d->ebp, offset);
}

/* The byte at address, sign-extended (the original's dword read shifted down 24). */
static uint32_t colour(Dialog *d, uint32_t address)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(d->port, 0, address);
}

/* A text (0x460c50) of the string at text, eax, in the dialog's box (left esi, top edi) at the
 * row: 26 high, at 0xe0 across. */
static void label(Dialog *d, uint32_t text, uint32_t row)
{
    uint32_t args[11];
    args[0] = row;
    args[1] = 0x18a;
    args[2] = 0xb4;
    args[3] = d->esi;
    args[4] = d->edi;
    args[5] = 5;
    args[6] = 0;
    args[7] = 1;
    args[8] = colour(d, 0x4f9bf8);
    args[9] = 0x10;
    args[10] = 1;
    d->ebx = 0x1a;
    d->edx = 0xe0;
    d->eax = text;
    d->ecx = d->esi;
    dialog_call(d, 0x460c50, args, 11);
}

/* A value chooser (0x460fa0) at eax, edx: its text slot, its value, the step, the lowest and
 * highest, the formatter, its two handlers. */
static void chooser(Dialog *d, uint32_t eax, uint32_t edx, uint32_t text, uint32_t value,
                    uint32_t step, uint32_t low, uint32_t high, uint32_t format, uint32_t changed,
                    uint32_t shown)
{
    uint32_t args[17];
    args[0] = text;
    args[1] = value;
    args[2] = step;
    args[3] = low;
    args[4] = high;
    args[5] = format;
    args[6] = changed;
    args[7] = shown;
    args[8] = colour(d, 0x4f9bfa);
    args[9] = 0x10;
    args[10] = 0;
    args[11] = 1;
    args[12] = 0x18a;
    args[13] = 0xb4;
    args[14] = d->esi;
    args[15] = d->edi;
    args[16] = 0;
    d->ecx = 0x1a;
    d->ebx = 0xab;
    d->eax = eax;
    d->edx = edx;
    dialog_call(d, 0x460fa0, args, 17);
}

/* A setting's name (0x415ed0 of the setting at value in its table) readied for the text at
 * ebp - slot: edx the name, eax the text. */
static void setting_text(Dialog *d, uint32_t value, uint32_t table, uint32_t slot)
{
    d->eax = port_u32(d->port, 0, value);
    d->edx = table;
    dialog_call(d, 0x415ed0, NULL, 0);
    d->edx = d->eax;
    d->eax = d->ebp - slot;
}

/* The rows moved 25 down (the words at ebp - 0x24 and - 0x28). */
static void next_row(Dialog *d)
{
    port_set16(d->port, d->ebp, -0x24u, local(d, -0x24u) + 0x19);
    port_set16(d->port, d->ebp, -0x28u, local(d, -0x28u) + 0x19);
}

/* Original 0x461930 (guarded 0x5158a4): the game settings dialog. Its five value texts
 * (0x4ca070) and labels (DIFFICULTY, START SPEED, ALL BONUS, LEVEL LIMIT, COLOR LEVEL; 0x4ca280)
 * made; the settings 0x532b4c and 0x532b64 kept at 0x532b50/0x532b68 and each setting's text
 * (0x415ed0 of 0x532b50, 0x532b60, 0x532b5c, 0x532b58 and 0x532b54 by their tables) set
 * (0x4ca370). A 394 by 180 box centred on the screen 0x558c7c (0x460a40) titled GAME (0x460c50)
 * with a rule (0x460ad0); a label and chooser (0x460c50, 0x460fa0) a row of 25 for each setting;
 * a rule, the RETURN button (0x460b60) and another rule. A new actor (0x4ca000 of 0x15c, made by
 * 0x4abd70) handed 0x45c6e0 and added to 0x54671c (0x4b5e70); 0x532a48 cleared; the frame ended
 * (0x4cda10). eax the restored chain, edx kept. */
uint32_t vertrix_port_game_dialog_461930(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x84
    };
    Port port;
    uint8_t stack[BELOW + 8];
    Dialog d;
    uint32_t record;
    uint32_t screen;
    uint32_t left;
    uint32_t height;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    d.port = &port;
    d.ebp = entry->esp - 4;
    record = d.ebp - 0x80;
    port_set32(&port, d.ebp, 0, entry->ebp);
    port_set32(&port, d.ebp, -4u, entry->ebx);
    port_set32(&port, d.ebp, -8u, entry->ecx);
    port_set32(&port, d.ebp, -0xcu, entry->edx);
    port_set32(&port, d.ebp, -0x10u, entry->esi);
    port_set32(&port, d.ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    d.edx = 0x4ec1ec;
    d.ecx = 0x5158a4;
    d.esi = 1;
    d.edi = 2;
    d.ebx = 0;
    port_set32(&port, d.ebp, -0x7cu, d.edx);
    port_set32(&port, d.ebp, -0x78u, d.ecx);
    port_set32(&port, d.ebp, -0x74u, d.ebx);
    d.eax = d.ebp - 0x6c;
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x68;
    d.edx = 4;
    d.ecx = 5;
    d.ebx = 6;
    port_set32(&port, d.ebp, -0x74u, d.esi);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x64;
    port_set32(&port, d.ebp, -0x74u, d.edi);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.esi = 7;
    port_set32(&port, d.ebp, -0x74u, 3);
    d.eax = d.ebp - 0x60;
    d.edi = 8;
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x5c;
    port_set32(&port, d.ebp, -0x74u, d.edx);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.edx = 0x50e332;
    d.eax = d.ebp - 0x58;
    port_set32(&port, d.ebp, -0x74u, d.ecx);
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e33d;
    d.eax = d.ebp - 0x54;
    d.ecx = 3;
    port_set32(&port, d.ebp, -0x74u, d.ebx);
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e349;
    d.eax = d.ebp - 0x50;
    port_set32(&port, d.ebp, -0x74u, d.esi);
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e355;
    d.eax = d.ebp - 0x4c;
    port_set32(&port, d.ebp, -0x74u, d.edi);
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e361;
    port_set32(&port, d.ebp, -0x74u, 9);
    d.eax = d.ebp - 0x48;
    d.ebx = 0x4f8128;
    dialog_call(&d, 0x4ca280, NULL, 0);
    port_set32(&port, d.ebp, -0x74u, 0xa);
    port_set32(&port, 0, 0x532b50, port_u32(&port, 0, 0x532b4c));
    port_set32(&port, 0, 0x532b68, port_u32(&port, 0, 0x532b64));
    setting_text(&d, 0x532b50, 0x532afc, 0x5c);
    d.ecx = 2;
    d.ebx = 0x4f8120;
    dialog_call(&d, 0x4ca370, NULL, 0);
    setting_text(&d, 0x532b60, 0x532af4, 0x60);
    dialog_call(&d, 0x4ca370, NULL, 0);
    d.ecx = 2;
    d.ebx = 0x4f8118;
    setting_text(&d, 0x532b5c, 0x532aec, 0x64);
    d.ecx = 0xa;
    d.ebx = 0x4f80f0;
    dialog_call(&d, 0x4ca370, NULL, 0);
    setting_text(&d, 0x532b58, 0x532ac4, 0x68);
    d.ecx = 3;
    d.ebx = 0x4f80e4;
    dialog_call(&d, 0x4ca370, NULL, 0);
    setting_text(&d, 0x532b54, 0x532ab8, 0x6c);
    dialog_call(&d, 0x4ca370, NULL, 0);
    screen = port_u32(&port, 0, 0x558c7c);
    height = port_u16(&port, screen, 8);
    left = (port_u32(&port, screen, 4) - 0x18a) >> 1;
    port_set16(&port, d.ebp, -0x18u, height - 0xc1);
    port_set16(&port, d.ebp, -0x30u, left + 0xdf);
    port_set16(&port, d.ebp, -0x20u, height - 0x42);
    port_set16(&port, d.ebp, -0x2cu, left + 0x85);
    port_set16(&port, d.ebp, -0x1cu, left + 0x105);
    d.esi = (uint32_t)(int32_t)(int16_t)left;
    d.edi = (uint32_t)(int32_t)(int16_t)(height - 0xdc);
    {
        uint32_t box[5] = {0x18a, 0xb4, d.esi, d.edi, 1};
        d.ecx = (uint32_t)(int32_t)(int16_t)(height - 0xdc + 9);
        d.ebx = d.esi;
        d.edx = 0x11;
        d.eax = 0x18a;
        dialog_call(&d, 0x460a40, box, 5);
    }
    {
        uint32_t title[11] = {d.edi, 0x18a, 0xb4, d.esi, d.edi, 0, 1, 1, colour(&d, 0x4f9bf8),
                              0x10,  1};
        d.ebx = 0x1a;
        d.edx = 0x18a;
        d.ecx = d.esi;
        d.eax = 0x50e36d;
        dialog_call(&d, 0x460c50, title, 11);
    }
    {
        uint32_t rule[5] = {0x18a, 0xb4, d.esi, d.edi, 1};
        port_set32(&port, d.ebp, -0x38u, word(&d, -0x18u));
        d.ecx = local(&d, -0x38u);
        d.ebx = d.esi;
        d.edx = 0x7e;
        d.eax = 0xe0;
        dialog_call(&d, 0x460ad0, rule, 5);
    }
    label(&d, local(&d, -0x58u), local(&d, -0x38u));
    port_set32(&port, d.ebp, -0x34u, word(&d, -0x30u));
    chooser(&d, local(&d, -0x34u), local(&d, -0x38u), local(&d, -0x6cu), 0x532ab8, 3, 0, 2,
            0x416b30, 0, 0x447f40);
    port_set16(&port, d.ebp, -0x24u, local(&d, -0x18u) + 0x19);
    port_set16(&port, d.ebp, -0x28u, local(&d, -0x18u) + 0x19);
    port_set32(&port, d.ebp, -0x3cu, word(&d, -0x24u));
    label(&d, local(&d, -0x54u), local(&d, -0x3cu));
    chooser(&d, local(&d, -0x34u), local(&d, -0x3cu), local(&d, -0x68u), 0x532ac4, 0xa, 0, 2,
            0x416b50, 0, 0x447f40);
    next_row(&d);
    label(&d, local(&d, -0x50u), word(&d, -0x24u));
    chooser(&d, local(&d, -0x34u), word(&d, -0x28u), local(&d, -0x64u), 0x532aec, 2, 1, 3, 0x416b70,
            0, 0x447f40);
    port_set16(&port, d.ebp, -0x28u, local(&d, -0x28u) + 0x19);
    port_set16(&port, d.ebp, -0x24u, local(&d, -0x24u) + 0x19);
    label(&d, local(&d, -0x4cu), word(&d, -0x24u));
    chooser(&d, local(&d, -0x34u), word(&d, -0x28u), local(&d, -0x60u), 0x532af4, 2, 1, 3, 0x416b90,
            0, 0x447f40);
    next_row(&d);
    label(&d, local(&d, -0x48u), word(&d, -0x24u));
    chooser(&d, local(&d, -0x34u), word(&d, -0x28u), local(&d, -0x5cu), 0x532afc, 3, 0, 2, 0x415ef0,
            0x448670, 0x448260);
    {
        uint32_t rule[5] = {0x18a, 0xb4, d.esi, d.edi, 0};
        port_set32(&port, d.ebp, -0x44u, word(&d, -0x20u));
        d.edx = 0x11;
        d.ebx = d.esi;
        d.ecx = local(&d, -0x44u);
        d.eax = 0x84;
        dialog_call(&d, 0x460a40, rule, 5);
    }
    {
        uint32_t button[12] = {0x1a,
                               word(&d, -0x2cu),
                               local(&d, -0x44u),
                               0x18a,
                               0xb4,
                               d.esi,
                               d.edi,
                               0,
                               colour(&d, 0x4f9bfc),
                               0x10,
                               0,
                               1};
        d.ecx = 0x7f;
        d.ebx = 1;
        d.edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x4f7b8c);
        d.eax = 0x50e372;
        dialog_call(&d, 0x460b60, button, 12);
    }
    {
        uint32_t rule[5] = {0x18a, 0xb4, d.esi, d.edi, 0};
        d.ebx = word(&d, -0x1cu);
        d.ecx = local(&d, -0x44u);
        d.edx = 0x11;
        d.eax = 0x85;
        dialog_call(&d, 0x460a40, rule, 5);
    }
    d.eax = 0x15c;
    dialog_call(&d, 0x4ca000, NULL, 0);
    if (d.eax != 0)
    {
        d.ecx = 0xb;
        d.ebx = 0xa;
        port_set32(&port, d.ebp, -0x40u, d.eax);
        port_set32(&port, d.ebp, -0x74u, d.ecx);
        dialog_call(&d, 0x4abd70, NULL, 0);
        port_set32(&port, d.ebp, -0x74u, d.ebx);
    }
    d.esi = d.eax;
    d.edx = 0x45c6e0;
    dialog_call(&d, 0x4ac8f0, NULL, 0);
    d.eax = 0x54671c;
    d.edx = d.esi;
    d.esi = 0;
    dialog_call(&d, 0x4b5e70, NULL, 0);
    port_set32(&port, 0, 0x532a48, 0);
    dialog_call(&d, 0x4cda10, NULL, 0);
    d.eax = port_u32(&port, record, 0);
    port.env.chain = d.eax;
    return port_return(&port, d.eax, entry->edx);
}

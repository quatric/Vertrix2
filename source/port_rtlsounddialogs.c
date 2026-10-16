#include "port_rtlsounddialogs.h"

/* The sound settings dialog. */

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

static void set_word(Dialog *d, uint32_t offset, uint32_t value)
{
    port_set16(d->port, d->ebp, offset, value);
}

/* The byte at address, sign-extended (the original's dword read shifted down 24). */
static uint32_t colour(Dialog *d, uint32_t address)
{
    return (uint32_t)(int32_t)(int8_t)port_u8(d->port, 0, address);
}

/* A label (0x460c50) of the text at eax in the dialog's box at the row, at 0xcc across. */
static void label(Dialog *d, uint32_t text, uint32_t row)
{
    uint32_t args[11];
    args[0] = row;
    args[1] = 0x21b;
    args[2] = 0x9b;
    args[3] = d->esi;
    args[4] = d->edi;
    args[5] = 8;
    args[6] = 0;
    args[7] = 1;
    args[8] = colour(d, 0x4f9bf8);
    args[9] = 0x10;
    args[10] = 1;
    d->ebx = 0x1a;
    d->edx = 0xcc;
    d->eax = text;
    d->ecx = d->esi;
    dialog_call(d, 0x460c50, args, 11);
}

/* A rule (0x460ad0) at eax, edx, ebx, ecx; the stack's last the flag. */
static void rule(Dialog *d, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t flag)
{
    uint32_t args[5];
    args[0] = 0x21b;
    args[1] = 0x9b;
    args[2] = d->esi;
    args[3] = d->edi;
    args[4] = flag;
    d->eax = eax;
    d->edx = edx;
    d->ebx = ebx;
    d->ecx = ecx;
    dialog_call(d, 0x460ad0, args, 5);
}

/* A volume slider (0x460ed0) at the row from 0 to 100 at value, its formatter and handler. */
static void slider(Dialog *d, uint32_t row, uint32_t value, uint32_t format)
{
    uint32_t args[12];
    args[0] = 0;
    args[1] = 2;
    args[2] = format;
    args[3] = 0;
    args[4] = 0x64;
    args[5] = value;
    args[6] = 0x447f40;
    args[7] = 0x21b;
    args[8] = 0x9b;
    args[9] = d->esi;
    args[10] = d->edi;
    args[11] = 0;
    d->ecx = 0x1a;
    d->ebx = 0x150;
    d->eax = local(d, -0x5cu);
    d->edx = row;
    dialog_call(d, 0x460ed0, args, 12);
}

/* A chooser (0x460fa0) at the row: its text, value, count, formatter and handlers. */
static void chooser(Dialog *d, uint32_t row, uint32_t text, uint32_t value, uint32_t count,
                    uint32_t format, uint32_t changed)
{
    uint32_t args[17];
    args[0] = text;
    args[1] = value;
    args[2] = count;
    args[3] = 0;
    args[4] = 2;
    args[5] = format;
    args[6] = changed;
    args[7] = 0x448260;
    args[8] = colour(d, 0x4f9bfd);
    args[9] = 0x10;
    args[10] = 0x19;
    args[11] = 0;
    args[12] = 0x21b;
    args[13] = 0x9b;
    args[14] = d->esi;
    args[15] = d->edi;
    args[16] = 0;
    d->ecx = 0x1a;
    d->ebx = 0x150;
    d->eax = local(d, -0x5cu);
    d->edx = row;
    dialog_call(d, 0x460fa0, args, 17);
}

/* A setting's name (0x415ed0 of the setting at value in its table) set as the text at ebp - slot
 * (0x4ca370). */
static void setting_text(Dialog *d, uint32_t value, uint32_t table, uint32_t slot)
{
    d->eax = port_u32(d->port, 0, value);
    d->edx = table;
    dialog_call(d, 0x415ed0, NULL, 0);
    d->edx = d->eax;
    d->eax = d->ebp - slot;
}

/* A picker actor (eax, as made) of the kind handed its handler (0x4ac8f0). */
static void picker(Dialog *d, uint32_t kind, uint32_t handler)
{
    Port *port = d->port;
    d->esi = d->eax;
    d->edx = handler;
    port_set16(port, d->esi, 0x15c, kind);
    dialog_call(d, 0x4ac8f0, NULL, 0);
}

/* Original 0x461fc0 (guarded 0x515900): the sound settings dialog. Its texts made (0x4ca070,
 * 0x4ca280: VOL. MUSIC, VOL. SFX, TEST MUSIC, TEST SFX), the volumes 0x532b98/0x532b9c printed
 * (%lu, 0x4cdfb0) and the four settings' names set (0x415ed0, 0x4ca370). A 539 by 155 box centred
 * on the screen 0x558c7c (0x460a40) titled SOUND (0x460c50); rows of rules (0x460ad0 with the
 * colours 0xff000000 by 0x4ac4f0), labels and the two volume sliders (0x460ed0 of 0x532bb4 and
 * 0x532bb8) and the two test choosers (0x460fa0 of 0x532fec and 0x532d8c); two picker actors
 * (0x4ca000 of 0x164 made by 0x4b5c60; kinds 0x5f and 0x60 with 0x4576d0 and 0x457670) added to
 * 0x54671c; a rule, the RETURN button (0x460b60) and a rule; a new actor (0x4abd70) handed
 * 0x45c6e0 and added; 0x532a48 cleared and the frame ended (0x4cda10). eax the restored chain,
 * edx kept. */
uint32_t vertrix_port_sound_dialog_461fc0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xb8
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
    record = d.ebp - 0xb4;
    port_set32(&port, d.ebp, 0, entry->ebp);
    port_set32(&port, d.ebp, -4u, entry->ebx);
    port_set32(&port, d.ebp, -8u, entry->ecx);
    port_set32(&port, d.ebp, -0xcu, entry->edx);
    port_set32(&port, d.ebp, -0x10u, entry->esi);
    port_set32(&port, d.ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    d.edx = 0x4ec1ec;
    d.ecx = 0x515900;
    d.esi = 1;
    d.edi = 2;
    d.ebx = 0;
    port_set32(&port, d.ebp, -0xb0u, d.edx);
    port_set32(&port, d.ebp, -0xacu, d.ecx);
    port_set32(&port, d.ebp, -0xa8u, d.ebx);
    d.eax = d.ebp - 0xa0;
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x9c;
    d.edx = 4;
    d.ecx = 5;
    port_set32(&port, d.ebp, -0xa8u, d.esi);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x98;
    port_set32(&port, d.ebp, -0xa8u, d.edi);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.ebx = 6;
    port_set32(&port, d.ebp, -0xa8u, 3);
    d.eax = d.ebp - 0x94;
    d.esi = 7;
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x90;
    port_set32(&port, d.ebp, -0xa8u, d.edx);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x8c;
    d.edx = 0x50e379;
    port_set32(&port, d.ebp, -0xa8u, d.ecx);
    dialog_call(&d, 0x4ca070, NULL, 0);
    d.eax = d.ebp - 0x88;
    port_set32(&port, d.ebp, -0xa8u, d.ebx);
    dialog_call(&d, 0x4ca280, NULL, 0);
    port_set32(&port, d.ebp, -0xa8u, d.esi);
    d.edx = 0x50e384;
    d.eax = d.ebp - 0x84;
    d.edi = 8;
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e38d;
    d.eax = d.ebp - 0x80;
    port_set32(&port, d.ebp, -0xa8u, d.edi);
    dialog_call(&d, 0x4ca280, NULL, 0);
    d.edx = 0x50e398;
    port_set32(&port, d.ebp, -0xa8u, 9);
    d.eax = d.ebp - 0x7c;
    dialog_call(&d, 0x4ca280, NULL, 0);
    {
        uint32_t music[3] = {d.ebp - 0xa0, 0x50e3a1, port_u32(&port, 0, 0x532b98)};
        d.ecx = music[2];
        d.eax = d.ebp - 0xa0;
        d.edx = 0xa;
        port_set32(&port, d.ebp, -0xa8u, d.edx);
        dialog_call(&d, 0x4cdfb0, music, 3);
    }
    {
        uint32_t effects[3] = {d.ebp - 0x9c, 0x50e3a5, port_u32(&port, 0, 0x532b9c)};
        d.ebx = effects[2];
        d.eax = d.ebp - 0x9c;
        d.ecx = 2;
        d.edx = 0x532c9c;
        dialog_call(&d, 0x4cdfb0, effects, 3);
    }
    d.ebx = 0x4f817c;
    d.eax = port_u32(&port, 0, 0x532ba0);
    dialog_call(&d, 0x415ed0, NULL, 0);
    d.ecx = 0x1c;
    d.edx = d.eax;
    d.eax = d.ebp - 0x98;
    d.ebx = 0x4f8300;
    dialog_call(&d, 0x4ca370, NULL, 0);
    d.esi = 0;
    setting_text(&d, 0x532ba4, 0x532fec, 0x94);
    d.ecx = 0x13;
    d.ebx = 0x4f8370;
    dialog_call(&d, 0x4ca370, NULL, 0);
    port_set32(&port, d.ebp, -0x68u, d.esi);
    setting_text(&d, 0x532ba8, 0x53305c, 0x90);
    d.ecx = 0x4c;
    d.ebx = 0x4f81d0;
    dialog_call(&d, 0x4ca370, NULL, 0);
    d.esi = 0x9b;
    setting_text(&d, 0x532bac, 0x532d8c, 0x8c);
    set_word(&d, -0x58u, d.esi);
    dialog_call(&d, 0x4ca370, NULL, 0);
    screen = port_u32(&port, 0, 0x558c7c);
    height = port_u16(&port, screen, 8);
    left = (port_u32(&port, screen, 4) - 0x21b) >> 1;
    set_word(&d, -0x4cu, 0x1a);
    set_word(&d, -0x40u, 0x7f);
    set_word(&d, -0x2cu, 0x21b);
    set_word(&d, -0x28u, left);
    set_word(&d, -0x24u, 0xca);
    set_word(&d, -0x3cu, height - 0xc3);
    set_word(&d, -0x18u, height - 0xa8);
    set_word(&d, -0x1cu, local(&d, -0x28u) + 0xcb);
    set_word(&d, -0x34u, height - 0x76);
    set_word(&d, -0x30u, height - 0x42);
    set_word(&d, -0x38u, 0xd0);
    set_word(&d, -0x54u, local(&d, -0x1cu));
    set_word(&d, -0x44u, local(&d, -0x30u));
    set_word(&d, -0x20u, local(&d, -0x28u) + 0x14b);
    set_word(&d, -0x50u, local(&d, -0x30u));
    set_word(&d, -0x48u, left);
    d.esi = word(&d, -0x28u);
    d.edi = word(&d, -0x3cu);
    {
        uint32_t box[5] = {0x21b, 0x9b, d.esi, d.edi, 1};
        d.ebx = d.esi;
        d.edx = 0x11;
        d.ecx = (uint32_t)(int32_t)(int16_t)(local(&d, -0x3cu) + 9);
        d.eax = 0x21b;
        dialog_call(&d, 0x460a40, box, 5);
    }
    {
        uint32_t title[11] = {d.edi, 0x21b, 0x9b, d.esi, d.edi, 0, 1, 1, colour(&d, 0x4f9bf8),
                              0x10,  1};
        d.ebx = 0x1a;
        d.edx = 0x21b;
        d.ecx = d.esi;
        d.eax = 0x50e3a9;
        dialog_call(&d, 0x460c50, title, 11);
    }
    port_set32(&port, d.ebp, -0x60u, word(&d, -0x18u));
    rule(&d, 0xcc, 0x33, d.esi, local(&d, -0x60u), 1);
    label(&d, local(&d, -0x88u), local(&d, -0x60u));
    port_set32(&port, d.ebp, -0x5cu, word(&d, -0x1cu));
    rule(&d, 0x150, 0x1a, local(&d, -0x5cu), local(&d, -0x60u), 0);
    d.edx = 0xff000000u;
    dialog_call(&d, 0x4ac4f0, NULL, 0);
    slider(&d, local(&d, -0x60u), port_u32(&port, 0, 0x532bb4), 0x417030);
    port_set32(&port, d.ebp, -0x64u, (uint32_t)(int32_t)(int16_t)(local(&d, -0x18u) + 0x19));
    label(&d, local(&d, -0x84u), local(&d, -0x64u));
    rule(&d, 0x150, 0x1a, local(&d, -0x5cu), local(&d, -0x64u), 0);
    d.edx = 0xff000000u;
    dialog_call(&d, 0x4ac4f0, NULL, 0);
    slider(&d, local(&d, -0x64u), port_u32(&port, 0, 0x532bb8), 0x417060);
    port_set32(&port, d.ebp, -0x6cu, word(&d, -0x34u));
    rule(&d, 0xcc, 0x33, d.esi, local(&d, -0x6cu), 1);
    label(&d, local(&d, -0x80u), local(&d, -0x6cu));
    chooser(&d, local(&d, -0x6cu), local(&d, -0x94u), 0x532fec, 0x1c, 0x4170f0, 0x448690);
    port_set32(&port, d.ebp, -0x74u, (uint32_t)(int32_t)(int16_t)(local(&d, -0x34u) + 0x19));
    label(&d, local(&d, -0x7cu), local(&d, -0x74u));
    chooser(&d, local(&d, -0x74u), local(&d, -0x8cu), 0x532d8c, 0x4c, 0x417130, 0x4486d0);
    d.eax = 0x164;
    dialog_call(&d, 0x4ca000, NULL, 0);
    if (d.eax != 0)
    {
        d.esi = 0xb;
        d.edi = 0xa;
        port_set32(&port, d.ebp, -0x78u, d.eax);
        port_set32(&port, d.ebp, -0xa8u, d.esi);
        dialog_call(&d, 0x4b5c60, NULL, 0);
        port_set32(&port, d.ebp, -0xa8u, d.edi);
    }
    picker(&d, 0x5f, 0x4576d0);
    d.edx = 0x14;
    d.eax = d.esi;
    dialog_call(&d, 0x4ac7b0, NULL, 0);
    d.eax = 0x54671c;
    d.edx = d.esi;
    port_set32(&port, d.esi, 0x160, 1);
    dialog_call(&d, 0x4b5e70, NULL, 0);
    d.eax = 0x164;
    dialog_call(&d, 0x4ca000, NULL, 0);
    if (d.eax != 0)
    {
        d.edx = 0xd;
        d.ecx = 0xa;
        port_set32(&port, d.ebp, -0x78u, d.eax);
        port_set32(&port, d.ebp, -0xa8u, d.edx);
        dialog_call(&d, 0x4b5c60, NULL, 0);
        port_set32(&port, d.ebp, -0xa8u, d.ecx);
    }
    d.ebx = local(&d, -0x68u);
    d.edi = local(&d, -0x3eu);
    picker(&d, 0x60, 0x457670);
    d.edx = 0x14;
    d.eax = d.esi;
    d.ecx = local(&d, -0x32u);
    dialog_call(&d, 0x4ac7b0, NULL, 0);
    d.edi = (uint32_t)((int32_t)d.edi >> 16);
    d.eax = 0x54671c;
    d.edx = d.esi;
    port_set32(&port, d.esi, 0x160, 1);
    dialog_call(&d, 0x4b5e70, NULL, 0);
    d.esi = word(&d, -0x28u);
    d.ecx = (uint32_t)((int32_t)d.ecx >> 16);
    port_set32(&port, d.ebp, -0x74u, word(&d, -0x58u));
    port_set32(&port, d.ebp, -0x70u, word(&d, -0x2cu));
    {
        uint32_t box[5] = {local(&d, -0x70u), local(&d, -0x74u), d.esi, d.edi, d.ebx};
        d.edx = 0x11;
        d.ebx = word(&d, -0x48u);
        d.eax = word(&d, -0x24u);
        dialog_call(&d, 0x460a40, box, 5);
    }
    {
        uint32_t button[12] = {word(&d, -0x4cu),
                               word(&d, -0x54u),
                               word(&d, -0x44u),
                               local(&d, -0x70u),
                               local(&d, -0x74u),
                               d.esi,
                               d.edi,
                               local(&d, -0x68u),
                               colour(&d, 0x4f9bfc),
                               0x10,
                               0,
                               1};
        d.edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x4f7b90);
        d.ecx = word(&d, -0x40u);
        d.ebx = 1;
        d.eax = 0x50e3af;
        dialog_call(&d, 0x460b60, button, 12);
    }
    {
        uint32_t box[5] = {local(&d, -0x70u), local(&d, -0x74u), d.esi, d.edi, local(&d, -0x68u)};
        d.eax = word(&d, -0x38u);
        d.edx = 0x11;
        d.ecx = word(&d, -0x50u);
        d.ebx = word(&d, -0x20u);
        dialog_call(&d, 0x460a40, box, 5);
    }
    d.eax = 0x15c;
    dialog_call(&d, 0x4ca000, NULL, 0);
    if (d.eax != 0)
    {
        d.esi = 0xf;
        d.edi = 0xa;
        port_set32(&port, d.ebp, -0x78u, d.eax);
        port_set32(&port, d.ebp, -0xa8u, d.esi);
        dialog_call(&d, 0x4abd70, NULL, 0);
        port_set32(&port, d.ebp, -0xa8u, d.edi);
    }
    d.esi = d.eax;
    d.edx = 0x45c6e0;
    dialog_call(&d, 0x4ac8f0, NULL, 0);
    d.eax = 0x54671c;
    d.edx = d.esi;
    dialog_call(&d, 0x4b5e70, NULL, 0);
    d.eax = 0;
    port_set32(&port, 0, 0x532a48, 0);
    dialog_call(&d, 0x4cda10, NULL, 0);
    d.eax = port_u32(&port, record, 0);
    port.env.chain = d.eax;
    return port_return(&port, d.eax, entry->edx);
}

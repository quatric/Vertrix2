#include "port_rtlrooms.h"

/* Screen room refreshes. */

/* Original 0x4237d0: under the guard record 0x51420c the screen eax refreshed: on its first time
 * (0x5405f4 clear) the count 0x5405f8 cleared, the flag set, 0x4b7cd0, 0x472100 and 0x41d640;
 * then 0x4b7d10, 0x41d670 with 7, 0x472350, the entry count +0x58 of 0x4b5eb0's record for
 * 0x54676c (0 without), the list 0x5b9c50 opened (0x486d00); a first refresh places the panel
 * 0x558c7c at 0x558c80's size (0x47ce10) and every entry from the old count to the new is added
 * (0x479e50 with 0x558c88); the list closed (0x41d6d0, 0x486da0, 0x487020, 0x486ed0), the count
 * kept, 0x41d660, 0x41de80, 0x41ddf0, and when 0x472360 says 1 the screen left (0x472330,
 * 0x41ac80, 0x418830 with 0) and the flag set from 0x418830's edx bits 8-15. eax the restored
 * chain, edx kept. */
uint32_t vertrix_port_screen_room_refresh_4237d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t record = ebp - 0x28;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x51420c;
    uint32_t esi = entry->esi;
    uint32_t flag;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, screen, ebp)
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    flag = port_u8(&port, 0, 0x5405f4);
    eax = (record & 0xffff00ffu) | (flag << 8);
    port_set32(&port, ebp, -0x24u, 0x4ec1ec);
    port_set32(&port, ebp, -0x20u, 0x51420c);
    port_set32(&port, ebp, -0x1cu, 0);
    if (flag == 0)
    {
        edx = (edx & 0xffffff00u) | 1;
        port_set32(&port, 0, 0x5405f8, 0);
        port_set8(&port, 0, 0x5405f4, 1);
        eax = CALL(0x4b7cd0, eax, edx);
        eax = CALL(0x472100, eax, vertrix_lift_edx);
        eax = CALL(0x41d640, screen, vertrix_lift_edx);
        edx = vertrix_lift_edx;
    }
    CALL(0x4b7d10, eax, edx);
    eax = CALL(0x41d670, screen, 7);
    CALL(0x472350, eax, vertrix_lift_edx);
    eax = CALL(0x4b5eb0, 0x54676c, vertrix_lift_edx);
    esi = eax != 0 ? port_u32(&port, eax, 0x58) : 0;
    CALL(0x486d00, 0x5b9c50, vertrix_lift_edx);
    eax = port_u32(&port, 0, 0x5405f8);
    if (eax == 0)
    {
        uint32_t size = port_u32(&port, 0, 0x558c80);
        uint32_t args[4] = {0, 0, port_u32(&port, size, 4), port_u32(&port, size, 8)};
        ecx = 0;
        ebx = 0;
        vertrix_lift_in_esi = esi;
        vertrix_lift_in_edi = screen;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x47ce10, port_u32(&port, 0, 0x558c7c), size, 0, 0, args, 4);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    }
    eax = port_u32(&port, 0, 0x5405f8);
    if (esi != eax)
    {
        ecx = eax;
    }
    if (esi != eax && eax <= esi)
    {
        do
        {
            ebx = ecx;
            ecx++;
            CALL(0x479e50, port_u32(&port, 0, 0x558c7c), port_u32(&port, 0, 0x558c88));
        } while (ecx <= esi && !port.env.failed);
    }
    CALL(0x41d6d0, screen, vertrix_lift_edx);
    CALL(0x486da0, 0x5b9c50, vertrix_lift_edx);
    CALL(0x487020, 0x5b9c50, vertrix_lift_edx);
    CALL(0x486ed0, 0x5b9c50, vertrix_lift_edx);
    port_set32(&port, 0, 0x5405f8, esi);
    CALL(0x41d660, screen, vertrix_lift_edx);
    CALL(0x41de80, screen, vertrix_lift_edx);
    eax = CALL(0x41ddf0, screen, vertrix_lift_edx);
    eax = CALL(0x472360, eax, vertrix_lift_edx);
    if (eax == 1)
    {
        CALL(0x472330, eax, vertrix_lift_edx);
        CALL(0x41ac80, screen, vertrix_lift_edx);
        CALL(0x418830, screen, vertrix_lift_edx & 0xffff00ffu);
        port_set8(&port, 0, 0x5405f4, vertrix_lift_edx >> 8);
    }
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
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

/* Original 0x45fc80 (five stack arguments, popped: the text, the font byte, the fade, the place
 * and the flags; guarded 0x51576c): a 0x170 byte panel (0x4ca000; 0x4b3100 makes it with esi 1)
 * placed (0x4adf20) at eax + 2 across and dx + 2 down, ecx - 4 by ebx - 4 (0x4b54d0), shown
 * (0x4ac7b0 with 2), +0x110 1, +0x52 9, +0x94 1, +0x95 1 and 0x4ac4e0 with 0x7f; its text, a 0x180
 * byte box (0x4b6350 with 3), placed (0x4adf20) with the text and the font (0x4b65d0), shown with
 * the flags in edi, its fade +0x44 set and put on the panel (0x4b3210 at the place with the flags
 * and 1). eax the panel. */
uint32_t vertrix_port_text_panel_make_45fc80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8 + 5 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t pushed[2];
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->eax + 2;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 5);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set16(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x10u, entry->ecx);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x51576c);
    port_set32(&port, ebp, -0x24u, 0);
    eax = port_call_with(&port, 0x4ca000, 0x170, 0x4ec1ec, 0, 0x51576c, esi, edi, ebp);
    edx = port_u32(&port, ebp, -0x14u) + 2;
    ebx = port_u32(&port, ebp, -0xcu) - 4;
    ecx = port_u32(&port, ebp, -0x10u) - 4;
    port_set16(&port, ebp, -0x14u, edx);
    port_set32(&port, ebp, -0xcu, ebx);
    port_set32(&port, ebp, -0x10u, ecx);
    if (eax != 0)
    {
        esi = 1;
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, esi);
        eax = port_call_with(&port, 0x4b3100, eax, 0, ebx, ecx, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, vertrix_lift_edx);
    }
    esi = eax;
    call_frame(&port, 0x4adf20, esi, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x16u) >> 16);
    edx = (uint32_t)(int32_t)(int16_t)edi;
    ecx = port_u16(&port, ebp, -0xcu);
    pushed[0] = port_u16(&port, ebp, -0x10u);
    call_frame(&port, 0x4b54d0, esi, edx, ebx, ecx, esi, edi, ebp, pushed, 1);
    port_call_with(&port, 0x4ac7b0, esi, 2, ebx, ecx, esi, edi, ebp);
    port_set8(&port, esi, 0x110, 1);
    port_set8(&port, esi, 0x52, 9);
    port_set8(&port, esi, 0x94, 1);
    port_set8(&port, esi, 0x95, 1);
    port_call_with(&port, 0x4ac4e0, esi, 0x7f, 0, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x18u, esi);
    eax = port_call_with(&port, 0x4ca000, 0x180, vertrix_lift_edx, 0, ecx, esi, edi, ebp);
    if (eax != 0)
    {
        port_set32(&port, ebp, -0x1cu, eax);
        port_set32(&port, ebp, -0x24u, 3);
        eax = port_call_with(&port, 0x4b6350, eax, vertrix_lift_edx, 0, 3, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
    }
    esi = eax;
    call_frame(&port, 0x4adf20, esi, 0, 0, 0, esi, edi, ebp, zeros, 5);
    ebx = (uint32_t)((int32_t)port_u32(&port, ebp, 9) >> 24);
    call_frame(&port, 0x4b65d0, esi, port_u32(&port, ebp, 8), ebx, 0, esi, edi, ebp, zeros, 3);
    edi = port_u32(&port, ebp, 0x18);
    port_call_with(&port, 0x4ac7b0, esi, 2, ebx, 0, esi, edi, ebp);
    port_set8(&port, esi, 0x44, port_u8(&port, ebp, 0x10));
    pushed[0] = edi;
    pushed[1] = 1;
    call_frame(&port, 0x4b3210, port_u32(&port, ebp, -0x18u), esi, port_u16(&port, ebp, 0x14), 0,
               esi, edi, ebp, pushed, 2);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, port_u32(&port, ebp, -0x18u), vertrix_lift_edx);
}

/* Original 0x440490 (one stack argument, popped: the text): each character of the text laid out
 * for the owner eax in the font dl from across ebx at down cx: a space advances by the font's
 * space width (0x541988 + 0x20c per font) plus 1; any other has its glyph (0x43f420) made into a
 * 0x15c byte sprite (0x4ca000; 0x4abd70 makes it) placed there (0x4adf20 with the glyph), +0x8e
 * 0 and +0x8f 1, handed the owner (its class +8) and shown (its class +0 with 2), advancing by
 * the glyph's width +4 plus 1 (a missing glyph by 1). eax the last value, edx the text end. */
uint32_t vertrix_port_text_glyph_row_440490(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->ebx;
    uint32_t text;
    uint32_t font;
    uint32_t glyph;
    uint32_t vtable;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x18u, entry->eax);
    eax = port_u32(&port, ebp, 8);
    port_set8(&port, ebp, -0xcu, entry->edx);
    port_set16(&port, ebp, -0x10u, entry->ecx);
    edx = (entry->edx & 0xffffff00u) | port_u8(&port, eax, 0);
    if ((edx & 0xff) == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        text = port_u32(&port, ebp, 8);
        ebx = (ebx & 0xffffff00u) | port_u8(&port, text, 0);
        font = (uint32_t)((int32_t)port_u32(&port, ebp, -0xfu) >> 24);
        if ((ebx & 0xff) == 0x20)
        {
            eax = port_u32(&port, font * 0x20c + 0x541988, 0);
            edi += eax;
            edi++;
        }
        else
        {
            eax = port_call_with(&port, 0x43f420, font, ebx & 0xff, ebx, ecx, esi, edi, ebp);
            port_set32(&port, ebp, -0x14u, eax);
            if (eax != 0)
            {
                eax = port_call_with(&port, 0x4ca000, 0x15c, vertrix_lift_edx, ebx, ecx, esi, edi,
                                     ebp);
                if (eax != 0)
                {
                    eax = port_call_with(&port, 0x4abd70, eax, vertrix_lift_edx, ebx, ecx, esi, edi,
                                         ebp);
                }
                esi = eax;
                glyph = port_u32(&port, ebp, -0x14u);
                zeros[2] = glyph;
                ecx = 0;
                ebx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x12u) >> 16);
                call_frame(&port, 0x4adf20, esi, (uint32_t)(int32_t)(int16_t)edi, ebx, ecx, esi,
                           edi, ebp, zeros, 5);
                zeros[2] = 0;
                port_set8(&port, esi, 0x8e, 0);
                vtable = port_u32(&port, esi, 0x158);
                ebx = vtable;
                port_set8(&port, esi, 0x8f, 1);
                port_call_with(&port, port_u32(&port, vtable, 8), esi, port_u32(&port, ebp, -0x18u),
                               ebx, ecx, esi, edi, ebp);
                if (esi != 0)
                {
                    ebx = port_u32(&port, esi, 0x158);
                    port_call_with(&port, port_u32(&port, ebx, 0), esi, 2, ebx, ecx, esi, edi, ebp);
                }
                eax = port_u32(&port, ebp, -0x14u);
                edi = (edi & 0xffff0000u) | ((edi + port_u16(&port, eax, 4)) & 0xffffu);
            }
            edi++;
        }
        edx = port_u32(&port, ebp, 8) + 1;
        port_set32(&port, ebp, 8, edx);
    } while (port_u8(&port, edx, 0) != 0 && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x445b90: the actor eax steered by the pointer: without the pointer 0x5bb254 (0x47e990)
 * it is handed 0 (0x4ac8f0) and +0x52 cleared; else its period run (0x4ac500, 0x4ac520; when up,
 * 0x4ac540 steps taken by 0x4ac5b0, +0x4a 0, +0x4c 5, 0x4ad530); unless the pointer is down
 * (0x47f410) +0x52 is cleared; the critical section 0x558c9c entered (import 0x4f1b48) round
 * 0x47f370 and left (import 0x4f1c40); unless 0x47f370 then says -1, +0x52 is 9, the actor
 * tested at the pointer 0x558944/0x558946 (0x7d00 each while 0x558958 is set) by 0x4b0b70 (+0x48
 * 0x23 on a hit); on key 0x74 down (0x476480) its point read (0x4764a0) and, on a hit there, the
 * key taken (0x476320), +0x52 0xa and the actor handed 0x445d10. Registers but eax kept. */
uint32_t vertrix_port_actor_pointer_steer_445b90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = actor;
    uint32_t ecx = entry->ecx;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, actor, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    eax = CALL(0x47e990, 0x5bb254, entry->edx);
    if (eax == 0)
    {
        eax = CALL(0x4ac8f0, actor, 0);
        port_set8(&port, actor, 0x52, 0);
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x4ac500, actor, vertrix_lift_edx);
    eax = CALL(0x4ac520, actor, vertrix_lift_edx);
    if (eax == 1)
    {
        eax = CALL(0x4ac540, actor, vertrix_lift_edx);
        CALL(0x4ac5b0, actor, eax);
        port_set16(&port, actor, 0x4a, 0);
        port_set16(&port, actor, 0x4c, 5);
        CALL(0x4ad530, actor, vertrix_lift_edx);
    }
    eax = CALL(0x47f410, 0x5bb254, vertrix_lift_edx);
    if (eax == 0)
    {
        port_set8(&port, actor, 0x52, 0);
        return port_return(&port, eax, entry->edx);
    }
    {
        uint32_t args[1] = {0x558c9c};
        eax =
            call_frame(&port, 0x4f1b48, eax, vertrix_lift_edx, ebx, ecx, actor, edi, ebp, args, 1);
        eax = CALL(0x47f370, 0x5bb254, vertrix_lift_edx);
        args[0] = 0x558c9c;
        eax =
            call_frame(&port, 0x4f1c40, eax, vertrix_lift_edx, ebx, ecx, actor, edi, ebp, args, 1);
        eax = CALL(0x47f370, 0x5bb254, vertrix_lift_edx);
    }
    if (eax == 0xffffffffu)
    {
        port_set8(&port, actor, 0x52, 0);
        return port_return(&port, eax, entry->edx);
    }
    port_set8(&port, actor, 0x52, 9);
    if (port_u32(&port, 0, 0x558958) != 0)
    {
        eax = 0x7d00;
    }
    else
    {
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, 0x558946);
    }
    ecx = port_u32(&port, 0, 0x558958);
    ebx = (uint32_t)(int32_t)(int16_t)eax;
    if (ecx != 0)
    {
        eax = 0x7d00;
    }
    else
    {
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, 0x558944);
    }
    edx = (uint32_t)(int32_t)(int16_t)eax;
    eax = CALL(0x4b0b70, actor, edx);
    if ((eax & 0xff) != 0)
    {
        port_set16(&port, actor, 0x48, 0x23);
    }
    eax = CALL(0x476480, 0x54d640, 0x74);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    {
        uint32_t args[1] = {ebp - 0x14};
        ecx = ebp - 0x18;
        ebx = ebp - 0x1c;
        call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebx, ecx, actor, edi, ebp, args, 1);
    }
    ebx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x1au) >> 16);
    edx = (uint32_t)((int32_t)port_u32(&port, ebp, -0x1eu) >> 16);
    eax = CALL(0x4b0b70, actor, edx);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    CALL(0x476320, 0x54d640, 0x74);
    port_set8(&port, actor, 0x52, 0xa);
    eax = CALL(0x4ac8f0, actor, 0x445d10);
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* The shared tail of 0x41f080 and 0x41f500 for the screen ecx (frame 0x12c, guard at ebp - 0x24):
 * the title text 0x4fc398 formatted with the language's name (0x5334a0 by 0x513c2c; 0x45f540)
 * set on the screen (0x41a960 with 1), its font 0x4f854c (0x4191b0), 0x45f770, the variant's
 * music started (0x46ea30 with esi or 0x46eda0 with 0x54000c), 0x472bd0, the keys 0x54d640 reset
 * (0x476090, 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 with the edx left, 0x3b, 0x3c and
 * 0x3d, 0x476120 with 0x5f and 0x60), 0x4b7cd0, 0x5588f8 cleared (0x477d70), 0x532a98 kept at
 * 0x532a4c, the screen readied (0x41aa20, 0x471a70, 0x471a80, 0x41ab60, 0x41ab00, 0x41aaa0 with
 * the painter 0x423960, 0x418840) and handed its step (0x418820). eax the restored chain. */
static uint32_t screen_title_setup(Port *port, const LiftEntry *entry, uint32_t esi, int music_esi,
                                   uint32_t step)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t ebx;
    uint32_t edi = entry->edi;
    uint32_t record = ebp - 0x24;
#define CALL(target, a, d) port_call_with(port, target, a, d, ebx, screen, esi, edi, ebp)
    ebx = port_u32(port, port_u8(port, 0, 0x513c2c) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x128, 0x4fc398);
    ebx = 1;
    CALL(0x41a960, screen, ebp - 0x128);
    eax = CALL(0x4191b0, screen, port_u32(port, 0, 0x4f854c));
    CALL(0x45f770, eax, vertrix_lift_edx);
    if (music_esi)
    {
        eax = CALL(0x46ea30, esi, vertrix_lift_edx);
    }
    else
    {
        eax = CALL(0x46eda0, port_u32(port, 0, 0x54000c), vertrix_lift_edx);
    }
    CALL(0x472bd0, eax, vertrix_lift_edx);
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    CALL(0x476140, 0x54d640, vertrix_lift_edx);
    CALL(0x476140, 0x54d640, 0x3b);
    CALL(0x476140, 0x54d640, 0x3c);
    CALL(0x476140, 0x54d640, 0x3d);
    CALL(0x476120, 0x54d640, 0x5f);
    eax = CALL(0x476120, 0x54d640, 0x60);
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x477d70, 0x5588f8, vertrix_lift_edx);
    port_set32(port, 0, 0x532a4c, port_u32(port, 0, 0x532a98));
    eax = CALL(0x41aa20, screen, vertrix_lift_edx);
    eax = CALL(0x471a70, eax, vertrix_lift_edx);
    CALL(0x471a80, eax, vertrix_lift_edx);
    CALL(0x41ab60, screen, vertrix_lift_edx);
    CALL(0x41ab00, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, 0x423960);
    CALL(0x418840, screen, vertrix_lift_edx);
    CALL(0x418820, screen, step);
#undef CALL
    eax = port_u32(port, record, 0);
    port->env.chain = eax;
    return port_return(port, eax, entry->edx);
}

enum
{
    TITLE_BELOW = 0x12c
};

static uint32_t screen_title_open(Port *port, uint8_t *stack, PORT_SIGNATURE, uint32_t guard)
{
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x24;
    port_open_stack(port, stack, calls, services, globals, entry, TITLE_BELOW);
    port_set32(port, ebp, 0, entry->ebp);
    port_set32(port, ebp, -4u, entry->ebx);
    port_set32(port, ebp, -8u, entry->ecx);
    port_set32(port, ebp, -0xcu, entry->edx);
    port_set32(port, ebp, -0x10u, entry->esi);
    port_set32(port, record, 0, port->env.chain);
    port->env.chain = record;
    port_set32(port, ebp, -0x20u, 0x4ec1ec);
    port_set32(port, ebp, -0x1cu, guard);
    port_set32(port, ebp, -0x18u, 0);
    return ebp;
}

/* Original 0x41f080 (guarded 0x514100): the title screen eax for the music 0x415d60 gives
 * (0x415d90, 0x41df30 with it, then screen_title_setup playing it by 0x46ea30, step 0x41f210). */
uint32_t vertrix_port_screen_title_music_41f080(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[TITLE_BELOW + 8];
    uint32_t ebp = screen_title_open(&port, stack, calls, services, globals, entry, 0x514100);
    uint32_t esi;
    esi = port_call_with(&port, 0x415d60, ebp - 0x24, 0x4ec1ec, 0x514100, entry->eax, 0, entry->edi,
                         ebp);
    port_call_with(&port, 0x415d90, esi, vertrix_lift_edx, 0x514100, entry->eax, esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x41df30, esi, vertrix_lift_edx, 0x514100, entry->eax, esi, entry->edi,
                   ebp);
    return screen_title_setup(&port, entry, esi, 1, 0x41f210);
}

/* Original 0x41f500 (guarded 0x514110): the title screen eax with the room 0x13 (0x41df30), then
 * screen_title_setup playing 0x54000c by 0x46eda0, step 0x41f680. */
uint32_t vertrix_port_screen_title_room_41f500(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[TITLE_BELOW + 8];
    uint32_t ebp = screen_title_open(&port, stack, calls, services, globals, entry, 0x514110);
    port_call_with(&port, 0x41df30, 0x13, 0x4ec1ec, 0x514110, entry->eax, 0, entry->edi, ebp);
    return screen_title_setup(&port, entry, 0, 0, 0x41f680);
}

/* Original 0x41e5e0 (guarded 0x5140c4): the five picture tables loaded: for each table k a block
 * at ebp - 0x58 opened (0x489f90); with at most one entry (0x54021c + 4k) it is closed (0x489fa0
 * with 0) and the load ends; else the table sized (0x45e8d0) and each entry j whose name
 * (0x54008c + 0x14k + 4j) is not 0x50dd32 (0x4ccfe0) has its two names formatted by 0x4fc9c8
 * (0x45f540, the second from 0x5400f0) and loaded (0x423dc0 with 0); a loaded picture is set into
 * the table (0x45e850 with 0x540154 and 0x5401b8 for the entry) and released (0x478d80); the
 * block closed (0x489fa0 with 0). eax the restored chain. */
uint32_t vertrix_port_picture_tables_load_41e5e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x264
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x40;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x5140c4;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t count;
    uint32_t table;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x3cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x38u, 0x5140c4);
    port_set32(&port, ebp, -0x34u, 0);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x24u, 0x54008c);
    do
    {
        CALL(0x489f90, ebp - 0x58, edx);
        count = port_u32(&port, port_u32(&port, ebp, -0x20u), 0x54021c);
        ecx = count;
        port_set32(&port, ebp, -0x34u, 1);
        if (count <= 1)
        {
            CALL(0x489fa0, ebp - 0x58, 0);
            break;
        }
        port_set32(&port, ebp, -0x1cu, count);
        CALL(0x45e8d0, port_u32(&port, ebp, -0x28u), count);
        edi = 0;
        table = port_u32(&port, ebp, -0x28u) * 0x14;
        port_set32(&port, ebp, -0x2cu, table);
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x24u));
        do
        {
            ecx = edi * 4;
            eax = CALL(0x4ccfe0, port_u32(&port, port_u32(&port, ebp, -0x18u), 0), 0x50dd32);
            if (eax != 0)
            {
                ebx = port_u32(&port, ecx + table + 0x54008c, 0);
                esi = table;
                CALL(0x45f540, ebp - 0x15c, 0x4fc9c8);
                ebx = port_u32(&port, ecx + table + 0x5400f0, 0);
                CALL(0x45f540, ebp - 0x260, 0x4fc9c8);
                ebx = 0;
                esi = CALL(0x423dc0, ebp - 0x15c, ebp - 0x260);
                if (esi != 0)
                {
                    uint32_t args[1];
                    ecx += table;
                    ebx = esi;
                    args[0] = port_u32(&port, ecx + 0x5401b8, 0);
                    ecx = port_u32(&port, ecx + 0x540154, 0);
                    vertrix_lift_in_esi = esi;
                    vertrix_lift_in_edi = edi;
                    vertrix_lift_in_ebp = ebp;
                    lift_call_arguments(&port.env, 0x45e850, port_u32(&port, ebp, -0x28u), edi, ebx,
                                        ecx, args, 1);
                    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
                    CALL(0x478d80, esi, vertrix_lift_edx);
                }
            }
            esi = port_u32(&port, ebp, -0x18u) + 4;
            edi++;
            port_set32(&port, ebp, -0x18u, esi);
        } while (edi < port_u32(&port, ebp, -0x1cu) && !port.env.failed);
        ebx = port_u32(&port, ebp, -0x20u);
        esi = port_u32(&port, ebp, -0x24u);
        edi = port_u32(&port, ebp, -0x28u);
        edx = 0;
        ecx = 0;
        port_set32(&port, ebp, -0x34u, 0);
        CALL(0x489fa0, ebp - 0x58, 0);
        ebx += 4;
        esi += 0x14;
        edi++;
        port_set32(&port, ebp, -0x34u, ecx);
        port_set32(&port, ebp, -0x20u, ebx);
        port_set32(&port, ebp, -0x24u, esi);
        port_set32(&port, ebp, -0x28u, edi);
    } while (edi < 5 && !port.env.failed);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

#include "port_rtlcomings.h"

/* Stream text writes, actors and title letters coming on, the slot screen and region scoring. */

/* Original 0x489470: the text edx written to the stream eax as its length (a dword) and then its
 * bytes, both through 0x4d79c0. */
uint32_t vertrix_port_stream_write_text_489470(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t text = entry->edx;
    uint32_t length = 0;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, stream);
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    port_set32(&port, ebp, -0x18u, length);
    port_call_with(&port, 0x4d79c0, stream, ebp - 0x18, 4, length, text, text + length + 1, ebp);
    eax = port_call_with(&port, 0x4d79c0, port_u32(&port, ebp, -0x14u), text,
                         port_u32(&port, ebp, -0x18u), length, text, text + length + 1, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x444700: the actor eax brought on (0x4ac1f0 with 1, 0x4ac8a0, 0x4ac500, 0x4ac600):
 * while its path is not over (0x4ac620) its steps go (0x4ac640, 0x4ac6b0, 0x4ad5e0, the result
 * kept at 0x5449bc), when its period is up its steps are taken (0x4ac540 into 0x5449b8, 0x4ac5b0,
 * 0x4ad060); its corner (0x4ad260 into 0x5449a8/0x5449aa) set at +0xe/+0x16, its travel +0x2a
 * (0x5449b0) against its length +0x30 (0x5449ac) fades it in over the first 40 (+0x44, 16 after
 * that until the last stretch, 0x5449b4); a faded or finished actor is stopped (0x4ac8f0). edx
 * kept. */
uint32_t vertrix_port_actor_bring_on_444700(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t travel;
    uint32_t length;
    port_open(&port, calls, services, globals, entry);
#define CALL(target, a, d) port_forward(&port, entry, target, a, d, ebx, actor)
    port_set32(&port, 0, 0x5449bc, 1);
    CALL(0x4ac1f0, actor, 1);
    CALL(0x4ac8a0, actor, vertrix_lift_edx);
    CALL(0x4ac500, actor, vertrix_lift_edx);
    CALL(0x4ac600, actor, vertrix_lift_edx);
    eax = CALL(0x4ac620, actor, vertrix_lift_edx);
    if (eax == vertrix_lift_edx)
    {
        port_set32(&port, 0, 0x5449b8, CALL(0x4ac640, actor, vertrix_lift_edx));
        CALL(0x4ac6b0, actor, vertrix_lift_edx);
        port_set32(&port, 0, 0x5449bc, CALL(0x4ad5e0, actor, port_u32(&port, 0, 0x5449b8)));
    }
    if (CALL(0x4ac520, actor, vertrix_lift_edx) == 1)
    {
        port_set32(&port, 0, 0x5449b8, CALL(0x4ac540, actor, vertrix_lift_edx));
        CALL(0x4ac5b0, actor, vertrix_lift_edx);
        CALL(0x4ad060, actor, port_u32(&port, 0, 0x5449b8));
    }
    ebx = 0x5449aa;
    CALL(0x4ad260, actor, 0x5449a8);
    port_set16(&port, actor, 0xe, port_u16(&port, 0, 0x5449a8));
    port_set16(&port, actor, 0x16, port_u16(&port, 0, 0x5449aa));
    travel = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16);
    port_set32(&port, 0, 0x5449b0, travel);
    length = (uint32_t)((int32_t)port_u32(&port, actor, 0x2e) >> 16);
    ebx = travel;
    port_set32(&port, 0, 0x5449ac, length);
    eax = length;
    if (travel <= 0x28)
    {
        port_set8(&port, actor, 0x44, 0x10);
        if (port_u32(&port, 0, 0x5449bc) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    else if (travel > length)
    {
        port_set8(&port, actor, 0x44, 0);
    }
    else
    {
        LiftFlags flags = {0};
        eax = (travel - 0x28) << 4;
        edx = 0;
        ebx = port_u32(&port, 0, 0x5449ac) - 0x28;
        lift_div1(32, ebx, &eax, &edx, &flags);
        edx = 0x10 - eax;
        port_set32(&port, 0, 0x5449b4, edx);
        eax = (int32_t)edx >= 0x10 ? 0x10 : edx;
        port_set8(&port, actor, 0x44, eax);
        eax = port_u8(&port, actor, 0x44);
        if ((int32_t)eax <= 0)
        {
            eax = 0;
        }
        port_set8(&port, actor, 0x44, eax);
        if ((eax & 0xff) != 0 && port_u32(&port, 0, 0x5449bc) != 0)
        {
            return port_return(&port, eax, entry->edx);
        }
    }
    eax = CALL(0x4ac8f0, actor, 0);
#undef CALL
    return port_return(&port, eax, entry->edx);
}

/* Original 0x45a290: the title letter eax counting down the fight: when its period is up (0x4ac500,
 * 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place (0x4ad060) and size (0x4ad260)
 * read; within the distance +0x30 its fade +0x44 is 16 less 16 * the travelled +0x2a / +0x30, else
 * none (and +0x48 0); its travel +0x2a less +0x32 a step (0 once below 0), its move made (0x4ad530)
 * and its place +8/+0xa set. At the end of its travel it is reset to its start +0x2c/+0x2e, faded
 * in (+0x44 16, +0x4a 150, +0x4c 5), the sound 0x4f81c4 played at 50 (0x4171e0, 0x417220) and
 * the letter handed 0x45a3e0 (0x4ac8f0). 0x457890 always follows. edx kept. */
uint32_t vertrix_port_title_letter_fight_count_45a290(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t distance;
    uint32_t steps;
    uint32_t place;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    distance = (uint32_t)((int32_t)port_u32(&port, letter, 0x2e) >> 16);
    port_call_with(&port, 0x4ac500, letter, entry->edx, entry->ebx, letter, entry->esi, distance,
                   ebp);
    eax = port_call_with(&port, 0x4ac520, letter, vertrix_lift_edx, entry->ebx, letter, entry->esi,
                         distance, ebp);
    if (eax != 1)
    {
        eax = port_call_with(&port, 0x457890, letter, vertrix_lift_edx, entry->ebx, letter,
                             entry->esi, distance, ebp);
        return port_return(&port, eax, entry->edx);
    }
    steps = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, entry->ebx, letter,
                           entry->esi, distance, ebp);
    port_call_with(&port, 0x4ac5b0, letter, steps, entry->ebx, letter, steps, distance, ebp);
    port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebp - 0x18, letter, steps, distance,
                   ebp);
    port_call_with(&port, 0x4ad260, letter, ebp - 0x1c, ebp - 0x18, letter, steps, distance, ebp);
    place = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
    if (place <= distance)
    {
        LiftFlags flags = {0};
        uint32_t edx = 0;
        eax = place << 4;
        lift_div1(32, distance, &eax, &edx, &flags);
        eax = 0x10 - eax;
        if ((int32_t)eax >= 0x10)
        {
            eax = 0x10;
        }
        port_set8(&port, letter, 0x44, eax);
    }
    else
    {
        port_set8(&port, letter, 0x44, 0);
        port_set16(&port, letter, 0x48, 0);
    }
    port_set16(&port, letter, 0x2a,
               port_u16(&port, letter, 0x2a) - port_u16(&port, letter, 0x32) * steps);
    if ((int32_t)port_u32(&port, letter, 0x28) < 0)
    {
        port_set16(&port, letter, 0x2a, 0);
    }
    port_call_with(&port, 0x4ad530, letter, steps, place, letter, steps, distance, ebp);
    port_set16(&port, letter, 8, port_u32(&port, ebp, -0x1cu));
    port_set16(&port, letter, 0xa, port_u32(&port, ebp, -0x18u));
    if (place == 0)
    {
        port_set16(&port, letter, 8, port_u16(&port, letter, 0x2c));
        port_set16(&port, letter, 0xa, port_u16(&port, letter, 0x2e));
        port_set8(&port, letter, 0x44, 0x10);
        port_call_with(&port, 0x4171e0, port_u32(&port, 0, 0x4f81c4), 0x32, place, letter, steps,
                       distance, ebp);
        port_call_with(&port, 0x417220, port_u32(&port, 0, 0x4f81c4), 0x32, place, letter, steps,
                       distance, ebp);
        port_set16(&port, letter, 0x48, 0);
        port_set16(&port, letter, 0x4a, 0x96);
        port_set16(&port, letter, 0x4c, 5);
        port_call_with(&port, 0x4ac8f0, letter, 0x45a3e0, place, letter, steps, distance, ebp);
    }
    eax = port_call_with(&port, 0x457890, letter, vertrix_lift_edx, place, letter, steps, distance,
                         ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x424230: under the guard record 0x5143a0 (three frame strings 0x4ca070) the screen eax
 * given the current slot's text 0x5332c0 by 0x4fc290 (0x45f540), or when 0x45f590 refuses it the
 * level 0x513c1a's name 0x5334a0 by 0x4fc398: 0x41a960 with it, 0x41aa20, 0x41aaa0, the slot's
 * picture 0x533cd0 (0x4191b0 with 1), +0xc8 1, the handlers 0x4237d0 (0x418840) and 0x424360
 * (0x418820), then 0x4cda10. eax the restored chain, edx kept. */
uint32_t vertrix_port_screen_slot_open_424230(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t record = ebp - 0x34;
    uint32_t text = ebp - 0x138;
    uint32_t ebx = 0x5143a0;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x5143a0);
    port_set32(&port, ebp, -0x28u, 0);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, screen, 0, 1, ebp)
    CALL(0x4ca070, ebp - 0x20, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 1);
    CALL(0x4ca070, ebp - 0x1c, vertrix_lift_edx);
    port_set32(&port, ebp, -0x28u, 2);
    CALL(0x4ca070, ebp - 0x18, vertrix_lift_edx);
    port_set32(&port, ebp, -0x28u, 3);
    ebx = port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x5332c0);
    CALL(0x45f540, text, 0x4fc290);
    eax = CALL(0x45f590, text, vertrix_lift_edx);
    if (eax == 0)
    {
        ebx = port_u32(&port, port_u8(&port, 0, 0x513c1a) * 4, 0x5334a0);
        CALL(0x45f540, text, 0x4fc398);
    }
    CALL(0x41a960, screen, text);
    CALL(0x41aa20, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, vertrix_lift_edx);
    ebx = 1;
    CALL(0x4191b0, screen, port_u32(&port, port_u32(&port, 0, 0x532a70) * 4, 0x533cd0));
    port_set8(&port, screen, 0xc8, 1);
    CALL(0x418840, screen, 0x4237d0);
    eax = CALL(0x418820, screen, 0x424360);
    CALL(0x4cda10, eax, vertrix_lift_edx);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x427ae0: the board eax judging the actor edx against its partner +0x3b0: both
 * players' +0x15c regions refreshed (0x432820) and their 65-byte maps +0x1de copied into the
 * frame, merged into the board's map +0x1c5 (0x428110), measured with the board's +0x164 and both
 * players' +0x178/+0x17c/+0x180 (0x427c10) and scored (0x428610 with +0x160 and 0x4fb500): eax 1
 * for a score below 3, 0 up to 5, else -1. */
uint32_t vertrix_port_object_compare_regions_427ae0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xa8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t board = entry->eax;
    uint32_t actor = entry->edx;
    uint32_t partner;
    uint32_t mine;
    uint32_t theirs;
    uint32_t map;
    uint32_t index;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, board);
    port_set32(&port, ebp, -0x18u, actor);
    partner = port_u32(&port, actor, 0x3b0);
    port_set32(&port, ebp, -0x1cu, partner);
    mine = port_u32(&port, actor, 0x15c);
    theirs = port_u32(&port, partner, 0x15c);
    port_call_with(&port, 0x432820, mine, theirs, entry->ebx, 0x41, mine, ebp - 0xa4, ebp);
    port_call_with(&port, 0x432820, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, 0x41,
                   mine + 0x1de, ebp - 0xa4, ebp);
    theirs = vertrix_lift_edx;
    for (index = 0; index < 0x41 && !port.env.failed; index++)
    {
        port_set8(&port, ebp - 0xa4 + index, 0, port_u8(&port, mine + 0x1de + index, 0));
    }
    for (index = 0; index < 0x41 && !port.env.failed; index++)
    {
        port_set8(&port, ebp - 0x60 + index, 0, port_u8(&port, theirs + 0x1de + index, 0));
    }
    map = board + 0x1c5;
    port_call_with(&port, 0x428110, board, ebp - 0xa4, ebp - 0x60, map, map, ebp - 0x60, ebp);
    {
        uint32_t args[5] = {port_u32(&port, partner, 0x178), port_u32(&port, actor, 0x180) - 0xc,
                            port_u32(&port, partner, 0x180) - 0xc, port_u32(&port, board, 0x164),
                            map};
        vertrix_lift_in_esi = map;
        vertrix_lift_in_edi = ebp - 0x60;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x427c10, board, port_u32(&port, actor, 0x17c),
                            port_u32(&port, partner, 0x17c), port_u32(&port, actor, 0x178), args,
                            5);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    }
    eax = port_call_with(&port, 0x428610, board, map, port_u32(&port, board, 0x160), 0x4fb500, map,
                         ebp - 0x60, ebp) &
          0xff;
    if ((int32_t)eax < 3)
    {
        eax = 1;
    }
    else if ((int32_t)eax <= 5)
    {
        eax = 0;
    }
    else
    {
        eax = 0xffffffffu;
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

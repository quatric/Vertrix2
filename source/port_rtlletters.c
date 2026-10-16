#include "port_rtlletters.h"

/* Title letters flying in and counting the waves, and the JPEG coefficient controller. */

/* Original 0x45a4f0: the title letter eax flying in to the fight: when its period is up (0x4ac500,
 * 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place (0x4ad060) and size (0x4ad260)
 * read; within the distance +0x30 its fade +0x44 is 16 less 16 * the travelled +0x2a / +0x30, else
 * none (and +0x48 0); its corner +0xe/+0x16 set to the place less half the extent 0x4b14c0 gives,
 * its travel +0x2a advanced by +0x32 a step and its move made (0x4ad530); a letter with no fade
 * left is stopped (0x4ac8f0) and the fight flag 0x532a40 set. edx kept. */
uint32_t vertrix_port_title_letter_fight_fly_45a4f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t letter = entry->eax;
    uint32_t distance;
    uint32_t steps;
    uint32_t eax;
    uint32_t edx;
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
        return port_return(&port, eax, entry->edx);
    }
    steps = port_call_with(&port, 0x4ac540, letter, vertrix_lift_edx, entry->ebx, letter,
                           entry->esi, distance, ebp);
    port_call_with(&port, 0x4ac5b0, letter, steps, entry->ebx, letter, steps, distance, ebp);
    port_call_with(&port, 0x4ad060, letter, vertrix_lift_edx, ebp - 0x1c, letter, steps, distance,
                   ebp);
    port_call_with(&port, 0x4ad260, letter, ebp - 0x18, ebp - 0x1c, letter, steps, distance, ebp);
    eax = (uint32_t)((int32_t)port_u32(&port, letter, 0x28) >> 16);
    if (eax <= distance)
    {
        LiftFlags flags = {0};
        edx = 0;
        eax <<= 4;
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
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4b14c0, letter, ebp - 0x24, ebp - 0x20, letter, steps, distance, ebp);
    edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) -
          (port_u32(&port, ebp, -0x24u) >> 1);
    port_set16(&port, letter, 0xe, edx);
    eax = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu) -
          (port_u32(&port, ebp, -0x20u) >> 1);
    port_set16(&port, letter, 0x16, eax);
    port_set16(&port, letter, 0x2a,
               port_u16(&port, letter, 0x2a) + port_u16(&port, letter, 0x32) * steps);
    eax = port_call_with(&port, 0x4ad530, letter, steps, ebp - 0x20, letter, steps, distance, ebp);
    if (port_u8(&port, letter, 0x44) == 0)
    {
        eax = port_call_with(&port, 0x4ac8f0, letter, 0, ebp - 0x20, letter, 1, distance, ebp);
        port_set32(&port, 0, 0x532a40, 1);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x45a620: the title letter eax counting down the wave: when its period is up (0x4ac500,
 * 0x4ac520) its steps (0x4ac540) are taken (0x4ac5b0), its place (0x4ad060) and size (0x4ad260)
 * read; within the distance +0x30 its fade +0x44 is 16 less 16 * the travelled +0x2a / +0x30, else
 * none (and +0x48 0); its travel +0x2a less +0x32 a step (0 once below 0), its move made (0x4ad530)
 * and its place +8/+0xa set. At the end of its travel it is reset to its start +0x2c/+0x2e, faded
 * in (+0x44 16, +0x4a 50, +0x4c 2) and handed 0x45a750 (0x4ac8f0). 0x457890 always follows. edx
 * kept. */
uint32_t vertrix_port_title_letter_wave_count_45a620(PORT_SIGNATURE)
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
        port_set8(&port, letter, 0x44, 0x10);
        port_set16(&port, letter, 0x48, 0);
        port_set16(&port, letter, 0x4a, 0x32);
        port_set16(&port, letter, 8, port_u16(&port, letter, 0x2c));
        port_set16(&port, letter, 0xa, port_u16(&port, letter, 0x2e));
        port_set16(&port, letter, 0x4c, 2);
        port_call_with(&port, 0x4ac8f0, letter, 0x45a750, place, letter, steps, distance, ebp);
    }
    eax = port_call_with(&port, 0x457890, letter, vertrix_lift_edx, place, letter, steps, distance,
                         ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4bb040: the JPEG coefficient controller of the decoder eax (0x74 bytes from the
 * memory manager +4's method 0), kept at +0x1ac with its start and input methods. With a full
 * buffer (edx set) each component of +0xd8 (0x54 bytes each, +0x24 of them) gets a virtual block
 * array (the manager's +0x14) of its width and height in blocks rounded up to its sampling
 * (0x4c9840; three times the height when progressive +0xdc) and the buffered methods; otherwise
 * ten 128-byte blocks (the manager's +4) and the single-pass methods. eax the controller. */
uint32_t vertrix_port_jpeg_coef_controller_init_4bb040(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t memory;
    uint32_t controller;
    uint32_t blocks;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, decoder);
    memory = port_u32(&port, decoder, 4);
    controller = port_call_with(&port, port_u32(&port, memory, 0), decoder, 1, 0x74, entry->ecx,
                                entry->edx, memory, ebp);
    port_set32(&port, ebp, -0x20u, controller);
    port_set32(&port, decoder, 0x1ac, controller);
    port_set32(&port, controller, 0, 0x4b9dd0);
    port_set32(&port, controller, 8, 0x4b9de0);
    port_set32(&port, controller, 0x70, 0);
    if (entry->edx != 0)
    {
        uint32_t component = port_u32(&port, decoder, 0xd8);
        uint32_t ecx = port_u32(&port, decoder, 0x24);
        port_set32(&port, ebp, -0x1cu, 0);
        if ((int32_t)ecx > 0)
        {
            port_set32(&port, ebp, -0x18u, controller);
            do
            {
                uint32_t progressive = port_u32(&port, decoder, 0xdc);
                uint32_t access = port_u32(&port, component, 0xc);
                uint32_t rows;
                uint32_t columns;
                uint32_t slot;
                if (progressive != 0)
                {
                    access *= 3;
                }
                memory = port_u32(&port, decoder, 4);
                rows = port_call_with(&port, 0x4c9840, port_u32(&port, component, 0x20),
                                      port_u32(&port, component, 0xc), progressive, ecx, component,
                                      memory, ebp);
                columns =
                    port_call_with(&port, 0x4c9840, port_u32(&port, component, 0x1c),
                                   port_u32(&port, component, 8), 1, ecx, component, memory, ebp);
                component += 0x54;
                {
                    uint32_t args[2] = {rows, access};
                    vertrix_lift_in_esi = component;
                    vertrix_lift_in_edi = memory;
                    vertrix_lift_in_ebp = ebp;
                    eax = lift_call_arguments(&port.env, port_u32(&port, memory, 0x14), decoder, 1,
                                              1, columns, args, 2);
                    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
                }
                slot = port_u32(&port, ebp, -0x18u);
                port_set32(&port, slot, 0x48, eax);
                port_set32(&port, ebp, -0x18u, slot + 4);
                port_set32(&port, ebp, -0x1cu, port_u32(&port, ebp, -0x1cu) + 1);
                ecx = port_u32(&port, decoder, 0x24);
            } while ((int32_t)port_u32(&port, ebp, -0x1cu) < (int32_t)ecx && !port.env.failed);
        }
        controller = port_u32(&port, ebp, -0x20u);
        port_set32(&port, controller, 4, 0x4ba220);
        port_set32(&port, controller, 0xc, 0x4ba470);
        port_set32(&port, controller, 0x10, controller + 0x48);
        return port_return(&port, controller, controller + 0x48);
    }
    blocks = controller;
    {
        uint32_t block;
        unsigned index;
        memory = port_u32(&port, decoder, 4);
        block = port_call_with(&port, port_u32(&port, memory, 4), decoder, 1, 0x500, entry->ecx,
                               memory, controller, ebp);
        for (index = 0; index < 10; index++)
        {
            port_set32(&port, controller, 0x20 + index * 4, block + index * 0x80);
        }
    }
    controller = port_u32(&port, ebp, -0x20u);
    port_set32(&port, controller, 4, 0x4ba210);
    port_set32(&port, controller, 0xc, 0x4b9f70);
    port_set32(&port, controller, 0x10, 0);
    return port_return(&port, controller, blocks + 0x28);
}

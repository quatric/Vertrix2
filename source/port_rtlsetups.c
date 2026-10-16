#include "port_rtlsetups.h"

/* Case folds, game step checks, item toggles, decoder table set-up and digit runs. */

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

/* Original 0x4eab80: the character at eax folded: copied into the frame (0x4e7120, cut at its lead
 * byte length by 0x4e6f30 with the byte from that call's edx); a lead byte under the code page
 * 0x3a4 with multibyte text on goes to 0x4eb250, else the frame is folded by 0x4f1908 (one
 * character) and read back by 0x4e3a50. edx kept. */
uint32_t vertrix_port_rtl_char_fold_4eab80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x10;
    uint32_t text = entry->eax;
    uint32_t eax;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0xc, entry->ebx);
    port_set32(&port, esp, 8, entry->ecx);
    port_set32(&port, esp, 4, entry->edx);
    port_call_with(&port, 0x4e7120, text, esp, text, entry->ecx, entry->esi, entry->edi,
                   entry->ebp);
    eax = port_call_with(&port, 0x4e6f30, esp, vertrix_lift_edx & 0xffffff00u, text, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    port_set8(&port, esp + eax, 0, vertrix_lift_edx);
    if (port_u32(&port, 0, 0x50a820) == 0x3a4 && port_u32(&port, 0, 0x5c8950) != 0 &&
        (port_u8(&port, port_u8(&port, esp, 0), 0x5c8961) & 1) != 0)
    {
        eax = port_call_with(&port, 0x4eb250, text, vertrix_lift_edx, text, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
        return port_return(&port, eax, port_u32(&port, esp, 4));
    }
    args[0] = esp;
    args[1] = 1;
    call_frame(&port, 0x4f1908, esp, vertrix_lift_edx, text, entry->ecx, entry->esi, entry->edi,
               entry->ebp, args, 2);
    args[0] = port_u32(&port, esp, 0);
    eax = call_frame(&port, 0x4e3a50, esp, vertrix_lift_edx, text, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 1);
    return port_return(&port, eax, port_u32(&port, esp, 4));
}

/* Original 0x443ab0: the game eax's step: 0x5448f0 set, 0x4ac500 and 0x4ac520; when that matches
 * its edx, 0x4ac540 (kept in 0x5448f4), 0x4ac5b0 and 0x4acc10 of it decide 0x5448f0; a clear
 * 0x5448f0 ends with 0x4ac8f0 of 0. edx kept. */
uint32_t vertrix_port_game_step_check_443ab0(PORT_SIGNATURE)
{
    Port port;
    uint32_t game = entry->eax;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x5448f0, 1);
    port_call_with(&port, 0x4ac500, game, 1, entry->ebx, game, entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4ac520, game, vertrix_lift_edx, entry->ebx, game, entry->esi,
                         entry->edi, entry->ebp);
    if (eax == vertrix_lift_edx)
    {
        eax = port_call_with(&port, 0x4ac540, game, vertrix_lift_edx, entry->ebx, game, entry->esi,
                             entry->edi, entry->ebp);
        port_set32(&port, 0, 0x5448f4, eax);
        port_call_with(&port, 0x4ac5b0, game, vertrix_lift_edx, entry->ebx, game, entry->esi,
                       entry->edi, entry->ebp);
        eax = port_call_with(&port, 0x4acc10, game, port_u32(&port, 0, 0x5448f4), entry->ebx, game,
                             entry->esi, entry->edi, entry->ebp);
        port_set32(&port, 0, 0x5448f0, eax);
    }
    if (port_u32(&port, 0, 0x5448f0) == 0)
    {
        eax = port_call_with(&port, 0x4ac8f0, game, 0, entry->ebx, game, entry->esi, entry->edi,
                             entry->ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x452370: the item +0x15c of eax told by its class (+0x158) method +4 whether it is on
 * (1 unless the owner +0x3b0 has +0x4c5 and +0x3f4 set); its answer edx 1 goes on to 0x43bbf0.
 * edx kept. */
uint32_t vertrix_port_item_toggle_452370(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t owner;
    uint32_t item;
    uint32_t ebx;
    uint32_t edx = 0;
    uint32_t methods;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    owner = port_u32(&port, self, 0x3b0);
    ebx = (entry->ebx & 0xffffff00u) | port_u8(&port, owner, 0x4c5);
    item = port_u32(&port, self, 0x15c);
    if ((ebx & 0xff) == 0 || port_u32(&port, owner, 0x3f4) == 0)
    {
        edx = 1;
    }
    methods = port_u32(&port, item, 0x158);
    eax = port_call_with(&port, port_u32(&port, methods, 4), item, edx, ebx, methods, self,
                         entry->edi, entry->ebp);
    if (vertrix_lift_edx == 1)
    {
        eax = port_call_with(&port, 0x43bbf0, self, 1, ebx, methods, self, entry->edi, entry->ebp);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c31a0: the decoder eax's quantizer (0x40 bytes, pool 1, from the memory manager +4's
 * method +0) kept in +0x1bc with its method 0x4c23f0 and four tables +0x2c cleared, then its
 * colour index table (+0xa0, 0x100 bytes a component +0x24) filled with -1. edx kept. */
uint32_t vertrix_port_jpeg_quantizer_init_4c31a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t memory;
    uint32_t object;
    uint32_t place;
    uint32_t eax;
    uint32_t components;
    uint32_t row;
    port_open(&port, calls, services, globals, entry);
    memory = port_u32(&port, cinfo, 4);
    object = port_call_with(&port, port_u32(&port, memory, 0), cinfo, 1, 0x40, memory, cinfo,
                            entry->edi, entry->ebp);
    port_set32(&port, cinfo, 0x1bc, object);
    port_set32(&port, object, 0, 0x4c23f0);
    for (place = object + 4; place != object + 0x14 && !port.env.failed; place += 4)
    {
        port_set32(&port, place, 0x28, 0);
    }
    memory = port_u32(&port, cinfo, 4);
    eax = port_call_with(&port, port_u32(&port, memory, 0), cinfo, 1,
                         port_u32(&port, cinfo, 0x24) << 8, memory, cinfo, entry->edi, entry->ebp);
    port_set32(&port, cinfo, 0xa0, eax);
    place = eax;
    components = port_u32(&port, cinfo, 0x24);
    if ((int32_t)components > 0)
    {
        row = 0;
        do
        {
            for (eax = 1; eax <= 0x40 && !port.env.failed; eax++)
            {
                port_set32(&port, place, 0, 0xffffffffu);
                place += 4;
            }
            eax = 0x40;
            row++;
        } while ((int32_t)row < (int32_t)port_u32(&port, cinfo, 0x24) && !port.env.failed);
    }
    return port_return(&port, eax, entry->edx);
}

/* `al` (with ah) as two decimal digits at `place` (`div cl` by ten unless below ten). */
static uint32_t two_digits(Port *port, uint32_t eax, uint32_t *edx, uint32_t place)
{
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    if ((eax & 0xff) < 0xa)
    {
        eax = (eax & 0xffff0000u) | ((eax & 0xff) << 8) | ((eax >> 8) & 0xff);
    }
    else
    {
        lift_div1(8, 0xa, &eax, edx, &flags);
    }
    eax = (eax & 0xffff00ffu) | ((((eax >> 8) + 0x30) & 0xff) << 8);
    eax = (eax & 0xffffff00u) | ((eax + 0x30) & 0xff);
    port_set8(port, place, 0, eax);
    port_set8(port, place, 1, eax >> 8);
    return eax;
}

/* Original 0x4ecf33: the value eax as decimal digits at ebx: the ten-thousands by 0x4ecf49, the
 * hundreds of the rest by 0x4ecf60, then its last two digits. eax as left, edx 0x4ecf60's. */
uint32_t vertrix_port_rtl_six_digits_4ecf33(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = 0;
    uint32_t low;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open(&port, calls, services, globals, entry);
    if (eax < 0x2710)
    {
        edx = eax;
        eax = 0;
    }
    else
    {
        lift_div1(32, 0x2710, &eax, &edx, &flags);
    }
    low = edx;
    port_call_with(&port, 0x4ecf49, eax, edx, entry->ebx, 0x2710, entry->esi, entry->edi,
                   entry->ebp);
    eax = low;
    edx = 0;
    if (eax < 0x64)
    {
        edx = eax;
        eax = 0;
    }
    else
    {
        lift_div1(16, 0x64, &eax, &edx, &flags);
    }
    low = edx;
    port_call_with(&port, 0x4ecf60, eax, edx, entry->ebx, 0x64, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    eax = two_digits(&port, low, &edx, entry->ebx);
    return port_return(&port, eax, edx);
}

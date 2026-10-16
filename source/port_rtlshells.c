#include "port_rtlshells.h"

/* The runtime library's destructor shells and small decoder helpers. */

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

/* A destructor shell for the object eax with the flags dl: bit 2 destroys an array (0x4ccb9f with
 * the type `array`, then 0x4ca040); otherwise the class `own` is set, `body` runs under the guard
 * record `guard`, the base class 0x517454 is set and bit 1 frees it (0x4ca050). eax the object. */
static uint32_t destroy(PORT_SIGNATURE, uint32_t array, uint32_t own, uint32_t guard, uint32_t body)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x34;
    uint32_t self = entry->eax;
    uint32_t edx = entry->edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x30, entry->ecx);
    if ((edx & 4) != 0)
    {
        uint32_t eax;
        port_set32(&port, esp, 0x20, 1);
        port_set32(&port, esp, 0, self);
        eax = port_call_with(&port, 0x4ccb9f, self, array, entry->ebx, self, entry->esi, entry->edi,
                             entry->ebp);
        port_set32(&port, esp, 0x20, 0);
        port_call_with(&port, 0x4ca040, eax, vertrix_lift_edx, entry->ebx, self, entry->esi,
                       entry->edi, entry->ebp);
        return port_return(&port, self, vertrix_lift_edx);
    }
    port_set32(&port, self, 0, own);
    port_set32(&port, esp, 0x24, self);
    port_set8(&port, esp, 0x28, edx);
    port_set32(&port, esp, 0x14, port.env.chain);
    port.env.chain = esp + 0x14;
    port_set32(&port, esp, 0x18, 0x4ec1ec);
    port_set32(&port, esp, 0x1c, guard);
    port_set32(&port, esp, 0x20, 3);
    port_call_with(&port, body, self, edx, entry->ebx, self, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, esp, 0x20, 0);
    port_set32(&port, self, 0, 0x517454);
    if ((edx & 2) != 0)
    {
        port_call_with(&port, 0x4ca050, self, edx, entry->ebx, self, entry->esi, entry->edi,
                       entry->ebp);
        edx = vertrix_lift_edx;
    }
    port.env.chain = port_u32(&port, esp, 0x14);
    return port_return(&port, self, edx);
}

/* Original 0x4d83f0: destroy with 0x519a10, 0x51a024, 0x519fc8 and 0x4d83c0. */
uint32_t vertrix_port_rtl_destroy_4d83f0(PORT_SIGNATURE)
{
    return destroy(calls, services, globals, entry, 0x519a10, 0x51a024, 0x519fc8, 0x4d83c0);
}

/* Original 0x4defd0: destroy with 0x51bb70, 0x51bb54, 0x51baf8 and 0x4def90. */
uint32_t vertrix_port_rtl_destroy_4defd0(PORT_SIGNATURE)
{
    return destroy(calls, services, globals, entry, 0x51bb70, 0x51bb54, 0x51baf8, 0x4def90);
}

/* Original 0x4ee980: destroy with 0x51c2f0, 0x51c2d4, 0x51c278 and 0x4ee910. */
uint32_t vertrix_port_rtl_destroy_4ee980(PORT_SIGNATURE)
{
    return destroy(calls, services, globals, entry, 0x51c2f0, 0x51c2d4, 0x51c278, 0x4ee910);
}

/* Original 0x4e62e0: the character eax converted to one wide character in the frame (0x4f1d00 in
 * the code page 0x50a820, flags 0x200) and that taken as eax, -1 on failure; a zero character
 * gives 0. */
uint32_t vertrix_port_rtl_char_widen_4e62e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 8;
    uint32_t args[8];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 4, entry->ecx);
    port_set32(&port, esp, 0, entry->edx);
    if (entry->eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = port_u32(&port, 0, 0x50a820);
    args[1] = 0x200;
    args[2] = esp;
    args[3] = 1;
    args[4] = entry->eax;
    args[5] = 2;
    args[6] = 0;
    args[7] = 0;
    eax = call_frame(&port, 0x4f1d00, esp, args[0], entry->ebx, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 8);
    return port_return(&port, eax != 0 ? eax : 0xffffffffu, vertrix_lift_edx);
}

/* Original 0x4b9cb0: the decoder eax's source (+0x18; pointer +0, bytes left +4) skips edx bytes,
 * refilling (0x4b9c20) while more are asked than are left; eax the bytes left after. */
uint32_t vertrix_port_jpeg_skip_input_4b9cb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t source;
    uint32_t edx = entry->edx;
    uint32_t left;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, cinfo, 0x18);
    if ((int32_t)edx <= 0)
    {
        return port_return(&port, cinfo, edx);
    }
    for (;;)
    {
        left = port_u32(&port, source, 4);
        if ((int32_t)edx <= (int32_t)left || port.env.failed)
        {
            break;
        }
        port_call_with(&port, 0x4b9c20, cinfo, edx, cinfo, source, left, entry->edi, entry->ebp);
        edx = vertrix_lift_edx - left;
    }
    port_set32(&port, source, 0, port_u32(&port, source, 0) + edx);
    eax = port_u32(&port, source, 4) - edx;
    port_set32(&port, source, 4, eax);
    return port_return(&port, eax, edx);
}

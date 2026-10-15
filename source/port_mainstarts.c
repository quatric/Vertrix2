#include "port_mainstarts.h"

/* The image decoder's main buffer pass start. */

/* `cdq; idiv divisor`: the quotient, the dividend unchanged when it would fault. */
static uint32_t divide(uint32_t dividend, uint32_t divisor)
{
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    uint32_t eax = dividend;
    uint32_t edx = (uint32_t)((int32_t)dividend >> 31);
    lift_idiv1(32, divisor, &eax, &edx, &flags);
    return eax;
}

/* Original 0x4bd750: the main buffer controller +0x1a8 of the decoder eax starts pass edx. Pass 2
 * takes 0x4bddc0 (edx 2); another pass than 0 is error 4 (the error manager's method +0). Pass 0
 * takes 0x4bd950, or with context rows (the upsampler +0x1c4's +8) 0x4bd9e0 and the funny
 * pointers: for each component (+0x24 of them, 0x54 bytes each at +0xd8) the row group (factor
 * +0xc times scaled size +0x24 over +0x13c, M) copies the buffer (+8 on) into both lists (+0x38,
 * +0x3c) for M+2 groups, swaps the last two groups of the second and makes the first's -1st group
 * its first row; +0x40, +0x44 and +0x4c are cleared. Pass 0 clears +0x30 and +0x34 and gives eax
 * the controller. */
uint32_t vertrix_port_main_start_pass_4bd750(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t main;
    uint32_t controller;
    uint32_t edx;
    uint32_t error;
    uint32_t eax;
    uint32_t groups;
    uint32_t group;
    uint32_t component;
    uint32_t place;
    uint32_t first;
    uint32_t second;
    uint32_t buffer;
    uint32_t ci;
    uint32_t i;
    port_open(&port, calls, services, globals, entry);
    main = port_u32(&port, cinfo, 0x1a8);
    if (mode != 0)
    {
        if (mode == 2)
        {
            port_set32(&port, main, 4, 0x4bddc0);
            return port_return(&port, cinfo, mode);
        }
        port_set32(&port, port_u32(&port, cinfo, 0), 0x14, 4);
        error = port_u32(&port, cinfo, 0);
        eax = port_call_with(&port, port_u32(&port, error, 0), cinfo, error, entry->ebx, main,
                             entry->esi, entry->edi, entry->esp - 4);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    edx = port_u32(&port, cinfo, 0x1c4);
    if (port_u32(&port, edx, 8) == 0)
    {
        port_set32(&port, main, 4, 0x4bd950);
    }
    else
    {
        port_set32(&port, main, 4, 0x4bd9e0);
        controller = port_u32(&port, cinfo, 0x1a8);
        groups = port_u32(&port, cinfo, 0x13c);
        component = port_u32(&port, cinfo, 0xd8);
        edx = component;
        ci = 0;
        if ((int32_t)port_u32(&port, cinfo, 0x24) > 0)
        {
            place = controller;
            do
            {
                group = divide(port_u32(&port, component, 0xc) * port_u32(&port, component, 0x24),
                               port_u32(&port, cinfo, 0x13c));
                first = port_u32(&port, port_u32(&port, controller, 0x38) + ci * 4, 0);
                second = port_u32(&port, port_u32(&port, controller, 0x3c) + ci * 4, 0);
                buffer = port_u32(&port, place, 8);
                for (i = 0; (int32_t)i < (int32_t)(group * (groups + 2)) && !port.env.failed; i++)
                {
                    uint32_t row = port_u32(&port, buffer + i * 4, 0);
                    port_set32(&port, second + i * 4, 0, row);
                    port_set32(&port, first + i * 4, 0, row);
                }
                for (i = 0; (int32_t)i < (int32_t)(group * 2) && !port.env.failed; i++)
                {
                    port_set32(&port, second + (group * (groups - 2) + i) * 4, 0,
                               port_u32(&port, buffer + (group * groups + i) * 4, 0));
                    port_set32(&port, second + (group * groups + i) * 4, 0,
                               port_u32(&port, buffer + (group * (groups - 2) + i) * 4, 0));
                }
                for (i = 0; (int32_t)i < (int32_t)group && !port.env.failed; i++)
                {
                    port_set32(&port, first - group * 4 + i * 4, 0, port_u32(&port, first, 0));
                }
                place += 4;
                component += 0x54;
                ci++;
                edx = cinfo;
            } while ((int32_t)ci < (int32_t)port_u32(&port, cinfo, 0x24) && !port.env.failed);
        }
        port_set32(&port, main, 0x40, 0);
        port_set32(&port, main, 0x44, 0);
        port_set32(&port, main, 0x4c, 0);
    }
    port_set32(&port, main, 0x30, 0);
    port_set32(&port, main, 0x34, 0);
    return port_return(&port, main, edx);
}

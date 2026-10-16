#include "port_rtldraws.h"

/* Depth-ordered drawing, the file dialog and the JPEG DC refinement. */

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

/* Original 0x48c860: the file dialog of the object eax (its interface +0x1bc): with the current
 * folder (0x4dabbe into the frame), the object's texts 0x510c9d, 0x510ca6 and 0x510cb3 and the
 * folder (0x47fc10) put in a 0x38-byte request filled by its method +0x20 of +0x1c8, the request
 * shown by the interface's method +0x10. eax 0 without a folder. edx kept. */
uint32_t vertrix_port_file_dialog_open_48c860(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x974
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t eax;
    uint32_t vtable;
    uint32_t dialog;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    if (port_u32(&port, object, 0x1bc) == 0)
    {
        return port_return(&port, object, entry->edx);
    }
    eax = port_call_with(&port, 0x4dabbe, ebp - 0x150, 0x104, entry->ebx, entry->ecx, entry->esi,
                         object, ebp);
    if (eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call_with(&port, 0x47fc10, object, ebp - 0x768, ebp - 0x150, 0xffffffffu, entry->esi,
                   object, ebp);
    port_call_with(&port, 0x47fc10, object, ebp - 0x970, 0x510c9d, 0xffffffffu, entry->esi, object,
                   ebp);
    port_call_with(&port, 0x47fc10, object, ebp - 0x560, 0x510ca6, 0xffffffffu, entry->esi, object,
                   ebp);
    port_call_with(&port, 0x47fc10, object, ebp - 0x358, 0x510cb3, 0xffffffffu, entry->esi, object,
                   ebp);
    port_call_with(&port, 0x4eb5c0, ebp - 0x4c, 0, 0x38, 0x38, entry->esi, object, ebp);
    port_set32(&port, ebp, -0x4cu, 0x38);
    vtable = port_u32(&port, object, 0x1c8);
    port_call_with(&port, port_u32(&port, vtable, 0x20), object, vtable, 0x38, 0x38, ebp - 0x44,
                   object, ebp);
    port_set32(&port, ebp, -0x2cu, ebp - 0x768);
    port_set32(&port, ebp, -0x28u, ebp - 0x358);
    port_set32(&port, ebp, -0x34u, ebp - 0x970);
    port_set32(&port, ebp, -0x24u, ebp - 0x560);
    port_set32(&port, ebp, -0x20u, ebp - 0x768);
    dialog = port_u32(&port, object, 0x1bc);
    vtable = port_u32(&port, dialog, 0);
    {
        uint32_t args[3] = {dialog, ebp - 0x4c, 0};
        vertrix_lift_in_esi = ebp - 0x44;
        vertrix_lift_in_edi = object;
        vertrix_lift_in_ebp = ebp;
        eax = lift_call_arguments(&port.env, port_u32(&port, vtable, 0x10), dialog, ebp - 0x4c,
                                  vtable, 0x38, args, 3);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c2c50: the JPEG progressive DC refinement of the decoder eax for the MCU blocks edx:
 * after a restart when one is due (0x4c26f0), one bit a block from the entropy +0x1bc's bit buffer
 * (+0xc, +0x10 bits; refilled by 0x4bbf30 from the source +0x18) sets the bit 1 << +0x19c of its
 * DC coefficient; the buffer and source kept and the restart count +0x28 less one. eax 1, or 0 when
 * the input is suspended. edx the bit buffer. */
uint32_t vertrix_port_jpeg_decode_dc_refine_4c2c50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t edi = entry->edx;
    uint32_t entropy;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esi = 0;
    uint32_t source;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x18u, decoder);
    entropy = port_u32(&port, decoder, 0x1bc);
    port_set32(&port, ebp, -0x20u, entropy);
    port_set32(&port, ebp, -0x1cu, port_shl(1, port_u8(&port, decoder, 0x19c)));
    if (port_u32(&port, decoder, 0x114) != 0 && port_u32(&port, entropy, 0x28) == 0)
    {
        uint32_t ecx = (decoder & 0xffffff00u) | port_u8(&port, decoder, 0x19c);
        if (port_call_with(&port, 0x4c26f0, decoder, entry->edx, entry->ebx, ecx, entry->esi, edi,
                           ebp) == 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
    }
    port_set32(&port, ebp, -0x24u, decoder);
    source = port_u32(&port, decoder, 0x18);
    port_set32(&port, ebp, -0x34u, port_u32(&port, source, 0));
    port_set32(&port, ebp, -0x30u, port_u32(&port, source, 4));
    edx = port_u32(&port, entropy, 0xc);
    ebx = port_u32(&port, entropy, 0x10);
    if ((int32_t)port_u32(&port, decoder, 0x164) > 0)
    {
        do
        {
            uint32_t block = port_u32(&port, edi, 0);
            port_set32(&port, ebp, -0x14u, block);
            if ((int32_t)ebx < 1)
            {
                if (port_call_with(&port, 0x4bbf30, ebp - 0x34, edx, ebx, 1, esi, edi, ebp) == 0)
                {
                    return port_return(&port, 0, vertrix_lift_edx);
                }
                edx = port_u32(&port, ebp, -0x2cu);
                ebx = port_u32(&port, ebp, -0x28u);
            }
            ebx--;
            if ((uint32_t)((int32_t)edx >> (ebx & 31)) & 1)
            {
                port_set16(&port, block, 0,
                           port_u16(&port, block, 0) | port_u32(&port, ebp, -0x1cu));
            }
            esi++;
            edi += 4;
        } while ((int32_t)esi < (int32_t)port_u32(&port, decoder, 0x164) && !port.env.failed);
    }
    source = port_u32(&port, decoder, 0x18);
    port_set32(&port, source, 0, port_u32(&port, ebp, -0x34u));
    source = port_u32(&port, decoder, 0x18);
    port_set32(&port, source, 4, port_u32(&port, ebp, -0x30u));
    port_set32(&port, entropy, 0x10, ebx);
    port_set32(&port, entropy, 0xc, edx);
    port_set32(&port, entropy, 0x28, port_u32(&port, entropy, 0x28) - 1);
    return port_return(&port, 1, edx);
}

/* Original 0x41a320: the level edx of the screen eax opened: its name and picture texts (0x5334a0,
 * 0x533578, each through 0x45f540 with 0x4fc4a0) into the frame; the level being played
 * (0x513c1e) goes to 0x41a960 with its name. Otherwise the object 0x423ea0 makes of them is placed
 * at the screen's +0xcc size (0x47e200), given 0x5b9c60 (0x47e360, its result kept) and shown
 * (0x478d80), the screen given 0x4182c0's handler and 0x540048 (0x41a2f0), a 0x280-byte view
 * (0x4ca000, 0x4413b0) kept at 0x544070, titled with the name (0x441530 with 0x10, 0xd and
 * 0x50dc38) and given the kept result (0x441b70). */
uint32_t vertrix_port_level_open_41a320(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x220
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t level = entry->edx;
    uint32_t name = ebp - 0x21c;
    uint32_t picture = ebp - 0x118;
    uint32_t slot = level * 4;
    uint32_t object;
    uint32_t size;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_call_with(&port, 0x45f540, name, 0x4fc4a0, port_u32(&port, slot, 0x5334a0), slot, level,
                   screen, ebp);
    ecx = slot + 0x533578;
    ebx = port_u32(&port, ecx, 0);
    port_call_with(&port, 0x45f540, picture, 0x4fc4a0, ebx, ecx, level, screen, ebp);
    if (level == port_u8(&port, 0, 0x513c1e))
    {
        eax = port_call_with(&port, 0x41a960, screen, name, ebx, ecx, level, screen, ebp);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    object = port_call_with(&port, 0x423ea0, name, picture, ebx, ecx, level, screen, ebp);
    size = port_u32(&port, screen, 0xcc);
    {
        uint32_t args[4] = {0, 0, port_u32(&port, size, 4), port_u32(&port, size, 8)};
        vertrix_lift_in_esi = object;
        vertrix_lift_in_edi = screen;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x47e200, object, size, 0, 0, args, 4);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    }
    eax = port_call_with(&port, 0x47e360, object, 0x5b9c60, 0, 0, object, screen, ebp);
    port_set32(&port, ebp, -0x14u, eax);
    eax = port_call_with(&port, 0x478d80, object, eax, 0, 0, object, screen, ebp);
    ebx = port_call_with(&port, 0x4182c0, eax, vertrix_lift_edx, 0, 0, object, screen, ebp);
    ecx = port_u32(&port, 0, 0x540048);
    port_call_with(&port, 0x41a2f0, screen, vertrix_lift_edx, ebx, ecx, object, screen, ebp);
    eax = port_call_with(&port, 0x4ca000, 0x280, vertrix_lift_edx, ebx, ecx, object, screen, ebp);
    if (eax != 0)
    {
        eax = port_call_with(&port, 0x4413b0, eax, vertrix_lift_edx, ebx, ecx, object, screen, ebp);
    }
    port_set32(&port, 0, 0x544070, eax);
    {
        uint32_t args[4] = {0, 0, 0xd, 0x50dc38};
        vertrix_lift_in_esi = object;
        vertrix_lift_in_edi = screen;
        vertrix_lift_in_ebp = ebp;
        lift_call_arguments(&port.env, 0x441530, eax, name, 0, 0x10, args, 4);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    }
    eax = port_call_with(&port, 0x441b70, port_u32(&port, 0, 0x544070),
                         port_u32(&port, ebp, -0x14u), 0, 0x10, object, screen, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x421ac0: under the guard record 0x5141c8 the screen eax reset (0x41ab90, 0x41ac20),
 * named (0x41a9e0), 0x45f9f0, 0x4719e0, the texts 0 and 1 (0x45e670, the second 0x50ddeb); unless
 * 0x4ccfe0 matches 0x4fc080, the settings of the current slot (0x534750 by 0x532a70, held in a
 * frame string by 0x4ca090) formatted with 0x4fcff8 (0x45f540) and loaded by 0x412240 into
 * 0x532928, whose handler +0x7b4 is told 2, and the string released (0x4ca210); then the handlers
 * 0x421f10 (0x418840) and 0x41c6d0 (0x418820). eax the restored chain, edx kept. */
uint32_t vertrix_port_settings_screen_open_421ac0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x134
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t record = ebp - 0x2c;
    uint32_t ebx = 0x5141c8;
    uint32_t edi = entry->edi;
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
    port_set32(&port, ebp, -0x28u, 0x4ec1ec);
    port_set32(&port, ebp, -0x24u, 0x5141c8);
    port_set32(&port, ebp, -0x20u, 0);
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, screen, 0, edi, ebp)
    CALL(0x41ab90, screen, 0x4ec1ec);
    CALL(0x41ac20, screen, vertrix_lift_edx);
    eax = CALL(0x41a9e0, screen, vertrix_lift_edx);
    eax = CALL(0x45f9f0, eax, vertrix_lift_edx);
    CALL(0x4719e0, eax, vertrix_lift_edx);
    CALL(0x45e670, 0, vertrix_lift_edx);
    CALL(0x45e670, 1, 0x50ddeb);
    if (CALL(0x4ccfe0, 0x4fc080, vertrix_lift_edx) == 0)
    {
        uint32_t text = ebp - 0x130;
        edi = 1;
        CALL(0x4ca090, ebp - 0x18, port_u32(&port, 0, 0x532a70) * 4 + 0x534750);
        ebx = port_u32(&port, ebp, -0x18u);
        port_set32(&port, ebp, -0x20u, edi);
        CALL(0x45f540, text, 0x4fcff8);
        CALL(0x412240, port_u32(&port, 0, 0x532928), text);
        eax = port_u32(&port, 0, 0x532928);
        if (eax != 0)
        {
            ebx = port_u32(&port, eax, 0x7b4);
            CALL(port_u32(&port, ebx, 0), eax, 2);
        }
        ebx = 0;
        port_set32(&port, ebp, -0x20u, 0);
        CALL(0x4ca210, ebp - 0x18, 0);
        port_set32(&port, ebp, -0x20u, 0);
    }
    CALL(0x418840, screen, 0x421f10);
    CALL(0x418820, screen, 0x41c6d0);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47faf0: the text edx (at most 256 bytes of it) copied with a 0 into the object eax's
 * +0xb9 and the object redrawn with it (0x47fa40 with +0xb8, its +0x38 and 0x102). eax 0 for an
 * empty text. */
uint32_t vertrix_port_object_set_text_47faf0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t text = entry->edx;
    uint32_t length = 0;
    uint32_t index;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, object);
    while (port_u8(&port, text, length) != 0 && !port.env.failed)
    {
        length++;
    }
    if (length == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (length > 0x100)
    {
        length = 0x100;
    }
    for (index = 0; index < length && !port.env.failed; index++)
    {
        port_set8(&port, object, 0xb9 + index, port_u8(&port, text, index));
    }
    port_set8(&port, object + length, 0xb9, 0);
    eax = port_call_with(&port, 0x47fa40, object, object + 0xb8, port_u32(&port, object, 0x38),
                         0x102, text + length, object + 0xb9, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4c58e0: the JPEG memory pool edx of the decoder eax freed (an error 0xe through the
 * error manager for a pool not 0 or 1): for the image pool every virtual array still realised
 * (+0x44, then +0x48 lists) closed by its method +0x38 and the lists cleared; then the pool's large
 * (+0x3c, 0x4c5be0) and small (+0x34, 0x4c5bc0) blocks released, each one's size and header
 * taken off the total +0x4c. */
uint32_t vertrix_port_jpeg_free_pool_4c58e0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t pool = entry->edx;
    uint32_t memory;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t edi = entry->edi;
    unsigned list;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x1cu, pool);
    memory = port_u32(&port, decoder, 4);
    if ((int32_t)pool < 0 || (int32_t)pool >= 2)
    {
        uint32_t error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0xe);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, port_u32(&port, ebp, -0x1cu));
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, error, ebx, decoder, memory, edi,
                       ebp);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, ebp, -0x1cu) == 1)
    {
        for (list = 0x44; list <= 0x48; list += 4)
        {
            ebx = port_u32(&port, memory, list);
            while (ebx != 0 && !port.env.failed)
            {
                if (port_u32(&port, ebx, 0x28) != 0)
                {
                    port_set32(&port, ebx, 0x28, 0);
                    port_call_with(&port, port_u32(&port, ebx, 0x38), decoder, ebx + 0x30, ebx,
                                   decoder, memory, edi, ebp);
                    edx = vertrix_lift_edx;
                }
                ebx = port_u32(&port, ebx, 0x2c);
            }
            port_set32(&port, memory, list, 0);
        }
    }
    edx = port_u32(&port, ebp, -0x1cu);
    eax = port_u32(&port, memory + edx * 4, 0x3c);
    port_set32(&port, memory + edx * 4, 0x3c, 0);
    while (eax != 0 && !port.env.failed)
    {
        uint32_t header = eax;
        port_set32(&port, ebp, -0x14u, port_u32(&port, header, 0));
        edi = port_u32(&port, header, 4) + port_u32(&port, header, 8) + 0x10;
        ebx = edi;
        port_call_with(&port, 0x4c5be0, decoder, header, ebx, decoder, memory, edi, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, memory, 0x4c, port_u32(&port, memory, 0x4c) - edi);
        eax = port_u32(&port, ebp, -0x14u);
    }
    edx = port_u32(&port, ebp, -0x1cu);
    eax = port_u32(&port, memory + edx * 4, 0x34);
    port_set32(&port, memory + edx * 4, 0x34, 0);
    while (eax != 0 && !port.env.failed)
    {
        uint32_t header = eax;
        port_set32(&port, ebp, -0x18u, port_u32(&port, header, 0));
        edi = port_u32(&port, header, 4) + port_u32(&port, header, 8) + 0x10;
        ebx = edi;
        port_call_with(&port, 0x4c5bc0, decoder, header, ebx, decoder, memory, edi, ebp);
        edx = vertrix_lift_edx;
        port_set32(&port, memory, 0x4c, port_u32(&port, memory, 0x4c) - edi);
        eax = port_u32(&port, ebp, -0x18u);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4cfd20 (one stack argument, the window, popped): the window procedure of the window
 * given back. With the current control (0x4ce220) +0x14 set: the control told (0x4cf940, its
 * methods +0x54 and +0x84), and unless the window still has 0x4cfa10's procedure (import 0x4f19f0
 * with -4) the kept procedure restored (0x4f1ad0) into +0x84's slot; a hook 0x4dc030 makes of
 * 0x5c7b84 told of message 0x36f (0x4cf650) when the application allows; +0x14 cleared. Without
 * it, the window's procedure kept as the property 0x502778 (0x4f1abc) and, when it reads back, the
 * window given 0x4cfc90 or 0x4cfa20 by the control's +0x28. */
uint32_t vertrix_port_window_procedure_restore_4cfd20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - BELOW;
    uint32_t window;
    uint32_t control;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi;
    uint32_t ebp = entry->ebp;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    port_set32(&port, entry->esp, -0x10u, entry->ebp);
    window = port_u32(&port, entry->esp, 4);
#define CALL(target, a, d, args, n)                                                                \
    (eax = call_frame(&port, target, a, d, ebx, ecx, window, edi, ebp, args, n))
    edi = entry->edi;
    ebx = entry->ebx;
    control = CALL(0x4ce220, entry->eax, entry->edx, NULL, 0);
    edi = control;
    ebx = port_u32(&port, control, 0x14);
    port_set32(&port, esp, 4, control);
    if (ebx != 0)
    {
        uint32_t vtable;
        uint32_t slot;
        uint32_t hook;
        CALL(0x4cf940, ebx, window, NULL, 0);
        edi = port_u32(&port, ebx, 0);
        CALL(port_u32(&port, edi, 0x54), ebx, vertrix_lift_edx, NULL, 0);
        vtable = port_u32(&port, ebx, 0);
        edi = vtable;
        slot = CALL(port_u32(&port, vtable, 0x84), ebx, vertrix_lift_edx, NULL, 0);
        ebp = slot;
        {
            uint32_t args[2] = {window, 0xfffffffcu};
            edi = CALL(0x4f19f0, eax, vertrix_lift_edx, args, 2);
        }
        CALL(0x4cfa10, eax, vertrix_lift_edx, NULL, 0);
        port_set32(&port, esp, 0, edi == eax ? 1 : 0);
        CALL(0x4ce740, port_u32(&port, esp, 0), vertrix_lift_edx, NULL, 0);
        if (port_u8(&port, eax, 0x14) == 0)
        {
            hook = CALL(0x4dc030, 0x5c7b84, 0x4cc760, NULL, 0);
            edi = hook;
            if (port_u32(&port, hook, 0x20) != 0)
            {
                uint32_t args[5] = {ebx, window, 0x36f, 0, 0};
                CALL(0x4cf650, eax, vertrix_lift_edx, args, 5);
                if (eax != 0)
                {
                    uint32_t more[2] = {window, eax};
                    CALL(port_u32(&port, hook, 0x20), eax, vertrix_lift_edx, more, 2);
                }
            }
        }
        if (port_u32(&port, esp, 0) == 0)
        {
            CALL(0x4cfa10, eax, vertrix_lift_edx, NULL, 0);
            {
                uint32_t args[3] = {window, 0xfffffffcu, eax};
                CALL(0x4f1ad0, eax, vertrix_lift_edx, args, 3);
            }
            port_set32(&port, slot, 0, eax);
        }
        eax = port_u32(&port, esp, 4);
        port_set32(&port, eax, 0x14, 0);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    {
        uint32_t args[2] = {window, 0xfffffffcu};
        ebx = CALL(0x4f19f0, eax, vertrix_lift_edx, args, 2);
    }
    if (ebx != 0)
    {
        uint32_t edx;
        {
            uint32_t args[3] = {window, 0x502778, ebx};
            CALL(0x4f1abc, ebx, vertrix_lift_edx, args, 3);
        }
        {
            uint32_t args[2] = {window, 0x502778};
            CALL(0x4f19cc, eax, vertrix_lift_edx, args, 2);
        }
        edx = vertrix_lift_edx;
        if (eax == ebx)
        {
            uint32_t args[3] = {window, 0xfffffffcu,
                                port_u32(&port, edi, 0x28) != 0 ? 0x4cfc90 : 0x4cfa20};
            CALL(0x4f1ad0, args[2], edx, args, 3);
            edx = vertrix_lift_edx;
        }
        return port_return(&port, eax, edx);
    }
#undef CALL
    return port_return(&port, eax, vertrix_lift_edx);
}

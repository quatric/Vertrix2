#include "port_rtlstreamopen.h"

/* Sound streams opened, the play screen started and the world map set up. */

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

/* Original 0x47eda0: the stream eax opened on its device (+0; none gives 0): its format +0x1c
 * written into a wave header at ebp - 0x26c (0x47fc10 with -1); a 0x48-byte description at ebp -
 * 0x6c cleared (0x4eb5c0) with its size 0x48, the flags from its class +0x20, the length +0x18,
 * the header, the 0x10-byte rectangle from +0x20..+0x2c; the buffer made by the device's class
 * +0x24 into +4 (with the given +0x54/+0x58 of +0x14 when set, else 1 and zeros). On failure it
 * is reported (0x480080) with +0x30 1 and 0, else +0x30 0 and 1. */
uint32_t vertrix_port_sound_stream_open_47eda0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x270
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stream = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi = entry->esi;
    uint32_t device;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    if (port_u32(&port, stream, 0) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    ebx = port_u32(&port, stream, 0x1c);
    port_call_with(&port, 0x47fc10, stream, ebp - 0x26c, ebx, 0xffffffffu, esi, stream, ebp);
    port_set32(&port, ebp, -0x24u, port_u32(&port, stream, 0x20));
    port_set32(&port, ebp, -0x20u, port_u32(&port, stream, 0x24));
    port_set32(&port, ebp, -0x1cu, port_u32(&port, stream, 0x28));
    port_set32(&port, ebp, -0x18u, port_u32(&port, stream, 0x2c));
    ecx = 0x48;
    port_call_with(&port, 0x4eb5c0, ebp - 0x6c, 0, 0x48, ecx, esi, stream, ebp);
    port_set32(&port, ebp, -0x6cu, ecx);
    esi = ebp - 0x54;
    edx = port_u32(&port, stream, 0x1c8);
    ebx = 0;
    port_call_with(&port, port_u32(&port, edx, 0x20), stream, edx, ebx, ecx, esi, stream, ebp);
    port_set32(&port, ebp, -0x68u, ebx);
    port_set32(&port, ebp, -0x44u, port_u32(&port, stream, 0x18));
    port_set32(&port, ebp, -0x3cu, ebp - 0x26c);
    esi = 0x10;
    port_set32(&port, ebp, -0x28u, 0x10);
    port_set32(&port, ebp, -0x2cu, ebp - 0x24);
    eax = port_u32(&port, stream, 0x14);
    device = port_u32(&port, stream, 0);
    ebx = port_u32(&port, device, 0);
    if (eax == 0)
    {
        uint32_t args[8] = {device, ebp - 0x6c, stream + 4, 1, 0, 0, 0, 0};
        eax = call_frame(&port, port_u32(&port, ebx, 0x24), device, ebp - 0x6c, ebx, ecx, esi,
                         stream, ebp, args, 8);
    }
    else
    {
        uint32_t given = eax;
        uint32_t args[8] = {device, ebp - 0x6c, 0, 0, 0, 0, 0, 0};
        ecx = port_u32(&port, given, 0x58);
        esi = port_u32(&port, given, 0x54);
        args[2] = esi;
        args[3] = ecx;
        eax = call_frame(&port, port_u32(&port, ebx, 0x24), ebp - 0x6c, device, ebx, ecx, esi,
                         stream, ebp, args, 8);
    }
    edx = eax;
    if ((int32_t)edx < 0)
    {
        port_call_with(&port, 0x480080, stream, edx, ebx, ecx, esi, stream, ebp);
        port_set32(&port, stream, 0x30, 1);
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, stream, 0x30, 0);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x41a540: the play screen eax started: +0xd4 1, the critical section 0x540020 entered
 * (import 0x4f1c30), the list 0x5b9c50 opened for 0x17c (0x4856a0), 0x540044 0, 0x540048 0x17c,
 * 0x5bb710 1; the board pictures by 0x4fc4a0 with 0x5334a0's and 0x533578's names at 0x513c38
 * (0x45f540) loaded into +0xcc (0x423ea0) and the panel by 0x513c39's name into +0xd0 (0x441d60
 * with 0); the screen readied with 0x513c1b (0x41a320, 0x41aa20, 0x41aaf0), the list closed
 * (0x487020, 0x487130), 0x4b7cd0, 0x41a930, 0x418a10, the key handler 0x41a680 (0x41a940),
 * 0x418820 and the painter 0x41a520 (0x418840). eax the last answer. */
uint32_t vertrix_port_play_screen_start_41a540(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x21c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = 1;
    uint32_t ecx = entry->ecx;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, ecx, screen, entry->edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, screen, 0xd4, 1);
    {
        uint32_t args[1] = {0x540020};
        call_frame(&port, 0x4f1c30, screen, entry->edx, ebx, ecx, screen, entry->edi, ebp, args, 1);
    }
    ecx = 0x17c;
    CALL(0x4856a0, 0x5b9c50, vertrix_lift_edx);
    port_set32(&port, 0, 0x540044, 0);
    port_set32(&port, 0, 0x540048, ecx);
    ecx = port_u8(&port, 0, 0x513c38) * 4;
    port_set32(&port, 0, 0x5bb710, ebx);
    ebx = port_u32(&port, ecx + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x218, 0x4fc4a0);
    ecx += 0x533578;
    ebx = port_u32(&port, ecx, 0);
    CALL(0x45f540, ebp - 0x114, 0x4fc4a0);
    eax = CALL(0x423ea0, ebp - 0x218, ebp - 0x114);
    port_set32(&port, screen, 0xcc, eax);
    ebx = port_u32(&port, port_u8(&port, 0, 0x513c39) * 4 + 0x5334a0, 0);
    CALL(0x45f540, ebp - 0x218, 0x4fc4a0);
    eax = CALL(0x441d60, ebp - 0x218, 0);
    edx = (vertrix_lift_edx & 0xffffff00u) | port_u8(&port, 0, 0x513c1b);
    port_set32(&port, screen, 0xd0, eax);
    CALL(0x41a320, screen, edx);
    CALL(0x41aa20, screen, vertrix_lift_edx);
    CALL(0x41aaf0, screen, vertrix_lift_edx);
    CALL(0x487020, 0x5b9c50, vertrix_lift_edx);
    eax = CALL(0x487130, 0x5b9c50, vertrix_lift_edx);
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x41a930, screen, vertrix_lift_edx);
    CALL(0x418a10, screen, vertrix_lift_edx);
    CALL(0x41a940, screen, 0x41a680);
    CALL(0x418820, screen, vertrix_lift_edx);
    eax = CALL(0x418840, screen, 0x41a520);
#undef CALL
    return port_return(&port, eax, entry->edx);
}
/* Original 0x420040 (guarded 0x514134): the world map screen eax set up: the world 0x532a70's
 * name (0x5332c0, 0x4ca090 into ebp - 0x1c) gives its title file by 0x4fc290, or the language's
 * by 0x4fc398 when that is missing (0x45f590), set on the screen (0x41a960); its map name
 * (0x533310, 0x4ca310) by 0x4fcff8 (0x45f540) loaded into a 0x7b8-byte map (0x4ca000; 0x4120a0
 * makes it with 0x7a) kept at 0x532928 (0x4122f0); 0x45f770, the keys 0x54d640 reset (0x476090,
 * 0x4760c0, 0x476590, 0x4765b0 with 1, 0x476140 with the edx left, 0x3d, 2 to 9, 0x2e and 0x2f),
 * 0x4b7cd0, the list 0x5b9c50 emptied (0x4871d0), the world's font 0x533cd0 (0x4191b0 with 1),
 * the screen readied (0x41aa20, 0x41aaa0 with the painter 0x4202a0, 0x418840) and the name
 * freed (0x4ca210). eax the restored chain. */
uint32_t vertrix_port_world_map_setup_420040(PORT_SIGNATURE)
{
    static const uint32_t keys[] = {0x3d, 2, 3, 4, 5, 6, 7, 8, 9, 0x2e, 0x2f};
    enum
    {
        BELOW = 0x138
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t ebx = 0x514134;
    uint32_t esi = 0;
    uint32_t edi = 1;
    unsigned i;
#define CALL(target, a, d) port_call_with(&port, target, a, d, ebx, screen, esi, edi, ebp)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x514134);
    port_set32(&port, ebp, -0x24u, 0);
    CALL(0x4ca090, ebp - 0x1c, port_u32(&port, 0, 0x532a70) * 4 + 0x5332c0);
    ebx = port_u32(&port, ebp, -0x1cu);
    port_set32(&port, ebp, -0x24u, 1);
    CALL(0x45f540, ebp - 0x134, 0x4fc290);
    eax = CALL(0x45f590, ebp - 0x134, vertrix_lift_edx);
    if (eax == 0)
    {
        ebx = port_u32(&port, port_u8(&port, 0, 0x513c1a) * 4 + 0x5334a0, 0);
        CALL(0x45f540, ebp - 0x134, 0x4fc398);
    }
    CALL(0x41a960, screen, ebp - 0x134);
    CALL(0x4ca310, ebp - 0x1c, port_u32(&port, 0, 0x532a70) * 4 + 0x533310);
    ebx = port_u32(&port, ebp, -0x1cu);
    CALL(0x45f540, ebp - 0x134, 0x4fcff8);
    eax = CALL(0x4ca000, 0x7b8, vertrix_lift_edx);
    if (eax != 0)
    {
        ebx = 1;
        port_set32(&port, ebp, -0x24u, 2);
        port_set32(&port, ebp, -0x18u, eax);
        eax = CALL(0x4120a0, eax, 0x7a);
        port_set32(&port, ebp, -0x24u, ebx);
    }
    port_set32(&port, 0, 0x532928, eax);
    eax = CALL(0x4122f0, eax, ebp - 0x134);
    CALL(0x45f770, eax, vertrix_lift_edx);
    CALL(0x476090, 0x54d640, vertrix_lift_edx);
    CALL(0x4760c0, 0x54d640, vertrix_lift_edx);
    CALL(0x476590, 0x54d640, vertrix_lift_edx);
    CALL(0x4765b0, 0x54d640, 1);
    eax = CALL(0x476140, 0x54d640, vertrix_lift_edx);
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        eax = CALL(0x476140, 0x54d640, keys[i]);
    }
    CALL(0x4b7cd0, eax, vertrix_lift_edx);
    CALL(0x4871d0, 0x5b9c50, 0);
    ebx = 1;
    CALL(0x4191b0, screen, port_u32(&port, port_u32(&port, 0, 0x532a70) * 4 + 0x533cd0, 0));
    CALL(0x41aa20, screen, vertrix_lift_edx);
    CALL(0x41aaa0, screen, 0x4202a0);
    esi = 0;
    CALL(0x418840, screen, vertrix_lift_edx);
    port_set32(&port, ebp, -0x24u, 0);
    CALL(0x4ca210, ebp - 0x1c, 0);
    port_set32(&port, ebp, -0x24u, 0);
#undef CALL
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

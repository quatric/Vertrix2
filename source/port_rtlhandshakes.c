#include "port_rtlhandshakes.h"

/* The network game's handshake. */

/* A call (with count stack arguments, nearest first) that leaves its eax and
 * edx in *eax and *edx; the eax. */
static uint32_t shake_call(Port *port, uint32_t *eax, uint32_t *edx, uint32_t target, uint32_t a,
                           uint32_t d, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                           uint32_t ebp, const uint32_t *stack, unsigned count)
{
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    *eax = lift_call_arguments(&port->env, target, a, d, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    *edx = vertrix_lift_edx;
    return *eax;
}

/* Original 0x416500 (guarded 0x513ae0): the network game's handshake step: the
 * timers of 0x4f819c run (0x417260, 0x417290); with the link 0x5bb254 up
 * (0x47f410 1) its peer (0x47f160) and its address (0x47f370, kept by 0x4ca070)
 * checked: none says 0x50d53f, -1 says 0x50d557 to the chat 0x532c24 (made by
 * 0x4ca280, shown by 0x4b76d0, freed by 0x4ca210). A version (0x48c680) other
 * than 0x4f7b40 (0x418150) says both versions (0x418170) in 0x50d576 (printed
 * by 0x4cdfb0, 0x4ca090) and ends (0x4cda10). Otherwise the link is asked in
 * turn: not ready (0x48c390) says 0x50d605, not joined (0x48c460) says
 * 0x50d5e9; then 0x47f3d0; no game (0x48b7e0) says 0x50d5cb; not started
 * (0x48c610) says 0x50d5af and closes it (0x48b970); started says 0x50d59f and
 * 0x532a4c becomes 0x4f7b74. The link down says 0x50d622. The address freed on
 * the ways out that kept it. eax the restored chain, edx kept. */
uint32_t vertrix_port_network_handshake_416500(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x5c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x58;
    uint32_t eax;
    uint32_t edx = 0x4ec1ec;
    uint32_t ebx = 0;
    uint32_t ecx = 0x513ae0;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t text;
#define CALL(target, a, d)                                                                         \
    shake_call(&port, &eax, &edx, target, a, d, ebx, ecx, esi, edi, ebp, NULL, 0)
#define STATE(value) port_set32(&port, ebp, -0x4cu, value)
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x54u, edx);
    port_set32(&port, ebp, -0x50u, ecx);
    STATE(ebx);
    CALL(0x417260, port_u32(&port, 0, 0x4f819c), edx);
    CALL(0x417290, port_u32(&port, 0, 0x4f819c), edx);
    if (CALL(0x47f410, 0x5bb254, edx) != 1)
    {
        esi = 0x14;
        text = CALL(0x4ca280, ebp - 0x18, 0x50d622);
        STATE(esi);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(ebx);
        CALL(0x4ca210, ebp - 0x18, 0);
        STATE(ebx);
        goto done;
    }
    ecx = CALL(0x47f160, 0x5bb254, edx);
    text = CALL(0x47f370, 0x5bb254, edx);
    ebx = 1;
    CALL(0x4ca070, ebp - 0x44, text);
    STATE(ebx);
    if (ecx == 0)
    {
        text = CALL(0x4ca280, ebp - 0x40, 0x50d53f);
        STATE(2);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(ebx);
        CALL(0x4ca210, ebp - 0x40, 0);
        STATE(ecx);
        ebx = 0;
        CALL(0x4ca210, ebp - 0x44, 0);
        STATE(ebx);
        goto done;
    }
    if (edx == 0xffffffffu)
    {
        ecx = 4;
        text = CALL(0x4ca280, ebp - 0x3c, 0x50d557);
        esi = 0;
        STATE(ecx);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(ebx);
        CALL(0x4ca210, ebp - 0x3c, 0);
        STATE(esi);
        CALL(0x4ca210, ebp - 0x44, 0);
        STATE(esi);
        goto done;
    }
    eax = CALL(0x48c680, 0x5bb254, edx);
    ebx = port_u32(&port, 0, 0x4f7b40);
    ecx = eax;
    if (CALL(0x418150, eax, ebx) != 0)
    {
        uint32_t args[4];
        CALL(0x418170, ebp - 0x38, ecx);
        STATE(6);
        CALL(0x418170, ebp - 0x34, ebx);
        ebx = port_u32(&port, ebp, -0x34u);
        esi = port_u32(&port, ebp, -0x38u);
        ecx = 7;
        STATE(ecx);
        args[0] = ebp - 0x44;
        args[1] = 0x50d576;
        args[2] = esi;
        args[3] = ebx;
        shake_call(&port, &eax, &edx, 0x4cdfb0, ebp - 0x44, ebp - 0x44, ebx, ecx, esi, edi, ebp,
                   args, 4);
        edi = 8;
        text = CALL(0x4ca090, ebp - 0x30, edx);
        STATE(edi);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(ecx);
        CALL(0x4ca210, ebp - 0x30, 0);
        STATE(ecx);
        CALL(0x4cda10, eax, edx);
        goto done;
    }
    if (CALL(0x48c390, 0x5bb254, edx) != 1)
    {
        esi = 0x12;
        edi = 1;
        text = CALL(0x4ca280, ebp - 0x1c, 0x50d605);
        STATE(esi);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(edi);
        CALL(0x4ca210, ebp - 0x1c, 0);
        STATE(edi);
    }
    else if (CALL(0x48c460, 0x5bb254, edx) != 1)
    {
        ecx = 0x10;
        ebx = 1;
        text = CALL(0x4ca280, ebp - 0x20, 0x50d5e9);
        STATE(ecx);
        CALL(0x4b76d0, 0x532c24, text);
        STATE(ebx);
        CALL(0x4ca210, ebp - 0x20, 0);
        STATE(ebx);
    }
    else
    {
        CALL(0x47f3d0, 0x5bb254, edx);
        if (CALL(0x48b7e0, 0x5bb254, edx) != 1)
        {
            edi = 0xe;
            text = CALL(0x4ca280, ebp - 0x24, 0x50d5cb);
            STATE(edi);
            CALL(0x4b76d0, 0x532c24, text);
            STATE(1);
            CALL(0x4ca210, ebp - 0x24, 0);
            STATE(1);
        }
        else if (CALL(0x48c610, 0x5bb254, edx) == 1)
        {
            ecx = 0xa;
            ebx = 1;
            text = CALL(0x4ca280, ebp - 0x2c, 0x50d59f);
            edi = 0;
            STATE(ecx);
            CALL(0x4b76d0, 0x532c24, text);
            STATE(ebx);
            CALL(0x4ca210, ebp - 0x2c, 0);
            STATE(ebx);
            port_set32(&port, 0, 0x532a4c, port_u32(&port, 0, 0x4f7b74));
            STATE(edi);
            CALL(0x4ca210, ebp - 0x44, 0);
            STATE(edi);
            goto done;
        }
        else
        {
            ecx = 0xc;
            ebx = 1;
            text = CALL(0x4ca280, ebp - 0x28, 0x50d5af);
            STATE(ecx);
            CALL(0x4b76d0, 0x532c24, text);
            STATE(ebx);
            CALL(0x4ca210, ebp - 0x28, 0);
            STATE(ebx);
            CALL(0x48b970, 0x5bb254, edx);
            STATE(ebx);
        }
    }
    STATE(0);
    CALL(0x4ca210, ebp - 0x44, 0);
    STATE(0);
done:
#undef CALL
#undef STATE
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

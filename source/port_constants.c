#include "port_constants.h"

/* Routines that only return a constant (mov eax, value; ret): the class and method addresses the
 * runtime library's virtual tables hand out, and a few others. */
static uint32_t constant(PORT_SIGNATURE, uint32_t value)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, value, entry->edx);
}

uint32_t vertrix_port_constant_4241d0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x419f60);
}

uint32_t vertrix_port_constant_4241e0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x419ea0);
}

uint32_t vertrix_port_constant_4241f0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x424160);
}

uint32_t vertrix_port_constant_4cb390(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4cc7a0);
}

uint32_t vertrix_port_constant_4cb3a0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4ccaf0);
}

uint32_t vertrix_port_constant_4cb3b0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4ccb40);
}

uint32_t vertrix_port_constant_4cfa10(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4cf9d0);
}

uint32_t vertrix_port_constant_4d2ea0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d09b0);
}

uint32_t vertrix_port_constant_4d2eb0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d05e0);
}

uint32_t vertrix_port_constant_4d2ec0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d0740);
}

uint32_t vertrix_port_constant_4d2ed0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d24a0);
}

uint32_t vertrix_port_constant_4d2ee0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d0620);
}

uint32_t vertrix_port_constant_4d2ef0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2460);
}

uint32_t vertrix_port_constant_4d2f00(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2420);
}

uint32_t vertrix_port_constant_4d2f10(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2440);
}

uint32_t vertrix_port_constant_4d2f20(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d0650);
}

uint32_t vertrix_port_constant_4d2f30(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d0670);
}

uint32_t vertrix_port_constant_4d2f40(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d06a0);
}

uint32_t vertrix_port_constant_4d2f50(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d02a0);
}

uint32_t vertrix_port_constant_4d2f60(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2170);
}

uint32_t vertrix_port_constant_4d2f70(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d21d0);
}

uint32_t vertrix_port_constant_4d2f80(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2260);
}

uint32_t vertrix_port_constant_4d2f90(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d22b0);
}

uint32_t vertrix_port_constant_4d2fa0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2310);
}

uint32_t vertrix_port_constant_4d2fb0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d21a0);
}

uint32_t vertrix_port_constant_4d2fc0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d2390);
}

uint32_t vertrix_port_constant_4d2fd0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d23f0);
}

uint32_t vertrix_port_constant_4d6490(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d54c0);
}

uint32_t vertrix_port_constant_4d64a0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5660);
}

uint32_t vertrix_port_constant_4d64b0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d57a0);
}

uint32_t vertrix_port_constant_4d64c0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d57c0);
}

uint32_t vertrix_port_constant_4d64d0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d6080);
}

uint32_t vertrix_port_constant_4d64e0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d58e0);
}

uint32_t vertrix_port_constant_4d64f0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4e00);
}

uint32_t vertrix_port_constant_4d6500(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4e30);
}

uint32_t vertrix_port_constant_4d6510(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5360);
}

uint32_t vertrix_port_constant_4d6520(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4990);
}

uint32_t vertrix_port_constant_4d6530(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4d10);
}

uint32_t vertrix_port_constant_4d6540(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4c00);
}

uint32_t vertrix_port_constant_4d6550(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d62e0);
}

uint32_t vertrix_port_constant_4d6560(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d6300);
}

uint32_t vertrix_port_constant_4d6570(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4ee0);
}

uint32_t vertrix_port_constant_4d6580(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4fd0);
}

uint32_t vertrix_port_constant_4d6590(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5010);
}

uint32_t vertrix_port_constant_4d65a0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d50d0);
}

uint32_t vertrix_port_constant_4d65b0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5150);
}

uint32_t vertrix_port_constant_4d65c0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5180);
}

uint32_t vertrix_port_constant_4d65d0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4270);
}

uint32_t vertrix_port_constant_4d65e0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4630);
}

uint32_t vertrix_port_constant_4d65f0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d41c0);
}

uint32_t vertrix_port_constant_4d6600(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d41a0);
}

uint32_t vertrix_port_constant_4d6610(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d42a0);
}

uint32_t vertrix_port_constant_4d6620(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4300);
}

uint32_t vertrix_port_constant_4d6630(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d4e60);
}

uint32_t vertrix_port_constant_4d6640(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5a30);
}

uint32_t vertrix_port_constant_4d6650(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5a70);
}

uint32_t vertrix_port_constant_4d6660(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5bf8);
}

uint32_t vertrix_port_constant_4d6670(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5c70);
}

uint32_t vertrix_port_constant_4d6680(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5ab0);
}

uint32_t vertrix_port_constant_4d6690(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d51c0);
}

uint32_t vertrix_port_constant_4d66a0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5280);
}

uint32_t vertrix_port_constant_4d66b0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d5330);
}

uint32_t vertrix_port_constant_4d7430(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d73b0);
}

uint32_t vertrix_port_constant_4d7460(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d73c0);
}

uint32_t vertrix_port_constant_4d7470(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d7400);
}

uint32_t vertrix_port_constant_4d7480(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d25e0);
}

uint32_t vertrix_port_constant_4d7490(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d7140);
}

uint32_t vertrix_port_constant_4d74a0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4d7110);
}

uint32_t vertrix_port_constant_4ee7f0(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4ee730);
}

uint32_t vertrix_port_constant_4ee800(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4ee750);
}

uint32_t vertrix_port_constant_4ee810(PORT_SIGNATURE)
{
    return constant(calls, services, globals, entry, 0x4ee6a0);
}

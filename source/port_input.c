#include "port_input.h"

enum
{
    INPUT_STATE = 0x00,
    INPUT_KEY = 0x04,
    INPUT_TARGET = 0x20,
    TARGET_HANDLER = 0x0c,
    INPUT_TIME = 0x40,
    INPUT_LAST_TIME = 0x48,
    STEP_EDX = 0x4c,
    STEP_EBX = 0x50,
    STEP_ECX = 0x54,
    INPUT_ENABLED = 0x5a,
    INPUT_SUSPENDED = 0x553648,
    TIME_UPDATE = 0x475e30,
    TIME_DUE = 0x475df0,
    STEP_COUNT = 0x475e10,
    STEPS_BEGIN = 0x475de0,
    STEP = 0x475b20,
    REPEAT_TICK = 0x475e50,
    HANDLER_CALL = 0x475c30,
    KEY_HELD = 0x475800,
    KEY_DOWN = 1,
    INPUT_READY = 0x475d70,
    SLOT_SIZE = 0x60
};

uint32_t vertrix_port_input_repeat_tick(PORT_SIGNATURE)
{
    Port port;
    uint32_t input = entry->eax;
    uint32_t eax;
    uint32_t steps;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, input, INPUT_ENABLED) != 1 || port_u32(&port, input, INPUT_TIME) == 0)
    {
        return port_return(&port, input, entry->edx);
    }
    port_call(&port, TIME_UPDATE, input, entry->edx, entry->ebx, entry->ecx);
    eax = port_call(&port, TIME_DUE, input, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (eax != 1)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    steps = port_call(&port, STEP_COUNT, input, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, STEPS_BEGIN, input, steps, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, input, INPUT_TIME);
    port_set32(&port, input, INPUT_LAST_TIME, eax);
    if (edx == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        uint32_t ecx = port_u32(&port, input, STEP_ECX);
        uint32_t ebx = port_u32(&port, input, STEP_EBX);
        edx = port_u32(&port, input, STEP_EDX);
        steps--;
        eax = port_call(&port, STEP, input, edx, ebx, ecx);
    } while (steps != 0);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_input_poll(PORT_SIGNATURE)
{
    Port port;
    uint32_t input = entry->eax;
    uint32_t target = input + INPUT_TARGET;
    uint32_t eax;
    uint32_t state;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, REPEAT_TICK, input, entry->edx, entry->ebx, input);
    if (port_u32(&port, 0, INPUT_SUSPENDED) != 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    state = port_u8(&port, input, INPUT_STATE);
    eax = (eax & 0xffff00ffu) | (state << 8);
    if (state == 0)
    {
        if (port_u32(&port, target, TARGET_HANDLER) == 0)
        {
            return port_return(&port, eax, target);
        }
        eax = port_call(&port, HANDLER_CALL, input, target, entry->ebx, input);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (state != 1)
    {
        return port_return(&port, eax, target);
    }
    eax = port_call(&port, KEY_HELD, input + INPUT_KEY, target, entry->ebx, input);
    edx = vertrix_lift_edx;
    if ((eax & 0xff) == 1 || port_u32(&port, edx, TARGET_HANDLER) == 0)
    {
        return port_return(&port, eax, edx);
    }
    eax = port_call(&port, HANDLER_CALL, input, edx, entry->ebx, input);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_byte_get(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, (entry->eax & 0xffffff00u) | port_u8(&port, entry->eax, 0),
                       entry->edx);
}

uint32_t vertrix_port_input_drain(PORT_SIGNATURE)
{
    Port port;
    uint32_t input = entry->eax;
    uint32_t target = input + INPUT_TARGET;
    uint32_t eax;
    uint32_t edx;
    uint32_t state;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, REPEAT_TICK, input, entry->edx, entry->ebx, input);
    edx = vertrix_lift_edx;
    state = port_u8(&port, input, INPUT_STATE);
    eax = (eax & 0xffff00ffu) | (state << 8);
    if (state == 0)
    {
        if (port_u32(&port, target, TARGET_HANDLER) == 0)
        {
            return port_return(&port, eax, edx);
        }
        eax = port_call(&port, HANDLER_CALL, input, edx, target, input);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    if (state != 1)
    {
        return port_return(&port, eax, edx);
    }
    /* Held: the handler runs until the key record answers 1 or the target has no handler. */
    for (;;)
    {
        eax = port_call(&port, KEY_HELD, input + INPUT_KEY, input + INPUT_KEY, target, input);
        edx = vertrix_lift_edx;
        if ((eax & 0xff) == 1 || port_u32(&port, target, TARGET_HANDLER) == 0)
        {
            return port_return(&port, eax, edx);
        }
        port_call(&port, HANDLER_CALL, input, edx, target, input);
    }
}

uint32_t vertrix_port_input_ready(PORT_SIGNATURE)
{
    Port port;
    uint32_t held;
    port_open(&port, calls, services, globals, entry);
    held = port_call(&port, KEY_HELD, entry->eax + INPUT_KEY, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, (held & 0xff) == KEY_DOWN, vertrix_lift_edx);
}

uint32_t vertrix_port_input_slot_ready(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = entry->edx & 0xffff;
    uint32_t ready;
    port_open(&port, calls, services, globals, entry);
    ready =
        port_call(&port, INPUT_READY, entry->eax + slot * SLOT_SIZE, slot, entry->ebx, entry->eax);
    return port_return(&port, ready, vertrix_lift_edx);
}

enum
{
    INPUT_RUNNING = 0x5328bc,
    INPUT_LOCK = 0x5328c0,
    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40
};

/* One input device: polled when it is open (its first dword 1). */
static uint32_t poll_device(Port *port, uint32_t device, uint32_t poll, uint32_t eax, uint32_t *edx,
                            uint32_t ebx, uint32_t ecx)
{
    if (port_u32(port, device, 0) != 1)
    {
        return eax;
    }
    eax = port_call(port, poll, device, *edx, ebx, ecx);
    *edx = vertrix_lift_edx;
    return eax;
}

uint32_t vertrix_port_input_poll_devices(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = INPUT_LOCK;
    uint32_t eax;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, INPUT_RUNNING) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    eax = port_call_stack(&port, ENTER_CRITICAL_SECTION, entry->eax, entry->edx, entry->ebx,
                          entry->ecx, &lock, 1);
    edx = vertrix_lift_edx;
    eax = poll_device(&port, 0x55608c, 0x4774e0, eax, &edx, entry->ebx, entry->ecx);
    eax = poll_device(&port, 0x5588f8, 0x477f10, eax, &edx, entry->ebx, entry->ecx);
    eax = poll_device(&port, 0x5536c8, 0x476d70, eax, &edx, entry->ebx, entry->ecx);
    eax = poll_device(&port, 0x553798, 0x476d70, eax, &edx, entry->ebx, entry->ecx);
    eax =
        port_call_stack(&port, LEAVE_CRITICAL_SECTION, eax, edx, entry->ebx, entry->ecx, &lock, 1);
    return port_return(&port, eax, entry->edx);
}

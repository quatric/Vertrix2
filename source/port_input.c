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

enum
{
    KEY_RECORD_FIELDS = 0x475da0,
    KEY_RECORD_SIZE = 0x60,
    STATE_FIELD_04 = 0x475810,
    STATE_FIELD_08 = 0x475820,
    STATE_FIELD_0C = 0x475830,
    KEY_RECORD_AGE = 0x475cd0
};

uint32_t vertrix_port_key_fields(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call(&port, KEY_RECORD_FIELDS, entry->eax + (entry->edx & 0xffff) * KEY_RECORD_SIZE,
                  entry->ebx, entry->ecx, entry->arguments[0]);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_key_record_fields(PORT_SIGNATURE)
{
    Port port;
    uint32_t state = entry->eax + 4;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_call(&port, STATE_FIELD_04, state, state, entry->ebx, entry->ecx);
    port_set32(&port, entry->edx, 0, value);
    state = vertrix_lift_edx;
    value = port_call(&port, STATE_FIELD_08, state, state, entry->ebx, entry->ecx);
    port_set32(&port, entry->ebx, 0, value);
    state = vertrix_lift_edx;
    value = port_call(&port, STATE_FIELD_0C, state, state, entry->ebx, entry->ecx);
    port_set32(&port, entry->ecx, 0, value);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_keys_age(PORT_SIGNATURE)
{
    Port port;
    uint32_t key;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    for (key = 0; key < 0x100; key++)
    {
        port_call(&port, KEY_RECORD_AGE, entry->eax + key * KEY_RECORD_SIZE, entry->edx, key + 1,
                  entry->edx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 0x100, edx);
}

enum
{
    KEY_CLEAR_FLAG = 0x475af0,
    KEY_STATE_SET = 0x475790,
    KEY_EVENTS_CLEAR = 0x4759e0,
    KEY_TIMER_AGE = 0x475e50,
    KEY_EVENTS_RUN = 0x475c30,
    KEY_HOLD_ENDED = 0x475800,
    INPUT_FROZEN = 0x553648
};

uint32_t vertrix_port_key_record_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t zero = 0;
    uint32_t offset;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, KEY_CLEAR_FLAG, record, entry->edx, entry->ebx, entry->ecx);
    for (offset = 0x3c; offset <= 0x54; offset += 4)
    {
        port_set32(&port, record, offset, 0);
    }
    port_call_stack(&port, KEY_STATE_SET, record + 4, 0, 0, 0, &zero, 1);
    result = port_call(&port, KEY_EVENTS_CLEAR, record, vertrix_lift_edx, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_key_record_age(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t eax;
    uint32_t state;
    uint32_t events = record + 0x20;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, KEY_TIMER_AGE, record, entry->edx, entry->ebx, record);
    if (port_u32(&port, 0, INPUT_FROZEN) != 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    state = port_u8(&port, record, 0);
    eax = (eax & 0xffff00ffu) | (state << 8);
    if (state == 0)
    {
        if (port_u32(&port, events, 0xc) == 0)
        {
            return port_return(&port, eax, events);
        }
    }
    else if (state == 1)
    {
        eax = port_call(&port, KEY_HOLD_ENDED, record + 4, events, entry->ebx, record);
        events = vertrix_lift_edx;
        if ((eax & 0xff) == 1 || port_u32(&port, events, 0xc) == 0)
        {
            return port_return(&port, eax, events);
        }
    }
    else
    {
        return port_return(&port, eax, events);
    }
    eax = port_call(&port, KEY_EVENTS_RUN, record, events, entry->ebx, record);
    return port_return(&port, eax, vertrix_lift_edx);
}

#include "inputdevices.h"

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

/* 0x476400's loop with the age routine `age`. */
static uint32_t keys_age_with(PORT_SIGNATURE, uint32_t age)
{
    Port port;
    uint32_t key;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    for (key = 0; key < 0x100; key++)
    {
        port_call(&port, age, entry->eax + key * KEY_RECORD_SIZE, entry->edx, key + 1, entry->edx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 0x100, edx);
}

uint32_t vertrix_port_keys_age(PORT_SIGNATURE)
{
    return keys_age_with(calls, services, globals, entry, KEY_RECORD_AGE);
}

uint32_t vertrix_port_keys_age_476440(PORT_SIGNATURE)
{
    return keys_age_with(calls, services, globals, entry, 0x475d20);
}

enum
{
    KEY_CLEAR_FLAG = 0x475af0,
    KEY_STATE_SET = 0x475790,
    KEY_EVENTS_CLEAR = 0x4759e0
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

/* One joystick direction for 0x476d70: the press routine runs when the direction comes on, the
 * release routine when it goes off; the state is kept at `field`. */
static uint32_t joystick_direction(Port *port, uint32_t stick, uint32_t field, uint32_t on,
                                   uint32_t press, uint32_t release, uint32_t *edx)
{
    uint32_t eax = on;
    uint32_t state = port_u32(port, stick, field);
    *edx = state;
    if (state == 0 && on == 1)
    {
        eax = port_call(port, press, stick, *edx, stick, on);
        *edx = vertrix_lift_edx;
        port_set32(port, stick, field, on);
    }
    else if (state == 1 && on == 0)
    {
        eax = port_call(port, release, stick, *edx, stick, on);
        *edx = vertrix_lift_edx;
        port_set32(port, stick, field, on);
    }
    return eax;
}

uint32_t vertrix_port_joystick_poll(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68,
        STATE = 0x64, /* below ebp: the device state, x and y then the buttons at +0x30 */
        BUTTONS = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t stick = entry->eax;
    uint32_t device;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t button;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (port_u8(&port, stick, 8) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, 0, 0x5536b4, port_u32(&port, stick, 0x14));
    eax = port_u32(&port, stick, 0x18);
    port_set32(&port, 0, 0x5536b8, eax);
    device = port_u32(&port, stick, 0x10);
    if (device == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    /* Poll, then read the state; a lost device is reacquired (0x476c80) and read again. */
    {
        uint32_t argument = device;
        eax = port_call_stack(&port, port_u32(&port, port_u32(&port, device, 0), 0x64), eax, device,
                              stick, port_u32(&port, device, 0), &argument, 1);
        edx = vertrix_lift_edx;
    }
    do
    {
        uint32_t arguments[3];
        device = port_u32(&port, stick, 0x10);
        arguments[0] = device;
        arguments[1] = 0x50;
        arguments[2] = ebp - STATE;
        result = port_call_stack(&port, port_u32(&port, port_u32(&port, device, 0), 0x24), device,
                                 edx, stick, port_u32(&port, device, 0), arguments, 3);
        edx = vertrix_lift_edx;
        if (result != 0)
        {
            port_set32(&port, stick, 4, 0);
            eax = port_call(&port, 0x476c80, stick, edx, stick, result);
            edx = vertrix_lift_edx;
            if (port_u32(&port, stick, 4) == 0)
            {
                return port_return(&port, eax, entry->edx);
            }
        }
    } while (result != 0);
    eax = joystick_direction(&port, stick, 0xa4, (int32_t)port_u32(&port, ebp, -STATE) < 0,
                             0x477010, 0x477040, &edx);
    eax = joystick_direction(&port, stick, 0xa8, (int32_t)port_u32(&port, ebp, -STATE) > 0,
                             0x477070, 0x4770a0, &edx);
    eax = joystick_direction(&port, stick, 0xac, (int32_t)port_u32(&port, ebp, -STATE + 4) < 0,
                             0x4770d0, 0x477100, &edx);
    eax = joystick_direction(&port, stick, 0xb0, (int32_t)port_u32(&port, ebp, -STATE + 4) > 0,
                             0x477130, 0x477160, &edx);
    for (button = 0; button < 0x20; button++)
    {
        uint32_t held = port_u32(&port, stick, 0x24 + button * 4);
        if (port_u8(&port, button, ebp - BUTTONS) & 0x80)
        {
            if (held == 0)
            {
                eax = port_call(&port, 0x476fb0, stick, button, stick, button);
                port_set32(&port, stick, 0x24 + button * 4, 1);
            }
        }
        else if (held == 1)
        {
            eax = port_call(&port, 0x476fe0, stick, button, stick, button);
            port_set32(&port, stick, 0x24 + button * 4, 0);
        }
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_keyboard_poll(PORT_SIGNATURE)
{
    enum
    {
        STATUS = 0x553870,
        LAST_SCAN = 0x553874,
        LAST_KEY = 0x553876,
        EVENTS = 0x553878, /* DIDEVICEOBJECTDATA, 0x14 bytes each */
        EVENT_COUNT = 0x556078,
        EVENT_INDEX = 0x55607c,
        KEY_MAP = 0x4fe600,
        KEYS = 0x54d640,
        IGNORED_KEY = 0x6b
    };
    Port port;
    uint32_t keyboard = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t ecx = entry->ecx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, keyboard, 0xc) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, 0, STATUS, 0x8007001eu);
    /* GetDeviceData for up to 0x200 events; a lost device is reacquired and read again. */
    do
    {
        uint32_t arguments[5];
        uint32_t device = port_u32(&port, keyboard, 0xc);
        uint32_t table = port_u32(&port, device, 0);
        port_set32(&port, 0, EVENT_COUNT, 0x200);
        arguments[0] = device;
        arguments[1] = 0x14;
        arguments[2] = EVENTS;
        arguments[3] = EVENT_COUNT;
        arguments[4] = 0;
        eax = port_call_stack(&port, port_u32(&port, table, 0x28), device, table, keyboard, ecx,
                              arguments, 5);
        port_set32(&port, 0, STATUS, eax);
        if (eax != 0)
        {
            device = port_u32(&port, keyboard, 0xc);
            port_set32(&port, keyboard, 0x10, 0);
            table = port_u32(&port, device, 0);
            arguments[0] = device;
            eax = port_call_stack(&port, port_u32(&port, table, 0x1c), device, table, keyboard, ecx,
                                  arguments, 1);
            if ((int32_t)eax >= 0)
            {
                port_set32(&port, keyboard, 0x10, 1);
            }
            else if (port_u32(&port, keyboard, 0x10) == 0)
            {
                return port_return(&port, eax, entry->edx);
            }
        }
        ecx = port_u32(&port, 0, STATUS);
    } while (ecx != 0);
    eax = port_u32(&port, 0, EVENT_COUNT);
    port_set32(&port, 0, EVENT_INDEX, 0);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    do
    {
        uint32_t scan;
        uint32_t key;
        eax = port_u32(&port, 0, EVENT_INDEX) * 0x14;
        scan = port_u16(&port, eax, EVENTS);
        key = port_u16(&port, 0, scan * 2 + KEY_MAP);
        port_set16(&port, 0, LAST_SCAN, scan);
        port_set16(&port, 0, LAST_KEY, key);
        if (key != IGNORED_KEY)
        {
            /* Key down (data bit 7) or up. */
            uint32_t argument = 0;
            uint32_t target = (port_u8(&port, eax, EVENTS + 4) & 0x80) ? 0x4761d0 : 0x476280;
            eax = port_call_stack(&port, target, KEYS, port_u16(&port, 0, LAST_KEY), 0, 0,
                                  &argument, 1);
        }
        port_set32(&port, 0, EVENT_INDEX, port_u32(&port, 0, EVENT_INDEX) + 1);
    } while (port_u32(&port, 0, EVENT_INDEX) < port_u32(&port, 0, EVENT_COUNT));
    return port_return(&port, eax, entry->edx);
}

/* One screen edge for 0x477f10: entering it (`inside` 1) runs `enter`, leaving it `leave`; the
 * state is kept at `field`. */
static uint32_t mouse_edge(Port *port, uint32_t mouse, uint32_t inside, uint32_t field,
                           uint32_t enter, uint32_t leave, uint32_t *edx, uint32_t ebx)
{
    uint32_t state = port_u32(port, mouse, field);
    uint32_t eax = inside;
    if (state == 0 && inside == 1)
    {
        eax = port_call(port, enter, mouse, *edx, ebx, 1);
        *edx = vertrix_lift_edx;
        port_set32(port, mouse, field, 1);
    }
    else if (state == 1 && inside == 0)
    {
        eax = port_call(port, leave, mouse, *edx, ebx, 1);
        *edx = vertrix_lift_edx;
        port_set32(port, mouse, field, 0);
    }
    return eax;
}

uint32_t vertrix_port_mouse_poll(PORT_SIGNATURE)
{
    enum
    {
        X = 0x5560d4,
        Y = 0x5560d8,
        EVENTS = 0x5560dc, /* DIDEVICEOBJECTDATA: offset, data, ... (0x14 bytes) */
        EVENT_COUNT = 0x5588dc,
        EVENT_INDEX = 0x5588e0,
        STATUS = 0x5588e4,
        START_X = 0x5588e8,
        START_Y = 0x5588ec,
        CLAMP = 0x478480,
        PRESS = 0x4784d0,
        RELEASE = 0x478520
    };
    Port port;
    uint32_t mouse = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, mouse, 8) != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, 0, START_X, port_u16(&port, mouse, 0x48));
    port_set32(&port, 0, START_Y, port_u16(&port, mouse, 0x4a));
    port_set32(&port, 0, X, port_u32(&port, 0, START_X));
    eax = port_u32(&port, 0, START_Y);
    port_set32(&port, 0, Y, eax);
    if (port_u32(&port, mouse, 0x30) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, 0, STATUS, 0x8007001eu);
    ebx = 0;
    /* GetDeviceData for up to 0x200 events; a lost device is reacquired (0x477c30). */
    do
    {
        uint32_t arguments[5];
        uint32_t device = port_u32(&port, mouse, 0x30);
        uint32_t table = port_u32(&port, device, 0);
        arguments[0] = device;
        arguments[1] = 0x14;
        arguments[2] = EVENTS;
        arguments[3] = EVENT_COUNT;
        arguments[4] = 0;
        port_set32(&port, 0, EVENT_COUNT, 0x200);
        result = port_call_stack(&port, port_u32(&port, table, 0x28), device, table, ebx, ecx,
                                 arguments, 5);
        edx = vertrix_lift_edx;
        port_set32(&port, 0, STATUS, result);
        if (result == 0x8000000au || result == 0x80070057u)
        {
            return port_return(&port, result, entry->edx);
        }
        if (result != 0)
        {
            port_set32(&port, mouse, 0xc, 0);
            eax = port_call(&port, 0x477c30, mouse, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            if (port_u32(&port, mouse, 0xc) == 0)
            {
                return port_return(&port, eax, entry->edx);
            }
        }
    } while (port_u32(&port, 0, STATUS) != 0);
    ecx = 0;
    ebx = port_u32(&port, 0, EVENT_COUNT);
    port_set32(&port, 0, EVENT_INDEX, 0);
    if (ebx != 0)
    {
        do
        {
            uint32_t event = port_u32(&port, 0, EVENT_INDEX) * 0x14;
            uint32_t data = port_u32(&port, event, EVENTS + 4);
            uint32_t swap = port_u32(&port, mouse, 0x38);
            uint32_t key = 0;
            ecx = port_u32(&port, event, EVENTS);
            eax = event;
            if (ecx == 0 || ecx == 4)
            {
                /* An axis, scaled by the speed (+0x44) in percent, then clamped. */
                int32_t step = (int32_t)(port_u32(&port, mouse, 0x44) * data) / 100;
                if (ecx == 0)
                {
                    port_set32(&port, 0, X, port_u32(&port, 0, X) + (uint32_t)step);
                    ebx = port_u32(&port, 0, Y);
                }
                else
                {
                    ecx = port_u32(&port, 0, Y) + (uint32_t)step;
                    port_set32(&port, 0, Y, ecx);
                    ebx = ecx;
                }
                eax = port_call(&port, CLAMP, mouse, port_u32(&port, 0, X), ebx, ecx);
            }
            else if (ecx == 0xc || ecx == 0xd)
            {
                /* The two main buttons, swapped when +0x38 is set. */
                key = (ecx == 0xc) == (swap == 0) ? 0x74 : 0x75;
            }
            else if (ecx >= 0xe && ecx <= 0x13)
            {
                key = 0xbe + ecx - 0xe;
            }
            if (key != 0)
            {
                eax = port_call(&port, (port_u8(&port, event, EVENTS + 4) & 0x80) ? PRESS : RELEASE,
                                mouse, key, ebx, ecx);
            }
            port_set32(&port, 0, EVENT_INDEX, port_u32(&port, 0, EVENT_INDEX) + 1);
        } while (port_u32(&port, 0, EVENT_INDEX) < port_u32(&port, 0, EVENT_COUNT));
    }
    if (port_u32(&port, mouse, 0x60) != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    /* Edge scrolling: the position within +0x54 of the left, right, top and bottom of the
     * scroll centre (+0x5c, +0x5e). */
    {
        uint32_t center_x = port_u16(&port, mouse, 0x5c);
        uint32_t margin = port_u32(&port, mouse, 0x54);
        uint32_t inside;
        ebx = port_u16(&port, mouse, 0x48);
        edx = 0;
        inside = ebx < center_x - margin;
        if (inside)
        {
            edx = 1;
        }
        eax = mouse_edge(&port, mouse, inside, 0x64, 0x478570, 0x4785c0, &edx, ebx);
        ebx = port_u16(&port, mouse, 0x48);
        inside = ebx > port_u16(&port, mouse, 0x5c) + port_u32(&port, mouse, 0x54);
        if (inside)
        {
            edx = 1;
        }
        eax = mouse_edge(&port, mouse, inside, 0x68, 0x478610, 0x478660, &edx, ebx);
        if (edx == 1)
        {
            ebx = port_u16(&port, mouse, 0x4a);
            eax = port_call(&port, CLAMP, mouse, port_u16(&port, mouse, 0x5c), ebx, 1);
            edx = vertrix_lift_edx;
        }
        ebx = port_u16(&port, mouse, 0x5e) - port_u32(&port, mouse, 0x54);
        edx = 0;
        inside = port_u16(&port, mouse, 0x4a) < ebx;
        if (inside)
        {
            edx = 1;
        }
        eax = mouse_edge(&port, mouse, inside, 0x6c, 0x4786b0, 0x478700, &edx, ebx);
        ebx = port_u32(&port, mouse, 0x54) + port_u16(&port, mouse, 0x5e);
        inside = port_u16(&port, mouse, 0x4a) > ebx;
        if (inside)
        {
            edx = 1;
        }
        eax = mouse_edge(&port, mouse, inside, 0x70, 0x478750, 0x4787a0, &edx, ebx);
        if (edx == 1)
        {
            eax = port_call(&port, CLAMP, mouse, port_u16(&port, mouse, 0x48),
                            port_u16(&port, mouse, 0x5e), 1);
        }
    }
    return port_return(&port, eax, entry->edx);
}

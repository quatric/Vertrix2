/* DirectInput 8: the system keyboard and mouse, read immediately (GetDeviceState) or buffered
 * (GetDeviceData). The platform feeds them through v3_input_*; game controllers are absent, so
 * the game's own key configuration applies (the Wii driver maps its controllers onto keys). */

#include "win32.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum
{
    DI_OK = 0,
    DI_BUFFEROVERFLOW = 1,
    DIERR_NOTFOUND = 0x80070002u,
    DIERR_INVALIDPARAM = 0x80070057u,
    E_NOINTERFACE = 0x80004002u,
    EVENTS = 256,
    KEYBOARD = 1,
    MOUSE = 2
};

typedef struct
{
    uint32_t offset, data, time, sequence;
} Event;

typedef struct
{
    int kind;
    uint32_t guest;
    uint32_t buffer_size;
    Event events[EVENTS];
    unsigned head, count;
    int overflow;
    uint32_t state_size; /* 16 (DIMOUSESTATE) or 20 (DIMOUSESTATE2) for the mouse */
} Device;

static Device keyboard = {KEYBOARD}, mouse = {MOUSE};
static uint8_t keys[256];
static int32_t mouse_dx, mouse_dy, mouse_dz;
static uint8_t buttons[8];
static uint32_t sequence;
static uint32_t vtable_input, vtable_device, input_object;

static void push(Device *d, uint32_t offset, uint32_t data)
{
    if (!d->buffer_size)
    {
        return;
    }
    if (d->count == EVENTS || d->count >= d->buffer_size)
    {
        d->overflow = 1;
        return;
    }
    Event *e = &d->events[(d->head + d->count) % EVENTS];
    e->offset = offset;
    e->data = data;
    e->time = (uint32_t)(v3_microseconds() / 1000u);
    e->sequence = ++sequence;
    ++d->count;
}

void v3_input_key(unsigned scan_code, int down)
{
    v3_lock();
    if (scan_code < 256 && (keys[scan_code] != 0) != (down != 0))
    {
        keys[scan_code] = down ? 0x80 : 0;
        push(&keyboard, scan_code, down ? 0x80 : 0);
    }
    v3_unlock();
}

void v3_input_mouse_move(int dx, int dy)
{
    v3_lock();
    mouse_dx += dx;
    mouse_dy += dy;
    if (dx)
        push(&mouse, 0, (uint32_t)dx);
    if (dy)
        push(&mouse, 4, (uint32_t)dy);
    v3_unlock();
}

void v3_input_mouse_button(unsigned button, int down)
{
    v3_lock();
    if (button < 8 && (buttons[button] != 0) != (down != 0))
    {
        buttons[button] = down ? 0x80 : 0;
        push(&mouse, 12 + button, down ? 0x80 : 0);
    }
    v3_unlock();
}

static Device *device_of(uint32_t guest)
{
    return guest == keyboard.guest ? &keyboard : guest == mouse.guest ? &mouse : NULL;
}

static void unimplemented(Cpu *c)
{
    v3_log("unimplemented DirectInput method %s", v3_host_current);
    v3_trap(c, v3_r32(c->esp), "unimplemented DirectInput method");
}

static void QueryInterface(Cpu *c)
{
    if (ARG(2))
    {
        v3_w32(ARG(2), 0);
    }
    STDCALL_RETURN(3, E_NOINTERFACE);
}

static void AddRef(Cpu *c)
{
    STDCALL_RETURN(1, 2);
}

static void Release(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

/* --- IDirectInput8A ------------------------------------------------------------------------- */

static void CreateDevice(Cpu *c)
{
    const uint32_t guid = v3_r32(ARG(1));
    Device *d = guid == 0x6f1d2b61u ? &keyboard : guid == 0x6f1d2b60u ? &mouse : NULL;
    v3_log("DirectInput CreateDevice({%08x}) -> %s", guid,
           d == &keyboard ? "keyboard" : d == &mouse ? "mouse" : "not found");
    if (!d)
    {
        v3_w32(ARG(2), 0);
        STDCALL_RETURN(4, DIERR_NOTFOUND);
    }
    if (!d->guest)
    {
        d->guest = v3_system_alloc(16);
        v3_w32(d->guest, vtable_device);
    }
    v3_w32(ARG(2), d->guest);
    STDCALL_RETURN(4, DI_OK);
}

static void EnumDevices(Cpu *c)
{
    /* No game controllers. */
    STDCALL_RETURN(5, DI_OK);
}

static void GetDeviceStatus(Cpu *c)
{
    STDCALL_RETURN(2, DI_OK);
}

static void Initialize(Cpu *c)
{
    STDCALL_RETURN(3, DI_OK);
}

/* --- IDirectInputDevice8A ------------------------------------------------------------------- */

static void GetCapabilities(Cpu *c)
{
    Device *d = device_of(ARG(0));
    const uint32_t caps = ARG(1);
    const uint32_t size = v3_r32(caps);
    memset(MEM(caps + 4), 0, size > 4 && size <= 44 ? size - 4 : 40);
    v3_w32(caps + 4, 0x5); /* attached, polled-data-format */
    v3_w32(caps + 8, d && d->kind == KEYBOARD ? 0x13 : 0x12);
    v3_w32(caps + 12, d && d->kind == KEYBOARD ? 0 : 3);
    v3_w32(caps + 16, d && d->kind == KEYBOARD ? 256 : 4);
    STDCALL_RETURN(2, DI_OK);
}

static void EnumObjects(Cpu *c)
{
    STDCALL_RETURN(4, DI_OK);
}

static void GetProperty(Cpu *c)
{
    Device *d = device_of(ARG(0));
    if (ARG(1) == 1 && d) /* DIPROP_BUFFERSIZE */
    {
        v3_w32(ARG(2) + 16, d->buffer_size);
    }
    STDCALL_RETURN(3, DI_OK);
}

static void SetProperty(Cpu *c)
{
    Device *d = device_of(ARG(0));
    if (ARG(1) == 1 && d) /* DIPROP_BUFFERSIZE: a DIPROPDWORD */
    {
        d->buffer_size = v3_r32(ARG(2) + 16);
        v3_log("DirectInput buffer size %u", d->buffer_size);
    }
    STDCALL_RETURN(3, DI_OK);
}

static void Acquire(Cpu *c)
{
    STDCALL_RETURN(1, DI_OK);
}

static void Unacquire(Cpu *c)
{
    STDCALL_RETURN(1, DI_OK);
}

static void GetDeviceState(Cpu *c)
{
    Device *d = device_of(ARG(0));
    const uint32_t size = ARG(1);
    const uint32_t out = ARG(2);
    v3_lock();
    if (d == &keyboard)
    {
        for (uint32_t i = 0; i < size && i < 256; ++i)
        {
            v3_w8(out + i, keys[i]);
        }
    }
    else if (d == &mouse)
    {
        v3_w32(out, (uint32_t)mouse_dx);
        v3_w32(out + 4, (uint32_t)mouse_dy);
        v3_w32(out + 8, (uint32_t)mouse_dz);
        for (uint32_t i = 0; 12 + i < size && i < 8; ++i)
        {
            v3_w8(out + 12 + i, buttons[i]);
        }
        mouse_dx = mouse_dy = mouse_dz = 0;
    }
    v3_unlock();
    STDCALL_RETURN(3, DI_OK);
}

static void GetDeviceData(Cpu *c)
{
    Device *d = device_of(ARG(0));
    const uint32_t object_size = ARG(1);
    const uint32_t out = ARG(2);
    const uint32_t in_out = ARG(3);
    const uint32_t flags = ARG(4);
    uint32_t wanted = v3_r32(in_out);
    uint32_t given = 0;
    v3_lock();
    const int overflow = d && d->overflow;
    if (d)
    {
        d->overflow = 0;
        while (given < wanted && given < d->count)
        {
            const Event *e = &d->events[(d->head + given) % EVENTS];
            if (out)
            {
                const uint32_t at = out + given * object_size;
                memset(MEM(at), 0, object_size);
                v3_w32(at, e->offset);
                v3_w32(at + 4, e->data);
                v3_w32(at + 8, e->time);
                v3_w32(at + 12, e->sequence);
            }
            ++given;
        }
        if (!(flags & 1)) /* not DIGDD_PEEK */
        {
            d->head = (d->head + given) % EVENTS;
            d->count -= given;
        }
        if (!out && wanted == 0xffffffffu)
        {
            /* Flush. */
            d->head = d->count = 0;
        }
    }
    v3_unlock();
    v3_w32(in_out, given);
    STDCALL_RETURN(5, overflow ? DI_BUFFEROVERFLOW : DI_OK);
}

static void SetDataFormat(Cpu *c)
{
    Device *d = device_of(ARG(0));
    const uint32_t format = ARG(1);
    if (d == &mouse)
    {
        d->state_size = v3_r32(format + 12);
    }
    STDCALL_RETURN(2, DI_OK);
}

static void SetEventNotification(Cpu *c)
{
    STDCALL_RETURN(2, DI_OK);
}

static void SetCooperativeLevel(Cpu *c)
{
    STDCALL_RETURN(3, DI_OK);
}

static void Poll(Cpu *c)
{
    STDCALL_RETURN(1, 1); /* DI_NOEFFECT */
}

static void GetDeviceInfo(Cpu *c)
{
    STDCALL_RETURN(2, DIERR_INVALIDPARAM);
}

typedef struct
{
    unsigned slot;
    const char *name;
    V3Code code;
} Method;

static uint32_t make_vtable(const char *interface, unsigned slots, const Method *methods)
{
    const uint32_t table = v3_system_alloc(4 * slots);
    for (unsigned i = 0; i < slots; ++i)
    {
        V3Code code = unimplemented;
        const char *name = "?";
        for (const Method *m = methods; m->name; ++m)
        {
            if (m->slot == i)
            {
                code = m->code;
                name = m->name;
            }
        }
        char *label = malloc(96);
        snprintf(label, 96, "%s::%s#%u", interface, name, i);
        v3_w32(table + 4 * i, v3_host_function(label, code));
    }
    return table;
}

static void DirectInput8Create(Cpu *c)
{
    static const Method input[] = {{0, "QueryInterface", QueryInterface},
                                   {1, "AddRef", AddRef},
                                   {2, "Release", Release},
                                   {3, "CreateDevice", CreateDevice},
                                   {4, "EnumDevices", EnumDevices},
                                   {5, "GetDeviceStatus", GetDeviceStatus},
                                   {7, "Initialize", Initialize},
                                   {0, NULL, NULL}};
    static const Method device[] = {{0, "QueryInterface", QueryInterface},
                                    {1, "AddRef", AddRef},
                                    {2, "Release", Release},
                                    {3, "GetCapabilities", GetCapabilities},
                                    {4, "EnumObjects", EnumObjects},
                                    {5, "GetProperty", GetProperty},
                                    {6, "SetProperty", SetProperty},
                                    {7, "Acquire", Acquire},
                                    {8, "Unacquire", Unacquire},
                                    {9, "GetDeviceState", GetDeviceState},
                                    {10, "GetDeviceData", GetDeviceData},
                                    {11, "SetDataFormat", SetDataFormat},
                                    {12, "SetEventNotification", SetEventNotification},
                                    {13, "SetCooperativeLevel", SetCooperativeLevel},
                                    {15, "GetDeviceInfo", GetDeviceInfo},
                                    {25, "Poll", Poll},
                                    {0, NULL, NULL}};
    if (!vtable_input)
    {
        vtable_input = make_vtable("IDirectInput8A", 11, input);
        vtable_device = make_vtable("IDirectInputDevice8A", 32, device);
        input_object = v3_system_alloc(16);
        v3_w32(input_object, vtable_input);
    }
    v3_log("DirectInput8Create(version %x)", ARG(1));
    v3_w32(ARG(3), input_object);
    STDCALL_RETURN(5, DI_OK);
}

const V3Export v3_dinput8[] = {{"DirectInput8Create", DirectInput8Create}, {NULL, NULL}};

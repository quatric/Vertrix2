#include "rtlsounddeviceopens.h"

enum
{
    /* The frame below the return slot, and the structures the device methods get by address
     * (offsets from the original's ebp, entry->esp - 4): DSCAPS (0x60 bytes, its dwFlags at +4),
     * DSBUFFERDESC (0x14 bytes) and WAVEFORMATEX. */
    BELOW = 0xa0,
    CAPS = 0x9c,
    CAPS_SIZE = 0x60,
    CAPS_FLAGS = 0x98,
    DESC = 0x3c,
    DESC_SIZE = 0x14,
    FORMAT = 0x28,

    /* WAVEFORMATEX fields, as offsets from the format. */
    FORMAT_TAG = 0x0,
    FORMAT_CHANNELS = 0x2,
    FORMAT_RATE = 0x4,
    FORMAT_BYTES_PER_SECOND = 0x8,
    FORMAT_ALIGN = 0xc,
    FORMAT_BITS = 0xe,
    FORMAT_EXTRA = 0x10,
    PCM = 1,

    /* DSBUFFERDESC fields: the size, DSBCAPS_PRIMARYBUFFER, the buffer bytes and the format. */
    DESC_FLAGS = 0x4,
    DESC_BYTES = 0x8,
    DESC_FORMAT = 0x10,
    PRIMARY_BUFFER = 1,

    /* DSCAPS flags: DSCAPS_PRIMARYSTEREO and DSCAPS_PRIMARY16BIT. */
    CAN_STEREO = 0x2,
    CAN_16BIT = 0x8,

    /* The config: 16-bit (bit 0 of +4), stereo (bit 0 of +5) and the rate (+6). */
    CONFIG_16BIT = 0x4,
    CONFIG_STEREO = 0x5,
    CONFIG_RATE = 0x6,
    FIRST_RATE = 44100,
    LOWEST_RATE = 0x2b11,

    /* The sound state: 0x79c bytes from the device, the primary buffer after it. */
    STATE = 0x52f170,
    STATE_SIZE = 0x79c,
    PRIMARY = 0x52f174,
    START_TICK = 0x52f900,
    MIXED = 0x52f904,
    /* 256 dwords of (-256000 + 2000 i) >> 7. */
    PAN_TABLE = 0x52f300,
    PAN_FIRST = 0xfffc1800u,
    PAN_STEP = 0x7d0,
    PAN_SHIFT = 7,
    PAN_END = 0x400,

    PRIORITY = 2,
    CURVE_STEP = 0x60,
    CURVE_KIND = 1,

    /* IDirectSound and IDirectSoundBuffer methods. */
    SET_COOPERATIVE_LEVEL = 0x18,
    GET_CAPS = 0x10,
    CREATE_SOUND_BUFFER = 0xc,
    SET_FORMAT = 0x38,
    PLAY = 0x30,
    PLAY_LOOPING = 1,

    NO_DEVICE = 2,
    FAILED = 5,

    FILL = 0x4eb5c0,
    DEVICE_CREATE = 0x40b620,
    DEVICE_RELEASE = 0x40b660,
    CURVE_TABLE_BUILD = 0x40ba00,
    GET_FOREGROUND_WINDOW = 0x4f1994,
    GET_TICK_COUNT = 0x4f1bf8
};

/* A COM method: an unknown call, which reads all four registers, handed what the original leaves
 * in them. Its edx comes back in vertrix_lift_edx. */
static uint32_t method(Port *port, uint32_t object, uint32_t slot, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *stack, unsigned count)
{
    const uint32_t vtable = port_u32(port, object, 0);
    return port_call_stack(port, port_u32(port, vtable, slot), eax, edx, ebx, ecx, stack, count);
}

/* Original 0x40b6e0 (eax = the sound config): opens the DirectSound device. Clears the sound
 * state (0x79c bytes at 0x52f170); returns 2 for a null config and 5 when the device cannot be
 * created (0x40b620). Sets the cooperative level for the foreground window (priority), reads the
 * caps and clears the config's stereo and 16-bit bits where the device has no primary stereo or
 * 16-bit, then creates the primary buffer into 0x52f174 and sets its format, PCM from 44100 Hz,
 * halving the rate after each refusal while it is above 11025 Hz. Then plays it looping, keeps
 * the tick count at 0x52f900, clears 0x52f904, builds the volume curve (0x40ba00 kind 1 step 0x60)
 * and the pan table at 0x52f300, and returns 0. A failure after the device exists releases it
 * (0x40b660) and returns 5. Returns the caller's edx. */
uint32_t vertrix_port_sound_device_open_40b6e0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t config = entry->eax;
    const uint32_t caps = frame - CAPS;
    const uint32_t desc = frame - DESC;
    const uint32_t format = frame - FORMAT;

    port_call(&port, FILL, STATE, 0, STATE_SIZE, entry->ecx);
    if (config == 0)
    {
        return port_return(&port, NO_DEVICE, entry->edx);
    }
    if (port_call(&port, DEVICE_CREATE, 0, STATE, 0, entry->ecx) != 0)
    {
        return port_return(&port, FAILED, entry->edx);
    }

    uint32_t device = port_u32(&port, STATE, 0);
    uint32_t release_ecx = entry->ecx;
    const uint32_t vtable = port_u32(&port, device, 0);
    const uint32_t window = port_call(&port, GET_FOREGROUND_WINDOW, 0, 0, 0, 0);
    const uint32_t level[3] = {device, window, PRIORITY};
    if (method(&port, device, SET_COOPERATIVE_LEVEL, window, device, vtable, entry->ecx, level,
               3) != 0)
    {
        goto failed;
    }

    port_set32(&port, caps, 0, CAPS_SIZE);
    device = port_u32(&port, STATE, 0);
    const uint32_t get_caps[2] = {device, caps};
    release_ecx = caps;
    if (method(&port, device, GET_CAPS, device, port_u32(&port, device, 0), vtable, caps, get_caps,
               2) != 0)
    {
        goto failed;
    }

    port_set16(&port, config, CONFIG_RATE, FIRST_RATE);
    const uint32_t device_flags = port_u8(&port, frame - CAPS_FLAGS, 0);
    if ((device_flags & CAN_STEREO) == 0)
    {
        port_set8(&port, config, CONFIG_STEREO, port_u8(&port, config, CONFIG_STEREO) & 0xfe);
    }
    if ((device_flags & CAN_16BIT) == 0)
    {
        port_set8(&port, config, CONFIG_16BIT, port_u8(&port, config, CONFIG_16BIT) & 0xfe);
    }
    const int stereo = (port_u8(&port, config, CONFIG_STEREO) & 1) != 0;
    const int wide = (port_u8(&port, config, CONFIG_16BIT) & 1) != 0;
    port_set16(&port, format, FORMAT_TAG, PCM);
    port_set16(&port, format, FORMAT_CHANNELS, stereo ? 2 : 1);
    port_set16(&port, format, FORMAT_BITS, wide ? 16 : 8);
    const uint32_t rate = port_u16(&port, config, CONFIG_RATE);
    port_set32(&port, format, FORMAT_RATE, rate);
    port_set32(&port, format, FORMAT_BYTES_PER_SECOND, rate);
    port_set16(&port, format, FORMAT_ALIGN, 1);
    port_set16(&port, format, FORMAT_EXTRA, 0);
    if (stereo)
    {
        port_set32(&port, format, FORMAT_BYTES_PER_SECOND, rate * 2);
        port_set16(&port, format, FORMAT_ALIGN, 2);
    }
    if (wide)
    {
        port_set32(&port, format, FORMAT_BYTES_PER_SECOND,
                   port_u32(&port, format, FORMAT_BYTES_PER_SECOND) * 2);
        port_set16(&port, format, FORMAT_ALIGN, port_u32(&port, format, FORMAT_ALIGN) * 2);
    }

    port_call(&port, FILL, desc, 0, DESC_SIZE, 0);
    port_set32(&port, desc, 0, DESC_SIZE);
    port_set32(&port, desc, DESC_FLAGS, PRIMARY_BUFFER);
    port_set32(&port, desc, DESC_BYTES, 0);
    port_set32(&port, desc, DESC_FORMAT, 0);
    device = port_u32(&port, STATE, 0);
    const uint32_t create[4] = {device, desc, PRIMARY, 0};
    release_ecx = desc;
    if (method(&port, device, CREATE_SOUND_BUFFER, device, port_u32(&port, device, 0), DESC_SIZE,
               desc, create, 4) != 0)
    {
        goto failed;
    }

    for (;;)
    {
        const uint32_t primary = port_u32(&port, PRIMARY, 0);
        const uint32_t buffer_vtable = port_u32(&port, primary, 0);
        const uint32_t set_format[2] = {primary, format};
        release_ecx = buffer_vtable;
        if (method(&port, primary, SET_FORMAT, primary, format, DESC_SIZE, buffer_vtable,
                   set_format, 2) == 0)
        {
            break;
        }
        if (port_u16(&port, config, CONFIG_RATE) <= LOWEST_RATE || port.env.failed)
        {
            goto failed;
        }
        port_set32(&port, format, FORMAT_RATE, port_u32(&port, format, FORMAT_RATE) >> 1);
        port_set32(&port, format, FORMAT_BYTES_PER_SECOND,
                   port_u32(&port, format, FORMAT_BYTES_PER_SECOND) >> 1);
        port_set16(&port, format, FORMAT_ALIGN, port_u16(&port, format, FORMAT_ALIGN) >> 1);
        port_set16(&port, config, CONFIG_RATE, port_u16(&port, config, CONFIG_RATE) >> 1);
    }

    const uint32_t primary = port_u32(&port, PRIMARY, 0);
    const uint32_t buffer_vtable = port_u32(&port, primary, 0);
    const uint32_t play[4] = {primary, 0, 0, PLAY_LOOPING};
    method(&port, primary, PLAY, primary, buffer_vtable, DESC_SIZE, buffer_vtable, play, 4);
    port_set32(&port, START_TICK, 0, port_call(&port, GET_TICK_COUNT, 0, 0, 0, 0));
    port_set32(&port, MIXED, 0, 0);
    port_call(&port, CURVE_TABLE_BUILD, CURVE_KIND, CURVE_STEP, DESC_SIZE, buffer_vtable);
    uint32_t pan = PAN_FIRST;
    for (uint32_t at = 0; at != PAN_END && !port.env.failed; at += 4)
    {
        port_set32(&port, PAN_TABLE + at, 0, (uint32_t)((int32_t)pan >> PAN_SHIFT));
        pan += PAN_STEP;
    }
    return port_return(&port, 0, entry->edx);

failed:
    port_call(&port, DEVICE_RELEASE, port_u32(&port, STATE, 0), vertrix_lift_edx, 0, release_ecx);
    return port_return(&port, FAILED, entry->edx);
}

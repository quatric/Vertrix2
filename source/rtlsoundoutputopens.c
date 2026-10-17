#include "rtlsoundoutputopens.h"

enum
{
    /* The frame below the return slot, and the structures the device methods get by address
     * (offsets from the original's ebp, entry->esp - 4): DSCAPS (0x60 bytes, its dwFlags at +4),
     * DSBUFFERDESC (0x14 bytes), the primary buffer's DSBCAPS (0x14 bytes, its dwBufferBytes at
     * +8) and WAVEFORMATEX. */
    BELOW = 0xb0,
    CAPS = 0xb0,
    CAPS_SIZE = 0x60,
    CAPS_FLAGS = 0xac,
    DESC = 0x50,
    DESC_SIZE = 0x14,
    BUFFER_CAPS = 0x3c,
    BUFFER_CAPS_SIZE = 0x14,
    BUFFER_CAPS_BYTES = 0x34,
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

    /* DSBUFFERDESC fields: the size, the flags, the buffer bytes and the format. The primary
     * buffer has DSBCAPS_PRIMARYBUFFER, the streaming one DSBCAPS_GETCURRENTPOSITION2 and
     * DSBCAPS_STICKYFOCUS. */
    DESC_FLAGS = 0x4,
    DESC_BYTES = 0x8,
    DESC_FORMAT = 0x10,
    PRIMARY_BUFFER = 1,
    STREAM_BUFFER = 0x14000,

    /* DSCAPS flags, by byte: DSCAPS_PRIMARYSTEREO and DSCAPS_EMULDRIVER in the first,
     * DSCAPS_SECONDARY16BIT (0x800) in the second. */
    CAN_STEREO = 0x2,
    EMULATED = 0x20,
    CAN_16BIT = 0x8,

    /* The config: 16-bit (bit 0 of +4), stereo (bit 0 of +5) and the rate (+6). */
    CONFIG_16BIT = 0x4,
    CONFIG_STEREO = 0x5,
    CONFIG_RATE = 0x6,
    LOWEST_RATE = 0x2b11,

    /* The output state: 0x1c bytes from the device, the primary and the streaming buffer, the
     * stream position and size, then the rate and the config's flag bytes. */
    STATE = 0x52f150,
    STATE_SIZE = 0x1c,
    PRIMARY = 0x52f154,
    STREAM = 0x52f158,
    STREAM_POSITION = 0x52f160,
    STREAM_BYTES = 0x52f164,
    RATE = 0x52f168,
    FLAGS = 0x52f16a,

    /* The streaming buffer holds between 20 and 100 ms of sound, 150 ms on an emulated driver. */
    SHORTEST_MS = 20,
    LONGEST_MS = 100,
    EMULATED_MS = 150,
    MS_PER_SECOND = 1000,

    PRIORITY = 2,

    /* IDirectSound and IDirectSoundBuffer methods. */
    SET_COOPERATIVE_LEVEL = 0x18,
    GET_CAPS = 0x10,
    CREATE_SOUND_BUFFER = 0xc,
    RELEASE = 0x8,
    BUFFER_GET_CAPS = 0xc,
    SET_FORMAT = 0x38,
    PLAY = 0x30,
    PLAY_LOOPING = 1,

    FAILED = 5,

    FILL = 0x4eb5c0,
    DEVICE_CREATE = 0x40b040,
    DEVICE_RELEASE = 0x40b080,
    GET_FOREGROUND_WINDOW = 0x4f1994
};

/* A COM method: an unknown call, which reads all four registers, handed what the original leaves
 * in them. Its edx comes back in vertrix_lift_edx. */
static uint32_t method(Port *port, uint32_t object, uint32_t slot, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *stack, unsigned count)
{
    const uint32_t vtable = port_u32(port, object, 0);
    return port_call_stack(port, port_u32(port, vtable, slot), eax, edx, ebx, ecx, stack, count);
}

/* Release the device (0x40b080) after a failed step, and return 5. ecx is what the original
 * leaves in it at that step. */
static uint32_t release(Port *port, uint32_t ecx, uint32_t edx)
{
    port_call(port, DEVICE_RELEASE, port_u32(port, STATE, 0), vertrix_lift_edx, 0, ecx);
    return port_return(port, FAILED, edx);
}

/* Original 0x40b110 (eax = the sound config): opens the DirectSound output. Clears the output
 * state (0x1c bytes at 0x52f150) and creates the device (0x40b040), returning 5 when it cannot.
 * Sets the cooperative level for the foreground window (priority), reads the caps and clears the
 * config's stereo and 16-bit bits where the device has no primary stereo or secondary 16-bit, then
 * creates the primary buffer into 0x52f154 and sets its PCM format, halving the rate after each
 * refusal while it is above 11025 Hz. The streaming buffer (0x52f158) gets the primary's size
 * held between 20 and 100 ms of sound (at least 150 ms on an emulated driver), a multiple of 4;
 * its position (0x52f160) starts at 0 and its size goes to 0x52f164. Both buffers play looping,
 * the rate and the config's flags go to 0x52f168, and it returns 0. A failure after the device
 * exists releases it (0x40b080, the primary buffer first once that exists) and returns 5. Returns
 * the caller's edx. */
uint32_t vertrix_port_sound_output_open_40b110(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    port_set32(&port, frame, 0, entry->ebp);
    const uint32_t config = entry->eax;
    const uint32_t caps = frame - CAPS;
    const uint32_t desc = frame - DESC;
    const uint32_t buffer_caps = frame - BUFFER_CAPS;
    const uint32_t format = frame - FORMAT;

    port_call(&port, FILL, STATE, 0, STATE_SIZE, 0);
    if (port_call(&port, DEVICE_CREATE, 0, STATE, 0, entry->ecx) != 0)
    {
        return port_return(&port, FAILED, entry->edx);
    }

    uint32_t device = port_u32(&port, STATE, 0);
    const uint32_t first_vtable = port_u32(&port, device, 0);
    const uint32_t window = port_call(&port, GET_FOREGROUND_WINDOW, 0, 0, 0, 0);
    device = port_u32(&port, STATE, 0);
    /* Through the vtable read before the window was found. */
    const uint32_t level[3] = {device, window, PRIORITY};
    if (port_call_stack(&port, port_u32(&port, first_vtable, SET_COOPERATIVE_LEVEL), window, device,
                        first_vtable, entry->ecx, level, 3) != 0)
    {
        return release(&port, entry->ecx, entry->edx);
    }

    port_set32(&port, caps, 0, CAPS_SIZE);
    device = port_u32(&port, STATE, 0);
    uint32_t vtable = port_u32(&port, device, 0);
    const uint32_t get_caps[2] = {device, caps};
    if (method(&port, device, GET_CAPS, device, caps, first_vtable, vtable, get_caps, 2) != 0)
    {
        return release(&port, vtable, entry->edx);
    }

    if ((port_u8(&port, frame - CAPS_FLAGS, 0) & CAN_STEREO) == 0)
    {
        port_set8(&port, config, CONFIG_STEREO, port_u8(&port, config, CONFIG_STEREO) & 0xfe);
    }
    if ((port_u8(&port, frame - CAPS_FLAGS, 1) & CAN_16BIT) == 0)
    {
        port_set8(&port, config, CONFIG_16BIT, port_u8(&port, config, CONFIG_16BIT) & 0xfe);
    }
    port_set16(&port, format, FORMAT_TAG, PCM);
    port_set16(&port, format, FORMAT_CHANNELS, (port_u8(&port, config, CONFIG_STEREO) & 1) ? 2 : 1);
    port_set16(&port, format, FORMAT_BITS, (port_u8(&port, config, CONFIG_16BIT) & 1) ? 16 : 8);
    const uint32_t rate = port_u16(&port, config, CONFIG_RATE);
    port_set32(&port, format, FORMAT_RATE, rate);
    port_set32(&port, format, FORMAT_BYTES_PER_SECOND, rate);
    port_set16(&port, format, FORMAT_ALIGN, 1);
    port_set16(&port, format, FORMAT_EXTRA, 0);
    if (port_u8(&port, config, CONFIG_STEREO) & 1)
    {
        port_set32(&port, format, FORMAT_BYTES_PER_SECOND, rate * 2);
        port_set16(&port, format, FORMAT_ALIGN, 2);
    }
    if (port_u8(&port, config, CONFIG_16BIT) & 1)
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
    vtable = port_u32(&port, device, 0);
    const uint32_t create_primary[4] = {device, desc, PRIMARY, 0};
    if (method(&port, device, CREATE_SOUND_BUFFER, device, desc, 0, vtable, create_primary, 4) != 0)
    {
        return release(&port, vtable, entry->edx);
    }

    /* Set the primary buffer's format, halving the rate while it is refused. A failure from here
     * on releases the primary buffer before the device. */
    uint32_t primary_ecx;
    for (;;)
    {
        const uint32_t primary = port_u32(&port, PRIMARY, 0);
        primary_ecx = port_u32(&port, primary, 0);
        const uint32_t set_format[2] = {primary, format};
        if (method(&port, primary, SET_FORMAT, primary, format, 0, primary_ecx, set_format, 2) == 0)
        {
            break;
        }
        if (port_u16(&port, config, CONFIG_RATE) <= LOWEST_RATE || port.env.failed)
        {
            goto release_primary;
        }
        port_set32(&port, format, FORMAT_RATE, port_u32(&port, format, FORMAT_RATE) >> 1);
        port_set32(&port, format, FORMAT_BYTES_PER_SECOND,
                   port_u32(&port, format, FORMAT_BYTES_PER_SECOND) >> 1);
        port_set16(&port, format, FORMAT_ALIGN, port_u16(&port, format, FORMAT_ALIGN) >> 1);
        port_set16(&port, config, CONFIG_RATE, port_u16(&port, config, CONFIG_RATE) >> 1);
    }

    port_set32(&port, buffer_caps, 0, BUFFER_CAPS_SIZE);
    {
        const uint32_t primary = port_u32(&port, PRIMARY, 0);
        const uint32_t get_buffer_caps[2] = {primary, buffer_caps};
        primary_ecx = buffer_caps;
        if (method(&port, primary, BUFFER_GET_CAPS, primary, port_u32(&port, primary, 0), 0,
                   buffer_caps, get_buffer_caps, 2) != 0)
        {
            goto release_primary;
        }
    }

    /* The primary buffer's size, held between 20 and 100 ms of sound (150 ms at least on an
     * emulated driver), down to a multiple of 4. */
    const uint32_t per_second = port_u32(&port, format, FORMAT_BYTES_PER_SECOND);
    uint32_t bytes = port_u32(&port, frame - BUFFER_CAPS_BYTES, 0);
    if (per_second * LONGEST_MS / MS_PER_SECOND < bytes)
    {
        bytes = per_second * LONGEST_MS / MS_PER_SECOND;
    }
    if (per_second * SHORTEST_MS / MS_PER_SECOND > bytes)
    {
        bytes = per_second * SHORTEST_MS / MS_PER_SECOND;
    }
    if ((port_u8(&port, frame - CAPS_FLAGS, 0) & EMULATED) &&
        per_second * EMULATED_MS / MS_PER_SECOND > bytes)
    {
        bytes = per_second * EMULATED_MS / MS_PER_SECOND;
    }
    bytes &= ~3u;
    port_set32(&port, frame - BUFFER_CAPS_BYTES, 0, bytes);

    port_call(&port, FILL, desc, 0, DESC_SIZE, 0);
    port_set32(&port, desc, 0, DESC_SIZE);
    port_set32(&port, desc, DESC_FLAGS, STREAM_BUFFER);
    port_set32(&port, desc, DESC_BYTES, bytes);
    port_set32(&port, desc, DESC_FORMAT, format);
    device = port_u32(&port, STATE, 0);
    vtable = port_u32(&port, device, 0);
    const uint32_t create_stream[4] = {device, desc, STREAM, 0};
    if (method(&port, device, CREATE_SOUND_BUFFER, device, desc, DESC_SIZE, vtable, create_stream,
               4) != 0)
    {
        return release(&port, vtable, entry->edx);
    }
    port_set32(&port, STREAM_POSITION, 0, 0);
    port_set32(&port, STREAM_BYTES, 0, port_u32(&port, desc, DESC_BYTES));

    static const uint32_t buffers[] = {PRIMARY, STREAM};
    for (size_t i = 0; i < sizeof buffers / sizeof buffers[0]; i++)
    {
        const uint32_t buffer = port_u32(&port, buffers[i], 0);
        const uint32_t play[4] = {buffer, 0, 0, PLAY_LOOPING};
        method(&port, buffer, PLAY, buffer, port_u32(&port, buffer, 0), 0, vtable, play, 4);
    }
    port_set16(&port, RATE, 0, port_u16(&port, config, CONFIG_RATE));
    port_set16(&port, FLAGS, 0, port_u16(&port, config, CONFIG_16BIT));
    return port_return(&port, 0, entry->edx);

release_primary:
    {
        const uint32_t primary = port_u32(&port, PRIMARY, 0);
        const uint32_t release_primary[1] = {primary};
        method(&port, primary, RELEASE, primary, port_u32(&port, primary, 0), 0, primary_ecx,
               release_primary, 1);
        return release(&port, primary_ecx, entry->edx);
    }
}

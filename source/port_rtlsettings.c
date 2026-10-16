#include "port_rtlsettings.h"

/* Default game settings. */

/* The text at `source` copied to `target` up to and including its end 0. */
static void copy_text(Port *port, uint32_t target, uint32_t source)
{
    uint32_t index = 0;
    uint32_t value;
    do
    {
        value = port_u8(port, source, index);
        port_set8(port, target, index, value);
        index++;
    } while (value != 0 && !port->env.failed);
}

/* Original 0x4290c0: the settings eax given their defaults: +0x228 the class 0x514554; +0 2,
 * +4 0x14, +8 1, +0xc 5, +0x10 0, +0x14 1, +0x18 0xc8; the keys +0x1c..+0x2c 0x5f, 0x60, 0x5d,
 * 0x62, 0x72, 0x73, 0x74, 0x75, 0x39; the volumes +0x30 0x30 and +0x34 0x40 with their scaled
 * +0x54/+0x58 (100 / 64 of each); +0x38..+0x44 from 0x532c98, 0x4f8300, 0x4f8370 and 0x4f81d0;
 * +0x48..+0x50 0; the scores +0x5c 100000, +0x60 100000, +0x64 50000, +0x68 10000, +0x6c 5000;
 * the texts 0x50e095, 0x50e099, 0x50e09d, 0x50e0a0 and 0x50e0a4 at +0x70..+0x80; +0x84 1,
 * +0x88 5, +0x8c 0, +0x90 1, +0x94 0; and the texts 0x50e0a8, 0x50e0ad, 0x50e0b4 and 0x50e0c4
 * at +0x98, +0xfc, +0x160 and +0x1c4. eax the settings, edx kept. */
uint32_t vertrix_port_settings_defaults_4290c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    static const uint16_t keys[9] = {0x5f, 0x60, 0x5d, 0x62, 0x72, 0x73, 0x74, 0x75, 0x39};
    static const uint32_t short_texts[5] = {0x50e095, 0x50e099, 0x50e09d, 0x50e0a0, 0x50e0a4};
    static const uint32_t long_texts[4][2] = {
        {0x50e0a8, 0x98}, {0x50e0ad, 0xfc}, {0x50e0b4, 0x160}, {0x50e0c4, 0x1c4}};
    Port port;
    uint32_t settings = entry->eax;
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->edx);
    port_set32(&port, entry->esp, -0xcu, entry->esi);
    port_set32(&port, entry->esp, -0x10u, entry->edi);
    port_set32(&port, settings, 0x228, 0x514554);
    port_set32(&port, settings, 0, 2);
    port_set32(&port, settings, 4, 0x14);
    port_set32(&port, settings, 8, 1);
    port_set32(&port, settings, 0xc, 5);
    port_set32(&port, settings, 0x10, 0);
    port_set32(&port, settings, 0x14, 1);
    port_set32(&port, settings, 0x18, 0xc8);
    for (index = 0; index < 9; index++)
    {
        port_set16(&port, settings, 0x1c + index * 2, keys[index]);
    }
    port_set32(&port, settings, 0x30, 0x30);
    port_set32(&port, settings, 0x34, 0x40);
    port_set32(&port, settings, 0x38, port_u32(&port, 0, 0x532c98));
    port_set32(&port, settings, 0x3c, port_u32(&port, 0, 0x4f8300));
    port_set32(&port, settings, 0x40, port_u32(&port, 0, 0x4f8370));
    port_set32(&port, settings, 0x44, port_u32(&port, 0, 0x4f81d0));
    port_set32(&port, settings, 0x48, 0);
    port_set32(&port, settings, 0x4c, 0);
    port_set32(&port, settings, 0x50, 0);
    port_set32(&port, settings, 0x54, (port_u32(&port, settings, 0x30) * 100) >> 6);
    port_set32(&port, settings, 0x5c, 100000);
    port_set32(&port, settings, 0x60, 100000);
    port_set32(&port, settings, 0x64, 50000);
    port_set32(&port, settings, 0x68, 10000);
    port_set32(&port, settings, 0x6c, 5000);
    port_set32(&port, settings, 0x58, (port_u32(&port, settings, 0x34) * 100) >> 6);
    for (index = 0; index < 5; index++)
    {
        uint32_t target = settings + 0x70 + index * 4;
        port_set32(&port, entry->esp, -0x14u, target);
        copy_text(&port, target, short_texts[index]);
    }
    port_set32(&port, settings, 0x84, 1);
    port_set32(&port, settings, 0x88, 5);
    port_set32(&port, settings, 0x8c, 0);
    port_set32(&port, settings, 0x90, 1);
    port_set32(&port, settings, 0x94, 0);
    for (index = 0; index < 4; index++)
    {
        uint32_t target = settings + long_texts[index][1];
        port_set32(&port, entry->esp, -0x14u, target);
        copy_text(&port, target, long_texts[index][0]);
    }
    return port_return(&port, settings, entry->edx);
}

#include "port_rtlmusicindexreads.h"

/* Reads a music file's index: a version 10 header, then for each entry two dwords and a name. */

enum
{
    /* The routine's frame under its return slot: the header, an entry and a string, all filled
     * by address. */
    BELOW = 0x40,
    HEADER = 0x28,
    ENTRY = 0x20,
    NAME = 0x18,
    RECORD_BYTES = 8,
    INDEX_VERSION = 10,

    /* The music file: its virtual error method, then the index it reads. */
    FILE_VMT_ERROR = 0x54,
    FILE_VERSION = 0x10,
    FILE_COUNT = 0x14,
    FILE_FIRSTS = 0x18,
    FILE_SECONDS = 0x1c,
    FILE_NAMES = 0x20,

    STRING_INIT = 0x4ca070,
    STRING_FREE = 0x4ca210,
    FILE_OPEN = 0x488c50,
    FILE_READ_EXACT = 0x489230,
    FILE_READ_TEXT = 0x4893c0,
    CALLOC = 0x4ec160
};

/* 0x489230: reads 8 bytes into `to`. The original's ebx is 1 at every call (what 0x488c50
 * returned, then a constant). */
static void read_record(Port *port, uint32_t file, uint32_t to)
{
    port_call(port, FILE_READ_EXACT, file, to, 1, RECORD_BYTES);
}

static uint32_t array(Port *port, uint32_t file)
{
    return port_call(port, CALLOC, port_u32(port, file, FILE_COUNT), 4, 0, 0);
}

/* Original 0x487be0 (eax = the music file, edx = its name, as 0x488c50 takes it): returns 1 once
 * the index is read into three arrays of count dwords (+0x18 the first dwords, +0x1c the second,
 * +0x20 the names), or 0 when the file does not open or the version is not 10; a wrong version
 * also calls the file's error method (+0x54), which gets the vmt, 1 and 8 in edx, ebx and ecx as
 * the original leaves them. The original's try/finally frame is left out. */
uint32_t vertrix_port_music_index_table_read_487be0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t header = frame - HEADER;
    const uint32_t record = frame - ENTRY;
    const uint32_t name = frame - NAME;
    const uint32_t file = entry->eax;
    uint32_t result = 0;

    port_call(&port, STRING_INIT, name, 0, 0, 0);
    if (port_call(&port, FILE_OPEN, file, entry->edx, 0, 0) == 1)
    {
        read_record(&port, file, header);
        const uint32_t version = port_u32(&port, header, 0);
        if (version != INDEX_VERSION)
        {
            const uint32_t vmt = port_u32(&port, file, 0);
            port_call(&port, port_u32(&port, vmt, FILE_VMT_ERROR), file, vmt, 1, RECORD_BYTES);
            port_call(&port, STRING_FREE, name, 0, 0, 0);
            return port_return(&port, 0, 0);
        }
        port_set32(&port, file, FILE_VERSION, version);
        port_set32(&port, file, FILE_COUNT, port_u32(&port, header, 4));
        if (port_u32(&port, file, FILE_COUNT) != 0)
        {
            port_set32(&port, file, FILE_NAMES, array(&port, file));
            port_set32(&port, file, FILE_SECONDS, array(&port, file));
            port_set32(&port, file, FILE_FIRSTS, array(&port, file));
            for (uint32_t index = 0; index < port_u32(&port, file, FILE_COUNT) && !port.env.failed;
                 index++)
            {
                read_record(&port, file, record);
                const uint32_t text = port_call(&port, FILE_READ_TEXT, file, 0, 0, 0);
                port_set32(&port, port_u32(&port, file, FILE_NAMES), index * 4, text);
                port_set32(&port, port_u32(&port, file, FILE_SECONDS), index * 4,
                           port_u32(&port, record, 4));
                port_set32(&port, port_u32(&port, file, FILE_FIRSTS), index * 4,
                           port_u32(&port, record, 0));
            }
        }
        result = 1;
    }
    port_call(&port, STRING_FREE, name, 0, 0, 0);
    return port_return(&port, result, 0);
}

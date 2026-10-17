#include "rtlhandlerrecords.h"

/* Fills the runtime's handler records: 42 records of a handler and two zero words, 0x20 bytes
 * apart from 0x50316c (the last one empty), eleven 12-byte records at 0x5c7574 that the records
 * 27 to 37 copy, and links three nodes into the application (0x4d30f0). */

enum
{
    RECORDS = 0x50316c,
    RECORD_STRIDE = 0x20,
    RECORD_COUNT = 42,
    /* The records copied from the shared ones. */
    SHARED_FIRST = 27,
    SHARED_COUNT = 11,

    /* Two words of 0x80000000 and two of 0, then the shared records. */
    LIMITS = 0x5c7564,
    SHARED = 0x5c7574,
    SHARED_STRIDE = 12,

    APPLICATION_LINK = 0x4d30f0,
    /* The three nodes linked, and the bytes linked with them. */
    LINK_NODES = 0x503698,
    LINK_NODE_STRIDE = 0x18,
    LINK_VALUES = 0x5c75f8,
    LINKS = 3
};

/* Each record's handler; the shared records' are in SHARED_HANDLERS. */
static const uint32_t HANDLERS[RECORD_COUNT] = {
    0x4d6490, 0x4d64a0, 0x4d64b0, 0x4d64c0, 0x4d64d0, 0x4d64e0, 0x4d64f0, 0x4d6500, 0x4d6510,
    0x4d6520, 0x4d6530, 0x4d6540, 0x4d6550, 0x4d6560, 0x4d6570, 0x4d6580, 0x4d6590, 0x4d65a0,
    0x4d65b0, 0x4d65c0, 0x4d65d0, 0x4d65e0, 0x4d65f0, 0x4d6600, 0x4d6610, 0x4d6620, 0x4d6630,
    0x0,      0x0,      0x0,      0x0,      0x0,      0x0,      0x0,      0x0,      0x0,
    0x0,      0x0,      0x4d6690, 0x4d66a0, 0x4d66b0, 0x0};

static const uint32_t SHARED_HANDLERS[SHARED_COUNT] = {0x4d6640, 0x4d6650, 0x4d6640, 0x4d6650,
                                                       0x4d6660, 0x4d6660, 0x4d6660, 0x4d6660,
                                                       0x4d6670, 0x4d6680, 0x4d6680};

static void record(Port *port, uint32_t at, uint32_t handler, uint32_t first, uint32_t second)
{
    port_set32(port, at, 0, handler);
    port_set32(port, at, 4, first);
    port_set32(port, at, 8, second);
}

/* Original 0x4d3140. It builds every record on its stack and copies it out, the shared ones
 * through 0x5c7574; only the stores remain. Its callers read eax and edx: the last link's result,
 * and its own edx (saved). */
uint32_t vertrix_port_rtl_handler_records_init_4d3140(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, LIMITS, 0, 0x80000000u);
    port_set32(&port, LIMITS, 4, 0x80000000u);
    port_set32(&port, LIMITS, 8, 0);
    port_set32(&port, LIMITS, 0xc, 0);
    for (uint32_t k = 0; k < SHARED_COUNT; k++)
    {
        record(&port, SHARED + k * SHARED_STRIDE, SHARED_HANDLERS[k], 0, 0);
    }
    for (uint32_t i = 0; i < RECORD_COUNT; i++)
    {
        const uint32_t at = RECORDS + i * RECORD_STRIDE;
        if (i >= SHARED_FIRST && i < SHARED_FIRST + SHARED_COUNT)
        {
            const uint32_t shared = SHARED + (i - SHARED_FIRST) * SHARED_STRIDE;
            record(&port, at, port_u32(&port, shared, 0), port_u32(&port, shared, 4),
                   port_u32(&port, shared, 8));
        }
        else
        {
            record(&port, at, HANDLERS[i], 0, 0);
        }
    }
    uint32_t result = 0;
    for (uint32_t k = 0; k < LINKS && !port.env.failed; k++)
    {
        result = port_call(&port, APPLICATION_LINK, LINK_VALUES + k,
                           LINK_NODES + k * LINK_NODE_STRIDE, 0, 0);
    }
    return port_return(&port, result, entry->edx);
}

#include "port_rtldisplaychainlists.h"

/* Rebuilds the global image record list (0x532c04) from an object's display chain. */

enum
{
    /* The routine's frame under its return slot: a callee fills the name string by address. */
    BELOW = 0x3c,
    NAME = 0x20,

    LIST = 0x532c04,
    LIST_INDEX = 0x532c00,
    LIST_COUNT = 0x532c18,
    LOCK = 0x558c9c,
    ENTER_CRITICAL_SECTION = 0x4f1b48,
    LEAVE_CRITICAL_SECTION = 0x4f1c40,

    /* A chain member: its flag bits, then three dwords copied to the record. */
    MEMBER_FLAGS = 0,
    MEMBER_FIRST = 4,
    MEMBER_SECOND = 8,
    MEMBER_THIRD = 0xc,

    RECORD_BYTES = 0x28,
    RECORD_KIND = 0,
    RECORD_LEVEL = 4,
    RECORD_FLAG_4 = 8,
    RECORD_FLAG_2 = 0xc,
    RECORD_FLAG_1 = 0x10,
    RECORD_NAME = 0x14,
    RECORD_THIRD = 0x18,
    RECORD_FIRST = 0x1c,
    RECORD_SECOND = 0x20,

    LIST_CLEAR = 0x4b7020,
    CHAIN_COUNT = 0x47f160,
    CHAIN_MEMBER = 0x47f260,
    CHAIN_NAME = 0x47f1b0,
    CHAIN_INDEX = 0x47f370,
    GET_MEMORY = 0x4ca000,
    RECORD_START = 0x4b74c0,
    LIST_ADD = 0x4b6f70,
    STRING_ASSIGN = 0x4ca310,
    STRING_FREE = 0x4ca210
};

/* The original reads the flags afresh for each field. */
static uint32_t member_flags(Port *port, uint32_t member)
{
    return port_u32(port, member, MEMBER_FLAGS);
}

/* Original 0x48c4a0 (eax = the object): clears the list, then under the lock 0x558c9c makes a
 * 0x28-byte record for each member of the object's chain: the member's flag bits (0x180, 0x78,
 * 4, 2, 1) as separate fields, the chain's name for that index and three of the member's dwords.
 * It stores the chain index in 0x532c00 and the member count in 0x532c18. As in the original, the
 * record is the one 0x4b74c0 returns, and a failed allocation is written through anyway. The
 * original's try/finally frame is left out. */
uint32_t vertrix_port_display_chain_list_rebuild_48c4a0(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t name = entry->esp - 4 - NAME;
    const uint32_t object = entry->eax;
    const uint32_t lock = LOCK;

    port_call(&port, LIST_CLEAR, LIST, 0, 0, 0);
    port_call_stack(&port, ENTER_CRITICAL_SECTION, 0, 0, 0, 0, &lock, 1);
    const uint32_t count = port_call(&port, CHAIN_COUNT, object, 0, 0, 0);
    for (uint32_t index = 0; index < count && !port.env.failed; index++)
    {
        const uint32_t member = port_call(&port, CHAIN_MEMBER, object, index, 0, 0);
        if (member == 0)
        {
            continue;
        }
        uint32_t record = port_call(&port, GET_MEMORY, RECORD_BYTES, 0, 0, 0);
        if (record != 0)
        {
            record = port_call(&port, RECORD_START, record, 1, 0, 0);
        }
        port_set32(&port, record, RECORD_KIND, (member_flags(&port, member) & 0x180) >> 7);
        port_set32(&port, record, RECORD_LEVEL, (member_flags(&port, member) & 0x78) >> 3);
        port_set32(&port, record, RECORD_FLAG_4, (member_flags(&port, member) & 4) >> 2);
        port_set32(&port, record, RECORD_FLAG_2, (member_flags(&port, member) & 2) >> 1);
        port_set32(&port, record, RECORD_FLAG_1, member_flags(&port, member) & 1);
        const uint32_t text = port_call(&port, CHAIN_NAME, object, name, index, 0);
        port_call(&port, STRING_ASSIGN, record + RECORD_NAME, text, 0, 0);
        port_call(&port, STRING_FREE, name, 0, 0, 0);
        port_set32(&port, record, RECORD_FIRST, port_u32(&port, member, MEMBER_FIRST));
        port_set32(&port, record, RECORD_SECOND, port_u32(&port, member, MEMBER_SECOND));
        port_set32(&port, record, RECORD_THIRD, port_u32(&port, member, MEMBER_THIRD));
        port_call(&port, LIST_ADD, LIST, record, 0, 0);
    }
    port_set32(&port, LIST_INDEX, 0, port_call(&port, CHAIN_INDEX, object, 0, 0, 0));
    port_set32(&port, LIST_COUNT, 0, count);
    port_call_stack(&port, LEAVE_CRITICAL_SECTION, 0, 0, 0, 0, &lock, 1);
    return port_return(&port, 0, 0);
}

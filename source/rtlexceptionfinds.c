#include "rtlexceptionfinds.h"

enum
{
    /* Under the saved ebx, ecx, edx, esi, edi and ebp: the stream record 0x4e6cf2 resets (+0),
     * whose +8 points at the answer (+0x54), and the query (+0x38) the handlers are given. */
    BELOW = 0x78,
    RECORD = 0x78,
    ANSWER_AT = 8,
    QUERY = 0x38,
    ANSWER = 0x54,

    /* The query: an exception record asking for the exception in hand, its parameter the stream
     * record. */
    QUERY_CODE = 0xe5671234,
    QUERY_PARAMETERS = 2,

    CHAIN_END = 0xffffffff,
    /* A chain of 0 never comes from Windows; the walk ends there rather than read a frame at
     * address 0 (the chain once started at 0 in every routine). */
    NO_CHAIN = 0,
    /* A runtime handler has "WATCOM" 5 bytes in (a jump, then the signature). */
    SIGNATURE = 5,
    /* The exception's flags: bit 1, it is being handled. */
    EXCEPTION_FLAGS = 4,
    HANDLED = 2,

    RESET_RECORD = 0x4e6cf2,
    THUNK_TARGET = 0x4e6cd4,
    /* The thread's data block, and the offset of its exception in hand. */
    THREAD_DATA = 0x507c9c,
    THREAD_EXCEPTION = 0x5c5c54
};

static uint32_t answer(Port *port, uint32_t record)
{
    return port_u32(port, port_u32(port, record, ANSWER_AT), 0);
}

/* Original 0x4e6d16 (eax = where the frame goes, ecx is kept): the exception being handled. Each
 * frame of the exception chain (fs:[0]) whose handler, past its jump thunks (0x4e6cd4), is a
 * runtime one ("WATCOM" at +5) is asked (cdecl: the query, 0, 0, 0) for the exception in hand,
 * which it leaves through the stream record's +8 (reset by 0x4e6cf2); one that answers 0 is the
 * frame stored at eax, and an exception it reports as handled is the result. With none, the last
 * answer, else the thread's exception (its data block, 0x507c9c, at 0x5c5c54's offset). edx is
 * kept. A chain of 0 ends the walk as -1 does (see NO_CHAIN). */
uint32_t vertrix_port_rtl_find_exception_4e6d16(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t record = entry->esp - RECORD;
    const uint32_t query = record + QUERY;
    port_set32(&port, record, ANSWER, 0);
    port_call(&port, RESET_RECORD, record, record + ANSWER, entry->ebx, entry->ecx);
    const uint32_t header[] = {QUERY_CODE, 0, 0, 0, QUERY_PARAMETERS, 0, record};
    for (uint32_t i = 0; i < sizeof header / sizeof header[0]; ++i)
    {
        port_set32(&port, query, 4 * i, header[i]);
    }
    uint32_t frame_found = 0;
    uint32_t found = 0;
    /* What eax and edx hold when the thread's data block is called: the last signature byte
     * compared (edx, or eax for the last), the handler's answer, or the chain. */
    uint32_t eax = port.env.chain;
    uint32_t edx = record + ANSWER;
    uint32_t frame = port.env.chain;
    for (; frame != CHAIN_END && frame != NO_CHAIN && !port.env.failed;
         frame = port_u32(&port, frame, 0))
    {
        const uint32_t handler = port_u32(&port, frame, 4);
        eax = port_call(&port, THUNK_TARGET, handler, edx, frame, entry->ecx);
        const uint32_t code = eax;
        static const char watcom[] = "WATCOM";
        int runtime = 1;
        for (uint32_t i = 0; runtime && watcom[i] != 0; ++i)
        {
            const uint32_t byte = port_u8(&port, code, SIGNATURE + i);
            if (watcom[i + 1] != 0)
            {
                edx = byte;
            }
            else
            {
                eax = byte;
            }
            runtime = byte == (uint8_t)watcom[i];
        }
        if (!runtime)
        {
            continue;
        }
        const uint32_t arguments[] = {query, 0, 0, 0};
        eax = port_call_stack(&port, handler, query, edx, frame, entry->ecx, arguments, 4);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            continue;
        }
        const uint32_t exception = answer(&port, record);
        eax = exception;
        frame_found = frame;
        if (port_u8(&port, exception, EXCEPTION_FLAGS) & HANDLED)
        {
            found = exception;
        }
    }
    if (found == 0)
    {
        found = answer(&port, record);
        if (found == 0)
        {
            found = port_call(&port, port_u32(&port, 0, THREAD_DATA), eax, edx, frame, entry->ecx) +
                    port_u32(&port, 0, THREAD_EXCEPTION);
        }
    }
    port_set32(&port, entry->eax, 0, frame_found);
    return port_return(&port, found, entry->edx);
}

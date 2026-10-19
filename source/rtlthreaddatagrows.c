#include "rtlthreaddatagrows.h"

enum
{
    LOCK = 0x507cc8,              /* a procedure variable */
    UNLOCK = 0x507ccc,            /* a procedure variable */
    CURRENT_THREAD_ID = 0x4f1ba0, /* an import slot */
    TLS_SET_VALUE = 0x4f1ce0,     /* an import slot */
    TLS_INDEX = 0x507c98,
    THREAD_DATA_SIZE = 0x509768,

    /* The threads' list and each entry's fields. */
    THREADS = 0x5c8aa0,
    ENTRY_NEXT = 0,
    ENTRY_ID = 4,
    ENTRY_DATA = 8,
    ENTRY_OWNED = 0xc,

    /* The thread data's fields. */
    DATA_STARTED = 0x52,
    DATA_FLAG = 0x53,
    DATA_SIZE = 0xf0,

    REALLOC = 0x4ec0e0,
    CALLOC = 0x4ec160,
    ERROR_MESSAGE = 0x4e628c,
    /* "Unable to reallocate thread data" and "Unable to allocate thread data". */
    REALLOC_FAILED = 0x513020,
    ALLOC_FAILED = 0x513048
};

/* Original 0x4e843c: the calling thread's data grown to the current size (0x509768). Under the
 * lock (0x507cc8, 0x507ccc) the thread's entry is found by its id in the list (0x5c8aa0). Data the
 * entry owns (+0xc) is reallocated (0x4ec0e0); otherwise new data is allocated (calloc, 0x4ec160),
 * takes the old data's bytes (its size at +0xf0) and becomes owned. Either failure is the fatal
 * error 1 (0x4e628c). The data (+8) is marked started (+0x52), its flag +0x53 cleared and its size
 * set, and made the thread's (TlsSetValue with 0x507c98). Returns the data. */
uint32_t vertrix_port_rtl_thread_data_grow_4e843c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t ecx = entry->ecx;
    uint32_t eax =
        port_call(&port, port_u32(&port, LOCK, 0), entry->eax, entry->edx, entry->ebx, ecx);
    const uint32_t id = port_call(&port, port_u32(&port, CURRENT_THREAD_ID, 0), eax,
                                  vertrix_lift_edx, entry->ebx, ecx);
    uint32_t thread = port_u32(&port, THREADS, 0);
    while (thread != 0 && port_u32(&port, thread, ENTRY_ID) != id && !port.env.failed)
    {
        thread = port_u32(&port, thread, ENTRY_NEXT);
    }
    const uint32_t size = port_u32(&port, THREAD_DATA_SIZE, 0);
    uint32_t data;
    if (port_u32(&port, thread, ENTRY_OWNED) != 0)
    {
        data = port_call(&port, REALLOC, port_u32(&port, thread, ENTRY_DATA), size, thread, ecx);
        if (data == 0)
        {
            port_call(&port, ERROR_MESSAGE, REALLOC_FAILED, 1, thread, ecx);
        }
    }
    else
    {
        data = port_call(&port, CALLOC, 1, size, thread, ecx);
        if (data == 0)
        {
            port_call(&port, ERROR_MESSAGE, ALLOC_FAILED, 1, thread, ecx);
        }
        const uint32_t old = port_u32(&port, thread, ENTRY_DATA);
        port_copy(&port, data, old, port_u32(&port, old, DATA_SIZE));
        ecx = 0;
        port_set32(&port, thread, ENTRY_OWNED, 1);
    }
    const uint32_t edx = vertrix_lift_edx;
    port_set32(&port, thread, ENTRY_DATA, data);
    port_set8(&port, data, DATA_STARTED, 1);
    port_set8(&port, data, DATA_FLAG, 0);
    port_set32(&port, data, DATA_SIZE, size);
    const uint32_t arguments[2] = {port_u32(&port, TLS_INDEX, 0), data};
    eax = port_call_stack(&port, port_u32(&port, TLS_SET_VALUE, 0), size, edx, thread, ecx,
                          arguments, 2);
    port_call(&port, port_u32(&port, UNLOCK, 0), eax, vertrix_lift_edx, thread, ecx);
    return port_return(&port, data, entry->edx);
}

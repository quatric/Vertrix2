#include "rtlthreaddataseconds.h"
#include "runtime.h"

enum
{
    /* The thread data's +0x1038 slot index, whose record 0x4ce7a0 makes. */
    SECOND_SLOT = 0x1038,
    SECOND_MAKER = 0x4ce7a0,

    THREAD_DATA = 0x4ce740
};

/* Original 0x4ce780: the thread data's record in the slot +0x1038 (0x4ce740, then the original
 * jumps to 0x4dbf80 with the maker 0x4ce7a0; its rewrite runs here on the same stack). */
uint32_t vertrix_port_rtl_thread_data_second_4ce780(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t data =
        port_forward(&port, entry, THREAD_DATA, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (port.env.failed)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    LiftEntry jumped = *entry;
    jumped.eax = data + SECOND_SLOT;
    jumped.edx = SECOND_MAKER;
    return vertrix_port_thread_slot(calls, services, globals, &jumped);
}

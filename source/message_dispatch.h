#ifndef VERTRIX_MESSAGE_DISPATCH_H
#define VERTRIX_MESSAGE_DISPATCH_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The stack locals the dispatcher leaves for its callees (the 0x14 bytes below the return address
 * and the two saved registers): the services resolve entry_esp - VERTRIX_DISPATCH_FRAME to their
 * storage. */
enum
{
    VERTRIX_DISPATCH_FRAME = 0x1c,
    VERTRIX_DISPATCH_FRAME_SIZE = 0x14
};

/* Original 0x4d2020 (eax = the object, edx = the message, ebx and ecx the message's registers;
 * `entry_esp` is the stack pointer on entry; one stack argument, the pointer to the handled
 * flag; ret 4): routes a control message. The messages 0x2b..0x2f, 0x39, 0x114, 0x115 and 0x210
 * call 0x4d0c84 (the object, message + 0xbc00, ebx, ecx, the flag pointer). 0x4e calls 0x4cb820
 * (the object, 0, 0xbc4e0000 | the word at ecx + 8, ecx pointing at two local dwords holding the
 * flag pointer and ecx, 0). 0x111 calls 0x4cb820 (the object, 0, 0xbd110000 | the high word of
 * ebx, 0, 0), answering zero when it answers zero and otherwise setting the flag (when the pointer
 * is not null) and answering one. 0x132..0x138 call 0x4d0c84 (the object, 0xbc19, 0, a pointer to
 * locals holding ebx at +4 and the message - 0x132 at +8, the flag pointer) and answer its result
 * only when the flag is then set. Everything else answers zero. *result is the original's eax.
 * Returns zero when memory cannot be accessed. */
int vertrix_message_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t entry_esp, uint32_t object, uint32_t message, uint32_t ebx,
                             uint32_t ecx, uint32_t flag_pointer, uint32_t *result);

#endif

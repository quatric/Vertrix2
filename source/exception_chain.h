#ifndef VERTRIX_EXCEPTION_CHAIN_H
#define VERTRIX_EXCEPTION_CHAIN_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The exception chain head (the dword at fs:[0], linear address zero in the oracle) and the 0x1c
 * stack locals below the three saved registers (entry_esp - 0x28): the services resolve both
 * handles to their storage. */
enum
{
    VERTRIX_EXCEPTION_HEAD = 0,
    VERTRIX_EXCEPTION_HEAD_SIZE = 4,
    VERTRIX_EXCEPTION_FRAME = 0x28,
    VERTRIX_EXCEPTION_FRAME_SIZE = 0x1c
};

/* Original 0x4da6b6 (registers eax, edx, ebx and ecx are the caller's; `entry_esp` is the stack
 * pointer on entry): the exception record at the chain head is re-examined. 0x4e0f8b (the caller's
 * registers) answers a value stored at frame local +0x10; the head pointer goes to +0x14 and the
 * record's dword at +8 to +0x18. 0x4e0a95 (eax the record's +8 dword, edx its +0xc dword, ebx the
 * caller's, ecx the record) answers a descriptor whose dword at +4, less one, is passed as ebx to
 * 0x4e0eaf (eax the local frame + 0x10, edx and ecx the record) and then 0x4e0ec7 (eax the
 * answer, edx frame + 0x10), 0x4e0b7c (eax the frame, edx frame + 0x10) and 0x4e0b9e (eax the
 * frame) work on the locals. The dword at frame + 4 they leave is stored in the record's +0xc and
 * returned. *result is the original's eax. Returns zero when memory cannot be accessed. */
int vertrix_exception_chain_step(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t entry_esp, uint32_t eax, uint32_t edx, uint32_t ebx,
                                 uint32_t ecx, uint32_t *result);

#endif

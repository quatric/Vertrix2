#ifndef MEMORYGETS_H
#define MEMORYGETS_H
#include "port.h"

/* Clean ports of the runtime's memory manager entries (port.h). */

/* Original 0x4ca000 (eax = size): GetMem. 0x4e7c90 allocates (edx the out-of-memory handler at
 * 0x518870, ebx the size); on failure, while the edx it leaves is still that handler, 0x4ce780
 * gives the thread record whose +0x28 is the handler, and a handler that answers non-zero (eax and
 * ebx the size) has the allocation retried with the edx it leaves. Returns the block (0 when it
 * fails); edx is unchanged. */
uint32_t vertrix_port_get_memory(PORT_SIGNATURE);

#endif

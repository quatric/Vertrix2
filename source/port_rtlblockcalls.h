#ifndef PORT_RTLBLOCKCALLS_H
#define PORT_RTLBLOCKCALLS_H

#include "port.h"

/* A runtime block call used by object construction, teardown and the global initialiser: it reaches
 * 0x4ce740, 0x4dc030, the guarded call pair, the handle close and the table register 0x4dde50. */
uint32_t vertrix_port_rtl_block_call_4ccb9f(PORT_SIGNATURE);

#endif

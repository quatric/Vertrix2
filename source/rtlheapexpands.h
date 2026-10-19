#ifndef RTLHEAPEXPANDS_H
#define RTLHEAPEXPANDS_H

#include "port.h"

/* _expand(): grow or shrink a heap block in place, under the heap lock. */
uint32_t vertrix_port_rtl_expand_4ec650(PORT_SIGNATURE);
/* The in-place resize itself. */
uint32_t vertrix_port_rtl_expand_block_4ec68c(PORT_SIGNATURE);

#endif

#ifndef RTLJPEGPROGRESSIVESTARTS_H
#define RTLJPEGPROGRESSIVESTARTS_H

#include "port.h"

/* At 0x4c23f0 the routine checks the scan's Ss/Se/Ah/Al values (+0x190..+0x19c) and raises error
 * 0x10 through [esi] if they form an invalid progression (0x4c241c-0x4c2490, 0x4c261c-0x4c2648). */
uint32_t vertrix_port_jpeg_progressive_huff_start_pass_4c23f0(PORT_SIGNATURE);

#endif

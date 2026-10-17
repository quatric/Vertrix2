#ifndef PORT_RTLMPEGSIDEINFOS_H
#define PORT_RTLMPEGSIDEINFOS_H

#include "port.h"

/* Reads MPEG-1 layer III side information: main_data_begin (9 bits), the private bits (5 for mono),
 * each channel's 4 scfsi bits, then each granule's fields; other layouts take the branch at
 * 0x4071f8. */
uint32_t vertrix_port_mpeg1_side_info_407020(PORT_SIGNATURE);

#endif

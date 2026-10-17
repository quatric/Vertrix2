#ifndef PORT_RTLFIXEDTEXTS_H
#define PORT_RTLFIXEDTEXTS_H

#include "port.h"

/* Formats a 16.16 fixed-point value (edx) as decimal text at eax: a minus sign, the integer part,
 * then [ebx+8] fraction digits (4 when -1), rounding the last digit up with carry. */
uint32_t vertrix_port_rtl_format_fixed_point_4df978(PORT_SIGNATURE);

#endif

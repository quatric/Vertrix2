#ifndef PORT_RTLTZRULES_H
#define PORT_RTLTZRULES_H

#include "port.h"

/* Parses a time zone change rule: Jn (Julian day), Mm.w.d (month, week, day) or a day number, then
 * the time. */
uint32_t vertrix_port_rtl_tz_rule_parse_4e97b4(PORT_SIGNATURE);

#endif

#ifndef PORT_RTLCODEPAGES_H
#define PORT_RTLCODEPAGES_H

#include "port.h"

/* Selects the multibyte code page: -1 for GetACP, -2 for GetOEMCP, -3 for the default, otherwise
 * the number given, and fills the ctype table. */
uint32_t vertrix_port_rtl_set_code_page_4e6f60(PORT_SIGNATURE);

#endif

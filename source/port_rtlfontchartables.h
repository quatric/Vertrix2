#ifndef PORT_RTLFONTCHARTABLES_H
#define PORT_RTLFONTCHARTABLES_H

#include "port.h"

/* 0x43fc50 builds about twenty character-to-glyph word tables (0x541988 through 0x543e60). */
uint32_t vertrix_port_font_char_tables_build_43fc50(PORT_SIGNATURE);

#endif

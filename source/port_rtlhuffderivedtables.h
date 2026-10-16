#ifndef PORT_RTLHUFFDERIVEDTABLES_H
#define PORT_RTLHUFFDERIVEDTABLES_H

#include "port.h"

/* This is most likely the libjpeg 6b Huffman decoder setup jpeg_make_d_derived_tbl, built into
 * Vertrix2.exe for JPEG loading. */
uint32_t vertrix_port_jpeg_make_huff_derived_table_4bbc00(PORT_SIGNATURE);

#endif

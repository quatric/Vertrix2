#ifndef RTLMUSICINDEXREADS_H
#define RTLMUSICINDEXREADS_H

#include "port.h"

/* Reads a music file's index of names and dword pairs (called from 0x45f482). */
uint32_t vertrix_port_music_index_table_read_487be0(PORT_SIGNATURE);

#endif

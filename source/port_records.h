#ifndef VERTRIX_PORT_RECORDS_H
#define VERTRIX_PORT_RECORDS_H
#include "port.h"

/* Clean ports of array list release, file text read, text list step, menu item, object text
 * value, decoder start, coefficient buffer, message format and pool block routines
 * (port_records.c). */
uint32_t vertrix_port_array_list_release_4874f0(PORT_SIGNATURE);
uint32_t vertrix_port_file_text_read_4893c0(PORT_SIGNATURE);
uint32_t vertrix_port_text_list_back_4b3880(PORT_SIGNATURE);
uint32_t vertrix_port_text_list_forward_4b3940(PORT_SIGNATURE);
uint32_t vertrix_port_menu_item_build_4b5580(PORT_SIGNATURE);
uint32_t vertrix_port_object_text_value_4b6930(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_start_4b9710(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_coefficients_4c3540(PORT_SIGNATURE);
uint32_t vertrix_port_decoder_message_format_4c3ed0(PORT_SIGNATURE);
uint32_t vertrix_port_pool_small_alloc_4c4ea0(PORT_SIGNATURE);
#endif

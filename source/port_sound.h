#ifndef VERTRIX_PORT_SOUND_H
#define VERTRIX_PORT_SOUND_H
#include "port.h"

/* Clean ports of sound, key queue, display and slot helpers (port_sound.c). */
uint32_t vertrix_port_slot_create_call_472d00(PORT_SIGNATURE);
uint32_t vertrix_port_queue_push_475b80(PORT_SIGNATURE);
uint32_t vertrix_port_queue_next_475c80(PORT_SIGNATURE);
uint32_t vertrix_port_slot_search_call_476530(PORT_SIGNATURE);
uint32_t vertrix_port_sound_key_is_control_476650(PORT_SIGNATURE);
uint32_t vertrix_port_resource_entry_256_476810(PORT_SIGNATURE);
uint32_t vertrix_port_sound_release_primary_476cc0(PORT_SIGNATURE);
uint32_t vertrix_port_sound_release_looped_477d10(PORT_SIGNATURE);
uint32_t vertrix_port_counter_take_477190(PORT_SIGNATURE);
uint32_t vertrix_port_text_append_call_4777c0(PORT_SIGNATURE);
uint32_t vertrix_port_offset_pair_call_478bf0(PORT_SIGNATURE);
uint32_t vertrix_port_offset_pair_clamp_call_478c40(PORT_SIGNATURE);
uint32_t vertrix_port_display_restart_47e780(PORT_SIGNATURE);
uint32_t vertrix_port_display_chain_find_47f320(PORT_SIGNATURE);
uint32_t vertrix_port_sound_release_stream_477320(PORT_SIGNATURE);
#endif

#ifndef BOBS_H
#define BOBS_H
#include "port.h"

/* Clean ports of actor wobble, grow, show, menu wait, move span, accelerate, cursor ease
 * and attack enter routines (bobs.c). */
uint32_t vertrix_port_actor_wobble_44a610(PORT_SIGNATURE);
uint32_t vertrix_port_actor_grow_start_44bba0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_show_sounds_44beb0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_menu_wait_44c1a0(PORT_SIGNATURE);
uint32_t vertrix_port_actor_move_span_44e2d0(PORT_SIGNATURE);
uint32_t vertrix_port_block_accelerate_update_44e6e0(PORT_SIGNATURE);
uint32_t vertrix_port_cursor_ease_450d40(PORT_SIGNATURE);
uint32_t vertrix_port_object_enter_attack_4522c0(PORT_SIGNATURE);
#endif

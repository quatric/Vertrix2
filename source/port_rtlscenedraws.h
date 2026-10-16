#ifndef PORT_RTLSCENEDRAWS_H
#define PORT_RTLSCENEDRAWS_H

#include "port.h"

/* At 0x42f910 the routine draws the actors in the scene object, passing edx through to each draw
 * call. */
uint32_t vertrix_port_scene_draw_actors_layered_42f910(PORT_SIGNATURE);

#endif

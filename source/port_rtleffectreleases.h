#ifndef PORT_RTLEFFECTRELEASES_H
#define PORT_RTLEFFECTRELEASES_H

#include "port.h"

/* Releases an object's effect slots: 500 at +0x15c and 8 at +0x92c (0x4b22c0). */
uint32_t vertrix_port_effects_release_all_43d800(PORT_SIGNATURE);

#endif

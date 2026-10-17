#ifndef RTLOWNERNOTES_H
#define RTLOWNERNOTES_H

#include "port.h"

/* Lets a window's owner handle a notification first (eax = the window). */
uint32_t vertrix_port_rtl_object_notify_owner_4d7140(PORT_SIGNATURE);

#endif

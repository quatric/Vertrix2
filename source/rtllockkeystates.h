#ifndef RTLLOCKKEYSTATES_H
#define RTLLOCKKEYSTATES_H

#include "port.h"

/* MFC's CFrameWnd::OnUpdateKeyIndicator: enables the Caps Lock, Num Lock, Scroll Lock and Kana
 * status bar indicators by their key's state; other commands pass the update on. */
uint32_t vertrix_port_lock_key_state_query_4d5bf8(PORT_SIGNATURE);

#endif

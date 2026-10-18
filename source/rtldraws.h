#ifndef RTLDRAWS_H
#define RTLDRAWS_H

#include "port.h"

/* Depth-ordered drawing, file dialogs, JPEG refinement and pools, level and settings screens,
 * object texts and window procedures */
uint32_t vertrix_port_file_dialog_open_48c860(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_decode_dc_refine_4c2c50(PORT_SIGNATURE);
uint32_t vertrix_port_level_open_41a320(PORT_SIGNATURE);
uint32_t vertrix_port_settings_screen_open_421ac0(PORT_SIGNATURE);
uint32_t vertrix_port_object_set_text_47faf0(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_free_pool_4c58e0(PORT_SIGNATURE);
uint32_t vertrix_port_window_procedure_restore_4cfd20(PORT_SIGNATURE);

#endif

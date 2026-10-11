#ifndef VERTRIX_PORT_FRAME_RESOURCE_H
#define VERTRIX_PORT_FRAME_RESOURCE_H
#include "port.h"

/* Clean ports of the frame resource lookups (port.h). A resource record keeps its frames' table
 * at +0x00, for a composite record the child records at +0x0c and the index within each child at
 * +0x10, and its kind at +0x14 (1 for a composite). */

/* Original 0x4877e0 (eax = record): the kind, the dword at +0x14. edx is unchanged. */
uint32_t vertrix_port_resource_kind(PORT_SIGNATURE);

/* Original 0x4877f0 (eax = record, edx = frame index): while 0x4877e0 says the record is a
 * composite (1), the index and record become the child's (+0x10 and +0x0c tables at the old
 * index). Returns the frame table's dword at the index, with edx the table. 0x4877e0 is called
 * with ebx the index, ecx the record and edx the entry edx, later the composite's child table. */
uint32_t vertrix_port_frame_resource_get(PORT_SIGNATURE);

/* Original 0x4ac8a0 (eax = actor): when the actor has a resource (+0xb0), its frame at the index
 * +0xb8 (0x4877f0, ebx passed on and ecx the actor) is stored at +0xb4 and returned. Without one
 * returns the actor. edx is unchanged. */
uint32_t vertrix_port_actor_lookup_image(PORT_SIGNATURE);

#endif

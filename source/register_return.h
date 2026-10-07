#ifndef VERTRIX_REGISTER_RETURN_H
#define VERTRIX_REGISTER_RETURN_H
#include <stdint.h>

/* Original variants 0x404580, 0x425f40, 0x4523b0, 0x4713c0,
 * 0x471ee0, 0x477930, 0x47f8f0, 0x4b3360, 0x4b9ce0, 0x4bb260,
 * 0x4c5c20, 0x4c6a80, 0x4c93c0, 0x4e3697, 0x4ec8c0: return incoming EAX unchanged,
 * without memory writes or other register/flag changes (apart from return ESP/EIP).
 * tools/verify_register_return.py verifies each complete entrypoint. */
uint32_t vertrix_return_unchanged(uint32_t value);
#endif

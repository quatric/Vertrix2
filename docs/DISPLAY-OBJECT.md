# Display object helpers

`display_object.c` recovers small routines of the display device wrapper
(`0x47e000..0x480000`). Interface handles are identity tokens; chain nodes are resolved
through `VertrixObjectStorage`, interface calls through supplied callbacks.

- `0x47f160`: number of nodes in the chain headed by dword `+0xc` (link dword `+0x60`).
- `0x47f320` / `0x47f370`: first node whose 16 bytes at `+8` equal the 16 bytes at `+0xa4`
  of the object; node handle (0 if none) and index (`0xffffffff` if none).
- `0x47f410`: 1 when dwords `+0` and `+0x10` are both nonzero (the other path tail-jumps to
  `0x47ed00`, which returns 0).
- `0x47ea20`: release (slot 2) and clear the interfaces at `+4` then `+8`.
- `0x47fe20`, `0x47fe50`, `0x47fe80`: when interface `+0x1bc` and value `+0x1c0` are
  nonzero, call slot 8 with the arguments (value, 1 / 2 / 4, 0).

Not ported: the COM setup routines (`0x47e680`, `0x47e7d0`, `0x47e890`, `0x47eeb0`,
`0x47f0f0`, `0x47f430`, `0x47f590`, `0x47fa40`, ...), which chain imported API calls and
vtable calls with stack-built structures.

Verification (`tools/verify_display_object.py`): 4,096 complete original executions per
routine over node chains of 0 to 8 nodes; results, object bytes and every interface call
compare. Evidence: `display-object-verification.json`.

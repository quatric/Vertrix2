# Actor clipping gate

`actor_gate.c` recovers original `0x4ae3e0` (0x4ae3e0..0x4af212), the routine
`0x4af8c0` calls with actor dword `0x144` as `mode`. It captures actor, image and
surface fields into the render globals `0x5bb680..0x5bc01f`, clips the image
rectangle and prepares the source/destination cursors that `0x4af560` draws from.
The native function returns the original `eax` (1 = drawable, 0 = rejected).

Stages, in original order:

1. **Capture** (`4ae3e0..4ae5db`): clears the visible rectangle (`4ae110`) when
   dword `0x13c` is zero, rejects a missing image (`0xb4`), surface (`0x5bc010`)
   and surface kind 3, and copies positions, image size and flag bytes. Mode 0
   also reads the map object at `[0x544070]`.
2. **Index and shift** (`4ae5db..4ae6b5`): clamps the map cell, chooses the image
   index (0x10 means unscaled) and the shift fields at `0x5bc000..0x5bc004`.
3. **Rectangle** (`4aed56`, `4ae6c2..4ae80a`): scales the size through the
   16-entry table at `0x5c1b00` (signed divides by the original width/height;
   zero divisors fault in the original) or takes it unscaled, then applies the
   clip rectangle for kinds 0/1 (surface), 3 (actor words `0xa8..0xae`); kind 2
   skips clipping, other kinds reuse the stale limits.
4. **Clip** (`4ae80a..4ae967`): adjusts position/size, accumulates skipped
   rows/columns into `0x5bb790` and records `0x5bc014`.
5. **Indexed skip** (`4ae967..4aeab0`): for scaled images sums skipped table
   bytes from `0x5c1c00 + index * 0x400` into the image offset.
6. **Mask columns/rows** (`4aead0..4af0e8`): for mode 0 with a mask object it
   marks columns that hit set mask bits in the 16-bit array at `0x5bb7ec`.
7. **Publish** (`4af0ee..4af212`): sets the cursors/pitch globals, the surface
   pixel address (`0x478eb0`, recovered inline) for 1/2/4-byte depths and the
   actor rectangle when dword `0x13c` is zero.

`si`/`di` are reused as loop counters by the original and stored back to
`0x5bb68e`/`0x5bc016`; the native code keeps that behavior.

Memory outside the globals (objects, image data, tables) is read through the
supplied `VertrixMemoryRead` callback; original addresses are identity tokens.
Division by zero, unreadable memory, out-of-range global writes and short
storage return zero and preserve globals and actor.

`tools/verify_actor_gate.py` executes the complete original 20,000 times with the
real `4ae110`, `478eb0` and fill `4eb5c0` and compares the return value, whole
globals and whole actor storage; 1,917 original faults are rejected natively.
Evidence: `actor-gate-verification.json`.

# Base actor draw slot and chain walk

`actor_draw_slot.c` recovers original `0x4ae010` (base vtable slot 3) and
`0x4ade60`, which base slot 2 `0x4ae140` forwards to.

- `4ae010` draws only when actor dword `0x124` is 1, the `4adfb0` refresh value
  is 1 and equals dword `0x138`, and the resource dwords `0x12c`/`0x130` are
  nonzero. The draw `47ce10` receives surface and selector (eax/edx), the
  signed words at `0x128` (x) and `0x12a` (y), and both resource dwords. When
  dword `0x140` is 1 the same rectangle is drawn again for the handle and
  selector at offsets `0x274`/`0x278` of the object pointed to by `0x544070`.
- `4ade60` walks nodes through the link at `node+0x108`, calling `4ac8a0(node)`
  then `4af8c0(node, arg)` per node; a null first node does nothing. `4ae140`
  is a tail forwarder.

`47ce10`, `4ac8a0` and `4af8c0` are supplied boundaries. Native chain walks
reject loops longer than 4096 nodes (the original never terminates on a cycle).

`tools/verify_actor_draw_slot.py` runs the complete originals in 8,192 draw
and 4,096 chain cases against whole actor storage and `0x5bb710` state.
Evidence: `actor-draw-slot-verification.json`.

# Player piece create/release

`player_piece.c` recovers original `0x432160`, `0x4321b0` and `0x432110`.

- `0x432160` creates the active piece. If player dword `0xb78` is nonzero it
  returns unchanged. Otherwise it allocates `0x18c` bytes, runs parent
  constructor `0x42aab0`, stores the handle at `0xb78`, then runs `0x42acf0`.
  Side is the sign-extended byte in `dl`, `ecx` is the frame array and `ebx` the
  level; difficulty comes from `0x532bbc`.
- `0x4321b0` releases it. It reads frame `0xb8` of the last active child
  (count `0x188`, handle `0x158 + count * 4`, the `0x42b070` read), stores it at
  `0xb7c`, calls virtual destructor slot 0 with flag 2 and clears `0xb78`.
- `0x432110` releases the preview actor at `0xb70`: dword `0x168` is copied to
  `0xb74`, then the actor is destroyed and `0xb70` cleared.

Heap allocation and the virtual destructor are supplied boundaries
(`VertrixPlayerActorDestroy`). The native create stages the parent and rejects
parent/children overlap and null identities before writing anything.

`tools/verify_player_piece.py` runs all three complete originals in 2,048 cases
with the allocator and destructor hooked, asserts the destructor argument
(identity and flag 2), and compares the whole player, parent and child storage.
Evidence: `player-piece-verification.json`.

`0x425e20` initializes a player piece object (base fields, class token
`0x5144d4`, level dword `+0x178 = 0`); the caller allocates `0x218` bytes and
stores the result at player `+0x450`. Covered by `verify_constructors.py`
(4,096 whole-object cases, `constructors-verification.json`).

Still separate: the destructor bodies (class `0x514774`), preview construction
`0x4320d0`/`0x42b6b0`, and the player/game-loop integration.

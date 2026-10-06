# UI actor storage

`ui_actor_storage.c` recovers UI actor construction helpers:

- `vertrix_ui_actor_storage_construct`: base constructor `0x4abd70`, then
  position and alternating setup (`0x46e0c8`/`0x46e257`); side 0 is left, side
  1 is right; pairs 0..11.
- `0x4710d0` (`vertrix_ui_actor_place`): initialize the actor (via `0x4adf20`)
  with the sign-extended x/y words, z = 0, bank `0x5449fc`, the frame dword
  and zero image/handler, then clear byte `+0x8e` and set byte `+0x8f`.

Allocation and scene-list registration stay external; invalid parameters
preserve all storage. `tools/verify_ui_actor_place.py` runs `0x4710d0` 4,096
times over random actors, coordinates including negative words, and frames,
with whole-object compares plus a short-storage preservation check
(`ui-actor-place-verification.json`).

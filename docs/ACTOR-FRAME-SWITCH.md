# Actor frame switch

`actor_frame_switch.c` recovers two base-actor routines:

- `0x449360`: when word `+0x48` is nonzero, set `+0x4a = 0` and `+0x4c = 4`,
  move `+0x48` toward zero by `cycles * 4` (the recovered `0x4ad530`
  arithmetic in `word_transition.c`) and arm the refresh (`0x4adfe0`, recovered
  in `actor_refresh.c`).
- `0x449390`: unless the frame index at `+0xb8` already equals the argument,
  attach resource `0x544a18` (`0x4ac8d0`), select the frame (`0x4ac710`), bind
  (`0x4ac8a0`) and arm the refresh.

The three actor calls of the second routine are supplied boundaries.
`tools/verify_actor_frame_switch.py` runs each complete original 8,192 times and
compares the whole actor, the shared refresh state at `0x5bb710` and the ordered
supplied calls (`actor-frame-switch-verification.json`). `0x449460` is not
ported: it calls `0x4ac8f0` with an `edx` left over from `0x4ac8a0`.

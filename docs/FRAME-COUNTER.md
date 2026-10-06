# Frame counter

`frame_counter.c`: `0x41d670` frames-per-second counter: every 1000 ms or more the rate becomes
`frames*1000/elapsed`, the frame count is cleared and the window restarts.
Not ported: `0x41d640` (resets via the unrecovered `0x4b7cd0`, which also produces edx).

Verification: `tools/verify_frame_counter.py`, 4,096 executions. Evidence:
`frame-counter-verification.json`.

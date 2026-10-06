# Frame-delta limiter (0x4b7d10)

`vertrix_time_frame_step` in `source/timing.c` reproduces the frame timer:
sample the millisecond clock into the now global, take the unsigned
difference against the previous global when ahead (a still or backwards
clock yields zero — the compare-then-recompute shape is not a saturating
delta as first modeled), store the sample back and the value capped at
`0xffff` into the third global. Returns the capped difference.

Verification (`tools/verify_time_frame_step.py`, evidence
`docs/time-frame-step-verification.json`): 1,024 complete original
executions pass with the `timeGetTime` import redirected to a scripted
stub (normal, wrap-around and saturation cases); the returned delta and
all three globals compare.

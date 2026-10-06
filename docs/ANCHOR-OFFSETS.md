# Anchor offsets

`anchor_offsets.c`: `0x414a90` (19 groups of up to 60 items) and `0x414b10` (5 groups of up to
5 items) store item offsets (anchor minus item position) when both components are nonnegative.

Verification: `tools/verify_anchor_offsets.py`, 4,096 executions each, both arrays compare whole.
Evidence: `anchor-offsets-verification.json`.

# Post-lock twin handler (0x451920)

`vertrix_object_post_lock_twin` in `source/object_events.c` reproduces the
twin post-lock dispatcher. A normalized instruction diff against `0x4517c0`
(with absolute jump targets erased) shows the two routines are identical
except for the has-match tail: the twin has no second effect at chain
count 6, and its flag tail plays the alt effect when flag_a is clear and
the flag effect otherwise — flag_b is never consulted.

The native shares the `post_lock_run` body with `vertrix_object_post_lock`
through a `twin` selector (the codebase's usual one-routine-per-address
rule is kept at the public boundary: two named natives, one static core).
The twin verifier randomizes flag_b on every bucket to prove its
irrelevance, and the chain-hits-6 bucket proves the absent second effect.

Verification (`tools/verify_object_post_lock_twin.py`, evidence
`docs/object-post-lock-twin-verification.json`): 1,024 complete original
executions pass with the same return/call/state/RNG coverage as the
`0x4517c0` proof.

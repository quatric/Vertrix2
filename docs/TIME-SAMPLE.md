# Clock sampler (0x4b7cd0)

`vertrix_time_sample` in `source/timing.c` reproduces the millisecond
clock reader: sample the platform clock (originally WinMM `timeGetTime`,
called through the import table) into both outputs (original globals
`0x5bd838` and `0x5bd844) and return the sample. The clock is a
caller-supplied `VertrixClock`, matching the random module's convention.

Verification (`tools/verify_time_sample.py`, evidence
`docs/time-sample-verification.json`): 1,024 complete original executions
pass with the import slot redirected to a scripted stub; the returned tick
and both globals compare.

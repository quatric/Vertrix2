# Border animation actor updates

`ui_border_update.c` adapts the recovered five-phase `linked_burst` behavior
to the original serialized actor fields. It preserves unrelated bytes and
resolves the first matching player identity through the existing list lookup.
The shared random state supplies the original burst step selection; actor
updates consume it in scene-list order.

The random-aware actor and scene entry points support callbacks `0x450130`,
`0x4501a0`, `0x450200`, `0x450270` and `0x450300`. The mapped render entry point
accepts that same random state before the existing sorted draw pass. Existing
entry points retain their signatures and reject border callbacks when no
random state is supplied. Failed storage/handler validation does not consume
random samples. Scene failure retains preceding successful updates as before.

The updated burst verifier compares all actor bytes and the shared random
cursor against original callback execution in 10,240 cases, with 20,480
short-storage/null-random preservation checks. The updated scene verifier
executes original `0x4b6200` in 512 mixed scenes with 6,127 actor updates across
twenty-two supported callbacks and idle actors. Actor storage, refresh words,
list order and the random cursor match. These fixtures do not reach RNG
refill; that behavior has separate recovery evidence.

Complete player construction and final binding of the border and companion
actors remain separate. Actual border update/draw frames and Wii hardware
execution still need integration checks. This does not establish a playable
game application.

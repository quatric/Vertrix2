# Active-piece child callbacks

`piece_child_update.c` recovers complete callbacks `0x44c2a0`, `0x44c2b0`,
`0x44c310` and `0x44c370`. The first binds the current descriptor. The next
two advance the primary timer and transition signed DWORD value `0x58` toward
60 or zero at step four, switching callbacks on arrival. The final callback
transitions toward zero at step eight and switches to the binding-only phase.
Every callback binds the current descriptor after its state work; null actor
resources leave the descriptor untouched.

The caller supplies the explicitly resolved original resource token and live
frame graph. The existing recovered timer, signed transition and resource
lookup helpers handle wrapped arithmetic and binding. Native validation stages
actor changes so unsupported callbacks and invalid binding preserve storage.
Base virtual refresh, interaction targets and child-chain handling remain
separate from these callback bodies.

The verifier executes all four complete original callbacks without hooks in
16,384 cases, including real timer operations, `0x4ad6e0` transitions and
`0x4877f0` lookup against direct resource fixtures. All extended actor bytes
compare; the current callback-change count is recorded in the verification JSON.
Null resources, zero periods, timer wrap
and arbitrary signed state are covered. Short storage and exhausted lookup
budget preserve native output. Linked resource graphs have separate lookup
evidence; actual piece resource publication and parent/game-loop integration
still require work.

`vertrix_piece_child_frame_update` now implements the complete recovered
`0x4ae150` base virtual wrapper for these callbacks. It validates class
`0x517af4`, excludes interaction targets and child-update chains, and clears
refresh `0x120` when requested before running the callback. The verifier
additionally compares 16,384 complete original virtual updates with conditional
refresh and checks 16,384 unsupported-class failures for preservation. The
parent resource-aware updater now calls this entry point in its child pass;
the integrated parent verification is documented in `PIECE-ACTOR-UPDATE.md`.

# Active-piece actor layout

`piece_actor_layout.c` recovers complete original `0x42af30`. It visits seven
parent handle slots at `0x15c..0x174`, skipping nulls. Each reached actor receives
the parent's current X at `0x0e` and current Y at `0x16` plus slot index times
the supplied original `0x4f90ac` row height. Word arithmetic wraps explicitly.
Coordinates are read as each actor is reached, preserving repeated-handle
ordering. The resolver keeps all storage live. Resolution failure retains
previous writes, while invalid parent storage fails before any writes.

The verifier executes the complete original routine without hooks in 4,096
cases, including null/repeated handles, arbitrary signed-position words and
row heights0,24,65535 and randomized values. Entire parent and child storage
compare across all reached actor position updates; the current count is in
`piece-actor-layout-verification.json`. There are 4,096 short-parent
preservation checks. The caller still needs the active-piece virtual update,
callback scheduling and complete player/game-loop integration; this helper
alone does not establish gameplay.

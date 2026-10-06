# Active-piece parent constructor

`vertrix_piece_actor_parent_construct` recovers complete original `0x42aab0`.
After the base actor constructor, it assigns class token `0x514774`, clears
the seven owned child handles at `0x15c..0x174`, and clears fields
`0x178..0x188`: movement state, stopped flag, mode, mode flag and active count.
Storage must hold at least `0x18c` bytes. All bytes outside the original writes
remain unchanged, including extra derived storage.

The extended piece verifier executes complete original constructor code without
hooks in 4,096 cases, comparing all 416 bytes with randomized input storage
and arbitrary original EDX values. Short storage is rejected without mutation
in another 4,096 cases. Existing layout, parent update with real child callback
phases, and rotation comparisons remain included.

Child actor allocation/setup in `0x42acf0`, the original resource graph,
surrounding player ownership and game-loop/Wii integration remain unfinished.
This constructor is a recovered component, not a playable game application.

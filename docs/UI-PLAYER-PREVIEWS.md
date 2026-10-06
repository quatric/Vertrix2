# Player preview construction and attachment

`vertrix_ui_player_preview_parent_construct` recovers complete original
`0x42b150`: call the base constructor, assign class token `0x514814`, and
clear all six owned preview handles. It preserves untouched extended storage
and rejects buffers shorter than `0x174`. The verifier compares all 416 actor
bytes with original constructor execution in 2,048 cases, including arbitrary
original EDX values, and checks 2,048 short-storage failures. The complete
preview construction fixtures now run this parent constructor first, then
supply the caller's player identity before constructing and attaching actors.

`ui_player_previews.c` recovers complete original `0x42b370` preview setup:
three companion/border pairs, linked identity from player field zero, and
parent handle arrays at `0x15c..0x164` and `0x168..0x170`. Actor storage is
interleaved companion/border in original allocation order. Handle identities
remain explicit serialized tokens that the caller's resolver maps to storage.

The caller owns six base actor slots and the live interface/generated-border
banks. Construction stages all six actors before publishing any of them or
writing the parent arrays. A failure in the final pair therefore preserves
earlier actor slots and the entire parent. Zero/duplicate handles, insufficient
storage and overlapping parent/actor storage are rejected. The helper preserves
all parent bytes outside the six handle fields and all actor bytes not touched
by the original constructors and setup.

`verify_ui_preview_pair.py` now executes complete original `0x42b370` in 512
cases, supplying only the heap allocation boundary. Original constructors,
position lookup, descriptor lookup, callback assignment, loop and parent
attachment execute normally. All 3,072 actors and all parent bytes compare,
with descriptor pointers normalized to native bank-local indices. Final-pair
binding failure and duplicate-handle rejection preserve outputs in 1,024 cases.
The earlier 2,048 pair-level comparisons remain included.

The recovered routine does not register actors with a scene. The caller still
needs native ownership/lifetime management, surrounding player construction
and the separate registration path. Resource fixtures are direct banks; VF
loading has separate evidence. Actual constructed preview update/draw frames
and full playable Wii execution remain unfinished.

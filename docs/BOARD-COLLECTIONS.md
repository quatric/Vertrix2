# Board collection wrappers

`board_collections.c` recovers the regular family of board methods at
`0x42ebc0..0x42ee00` and the three list helpers behind them, over the scene
collections (SCENE-RECOVERY.md) named by board offset:

| Original | Native | Behavior |
| --- | --- | --- |
| `0x4b22c0` via `0x42ebc0` (+0x220), `0x42ebe0` (+0x87c), `0x42ec00` (+0x988), `0x42ec20` (+0x9e8), `0x42ec40` (+0xa2c), `0x42ec60` (+0xbdc) | `vertrix_board_clear_collection` | destroy (flag 2) and clear every set entry in order |
| `0x4b2300` via `0x42eca0`, `0x42ecc0`, `0x42ece0`, `0x42ed00`, `0x42ed20`, `0x42ec80` | `vertrix_board_collection_all_handler` | 1 when every set entry's handler token (+0x154) equals the argument; stops at the first mismatch |
| `0x4b2340` via `0x42eda0` (+0x220) | `vertrix_board_collection_set_handler` | set the handler token of every set entry (`0x4ac8f0`) |
| `0x42ed40`, `0x42edf0` (piece +0x15c), `0x42ed70` (piece +0x170) | `vertrix_board_piece_all_handler` | the same check over the active piece's three child handles; 1 without a piece |
| `0x42edc0` | `vertrix_board_piece_set_handler` | set the handler token of the piece's list 0 children |
| `0x4387b0` | `vertrix_board_prepare_slots` | for every set slot of the grid at +0x220: objects whose byte +0x44 is not 0x10 get handler `0x44eaf0`; objects with +0x44 = 0x10 and kind byte +0x15c = 5 get +0x93 = 0, +0x4e = 0x32, +0x95 = 1 |
| `0x438c60` | `vertrix_board_apply_pattern` | for every set slot whose entry in a 65-byte pattern (row `dl` of the table at `0x4f7e40`, row-major) is 1, word +0x48 = 0x64 |
| `0x4398c0` | `vertrix_board_clear_marked_extra` | destroy and clear the +0xbdc entries whose marker is 2 |
| `0x439190` | `vertrix_board_destroy_marked` | for markers equal to 2, destroy and clear the +0x220 entry and then the +0xbdc entry |
| `0x438b90` | `vertrix_board_assign_effect` | row-order handler assignment by mode: 0 `0x44f1e0` and word +0x4c = 10; 1 `0x44f320` and +0x4c = 10; 2 `0x44f430` and dword +0x88 = 10; 3 `0x44f560`; 4 `0x44f690`; others nothing |

Handler tokens are original addresses compared as values. Objects are resolved
through `VertrixObjectStorage`; the destructor is `VertrixBoardDestroy`.
`tools/verify_board_collections.py` runs each complete original wrapper (with
the real list helpers) over random boards 2,048 times and compares the scene,
every object and the destruction order. Evidence:
`board-collections-verification.json`.

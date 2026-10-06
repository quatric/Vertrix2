# Active-piece child initialization

`vertrix_piece_child_construct` recovers the original base constructor followed
by child setup `0x42ae11..0x42aea5`. It attaches resource token `0x544bd8`,
selects the supplied frame, sets primary timer period24 and animation period12,
and copies the caller's four clipping words with mode3. Positions and other
defined fields retain original constructor values. The last child receives
callback `0x44c2b0`; earlier children receive `0x44c2a0`.

No image is bound by this setup. Descriptor binding occurs in the recovered
child update callbacks. Allocation and parent handle publication remain
separate. Storage must hold a base actor; clipping input is copied before
mutating the destination, and untouched extended bytes remain unchanged.

The child verifier executes the original constructor and complete setup
fragment without hooks in 2,048 cases. Entire 384-byte actors compare across
arbitrary frame DWORDs, signed clipping bounds and both last-child branches.
There are 4,096 short-storage/null-bounds preservation checks. The existing
callback and virtual frame comparisons remain included. Complete parent
`0x42acf0` construction, resource publication and full gameplay still require
integration.

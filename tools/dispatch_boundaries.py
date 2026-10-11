"""Routines the platform implements itself: they stay call boundaries even when a lifted copy
exists (verified or not)."""

# 0x48ae00: the host JPEG boundary currently returns no bitmap; it is not a verified decoder.
# 0x475090: the palette table builder, done by the recovered palette_tables.c (too slow lifted).
# 0x4d88a0: the TList insert, served by host_list_insert in lift_host.c (its lift verifies since
# the oracle forwards global reads, but the host keeps its own list growth).
# 0x4ca050 (FreeMem), 0x4ca040 (its jump) and 0x4ea190 (the free 0x4ca050 jumps to, which 95 sites
# also call directly): the host allocator hands out every block (0x4e7c90,
# 0x4ca000), so only the host can release them; the lifted RTL free knows only its own arenas, and
# with it the image buffers of every screen stayed allocated until the heap ran out (the second
# round's end in a long session).
NATIVE_UNVERIFIED_BOUNDARIES = frozenset({0x48ae00, 0x475090, 0x48ac50, 0x48ad00, 0x4e0f8b, 0x4cd8b0,
                                          0x4d88a0, 0x4ca040, 0x4ca050, 0x4ea190})

# Hand-recovered routines the dispatcher runs instead of a lifted copy: address -> (entry point in
# source/native_dispatch.c, stack bytes, stack arguments).
NATIVE_PORTS = {0x41c7b0: ('vertrix_native_title_frame', 0, 0),
                0x41b820: ('vertrix_native_game_frame', 0, 0),
                0x410270: ('vertrix_native_s3m_pattern', 0, 0),
                0x4327e0: ('vertrix_native_kind_snapshot', 0, 0),
                0x4046e0: ('vertrix_native_bit_read', 0, 0),
                0x4346b0: ('vertrix_native_line_pass', 0, 0)}

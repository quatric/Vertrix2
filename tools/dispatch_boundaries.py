"""Unverified entries retained at call boundaries even when optional lifting is enabled."""

# 0x48ae00: the host JPEG boundary currently returns no bitmap; it is not a verified decoder.
# 0x475090: the palette table builder, done by the recovered palette_tables.c (too slow lifted).
NATIVE_UNVERIFIED_BOUNDARIES = frozenset({0x48ae00, 0x475090, 0x48ac50, 0x48ad00, 0x4e0f8b, 0x4cd8b0})

# Hand-recovered routines the dispatcher runs instead of a lifted copy: address -> (entry point in
# source/native_dispatch.c, stack bytes, stack arguments).
NATIVE_PORTS = {0x41c7b0: ('vertrix_native_title_frame', 0, 0),
                0x41b820: ('vertrix_native_game_frame', 0, 0)}

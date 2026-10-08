"""Unverified entries retained at call boundaries even when optional lifting is enabled."""

# 0x48ae00: the host JPEG boundary currently returns no bitmap; it is not a verified decoder.
# 0x475090: the palette table builder, done by the recovered palette_tables.c (too slow lifted).
NATIVE_UNVERIFIED_BOUNDARIES = frozenset({0x48ae00, 0x475090})

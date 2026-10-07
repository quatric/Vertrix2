"""Unverified entries retained at call boundaries even when optional lifting is enabled."""

# The host JPEG boundary currently returns no bitmap; it is not a verified decoder.
NATIVE_UNVERIFIED_BOUNDARIES = frozenset({0x48ae00})

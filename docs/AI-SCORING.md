# Computer-player scoring

`ai_scoring.c` recovers the two larger evaluators:

- `0x428110`: compare the pressure of two boards (5 columns of 13 cells;
  `0xff` empty, 5 stone, 6 bomb) and the player's level byte (`+0x17c`). It
  writes levels for filled cells, column heights (or 4 when a top-row path is
  open), stones and bombs, with their positive differences, plus three flag
  bytes (`0x10..0x12`). Bytes `0x01`, `0x06`, `0x0b` and `0x0f` are written by
  `0x427c10` (see AI-FEATURES.md). The bomb level is compared with the stone
  level of the second board, because the original reuses `edx`.
- `0x428610`: score a record list (mode, count, five-byte records) against a
  byte table and a limit; recorded smallest ranks double as the score, otherwise
  per-slot 8-bit sums are averaged and combined per mode. Records whose slot is
  outside the six sums overrun the original's stack and are rejected natively.

`tools/verify_ai_scoring.py` runs both complete originals 8,192 times over
random boards, levels, record lists, tables and limits and compares every output
byte and the signed score (`ai-scoring-verification.json`).

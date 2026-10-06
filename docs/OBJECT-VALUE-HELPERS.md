# Object value helpers

`object_value_helpers.c` recovers five small pure routines.

- `0x4776a0`: decimal text with a digit limit. At most `width` digits (lowest first, so a
  longer number loses its top digits), zero gives one digit, a negative value uses one
  position of the width and gets a minus sign. `-2147483648` keeps the original 32-bit
  quirk (negated value stays negative, digits come out as `'0' + negative remainder`).
- `0x478b70`: ramp of `word(+0x26)` bytes at `+0x130`, step `0x100 / (n - 1)` (a single
  entry is `0x80`), saturating at `0xff`.
- `0x478da0`: remaining = `+0x14 - +4 * byte(+0xc)` to `+0x18`, flag `remaining != 0` to `+0x10`.
- `0x478480`: clamp a signed position into the word rectangle `+0x3c..+0x42`, store words at
  `+0x48/+0x4a` (below the minimum wins).
- `0x479a40`: pack `0x00rrggbb` for pixel format byte `+0xd` (0 = 3-3-2, 1 = 5-5-5, 2 = 5-6-5,
  otherwise unchanged); also stores the format in global `0x558a50`.

Verification (`tools/verify_object_value_helpers.py`): 8,192 complete original executions
per routine; text buffers and length, whole objects, results and the global compare.
Evidence: `object-value-helpers-verification.json`.

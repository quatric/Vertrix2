# Nine-record event stack

`event_stack.c` recovers the small stack of 0x34-byte records embedded in an
engine object (record `n` at `+0x34 * n`, record count byte at `+0x208`; the
count addresses the top and record 0 is the unused bottom):

- `0x482060`: push (stdcall, 11 stack arguments). Does nothing when nine records
  are already stacked; otherwise increments the count and fills the new record.
- `0x482110`: pop. Does nothing when the count is zero; otherwise copies the top
  record to each non-null destination pointer, then decrements the count.
- `0x482210`: overwrite the record at the current top (even record 0) from each
  non-null source pointer without changing the count.
- `0x482300`: 1 when the count is zero.

Fields are named by record offset (`b00`, `d04`, ...); their purpose is not
recovered. Short storage is rejected unchanged, as for other storage modules.

`tools/verify_event_stack.py` runs each complete original 4,096 times with random
counts (including out-of-range values), contents and random null/non-null pointer
subsets, comparing the whole object and every output. Evidence:
`event-stack-verification.json`.

`0x478cd0` maps a key byte to a slot index 0..4 (keys 8, `0xf`, `0x10`, `0x18`,
`0x20`) at `+0xd`; other keys leave storage untouched. `0x478da0` scales the
dword at `+0x4` by the byte at `+0xc`, subtracts from `+0x14` into `+0x18`,
and reports whether the result is nonzero (also stored at `+0x10`); only the
stored byte participates despite the full-`edx` register traffic. Both covered
by `verify_event_stack.py` (4,096 cases each).

# Table queries

`table_queries.c` recovers small lookups over the static and session tables. Tables are
supplied as the original bytes; the original reads fixed globals.

- `0x417930`, `0x417970`: byte pair at `row*28+column` of `0x4f9320`/`0x4f9538`; the second
  returns `0xffffffff` for a zero entry, else the byte of `0x4f90f7` at `first*8+second`.
- `0x417cf0`, `0x417d10`, `0x417d40`, `0x417d70`: dword at `row*22+column` of `0x533e1c` (the
  last three add the dword `0x4f8ce0/e4/e8`).
- `0x417df0`, `0x417da0`: any nonzero in 13 byte rows of `0x4f9ad8`; number of 6 groups of 5
  bytes of `0x4f9800` with a nonzero byte.
- `0x417e20`: threshold bonus (`(limit-value)*multiplier[level]+base`, +50%, capped at 99999999).
- `0x417fc0`, `0x418000`, `0x418050`, `0x4180a0`: per-column counts / n-th row over the 19
  column grid at `0x534c18` with counts at `0x534f10` (match a value, or the values 0, 3, 4, 5).
- `0x417840`: last index (<= 254) where consecutive dwords of `0x533290` differ, plus one. A limit
  of 255 or more never terminates in the original (the byte counter wraps).
- `0x40f170`: 1-based first of 96 words (`0x4f74d4`) not above the value.
- `0x415c00`, `0x415c30`: all 19 dwords nonzero (`0x5344a4`, `0x5344f0`).
- `0x415e40`, `0x415e80`: last index matching by compare callback (`0x4ccfe0`) or equality.
- `0x4153e0`: pair of dwords of the 14x20 table `0x5336ac` by mode (2m, 2m+1; mode 6: rows 10,
  11; mode 5: rows 12, 13).
- `0x417e60`, `0x417ed0`: random zero slot of 19 (draw `0x4826c0` supplied). The original reads
  stale stack for a draw not below the count; the native returns 0 there.

Verification: `tools/verify_table_queries.py`, 4,096 cases per routine against the complete
original (only `0x4ccfe0` and `0x4826c0` are data-driven stubs). Evidence:
`table-queries-verification.json`.

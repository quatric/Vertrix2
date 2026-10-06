# Release tables

`release_tables.c` recovers two shutdown loops over global handle tables:

- `0x43f3f0`: for the 548 entries at `0x5410f8`, release every nonzero entry
  (original `0x4830f0`) in order, then store zero in the dword at `0x54406c`.
- `0x442110`: release all 115 entries at `0x54414c` (original `0x4ea190`),
  zero entries included.

The release routines are supplied boundaries. `tools/verify_release_tables.py`
runs both complete originals 2,048 times with random tables, stubbing and
logging the callee, and compares the ordered events, the state dword and the
unchanged tables (`release-tables-verification.json`).

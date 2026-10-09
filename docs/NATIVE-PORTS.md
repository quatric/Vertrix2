# Native ports in the lifted dispatcher

Routines whose batch lift did not pass verification
(`docs/lifted-batch-verification.json`) are otherwise call boundaries:
lifted callers that reach them fall through to the platform. A hand
recovery can take their place in the dispatch table:

1. Write it over the original's address space with
   `source/native_memory.[ch]`. An address the services resolve is used in
   place. Any other address is read through `VertrixGlobals` and stored
   through the `0xf0000000` pseudo call, exactly as `lift_load` and
   `lift_store` do on the lifted host.
2. Verify it against the original with a dedicated oracle. The oracle
   should cover both the object path and the globals path.
3. Add an adapter with the lifted-routine signature to
   `source/native_dispatch.[ch]`, list it in `NATIVE_PORTS`
   (`tools/dispatch_boundaries.py`) and run `tools/gen_dispatch.py`.

| Original | Routine | Source | Oracle / evidence |
|---|---|---|---|
| `0x410270` | S3M pattern converter (`docs/S3M-PATTERN.md`) | `source/s3m_pattern.c` | `tools/verify_s3m_pattern.py`, `docs/s3m-pattern-verification.json` |
| `0x4327e0` | Slot kind snapshot (28 lifted call sites) | `source/native_ports.c` | `tools/verify_kind_snapshot.py`, `docs/kind-snapshot-verification.json` |

## 0x4327e0 slot kind snapshot

eax = slot pointer array, edx = kind bytes, ebx = count. For each slot the
kind byte is first set to `0xff`. The slot dword is then read, and when it
is non-zero the byte at object `+0x15c` replaces the `0xff`. The loop is a
do-while ending when the slot pointer reaches `eax + count * 4` (unsigned,
wrapping, so a count of `0x40000000` or `0xc0000000` runs once). A zero
count returns at once. eax on return is the final slot pointer. Because the
stores happen in order, overlapping arrays see earlier stores. The native
array form for the recovered board code is `vertrix_board_snapshot_kinds`
(`source/board_markers.c`).

Verification: 4,096 complete original executions compare the returned eax
and the whole 0x20000 byte test memory. The cases cover zero, ordinary,
wrapping and huge counts, unaligned and overlapping arrays, and empty and
occupied slots. Two thirds of them serve the kinds, the slots or the
objects as globals. Page zero is unmapped for this oracle, so a slot
pointer overwritten by an overlapping store faults as on Windows. Such
cases, where the original itself faults, are skipped and counted. The
batch lift had failed because of this oracle artifact and the generic
oracle's pointer draws; the routine has no exception frame.

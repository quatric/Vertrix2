# Native ports in the lifted dispatcher

Routines whose batch lift did not pass verification
(`docs/lifted-batch-verification.json`) are otherwise call boundaries:
lifted callers that reach them fall through to the platform. A hand
recovery can take their place in the dispatch table:

`tools/port_oracle.py` is the shared oracle harness for these ports (mirrored regions, object
and global modes).

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
| `0x4046e0` | Coded-stream bit read (24 lifted call sites) | `source/native_ports.c` | `tools/verify_bit_read.py`, `docs/bit-read-verification.json` |
| `0x4346b0` | Line-matching pass (6 lifted call sites) | `source/native_ports.c` | `tools/verify_line_pass_port.py`, `docs/line-pass-port-verification.json` |

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

## 0x4046e0 bit read

The byte at the stream pointer (global `0x51f014`) is shifted left by the
low five bits of the bit index (global `0x51f018`) as an eight bit operand
(`shl bl, cl`), so an index of 8 to 31 leaves zero. The top bit is the
result. The routine then stores index plus one, advances the pointer by
`(index + 1) >> 3` (arithmetic) and stores the index's low three bits, in
that order. `vertrix_bit_reader_next` (`source/bit_reader.c`) is the same on
a native reader. Verification: 4,096 complete original executions cover
indexes below 8, wide and negative indexes, and the byte served from an
object or from globals. The result, the order of the three global stores
and both memory regions compare.

## 0x4346b0 line pass

The same algorithm as `vertrix_line_pass` (`source/match.c`): the board is
copied, then the six directions are scanned, and runs longer than the
threshold byte set their mask dwords to 1. Widening the oracle's domain
beyond the earlier `tools/verify_line_pass.py` (masks 0/1, rewards below
0x10000, game palettes) exposed two details that matter over the raw
address space:

- A cell counts as already marked only when its mask dword is exactly 1
  (`cmp dword ptr [ecx], 1` at `0x434b70`). The native model's `!= 0`
  agrees only for 0/1 masks.
- The reward is a 16-bit word (`mov dx, word ptr [eax]` / `inc` / store at
  `0x434b93`), so it wraps at 0x10000 and leaves the upper half alone.

Both are harmless for `match_board`, which clears the mask and counts from
zero, but the port follows the original. Verification: 8,192 complete
original executions over any board byte, arbitrary mask dwords, wrapping
rewards and any threshold byte (with garbage above `bl`). A third of the
cases take the globals path. The full eax and the board, mask and reward
regions compare.

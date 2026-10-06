# Chain-select win handler (0x43ac00)

`vertrix_object_chain_select` in `source/object_glue.c` reproduces the win
handler that the progress update (`0x43b720`), the post-lock dispatchers
(`0x4517c0`, `0x451920` twin) and the timed power states replay through the
win boundary. It stores one at the holder's `+0x474`, runs the holder's
virtual slot 6 (`0x43d320`, already recovered), then branches on the state
the slot left behind: one takes the first path (chain length one, the
`+0x474` cleared to zero, fallback `state_defaults[column]` from the
original table `0x532ca4`); anything else takes the second path (chain
length five, `+0x474` kept at one, fallback the original global
`0x4f81cc`). The chain is looked up in the grid (`0x534c18`) by the
column at `+0x488` through the counts at `0x534f10` (`0x417fc0` /
`0x418000`, already recovered), and the first matching row addresses the
cell array at `0x544f90` (`0x118` bytes per column, `0x1c` per row). An
empty result stores the zero address for chain one and returns without
storing for chain five. The selected row is stored as the value of a fresh
`0x10`-byte table (`0x43d330`, raw `0x4ca000` operator new — no constructor
runs, so `+0xc` is untouched) alongside the fallback and a zero, and the
holder's `+0x468` object is release-called with the new handle. The state
the slot leaves is a caller-supplied parameter: the boundary call cannot
observe the method's memory write, so the verifier drives both sides with
the same post-call value.

Two oracle traps were found while proving it: the table constructor
`0x487870` returns Self in eax (a zero-returning stub breaks the store
address), and the verifier's grid seed must stay inside the original
`0x534c18..0x534f10` region (19 columns by 10 rows) or it overwrites the
counts at `0x534f10`.

Verification (`tools/verify_object_chain_select.py`, evidence
`docs/object-chain-select-verification.json`): 2,048 complete original
executions pass, covering the returned eax, the holder `+0x474` writes,
the new table bytes, the release target object, the slot-6 call, the
release arguments (native `0x4d88a0` against original `0x4879f0`) and the
`0x10` allocation. All four path shapes execute.

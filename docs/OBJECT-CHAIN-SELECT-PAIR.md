# Chain-select-pair handler (0x43acd0)

`vertrix_object_chain_select_pair` in `source/object_glue.c` reproduces the
sibling of the win handler used by the timed power states (and 48 other
callers): it runs the holder's virtual slot 6 (`0x43d320`) — ignoring its
result and the state at `+0x474` — then looks up the chain of length two in
the grid (`0x534c18`) by the column at `+0x488` through the counts at
`0x534f10`, taking the first matching row to address the cell array at
`0x544f90` (`0x118` bytes per column, `0x1c` per row). An empty result
stores the zero address (there is no early-return path here). The selected
row is stored as the value of a fresh `0x10`-byte table (`0x43d330`) with
the fallback `pair_defaults[column]` of the original table `0x532cf0` and
a zero, and the holder's `+0x468` object is release-called with the new
handle.

The native shares the `chain_select_run` core with
`vertrix_object_chain_select` (two named natives, one static body — the
same pattern as the post-lock twin): the pair fixes chain two, always
stores, and writes no state.

Verification (`tools/verify_object_chain_select_pair.py`, evidence
`docs/object-chain-select-pair-verification.json`): 2,048 complete
original executions pass with the same return/table/release/slot-6
coverage as the `0x43ac00` proof. Both path shapes execute.

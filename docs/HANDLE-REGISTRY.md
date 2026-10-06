# Handle registry and guarded calls

`handle_registry.c`: `0x40a890` add to the 8 slot set at `0x52f090`; `0x40ad50` release handle
(table `0x52f0b0`, count `0x52f130`); `0x40ab60` init (zero 32 entries, call `[0x52f03c]`);
`0x40aba0` shutdown (3 when any entry in use, else clear and call `[0x52f040]`); `0x40ab20`
reentrancy guard around `[0x52f020]` (disabled when `0x4f6418` is 0xffff, depth `0x4f644c`);
`0x40aca0` close (`[0x52f058]`, then release the cell's object via `0x4ea190`); `0x40a860` assign
one of 12 texts (`0x4f641c`) through `0x4eb860`.

Not ported: `0x40a8f0` and `0x40a950` (they dispatch through function pointer cells held in the
registry slots, which have no recoverable native form yet) and `0x40a800` (copies two static
tables into library state).

Verification: `tools/verify_handle_registry.py`, 4,096 executions each; the library entries
and RTL calls are data-driven stubs whose call sequence and arguments compare. Evidence:
`handle-registry-verification.json`.

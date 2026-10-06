# Device flags

`device_flags.c`: the flag-byte state machine at `0x531b44` (bit 7 open, bit 5 locked, bit 4
dirty, bit 0 parameters set). Status 0 ok, 2 invalid argument, 3 closed.
`0x40ee30` mark dirty, `0x40ee60` set limit (<= 0x40), `0x40eea0` set pair, `0x40ef00` read the
values `0x531b5c`/`0x531b50`, `0x40ef40` read the locked bit, `0x40ede0` lock: sets bit 5 and
calls `0x40ae00(item, 0)` (supplied) for each of `count` (`0x531b48`, signed) items at
`0x531ac4`.

Verification: `tools/verify_device_flags.py`, 4,096 executions each; `0x40ae00` is a stub whose
calls compare. Evidence: `device-flags-verification.json`.

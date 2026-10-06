# Player actions

`player_actions.c` recovers two routines of the player object (the event stack is embedded at
`+0x19c`, the board object is the dword at `+0x15c`):

- `0x43bb60` pushes an event describing the player on its event stack (bytes `+0x4c4`, `+0x4c5`,
  `+0x4cc`, `+0x4cd`, dwords `+0x4c8`, `+0x194`, `+0x198`, `+0x154` and board fields `+0xb80`,
  `+0xc0`, words `+0x12`, `+0x1a`, dwords `+0xb84`, `+0xb88`) through the recovered
  `0x482060`. A full stack drops the event.
- `0x43b7c0` draws levels below 10 until one differs from the current level (`+0x17c`) and sets it
  with `0x43b810`.

`tools/verify_player_actions.py` runs each original routine 4,096 times (the recovered callees run
for real, the random draw `0x4826c0` is stubbed and replayed and the notification `0x431400` is
stubbed and logged) and compares whole objects, notifications and the draws consumed. Evidence:
`player-actions-verification.json`.

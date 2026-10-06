# Label actors `0x4b65d0`, `0x45fb00`, `0x45fc80`, `0x45fe10`, `0x45fee0`

- `0x4b65d0` (`vertrix_object_label_text`, `source/object_label.c`, `tools/verify_object_label_text.py`,
  `docs/object-label-text-verification.json`): 4,096 complete original executions. It assigns the
  text through `0x4ca370`, stores the glyph byte and the four words, calls `0x4408e0` with four
  pointers to locals and copies the results to `+0xe`, `+0x16`, `+0xf4` and `+0xf8`.
- `0x45fb00` and `0x45fc80` (`vertrix_label_frame`) build a framed label from a frame actor
  (`0x170` bytes) and a text actor (`0x180` bytes) linked by `0x4b3210`. `0x45fe10` and `0x45fee0`
  (`vertrix_label_box`) build a single box actor (`0x160` bytes). `source/label_actor.c`,
  `tools/verify_label_actor.py`, `docs/label-actor-verification.json`: 1,024 complete original
  executions of each routine, every callee call with registers and stack arguments, the returned
  actor and every pool object compare. Changing one stored constant makes the oracle fail.
- The box routines add 2 to a dword whose high half is an uninitialised stack halfword; that
  halfword is a parameter (`stale`) that the oracle reads from the original's stack.
- Callees stay call boundaries: `0x4ca000` (operator new), `0x4b3100`, `0x4b6350`, `0x4b5400`
  (class wrappers), `0x4adf20`, `0x4b54d0`, `0x4ac7b0`, `0x4ac4e0`, `0x4ac4f0`, `0x4b3210`.

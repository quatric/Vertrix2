# UI slide setup

`ui_slide_setup.c` recovers four small actor position routines. All edit signed-word
fields of one actor: `+0xe/+0x16` current x/y, `+0x10/+0x18` start, `+0x12/+0x1a` step,
`+0x14/+0x1c` target.

- `0x4717f0`: start = current, step 8/8, y += 0x140 (enter from below).
- `0x4719a0`: start = current, step 8/4, y -= 0x70, then `+8/+0xa` = new x/y.
- `0x471820`: mode 1 enters from the left (x = offset - distance - 4), any other mode
  from the right (x = word `0x5b9c8e` + 4 + offset); start/target y = current y,
  step 8/8. The original removes two stack words and reads only the first.
- `0x457890`: centres the actor on its anchor words (`+8/+0xa/+0xc`) using the measured
  resource size from `0x4b14c0` (reused through `vertrix_resource_measure_state`).
  Missing descriptor and screen state are supplied parameters.

Verification (`tools/verify_ui_slide_setup.py`): 4,096 complete original executions per
routine, including the real `0x4b14c0` with and without a descriptor; the whole 256-byte
actor compares after every call. Evidence: `ui-slide-setup-verification.json`.

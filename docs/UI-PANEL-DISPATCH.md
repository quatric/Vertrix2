# UI panel dispatch

`ui_panel_dispatch.c` recovers the broadcasts over the four player panel objects held in
the globals `0x54670c`, `0x546710`, `0x546714`, `0x546718` (panel handles are identity
tokens; the class vtable at object `+0x158` is supplied through `VertrixVirtualCall`).

- `0x45f9f0`: slot 0 (destroy, argument 2) on every non-null panel, order 0..3.
- `0x45fa70`: slot 1 on panels 0..3, no null checks (the argument register carries the
  vtable pointer and is not modeled).
- `0x45fab0`: slot 2 with the caller's argument on panels 1, 2, 3, 0, no null checks.
- `0x472d50`: slot 0 (argument 2) on the single panel at `0x546794` when non-null, then
  the global is cleared.

Verification (`tools/verify_ui_panel_dispatch.py`): 2,048 complete original executions
each; every virtual call and the cleared global compare. Evidence:
`ui-panel-dispatch-verification.json`.

# Composed proof: attack entry with real state entries

`tools/verify_object_attack_composed.py` (evidence
`docs/object-attack-composed-verification.json`) runs the original
`0x4522c0` with the real `0x43bce0` (`vertrix_player_enter_452370`) and
`0x43bd00` (`vertrix_player_enter_4523d0`) bodies executing inside the
call handlers, against native `vertrix_object_enter_attack` with the same
real natives linked in.

Only `0x43bbf0` and the cursor method stay stubbed (logged and replayed).
2,048 cases pass across dead-opponent / state-1 / step-set / full-attack
buckets — return value, every Calls call, the method cursor/table/return,
and every pool object compare.

Oracle trap: the handlers mutate the host buffers while the oracle runs,
so the native phase would start from already-transitioned state (the
failure showed the native reading back `STATE_BUSY` written by the
handler's `enter_4523d0` instead of the case baseline). The harness
snapshots all pool buffers before executing and restores them after; the
handler return values are recorded and replayed, which is unaffected.

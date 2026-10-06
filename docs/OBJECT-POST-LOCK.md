# Post-lock handler (0x4517c0)

`vertrix_object_post_lock` in `source/object_events.c` reproduces the
original post-lock/post-clear dispatcher: the largest composition in the
recovered tree so far, wiring nearly every bonus-chain native together.

Disassembly (`work/disassembly.txt:101224`, twin at `0x451920`):

```
prologue: esi = edi = eax (player); cursor = [player + 0x15c]
  match = 0x432480(cursor, side=[player + 0x4dc], outs)   (boundary)
no match: suppress=[player + 0x44c] == 1 -> 0x452250 (real arm_hold)
  bonus_ready == 1 -> event(0x451a60), set_b08(2), clear_18c, cursor method
  else -> event(0x450ff0), set_b08(0), cursor method
match: mode=[player + 0x4c8] == 0x24 -> sfx(mode_fx) + reset_side (real)
  bonus_ready -> match_reward (real, reward) -> add_score (real, mult)
  chain++/total+=reward; count == 3 or 6 -> sfx(chain_fx)
  flag_a == 1 -> sfx(flag_fx); elif flag_b == 1 -> sfx(alt_fx)
  event(0x4520f0); cursor method
every path ends at the cursor method ([cursor + 0x158 + 4]) and returns
its eax; the shared block lives at 0x451832, which the first trace
misread as a plain epilogue.
```

Depth of the composition: the reward loop runs the real progress update
(which runs the real conditional reset, the real sfx routing and the real
level bump) and the real bonus branches run the real hold arming, side
reset, score and meter stores. Only the match scan, the event machine,
the cursor method, the letter, the win handler and the refresh/notify/
play/allocator leaves stay boundaries. Sub-call results are ignored as
in the original; 0 returns only when the entry reads fail.

Verification (`tools/verify_object_post_lock.py`, evidence
`docs/object-post-lock-verification.json`): 1,024 complete original
executions pass across suppressed/dead/armed/bonus/spawn/mode-24/chain-3/
chain-6/flagged/random buckets — return value, every call log, all six
pool objects, the loser flag and the RNG position compare (both sides
seeded identically, preview regeneration consuming in lockstep).

Oracle traps caught during verification:
- The shared tail is a cursor-method call, not an epilogue; every path
  returns the method's eax (native first returned a constant 1).
- Match-scan stack outs arrive last-push-first: `stack[0]` is `&-0x20`
  (flag_b), `stack[1]` is `&-0x1c` (flag_a); reward/mult ride in ebx/edx.
- The chain-effect and progress-win effect ids are the same global
  (`0x4f81b4`); separate test values diverge immediately.
- Direct-callback boundaries must still pop one replay value per oracle
  stub hit, or later pops misalign (first seen as a method-return
  mismatch).
- The `PostLockFrame` must travel as the context into `progress_update`;
  passing the services context instead segfaults in the reset shim.
- Unbounded `+0x180` chains make loop-heavy cases crawl; chains are
  clamped to small test values.

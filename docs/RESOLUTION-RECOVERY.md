# Resolution recovery

Native `vertrix_score_add` preserves `0x0043ba90`: multiply the input by
the difficulty factor (5, 10, 20 at `0x004f80cc`), add to player `+0x174`,
then cap the unsigned result at 99,999,999. Multiplication and addition wrap
in 32 bits before comparison. 30,147 original-instruction comparisons passed,
including normal inputs, cap boundaries, and overflow cases.

Further instruction-level findings, not completed native state transitions:

- `0x004517c0` and `0x00451920` invoke match orchestration `0x00432480`
  with player `+0x4dc`. Matching updates level/bonus progress through
  `0x0043b9c0`, scoring through `0x0043ba90`, and fields `+0x184`
  (increment) and `+0x188` (add the matched reward).
- `0x0043b9c0` subtracts reward from `+0x180`. Below one, it adds 12
  repeatedly, updates levels through `0x0043b720` and `0x0043b800`, and
  invokes sound and other services. It updates `+0x18c`, capped at 3,
  except when `+0x44c` is 1. These services and transitions remain to port.
- `0x0043ba70` tests `+0x18c == 3`; `0x0043ba80` resets it.
- The two resolution handlers have differing chain notification branches:
  `0x004517c0` checks chain counts 3 and 6; `0x00451920` checks 3.
  Preserve this distinction when implementing their final state machines.
- Resolution transitions lead toward callbacks `0x004520f0`,
  `0x00451a60`, and `0x00450ff0`. Graphics updates, bonus interactions,
  clear timing, and subsequent piece spawning remain unfinished.

The level-to-motion update `0x00431400` is now native as
`vertrix_motion_level`: for an active piece with state `+0x168 == 0`, select
the difficulty/level period at `0x004f7d50`, write its `+0xc0`, select the
low 16 bits of the step table at `0x004f7dc8` for `+0x1a`, and reset
counter `+0xbc`. A nonzero state suppresses all three updates. 360 comparisons
execute the full original update, including its original setter and counter
reset, across all difficulties, levels, and several state/initial values.
The table extraction is reproducible with `tools/recover_tables.py`.
Frame scheduling, interpolation, and full level/bonus transitions remain to port.

The two original integer timer families (`0x004ac500` and `0x004ac600`)
are native in `timer.c`. They add global elapsed input `0x005bd834` to
their wrapping counters, compare unsigned against the period, divide for
completed cycles, scale with a wrapping multiply before division, and retain
the remainder when consuming completed cycles. Division treats period zero
as one; the due check still compares against zero. 24,802 sequence comparisons
execute both original families across boundaries and random 32-bit inputs.
The floating interpolation helpers and calling frame schedule remain unrecovered.

The elapsed producer `0x004b7d10` is native as `vertrix_frame_sample`.
It reads an unsigned clock sample through import `0x004f172c`, writes current
sample `0x005bd838`, and updates baseline `0x005bd844`. If current is not
greater than baseline, elapsed is zero; otherwise subtraction is capped at
65,535 and written to `0x005bd834`. Equal, backward and wraparound samples
still update the baseline. 10,100 comparisons passed with the original
clock import supplied by the oracle and all arithmetic instructions unchanged.
Wii clock integration, startup baseline initialization, pause/elapsed overrides,
and the full frame schedule remain separate work.

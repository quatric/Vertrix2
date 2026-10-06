# Composed proof: reward -> progress -> level

`tools/verify_player_reward_composed.py` (evidence
`docs/player-reward-composed-verification.json`) runs the original
`0x43b9c0` with its inner `0x43b720` / `0x43b800` executing for real
against native `vertrix_player_match_reward` driving the real
`vertrix_player_progress_update` / `vertrix_player_bump_level` natives.

Only true boundaries are stubbed and logged on both sides: `0x43bb00`,
`0x4715a0`, `0x43c0e0`, `0x43ac00` (replayed win returns from a shared
queue), `0x4726d0`, and `0x431400`. 2,048 cases pass across reward-loop /
progress-win-alive / progress-win-dead / meter-only / random buckets,
comparing the whole player object, opponent untouchedness, the loser flag,
and all six call logs.

Oracle trap: the win handler fires once per loop iteration, so the shared
win-return queue is pre-filled with 64 values per case; a single value
exhausts the queue (`IndexError`) on multi-iteration loops.

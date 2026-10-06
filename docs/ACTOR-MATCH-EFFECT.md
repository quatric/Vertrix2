# Match-effect actor factory (0x430190)

`vertrix_actor_spawn_match_effect` in `source/actor_spawn.c` reproduces the
effect actor built by the match orchestrator (`0x432480`) for special
column cells: the base position words come from the source dwords `+0xc` /
`+0x14` (arithmetic shift right `0x10`, plus `0x77` / `0x137`);
`0x4ca000(0x15c)` allocates the actor, which a non-zero result sends through
`0x4abd70`, then `0x4adf20` (five zero stack arguments) initialises it,
`0x4ac470` sets four steps, `0x4ac7b0` one period step, `0x4ac8d0` binds
resource `0x544d28` and `0x4ac710` selects frame zero. The position words
`+0xe` / `+0x16` are the scaled pair sums minus three (16-bit add, 32-bit
subtract, word store). Only the allocator goes through the calls boundary;
every other callee is an already-proven pure routine called directly, so
the oracle lets them execute for real on both sides.

Verification (`tools/verify_actor_match_effect.py`, evidence
`docs/actor-match-effect-verification.json`): 1,024 complete original
executions pass, comparing the returned actor handle, the single allocator
call and every pool object.

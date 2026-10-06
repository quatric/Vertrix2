# Match burst spawner (0x4302a0)

`vertrix_actor_spawn_match_burst` in `source/actor_spawn.c` reproduces the
eight-actor burst built by the match orchestrator (`0x432480`): one draw
below `0x168` gives the shared descriptor and one below two plus three the
shared count; every actor takes the position words `+0xe` / `+0x16`
(source words plus the scaled pair plus `0xc`), resource `0x54651c`,
handler `0x444700`, the unsigned remainder of the descriptor below `0x168`
in word `+0x24` and the count in `+0x28`, and is appended to the list at
source `+0xcec`. The allocator, draw, frame bind (`0x4ac8a0`, which
provably preserves edx, so the post-bind `idiv` genuinely divides the
descriptor) and list append go through caller hooks; every other callee is
an already-proven pure routine called directly.

Verification (`tools/verify_actor_match_burst.py`, evidence
`docs/actor-match-burst-verification.json`): 512 complete original
executions pass, comparing the zero return, the draw divisor order, the
bind (actor, descriptor) pairs, the append (list, item) pairs and every
pool object. The oracle allocator never returns the source handle (a real
allocator returns fresh memory; aliasing would corrupt the source mirror).

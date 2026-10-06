# Match scan orchestrator (0x432480)

`vertrix_match_scan` in `source/match_scan.c` reproduces the figure/line
match orchestrator that both post-lock dispatchers replay through the
match boundary: snapshot the 65 slot kinds (`0x4327e0`), clear the mask
(`0x432840`), refresh the full 65-byte line image, run the figure pass
(`0x434ee0`, flags word A and B on a hit), run the line pass (`0x4346b0`
on the unmodified image with the side byte as threshold, flag word A on a
hit), sweep the 5×13 cells with the timer set and the clear event
(`0x4504e0`), then run the per-cell reward loop (score multiplier, timer,
kind byte, effect actor `0x430190` plus effect event `0x450450` and burst
spawner `0x4302a0` for kind 7 with the burst event `0x450330`, otherwise
the virtual dispatch from table `0x4fb7b0`, then the burst event for every
cell). Returns one unless nothing matched and no cell was swept.

Notable traps, all proven against the original: the image copy is a full
65 bytes (the disassembly drops a `rep` prefix — 16 dwords plus one byte);
the return is cell-sweep OR match (not match alone); the line path sets
only the first flag word; the return out-words, reward and multiplier are
four separate stores; the post-call state the slot method leaves behind is
a caller parameter. Two genuine bugs in already-proven callees surfaced
while proving this routine: the line pass now treats kind 7 as an ordinary
run color, never rewards fresh cells and reports only added reward
(evidence `docs/line-pass-verification.json`); the figure pass gates
members (not anchors) against `{0xff, stone, bomb}`, compares colors
sign-extended, tests overlap against call-fresh scratch, brands accepted
cells 7 in a commit phase and writes mask/brand only when enabled
(evidence `docs/figure-pass-verification.json`).

Verification (`tools/verify_match_scan.py`, evidence
`docs/match-scan-verification.json`): 128 complete original executions
pass, comparing the return value, all four out-words, the player bytes,
the line image, the 65 mask dwords, every object and the draw/bind/append
call logs. Only the allocator, the random draw, the frame bind, the list
append and the virtual method are stubbed.

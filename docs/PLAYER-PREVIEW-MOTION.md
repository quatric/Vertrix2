# Preview-parent movement start and limit

`player_preview_motion.c` recovers original `0x42b000` and `0x42b050` on
serialized player storage. A nonzero state at `0x178` suppresses movement-start
changes. Otherwise the routine sets that state to one, assigns the original
difficulty-indexed fast period and step, and clears the primary counter. The
existing recovered timing helper supplies these tables; no new timing model
is introduced. Difficulty0..2 is required only when the state is zero.

The limit helper compares current Y at `0x16` with the limit at `0xae` as
signed 16-bit values, returning true only for strictly greater Y. Both helpers
preserve outputs when required storage is unavailable.

The extended player-preview verifier executes each complete original routine
without hooks in 4,096 cases. Entire player storage compares for movement
start across all difficulty values and zero/nonzero state. Signed limit results
compare across randomized words. There are 8,192 short-storage preservation
checks. Including prior mode/selection/snapshot cases, the verifier now covers
28,672 original helper calls. Scheduling this movement and connecting the
full player state machine remain unfinished.

# Active-piece parent update

`piece_actor_update.c` recovers original `0x42ac40` ordering. Advance the
parent primary timer; if due, consume complete cycles and move Y by step times
cycles unless field `0x17c` is nonzero. Then virtual-update seven nonnull child
slots, apply their mode-dependent effect, and run the recovered `0x42af30`
layout. Timer and position arithmetic wrap as in the original.

When parent mode `0x180` and flag `0x184` both equal one, child effect `0x48`
becomes -200. Otherwise it becomes the low word of that child's `0x58` value.
Handles and mode fields are read as reached. Null slots are skipped; repeated
handles retain repeated updates. The caller supplies child virtual dispatch,
mutable storage resolution, elapsed time and original row height. Child
classes and handlers remain explicit rather than inferred from sprite banks.
Late failure retains earlier timer, movement and child mutations.

The extended layout verifier executes complete original `0x42ac40` without
hooks in 4,096 cases, using actual original base-class virtual updates with
all four recovered piece callbacks. Whole parent/child storage matches movement, zero periods,
timer wrap, stopped movement, mode effects and final layout. Native child
dispatch and three resolver passes match expected slot ordering. Another
4,096 checks confirm short-parent rejection before mutation. The original
layout comparisons remain included.

`vertrix_piece_actor_update_resource` connects the parent traversal to the
recovered child frame entry point, including conditional refresh clearing.
The caller supplies a shared explicit resource graph and identity resolver.
Fixtures use direct and null resources; original VF resource publication,
surrounding player dispatch and full game-loop/Wii execution still need work.

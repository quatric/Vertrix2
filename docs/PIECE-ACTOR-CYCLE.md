# Active-piece actor rotation

`vertrix_piece_actor_cycle` recovers complete original `0x42af80`. With fewer
than two active actors, it returns without resolving or changing anything.
Otherwise it rotates active parent handles left, sets the new penultimate
actor's callback to `0x44c370`, and the final actor's callback to `0x44c2b0`.
Repeated handles preserve the original assignment order. Counts0..7 are
supported. The caller owns stable storage and supplies mutable resolution.
Invalid count, short parent or unresolved required endpoint preserves output.

The extended layout/update verifier executes complete original `0x42af80`
without hooks in 4,096 cases across counts0..7. All parent and child bytes
compare, including unused slots, null intermediate handles and repeated
endpoints. It checks 12,288 invalid-count, short-storage and null-endpoint
preservation cases. The existing complete parent update and layout comparisons
remain included. Connecting input actions to this routine and complete player
scheduling still require integration.

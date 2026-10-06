# Piece parent and base actor destructors

`piece_actor_destroy.c` recovers original `0x42ab10`, vtable slot 0 of class
`0x514774`, and `0x4ac130`, the base actor destructor it calls.

`0x4ac130`: without flag 4, store class `0x517af4` at `0x158`, then free the
storage when flag 2 is set. `0x42ab10`: store class `0x514774`, call each
nonzero child's virtual destructor (slot 0, flag 2) in slot order
`0x15c..0x174` without clearing the slot, then run `0x4ac130` with the same
flags. Flag 4 is the original virtual-base cleanup path and is rejected.

Child destruction and storage release are supplied boundaries. The vtable
(`0x514774`) is: `0x42ab10` destroy, `0x42ac40` update, `0x42abf0` forward slot 2
to every child, `0x42ac10` and `0x42ac10` no-ops, `0x42ac30` self slot 2, and
`0x4adf90`.

`tools/verify_piece_actor_destroy.py` runs both complete originals in 8,192
cases, recording child destructor and free arguments, and compares the whole
parent storage and event order. Evidence: `piece-actor-destroy-verification.json`.
Child destructor bodies and slot 2 (`0x42abf0`) remain separate.

## Slot 2 forwarding

`0x42abf0` calls vtable slot 2 (`[vtable + 8]`) with the caller's `edx` on each
nonzero child in slot order; `0x42ac30` calls the actor's own slot 2 with the
same `edx`. `0x42ac10` is a bare `ret`. Native entry points
`vertrix_piece_actor_forward_slot2` and `vertrix_piece_actor_self_slot2` take
the slot-2 target as a callback receiving handle, vtable token and argument.
`tools/verify_piece_actor_slot2.py` compares both complete originals in 8,192
cases (call order, identity, argument; storage unchanged) plus 8,192 rejection
cases. Evidence: `piece-actor-slot2-verification.json`. Slot-2 bodies remain
separate.

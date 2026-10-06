# Player companion actor setup

`ui_companion_actor.c` recovers the original base constructor and
`0x42b3f3..0x42b499` setup preceding image binding. The three preview slots
use the selected interface resource `0x5449fc`, source descriptor plus slot
with unsigned 32-bit wrapping, timer 12, amount zero, anchor zero, and the
caller's linked identity. Slot identity at actor offset `0x58` is one-based.
Position can be supplied by the separately recovered border position table.

The helper preserves bytes that the original does not initialize. Invalid
indices and insufficient storage preserve the entire destination. Serialized
resource identities remain little-endian tokens, never native pointers.

`verify_ui_companion_actor.py` executes the original constructor and setup
without hooks and compares all 384 bytes of extended actor storage in 2,048
cases, including signed positions and arbitrary source/linked identities.
It also checks 4,096 failure-preservation cases. Allocation, attachment to the
player, subsequent image and callback binding, update execution and full
gameplay remain separate; this component alone does not make a playable game.

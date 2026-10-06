# Final companion and border setup

`ui_preview_pair.c` composes the recovered side/slot positions, companion and
border constructors, direct image binding and final callback assignments from
the original player setup. Companion actors use the selected interface bank
`0x5449fc` at source plus slot and callback `0x44ff90`. Border actors use the
generated bank `0x5466a4` at frame zero and callback `0x450130`.

The caller supplies distinct actor storage and live resolved banks. Construction
stages both base actors, validates both bindings, then publishes both. Unrelated
bytes and extended storage are preserved. Overlapping base storage, invalid
slot, insufficient storage, missing bank or out-of-range frame fail without
changing either actor. Bank ownership remains with the caller; this helper
does not allocate actors or attach them to player arrays or the scene.

The verifier executes the original base constructors and complete setup
fragments through `0x42b4b4` and `0x42b586` without hooks. Actual original
`0x4877f0` descriptor binding runs against direct resource fixtures. Descriptor
pointers normalize to the native bank-local indices, and all extended actor
bytes compare in 2,048 pairs, covering all three slots and all side bytes.
There are 6,144 failed-binding/overlap preservation checks. VF bank loading has
separate evidence; actual constructed pair update/draw frames, player ownership
and registration, and complete gameplay still require integration. Complete
preview-loop construction and parent handle publication now have separate
evidence in `UI-PLAYER-PREVIEWS.md`.

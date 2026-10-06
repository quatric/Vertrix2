# Selected sprite and interface resources

`sprite_resources.c` composes the recovered 20 direct sprite loads with the
original `0x45e490` solid/hollow artwork builder, `0x45e530` additional image,
and their render views. It uses
the already selected `0x5449fc` interface bank and `0x546538` stencil bank.
It therefore honors the supplied stencil selector without a second VF load or
a separately hardcoded stencil filename.

The published map includes the 20 original direct resource tokens and generated
tokens `0x546618`, `0x546634` and `0x5466a4`. The generated animation resources remain
available through the artwork view. Selection, channel masks and descriptor
format are explicit. Loader initial selections can be supplied by
`vertrix_sprite_selection_init`; later settings changes remain caller-owned.

Loading stages all owned allocations before publishing the context. Every
internal bank, frame, binding, map and animation-descriptor pointer is rebased
into the final storage. Keep that context at a stable address while actors or
renderers borrow it. It owns pixels after archive closure. Freeing releases the
generated artwork and direct banks; borrowed render-view frames are never
separately freed. Output must start at zero; failed loads preserve it.

`tools/verify_sprite_resources.py` compares eight integrated sets with the
separately original-verified artwork path across source-frame, first-source and
channel-order variations. After closing the VF, it checks generated pixels,
dimensions and origins, all 184 published bindings and the internal pointers.
The additional image matches the separately original-verified border builder.
It checks occupied-output rejection, repeated free, invalid source frame,
insufficient stencil frames, a missing final bank and unsupported descriptor
format, plus failure of the final additional-image source selection. See
`sprite-resources-verification.json`.

This is a resource integration component, not complete startup execution.
Other original derived builders, font and audio graph integration, actor/scene
creation, gameplay scheduling and Wii execution remain separate. The portable
component compiles for PowerPC; the whole game is still not playable.

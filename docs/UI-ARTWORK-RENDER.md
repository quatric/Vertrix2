# Rendering generated interface artwork

`vertrix_ui_artwork_render_view` connects the owned images produced by the
recovered original `0x45e490` VF artwork builder to mapped actor rendering.
It borrows the solid/hollow images, creates their frame descriptors with the
original wrapping origins, and exposes one-frame banks under resource tokens
`0x546618` and `0x546634`.

The caller supplies the recovered descriptor format word; the adapter accepts
the four-byte source format used by the recovered renderer. It exposes two
animation resources using bank-local descriptor ID0, so update-time frame
binding and draw-time binding agree. These resources belong to the render view;
they do not modify the existing display asset structure's descriptor IDs.
Pass them in the frame options and pass the view's bank map to mapped frame
rendering. Final scene scheduling and original runtime artwork selection remain
outside this adapter.

Artwork owns the pixels. Keep the artwork and view at stable addresses while
actors/frame options borrow them. The view owns no allocation and must not be
freed through sprite/bank ownership functions. Releasing artwork invalidates the
view. Invalid input or an occupied view is rejected without mutation.

`tools/verify_ui_artwork.py` now verifies the adapter against actual generated
original banks for all eight existing VF artwork configurations. It compares
descriptor metadata and shared pixel ownership, then executes complete original
`0x4ac8a0` binding and `0x4af8c0` drawing for 1,024 cases, covering both generated
images, clipping, anchors, vertical displacement and scale8/16. Native targets
and actor storage match the original after normalizing descriptor identity.
The original artwork builder's allocation/resource construction boundaries are
supplied as in its existing verification; drawing executes without hooks.

This verifies actual generated artwork through rendering. It does not prove
complete game scene construction, full application behavior or Wii execution.

`vertrix_ui_artwork_actor_construct` binds the recovered interface constructor
to the render view's solid descriptor. It uses the original 24 placements and
alternating animation setup for pair0..11 on both sides, leaving allocation and
scene registration to the caller. Invalid parameters preserve actor storage.

The verifier additionally executes original base construction and complete
position/setup fragments for all24 actors and compares every actor byte.
It then runs complete original `0x4b6200` update and `0x4b6240` draw against
the composed native frame path for sixteen persistent frames in each of the
eight generated artwork configurations: 128 frames at640x480. It compares all
destination pixels, every actor byte and six shared refresh words. The two
additional idle actors supply explicit linked-player identity/state fixtures;
they are not a recovered player implementation. Timers use explicit500ms
intervals to exercise the animation transitions and solid/hollow bank changes.
Original builder allocation boundaries remain supplied; frame update and drawing
execute without hooks. These checks join actual generated VF images, original
setup and animation, but final game scheduling and player/menu behavior remain
unfinished.

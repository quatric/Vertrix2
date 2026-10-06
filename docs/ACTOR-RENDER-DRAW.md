# Drawing decoded VF frames through actors

The actor-level binding/drawing entry points also support explicitly mapped
direct resource banks. `vertrix_sprite_actor_image_resource` and
`vertrix_sprite_actor_draw_resource32` validate the caller's resource identity
against actor field `0xb0`. `vertrix_sprite_actor_draw_mapped32` reads that field
and selects the first matching entry in a live `VertrixSpriteBankMap`. They retain
the original descriptor binding and drawing order without guessing asset names.
The existing main-bank entry points delegate with token `0x5449fc`.

The verifier compares 8,192 explicit-resource draws and 8,192 mapped draws with
whole original `0x4ac8a0` and `0x4af8c0`, rotating direct-bank identities
`0x5449fc`, `0x546618` and `0x546634`. VF sprite fixtures are supplied explicitly
to those original banks; this validates identity-based drawing, not final asset
selection for each game resource. Unselected native mapping entries have no
bank, so selecting the wrong entry fails the comparison. Mismatched identities
and absent mappings preserve actor, destination and render preparation.
Mapped variants of the linked, scene and frame APIs select each reached
actor's bank from its current resource token. Frame rendering resolves that
token after the recovered update has completed, so bank switches take effect
in the same frame. Existing main-bank APIs delegate through a one-entry map.

`vertrix_actor_render_draw32` connects the recovered actor geometry, style,
render preparation, operation selection and pixel traversal to decoded
`VertrixSpriteFrame` artwork. Frames may come directly from the original VF
loader; the draw path retains their descriptor anchors and format flags.

The target is a bounded four-byte surface. Direct actor coordinates, vertical
displacement, clipping and scale advances determine source and destination
positions. The draw operation uses the original binary-alpha flag and actor
alpha override. Drawing stages the destination and render preparation before
publication; rejected inputs preserve both, and source pixels remain unchanged.
Disjoint destination rows stage only the clipped rectangle, rather than the
entire screen. Overlapping destination rows retain shared backing and their
original stride. This reduces copying and temporary storage for ordinary
sprites; actual Wii performance has not been measured.

`vertrix_sprite_actor_draw32` also resolves the actor's selected frame from the
configured VF bank. It follows original `0x4ac8a0` binding then `0x4af8c0`
drawing, retaining the local frame identity in actor field `0xb4`. It currently
requires initialized geometry and direct-coordinate mode `0x144 == 1`.
Invalid frame selection preserves actor, destination and preparation. Once
binding succeeds, its actor mutation precedes drawing even if drawing clips or
rejects unsupported effects, matching the original order.

`tools/verify_actor_render_draw.py` executes original `0x4ac8a0` then complete
`0x4af8c0`, including real `0x4ae3e0` and `0x4af560`, with no drawing hooks.
It compares all destination bytes
for 8,192 cases, including 6,144 cases using ten actual frames decoded directly
from `sprite/damier.spr` in the original VF. It checks scale 1–16, anchors,
vertical displacement, clipping, binary/opaque pixels and alpha override.
It also checks actor effects 0, 1, 3–8, amounts 0/25/50/75/100, fixed colors,
color transforms, palette shifts and cycling, including overlapping destination
row strides. Source preservation, invalid actors and truncated destination
failure preservation are checked. Unmatched original flag combinations leave
pixels unchanged; the native component explicitly rejects them.
The same cases verify combined bank binding and drawing, including actor field
mutation, prepared state and invalid frame failure preservation.

`vertrix_sprite_chain_draw32` implements original `0x4ade60` traversal: bind
and draw each actor before reading its next handle at `0x108`. It resolves local
handles through the caller's actor store and preserves prior draws if a later
actor cannot be resolved or drawn. A supplied budget terminates malformed cycles.
An empty chain succeeds without accessing destination or actor storage.

The verifier also runs complete original `0x4ade60` across 512 chains with
3,193 actors and compares the entire destination and every actor's storage,
normalizing descriptor pointers to local frame IDs. Actual VF sprites overlap;
copy/fade, scale 8/16 and alpha override are included. Cycle budget exhaustion
and failure resolving a later actor retain the verified preceding draws.
This chain path shares the bank draw restrictions: initialized direct-coordinate
actors, the direct `0x5449fc` bank, and no border or callback rendering.

`vertrix_sprite_scene_draw32` connects original `0x4b6240` scene traversal to
linked VF drawing. It snapshots the root handles and signed Y coordinates,
then draws in ascending Y with stable list order for ties. Original sentinel
32000 excludes roots at or above that Y. Linked companions still draw through
their root even if their own Y would exclude them as independent roots.
Duplicate root entries retain their separate draws. Root class `0x517af4`
selects the recovered virtual method `0x4ae140`; other virtual classes reject.
The original scratch arrays bound this component to 1024 scene roots.

Complete original `0x4b6240` execution matches 256 scenes with 1,288 root draws,
including real base-class virtual calls and the full linked draw pipeline.
Checks cover signed negative Y, equal-Y stability, duplicate roots, sentinel
exclusion and companions, comparing all destination bytes and actor storage.
Empty scenes work without a destination; oversized scenes and unsupported
classes preserve destination and preparation. Full game scene construction,
other actor classes, general transforms and final Wii presentation remain
unfinished.

`vertrix_ui_scene_frame_render` joins recovered `0x4b6200` virtual scene
updates with sorted `0x4b6240` drawing. Its frame options carry the elapsed
interval, refresh state and live animation resources. Update failure prevents
drawing; failure during drawing retains completed updates and any earlier draws.
The caller still supplies scene construction, background and frame scheduling.

The combined verifier executes both original functions for 1,024 consecutive
frames across 128 persistent scenes, with eight frames per scene and 6,760 actor
updates/root draws. Whole actor storage, shared refresh words, list contents and
destination bytes match. All twelve recovered interface handlers plus
idle actors are included, exercising transitions, linked identity lookup,
visibility changes, timers and scaling with actual VF sprites. Original refresh
fixture storage uses six words before the adjacent renderer kernel pointer;
the isolated update tests' larger synthetic backing is not used here.
Failure tests verify that rejected updates prevent drawing and that a drawing
failure retains the fully verified preceding updates.

512 frames use three distinct banks made by reordering decoded VF frames;
3,608 mapped actor updates/draws include 34 observed resource identity switches.
The distinct banks expose wrong resource selection in destination comparisons.
64 additional complete original linked draws compare mixed resource banks
within a chain. These are explicit fixture bank assignments; final original
asset-bank construction remains to be connected.

This frame composition currently uses explicitly mapped direct VF banks and
actors without interaction targets or child update chains. Final asset-bank
construction, full game scheduling, menus/player integration and Wii presentation remain
unfinished. Passing consecutive component frames does not prove a playable game.

This composition verification covers direct coordinates and recovered effects.
Special clipping flags and transform traversal remain unsupported here. Other
amounts and palette shifts have separate component verification but are not
all enumerated by this actor-level test. This is a recovered drawing component, not a playable
Wii application or proof of hardware behavior.

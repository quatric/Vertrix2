# VF interface artwork

`vertrix_ui_artwork_load` loads the caller-selected original VF sprite bank,
applies the five recovered clone/mirror substitutions, and generates two owned
images from one selected configured frame using Circle.spr frame 9, with solid
and hollow stencil modes respectively. The initialized selection at 4fbfac is
34. This follows
the recorded original45e490 artwork sequence. Descriptor origins include the
stencil half-width/half-height with unsigned 32-bit wrapping.

The filename, first-source selector and artwork frame index remain explicit inputs.
The startup selector has not been proven; Damier.spr is a verification fixture,
not a claim about the original startup selection.

`tools/verify_ui_artwork.py` executes the complete original45e490 builder,
actual4877f0 lookup, actual4831b0 stencil and actual487850 publication. Hooks
supply empty resource construction and image allocation. Input pixels come from
the separately verified VF decoding/configuration path. Eight configurations
cover both color orders, two first-source selections and artwork indices 0/34.
Both output pixels, dimensions and origins are compared with original execution.
Output rejection, failure cleanup and ownership after VF closure are checked.
The JSON report records the verified pixel count.

`ui_display.c` owns the artwork and exposes two one-frame resources for the
recovered alternating display handlers. The original546618 resource binds the
solid image and original546634 binds the hollow image. Descriptor identifiers
0/1 are local bank identifiers, not emulated addresses. Image resolution checks
both resource identity and descriptor, returning the borrowed pixels and full
32-bit origins for the renderer. Keep the asset structure at a stable address
while displays reference it; free it only after retiring those displays.

The VF integration check exercises both original attachment branches after the
archive closes, resolves their matching oracle-verified pixels, rejects an
unbound display, preserves occupied assets, and rejects freed assets. The
complete six-phase handler oracle remains separate. This adapter does not yet
draw the display or integrate the application's full actor scheduler.

The Wii build verification now covers all 115 portable source modules and finds
no unresolved recovered dependencies. Final application integration and hardware
execution remain unfinished.

The construction loop at46dfda..46e32a is recorded in ui-display-setup.json,
reproducible with tools/recover_ui_display_setup.py. It creates twelve pairs of
alternating displays, linked to IDs23/24, with thresholds1..12 shared by each
pair. Primary periods are10; secondary periods decrease from441 to1 by40 per
pair. The four initialized coordinate tables supply signed relative positions
at four-byte strides, added to runtime533d70/533d74 with16-bit wrapping. All
alternating displays start in phase0 with source0, handler450a10, frame0 and
solid resource546618. Separate movement displays are also created per side.
This is static instruction/table evidence; constructor defaults, full object
creation and startup globals still require execution verification.

verify_ui_display_setup.py additionally executes both complete post-position
initialization fragments46e101..46e16e/46e290..46e302 without hooks. All object
bytes match512 seeded cases, including real resource attachment and descriptor
binding. Both sides share each pair's threshold; the right fragment advances
the pair counter and coordinate offset. Primary/secondary counters retain their
prior values, animation counter/frame reset, and animation period is retained.
ui_display_initialize_animation implements these recovered animation fields
for pairs0..11 using the owned VF resources. The VF integration check covers
all twelve pair settings and invalid-pair preservation. Actor IDs/flags,
constructor defaults, position setup and list insertion remain outside this
animation setup API and require further integration.

ui_display_layout.c implements the original coordinate tables and16-bit offset
addition for all24 display positions. verify_ui_display_setup.py now additionally
executes both preceding position fragments and actual4adf20 without hooks,
comparing native coordinates and all original object bytes in512 cases. The
setter initializes origin/current X/Y, zeros angle/orientation and clears initial
resource/frame/descriptor/handler fields; the native layout API returns only
coordinates, leaving actor storage initialization to the forthcoming constructor.
Adjacent oracle fragments invalidate translated code blocks between changing
stop boundaries so a cached block cannot bypass a new emulation stop.

The original base actor constructor4abd70 now has complete execution evidence:
121 writes match512 randomized whole-storage cases without hooks. See
ACTOR-CONSTRUCTOR.md and actor-constructor-verification.json. Full actor storage
integration and allocation/list insertion remain outstanding.

ui_actor_storage_construct now combines the verified base constructor, original
coordinate tables and alternating-display setup into complete portable storage
creation for each pair/side. Its complete output, including untouched bytes and
bytes beyond base storage, matches512 original constructor-plus-setup executions.
The verifier supplies a direct one-frame original resource and descriptor token;
actual lookup and binding execute. The native constructor accepts the mapped
descriptor token, retains original resource/handler identities as tokens, and
rejects invalid pair/side/short storage without mutation. Scene allocation,
registration, native token mapping and actor update/render integration remain
unfinished. This comparison covers creation, not an entire game session.

ui_actor_update.c now dispatches all six recovered alternating handlers from
portable actor storage. It maps stored546618/546634 resource identities to
borrowed native resources, decodes words/dwords explicitly, invokes the verified
handler implementation, and writes only modeled fields back. Class metadata and
unrelated actor bytes remain intact. Unknown resource tokens and invalid storage
are rejected before mutation. The caller still resolves the linked actor.

The updated complete-handler verifier compares this storage adapter with12288
original executions without hooks, including5750 handler changes and612 actual
resource switches. It checks entire object bytes, unchanged linked storage, and
short/unknown-token rejection. Descriptor values remain mapped identity tokens;
VF asset binding, scene lookup/registration and rendering still need integration
with this storage adapter. This handler verification uses direct resource
fixtures and does not establish a playable application.

ui_display_storage.c now connects portable actor creation/update to the owned
VF artwork bank. Creation uses the solid-image descriptor identifier; update
maps original resource identities through the two native one-frame resources.
Image resolution verifies both stored resource identity and descriptor before
returning borrowed pixels and original32-bit origins. It preserves outputs on
invalid descriptors or freed assets. Actor bytes never contain native pointers.

The VF verifier now exercises all24 pair/side creations and both original
attachment branches after archive closure, checks matching oracle-verified
pixels/origins and retained constructor padding, and checks invalid descriptor
and freed-asset rejection. Allocation/scene registration, linked-actor lookup,
rendering and full application execution remain unfinished. Runtime filename
and first-source choices remain explicit rather than inferred startup defaults.

ui_actor_storage_update_list now performs original4b5eb0 linked lookup before
dispatching the six recovered handlers. Display field4 selects the first listed
actor whose field0 matches; its fields58/64 supply the linked values. A callback
resolves scene handles to stable live storage. Missing matches preserve the
original waiting behavior; unresolved or short storage fails before mutation.
The complete original handler oracle compares this adapter in12288 cases with
two duplicate IDs carrying different values, verifying first-match selection,
whole display bytes and resource changes. Unresolved-handle preservation is
also checked. Scene allocation/registration, other actor types and rendering
remain unfinished; this is linked lookup integration, not a complete scene.

object_list_append now implements original4b5e70 registration within caller-
reserved list capacity. It appends without sorting or deduplication and preserves
unused tail slots. verify_object_append.py executes complete original4b5e70,
4d88a0 and4d8770 without hooks in2048 capacity/count/handle fixtures, comparing
all list descriptor bytes and every item slot. Native full-capacity and null-
handle rejection preserve storage. Original allocation growth remains outside
this append API and its proof; caller allocation, complete scene construction
and scene-wide scheduling still require integration.

object_list_owned.c now implements original4d8770 owned allocation/resize and
registration growth. Initial capacity equals requested count; subsequent growth
uses count/8 clamped4..1024, or the explicit original growth-step setting.
Active slots are copied, newly active slots zeroed, shrinking retains stale tail
within existing capacity, and resize0 frees list allocation. Actors remain owned
by the scene. Native allocation failures preserve the prior list.

verify_object_growth.py compares512 original resize executions with native
count/capacity/all active slots, including independent combinations of adaptive
and fixed growth settings and initial/shrink/grow/zero requests. Hooks provide
allocation/free and CRT copy; original growth logic and memset execute unchanged.
Uninitialized unused tail on new allocation is not compared. An ordered2048-
registration native sequence and disposal also pass. Scene construction and
full application execution remain unfinished.

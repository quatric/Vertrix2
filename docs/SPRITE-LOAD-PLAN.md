# Startup sprite selection and owned banks

`sprite_load_plan.c` preserves the 20 direct sprite loads made by original
`0x45dca0`, in their execution order. Inputs are the 19 runtime setting bytes at
`0x513c4d..0x513c5f` and the separate interface selector at `0x53bd09`. Each entry
retains the original resource identifier and selects a filename from the VF's
SpriteFileName.ini table. Resource identifiers are opaque tokens, not Wii pointers.
Invalid selection or filename resolution preserves the output plan.

`sprite_load_set.c` owns those 20 direct banks and publishes a map for the existing
mapped actor renderer. Resource `0x5449fc` alone receives the recovered interface
clone/mirror replacements through the existing UI-bank loader; other banks retain
their direct processed frames. Graphics masks and first-source selector remain
explicit. Output stays unchanged on failure; successful banks own their pixels
after archive closure. Keep the set at a stable address while borrowed by a
renderer. Freeing releases every frame and clears the set.

`vertrix_ui_artwork_build` accepts the already loaded interface and stencil banks
and generates the original solid/hollow interface images using source frame
selection and stencil frame 9. It borrows bank pixels and owns the resulting
images. This allows the selected startup banks to supply artwork without a second
VF load or an independent hardcoded stencil choice. The artwork verifier compares
this path's pixels, dimensions and origins with the existing original-execution
checks across all eight artwork configurations.

This does not execute the complete startup graph. Progress updates, other derived
builders, runtime settings initialization and application scene construction
remain separate. The loader-initialized byte at `0x53bd09` is zero because it is
in the uninitialized `.bss` section; this selects damier.spr. Earlier evidence
that recorded 13 was a test-harness mapping error: pefile copied file-offset-zero
bytes into this section. The original execution harness now clears uninitialized
sections with no raw-data pointer. Runtime settings changes remain explicit;
loader initialization alone does not prove the entire startup path.

`vertrix_sprite_selection_init` exposes that loader state: the 19 initialized
setting bytes are 1 through 19, interface slot and first-source selector are
zero, the initialized artwork source at `0x4fbfac` is 34, and the additional-image
source at `0x4fbf74` is 20. The verifier compares
every field against the corrected loaded image. These values can initialize
runtime selection storage; later original settings updates remain separate.

`tools/verify_sprite_load_plan.py` executes the complete original `0x45dca0`
control flow with resource-loading, progress, clone/mirror and derived-builder
side effects supplied at boundaries. The actual filename builder executes.
Across 512 selector sets, all 10,240 resource/path selections match; 1,024 invalid
selections preserve native output. These hooks verify selections and ordering,
not the skipped side effects or post-configuration startup state.

`tools/verify_sprite_load_set.py` compares every frame's metadata and bytes with
an independent VF/SPR decoder after closing the archive. It checks six mask
orderings and two explicit first-source fixtures, including simultaneous mirrored
interface replacements, stable bank-map pointers, occupied-output rejection and
failure at the final missing resource. The reference preserves the verified
SPR channel swap and subsequent mask-rank conversion rather than assuming a
general RGB byte-routing rule. Reports are `sprite-load-plan-verification.json`
and `sprite-load-set-verification.json`.

The portable library compiles for PowerPC. Full startup, playable gameplay and
Wii execution remain unfinished.

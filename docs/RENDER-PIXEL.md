# Flag-selected pixel drawing

render_pixel.c connects the original92-rule flag selector and32-bit address
table to eighty-seven recovered native pixel kernels. Original addresses are evidence
identifiers in a switch; Wii code never calls them. Each operation consumes
numerical source/destination pixels and the native preparation/table views.
Missing required storage or an unsupported selected kernel preserves output.

Supported kernels include full direct copy, palette and fixed-channel conversion,
constant-color half blending, constant blend followed by palette conversion,
palette-row half selection, palette channel-index averaging, ordinary half blend,
packed add/subtract/invert effects, weighted palette-index blending and weighted
RGB byte-table blending. Palette kernels use the prepared signed map shift and
the recovered prefix/row/suffix view resolver. The row-half kernel48da80 averages
map selectors but retains source channel indices;48dba0 averages channel indices
but retains the source map selector. These behaviors are distinct.

Additional kernels include48de30, which selects the source map row and the
destination channel indices;48df10 exchanges those roles. Kernel48dff0 first
blends RGB at50 percent and then converts the result through its own palette
lookup, distinct from index averaging. Kernel490560 first weights RGB through
the byte tables and then converts that packed result through the palette.
Separate original48db70/48dcd0 half-blend and4902a0/4904c0 weighted kernels
share verified native implementations while retaining their original selection.

Kernels48e0c0,48e190,48e280,48e370 and48e460 convert the source through
the palette before applying half blend, add, either subtraction direction or
inversion. Kernel48e520 converts the destination before inverting it. This
ordering matters: applying the effect before palette conversion changes output.
Kernel48e5f0 averages source/destination row selectors while using the prepared
fixed channel indices.

verify_render_pixel.py executes the original4af2a0 selector and4b1fde address
selection unchanged, followed by the selected original kernel body. Each of the
eighty-seven supported kernels matches256 cases, for22272 total, using the recovered
palette/weight tables, variable signed map shifts, fixed indices and constant
colors. All1280 other rule-fixture calls reject while preserving native output.
Rejecting those kernels is explicit unfinished work, not proof of compatibility.

The comparison begins with prepared views and numerical pixels. It does not
cover complete actor preparation, source-alpha traversal, clipping, drawing
whole sprites, other pixel formats, presentation or Wii hardware execution.
Full game integration remains unfinished and no playable build is claimed.

Kernel48e6c0 adds separately truncated quarter-source and quarter-destination
RGB to the prepared half-color. Kernel48e700 averages source/destination
channel indices, then averages each result with its fixed index while retaining
the source row selector. Kernel48e850 maps fixed indices through the source
row before blending the resulting RGB with the destination at half strength.

Kernel48e900 adds fixed-index palette output to the destination;48eb40
subtracts that output from the destination. Kernel48e9d0 first blends source
RGB with the prepared half-color, then applies packed addition. Kernel48ea30
averages source channel indices with fixed indices, maps through the source
row, then applies packed addition to destination RGB.

Kernel48ec10 subtracts the source/constant half-blend from the destination;
48ee50 reverses that subtraction. Kernel48ec70 averages source and fixed
channel indices, maps through the source row, then subtracts the mapped RGB
from the destination. Kernel48ed80 subtracts destination RGB from the
fixed-index palette output. All retain the original packed subtraction masks.

Kernel48eeb0 averages source and fixed channel indices, maps through the
source row, then subtracts destination RGB from that mapped value. The
comparison executes its complete original body, including packed borrow masks.

Kernel48efc0 inverts source RGB before selecting its palette row, then
uses the prepared fixed channel indices. Kernel48f070 inverts source RGB
before half blending with the prepared constant color. Both operation orders
are verified against complete original kernel executions.

Kernel48f0a0 inverts source RGB, then averages its palette channel indices
with fixed indices and maps through its row. Kernel48f190 inverts destination
RGB before fixed-index palette conversion. Kernel48f230 inverts destination
RGB before half blending with the prepared constant color.

Kernel48f260 inverts destination RGB, averages the resulting palette
channel indices with fixed indices, and maps through the inverted destination
row. Its complete original body matches256 dispatcher-selected cases.

Kernel48f360 uses the source palette row and fixed channel indices; its
destination lookup does not affect the resulting pixel. Kernel48f430 maps
destination channel indices through the source row, then half blends that RGB
with the prepared constant color. Both complete original bodies are verified.

Kernel48f520 averages destination palette channel indices with fixed
indices, then maps the result through the source palette row. Its complete
original body matches256 dispatcher-selected cases.

Kernel48f620 uses the destination palette row with fixed channel indices.
Kernel48f6f0 maps source channel indices through the destination row, then
half blends the mapped RGB with the prepared constant color. Both complete
original bodies match256 dispatcher-selected cases each.

Kernel48f800 averages source palette channel indices with fixed indices,
then maps through the destination palette row. Its complete original body
matches256 dispatcher-selected cases.

Kernel48f910 sums separately truncated quarter-source and quarter-destination
RGB with the prepared half-color, then converts that combined pixel through
the palette. Its complete original body matches256 selected cases.

Kernel48f9f0 half blends source RGB with the prepared constant color,
converts that result through the palette, then applies packed addition to
destination RGB. Its complete original body matches256 selected cases.

Kernels48faf0 and48fbe0 half blend source RGB with the prepared constant
color and convert through the palette before packed subtraction. The former
subtracts mapped RGB from destination; the latter reverses that subtraction.
Both complete original bodies match256 selected cases each.

Kernels48fcd0 and48fdb0 invert source or destination RGB respectively,
half blend with the prepared constant color, then convert the result through
the palette. Both complete original bodies match256 selected cases each.

Kernel48fe90 maps destination channel indices through the source palette
row, half blends that RGB with the prepared constant color, then converts
through the palette again. Its complete original body matches256 cases.

Kernel490010 maps source channel indices through the destination palette
row, half blends that RGB with the prepared constant color, then converts
through the palette again. Its complete original body matches256 cases.

Kernel4901a0 weights source and destination row selectors through the
prepared word tables, then maps source channel indices through that row.
The sum retains original16-bit arithmetic. Signed word selectors now resolve through the complete backed map layout;
only combined shift/selector slots outside-200..400 reject. Complete original bodies match256 selected cases.

An additional601 complete4901a0 executions cover every backed map slot with
random channel bytes and word operands whose16-bit sums wrap to signed
selectors. Variable shifts include negative and greater-than255 selectors.
These fixture tables isolate arithmetic and map resolution; they supplement
the comparisons using recovered percentage tables.

Kernel4906a0 converts source RGB through the palette before blending it
with destination RGB through the prepared percentage byte tables. Its complete
original body matches256 selected cases, distinct from490560 which converts
after weighting.

Kernel4907d0 weights source and destination row selectors through the
prepared word tables, retaining16-bit signed sum semantics, and maps fixed
channel indices through the selected row. Its complete original body matches
256 dispatcher-selected cases with recovered percentage tables.

Kernel4908c0 weights source and destination RGB channels through the byte
tables, adds the corresponding prepared fixed-color channel, and halves each
sum before packing. Its complete original body matches256 selected cases
with independently varied fixed-color channels.

Kernel490980 weights source and destination palette channel indices through
the byte tables, averages each sum with the fixed index, then maps through
the source row. Its complete original body matches256 selected cases.

Kernel490b30 maps fixed channel indices through the source palette row
before weighting that RGB and destination RGB through the percentage byte
tables. Its complete original body matches256 selected cases.

Kernel490c60 weights source and destination RGB, adds fixed-color channels,
halves each channel sum, then converts the packed result through the palette.
Its complete original body matches256 selected cases.

Kernel490dc0 uses source hue to select cycled auxiliary channel indices,
then maps through the source palette row. All256 cycle values execute the
original4754e0 binding and complete pixel kernel. The achromatic/cycle255
adjacent-global value retains the original numerical pointer-table token
54bb90+4*map_shift, never a host pointer. Default palette layout only.

Kernel490e90 selects cycled auxiliary indices using the prepared fixed hue,
then maps through the source palette row. All256 cycles execute original
4754e0 and the complete kernel with independently varied fixed hues.

Kernel490f60 half blends source RGB with the prepared constant color,
uses that blended pixel to select both hue and row, and maps the cycled
auxiliary indices through that row. All256 cycles execute original4754e0
and the complete kernel unchanged.

Kernel491050 averages source and fixed palette indices, maps through the
source row, then uses the resulting RGB hue for auxiliary cycling. The final
conversion retains the original source row. All256 cycles match complete
original binding and kernel execution.

Kernel4911d0 averages source and destination palette row selectors, uses
source hue to select cycled auxiliary indices, and converts through that
averaged row. All256 cycles match complete original binding and execution.

Kernel4912e0 separately halves source and destination RGB before summing,
uses that blended pixel to select hue and row, and maps cycled auxiliary
indices through that row. All256 cycles match complete original execution.

Kernel4913e0 averages cycled source auxiliary channel indices with
destination palette indices, then maps through the original source row.
All256 cycles match complete original binding and kernel execution.

Kernel491530 converts cycled source auxiliary indices through the source
row, then separately halves that RGB and destination RGB before summing.
All256 cycles match complete original binding and kernel execution.

Kernel491620 converts cycled source auxiliary indices through the source
row before applying packed addition with destination RGB. All256 cycles
match complete original binding and pixel arithmetic.

Kernels491720 and491820 convert cycled source auxiliary indices through
the source row before packed subtraction. The former subtracts converted
RGB from destination; the latter reverses direction. All256 cycles match
complete original binding and execution for each kernel.

Kernels491920 and491a00 select hue and row from source or destination
respectively, convert cycled auxiliary indices, then invert the resulting RGB.
All256 cycles match complete original binding and execution for each kernel.

Kernel491af0 selects the destination hue for cycling and retains the source palette row. All256 complete original executions match the native result.

Kernel491be0 cycles source hue through the destination palette row. Kernel491ce0 cycles source hue through a weighted source/destination row, using word tables with16-bit wrap and signed selection. Each matches256 complete original executions. An additional601 cycling cases cover every shifted map slot from-200 through400 using arbitrary word weights and channel bytes.

Kernel491e10 blends source/destination RGB with byte weights before selecting both cycled hue and palette row. Kernel491f70 retains source hue/row, then blends cycled auxiliary indices with destination palette indices using byte weights before map reads. Both match256 complete original executions each. The two operations preserve the original order of truncation and table lookup.

Kernel492120 selects source hue/row, resolves the cycled color, then blends its RGB bytes with destination RGB using the prepared byte weights. All256 complete original executions match. The remaining32-bit dispatch entries are48d8c0,492b90,492cc0,492dc0,492e40 and492f90.

Kernel48d8c0 retains the source palette row and averages its channel indices with the fixed indices before map reads. All256 complete original executions match. Inspection of492b90,492cc0,492dc0,492e40 and492f90 shows destination rectangle loops over5bb750/5bb752 with row advance5bb7c8; these are not single-pixel routines. They remain rejected by the pixel API until separate traversal integration.

render_row.c now composes original0x492280 binary-alpha row traversal with all87 recovered single-pixel kernels. All22,272 whole original row executions match entire backing and final source/destination pointers/counts, including unaligned/overlapping views and zero-alpha skipping. Another22,272 invalid offset calls preserve storage. Row map shifts are restricted to-100..98 so all possible cycled channel indices retain owned backing; the separate single-pixel comparisons retain their wider-100..300 shifts. The original can read adjacent global storage for some extreme map/cycle combinations, which native owned tables reject.

The row API stages one shared backing to preserve forward aliasing semantics and publishes only after success. Prepared palette/weight storage must be independent of destination. This uses a temporary backing-sized allocation; final actor integration and full scene traversal remain unfinished.

render_row.c now also implements original0x492550 sampled binary-alpha row traversal with all87 recovered kernels. It samples before each supplied advance, skips zero-alpha source, and advances both table/source even on skipped pixels. Width must be positive because the original body has no zero-width guard; the native API rejects zero rather than emulating16-bit underflow.

All22,272 complete original sampled row runs match backing and final source/destination/table pointers/count, covering zero advances, skipped source samples, unaligned aliasing and arbitrary final advances up to255. Another22,272 short-table cases preserve storage. Advance storage must be independent of destination. Horizontal table generation, vertical/actor integration and complete playable game remain unfinished.

Original0x492710 sampled opaque row is now integrated with all87 recovered pixel kernels. Unlike0x492550, every source sample invokes its kernel even when source alpha is zero. Sampling advances follow the invocation. All22,272 complete original executions match whole backing plus final source/destination/table pointers/counts, including zero-alpha sources, repeated/skipped samples, unaligned aliasing and arbitrary final table advances. The binary sampled and unscaled row checks remain passing. Vertical/actor traversal and full playable application remain unfinished.

vertrix_render_sample32 now composes sampled rows with original0x4928f0 vertical traversal. It draws the current row, advances source by vertical byte times source byte stride and destination by its byte stride, restarting horizontal advances for every row. The original helper pipelines base-pointer updates ahead of actual row pointers; the wrapper preserves the resulting sampling order. Width and height must be positive.

All22,272 complete original sampled image executions match whole backing and final source/destination/vertical cursors and remaining height across87 kernels, alternating opaque and binary paths. Tests include unaligned aliasing, repeated rows and final unsampled advances up to255. Another22,272 short vertical table cases preserve storage. Image rendering stages the backing once and reuses it across rows, avoiding per-row copies. General transform/reverse traversal, actor preparation and scene/application integration remain unfinished.

Original0x492400 native-size opaque row is now composed with all87 pixel kernels. All22,272 complete original rows match backing and final pointers/count, including zero widths, zero-alpha source pixels and unaligned forward aliasing.

vertrix_render_image32 composes original0x492880 vertical traversal with native-size opaque/binary rows. All22,272 complete original images match whole backing and final pointers/height across87 kernels, alternating binary and opaque rendering. All22,272 invalid-source-offset cases preserve backing. The native source/destination strides include complete row spacing; original residual source padding is measured in pixels. Both native-size and sampled image paths share one staging allocation per image. General reverse/transform traversal, actor setup and playable application remain unfinished.

vertrix_render_alpha_image32 now recovers original0x4ab380 premultiplied-alpha traversal through shared staging. Alpha zero skips;255 copies the full source word; partial alpha adds source RGB to independently truncated inverse-alpha weighted destination RGB with the original packed-OR behavior. Native image and sampled binary APIs normalize their binary argument to a boolean so alpha mode stays confined to this explicit API.

All4,096 complete original executions match whole backing, including overlapping/unaligned source and destination, zero strides, empty images, alpha0/255/partial and arbitrary channel bytes. Source stride is tested in multiples of four, matching original pixel-unit residual padding. Existing87-kernel and row/image comparisons pass. General transforms and full actor/application integration remain unfinished.

vertrix_render_bound32 now composes recovered operation selection with complete32-bit native/scaled drawing. Caller supplies resolved flags, geometry and prepared palette/weight views. Rule-zero native drawing uses direct copy/binary or the premultiplied-alpha override; scaled alpha override follows the original fallback to ordinary prepared kernels. General transform paths reject and preserve backing.

All22,272 comparisons execute original0x4af786 selection through its complete selected drawing body, ending at4af7b9. Preparation0x4ae250 is a supplied boundary because inputs are explicitly already prepared. Native/scaled and opaque/binary paths alternate across all87 pixel kernels, including rule-zero alpha choices. Another22,272 transform requests preserve storage. This connects selectors to drawing bodies; actor clipping, pixel gate, full preparation, borders and presentation remain outside this API.

vertrix_render_prepared32 now composes the original pixel gate, state-to-flags construction, conditional4ae250 preparation and bound drawing. Preparation is published after successful drawing; failed backing validation preserves both preparation and pixels. A disabled pixel gate succeeds without mutation. Geometry and destination format4 remain caller-resolved.

All2,048 complete original4af560 executions match whole backing with real4ae250 and drawing bodies, after removing the supplied preparation hook used by earlier bound-image fixtures. Tests vary fixed-color banks, equal/mismatched source format, weighted effects, signed map shifts, cycles, alpha overrides, native/scaled modes and resource-null gates. Renderer tables and geometry are supplied inputs. Borders, callbacks, general transforms, actor geometry preparation and playable game remain outside this comparison. Failure-preservation cases are counted in render-pixel-verification.json.

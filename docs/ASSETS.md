# Original VF asset loading

The port uses the original `Vertrix2.vf` directly. Extracted asset folders are
development references and are not the runtime asset format.

The native loader in `source/vf.c` opens VF version 10 read-only, indexes names,
sizes and offsets, and reads requested payload ranges directly from the file.
It keeps the directory in memory rather than loading the 27 MB asset payload.
All integers are explicitly decoded as little-endian for Wii PowerPC.
Names retain their original byte encoding. Lookup accepts `/` or `\`, ASCII
case differences, and the archive's leading `./` or `.\` prefix.

For the eventual Homebrew Channel package, place the unchanged archive at
`sd:/apps/vertrix2/Vertrix2.vf`. The Wii archive module mounts the SD card and
opens this file directly; see [Wii archive access](WII-ARCHIVE.md). Full
application startup and gameplay integration remain unfinished.

```c
VertrixVf *assets = vertrix_vf_open("sd:/apps/vertrix2/Vertrix2.vf");
uint32_t index, size;
if (assets && vertrix_vf_find(assets, "texte/BackGroundFileName.ini", &index) &&
    vertrix_vf_size(assets, index, &size))
{
    /* Allocate the needed payload buffer, then call vertrix_vf_read.
     * Consumers can also read a bounded range without loading a whole asset. */
}
vertrix_vf_close(assets);
```

The loader rejects unsupported versions, truncated directories, embedded NUL
names, ranges outside the file, and payloads overlapping the directory. It
does not modify or extract the archive. One handle uses one shared file cursor;
concurrent readers need separate handles or external synchronization.

Validation reads all 1,525 original assets and compares their SHA-256 hashes
to the independently extracted manifest. It also verifies partial reads,
normalized lookup, end-of-entry bounds, and seven malformed archives.
27,491,361 payload bytes matched. Wii compilation passes; SD/hardware execution
and asset decoders remain unfinished.

```sh
python tools/verify_vf.py /path/to/Vertrix2.vf /path/to/extraction.json \
    --build-dir /path/to/scratch/vf-verification
```

## Block animation delays

`vertrix_asset_animation_ranges` in `source/assets.c` reads `texte/BlocsSpeed.ini`
from this archive and returns the original seven color delay ranges for one
character/decor row (0–19). Pass these ranges directly to spawn initialization.
They are animation delay periods, not sprite frame indices. Normal colors,
stone and bomb retain the original column mapping, verified for all 20 rows.
This is the first archive-backed consumer; general settings and image/audio
decoding still require integration.

## Original BMP artwork

`vertrix_image_bmp` decodes all original 24-bit uncompressed BMP assets directly
from the VF entry, reading one padded scanline at a time. Output is top-down
RGBA with alpha 255; the separately stored PCX masks still need decoding and
application. Initialize `VertrixImage` to zero, decode by archive name, and
release it with `vertrix_image_free`. A nonempty output is rejected so ownership
cannot be overwritten. Failed/unsupported decoding leaves output untouched.

All 70 original BMPs (986,317 pixels) match Pillow's independent RGBA decode
byte-for-byte. Twenty-four synthetic layouts additionally cover scanline
padding, odd widths and top-down/bottom-up storage; fourteen invalid inputs
are rejected. `Bloc_Mike.bmp` has an undersized declared file length, so
bounds are checked against the actual VF entry rather than that stale header.
The output remains ordinary RGBA; GX texture conversion and rendering are
still unfinished, as are JPEG/PCX assets and full Wii startup integration.

```sh
python tools/verify_image.py /path/to/Vertrix2.vf --build-dir /path/to/scratch/image
```

Report: `docs/image-verification.json`, including individual decoded-pixel hashes.

## Original PCX artwork and masks

`vertrix_image_pcx` reads all original one-plane, 8-bit RLE PCX assets directly
from VF. It preserves the palette indices and full 256-entry RGB palette in
`VertrixPcx`; original mask interpretation is a separate step. Output rows
exclude encoded scanline padding. The decoder uses a 4 KB input cache and
allocates only the resulting indices, without extracting the encoded file.
Initialize output to zero and release it with `vertrix_pcx_free`.

All 529 original PCX assets (7,677,516 pixels) match Pillow's independent index
output and palette-expanded RGB. Eight synthetic cases cover odd widths,
scanline padding, escaped high-valued indices and long RLE runs. Twelve invalid
files are rejected. Version/encoding/plane/bounds checks reject unsupported or
truncated data; failures leave output unchanged. Palette indices have not been
assumed to be alpha values.

```sh
python tools/verify_pcx.py /path/to/Vertrix2.vf --build-dir /path/to/scratch/pcx
```

Report: `docs/pcx-verification.json`, with individual decoded-index hashes.
JPEG decoding, original mask composition, GX textures and full-game rendering
remain unfinished.

## Original SPR resources

`vertrix_image_sprite` loads one frame directly from an original `.spr` VF
entry. All 20 original resources contain uncompressed four-byte frames: 216
frames and 337,657 pixels in total. It preserves the stored alpha component,
converts BGRA byte order to RGBA, retains the original ten-word descriptor,
and exposes the real frame count for recovered animation playback. Release
with `vertrix_sprite_free`. The output must be empty and initialized to zero.

Resource loading at `0x4873d0` reads a two-byte frame count, then calls frame
reader `0x482d00`. That routine reads 48 bytes: an eight-byte storage prefix
followed by the 40-byte descriptor. Width/height are descriptor `+4/+8`;
descriptor byte `+0x27` gives the four-byte pixel format. Prefix byte 0 selects
raw versus compressed storage. All supplied `.spr` frames use raw format 4.
The original channel-mask setup in `0x483ed0` uses red `0x00ff0000`, green
`0x0000ff00`, blue `0x000000ff` and alpha `0xff000000`, confirming the stored
little-endian channel order. Native loading retains that alpha byte without
assuming how separate PCX masks are combined.

An independent serialization parser verifies every original frame's dimensions,
pixel bytes, descriptor and count; nine malformed resources are rejected.
This verifies raw loading rather than claiming execution of the full original
resource reader. That reader also applies color-processing routines `0x483750`
and `0x483ed0`; both four-byte source transformations are recovered below.
Graphics format selection and the renderer's actual blending remain unfinished.
The descriptor's layout fields are retained without assigning
guessed meanings. Compressed/indexed SPR variants are unsupported, since none
of the original 20 resources use them.

```sh
python tools/verify_sprite.py /path/to/Vertrix2.vf --build-dir /path/to/scratch/sprite
```

Report: `docs/sprite-verification.json`, including per-frame pixel hashes.
JPEG decoding, separate mask application and Wii
rendering remain unfinished. The full-game goal remains active.

## Original sprite alpha normalization

`vertrix_image_binary_alpha` applies the four-byte image transformation at
`0x483750`: stored alpha zero becomes 255, and every nonzero value becomes
zero. RGB channels remain unchanged. Call it explicitly after decoding when
the original resource-loading path requires this step; raw SPR decoding still
preserves the source bytes.

Verification executes the original routine in the executable against all 256
alpha values, 131,072 random pixels, and all 337,657 pixels from the original
216 sprite frames. The native result matches exactly. This step does not
implement separate PCX mask attachment or renderer blending.

```sh
python tools/verify_alpha.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf --build-dir /path/to/scratch/alpha
```

Report: `docs/alpha-verification.json`.

## Original sprite color processing

`vertrix_image_color_order` recovers `0x483ed0` and its per-pixel helper
`0x481e10` for the fixed four-byte BGRA source used by the original SPR files.
Destination RGB mask positions determine byte ordering; alpha is preserved.
Despite accepting 16-bit destination masks, the original routine still writes
four-byte pixels rather than packing RGB565. Native code preserves that behavior.
The API rejects zero masks or equal trailing bit positions before mutation.

`vertrix_image_sprite_processed` reads a frame directly from the VF archive and
applies alpha normalization followed by color ordering. It retains dimensions,
frame count and descriptor metadata. Raw decoding remains available separately.
The caller supplies destination masks; automatic graphics format selection and
GX upload are not implemented yet.

Verification executes the complete original `0x483ed0`, including format
construction and pixel conversion, for six 32-bit and six RGB565 channel layouts
(12,288 random pixels), and all 337,657 pixels in the 216 original sprite frames.
The combined VF loading entry point is also checked against both original
processing routines for every frame.

```sh
python tools/verify_color_order.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf --build-dir /path/to/scratch/color-order
```

Report: `docs/color-order-verification.json`. Separate masks, renderer blending
and the full playable Wii application remain unfinished.

## Original binary PCX mask application

`vertrix_image_mask` recovers the binary path at `0x4797f0`: PCX index zero
sets alpha to zero, and every nonzero index sets alpha to 255. RGB channels
are preserved, and the palette is not consulted. Native code requires matching
dimensions before mutation; the original routine assumes sufficient mask data.
The separate graded effect path at `0x4798b0` is recovered below.

`vertrix_image_bmp_masked` loads artwork and its PCX mask directly from VF,
applies this operation, and releases the temporary indices. Failures leave the
output untouched. Both filenames are explicit; resource selection still needs
to follow the original asset tables during runtime integration.

Verification executes the original mask instructions with already decoded
indices supplied at the PCX decoder boundary and skips its deallocation call.
All 256 possible indices and all 7,677,516 pixels from the 529 original PCX
assets match. Direct VF composition also matches for 18 same-name BMP/PCX pairs,
covering 580,608 artwork pixels. This does not claim that every PCX is used as
a binary mask by the original game.

```sh
python tools/verify_mask.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf --build-dir /path/to/scratch/mask
```

Report: `docs/mask-verification.json`. JPEG decoding,
runtime resource selection and Wii rendering remain unfinished.

## Original graded mask effect

`vertrix_image_mask_graded` recovers `0x4798b0`. Zero indices produce alpha
zero. Nonzero indices add the supplied offset with 16-bit wrapping, then clamp
to 255. Each RGB component becomes `channel * alpha / 255`, rounded down;
the resulting alpha replaces the previous alpha. Repeated application therefore
scales the already modified RGB again, as in the original routine.

The original lookup table at `0x578600` is initialized by the loop at
`0x4807ea..0x48087a`. Verification executes that loop rather than supplying a
table generated from the native implementation. The original mask routine then
executes unchanged, with decoded PCX indices supplied at its decoder boundary.
All 65,536 channel/alpha combinations, 14 offset cases including signed and
16-bit wrap boundaries, and 7,677,516 pixels from all 529 original PCX resources
match. Each asset uses one of the tested offsets; this does not imply the
original game applies the graded effect to every PCX resource.

```sh
python tools/verify_graded_mask.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf --build-dir /path/to/scratch/graded-mask
```

Report: `docs/graded-mask-verification.json`. The effect is available for images
and PCX indices loaded directly from VF. Runtime effect selection, JPEG assets,
renderer blending and the full Wii application still need integration.

## Character block resource selection

`vertrix_asset_block_files` reads the selected character row directly from
`texte/BlocsFileName.ini`, returning artwork and mask paths under `image/Blocs/`.
All 20 rows are checked against an independent parser of the archive entry.
The first 18 pairs exist in VF, including the case variation in Valerie's mask.
The last two rows reference absent `Bloc_Special` files; the API preserves those
configured names rather than inventing replacement assets. Invalid character
indices and malformed tables leave the output untouched.

Verification is included in `tools/verify_assets.py` and
`docs/assets-verification.json`. This loads the original configuration format;
it does not claim recovery of the executable's general-purpose string parser.
Original runtime fallback decisions and sheet layout remain to be recovered.

## Original block sheet frames

`vertrix_image_block_frame` extracts 24x24 pixels using the resource ordering
at `0x45f0c0`. Original sheets measure 192x168: eight frame columns and seven
color rows. The row-to-resource table at `0x4fc048` is `5,0,1,2,3,4,6`.
Thus native normal colors 0..4 select rows 1..5, stone 5 selects row 0, and
bomb 6 selects row 6. Existing alpha and RGB processing are preserved.

Verification executes the original selection routine and captures its resource,
frame and copy coordinates at the allocation/copy boundaries. All 56 layouts
match native extraction across all 18 character sheets loaded with their masks
directly from VF: 1,008 frames and 580,608 pixels. Invalid colors and frames
are rejected. This verifies frame selection and crop contents, not renderer
blending or the original general-purpose clipping/copy implementation.

```sh
python tools/verify_block_frames.py /path/to/Vertrix2.exe /path/to/Vertrix2.vf --build-dir /path/to/scratch/block-frames
```

Report: `docs/block-frames-verification.json`. Runtime resource ownership,
graphics format selection and Wii rendering still need integration.

## Runtime-owned character block sets

`vertrix_asset_block_set` combines VF character filename selection, original
animation delays, BMP artwork, binary PCX mask application, 56 frame crops and
destination color ordering into one owned `VertrixBlockSet`. Each of seven
colors has eight 24x24 frames and its recovered animation-delay range.
Initialize the output to zero and release it with `vertrix_block_set_free`.
The set stores 129,024 pixel bytes; source sheet and mask data are temporary.

Loading is transactional: missing resources, invalid masks or partial failures
release temporary allocations and leave the output unchanged. Existing owned
frames are rejected so that reloading cannot lose their allocations. Missing
special placeholders retain their existing failure behavior without replacement.

`tools/verify_block_frames.py` verifies all 18 complete sets against the original
frame coordinates and masked VF sheet pixels, checks delay ranges, and exercises
missing-character, invalid-mask and cleanup paths. This is a runtime resource
loader, not a playable application or proof of Wii rendering. Renderer upload,
original resource lifecycle decisions and game-state integration remain unfinished.

## Wii RGBA8 texture preparation

`vertrix_texture_rgba8` converts decoded RGBA images to GX_TF_RGBA8 storage:
4x4 tiles with separate AR and GB planes. The buffer is aligned to 32 bytes;
edge padding is transparent and no source channel is changed. Logical and
storage dimensions are retained separately. Images up to 1024x1024 are accepted.
Release owned buffers with `vertrix_texture_free`.

The layout reference is Dolphin's RGBA8 texel decoder in
[TextureDecoder_Common.cpp](https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/TextureDecoder_Common.cpp).
Verification uses independent texel addressing to decode every prepared pixel
back to the masked source: all 1,008 original block frames, plus five small
fixtures exercising tile and padding boundaries. Alignment and cleanup are
also checked. This does not execute Dolphin or prove hardware rendering.

The PowerPC library includes this platform conversion. Cache flushing, GX
texture-object setup, filtering, blending and actual drawing remain unfinished.
Results are included in `docs/block-frames-verification.json`.

## Wii GX texture upload layer

`vertrix_wii_texture_init` prepares aligned RGBA8 data, flushes its CPU cache,
invalidates the texture cache, and initializes a GX texture object using the
padded storage dimensions. The logical UV limits are retained for drawing.
The caller selects GX_NEAR or GX_LINEAR explicitly; original filter selection
has not yet been recovered. This API requires an already initialized GX context.

`vertrix_wii_texture_bind` loads the object into one of the eight texture map
slots. `vertrix_wii_texture_free` waits for outstanding draws before releasing
owned pixel memory. Initializing a nonempty object is rejected, and failures
leave it unchanged.

```sh
make wii-textures BUILD=/path/to/scratch/wii-build
```

This builds `libvertrix-wii-textures.a` against the installed libogc headers.
The upload layer also passes a link-only PowerPC ELF check against libogc,
including cache, texture and draw-completion symbols. That harness is stored
outside deliverables and has not been run. No GX runtime rendering, blending,
filter fidelity or playable game is claimed by these compile/link checks.
GX startup, draw dispatch and original rendering-state recovery remain unfinished.

## VF artwork runtime descriptors

block_artwork.c owns one original character block set and exposes seven native frame resources with eight descriptors each. The loader reads artwork, masks and delay ranges directly from VF through the existing verified asset loader. Local descriptor handles 1..56 resolve to owned images; they are platform identifiers rather than original Windows pointers. The set must stay at its original address because resource nodes reference embedded descriptor arrays. Release with vertrix_block_artwork_free.

These resources can be passed directly to vertrix_block_resource_update. verify_block_artwork.py binds all 1,008 frames across 18 characters, compares pixels against the verified asset loader, checks archive-independent ownership, rejects reloads and verifies cleanup. Test animation periods are fixtures, not recovered gameplay defaults. Full actor lifecycle, GX rendering and gameplay integration remain incomplete. Evidence: block-artwork-verification.json.

### Original font-map initialization

Recovered 0x43fc50 initializes 19 maps, preserving unspecified glyphs. Letters, digits, punctuation and special GO/VS glyphs now match the original. Space dimensions for slots7–9 use original resource indices6/9 with even rounding and unsigned wrap. The helpers at0x43f480 and subsequent punctuation helpers write map indices; earlier resource-clone descriptions were inaccurate. Verification compared 5,120 full maps against the executable, hooking only resource lookup0x4877f0. VF font-resource construction and text rendering are still unfinished. Wii compilation and formatting checks passed.

## Complete original VF font glyph bank

font_bank.c implements39 original43eab0 operations and owns548 images with original descriptor origins:466 base glyphs plus82 derived glyphs. Base images use original color-order processing; stencil transforms use Circle.spr frames6/9, and final outlines run in original538,528,518 order while mutating source84..93. The complete original43eab0/43f110/43f190/4831b0/483400 execution matches310,592 final pixels and all dimensions/origins. Hooks provide independently decoded VF base sheets/stencils, allocation/clone/progress and skip separately verified map initialization. Buffer lifetime after archive close, occupied output and invalid masks are checked. OriginalRGBA order is verified. Native filenames follow verified original tables; alternate filename configurations, font-map binding, renderer and playable application remain unfinished. Wii compilation and formatting checks passed. Evidence: font-bank-verification.json.

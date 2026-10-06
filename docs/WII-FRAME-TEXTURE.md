# Uploading recovered CPU frames to Wii textures

`frame_texture.c` packs the recovered renderer's bounded four-byte surface into
GX RGBA8 4x4 tiles. The caller supplies three complete byte masks describing RGB
in each little-endian CPU pixel; the remaining byte supplies alpha. This keeps
the recovered channel layout explicit. Row stride is honored, including shared
or overlapping rows, and padding to complete tiles is transparent.

Initialization owns a 32-byte-aligned allocation. Updates validate the full
source and destination first and reuse that allocation. Invalid dimensions,
backing, masks or texture geometry preserve existing pixels and metadata.
Source and texture backing must be independent; dimensions are limited to
1–1024 pixels per axis.

`wii_frame_texture.c` adds GX object initialization and upload synchronization.
An update waits for earlier GPU draws before overwriting texture storage, then
flushes the CPU cache and invalidates the texture cache. The GX object and
allocation remain stable. Bind and free use the existing Wii texture API.
`make wii-frames` builds this path against the actual libogc headers for PowerPC.
It requires an initialized GX context; final quad geometry, video buffers and
presentation still belong to the application.

`tools/verify_wii_frame_texture.py` checks 768 initial uploads and 768 updates,
including a full640x480 frame, all24 channel permutations, padding and unusual
strides. An independent GX tile decoder compares every channel. Recorded GX
stubs verify call ordering and that old texture bytes remain unchanged until
draw completion, then check allocation/object reuse and bind/free behavior.
Invalid backing/masks reject before any GX call or pixel mutation. These host
stubs do not execute a GPU.

The actual generated VF interface-frame verifier also converts two visible
640x480 frames in each artwork configuration. Those frames first match complete
original update/draw execution, then every decoded GX tile channel matches the
verified CPU frame. Their second upload reuses the same portable allocation.
This joins original VF artwork, actor setup/animation, CPU rendering and Wii
texture packing. Final display colors require the caller's recovered masks;
the fixture specifies its byte order explicitly. Full application linking,
video presentation, hardware execution and Wii performance remain unverified.

# Original VF character textures on Wii

`vertrix_wii_block_set_load` connects the archive loader to GX texture ownership. It resolves the original character file names and animation delay ranges, decodes the paired BMP/PCX resources, preserves the recovered seven-color/eight-frame ordering, and uploads all 56 frames through the existing Wii texture module. Its explicit RGB masks produce RGBA byte order for the GX tiler. Filtering is selected by the caller.

The input archive can be `storage.archive` from `vertrix_wii_archive_open`. Initialize the GX context before uploading. Initialize `VertrixWiiBlockSet` to zero and retain it while drawing. The archive can be closed once all required resources have been loaded. Free the texture set after use; the existing texture cleanup waits for GPU draws before releasing memory.

Loading is transactional. Output stays unchanged on failure; decoded images and uploaded partial textures are released. Missing placeholder character rows are not replaced with invented assets. The original resource fallback behavior remains a separate recovery task.

`make wii-assets` compiles the module and its asset dependencies into a Wii static library. PowerPC compilation with warnings as errors, formatting checks, and a scratch Wii ELF link connecting archive open, texture-set load/free and archive close all passed. The link check is not a runtime test and is not a playable application. Actual GX upload and rendering have not yet been tested on Wii or Dolphin. Existing host verification covers the underlying archive, frame extraction and texture byte layout separately.

## Connected host verification

`tools/verify_wii_assets.py` compiles the actual VF, image, asset, texture, Wii texture and Wii asset sources together with recorded host GX/cache stubs under AddressSanitizer and UndefinedBehaviorSanitizer. It loads all 18 available character sets from the original VF, checks 1,008 frame uploads and 580,608 tiled pixels against decoded RGBA, verifies delay propagation, alignment, texture dimensions, UV limits, both filtering modes, ready-output rejection, cleanup and repeated cleanup. Three unavailable/invalid character rows fail without changing output. No sanitizer errors were reported.

The stubs validate call arguments and ownership only. Cache behavior, GX rendering, SD mounting, allocation-failure injection and hardware execution remain outside this test. The report is saved in `wii-assets-verification.json`.

## Original SPR texture frames

`vertrix_wii_sprite_frame_load` loads an individual original SPR frame directly from VF, applies the recovered original binary-alpha and channel-order processing, and initializes a Wii texture. The output retains the original frame count and all ten decoded descriptor words for layout and anchors. Cleanup releases texture ownership and zeros the descriptor. Failure preserves output.

The connected sanitizer test now covers all 20 SPR files and 216 frames, verifies descriptor propagation and 355,648 padded texture pixels, and checks ready-output rejection plus out-of-range-frame rejection. Combined block and SPR runs upload and release 1,224 texture objects. GPU calls remain host stubs. PowerPC compilation and formatting checks pass. Actual Wii rendering and recovery of the complete object/layout lifecycle remain unfinished.

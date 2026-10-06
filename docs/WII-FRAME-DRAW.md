# Drawing recovered frames on Wii

`vertrix_wii_frame_draw` draws an uploaded CPU frame as a textured quad at a
caller-selected destination rectangle. Texture coordinates exclude tile padding.
The caller initializes GX, the viewport and an orthographic projection in
destination pixel coordinates. The function configures texture, vertex, TEV,
depth, blend, alpha and culling state; it does not restore prior state.

Completed frames are drawn opaque. Recovered RGB effects can leave zero alpha,
so blending or alpha rejection here would hide valid original frame pixels.
Invalid textures, dimensions or texture-coordinate limits issue no GX commands.

`make wii-frame-draw` builds the drawing and upload modules against the actual
libogc headers with the PowerPC compiler. `tools/verify_wii_frame_draw.py`
records GX calls for 2,048 rectangles and checks state, corner order and texture
coordinates. Another 4,096 invalid cases reject without issuing commands.
The report is `wii-frame-draw-verification.json`.

These checks validate command construction and compilation. They do not execute
the Wii GPU. Video initialization, projection setup, frame-buffer copying,
swapping, vertical synchronization and the complete game loop remain to be
integrated and tested. This component is not a playable game build.

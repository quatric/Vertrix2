# Presenting the original frame

`wii_frame_present.c` connects the completed 640x480 CPU-frame texture to Wii
display-buffer presentation. It sets an orthographic projection and identity
model matrix, fills the configured viewport, draws the opaque frame, copies it
to the next XFB, waits for GPU completion, schedules that buffer, flushes VIDEO
and waits for vertical synchronization. It alternates two supplied XFBs. Field
rendering uses the upcoming field's viewport jitter; other modes use a normal
viewport. This module does not advance the recovered gameplay clock.

The application must initialize GX and VIDEO and configure display-copy
dimensions, scaling and filtering for the supplied mode. Both independent XFBs
must have sufficient storage and remain live, as must the borrowed mode. The
first presentation uses the first supplied XFB. This fills the configured
viewport; final aspect-ratio policy still belongs to application video setup.
Invalid inputs preserve the presenter and issue no graphics or video commands.

`make wii-frame-present` builds the presentation, drawing and upload archive
with the PowerPC compiler and actual libogc headers. The recorded host verifier
checks 2,048 consecutive presentations across normal and field viewports,
including projection arguments, buffer alternation and copy/completion/display/
flush/vsync ordering. It also checks 8,192 invalid-input preservation cases.
See `wii-frame-present-verification.json`.

Host recording does not execute a GPU or video hardware. Framebuffer allocation,
video initialization, display-copy configuration, hardware timing and the full
game application remain unverified. The port is still not playable.

# Wii video initialization

`vertrix_wii_video_init` initializes VIDEO, copies the console's preferred mode,
allocates two XFBs and a 32-byte-aligned 256 KiB GX FIFO, and connects the XFBs
to the frame presenter. It clears both display buffers to black and initially
displays the second buffer, leaving the first available for the first frame.
It initializes GX display-copy dimensions and scaling, the mode's sample and
vertical filters, field mode, pixel format and normal copy gamma.

Each XFB reserves 1,024 rows so display-copy Y-scale rounding does not overrun
an allocation sized only for the nominal mode height. This costs extra memory.
The initializer accepts preferred modes up to 640 pixels wide, 528 EFB rows and
576 nominal XFB rows. VIDEO/GX own references to the context and its allocations
after initialization: initialize zero storage once, keep it at a stable address,
and retain it until application exit. Shutdown and mode changes are not provided.
Allocation failures free temporary allocations and leave output untouched before
GX initialization or display configuration; VIDEO discovery may already occur.

`make wii-video` builds the video, presentation, drawing and upload archive with
the PowerPC compiler and actual libogc headers. `tools/verify_wii_video.py` uses
recorded host stubs for 64 synthetic mode configurations and 192 allocation
failures. It verifies mode propagation, buffer reservation, allocation rollback,
FIFO clearing, initial buffer separation, returned copy height, filters, field
mode and pixel format. The synthetic modes test parameter handling and do not
establish which modes real consoles select. See `wii-video-verification.json`.

No Wii GPU or video hardware has been executed in these checks. Actual display
output, regional timing, aspect-ratio policy, performance and complete gameplay
integration still require verification. This archive is not a playable game.

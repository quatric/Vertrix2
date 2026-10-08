# Title and menu frame handler

`title_frame.c` recovers `0x41c7b0`, the idle handler that runs one frame of the title and menu
screens (the handler `0x418840` stores at form `+0xbc`). It is pure orchestration: the first frame
runs the setup `0x41d640`; every frame runs the stage routines (`0x41d670`, `0x41dec0`, `0x419490`,
the scene lists `0x471a70`, `0x471a60`, `0x471a20`, `0x471a40`, `0x471a50`, the draw surface
`0x4854a0`, `0x485520`, `0x486d00`, `0x486da0`, `0x487020`, ...); the transition modes at
`0x532b48` and `0x532b44` pick the screen slot `0x532a50`; and when that differs from the
requested screen `0x532a98` it installs the next handler (`0x41c9e0` or `0x41cbb0`).

The stages stay unrecovered callees reached through the call boundary. The static flags are read
through the globals hook and stored through the boundary store.
`tools/verify_title_frame.py` runs the complete original 4,096 times with every callee stubbed,
over random flag, screen and transition states, and compares the order of every call and store
and the registers each callee reads. Evidence: `title-frame-verification.json`.
`source/native_dispatch.c` lets the dispatcher run the port in place of the lifted copy.

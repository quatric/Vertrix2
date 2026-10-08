# Game screen frame handler

`game_frame.c` recovers `0x41b820`, the idle handler that runs one frame of the game screens, the
counterpart of the title handler (`TITLE-FRAME.md`) with three scene lists
(`0x54671c`, `0x546744`, `0x546730`; see `OBJECT-BROADCAST.md`).

Each frame runs the stage routines, draws the three lists into the back buffer when `0x4854a0`
reports it ready, and applies the screen transition mode. When the screen slot `0x532a4c`
differs from the requested screen `0x532a98` it performs the transition for the screen it is
leaving: most clear the scene list (`0x4719e0`) and run one screen routine; the level screens
(`0x4f7b54`, `0x4f7b58`, `0x4f7b60`, `0x4f7b64`, `0x4f7ba8`) copy the four settings at
`0x532b54..0x532b60` to `0x532bbc..0x532bc8`, reset the play state and install the next handler
(`0x41c160`, `0x41c1d0`, `0x41c240`, `0x41c2b0`) through `0x418840`; the start screens
(`0x4f7b70`, `0x4f7b74`) reset the play state and choose the handler from the profile count
`0x532bcc`. The screens are tested in the original's order because the table may hold the same
number in several slots.

Everything else stays an unrecovered callee reached through the call boundary.
`tools/verify_game_frame.py` runs the complete original 4,096 times with every callee stubbed
over random flags, screen tables and current and requested screens (494 distinct call sequences,
every callee reached) and compares the order of every call with the registers it reads, the
stores between calls, the final values, preserved registers and stack cleanup. Evidence:
`game-frame-verification.json`. `source/native_dispatch.c` lets the dispatcher run it.

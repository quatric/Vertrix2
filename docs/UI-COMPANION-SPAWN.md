# Companion spawner (0x471100)

`vertrix_ui_companion_spawn` in `source/ui_companion_actor.c` reproduces
the companion actor factory: when the configuration dword at index * 4 +
0x5cc is one, a 0x15c actor is allocated (0x4ca000 through the calls
boundary, 0x4abd70 builds it), placed (0x4710d0: sign-extended x/y,
resource 0x5449fc, the frame), styled with the record at index * 12
(0x4123d0), flagged at +0x110 when the index matches the sentinel and
appended to the list 0x54671c (0x4b5e70). Disabled entries return zero
without allocating. The allocator receives the live index/frame/index
registers and the append receives the live actor/sentinel, exactly as the
original threads them.

Verification (`tools/verify_ui_companion_spawn.py`, evidence
`docs/ui-companion-spawn-verification.json`): 512 complete original
executions pass with the allocator and the append stubbed and logged;
the returned actor, both call logs and every pool object compare.

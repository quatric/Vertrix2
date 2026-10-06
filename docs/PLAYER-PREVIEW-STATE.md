# Preview selection and player mode

`player_preview_state.c` recovers original `0x42b070`, `0x42b0e0`, `0x42b0f0`
and `0x42b110`. The selected frame comes from the last active companion slot:
count at `0x188`, handle at `0x158 + count * 4`, then actor frame at `0xb8`.
Native counts are bounded to 1..3 and identity resolution remains explicit.

Mode is the DWORD at `0x180`. Setting mode to one from zero sets flag `0x184`
to one; leaving mode one clears that flag. Other transitions retain the flag.
The toggle computes unsigned `1 - flag`, preserving original wrap behavior for
all DWORD values rather than treating the storage as a boolean.

The verifier executes all four complete original helpers without hooks in
4,096 cases each. It compares entire player storage for mode assignment and
toggle, and the original selected frame for each valid preview count. It also
checks 12,288 insufficient-storage failures for destination/output preservation.
The helpers still need connection to the surrounding player state machine and
game loop. These checks do not establish a playable Wii game.

`vertrix_player_preview_frames` additionally recovers complete `0x42b090`
with its `0x425de0` initialization: seven DWORDs become `0xffffffff`, then
active companion frame IDs replace the leading entries in slot order. Native
counts0..3 are supported; zero previews need no resolver. Output is a native
uint32 array. The resolver must keep counts and handles stable during the
read. Staging preserves all output entries if a later actor cannot resolve.

The extended verifier executes the complete original snapshot in 4,096 cases,
including zero previews and all three active counts. All nine destination
entries compare, including two untouched trailing entries. Insufficient
capacity, invalid count and missing final actor preserve output in 12,288
cases. Together the verifier covers 20,480 complete original helper calls.

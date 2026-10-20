# 0x4df320 (printf's driver): the format is text in a pool object (+0x10), the argument pointer is
# another's first field; the stubbed spec parser (0x4df6c8) answers where the spec's letter is, so
# plain characters, %n, %s, %S, other letters and the end come up. The stubbed formatter
# (0x4dfb24) cannot lay out its counts in the frame, so the frame starts zeroed: the oracle checks
# the walk, the calls and %n (the output procedure is vsprintf's, 0x4cd090, stubbed); the layout is checked against the lifted copy in a game run.
export VERTRIX_FRAME_BYTES="0"
export VERTRIX_RETURN_EDX="0x4dfb24:0x10"
export VERTRIX_HANDLE_REGISTERS=ebx
export VERTRIX_EXTRA_CALLEES="0x4cd090:0"
export VERTRIX_CODE_TARGET=0x4cd090
export VERTRIX_REGISTER_CHOICES="edx:0x806010,0x807010,0x806018"
export VERTRIX_FIELD_CHOICES="0x0:4:0x806020,0x807024;0x10:4:0x62732561,0x53256e25,0x6e256e25,0x25782578;0x14:4:0x5a6e2578,0,0x25252525;0x18:4:0,0x41;0x20:4:0x806030,0x808030;0x24:4:0x807034,0x809038"
export VERTRIX_RETURN_CHOICES="0x4df6c8:0x806011,0x806012,0x806013,0x806015,0x806016,0x807011,0x807013,0x807015,0x806018,0x807019;0x4dfb24:0x806010,0x807014"

# 0x4c9b10 (sqrt): the high dword is negative, 0 or positive, so the domain error, the value kept
# and the software root all run (the coprocessor flag stays 0 under the verifier, as in the lifted
# runtime); the value the domain error is handed (edx of 0x4dad2e) is logged with the call.
export VERTRIX_CALL_BYTES="0x4dad2e:edx:8"
export VERTRIX_REGISTER_CHOICES="edx:0,0,0x80000000,0xbff00000,0x3ff00000,0x40100000,0x7ff00000"

# 0x4ec970 (printf's %e, %f and %g): the conversion's parameter block (edx of 0x4eccb9) is logged
# with the call, so the mode, trimming, letter and precision it is handed are compared; the letter
# (+0x15) is each of e, E, f, g and G, the flags (+0x1e) any of #, space and +, and the precision
# (+8) 0, -1 or a few digits.
export VERTRIX_CALL_BYTES="0x4eccb9:edx:0x14"
export VERTRIX_FIELD_CHOICES="0x15:1:0x65,0x45,0x66,0x67,0x47;0x1e:1:0,1,2,4,6,7;0x8:4:0,0xffffffff,3,10"

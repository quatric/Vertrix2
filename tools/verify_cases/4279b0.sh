# 0x4279b0 (the AI's judgement whether to answer now): the two boards' cells it copies into its
# frame for 0x428110 are compared with the call (VERTRIX_CALL_BYTES), and the frame starts with
# scores on both sides of 1 and of the sign bit, as 0x4288d0 would leave the first one.
export VERTRIX_CALL_BYTES="0x428110:edx:0x41,ebx:0x41"
export VERTRIX_FRAME_BYTES="0,1,2,0x7f,0x80,0xff"
export N=256

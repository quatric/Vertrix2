# 0x474910 (a hue, saturation and value's colour): red's output and both stdcall outputs are pool
# objects; the helpers' singles come back as 0 or not, and the sector (0x4d67b2) covers 0 to 5 and
# beyond; the hue (0x4d74a6) is sometimes 360. Every working global the original stores must be
# stored.
export VERTRIX_REGISTER_CHOICES="ecx:0x806000,0x807000"
export VERTRIX_ARGUMENT_CHOICES="0:0x806100,0x807100;1:0x806200,0x808200"
export VERTRIX_RETURN_CHOICES="0x4eb606:0,0x3f000000,0x43b40000,0x3f800000;0x4d67b2:0,1,2,3,4,5,6,0x10005;0x4d74a6:0,0x43b40000,0x3f800000,0x42f00000"
export VERTRIX_CHECK_MISSING_STORES=1
export N=256

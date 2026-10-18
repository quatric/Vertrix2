# 0x474560 (hue, saturation and value): the hue and both stdcall outputs are pool objects; the
# helpers' singles come back as 0 or not so black, grey and coloured inputs are all reached.
export VERTRIX_REGISTER_CHOICES="ecx:0x806000,0x807000"
export VERTRIX_ARGUMENT_CHOICES="0:0x806100,0x807100;1:0x806200,0x808200"
export VERTRIX_RETURN_CHOICES="0x4eb606:0,0x3f000000,0x3f800000,0xbf000000;0x4d81fe:0,0x3f000000;0x4eb526:0,1,0x3f800000"
export N=256
# Every working global the original stores must be stored.
export VERTRIX_CHECK_MISSING_STORES=1

# 0x423960 (a screen wipe frame): the wipe started or not, its last count 480 or not, the list's
# entry (0x4b5eb0) 0 or a pool object whose count (+0x58) is 0, small, near or at 480, the
# surfaces and sources pool objects, and the input done (0x472360 = 1) or not. Every global the
# original stores must be stored.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_FIELD_CHOICES="0x58:4:0,1,3,7,0x1dd,0x1e0"
export VERTRIX_GLOBAL_CHOICES="0x5405fc:1:0,1;0x540600:4:0x1e0,0x1e0,3,0;0x558c7c:4:0x806000,0x807000;0x558c80:4:0x806000,0x808000;0x558c88:4:0x807000,0x809000"
export VERTRIX_RETURN_CHOICES="0x4b5eb0:0,0x806000,0x807000;0x472360:0,1,2"
export VERTRIX_CHECK_MISSING_STORES=1
export N=128

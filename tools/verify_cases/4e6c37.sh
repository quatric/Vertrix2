# 0x4e6c37 (terminate()): the thread data procedure (0x507c9c) is 0x4e04ec, whose stub returns the
# offset of one of two pool objects (0x5c5c54 = 0), and the object's terminate handler (+0x14) is
# none or a routine the verifier stubs, so the call through it runs. The current exception
# (0x4e0f8b) is a pool object whose text (+0xc) is often 0, which reaches exit(1): the message
# flag (0x5c7b90) and exit hook (0x507ce4) set or not, the message hook (0x507cd8) a stub, and
# the two buffers it frees (0x5c7b94, 0x5c7b98) there or not. Every global it clears must be.
export VERTRIX_GLOBAL_CHOICES="0x507c9c:4:0x4e04ec;0x5c5c54:4:0;0x5c7b90:4:0,1;0x507ce4:4:0,0x4e6250;0x507cd8:4:0x4e04f4;0x5c7b94:4:0,0x806800;0x5c7b98:4:0,0x807800"
export VERTRIX_RETURN_CHOICES="0x4e04ec:0x806000,0x807000;0x4e0f8b:0x806000,0x807000"
export VERTRIX_FIELD_CHOICES="0x14:4:0,0,0x4e6250;0xc:4:0,0,0x512eac"
export VERTRIX_CHECK_MISSING_STORES=1

# 0x4dfac0 (printf's wide string): the output procedure (ecx) is the verifier's stubbed leaf
# (0x700404), so its calls are logged and compared. wctomb (0x4e62e0) answers -1, 0 or a few bytes,
# and the characters left in the state (+0x28) are none, a few or more than a character's bytes,
# so the byte loop, the skip and the cut all run.
export VERTRIX_HANDLE_REGISTERS=ebx
export VERTRIX_REGISTER_CHOICES="ecx:0x700404"
export VERTRIX_RETURN_CHOICES="0x4e62e0:0xffffffff,0,1,1,2,3,4"
export VERTRIX_FIELD_CHOICES="0x28:4:0,1,2,3,7,0x20,0xffffffff"

# 0x4e63b0 (_ui64toa): the original runs the 64-bit divide (0x4e88bf) itself, since the port reads
# the remainder it leaves in ecx:ebx; the value is a pool object's first two words (small, large or
# with a high half). The radix is 4 or more: the original gathers the digits from esp+1 up to its
# own radix at esp+0x24, so a value of more than 35 digits (only in radix 2 or 3) overwrites the
# radix with a digit and goes on dividing by that (printf asks for 8, 10 and 16 only).
export VERTRIX_RUN_CALLEES="0x4e88bf"
export VERTRIX_HANDLE_REGISTERS=eax,edx
export VERTRIX_REGISTER_CHOICES="ebx:4,8,10,10,16,36"
export VERTRIX_FIELD_CHOICES="0x0:4:0,1,9,10,35,0x7fffffff,0xffffffff,0x12345678;0x4:4:0,0,0,1,0xffffffff,0x80000000"

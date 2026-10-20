# 0x4eccb9 (a value's digits): the digit writer 0x4ecf33 is the routine's own code, which the
# original runs (the port has it in C). The value (eax) and the parameters (edx) are pool objects:
# the value's word is a zero, small, near 10^8, near 10^16 or large exponent of either sign, the
# parameters' precision (+0) and decimals (+4) small, zero or negative and their mode (+8) each of
# E, F and G with the long and fixed bits. The class (0x4edf7f) is each of zero, number, NaN and
# infinity, and the integers 0x4ee025 answers have every digit count up to eight, some of them
# leading or trailing nines and zeros so the rounding carries.
export VERTRIX_RUN_CALLEES="0x4ecf33"
export VERTRIX_HANDLE_REGISTERS=eax,edx,ebx
export VERTRIX_RETURN_CHOICES="0x4edf7f:0,1,1,1,1,1,2,3,4;0x4ee025:0,1,5,99999999,12345678,50000000,99999995,10000000,7,49999999,90000000"
export VERTRIX_FIELD_CHOICES="0x8:2:0,1,0x4008,0x4105,0x3ffe,0x3fff,0x4005,0x4019,0x401a,0x4034,0x4035,0x4100,0x3f00,0x8000,0xbfff,0xc019;0x0:4:0,1,3,6,10,17,0xffffffff;0x4:4:0,1,2,0xffffffff,0xfffffffd;0x6:1:0,0x80"

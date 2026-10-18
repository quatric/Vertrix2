# 0x4ea540 (strtol/strtoul): the string a pool object led by blanks, signs and "0x" prefixes, the
# end pointer a pool object or 0, every base case and the signed flag; the digit values from
# 0x4ea6b0 include ones at and above each base so the loop ends and overflows are reached.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_REGISTER_CHOICES="edx:0,0x807100;ebx:0,0,2,8,10,16,16,36,1,37;ecx:0,1,1,2"
export VERTRIX_FIELD_CHOICES="0x0:1:0x20,0x2b,0x2d,0x30,0x31;0x1:1:0x78,0x58,0x30,0x2d,0x37;0x2:1:0x30,0x78,0x41"
export VERTRIX_RETURN_CHOICES="0x4ea6b0:0,1,7,9,15,35,0xffffffff,0x10,0xa,0x24,0x40"
export N=256
# The base 10 and 16 digit limits also drawn small so a value equal to its limit is reached.
export VERTRIX_GLOBAL_CHOICES="0x50b23c:4:0x19999999,0,1,7;0x50b254:4:0xfffffff,1,7,15"

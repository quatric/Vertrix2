# 0x4ed2b5 (a number's exponent form): the format a pool object with the precision, point, flags,
# letter and exponent digits drawn around their edges; the digits at 0x806f00 and a count up to 9;
# exponents on both sides of 10, 100 and 1000; the buffer at 0x807f00.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_FIELD_CHOICES="0x0:4:0,1,2,6,0xffffffff;0x4:4:0,1,3,9,0xffffffff,0xfffffffc;0x8:4:0,4,8,0x10,0x14,0x1c;0xc:4:0,0x65,0x45;0x10:4:0,1,2,3,4,7,0xffffffff"
export VERTRIX_REGISTER_CHOICES="edx:0x806f00;ebx:0,1,3,9;ecx:0,7,9,10,99,100,999,1000,12345,0xfffffff9,0xffffff9c,0x80000000"
export VERTRIX_ARGUMENT_CHOICES="0:0x807f00"
export N=256

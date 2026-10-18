# 0x4cd7dc: the record a pool object; 0x4e0bed returns 0 or a pool object that catches by type
# (+0 = 0, or not) whose type record (+4) sits at +0x10 of an object, its kind byte covering the
# reported kinds (1, 5, 14), the table's others and those above 16; the record's current pointer
# (+4) equal to its end (+8) or not.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_RETURN_CHOICES="0x4e0bed:0,0x806000,0x807000,0x808000"
export VERTRIX_FIELD_CHOICES="0x0:4:0,0,0,1;0x4:4:0x806010,0x807010,0x808010;0x8:4:0x806010,0x809000;0x10:1:0,1,2,5,6,14,15,16,17,18,0xff"
export N=256

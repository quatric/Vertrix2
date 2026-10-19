# 0x4e843c (the thread data grown): the threads' list (0x5c8aa0) is a pool object whose next (+0)
# is none or another, each with the id GetCurrentThreadId (0x4f1ba0) answers or another (+4), its
# data (+8) a pool object and owned or not (+0xc); the data's size (+0xf0) is a few bytes, and
# realloc and calloc answer a pool object or nothing.
export VERTRIX_GLOBAL_CHOICES="0x5c8aa0:4:0x806000;0x509768:4:0x100,0x104"
export VERTRIX_RETURN_CHOICES="0x4f1ba0:7,7,9;0x4ec0e0:0x808000,0x808000,0;0x4ec160:0x809000,0x809000,0"
export VERTRIX_FIELD_CHOICES="0x0:4:0,0x807000;0x4:4:7,9;0x8:4:0x807000,0x808000;0xc:4:0,1;0xf0:4:0,5,0x20,0x41"

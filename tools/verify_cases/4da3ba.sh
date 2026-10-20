# 0x4da3ba (the C++ throw): the throw's state is what the stubbed preparation (0x4e38ff) would have
# left in the frame, so the frame starts as bytes of 0 to 6: whether it is raised (+0x16), the
# action (+0xa) and the options (+0xb) take every value the routine tells apart. The current
# exception (0x4e0f8b) and the catch found (0x4e0c56) are pool objects.
export VERTRIX_FRAME_BYTES="0,0,0,1,2,3,4,5,6"
export VERTRIX_RETURN_CHOICES="0x4e0f8b:0x806000,0x807000;0x4e0c56:0x808000,0x809000"

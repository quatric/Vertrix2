# 0x4c8500 (fill_inverse_cmap): the colormap's rows and the histogram's planes are pool objects,
# the colour count 1 to 256 (libjpeg's two-pass limit; more overruns the frame's lists) and the
# cell inside the 32 x 64 x 32 histogram.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_REGISTER_CHOICES="edx:0,3,4,13,31;ebx:0,7,8,40,63;ecx:0,3,4,17,31"
export VERTRIX_FIELD_CHOICES="0x0:4:0x806000,0x807000,0x808000;0x4:4:0x806000,0x807000,0x808000;0x8:4:0x806000,0x807000,0x808000;0x10:4:0x806000,0x807000;0x18:4:0x806000,0x807000;0x84:4:1,2,7,32,200,256;0x88:4:0x806000,0x807000;0x1cc:4:0x806000,0x807000"
export N=256

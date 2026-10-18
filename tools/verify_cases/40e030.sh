# 0x40e030 (the mixer's instrument tick): the channel a pool object, its instrument 0 or a pool
# object; key on or released, both envelopes' flags (on, sustain, loop), counts, sustain and loop
# points, the points reached or not, the fadeout full or not, panning on both sides, every vibrato
# type and the sweep on or off.
export VERTRIX_HANDLE_REGISTERS=eax
export VERTRIX_FIELD_CHOICES="0x0:1:0,1;0x34:4:0,0x806000,0x807000,0x808000;0x88:4:0,1,2,3;0x98:4:0,1,2,3;0x80:4:0,1,5,100;0x90:4:0,1,5,100;0x84:4:0,0x2010,0x4001,0x3f80;0x82:1:0,1,2,3,4;0xbc:1:0,1,3,5,7;0xb8:1:1,2,4;0xb9:1:0,1,2;0xba:1:0,1;0xbb:1:1,2,3;0xf4:1:0,1,3,5,7;0xf0:1:1,2,4;0xf1:1:0,1,2;0xf2:1:0,1;0xf3:1:1,2,3;0x78:4:0x7fff,0x4000,5;0x7c:4:0,0x100,10;0x1c:4:0,0x80,0xff,0x40;0xa8:4:0,0x40;0xa4:4:0,0x1000"
export N=256

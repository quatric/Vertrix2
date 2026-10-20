# 0x4d2710 (a window centred): the rectangles are what the stubbed GetWindowRect, GetClientRect and
# SystemParametersInfo would have stored, so the frame starts as bytes from a few values (edges
# below, inside and past one another, odd and even); the style (0x4cccc0) is a child's or not, the
# parent or owner (0x4f19c8, 0x4f1a04) and the window the owner names (0x4f1a94) none or one, and
# GetWindowLong (0x4f19f0) visible or hidden, minimized or not.
export VERTRIX_FRAME_BYTES="0,0,1,3,0x10,0x7f,0x80,0xff"
export VERTRIX_RETURN_CHOICES="0x4cccc0:0,0x40000000,0x10000000;0x4f19c8:0,0x1234;0x4f1a04:0,0x1234;0x4f1a94:0,0,0x5678;0x4f19f0:0,0x10000000,0x30000000,0x10000000"

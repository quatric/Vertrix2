# 0x43e320 (the actors' projection): the owner a pool object whose 450 slots (+0x15c) hold 0 or one
# of three pool objects, so each actor's last projection is its own; the scale compare goes both
# ways, 0x4ad720 says fits or not, and the distance (+0x58) is 200 (no depth), 5 or 12 (level 0)
# or more, with positions and levels on both sides of 0. Every global the original stores must be
# stored.
export VERTRIX_HANDLE_REGISTERS=eax
slots=""
for i in {0..449}; do
    slots="$slots;$(printf '0x%x' $((0x15c + 4 * i))):4:0,0,0x806000,0x807000,0x808000"
done
export VERTRIX_FIELD_CHOICES="0x58:4:200,200,0,5,12,100,199,0xffffff38,13;0x8:2:0,5,0xfff0,0x7fff;0xa:2:0,7,0x8000$slots"
unset slots i
export VERTRIX_RETURN_CHOICES="0x4ad720:0,1"
export VERTRIX_CHECK_MISSING_STORES=1
export N=16

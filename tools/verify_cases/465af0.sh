# 0x465af0 (the play screen's panels): the title mode 0 or not, the panel mode 0, 1 or 2, the bar
# counts small (odd and even) and the allocator failing or not. The constructors return one of 64
# addresses in the pool's pages, so most actors are their own object and an earlier actor's
# fields are not hidden by a later one's (the fourth panel's frame, 0x465fb1).
export VERTRIX_GLOBAL_CHOICES="0x532a84:4:0,1;0x532a8c:4:0,1,2;0x4f86d4:4:0,1,4,5;0x4f870c:4:0,1,4,5"
actors=""
for i in {0..63}; do
    actors="$actors,$(printf '0x%x' $((0x806000 + 0x100 * i)))"
done
export VERTRIX_RETURN_CHOICES="0x4ca000:0,0x806000,0x807000;0x4b5400:${actors#,};0x4b6350:${actors#,};0x4abd70:${actors#,}"
unset actors i
export N=16

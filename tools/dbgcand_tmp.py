board = bytes.fromhex('00030302030302ff01ffff000604060503050301ff00060205040505070303ff000206020402070403ffff0000050501070301ff0005030500ff03060204020503')
shapes = [
    (7, 7, [-1, 1, -2, 0, 2, -1, 1], [-1, -1, 0, 0, 0, 1, 1]),
    (5, 6, [0, -1, 0, 1, 0], [-1, 0, 0, 0, 1]),
    (5, 5, [-1, 1, 0, -1, 1], [-1, -1, 0, 1, 1]),
    (5, 4, [-1, 0, 1, 0, -1], [-2, -1, 0, 1, 2]),
    (5, 4, [-2, -1, 0, 1, 2], [1, 0, -1, 0, 1]),
    (5, 4, [1, 0, -1, 0, 1], [-2, -1, 0, 1, 2]),
    (5, 4, [-2, -1, 0, 1, 2], [-1, 0, 1, 0, -1]),
    (5, 3, [-2, -1, 0, 1, 2], [0, 0, 0, 0, 0]),
    (4, 2, [0, -1, 1, 0], [-1, 0, 0, 1]),
]
def cell(x, y):
    return board[x * 13 + y]
orig_extra = {4, 18}
for si, (n, w, dx, dy) in enumerate(shapes):
    for x in range(5):
        for y in range(13):
            members = [(x + dx[i], y + dy[i]) for i in range(n)]
            if not all(0 <= a < 5 and 0 <= b < 13 for a, b in members):
                continue
            if not ({m[0] * 13 + m[1] for m in members} >= orig_extra):
                continue
            vals = {cell(*m) for m in members}
            print('shape', si, 'anchor', (x, y), 'vals', vals)

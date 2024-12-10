def is_in_bounds(data, pos):
    return 0 <= pos[0] < len(data[0]) and 0 <= pos[1] < len(data)


def find_trails(data, x, y):
    queue = [(x, y)]
    targets = []
    while len(queue) != 0:
        x, y = queue.pop()
        if data[y][x] == 9:
            targets.append((x, y))
            continue
        for pos in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
            if is_in_bounds(data, pos) and data[pos[1]][pos[0]] == data[y][x] + 1:
                queue.append(pos)
    return targets


with open("../inputs/day10.txt") as f:
    data = [[int(x) for x in list(line.replace("\n", ""))] for line in f.readlines()]
    total_trails = []
    sum = 0
    for y, row in enumerate(data):
        for x, val in enumerate(row):
            if val == 0:
                trails = find_trails(data, x, y)
                sum+=len(set(trails))
                total_trails.extend(trails)
    print(sum)
    print(len(total_trails))
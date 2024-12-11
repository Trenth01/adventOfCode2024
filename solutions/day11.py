from collections import Counter
import math


def apply_rules(x, count):
    str_x = str(x)
    if x == 0:
        return [{1: count}]
    elif len(str_x) % 2 == 0:
        x_front = str_x[:len(str_x)//2]
        x_back = str_x[len(str_x)//2:]
        return [{math.floor(int(x_front)): count}, {math.floor(int(x_back)): count}]
    else:
        return [{x * 2024: count}]


def blink(frequency_map):
    output = Counter({})
    [[output.update(y) for y in apply_rules(x, frequency_map[x])] for x in frequency_map]
    return output


with open("../inputs/day11.txt") as file:
    freq_map = Counter([int(x) for x in file.read().replace("\n", "").split(" ")])
    for i in range(0, 500):
        freq_map = blink(freq_map)
    print(sum(
        freq_map[x]
        for x in freq_map
    ))
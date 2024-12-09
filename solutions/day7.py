def recursive_death_bullshit(target, factors):
    if len(factors) == 1:
        return factors[0] == target

    return (
            recursive_death_bullshit(target, [factors[0] + factors[1]] + factors[2:]) or
            recursive_death_bullshit(target, [factors[0] * factors[1]] + factors[2:]) or
            recursive_death_bullshit(target, [int(str(factors[0]) + str(factors[1]))] + factors[2:])
    )

with open("../inputs/day7.txt") as file:
    print(sum(
        int(line[0])
        for line in [line.replace(":", "").replace("\n", "").split(" ") for line in file.readlines()]
        if recursive_death_bullshit(int(line[0]), list(map(int, line[1:])))
    ))



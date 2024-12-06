//
// Created by Trent on 12/1/2024.
//
#pragma once
#include <set>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class GuardNotFoundException final : public std::exception {
public:
    char * what () {
        return "GuardNotFound";
    }
};

class InfLoopException final : public std::exception {
public:
    char * what () {
        return "inf loop";
    }
};

inline vector <char> GUARD_DIRECTIONS = {'^', '>', 'v', '<'} ;
inline vector <tuple<int, int>> dx_dy = {{0, -1}, {1,0}, {0, 1}, {-1, 0}};
constexpr char barrier = '#';

inline tuple<int, int> find_guard_pos(const vector<string>& map) {
    for(int y = 0; y < map.size(); y++) {
        for(int x = 0; x < map[y].size(); x++) {
            if(ranges::find(GUARD_DIRECTIONS, map[y][x]) != GUARD_DIRECTIONS.end()) {
                return make_tuple(x, y);
            }
        }
    }
    throw GuardNotFoundException();
}

inline set<tuple<int, int>> find_guard_path(const vector<string>& map, const int &start_x, const int &start_y) {
    char direction = map[start_y][start_x];
    int x = start_x, y = start_y, step_counter = 0;
    set<tuple<int, int>> visited;
    set<tuple<char, int, int>> contacts;
    while (x == clamp(x, 1, static_cast<int>(map[0].size())-2) && y == clamp(y, 1, static_cast<int>(map.size())-2)) {
        const int index = ranges::find(GUARD_DIRECTIONS, direction) - GUARD_DIRECTIONS.begin();
        if (auto [dx, dy] = dx_dy[index]; map[y+dy][x+dx] == barrier) {
            auto contact = make_tuple(direction, x, y);
            if (contacts.contains(contact)) {
                throw InfLoopException();
            }
            contacts.insert(contact);
            direction = GUARD_DIRECTIONS[(index + 1) % 4];
        }else{
            visited.insert(make_tuple(x, y));
            x += dx, y += dy;
        }
    }
    visited.insert(make_tuple(x, y));
    return visited;
}

inline int find_inf_loops(set<tuple<int, int>> paths, const vector<string>& map, const int &start_x, const int &start_y) {
    const auto first_step = make_tuple(start_x, start_y);
    paths.erase(first_step);
    int counter = 0;
    for (auto path : paths) {
        vector<string> perturbed_map = map;
        perturbed_map[get<1>(path)][get<0>(path)] = barrier;
        try {
            find_guard_path(perturbed_map, start_x, start_y);
        }catch(InfLoopException) {
            counter++;
        }
    }
    return counter;
}

inline tuple<int, int> day6(const vector<string>& map) {
    auto [start_x, start_y] = find_guard_pos(map);
    const auto path1 = find_guard_path(map, start_x, start_y);
    int part1 = path1.size();
    int part2 = find_inf_loops(path1, map, start_x, start_y);
    return {part1, part2};
}

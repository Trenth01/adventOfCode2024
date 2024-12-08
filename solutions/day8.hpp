//
// Created by Trent on 12/1/2024.
//
#pragma once
#include <set>
#include <map>
#include <tuple>
#include <string>
#include <vector>
using namespace std;


inline map<char, set<tuple<int,int>>> find_frequencies(const vector<string>& input_map) {
    map<char, set<tuple<int,int>>> frequency_map;
    for(int y = 0; y < input_map.size(); y++) {
        for(int x = 0; x < input_map[y].size(); x++) {
            if(iswalnum(input_map[y][x])){
                auto coords = make_tuple(x, y);
                if (frequency_map.contains(input_map[y][x])) {
                    frequency_map[input_map[y][x]].insert(coords);
                }else{
                    frequency_map[input_map[y][x]] = {coords};
                }
            }
        }
    }
    return frequency_map;
}


inline vector<tuple<int, int>> find_distances(const tuple<int, int> &cords, const set<tuple<int, int>> &coords_set) {
    vector<tuple<int, int>> distances;
    for (tuple other_cords: coords_set) {
        int x_distance = get<0>(cords) - get<0>(other_cords);
        int y_distance = get <1>(cords) - get <1>(other_cords);
        if (x_distance != 0 && y_distance != 0) {
            distances.emplace_back(x_distance, y_distance);
        }
    }
    return distances;
}

inline bool is_frequency(const tuple<int, int> &cords, const set<tuple<int, int>> &coords_set, const tuple<int, int> &distance) {
    int x = get<0>(cords), y = get<1>(cords), dx=get<0>(distance), dy=get<1>(distance);
    auto check_coord = make_tuple(x+dx, y+dy);
    return coords_set.contains(check_coord);
}

inline bool is_in_bounds(const tuple<int, int> &cords, const tuple<int, int> &distance, const vector<string>& input_map) {
    int x = get<0>(cords), y = get<1>(cords), dx=get<0>(distance), dy=get<1>(distance), max_x = input_map[0].size(), max_y = input_map.size();
    return x+dx < max_x && y+dy < max_y && x+dx >= 0 && y+dy >= 0;
}

inline tuple<int, int> day8(const vector<string>& input_map) {
    set<tuple<int, int>> part1_antinodes;
    set<tuple<int, int>> part2_antinodes;
    for (auto frequency_maps = find_frequencies(input_map); const auto&[fst, snd]: frequency_maps) {
        for (tuple coords : snd) {
            for (tuple distance: find_distances(coords, snd)) {
                int x = get<0>(coords), y = get<1>(coords), dx=get<0>(distance), dy=get<1>(distance), max_x = input_map[0].size(), max_y = input_map.size();
                if (!is_frequency(coords, snd, distance) && is_in_bounds(coords, distance, input_map)) {
                    part1_antinodes.insert(make_tuple(x+dx, y+dy));
                }
                int multiplier = 1;
                while (abs(dy) * multiplier < max_y && abs(dx) * multiplier < max_x) {
                    auto new_distance = make_tuple(dx*multiplier, dy*multiplier);
                    if (is_in_bounds(coords, new_distance, input_map)) {
                        part2_antinodes.insert(make_tuple(x+dx*multiplier, y+dy*multiplier));
                    }
                    multiplier++;
                }
                multiplier = -1;
                while (abs(dy* multiplier) < max_y && abs(dx * multiplier) < max_x) {
                    auto new_distance = make_tuple(dx*multiplier, dy*multiplier);
                    if (is_in_bounds(coords, new_distance, input_map)) {
                        part2_antinodes.insert(make_tuple(x+dx*multiplier, y+dy*multiplier));
                    }
                    multiplier--;
                }
            }
        }
    }
    return {part1_antinodes.size(), part2_antinodes.size()};
}

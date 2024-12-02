//
// Created by Trent on 12/1/2024.
//
#pragma once
using namespace std;
#include <sstream>
#include <vector>
#include <tuple>


inline int get_sign(int diff) {
    return diff/abs(diff);
}

inline bool check_safe(const int level, const int next_level, int &sign) {
    const int diff = next_level - level;
    if (diff == 0) {
        return false;
    }
    if (sign == 0) {
        sign = get_sign(diff);
    }
    if (get_sign(diff) != sign || abs(diff) > 3) {
        return false;
    }
    return true;
}

inline int part1(const vector<string>& input) {
    int count = input.size();
    for(const string& report: input) {
        istringstream ss(report);
        int level, next_level;
        int sign = 0;
        ss >> level;
        while (ss >> next_level) {
            if (!check_safe(level, next_level, sign)) {
                count--;
                break;
            }
            level = next_level;
        }
    }
    return count;
}

inline bool is_safe(const vector<int>& levels) {
    int sign = 0;
    for (size_t i = 0; i < levels.size() - 1; ++i) {
        if (!check_safe(levels[i], levels[i + 1], sign)) {
            return false;
        }
    }
    return true;
}

inline int part2(const vector<string>& input) {
    int count = 0;
    for (const string& report : input) {
        istringstream ss(report);
        vector<int> levels;
        int level;
        while (ss >> level) {
            levels.push_back(level);
        }
        if (is_safe(levels)) {
            count++;
            continue;
        }
        bool safe_with_skip = false;
        for (size_t i = 0; i < levels.size(); ++i) {
            vector<int> temp_levels = levels;
            temp_levels.erase(temp_levels.begin() + i); // Remove the level at index i
            if (is_safe(temp_levels)) {
                safe_with_skip = true;
                break;
            }
        }
        if (safe_with_skip) {
            count++;
        }
    }
    return count;
}

inline tuple<int, int> day2(const vector<string>& input) {
    return {part1(input), part2(input)};
}

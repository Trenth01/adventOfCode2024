//
// Created by Trent on 12/1/2024.
//
#pragma once
#include <regex>
#include <numeric>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

inline string filterDonts(const string& instructions) {
    const regex pattern(R"(don't\(\).*?do\(\))");
    return regex_replace(instructions, pattern, "");;
}

inline int computeRegexSum(const string& i, const regex& pattern) {
    return accumulate(sregex_iterator(i.begin(), i.end(), pattern), sregex_iterator(), 0, [](int sum, const smatch& match) {
        return sum+stoi(match[1]) * stoi(match[2]);
    });
}

inline tuple<int, int> day3(const vector<string>& input) {
    const regex multiplier(R"(mul\((\d*),(\d*)\))");

    string part1;
    for (const auto & i : input) {
        part1.append(i);
    }

    const string part2 = filterDonts(part1);

    return {computeRegexSum(part1, multiplier), computeRegexSum(part2, multiplier)};
}

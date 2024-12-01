#pragma once
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <tuple>

inline int part1(const vector<int>& leftList, const vector<int>& rightList) {
    vector<int> sortedLeft = leftList;
    vector<int> sortedRight = rightList;
    ranges::sort(sortedLeft);
    ranges::sort(sortedRight);

    int totalDiff = 0;
    for (int i = 0; i < sortedLeft.size(); i++) {
        totalDiff += abs(sortedLeft[i] - sortedRight[i]);
    }

    return totalDiff;

}

inline int part2(const vector<int>& leftList, const vector<int>& rightList) {
    int totalDiff = 0;
    unordered_map<int, int> rightMap;

    for (int num : rightList) {
        rightMap[num]++;
    }
    for (int i : leftList) {
        if (rightMap.contains(i)) {
            totalDiff += i * rightMap[i];
        }
    }
    return totalDiff;
}


inline tuple<int, int> day1(const vector<string>& input) {
    vector<int> leftList, rightList;
    for (const auto & i : input) {
        istringstream ss(i);
        int left, right;
        ss >> left >> right;
        leftList.push_back(left);
        rightList.push_back(right);
    }
    return {part1(leftList, rightList), part2(leftList, rightList)};
}
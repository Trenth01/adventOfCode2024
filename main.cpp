#include <chrono>
#include <functional>
#include <map>

#include "solutions/day1.hpp"
#include "solutions/day2.hpp"
#include "solutions/day3.hpp"
#include "solutions/day4.hpp"
#include "solutions/day5.hpp"
#include "solutions/day6.hpp"
#include "solutions/day7.hpp"
#include "solutions/day8.hpp"
//
// Created by Trent on 12/1/2024.
//

vector<string> fileInput(const string& fileName) {
    const string filePath = "../inputs/" + fileName;
    auto inputFile = ifstream(filePath);
    vector<string> lines;
    string line;

    if (!inputFile) {
        cerr << "Unable to open file" << endl;
        return lines;
    }

    while (getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
    return lines;
}

void solveDay(const int day, const function<tuple<int, int>(const vector<string>&)>& solveFunction) {
    const string inputFile = "day" + to_string(day) + ".txt";
    const vector<string> inputText = fileInput(inputFile);

    auto [part1, part2] = solveFunction(inputText);
    cout << "Day " << day << " solutions: \n"
         << "Part 1: " << part1 << "\n"
         << "Part 2: " << part2 << endl;
}

int main() {
    map<int, function<tuple<int, int>(const vector<string>&)>> solutions = {
        {1, day1},
        {2, day2},
        {3, day3},
        {4, day4},
        {5, day5},
        {6, day6},
        {7, day7},
        {8, day8}
    };
    if (constexpr int day = 8; solutions.contains(day)) {
        const auto start = std::chrono::high_resolution_clock::now();
        solveDay(day, solutions[day]);
        const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = duration_cast<chrono::microseconds>(stop - start);
        cout << "Duration in microseconds: " << duration.count() << endl;
    } else {
        cerr << "Solution for day " << day << " not implemented!" << endl;
    }

    return 0;
}


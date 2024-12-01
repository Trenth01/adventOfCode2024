#include <chrono>
#include <functional>
#include <map>

#include "solutions/day1.hpp"
//
// Created by Trent on 12/1/2024.
//


vector<string> fileInput(const string& fileName) {
    const string filePath = "../inputs/" + fileName;
    ifstream inputFile = ifstream(filePath);
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

void solveDay(int day, const function<tuple<int, int>(const vector<string>&)>& solveFunction) {
    const string inputFile = "day" + to_string(day) + ".txt";
    const vector<string> inputText = fileInput(inputFile);

    auto [part1, part2] = solveFunction(inputText);
    cout << "Day " << day << " solutions: \n"
         << "Part 1: " << part1 << "\n"
         << "Part 2: " << part2 << endl;
}

int main() {

    map<int, function<tuple<int, int>(const vector<string>&)>> solutions = {
        {1, day1}
        // Add more days here, e.g., {2, day2}, {3, day3}, etc.
    };
    if (constexpr int day = 1; solutions.contains(day)) {
        const auto start = std::chrono::high_resolution_clock::now();
        solveDay(day, solutions[day]);
        const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = duration_cast<chrono::microseconds>(stop - start);
        cout << duration.count() << endl;
    } else {
        cerr << "Solution for day " << day << " not implemented!" << endl;
    }

    return 0;
}


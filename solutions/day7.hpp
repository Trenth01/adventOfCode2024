#pragma once
using namespace std;
#include <sstream>
#include <tuple>

inline string int128ToString(__int128 value) {
    if (value == 0) {
        return "0";
    }

    bool isNegative = value < 0;
    if (isNegative) {
        value = -value;
    }

    std::string result;
    while (value > 0) {
        result += '0' + (value % 10);
        value /= 10;
    }

    if (isNegative) {
        result += '-';
    }

    std::reverse(result.begin(), result.end());
    return result;
}


inline long long check_valid(const long long& target, const vector<long long>& factors) {
    int n = factors.size();
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        long long result = factors[0];
        for (int i = 0; i < n - 1; ++i) {
            if (mask & (1 << i)) {
                result *= factors[i + 1];
            } else {
                result += factors[i + 1];
            }
        }
        if (result == target) {
            return target;
        }
    }
    return 0;
}

inline long long concatenate(const long long& a, const long long& b) {
    return stoll(to_string(a) + to_string(b));
}

inline long long check_concatenation(const long long& target, const vector<long long>& factors, const int& pos) {
    for (int i = pos; i < factors.size() - 1 ; ++i) {
        vector<long long> new_factors = factors;
        long long front = new_factors[i];
        new_factors.erase(new_factors.begin() + i);
        new_factors[i] = concatenate(front, new_factors[i]);
        if (check_valid(target, new_factors) != 0) {
            return target;
        }
        //return check_concatenation(target, new_factors, i++);
    }
    return 0;
}

inline tuple<int, int> day7(const vector<string>& input) {
    __int128  part1 = 0;
    __int128  part2 = 0;
    for (const auto & i : input) {
        stringstream ss(i);
        string s;
        long long target = 0;
        vector<long long> factors;
        while (ss >> s) {
            if (target == 0) {
                target = stoll(s.substr(0, s.find(':')));
                continue;
            }
            factors.push_back(stoll(s));
        }
        if (const __int128 result = check_valid(target, factors); result != 0) {
            part1 += result;
        }else {
            part2 += check_concatenation(target, factors, 0);
        }
    }
    cout << "the numbers were too big lol" << endl;
    cout << "Part 1: " << int128ToString(part1) << endl;
    cout << "Part 2: " << int128ToString(part2) << endl;

    return {-1, -1};
}

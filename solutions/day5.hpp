//
// Created by Trent on 12/1/2024.
//
#pragma once
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

inline int getMidNumber(const vector<int> &v) {
    return v[(v.size() -1 )/ 2];
}

inline int correctVector(vector<int> v, map<int, set<int>>& pages) {
    unordered_map<int, vector<int>> adj;
    unordered_map<int, int> in_degree;
    unordered_set<int> unique_pages(v.begin(), v.end());

    for (int page : v) {
        in_degree[page] = 0;
    }

    for (int page : v) {
        if (pages.contains(page)) {
            for (int dependent : pages[page]) {
                if (unique_pages.contains(dependent)) {
                    adj[page].push_back(dependent);
                    in_degree[dependent]++;
                }
            }
        }
    }

    queue<int> q;
    for (int page : unique_pages) {
        if (in_degree[page] == 0) {
            q.push(page);
        }
    }

    vector<int> sorted_pages;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        sorted_pages.push_back(curr);

        for (int dependent : adj[curr]) {
            in_degree[dependent]--;
            if (in_degree[dependent] == 0) {
                q.push(dependent);
            }
        }
    }

    if (sorted_pages.size() != unique_pages.size()) {
        throw runtime_error("Cycle detected in page-ordering rules.");
    }

    return getMidNumber(sorted_pages);
}

inline int checkValidAndGetMid(string s, map<int, set<int>> &pages) {
    vector<int> v;
    size_t pos = 0;
    string comma = ",";
    while ((pos = s.find(comma)) != std::string::npos) {
        v.push_back(stoi(s.substr(0, pos)));
        s.erase(0, pos + comma.length());
    }
    v.push_back(stoi(s));
    for (int i = 0; i < v.size(); i++) {
        vector<int> after_instructions(v.begin() + i, v.end());
        for (int j = 0; j < after_instructions.size(); j++) {
            if (pages[v[i]].contains(after_instructions[j])) {
                return -1 * correctVector(v, pages) ;
            }
        }

    }
    return getMidNumber(v);
}


inline tuple<int, int> day5(const vector<string>& input) {
    vector<string> updates;
    map<int, set<int>> pages;
    int part1Sum = 0, part2Sum = 0;
    for (const auto & i : input) {
        stringstream ss(i);
        string s;
        ss >> s;
        if (s.empty()) {
            continue;
        }
        if (s.find('|' ) != string::npos){
            int page1 = stoi(s.substr(0, s.find('|')));
            int page2 = stoi(s.substr(s.find('|')+1));
            if (pages.contains(page2)){
                pages[page2].insert(page1);
            } else {
                pages[page2] = {page1};
            }
        }else{
            int sum = checkValidAndGetMid(s, pages);
            if (sum > 0) {
                part1Sum += sum;
            }else {
                part2Sum -= sum;
            }
        }
    }

    return {part1Sum, part2Sum};
}

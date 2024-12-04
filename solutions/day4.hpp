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

inline int check_up(const vector<string>& map, const int &x, const int &y){
    if (y < 3){
      return 0;
    }
    if (map[y-1][x] != 'M' || map[y-2][x] != 'A' || map[y-3][x] != 'S'){
      return 0;
    }
    return 1;
}


inline int check_down(const vector<string>& map, const int &x, const int &y){
  if (y > map.size()-4){
    return 0;
  }
  if (map[y+1][x] != 'M' || map[y+2][x] != 'A' || map[y+3][x] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_left(const vector<string>& map, const int &x, const int &y){
  if (x < 3){
    return 0;
  }
  if (map[y][x-1] != 'M' || map[y][x-2] != 'A' || map[y][x-3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_right(const vector<string>& map, const int &x, const int &y){
  if (x > map[y].size()-4){
    return 0;
  }
  if (map[y][x+1] != 'M' || map[y][x+2] != 'A' || map[y][x+3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_down_right(const vector<string>& map, const int &x, const int &y){
  if (x > map[y].size()-4 || y > map.size()-4){
    return 0;
  }
  if (map[y+1][x+1] != 'M' || map[y+2][x+2] != 'A' || map[y+3][x+3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_down_left(const vector<string>& map, const int &x, const int &y){
  if (x < 3 || y > map.size()-4){
    return 0;
  }
  if (map[y+1][x-1] != 'M' || map[y+2][x-2] != 'A' || map[y+3][x-3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_up_right(const vector<string>& map, const int &x, const int &y){
  if (x > map[y].size()-4 || y < 3){
    return 0;
  }
  if (map[y-1][x+1] != 'M' || map[y-2][x+2] != 'A' || map[y-3][x+3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_up_left(const vector<string>& map, const int &x, const int &y){
  if (x < 3 || y < 3){
    return 0;
  }
  if (map[y-1][x-1] != 'M' || map[y-2][x-2] != 'A' || map[y-3][x-3] != 'S'){
    return 0;
  }
  return 1;
}

inline int check_x_mas(const vector<string>& map, const int &x, const int &y){
  if (x < 1 || x > map[y].size()-2 || y < 1 || y > map.size()-2){
    return 0;
  }
  if (((map[y+1][x+1] == 'M' && map[y-1][x-1] == 'S') || (map[y+1][x+1] == 'S' && map[y-1][x-1] == 'M')) &&
      ((map[y+1][x-1] == 'M' && map[y-1][x+1] == 'S') || (map[y+1][x-1] == 'S' && map[y-1][x+1] == 'M'))){
    return 1;
  }
  return 0;
}

inline int check_xmas(const vector<string>& map, const int &x, const int &y){
    int sum = 0;
    vector<int(*)(const vector<string>&, const int&, const int&)> functions = {check_up, check_down, check_left, check_right, check_down_right, check_up_right, check_up_left, check_down_left};
    for(auto function: functions){
      sum+=function(map, x, y);
    }
    return sum;
}

inline tuple<int, int> day4(const vector<string>& input) {
  int xmas_count = 0;
  int x_mas_count = 0;
  for(int y = 0; y < input.size(); y++) {
    for(int x = 0; x < input[y].size(); x++) {
      if(input[y][x] == 'X') {
        xmas_count+=check_xmas(input, x, y);
      }
      if(input[y][x] == 'A') {
        x_mas_count+=check_x_mas(input, x, y);
      }

    }
  }

  return {xmas_count, x_mas_count};
}

// #include <bits/stdc++.h>
#ifndef SLIDER_MAP_H
#define SLIDER_MAP_H

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
using namespace std;

typedef vector<vector<char>> ColorMap;

struct SliderMap {
public:
  ColorMap color_map;
  ColorMap target_map;
  unsigned int n_diff_colors;
  unsigned int distance;
  unsigned int row_idx, col_idx;
  unsigned int heuristic_value;
  string path;
  string possible_dirs;  
  static const string ACTIONS;
  static unsigned int ROW_TARGET;
  static unsigned int COL_TARGET;
  static unsigned int N_ROW;
  static unsigned int N_COL;

  // empty constructor is only for using map["key"] = val
  // SliderMap()
  // // n_diff_colors{0},
  // //   distance{move(t_smap.distance)},
  // //   path{move(t_smap.path)},
  // //   possible_dirs{move(t_smap.possible_dirs)},
  // //   row_idx{move(t_smap.row_idx)},
  // //   col_idx{move(t_smap.col_idx)}
  // {
  // }
  SliderMap(ColorMap &t_color_map, ColorMap &t_target_color_map, string t_path);
  SliderMap(const SliderMap &t_smap);
  SliderMap(SliderMap &&t_smap) noexcept;
  void update_member_var();
  void print();
  void print_map();
  SliderMap& operator=(SliderMap &t_smap);
  vector<char>& operator[](unsigned int idx);
  SliderMap operator()(const char ch);
  bool movementAllowed(char direction);
  static void compute_target(ColorMap &target);
private:  
  void set_n_diff_color();
  void set_distance();
  void set_whiteblock_coordinates();
  const string get_possible_action();
};

unsigned long long int get_checksum(const string &path);
unsigned long long int get_checksum(const char *path);

vector<ColorMap> read_SliderMap(const string& project_dir, const string& rel_path);
vector<SliderMap> get_next_slide_maps(SliderMap &t_smap);

#endif
// #include <bits/stdc++.h>
#include "slider_map.h"
using namespace std;

const string SliderMap::ACTIONS{'U', 'D', 'L', 'R'};
unsigned int SliderMap::ROW_TARGET{0};
unsigned int SliderMap::COL_TARGET{0};
unsigned int SliderMap::N_ROW{0};
unsigned int SliderMap::N_COL{0};

SliderMap::SliderMap(ColorMap &t_color_map, ColorMap &t_target_color_map,
                     string t_path)
    : color_map{t_color_map}, target_map{t_target_color_map},
      n_diff_colors{0}, distance{0}, row_idx{0}, col_idx{0},
      heuristic_value{0}, path{t_path}, possible_dirs{""} {
  // assign color map
  // color_map.resize(t_n_row_idx, vector<char *>(t_n_col));
  // for (size_t i = 0; i < t_color_map.size(); ++i) {
  //   for (size_t j = 0; j < t_color_map[i].size(); ++j) {
  //     color_map[i][j] = t_color_map[i][j];
  //   }
  //   color_map[i].shrink_to_fit();
  // }
  color_map.shrink_to_fit();
  set_whiteblock_coordinates();
  update_member_var();
}
SliderMap::SliderMap(const SliderMap &t_smap)
    : color_map{t_smap.color_map}, target_map{t_smap.target_map},
      n_diff_colors{t_smap.n_diff_colors}, distance{t_smap.distance},
      row_idx{t_smap.row_idx}, col_idx{t_smap.col_idx},
      heuristic_value{t_smap.heuristic_value}, path{t_smap.path},
      possible_dirs{t_smap.possible_dirs} {}
SliderMap::SliderMap(SliderMap &&t_smap) noexcept
    : color_map{move(t_smap.color_map)}, target_map{move(t_smap.target_map)},
      n_diff_colors{move(t_smap.n_diff_colors)}, distance{t_smap.distance},
      row_idx{move(t_smap.row_idx)}, col_idx{move(t_smap.col_idx)},
      heuristic_value{move(t_smap.heuristic_value)}, path{move(t_smap.path)},
      possible_dirs{move(t_smap.possible_dirs)} {}
void SliderMap::update_member_var() {
  possible_dirs = get_possible_action();
  set_n_diff_color();
  set_distance();
  heuristic_value = n_diff_colors + distance + path.size();
}

void SliderMap::print() {
  cout << "row_idx: " << row_idx << ", col_idx: " << col_idx << '\n';
  cout << "Distance: " << distance << '\n';
  cout << "n_diff_colors: " << n_diff_colors << '\n';
  cout << "path: " << path << '\n';
  cout << "heuristic: " << heuristic_value << endl;
}
void SliderMap::print_map() {
  cout << "map with path: " << path << endl;
  for (auto row_idx : color_map) {
    for (auto ch_ptr : row_idx) {
      cout << ch_ptr;
    }
    cout << endl;
  }
  cout << endl;
}
SliderMap &SliderMap::operator=(SliderMap &t_smap) {
  color_map = t_smap.color_map;
  target_map = t_smap.target_map;
  n_diff_colors = t_smap.n_diff_colors;
  distance = t_smap.distance;
  path = t_smap.path;
  possible_dirs = t_smap.possible_dirs;
  row_idx = t_smap.row_idx;
  col_idx = t_smap.col_idx;
  heuristic_value = t_smap.heuristic_value;
  return *this;
}

vector<char> &SliderMap::operator[](unsigned int idx) { return color_map[idx]; }

SliderMap SliderMap::operator()(const char ch) {
  auto possible_actions = get_possible_action();
  if (find(possible_actions.begin(), possible_actions.end(), ch) ==
      possible_actions.end()) {
    throw runtime_error("Given direction is not possible or meaningless");
    return *this;
  }

  auto new_smap = SliderMap(*this);
  new_smap.path += ch;
  unsigned int new_row_idx{row_idx};
  unsigned int new_col_idx{col_idx};

  switch (ch) {
  case 'U':
    new_row_idx += 1;
    new_smap.row_idx += 1;
    break;
  case 'D':
    new_row_idx -= 1;
    new_smap.row_idx -= 1;
    break;
  case 'L':
    new_col_idx += 1;
    new_smap.col_idx += 1;
    break;
  case 'R':
    new_col_idx -= 1;
    new_smap.col_idx -= 1;
    break;
  }
  swap(new_smap[row_idx][col_idx], new_smap[new_row_idx][new_col_idx]);
  new_smap.update_member_var();
  return move(new_smap);
}

void SliderMap::set_n_diff_color() {
  n_diff_colors = 0;
  for (size_t i = 0; i < N_ROW; ++i) {
    for (size_t j = 0; j < N_COL; ++j) {
      if (color_map[i][j] != target_map[i][j] && 
          target_map[i][j] != 'W') {
        n_diff_colors++;
      }
    }
  }
}

void SliderMap::set_distance() {
  distance = static_cast<unsigned int>(
      abs(static_cast<int>(SliderMap::ROW_TARGET) - static_cast<int>(row_idx)) +
      abs(static_cast<int>(SliderMap::COL_TARGET) - static_cast<int>(col_idx)));
}

void SliderMap::set_whiteblock_coordinates() {
  for (unsigned int i = 0; i < N_ROW; ++i) {
    for (unsigned int j = 0; j < N_COL; ++j) {
      if (color_map[i][j] == 'W') {
        row_idx = i;
        col_idx = j;
        return;
      }
    }
  }
  cerr << "Algorithm failure: 'W' not found" << endl;
}
bool SliderMap::movementAllowed(char direction) {
  switch (direction) {
  case 'U':
    if (*path.rbegin() == 'D')
      return false;
    else
      return (row_idx != N_ROW - 1) ? true : false;
  case 'D':
    if (*path.rbegin() == 'U')
      return false;
    else
      return (row_idx != 0) ? true : false;
  case 'L':
    if (*path.rbegin() == 'R')
      return false;
    else
      return (col_idx != N_COL - 1) ? true : false;
  case 'R':
    if (*path.rbegin() == 'L')
      return false;
    else
      return (col_idx != 0) ? true : false;
  default:
    cerr << "Error with direction";
  }
  return false;
}
const string SliderMap::get_possible_action() {
  string result;
  for (auto const ch : SliderMap::ACTIONS) {
    if (movementAllowed(ch))
      result.push_back(ch);
  }
  result.shrink_to_fit();
  return result;
}

void SliderMap::compute_target(ColorMap &target) {
  for (unsigned int i = 0; i < N_ROW; ++i) {
    for (unsigned int j = 0; j < N_COL; ++j) {
      if (target[i][j] == 'W') {
        SliderMap::ROW_TARGET = i;
        SliderMap::COL_TARGET = j;
        return;
      }
    }
  }
}

unsigned long long int get_checksum(const string &path) {
  unsigned long long int checksum_prev{0}, checksum_current{0};
  unsigned int ascii_code{0};
  for (size_t i = 0; i < path.size(); ++i) {
    ascii_code = static_cast<unsigned int>(path[i]);
    checksum_prev = checksum_current;
    checksum_current = (checksum_prev * 243 + ascii_code) % 100000007;
  }
  return checksum_current;
}

unsigned long long int get_checksum(const char *path) {
  unsigned long long int checksum_prev{0}, checksum_current{0};
  unsigned int ascii_code{0};
  int i = 0;
  while (*(path + i) != '\0') {
    ascii_code = static_cast<unsigned int>(path[i]);
    checksum_prev = checksum_current;
    checksum_current = (checksum_prev * 243 + ascii_code) % 100000007;
    ++i;
  }
  return checksum_current;
}

vector<ColorMap> read_SliderMap(const string &project_dir,
                                const string &rel_path) {
  istream *iss;
  ifstream freader;
  if (project_dir != "" && rel_path != "") {
    freader.open(project_dir + rel_path);
    iss = &freader;
  } else
    iss = &cin;

  unsigned int N{0};
  *iss >> N;
  SliderMap::N_ROW = N;
  SliderMap::N_COL = N;

  ColorMap matrix_begin(N);
  ColorMap matrix_end(N);
  string s;

  vector<ColorMap> maps(2);

  for (unsigned int i = 0; i < N; ++i) {
    *iss >> s;
    for (auto ch : s) {
      matrix_begin[i].push_back(ch);
    }
  }

  for (size_t i = 0; i < N; ++i) {
    *iss >> s;
    for (auto ch : s) {
      matrix_end[i].push_back(ch);
    }
  }
  return vector<ColorMap>{matrix_begin, matrix_end};
}

vector<SliderMap> get_next_slide_maps(SliderMap &t_smap) {
  vector<SliderMap> result;
  for (auto ch : t_smap.possible_dirs) {
    result.push_back(t_smap(ch));
  }
  return move(result);
}
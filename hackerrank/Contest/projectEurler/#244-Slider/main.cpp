#include <bits/stdc++.h>
// #include <cmath>
// #include <cstdio>
// #include <vector>
// #include <iostream>
// #include <algorithm>
// #include <memory>
using namespace std;

typedef vector<vector<shared_ptr<char>>> Map;

int n{0};
const string actions = {'U', 'D', 'L', 'R'};
int n_row{0};
int n_col{0};

class SliderMap {
private:
  Map map;
  int row, col;
  void find_whiteblock_coordinates() {
    for (int row_idx = 0; row_idx < n_row; ++row_idx) {
      for (int col_idx = 0; col_idx < n_col; ++col_idx) {
        if (*map[row_idx][col_idx] == 'W') {
          row = row_idx;
          col = col_idx;
          return;
        }
      }
    }
    cerr << "Algorithm failure: 'W' not found" << endl;
  }

  bool movementAllowed(char direction) {
    switch (direction) {
    case 'U':
      return (row != n_row - 1) ? true : false;
    case 'D':
      return (row != 0) ? true : false;
    case 'L':
      return (col != n_col - 1) ? true : false;
    case 'R':
      return (col != 0) ? true : false;
    default:
      cerr << "Error with direction";
    }
  }

public:
  SliderMap(Map _map) : map{_map}, row{0}, col{0} {
    find_whiteblock_coordinates();
  }
  SliderMap(SliderMap &_smap)
      : map{_smap.get_map()}, row{_smap.get_row_idx()},
        col{_smap.get_col_idx()} {}
  vector<shared_ptr<char>> operator[](int idx) { return map[idx]; }
  const string get_possible_action() {
    string result;
    for (auto const ch : actions) {
      if (movementAllowed(ch))
        result.push_back(ch);
    }
    return result;
  }
  Map get_map() { return map; }
  int get_row_idx() { return row; }
  int get_col_idx() { return col; }

  SliderMap operator()(const char ch) {
    auto new_smap = SliderMap(map);
    auto tmp = new_smap[row][col];
    switch (ch) {
    case 'U':
      new_smap[row][col] = new_smap[row + 1][col];
      new_smap[row + 1][col] = tmp;
      break;
    case 'D':
      new_smap[row][col] = new_smap[row - 1][col];
      new_smap[row - 1][col] = tmp;
      break;
    case 'L':
      new_smap[row][col] = new_smap[row][col + 1];
      new_smap[row][col + 1] = tmp;
      break;
    case 'R':
      new_smap[row][col] = new_smap[row][col - 1];
      new_smap[row][col - 1] = tmp;
      break;
    }
    return new_smap;
  }
};

int get_checksum(string &path) {
  int checksum_prev{0}, checksum_current{0};
  int ascii_code{0};
  for (int i = 0; i < path.size(); ++i) {
    ascii_code = int(path[i]);
    checksum_prev = checksum_current;
    checksum_current = (checksum_prev * 243 + ascii_code) % 100000007;
  }
  return checksum_current;
}

vector<SliderMap> get_next_sliderMap(SliderMap &const _smap) {
  auto dirs = _smap.get_possible_action();
  vector<SliderMap> next_sliderMaps;
  for (auto dir : dirs) {
    next_sliderMaps.push_back(_smap(dir));
  }
  return next_sliderMaps;
}

void solution(Map _begin, Map _end) {
  SliderMap mapBegin{_begin};
  SliderMap mapEnd{_end};

  deque<SliderMap> queue;
  auto next_maps = get_next_sliderMap(mapBegin);
  queue.insert(queue.end(), next_maps.begin(), next_maps.end());

  while (queue.size() > 0) {
    auto smap = queue.front();
    queue.pop_front();

    next_maps = get_next_sliderMap(mapBegin);
    queue.insert(queue.end(), next_maps.begin(), next_maps.end());
  }
};

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  cin >> n;
  n_row = n;

  vector<string> matrix_begin;
  vector<string> matrix_end;
  string s;

  for (int i = 0; i < n; ++i) {
    cin >> s;
    matrix_begin.push_back(s);
  }
  for (int i = 0; i < n; ++i) {
    cin >> s;
    matrix_end.push_back(s);
  }

  string path;
  // find path

  // calculate result for each
  get_checksum(path);

  // sum them all

  return 0;
}

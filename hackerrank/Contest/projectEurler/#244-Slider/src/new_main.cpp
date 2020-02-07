#include "slider_map.h"

void extend_map(map<const string, SliderMap> &cache_map,
                multimap<unsigned int, string> &heuristic_map, string path) {
  for (auto m : get_next_slide_maps(cache_map.at(path))) {
    heuristic_map.insert(pair<unsigned int, string>(m.heuristic_value, m.path));
    cache_map.insert(make_pair(m.path, move(m)));
  }
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  string project_dir{"/home/lenty/scripts/cpp/coding_practice/hackerrank/Contest/projectEurler/#244-Slider/"};
  string rel_path{"test/data/input8.txt"};
  auto color_maps = read_SliderMap(project_dir, rel_path);
  SliderMap::compute_target(color_maps[1]);
  SliderMap begin{color_maps[0], color_maps[1], ""};
  SliderMap end{color_maps[1], color_maps[1], ""};

  map<const string, SliderMap> cache_map;
  multimap<unsigned int, string> heuristic_map;
  cache_map.insert(make_pair(begin.path, move(begin)));

  string m_path{""};


  heuristic_map.insert(pair<unsigned int, string>(cache_map.at("").heuristic_value, ""));

  // get the smallest heuristic map
  auto smallest_heuristic_smap = cache_map.at(heuristic_map.begin()->second);
  vector<string> possible_path;
  unsigned int shortest_path_length = {numeric_limits<unsigned int>::max()};
  while (smallest_heuristic_smap.distance > 0 ||
         smallest_heuristic_smap.path.size() <= shortest_path_length) {
    if (smallest_heuristic_smap.distance == 0 && smallest_heuristic_smap.n_diff_colors==0) {
      auto another_possible_path = smallest_heuristic_smap.path;
      auto another_possible_size = static_cast<unsigned int>(another_possible_path.size());
      if(shortest_path_length >another_possible_size){
        shortest_path_length = another_possible_size;
        possible_path.clear();
        possible_path.shrink_to_fit();
        possible_path.push_back(another_possible_path);
      }
      else if(shortest_path_length == another_possible_size){
        possible_path.push_back(another_possible_path);
      }
      
    }
    auto it = heuristic_map.begin();
    extend_map(cache_map, heuristic_map, smallest_heuristic_smap.path);
    cache_map.erase(it->second);
    heuristic_map.erase(it);    
    smallest_heuristic_smap = cache_map.at(heuristic_map.begin()->second);
  }

  unsigned long long int sum{0};
  for(auto p:possible_path){
    cout << p << endl;
    // cache_map.at(p).print_map();
    sum += get_checksum(p);
  }
  sum %= 100000007;
  cout << sum << endl;

  return 0;
}

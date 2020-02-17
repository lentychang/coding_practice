#include "slider_map.h"

using namespace std;

void extend_map(multimap<unsigned int, SliderMap> &heuristic_map) {
  for (auto m : get_next_slide_maps(heuristic_map.begin()->second)) {
    heuristic_map.insert(pair<unsigned int, SliderMap>(m.heuristic_value, m));
  }
}

int main(int argc,char *argv[]) {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  string project_dir{"/home/lenty/scripts/cpp/coding_practice/hackerrank/Contest/projectEurler/#244-Slider/"};
  string rel_path{"test/data/input"};
  rel_path.append(argv[1]);
  rel_path.append(".txt");
  auto color_maps = read_SliderMap(project_dir, rel_path);
  SliderMap::compute_target(color_maps[1]);
  SliderMap begin{color_maps[0], color_maps[1], ""};
  SliderMap end{color_maps[1], color_maps[1], ""};

  multimap<unsigned int, SliderMap> heuristic_map;
  heuristic_map.insert(pair<unsigned int,SliderMap>(begin.heuristic_value,begin));

  string m_path{""};

  // get the smallest heuristic map
  vector<string> possible_path;
  unsigned int shortest_path_length = {numeric_limits<unsigned int>::max()};
  multimap<unsigned int, SliderMap>::iterator candidate_iter;
  while (heuristic_map.size()>0) {
    candidate_iter=heuristic_map.begin();
    auto path_length_candidate = candidate_iter->second.path.size();
    if (candidate_iter->second.n_diff_colors == 0 && candidate_iter->second.distance==0) {
      if(shortest_path_length > path_length_candidate){
        shortest_path_length = path_length_candidate;
        possible_path.clear();
        possible_path.shrink_to_fit();
        possible_path.push_back(candidate_iter->second.path);
      }
      else if(shortest_path_length == path_length_candidate){
        possible_path.push_back(candidate_iter->second.path);
      }      
    }
    else{
      if(shortest_path_length-path_length_candidate >= candidate_iter->second.n_diff_colors){
        extend_map(heuristic_map);
      }
    }    
    heuristic_map.erase(candidate_iter);    
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

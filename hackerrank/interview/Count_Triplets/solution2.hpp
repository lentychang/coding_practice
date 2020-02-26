#include <bits/stdc++.h>
#include "utils.hpp"
using namespace std;

// Complete the countTriplets function below.
long solution2(vector<long> arr, long r) {
  unordered_map<long, vector<long>> mp;
  for (long idx = 0; idx < static_cast<long>(arr.size()); ++idx) {
    if (mp.find(arr[idx]) == mp.end()) {
      mp[arr[idx]] = vector<long>{idx};
    } else {
      mp[arr[idx]].push_back(idx);
    }
  }

  vector<long> keys;
  for (auto p : mp) {
    keys.push_back(p.first);
  }
  sort(keys.begin(), keys.end());
  long sum = 0;
  if (r == 1) {
    long size = 0;
    for (auto p : keys) {
      size = mp[p].size();
      sum += size * (size - 1) * (size - 2) / 6;
    }
  } else {
    for (auto iter = mp.begin(); iter != mp.end(); ++iter) {
      auto second_member_iter = mp.find(iter->first * r);
      auto third_member_iter = mp.find(iter->first * r * r);

      if (second_member_iter != mp.end() && third_member_iter != mp.end()) {
        auto vec_j = second_member_iter->second;
        auto vec_k = third_member_iter->second;

        long start_j{0}, start_k{0};

        for (auto i : iter->second) {
          for (long j = start_j; j < static_cast<long>(vec_j.size()); ++j) {
            if (i < vec_j[j]) {
              for (long k = start_k; k < static_cast<long>(vec_k.size()); ++k) {
                if (vec_j[j] < vec_k[k]) {
                  sum += (static_cast<long>(vec_k.size()) - k);
                  break;
                } else {
                  start_k++;
                }
              }
            } else {
              start_j++;
            }
          }
          start_k = 0;
        }
      }
    }
  }
  return sum;
}

long test2(const char* filename){
  auto arr = get_array(filename);
  auto r = get_ratio(filename);

  long ans = solution2(arr, r);
  cout << ans << "\n";
  return 0;
}
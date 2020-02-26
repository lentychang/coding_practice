#include <bits/stdc++.h>
#include "utils.hpp"
using namespace std;

// Complete the countTriplets function below.
long solution1(vector<long> arr, long r) {
  unordered_map<long, long> count_mp, track_mp;
  for (long i : arr) {
    count_mp[i]++;
  }
  long sum = 0;

  for (long i : arr) {
    count_mp[i]--;
    if (i % r == 0) {
      long n_first = track_mp[i / r];
      long n_third = count_mp[i * r];
      sum += n_first * n_third;
    }
    track_mp[i]++;
  }

  return sum;
}

int test1(const char* filename) {
  auto arr = get_array(filename);
  auto r = get_ratio(filename);
  long ans = solution1(arr, r);

  cout << ans << "\n";
  return 0;
}

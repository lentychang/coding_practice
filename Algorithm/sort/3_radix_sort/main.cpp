#include <bits/stdc++.h>
using namespace std;

void radix_sort(vector<int> &data) {
  int n = data.size();
  int max_val = *max_element(data.begin(), data.end());
  int count = max_val;
  int idx{0};

  int digit = 1;
  while (count > 9) {
    count /= 10;
    digit += 1;
  }
  vector<vector<int>> bucket;
  bucket.resize(n, vector<int>(n, 0));
  vector<int> group_by_digit(n, 0);

  if (digit <= 9) {
    //use LSD(Least significant digit) method
    int current_scale = 1;
    while (current_scale <= max_val) {
      for (int i = 0; i < n; ++i) {
        // calcuate i-th digit for every element
        int module = int(data[i] / current_scale) % 10;

        // put to position related to module number(row) and module-th in
        // group_by_digit (col)
        bucket[module][group_by_digit[module]] = data[i];
        // this count the number of elements in same digit.
        group_by_digit[module] += 1;
      }

      for (int i = 0; i < n; ++i) {
        if (group_by_digit[i] != 0) {
          for(int j = 0; j < group_by_digit[i]; j++) {
            data[idx] = bucket[i][j];
            idx += 1;
          }
          group_by_digit[i] = 0;
        }
      }

      current_scale *= 10;
      idx = 0;
    }
  }
  for (auto e : data) {
    cout << e << " ";
  }
  cout << endl;
}

int main() {

  vector<int> data{89, 34, 23, 78, 67, 100, 66, 29,
                   79, 55, 78, 88, 92, 96,  96, 23};
  radix_sort(data);

  return 0;
}
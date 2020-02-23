#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int> &data) {
  //           till the last second, since it will compare with last one
  for (size_t i = 0; i < data.size() - 1; ++i) {
    // till the last nth number, because every one round, it will fixed
    // nth-largest number.
    for (size_t j = 0; j < data.size() - i - 1; ++j) {
      if (data[j] > data[j + 1]) {
        swap(data[j], data[j + 1]);
      }
    }
  }
}


void test_bubule_sort(vector<int> &data, vector<int> &result) {
  bool sucess = true;
  for (size_t i = 0; i < result.size(); ++i) {
    if (data[i] != result[i]) {
      sucess = false;
      cout << "Test Failed !!" << endl;
      break;
    }
  }

  if (sucess)
    cout << "Test passed !" << endl;
}

int main() {
  vector<int> data{89, 34, 23, 78, 67, 100, 66, 29,
                   79, 55, 78, 88, 92, 96,  96, 23};
  vector<int> result{23, 23, 29, 34, 55, 66, 67, 78,
                     78, 79, 88, 89, 92, 96, 96, 100};

  bubble_sort(data);
  test_bubule_sort(data, result);
  return 0;
}

#include<bits/stdc++.h>

#ifndef UTILS_HPP
#define UTILS_HPP
using namespace std;

string ltrim(const string &str) {
  string s(str);

  s.erase(s.begin(),
          find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end());

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}

vector<long> get_array(const char* filename) {
  string nr_temp;
  fstream reader(filename);
  istream *iss;
  iss = &reader;
  // iss = &cin;
  getline(*iss, nr_temp);

  vector<string> nr = split(rtrim(nr_temp));

  int n = stoi(nr[0]);

  long r = stol(nr[1]);

  string arr_temp_temp;
  getline(*iss, arr_temp_temp);

  vector<string> arr_temp = split(rtrim(arr_temp_temp));

  vector<long> arr(n);

  for (int i = 0; i < n; i++) {
    long arr_item = stol(arr_temp[i]);

    arr[i] = arr_item;
  }
  return arr;
}

long get_ratio(const char* filename){
  string nr_temp;
  fstream reader(filename);
  istream *iss;
  iss = &reader;
  // iss = &cin;
  getline(*iss, nr_temp);

  vector<string> nr = split(rtrim(nr_temp));

  return stol(nr[1]);
}
#endif
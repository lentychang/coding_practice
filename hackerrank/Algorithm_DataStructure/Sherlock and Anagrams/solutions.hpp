#include<bits/stdc++.h>
using namespace std;

bool isAnagram(const string &s1, const string &s2)
{
    
    unordered_map<char, int> dict1;
    unordered_map<char, int> dict2;
    for (auto ch : s1)
    {
        if (dict1.find(ch) == dict1.end())
            dict1.insert(pair<char, int>(ch, 1));
        else
            dict1.at(ch) += 1;
    }

    for (auto ch : s2)
    {
        if (dict2.find(ch) == dict2.end())
            dict2.insert(pair<char, int>(ch, 1));
        else
            dict2.at(ch) += 1;
    }
    return dict1==dict2;
}

vector<int> find_rest(unordered_map<char, vector<int>> &m, char ch, int idx)
{
    auto iter = find(m[ch].begin(), m[ch].end(), idx);
    if (iter == m[ch].end() || iter + 1 == m[ch].end())
    {
        return vector<int>();
    }
    return vector<int>(iter + 1, m[ch].end());
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams_complicated(string s)
{
    int length = static_cast<int>(s.size());
    unordered_map<char, vector<int>> dict;
    for (int i = 0; i < length; ++i)
    {
        if (dict.find(s[static_cast<unsigned int>(i)]) == dict.end())
        {
            dict.insert(pair<char, vector<int>>(s[static_cast<unsigned int>(i)], vector<int>(1, i)));
        }
        else
        {
            dict.at(s[static_cast<unsigned int>(i)]).push_back(i);
        }
    }
    int count = 0;
    vector<pair<int, int>> source_sets;
    for (int start_idx = 0; start_idx < length - 1; ++start_idx)
    {
        auto rest_idx = find_rest(dict, s[static_cast<size_t>(start_idx)], start_idx);
        for (int window_width = 1; window_width < length - start_idx; ++window_width)
        {
            // source_sets.push_back(pair<unsigned int, unsigned int>(start_idx, window_width));
            set<int> window_start_idx;
            for (int fit_start_idx : rest_idx)
            {

                int end = min(fit_start_idx, length - window_width);
                for (int window_start = max(0, fit_start_idx - window_width + 1); window_start <= end; ++window_start)
                {
                    if (window_start <= start_idx)
                    {
                        continue;
                    }
                    window_start_idx.insert(window_start);
                }
            }
            for (auto id : window_start_idx)
            {
                auto ss = s.substr(static_cast<size_t>(start_idx), static_cast<size_t>(window_width));
                auto sub_string = s.substr(static_cast<size_t>(id), static_cast<size_t>(window_width));
                if (isAnagram(ss, sub_string))
                {
                    count++;
                }
            }
        }
    }
    return count;
}


// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams_easy(string s)
{
    int length = static_cast<int>(s.size());
    int count = 0;
    vector<pair<int, int>> source_sets;
    for (int start_idx = 0; start_idx < length - 1; ++start_idx)
    {
        for (int window_width = 1; window_width < length - start_idx; ++window_width)
        {
            // source_sets.push_back(pair<unsigned int, unsigned int>(start_idx, window_width));
            // set<unsigned int> window_start_idx;
            for (int i = start_idx + 1; i < length - window_width + 1; ++i)
            {
                if (isAnagram(s.substr(static_cast<size_t>(start_idx), static_cast<size_t>(window_width)), s.substr(static_cast<size_t>(i), static_cast<size_t>(window_width))))
                {
                    count++;
                }
            }
        }
    }
    return count;
}


bool test_isAnagram()
{
    string s1("abc");
    string s2("bac");
    string s3 = "ccc";
    string s4 = "abcc";
    return isAnagram(s1, s2) == true && isAnagram(s1, s3) == false && isAnagram(s1, s4) == false;
}

bool test_find_rest()
{
    unordered_map<char, vector<int>> umap;
    umap['a'] = {1, 4, 5, 6, 7};
    umap['b'] = {0, 2, 8, 9};
    umap['c'] = {3};
    return find_rest(umap, 'a', 1) == vector<int>{4, 5, 6, 7} && find_rest(umap, 'a', 5) == vector<int>{6, 7} && find_rest(umap, 'a', 7) == vector<int>{} && find_rest(umap, 'a', 3) == vector<int>{};
}

void test()
{
    assert(test_isAnagram() && "isAnagram");
    assert(test_find_rest() && "test find_rest");
}
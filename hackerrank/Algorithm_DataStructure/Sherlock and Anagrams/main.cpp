#include <bits/stdc++.h>

using namespace std;

bool isAnagram(string &s1, string &s2)
{
    int length = s1.size();
    map<char, int> dict;

    for (auto ch : s1)
    {
        if (dict.find(ch) == dict.end())
        {
            dict.insert(pair<char, int>(ch, 1));
        }
        else
        {
            dict[ch] += 1;
        }
    }
    for (auto ch : s2)
    {
        if (dict.find(ch) == dict.end())
        {
            return false;
        }
        else
        {
            if (dict[ch] == 0)
            {
                return false;
            }
            dict[ch] -= 1;
        }
    }

    for (auto pair : dict)
    {
        if (pair.second != 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> find_rest(unordered_map<char,vector<int>> &m, char ch, int idx){
    auto iter = find(m[ch].begin(),m[ch].end(),idx);
    if(iter==m[ch].end() || iter+1 == m[ch].end()){
        return vector<int>();    
    }
    return vector<int>(iter+1,m[ch].end());
}


// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s)
{
    unordered_map<char,vector<int>> dict;
    for(int i=0;i<s.size();++i){
        if(dict.find(s[i])==dict.end()){
            dict.insert(pair<char,vector<int>>(s[i],vector<int>(1,i)));
        }
        else{
            dict[s[i]].push_back(i);
        }
    }

    for(int start_idx=0;start_idx<s.size()-1;++start_idx){
        auto rest_idx = find_rest(dict,s[start_idx],start_idx);
        for(int window_width=1;window_width<s.size()-1;++window_width){
            for(auto fit_start_idx:rest_idx){
                for()
            }
        }
    }
}

int main()
{
    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++)
    {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);
        cout << result << "\n";
    }
    return 0;
}


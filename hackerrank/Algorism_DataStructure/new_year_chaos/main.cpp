#include <bits/stdc++.h>
#include <iterator>

using namespace std;

vector<string> split_string(string);

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {
    int dist{0};
    int ans{0};
    // check if there are anyone who move more than twice
    for(int i=0;i<q.size();i++){
        dist =(q[i]- i-1);
        if(dist >2){
            cout << "Too chaotic" << endl;
            return;
        }
        // i is current position
        // j is position before bribes
        for(int j=max(0,q[i]-2);j<i;j++){
            if(q[j]>q[i]) ans++;
        }
    }

    cout << ans << endl;
        
}


int main()
{
    int t;

    istream* is;
    is = new ifstream{"input.txt"};
    // *is = cin;

    *is >> t;
    is->ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        *is >> n;
        is->ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(*is, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

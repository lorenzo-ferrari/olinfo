#include <bits/stdc++.h>
using namespace std;
ifstream in ("input.txt");
ofstream out ("output.txt");

string convert (string s)
{
    string res;
    int k = s[0]-'a';

    for(int i = 0; i < s.size(); i++)
    {
        if(s[i]-k >= 'a')
            res.push_back(s[i]-k);
        else 
            res.push_back(s[i]-k+26);
    }
        
    
    return res;
}

unordered_map <string, int> m;

int main()
{
    unsigned int N, D;
    string s;
    vector <string> memo;
    in >> N >> D;

    for(int i = 0; i < N; i++)
    {
        in >> s;
        s = convert(s);
        m[s]++;

        if(m[s] == 1) memo.push_back(s);
    }

    int maxx = 0;

    for(int i = 0; i < memo.size(); i++)
        maxx = max(maxx, m[memo[i]]);

    out << maxx;
}
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

int main(){
    ifstream cin("input.txt");
    ofstream cout ("output.txt");

    int m, n, k;
    int trans[150][150];
    char s[10];

    cin >> m >> n >> k;
    for(int i = 0; i < k; i++) cin >> s[i];
    for(int i = 0; i < m; i++){
        int s,e; char c;
        cin >> s >> e >> c;
        trans[s][c] = e;
    }

    int state = 1;
    for(int i = 0; i < k; i++){
        state = trans[state][s[i]];
    }
    cout << state << "\n";        
}
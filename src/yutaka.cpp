#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;

const int mod = 1e9 + 7;
const int nax = 1e6 + 1;

int last[nax], dp[nax], ps[nax];

int taglia(int n, int v[]){
    fill(last,last+nax,-1);
    ps[0] = 1;
    for(int i = 0, nxt=-1; i < n;) {
        nxt = max(nxt,last[v[i]]);
        last[v[i]] = i;

        dp[i] = (nxt == -1) ? ps[i] : (ps[i] - ps[nxt] + mod) % mod;
        ps[i+1] = (ps[i]+dp[i]); if(ps[++i] > mod) ps[i] -= mod;
    }
    
    return dp[n-1];
}
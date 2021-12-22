#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

unordered_map <int, int> m;

int K;

int64_t comb(int N)
{
    if(N < 0) return 0;
    if(m[N]) return m[N];

    int64_t meta_sx = N/2, meta_dx = (N+1)/2;
    int64_t ans = (comb(meta_sx)*comb(meta_dx))%MOD;

    for(int l = 2; l <= K; l++)
        for(int fuori = 1; fuori < l; fuori++)
            ans = (ans + comb(meta_sx - fuori)*comb(meta_dx - l + fuori)) % MOD; 

    m[N] = ans;

    return ans;
}

int progetti(int N, int k)
{
    K = k;
    m[0] = 1;
    m[1] = 1;

    return comb(N);
}

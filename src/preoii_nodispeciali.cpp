#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pii = pair<LL, LL>;

int trova_sede(int N, int K, int A[], int B[], int P[], int filiali[]) {
    vector<vector<pii>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        --A[i], --B[i];
        g[A[i]].push_back({B[i], P[i]});
        g[B[i]].push_back({A[i], P[i]});
    }
    vector<bool> I(N);
    vector<int> H(N);
    for (int i = 0; i < K; ++i) {
        I[filiali[i] - 1] = true;
    }

    LL cost = 0, id = 0;
    {
        function<void(int, int, LL)> dfs = [&](int v, int p, LL d) {
            if (I[v]) { cost += d; ++H[v]; }
            for (auto [u, w] : g[v])
                if (u != p)
                    dfs(u, v, d + w), H[v] += H[u];
        };
        dfs(0, -1, 0);
    }

    function<void(int, int, LL)> dfs = [&](int v, int p, LL d) {
        if (d < cost) cost = d, id = v;
        for (auto [u, w] : g[v])
            if (u != p)
                dfs(u, v, d + (K - 2 * H[u]) * w);
    };
    dfs(0, -1, cost);

    return id + 1;
}
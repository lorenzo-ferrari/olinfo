// https://training.olinfo.it/#/task/garden/statement
// worst case O(NQ(logK - logQ)
// weak testcases, random optimizations are enough

#pragma GCC target("avx2")
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int LG = 31;
static constexpr int M = 3e5;

static int up[LG][M];
bitset<M> good;

inline void build(int n, vector<int> to, int p) {
    good[2*p] = good[2*p+1] = 1;
    for (int i = 0; i < n; ++i) {
        up[0][i] = to[i];
        if (good[to[i]]) good[i] = 1;
    }
    for (int j = 1; j < LG; ++j) {
        for (int i = 0; i < n; ++i) {
            up[j][i] = up[j-1][up[j-1][i]];
            if (good[up[j][i]]) good[i] = 1;
        }
    }
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;
    int p; cin >> p;
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }
    // split each node v into two:
    // a) v0 = 2*v: v, doesn't come from best path
    // b) v1 = 2*v+1: v, does come from best path
    vector<int> to(2*n);
    for (int i = 0; i < n; ++i) {
        int u = adj[i][0][0];
        to[2*i] = 2*u + (adj[u][0][1] == adj[i][0][1]);
        if ((int)adj[i].size() == 1) {
            to[2*i+1] = to[2*i];
        } else {
            u = adj[i][1][0];
            to[2*i+1] = 2*u + (adj[u][0][1] == adj[i][1][1]);
        }
    }

    build(2*n, to, p);

    int q; cin >> q;
    vector<array<int, 2>> ks(q);
    for (int i = 0, k; i < q; ++i) {
        cin >> k;
        ks[i] = {k, i};
    }
    sort(begin(ks), end(ks));
    for (int i = q-1; i > 0; --i) {
        ks[i][0] -= ks[i-1][0];
    }
    vector<int> cur;
    for (int i = 0; i < 2*n; i += 2) {
        if (good[i]) {
            cur.push_back(i);
        }
    }
    vector<int> ans(q);
    for (auto [k, i] : ks) {
        for (int j = 0; j < LG; ++j) {
            if (k & (1 << j)) {
                for (int& v : cur) {
                    v = up[j][v];
                }
            }
        }
        for (int& v : cur) {
            ans[i] += (v/2 == p);
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}

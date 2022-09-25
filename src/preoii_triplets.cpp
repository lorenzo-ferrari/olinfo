#include <bits/stdc++.h>
using namespace std;
using LL = long long;

vector<vector<int>> adj;

array<int, 3> diam() {
    function<array<int,2>(int,int)> dfs = [&](int v, int p) -> array<int, 2> {
        array<int, 2> ans{0,v};
        for (int u : adj[v]) {
            if (u == p) continue;
            auto t = dfs(u, v);
            ++t[0];
            if (t > ans) {
                ans = t;
            }
        }
        return ans;
    };
    int a = dfs(0, -1)[1];
    int b = dfs(a, -1)[1];
    int l = dfs(a, -1)[0];
    return {a, b, l};
}

int third(int x, int y) {
    vector<int> path(adj.size());
    function<int(int,int)> dfs = [&](int v, int p) -> int {
        if (v == y) return path[v] = 1;
        for (int u : adj[v]) {
            if (u == p) continue;
            path[v] |= dfs(u, v);
        }
        return path[v];
    };
    dfs(x, -1);
    function<int(int,int)> dep = [&](int v, int p) -> int {
        int ans = 0;
        for (int u : adj[v]) {
            if (u == p) continue;
            ans = max(ans, dep(u, v) + 1 - path[u]);
        }
        return ans;
    };
    return dep(x, -1);
}

int build(int n, vector<int> a, vector<int> b) {
    adj.resize(n);
    for (int i = 0; i < n-1; ++i) {
        adj[a[i]].push_back(b[i]);
        adj[b[i]].push_back(a[i]);
    }
    auto d = diam();
    return 2 * (d[2] + third(d[0], d[1]));
}
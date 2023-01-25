#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL travel_plan(int n, int m, int r[][2], int l[], int k, int p[]) {
    vector<vector<array<LL, 2>>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[r[i][0]].push_back({r[i][1], l[i]});
        adj[r[i][1]].push_back({r[i][0], l[i]});
    }
    constexpr LL INF = 1e15;
    vector<array<LL, 2>> d(n, {INF, INF});
    priority_queue<array<LL, 2>> Q;
    for (int i = 0; i < k; ++i) {
        d[p[i]][0] = d[p[i]][1] = 0;
        Q.push({0, p[i]});
    }
    vector<bool> vis(n);
    while (!Q.empty()) {
        int v = Q.top()[1];
        Q.pop();
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        for (auto [u, w] : adj[v]) {
            if (d[u][0] >= d[v][1] + w) {
                d[u][1] = d[u][0];
                d[u][0] = d[v][1] + w;
                Q.push({-d[u][1], u});
            } else if (d[u][1] > d[v][1] + w) {
                d[u][1] = d[v][1] + w;
                Q.push({-d[u][1], u});
            }
        }
    }
    return d[0][1];
}

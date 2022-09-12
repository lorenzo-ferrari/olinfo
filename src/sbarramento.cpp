#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr LL INF = 1e18;

LL fuggi(int n, int m, vector<int> a, vector<int> b, vector<int> t, vector<int> r) {
    vector<vector<array<int, 3>>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[b[i]].push_back({a[i], t[i], r[i]});
    }
    vector<LL> db(n, INF); db[n-1] = 0;
    vector<LL> dr(n, INF); dr[n-1] = 0;
    priority_queue<array<LL, 2>> Q;
    Q.push({0, n-1});
    while (!Q.empty()) {
        LL v = Q.top()[1];
        LL td = -Q.top()[0];
        Q.pop();
        for (auto [u, w, b] : adj[v]) {
            LL prv = min(max(dr[u], db[u]-1), db[u]);
            if (b) {
                dr[u] = min(dr[u], td + w);
            } else {
                db[u] = min(db[u], td + w);
            }
            LL cur = min(max(dr[u], db[u]-1), db[u]);
            if (cur < prv) {
                Q.push({-cur, u});
            }
        }
    }
    return min(max(dr[0], db[0]-1), db[0]);
}

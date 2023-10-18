#include "bits/stdc++.h"
using namespace std;
using LL = long long;
using vi = vector<int>;
using vll = vector<LL>;

vll dijkstra(int n, vector<vector<array<LL, 2>>> adj, int src) {
    vll d(n, 1e18);
    priority_queue<array<LL, 2>> Q;
    d[src] = 0;
    Q.push({0, src});
    while (!Q.empty()) {
        LL td =-Q.top()[0];
        int v = Q.top()[1];
        Q.pop();
        if (td != d[v]) {
            continue;
        }
        for (auto [u, w] : adj[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                Q.push({-d[u], u});
            }
        }
    }
    return d;
}

vll shorten(int n, int m, int q, vll k, vi a, vi b, vi c) {
    vector<vector<array<LL, 2>>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[a[i]].push_back({b[i], c[i]});
        adj[b[i]].push_back({a[i], c[i]});
    }
    auto d0 = dijkstra(n, adj, 0);
    auto d1 = dijkstra(n, adj, 1);
    auto d2 = dijkstra(n, adj, 2);
    map<LL, LL> opt;    // {d0+d2+2*d1, d1}
    for (int i = 0; i < n; ++i) {
        LL sum = d0[i] + d2[i] + 2*d1[i];
        auto it = opt.upper_bound(sum);
        while (it != end(opt) && it->first - it->second > sum - d1[i]) {
            ++it;
            opt.erase(prev(it));
        }
        if (it == begin(opt) || sum - d1[i] < prev(it)->first - prev(it)->second) {
            opt[sum] = d1[i];
        }
    }
    vector<array<LL, 2>> qs(q);
    for (int i = 0; i < q; ++i) {
        qs[i] = {k[i], i};
    }
    sort(begin(qs), end(qs));
    vll ans(q, 1e18);
    for (auto [ki, i] : qs) {
        while ((int)opt.size() > 1) {
            auto [sum0, c0] = *begin(opt);
            auto [sum1, c1] = *next(begin(opt));
            if (sum0 - ki - min(ki, c0) >= sum1 - ki - min(ki, c1)) {
                opt.erase(begin(opt));
            } else {
                break;
            }
        }
        auto [sum0, c0] = *begin(opt);
        ans[i] = max(sum0 - ki - min(ki, c0), 0LL);
    }
    return ans;
}

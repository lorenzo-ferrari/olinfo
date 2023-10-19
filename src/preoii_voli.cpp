#include "bits/stdc++.h"
using namespace std;
using LL = long long;
using vi = vector<int>;

LL plan(int n, int m, int k, vi a, vi b, vi l, vi c, vi t) {
    vector<map<int, vector<array<int, 2>>>> adj(n);
    for (int i = 0; i < m; ++i) {
        adj[a[i]][c[i]].push_back({b[i], l[i]});
        adj[b[i]][c[i]].push_back({a[i], l[i]});
    }
    vector<map<int, LL>> d(n);
    priority_queue<array<LL, 3>> Q;
    Q.push({0, 0, k});
    d[0][k] = 0;
    while (!Q.empty()) {
        LL td =-Q.top()[0];
        int v = Q.top()[1];
        int r = Q.top()[2];
        Q.pop();
        if (d[v][r] != td) {
            continue;
        }
        if (r == k) {
            for (auto [s, nb] : adj[v]) {
                for (auto [u, w] : nb) {
                    if (!d[u].count(s) || d[u][s] > d[v][r] + w + t[s]) {
                        d[u][s] = d[v][r] + w + t[s];
                        Q.push({-d[u][s], u, s});
                    }
                }
            }
        } else {
            for (auto [u, w] : adj[v][r]) {
                if (!d[u].count(r) || d[u][r] > d[v][r] + w) {
                    d[u][r] = d[v][r] + w;
                    Q.push({-d[u][r], u, r});
                }
            }
            if (!d[v].count(k) || d[v][k] > d[v][r]) {
                d[v][k] = d[v][r];
                Q.push({-d[v][k], v, k});
            }
        }
    }
    LL ans = 1e18;
    for (auto [_, val] : d[n - 1]) {
        ans = min(ans, val);
    }

    return ans;
}

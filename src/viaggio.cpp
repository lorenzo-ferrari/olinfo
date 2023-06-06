#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<vector<array<LL, 2>>> adj(n);
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c; --a, --b;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    static constexpr LL INF = 1e18;

    vector<LL> d(n, INF);
    priority_queue<array<LL, 2>> Q;
    d[0] = 0;
    Q.push({0, 0});
    while (!Q.empty()) {
        LL  v = Q.top()[1];
        LL td =-Q.top()[0];
        Q.pop();
        if (td > d[v]) continue;
        for (auto [u, w] : adj[v]) {
            if (d[u] > d[v] + w) {
                d[u] = d[v] + w;
                Q.push({-d[u], u});
            }
        }
    }

    if (d[n - 1] == INF) {
        cout << "-1\n";
    } else {
        cout << d[n - 1] << "\n";
    }
}

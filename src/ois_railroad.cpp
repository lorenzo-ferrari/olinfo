#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m; cin >> m;
    vector<array<int, 3>> e;
    vector<vector<array<LL, 2>>> adj(n);
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c;
        e.push_back({a, b, c});
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    static constexpr LL INF = 1e18;
    auto dijkstra = [&](int s) -> vector<LL> {
        vector<LL> d(n, INF);
        d[s] = 0;
        priority_queue<array<LL, 2>> Q;
        Q.push({0, s});
        while (!Q.empty()) {
            int v =  Q.top()[1];
            LL td = -Q.top()[0];
            Q.pop();
            if (td > d[v]) continue;
            for (auto [u, w] : adj[v]) {
                if (d[u] > td + w) {
                    d[u] = td + w;
                    Q.push({-d[u], u});
                }
            }
        }
        return d;
    };
    auto d0 = dijkstra(0);
    auto dn = dijkstra(n-1);
    auto in = [&](int i) -> bool {
        return d0[i] + dn[i] == d0[n-1];
    };
    LL ans = INF;
    for (auto& [a, b, c] : e) {
        if (in(a) && in(b)) continue;
        LL oth = min(d0[a] + dn[b], d0[b] + dn[a]);
        assert(oth + c > d0[n-1]);
        LL nc = d0[n-1] - oth - 1;
        if (nc <= 0) continue;
        ans = min(ans, c - nc);
    }
    cout << (ans == INF ? -1 : ans) << "\n";
}

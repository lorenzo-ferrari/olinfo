#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0, a, b, v; i < m; ++i) {
        cin >> a >> b >> v;
        // a values v the friendship with b
        adj[b].push_back({a, v});
    }
    vector<int> bw(n), bg(n);
    for (int i = 0; i < n; ++i) {
        for (auto [j, v] : adj[i]) {
            if (v < 0) continue;
            bw[j] += v;
        }
    }

    queue<int> Q;
    vector<int> vis(n, false);

    auto detach = [&](int x) -> void {
        assert(!vis[x]);
        vis[x] = true;
        Q.push(x);
    };
    auto process = [&](int x) -> void {
        for (auto [y, v] : adj[x]) {
            if (vis[y] || y == 0) continue;
            bw[y] -= v;
            bg[y] += v;
            if (bg[y] > bw[y]) {
                detach(y);
            }
        }
    };

    detach(n - 1);
    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();
        process(v);
    }

    for (int i = 0; i < n; ++i) {
        cout << "WG"[vis[i]];
    }
    cout << "\n";
}

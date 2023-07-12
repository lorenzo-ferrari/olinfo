#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<vector<array<int, 2>>> adj(n);
    LL tot = 0;
    for (int i = 0, a, b, c; i < n-1; ++i) {
        cin >> a >> b >> c; --a, --b;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        tot += c;
    }
    if (k == 1) {
        cout << 2*tot << "\n";
        return 0;
    } else {
        vector<LL> d(n);
        auto dfs = [&](auto&& self, int v, int p) -> void {
            for (auto [u, w] : adj[v]) {
                if (u == p) continue;
                d[u] = d[v] + w;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, -1);
        auto it = max_element(begin(d), end(d));
        int i = it - begin(d);
        d[i] = 0;
        dfs(dfs, i, -1);
        cout << 2*tot - *max_element(begin(d), end(d)) << "\n";
    }
}

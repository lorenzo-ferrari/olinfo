#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int tot = 0;
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        cin >> sz[i];
        tot += sz[i];
    }
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = 2e9;
    auto dfs = [&](auto&& self, int v, int p) -> int {
        for (int u : adj[v]) {
            if (u != p) {
                sz[v] += self(self, u, v);
            }
        }
        int loc = tot - sz[v];
        for (int u : adj[v]) {
            if (u != p) {
                loc = max(loc, sz[u]);
            }
        }
        ans = min(ans, loc);
        return sz[v];
    };
    dfs(dfs, 0, -1);
    cout << ans << "\n";
}

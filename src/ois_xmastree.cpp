#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    // initially, all nodes are turned on
    // {0, 1} -> {on, off}
    vector<array<LL, 2>> dp(n);
    auto solve = [&](auto&& self, int v, int p) -> void {
        if (v && (int)adj[v].size() == 1) {
            dp[v][0] = a[v];
            return;
        }
        LL delta = -1e15, sum = 0;
        int par = 0;
        for (int u : adj[v]) {
            if (u == p) continue;
            self(self, u, v);
            LL ma = max(dp[u][0], dp[u][1]);
            LL mb = min(dp[u][0], dp[u][1]);
            sum += ma;
            par ^= (ma == dp[u][1]);
            delta = max(delta, mb - ma);
        }
        dp[v][par  ] = sum + (par == 0) * a[v];
        dp[v][par^1] = sum + (par != 0) * a[v] + delta;
    };
    solve(solve, 0, -1);
    cout << max(dp[0][0], dp[0][1]) << "\n";
}

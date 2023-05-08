#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    vector<int> p(n), b(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i] >> p[i];
        if (p[i] != -1) {
            adj[p[i]].emplace_back(i);
        }
    }

    int cnt = 0;
    auto dfs = [&](auto&& self, int v, int c) -> void {
        cnt += (b[v] > c);
        for (int u : adj[v]) {
            self(self, u, min(c, b[v]));
        }
    };
    dfs(dfs, 0, 2e9);
    
    cout << cnt << "\n";
}

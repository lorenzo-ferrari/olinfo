#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        adj[i].push_back(i);
    }
    vector<vector<bool>> good(n, vector<bool>(420, true));
    for (int i = 0; i < k; ++i) {
        int l; cin >> l;
        vector<int> h(l);
        for (int j = 0; j < l; ++j) {
            cin >> h[j];
        }
        for (int j = 0; j < 420; ++j) {
            good[h[j % l]][j] = false;
        }
    }
    assert(good[0][0]);
    vector<vector<int>> d(n, vector<int>(420, 1e9));
    queue<array<int, 2>> Q;
    d[0][0] = 0;
    Q.push({0, 0});
    while (!Q.empty()) {
        auto [v, t] = Q.front();
        Q.pop();
        int tt = (t + 1) % 420;
        for (int u : adj[v]) {
            if (!good[u][tt]) continue;
            if (u == n-1) {
                cout << d[v][t]+1 << "\n";
                return 0;
            }
            if (d[u][tt] > d[v][t]+1) {
                d[u][tt] = d[v][t]+1;
                Q.push({u, tt});
            }
        }
    }
    cout << -1 << "\n";
}

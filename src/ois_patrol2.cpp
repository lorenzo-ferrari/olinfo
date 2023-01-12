#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m; cin >> m;
    int l; cin >> l;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> c(l);
    for (int& i : c) cin >> i;
    vector<int> d(n, 1e9);
    d[0] = 0;
    priority_queue<array<int, 2>> Q;
    Q.push({0, 0});
    while (!Q.empty()) {
        int v =  Q.top()[1];
        int t = -Q.top()[0];
        Q.pop();
        if (d[v] < t) continue;
        for (int u : adj[v]) {
            int tt = t + 1 + (c[(t+1)%l] == u);
            if (d[u] > tt) {
                d[u] = tt;
                Q.push({-d[u], u});
            }
        }
    }
    cout << d[n-1] << "\n";
}


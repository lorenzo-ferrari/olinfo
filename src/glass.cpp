#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
#ifdef LORENZO
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    int m; cin >> m;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < m; ++i) {
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    vector<vector<array<int, 2>>> cl(n);
    for (int i = 0; i < n; ++i) {
        cl[i].push_back({c[i], 0});
    }
    queue<int> Q;
    for (int i = 0; i < n; ++i) {
        Q.push(i);
    }
    auto insert = [&](int col, int dis, vector<array<int, 2>>& clu) -> bool {
        for (auto& x : clu) {
            if (x[0] == col) {
                if (x[1] > dis) {
                    x[1] = dis;
                    return true;
                } else {
                    return false;
                }
            }
        }
        if (clu.size() < 3 || clu.back()[1] > dis) {
            clu.push_back({col, dis});
            return true;
        }
        return false;
    };
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        for (int u : adj[v]) {
            bool news = false;
            for (auto [key, val] : cl[v]) {
                news |= insert(key, val + 1, cl[u]);
                sort(cl[u].begin(), cl[u].end(), [](array<int, 2>& a, array<int, 2>& b){ return a[1] < b[1]; });
                if ((int)cl[u].size() > 3) {
                    cl[u].pop_back();
                }
            }
            if (news) {
                Q.push(u);
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < n; ++i) {
        if ((int)cl[i].size() != 3) continue;
        int sum = 0;
        for (auto [_, val] : cl[i]) {
            sum += val;
        }
        ans = min(ans, sum);
    }
    cout << (ans == 1e9 ? -1 : ans) << "\n";
}

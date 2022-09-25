#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, c, root;
    cin >> n >> c;
    vector<int> p(n), t(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i] >> t[i];
        if (p[i] == -1)
            root = i;
        else
            g[p[i]].push_back(i);
    }

    vector<int> o;
    function<void(int)> dfs = [&](int v) {
        for (int u : g[v])
            dfs(u);
        o.push_back(v);
    };
    dfs(root);

    vector<vector<int>> dp(n, vector<int> (c + 1));
    for (int v : o) {
        int s = g[v].size();
        if (s == 0) {
            fill(dp[v].begin(), dp[v].end(), 0);
            dp[v][0] = t[v];
        } else {
            vector<int> sos(s, 0);
            vector<int> sas(s);
            for (int i = 0; i < s; ++i)
                sas[i] = dp[g[v][i]][0];
            auto it = max_element(sas.begin(), sas.end());
            dp[v][0] = t[v] + *it;
            for (int i = 1; i <= c; ++i) {
                int j = it - sas.begin();
                sas[j] = dp[g[v][j]][++sos[j]];
                it = max_element(sas.begin(), sas.end());
                dp[v][i] = t[v] + *it;
            }
            for (int i = c; i > 0; --i)
                dp[v][i] = min(dp[v][i], dp[v][i - 1] - t[v]);
        }
    }

    cout << dp[root][c] << "\n";
}

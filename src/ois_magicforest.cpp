#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr unsigned int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<array<int, 3>> e(m);
    vector<vector<array<int, 2>>> adj(n);
    for (auto& [a, b, c] : e) {
        cin >> a >> b >> c; --a, --b;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    sort(begin(e), end(e), [](array<int, 3> a, array<int, 3> b){
        return a[2] > b[2];
    });
    vector<map<int, int>> dp(n);
    unsigned int ans = 0;
    for (auto [a, b, c] : e) {
        int pa = dp[b][c+1];
        int pb = dp[a][c+1];
        dp[a][c] += 1 + pa; dp[a][c] %= mod;
        dp[b][c] += 1 + pb; dp[b][c] %= mod;
        ans += pa + pb + 1;
        ans %= mod;
    }
    cout << ans << "\n";
}

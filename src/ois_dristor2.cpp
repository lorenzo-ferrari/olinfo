#include <bits/stdc++.h>
using namespace std;

static constexpr int mod = 1e9 + 7;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
        cin >> g[i][j];
    }
    vector<vector<int>> dp(1 << n, vector<int>(m+1));
    for (int i = 0; i <= m; ++i) {
        dp[0][i] = 1;
    }
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int j = 1; j <= m; ++j) {
            dp[mask][j] = dp[mask][j - 1];
            for (int i = 0; i < n; ++i) {
                if (!g[i][j-1] || !(mask & (1 << i))) continue;
                int omask = mask ^ (1 << i);
                dp[mask][j] += dp[omask][j - 1];
                dp[mask][j] %= mod;
            }
        }
    }
    auto cnt = [&](int mask) -> size_t {
        return __builtin_popcount(mask);
    };
    int bmask = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (!dp[mask][m]) continue;
        if (cnt(mask) > cnt(bmask) || (cnt(mask) == cnt(bmask) && dp[mask][m] > dp[bmask][m])) {
            bmask = mask;
        }
    }
    cout << dp[bmask][m] << "\n";
}

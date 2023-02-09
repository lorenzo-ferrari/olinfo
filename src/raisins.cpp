#include <bits/stdc++.h>
using namespace std;

static constexpr int N = 50;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int r[N][N]{};
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> r[i][j];
    for (int i = 1; i < n; ++i) for (int j = 0; j < m; ++j) r[i][j] += r[i-1][j];
    for (int i = 0; i < n; ++i) for (int j = 1; j < m; ++j) r[i][j] += r[i][j-1];
    auto sum = [&](int il, int ih, int jl, int jh) -> int {
        int ans = r[ih][jh];
        if (il) ans -= r[il-1][jh];
        if (jl) ans -= r[ih][jl-1];
        if (il && jl) ans += r[il-1][jl-1];
        return ans;
    };
    int dp[N][N][N][N]{};
    bool vis[N][N][N][N]{};
    auto solve = [&](auto&& self, int i0, int i1, int j0, int j1) -> int {
        if (i0 == i1 && j0 == j1) return 0;
        if (vis[i0][i1][j0][j1]) return dp[i0][i1][j0][j1];
        vis[i0][i1][j0][j1] = true;
        int mn = 1e9;
        for (int k = 1; k <= i1-i0; ++k) {
            mn = min(mn, self(self, i0, i0+k-1, j0, j1) + self(self, i0+k, i1, j0, j1));
        }
        for (int k = 1; k <= j1-j0; ++k) {
            mn = min(mn, self(self, i0, i1, j0, j0+k-1) + self(self, i0, i1, j0+k, j1));
        }
        return dp[i0][i1][j0][j1] = mn + sum(i0, i1, j0, j1);
    };
    cout << solve(solve, 0, n-1, 0, m-1) << "\n";
}

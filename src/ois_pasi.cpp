#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 102;
static constexpr LL INF = 1e18;

static constexpr array<int, 4> dx{ 1, 0,-1, 0};
static constexpr array<int, 4> dy{ 0, 1, 0,-1};

int main() {
    int n; cin >> n;
    int m; cin >> m;
    int x; cin >> x;
    int y; cin >> y;
    LL k; cin >> k;

    static LL g[N][N]{};
    static LL neb[N][N]{};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
            for (int dir = 0; dir < 4; ++dir) {
                int ii = i+dx[dir];
                int jj = j+dy[dir];
                neb[ii][jj] = max(neb[ii][jj], g[i][j]);
            }
        }
    }

    vector<vector<LL>> dp(N, vector<LL>(N, -INF));
    vector<vector<LL>> prv;
    dp[x][y] = 0;

    LL ans = 0;
    for (int d = 1; d < N*N && d <= k/2; ++d) {
        prv = dp;
        dp.assign(N, vector<LL>(N, -INF));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                LL src = -INF;
                for (int dir = 0; dir < 4; ++dir) {
                    int ii = i+dx[dir];
                    int jj = j+dy[dir];
                    if (ii < 1 || n < ii) continue;
                    if (jj < 1 || m < jj) continue;
                    src = max(src, prv[ii][jj]);
                }
                dp[i][j] = src + g[i][j];
                if (k/2 == d) {
                    ans = max(ans, 2*dp[i][j] - g[i][j]);
                } else if (k/2 >= N*N) {
                    ans = max(ans, 2*dp[i][j] - g[i][j] + (LL)(k/2 - d)*(g[i][j] + neb[i][j]));
                }
            }
        }
    }

    cout << ans << "\n";
}

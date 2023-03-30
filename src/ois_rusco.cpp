#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;

static constexpr int N{1818};

static constexpr int dx[]{1, 0,-1, 0};
static constexpr int dy[]{0, 1, 0,-1};

static int g[N][N];
static int dp[N][N];
static array<int, 2> jj[N][N];
static array<int, 2> d[N][N];
static bool flow[N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    int m; cin >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dp[i+1][j] < dp[i][j] + g[i+1][j]) {
                dp[i+1][j] = dp[i][j] + g[i+1][j];
                jj[i+1][j] = {i, j};
            }
            if (dp[i][j+1] < dp[i][j] + g[i][j+1]) {
                dp[i][j+1] = dp[i][j] + g[i][j+1];
                jj[i][j+1] = {i, j};
            }
        }
    }
    array<int, 2> cur{n-1, m-1};
    while (cur[0] || cur[1]) {
        flow[cur[0]][cur[1]] = 1;
        cur = jj[cur[0]][cur[1]];
    }
    flow[0][0] = flow[n-1][m-1] = 0;

    int ans = dp[n-1][m-1];

    queue<array<int, 3>> Q; // {i, j, from_flow}
    Q.push({0, 0, 0});
    while (!Q.empty()) {
        auto [i, j, from_flow] = Q.front();
        Q.pop();
        if (i == n-1 && j == m-1) continue;
        if (!flow[i][j]) {
            for (int k = 0; k < 2; ++k) {
                int ii = i + dx[k];
                int jj = j + dy[k];
                if (ii >= n || jj >= m) continue;
                if (d[ii][jj][0] < d[i][j][from_flow] + g[ii][jj]) {
                    d[ii][jj][0] = d[i][j][from_flow] + g[ii][jj];
                    Q.push({ii, jj, 0});
                }
            }
        } else if (flow[i][j]) {
            for (int k = 0; k < 4; ++k) {
                int ii = i + dx[k];
                int jj = j + dy[k];
                if (ii < 0 || ii >= n || jj < 0 || jj >= m) continue;
                if (flow[ii][jj] && k < 2) continue;    // l'arco e' saturo
                if (!from_flow && k < 2) continue;      // l'arco interno a (ii,jj) e' saturo
                if (!flow[ii][jj] && k >= 2) continue;  // l'arco non esiste
                int delta = (flow[ii][jj] ? -g[i][j] : g[ii][jj]);
                if (d[ii][jj][1] < d[i][j][from_flow] + delta) {
                    d[ii][jj][1] = d[i][j][from_flow] + delta;
                    Q.push({ii, jj, 1});
                }
            }
        }
    }

    ans += d[n-1][m-1][0];
    cout << ans << "\n";
}

/*
4 5
0 2 1 0 0
1 0 1 5 0
1 1 6 1 2
0 0 1 1 0
*/

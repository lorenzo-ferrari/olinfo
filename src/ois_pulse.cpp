#include "bits/stdc++.h"
using namespace std;

static constexpr int N = 500;
static constexpr int INF = 1e9;

int main() {
    int n; cin >> n;
    int p; cin >> p;
    vector<int> x(p), y(p), r(p);
    for (int i = 0; i < p; ++i) {
        cin >> x[i] >> y[i] >> r[i];
        --x[i], --y[i];
    }

    auto good = [&](int i, int j) -> bool {
        return 0 <= i && i < n && 0 <= j && j < n;
    };

    static bool bad[N][N][60]{};
    for (int i = 0; i < p; ++i) {
        for (int t = 0; t < 60; ++t) {
            int c = t % r[i];
            for (int dx = -c; dx <= c; ++dx) {
                for (int dy = -(c - abs(dx)); dy <= c - abs(dx); ++dy) {
                    int xx = x[i] + dx;
                    int yy = y[i] + dy;
                    if (good(xx, yy)) {
                        bad[xx][yy][t] = true;
                    }
                }
            }
        }
    }

    static int dist[N][N][60];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int t = 0; t < 60; ++t)
                dist[i][j][t] = INF;
    
    static constexpr array<int, 5> dx{0, 0, 1, 0,-1};
    static constexpr array<int, 5> dy{0, 1, 0,-1, 0};

    queue<array<int, 3>> Q;
    Q.push({0, 0, 0});
    dist[0][0][0] = 0;
    while (!Q.empty()) {
        auto [i, j, t] = Q.front();
        Q.pop();

        int nt = (t + 1) % 60;
        for (int k = 0; k < 5; ++k) {
            int ii = i + dx[k];
            int jj = j + dy[k];
            if (!good(ii, jj) || bad[ii][jj][nt]) continue;
            if (dist[ii][jj][nt] == INF) {
                dist[ii][jj][nt] = dist[i][j][t] + 1;
                Q.push({ii, jj, nt});
            }
        }
    }

    int ans = INF;
    for (int t = 0; t < 60; ++t) {
        ans = min(ans, dist[n-1][n-1][t]);
    }
    cout << ans << "\n";
}

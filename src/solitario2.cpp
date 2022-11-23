#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

static constexpr size_t N = 16;

static constexpr int d[12][3][2]{
    {{-1,-1},{ 0, 0},{ 1, 1}},
    {{-1, 0},{ 0, 0},{ 1, 0}},
    {{-1, 1},{ 0, 0},{ 1,-1}},
    {{ 0, 1},{ 0, 0},{ 0,-1}},
    {{-2,-2},{-1,-1},{ 0, 0}},
    {{-2, 0},{-1, 0},{ 0, 0}},
    {{-2, 2},{-1, 1},{ 0, 0}},
    {{ 0, 2},{ 0, 1},{ 0, 0}},
    {{ 2, 2},{ 1, 1},{ 0, 0}},
    {{ 2, 0},{ 1, 0},{ 0, 0}},
    {{ 2,-2},{ 1,-1},{ 0, 0}},
    {{ 0,-2},{ 0,-1},{ 0, 0}}
};


int n, m, cnt, ans;
static bool g[N][N];
static int fr[N*N];
int t = 0;

static bool ok(int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
}

static bool tris(int x) {
    int i = x/N;
    int j = x%N;
    if (!g[i][j]) return false;
    for (int _ = 0; _ < 12; ++_) {
        auto dd = d[_];
        if (ok(i+dd[0][0],j+dd[0][1]) and
            ok(i+dd[1][0],j+dd[1][1]) and
            ok(i+dd[2][0],j+dd[2][1]) and
            g[i+dd[0][0]][j+dd[0][1]] and
            g[i+dd[1][0]][j+dd[1][1]] and
            g[i+dd[2][0]][j+dd[2][1]]) {
            return true;
        }
    }
    return false;
}

static void solve(int i) {
    if (i && tris(fr[i-1]) || (cnt + (t - i) - (t - i)/3 <= ans)) return;
    if (i == t) {
        ans = max(ans, cnt);
    } else {
        g[fr[i]/N][fr[i]%N] = 1;
        ++cnt;
        solve(i+1);
        g[fr[i]/N][fr[i]%N] = 0;
        --cnt;
        solve(i+1);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x; cin >> x;
            if (!x) {
                fr[t++] = i*N + j;
            } else {
                g[i][j] = true;
            }
        }
    }
    solve(0);
    cout << ans << "\n";
}

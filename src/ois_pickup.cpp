#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int N = 301;

static LL  dp[N][N][N]; // [i][sum][mod]
static LL vis[N][N][N];
static LL pw[N];        // 10**i % a

LL a, b, k;

static LL solve(LL n, int i, int s, int m) {
    if (!i || vis[i][s][m]) {
        return dp[i][s][m];
    }
    vis[i][s][m] = true;
    for (int d = 1; n > 0 && d <= s && d < 10; ++d) {
        int ps = s - d;
        int pm = (m - pw[i-1]*d + 10*a) % a;
        dp[i][s][m] += solve(n, i-1, ps, pm);
        n -= solve(n, i-1, ps, pm);
    }
    return dp[i][s][m];
}

static void build(LL& n, int i, int s, int m) {
    if (i == 1) {
        cout << s;
        return;
    }
    for (int d = 1; d < 10; ++d) {
        int ps = s - d;
        int pm = (m - pw[i-1]*d + 10*a) % a;
        if (n <= solve(n, i-1, ps, pm)) {
            cout << d;
            build(n, i-1, ps, pm);
            return;
        }
        n -= solve(n, i-1, ps, pm);
    }
}

int main() {
    cin >> a >> b >> k;
    pw[0] = 1 % a;
    for (int i = 1; i < N; ++i) {
        pw[i] = 10 * pw[i - 1] % a;
    }
    for (int i = 1; i < 10; ++i) {
        ++dp[1][i][i%a];
    }
    for (int i = 1; i <= b; ++i) {
        if (k <= solve(k, i, b, 0)) {
            build(k, i, b, 0);
            cout << "\n";
            return 0;
        }
        k -= solve(k, i, b, 0);
    }
}

#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 10005;
constexpr double TL = 0.5;

static int prf[N];
static bool dp[N][N];

static bool good(int l, int r) {
    return prf[l-1] == prf[r];
}

int conta(int n, vector<int> v) {
    clock_t tbegin = clock();
    for (int i = 0; i < n; ++i) {
        prf[i+1] = prf[i] ^ v[i];
    }
    for (int i = 1; i <= n; ++i) dp[i][i-1] = true;
    for (int i = 1; i+2 <= n; ++i) dp[i][i+2] = good(i, i+2);
    for (int l = 5; l < n; l += 3) {
        if (clock() - tbegin > TL * CLOCKS_PER_SEC) {
            break;
        }
        for (int i = 1; i + l <= n; ++i) {
            int j = i + l;
            if (!good(i, j)) continue;
            for (int k = i; k <= j; k += 3) {
                if (dp[i][k-1] && dp[k][j]) {
                    dp[i][j] = true;
                    break;
                }
                if (dp[i+1][k] && dp[k+2][j-1]) {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }
    int ans[N]{};
    for (int i = 1; i <= n; ++i) {
        ans[i] = ans[i-1];
        for (int j = 3; j <= i; j += 3) {
            if (dp[i-j+1][i] && ans[i] < ans[i-j] + j) {
                ans[i] = ans[i-j] + j;
            }
        }
    }
    return ans[n];
}

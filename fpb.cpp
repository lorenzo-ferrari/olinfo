#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> dp(n + 1, vector<int> (k + 1));
    vector<vector<int>> dpp(n + 1, vector<int> (k + 1));
    
    dp[0][0] = dpp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i][0] = 1;
        dpp[i][0] = dpp[i - 1][0] + dp[i][0];
    }
    for (int j = 1; j <= k; ++j) {
        dp[j][j] = dpp[j][j] = 1;
        for (int i = j + 1; i <= n; ++i) {
            dp[i][j] = (dp[i - 1][j] + dpp[i - 2][j - 1] + dp[i - 1][j - 1]) % mod;
            dpp[i][j] = (dpp[i - 1][j] + dp[i][j]) % mod;
        }
    }

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    int ans = 0;
    vector<int> gcd(n + 1); gcd[n] = 1;
    vector<int> nxt(n + 1); nxt[n] = n;
    for (int i = n - 1; i >= 0; --i) {
        gcd[i] = a[i];
        int e = i + 1;
        while (a[i] % gcd[e] != 0)
            ++e;
        for (int j = i + 1; j < e; ++j)
            gcd[j] = __gcd(gcd[j], gcd[j - 1]);
        for (int j = e - 1; j >= i; --j)
            nxt[j] = (gcd[j + 1] != gcd[j]) ? j + 1 : nxt[j + 1];
        for (int j = i, jj; j < n; j = nxt[j]) {
            jj = nxt[j];
            for (int kl = 0, kr; kl < k; ++kl) {
                kr = k - 1 - kl;
                ans = (ans + gcd[j] * (dp[i][kl] * (dpp[n-j-1][kr] - (jj < n ? dpp[n-jj-1][kr] : 0) + mod) % mod)) % mod;
            }
        }
    }

    cout << ans << "\n";
}

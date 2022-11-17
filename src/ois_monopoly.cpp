#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<LL> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    static constexpr LL INF = 1e15;
    vector<LL> dp(n, -INF); dp[0] = 0;
    vector<LL> prv(n);
    while (k--) {
        prv = dp;
        dp.assign(n, -INF);
        for (int i = 0; i < n; ++i) {
            for (int a = 3; a < 12; ++a) {
                int ii = (i + a) % n;
                dp[ii] = max(dp[ii], prv[i] + v[ii]);
            }
            for (int a = 2; a <= 12; a += 2) {
                int ii = (i + a) % n;
                for (int b = 3; b < 12; ++b) {
                    int jj = (ii + b) % n;
                    dp[jj] = max(dp[jj], prv[i] + v[ii] + v[jj]);
                }
            }
            for (int a = 2; a <= 12; a += 2) {
                for (int b = 2; b <= 12; b += 2) {
                    int ii = (i  + a) % n;
                    int jj = (ii + b) % n;
                    for (int c = 2; c <= 12; ++c) {
                        int kk = (jj + c) % n;
                        dp[kk] = max(dp[kk], prv[i] + v[ii] + v[jj] + v[kk]);
                    }
                }
            }
        }
    }
    cout << *max_element(begin(dp), end(dp)) << "\n";
}

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<LL> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<double> prf(n);      // prf[i] = a[i] - a[i-1]/2 + a[i-2]/4 - ...
    vector<double> sff(n+1);    // sff[i] = a[i] - a[i+1]/2 + a[i+2]/4 - ...
    for (int i = n-1; i >= 0; --i) {
        sff[i] = a[i] - sff[i+1] / 2;
    }
    prf[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prf[i] = a[i] - prf[i-1] / 2;
    }
    auto p = a;
    for (int i = 1; i < n; ++i) {
        p[i] += p[i-1];
    }
    auto sum = [&](int l, int r) -> LL {
        return p[r] - (l ? p[l-1] : 0);
    };
    auto gsum = [&](int l, int r, bool from_left) -> double {
        if (from_left) {
            if ((r - l) & 1) {
                return sff[l] - sff[r+1] / pow(2, r-l+1);
            } else {
                return sff[l] + sff[r+1] / pow(2, r-l+1);
            }
        } else {
            if (l == 0) {
                return prf[r];
            }
            if ((r - l) & 1) {
                return prf[r] - prf[l-1] / pow(2, r-l+1);
            } else {
                return prf[r] + prf[l-1] / pow(2, r-l+1);
            }
        }
    };
    // dp[i][j][0] : william
    // dp[i][j][1] : giorgio
    vector<vector<array<LL, 2>>> dp(n, vector<array<LL, 2>>(n));
    vector<vector<array<char, 2>>> jj(n, vector<array<char, 2>>(n));
    for (int i = 0; i < n; ++i) {
        dp[i][i][0] = dp[i][i][1] = a[i];
        jj[i][i][0] = jj[i][i][1] = 'L';
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            int j = i + len - 1;
            // william
            if (dp[i][j-1][1] < dp[i+1][j][1]) {
                dp[i][j][0] = sum(i, j) - dp[i][j-1][1];
                jj[i][j][0] = 'R';
            } else {
                dp[i][j][0] = sum(i, j) - dp[i+1][j][1];
                jj[i][j][0] = 'L';
            }
            // giorgio
            double suml = gsum(i, j, 1);
            double sumr = gsum(i, j, 0);
            if (suml > sumr + 1e-9) {
                dp[i][j][1] = sum(i, j) - dp[i+1][j][0];
                jj[i][j][1] = 'L';
            } else if (sumr > suml + 1e-9) {
                dp[i][j][1] = sum(i, j) - dp[i][j-1][0];
                jj[i][j][1] = 'R';
            } else {
                dp[i][j][1] = sum(i, j) - max(dp[i+1][j][0], dp[i][j-1][0]);
                jj[i][j][1] = "LR"[dp[i+1][j][0] < dp[i][j-1][0]];
            }
        }
    }
    int l = 0, r = n-1, c = 0;
    for (int i = 0; i < n; ++i) {
        cout << jj[l][r][c];
        if (jj[l][r][c] == 'L') {
            ++l;
        } else {
            --r;
        }
        c ^= 1;
    }
    cout << "\n";
}

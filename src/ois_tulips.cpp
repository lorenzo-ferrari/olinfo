#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<LL> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<LL> prv(n);
    vector<LL> dp(n);
    for (int i = 0; i < n; ++i) { // k = 1
        if (i == 0) {
            dp[i] = a[i];
        } else {
            dp[i] = min(dp[i - 1], a[i]);
        }
    }
    for (int kk = 2; kk <= k; ++kk) {
        prv = dp;
        stack<array<LL, 2>> st;
        for (int i = kk - 1; i < n; ++i) {
            LL mx_prv = prv[i - 1];
            while (!st.empty() && a[st.top()[0]] >= a[i]) {
                mx_prv = max(mx_prv, st.top()[1]);
                st.pop();
            }
            dp[i] = a[i] + mx_prv;
            if (!st.empty()) {
                dp[i] = max(dp[i], dp[st.top()[0]]);
            }
            st.push({i, mx_prv});
        }
    }

    cout << dp[n - 1] << "\n";
}

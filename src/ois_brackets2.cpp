#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int s = accumulate(begin(a), end(a), 0) / 2;

    vector<vector<int>> dp(n+1, vector<int>(s+1));
    dp[n][0] = true;
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= s; ++j) {
            if (j + a[i] <= s) dp[i][j + a[i]] |= dp[i + 1][j];
            if (j - a[i] >= 0) dp[i][j - a[i]] |= dp[i + 1][j];
        }
    }
    if (!dp[0][0]) {
        cout << "-1";
    } else {
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            if (cur + a[i] <= s && dp[i + 1][cur + a[i]]) {
                cout << string(a[i], '(');
                cur += a[i];
            } else {
                cout << string(a[i], ')');
                cur -= a[i];
            }
        }
    }
    cout << "\n";
}

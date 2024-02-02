#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    int m; cin >> m;
    set<array<int, 2>> s;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        s.insert({a, b});
    }
    vector<int> dp(n, -1e9);
    for (int i = 0; i < n; ++i) {
		if (t[i] == k+1) continue;
		if (i <= 1) dp[i] = 1;
        if (i >= 1 && s.count({t[i - 1], t[i]})) dp[i] = max(dp[i], 1 + dp[i - 1]);
        if (i >= 2 && s.count({t[i - 2], t[i]})) dp[i] = max(dp[i], 1 + dp[i - 2]);

    }

    cout << max({dp[n - 1], dp[n - 2], 0}) << "\n";
}

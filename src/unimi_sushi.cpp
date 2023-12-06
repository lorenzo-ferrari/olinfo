#include "bits/stdc++.h"
using namespace std;

#define all(x) begin(x),end(x)

int main() {
    int n; cin >> n;
    vector<array<int, 3>> items(n);
    vector<int> z;
    for (int i = 0, a, b, c; i < n; ++i) {
        cin >> a >> b >> c;
        z.push_back(a);
        z.push_back(a + c);
        items[i] = {a, a + c, b};
    }
    sort(all(z));
    z.erase(unique(all(z)), end(z));
    for (auto& [l, r, _] : items) {
        l = lower_bound(all(z), l) - begin(z);
        r = lower_bound(all(z), r) - begin(z);
    }

    int T = z.size();
    vector<vector<int>> ends_at(T);
    for (int i = 0; i < n; ++i) {
        ends_at[items[i][1]].push_back(i);
    }

    vector<long long> dp(T);
    for (int i = 1; i < T; ++i) {
        dp[i] = dp[i - 1];
        for (int j : ends_at[i]) {
            dp[i] = max(dp[i], items[j][2] + dp[items[j][0]]);
        }
    }

    cout << dp[T - 1] << "\n";
}

#include <bits/stdc++.h>
using namespace std;

int Gira(int n, int freccia[]) {
    vector<int> p0(n+1), p1(n+1);
    for (int i = 0; i < n; ++i) p0[i+1] = p0[i] + (freccia[i] == 0);
    for (int i = 0; i < n; ++i) p1[i+1] = p1[i] + (freccia[i] == 1);
    auto c0 = [&](int l, int r) -> int { return p0[r] - p0[l]; };
    auto c1 = [&](int l, int r) -> int { return p1[r] - p1[l]; };
    vector<int> dp(n+1, 1e9); dp[0] = 0;
    for (int i = 2; i <= n; i += 2) {
        for (int l = i/2; l > 0; --l) {
            dp[i] = min(dp[i], dp[i - 2*l] + c0(i - l, i) + c1(i - 2*l, i - l));
        }
    }
    return dp.back();
}

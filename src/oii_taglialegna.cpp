#include "bits/stdc++.h"
using namespace std;
using LL = long long;

void Abbatti(int, int);

void Pianifica(int n, int h[]) {
    vector<int> dx(n), sx(n);
    sx[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        while (j >= 0 && i - j < h[i]) {
            j = sx[j] - 1;
        }
        sx[i] = j + 1;
    }
    dx[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; --i) {
        int j = i+1;
        while (j < n && j - i < h[i]) {
            j = dx[j] + 1;
        }
        dx[i] = j - 1;
    }

    vector<array<int, 2>> dp(n, {1<<30, -1});
    stack<array<int, 3>> st;    // {dx[i], dp[i-1], (n+i)} catena
    dp[0] = {1, n};             // {dp[i], cosa taglio, +n se dx}
    st.push({dx[0], 1, n});
    for (int i = 1; i < n; ++i) {
        // cadi a sx
        if (sx[i] == 0) {
            dp[i] = {1, i};
        } else {
            dp[i] = {1 + dp[sx[i] - 1][0], i};
        }

        if (!st.empty() && st.top()[0] < i) {
            st.pop();
        }
        if (!st.empty()) {
            dp[i] = min(dp[i], {st.top()[1], st.top()[2]});
        }
        if (!st.empty() && st.top()[0] == dx[i] && st.top()[1] > 1 + dp[i - 1][0]) {
            st.pop();
        }
        if (st.empty() || st.top()[1] > 1 + dp[i - 1][0]) {
            st.push({dx[i], 1 + dp[i - 1][0], i+n});
        }
    }

    int cur = n - 1;
    while (cur != -1) {
        int i = dp[cur][1] % n;
        int d = dp[cur][1] / n;
        Abbatti(i, d);
        if (d == 0) {
            cur = sx[i] - 1;
        } else {
            cur = i - 1;
        }
    }
}

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

long long bfs(int n, LL k, vector<int> p, vector<int> f) {
    LL ans = 0;
    LL sum = 0;
    priority_queue<int> Q;
    vector<array<LL, 2>> v(n);
    for (int i = 0; i < n; ++i) {
        v[i] = {p[i], f[i]};
    }
    sort(begin(v), end(v), greater<array<LL, 2>>());
    for (auto [pp, ff] : v) {
        sum += ff;
        Q.push(ff);
        while (!Q.empty() && (sum > k || Q.top() >= pp)) {
            sum -= Q.top();
            Q.pop();
        }
        ans = max(ans, pp * (int)Q.size() - sum);
    }
    return ans;
}

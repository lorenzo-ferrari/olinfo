#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static int try_swap(int n, vector<int> v, int a, int b) {
    vector<int> tr(10); // key to place
    iota(begin(tr), end(tr), 0);
    auto costs = [&]() -> vector<int> {
        vector<int> ans(n);
        for (int cur = 0, i = 0; i < n; ++i) {
            assert(0 <= v[i] && v[i] <= 9);
            ans[i] = abs(cur - tr[v[i]]);
            cur = tr[v[i]];
        }
        return ans;
    };
    auto c0 = costs();
    swap(tr[a], tr[b]);
    auto c1 = costs(); c1.push_back(0);
    for (int i = 1; i < n; ++i) c0[i] += c0[i-1];
    for (int i = n-1; i >= 0; --i) c1[i] += c1[i+1];
    int ans = min(c0[n-1], c1[0]);
    for (int c = 1; c < n; ++c) {
        if (v[c-1] == a || v[c-1] == b) {
            int cur = c0[c-1] + c1[c+1];
            int pp = v[c-1];
            int pn = tr[v[c]];
            cur += abs(pp - pn);
            ans = min(ans, cur);

        } else {
            int cur = c0[c-1] + c1[c];
            ans = min(ans, cur);
        }
    }
    return ans;
}

static void solve() {
    string s; cin >> s;
    int n = s.size();
    vector<int> v;
    for (char c : s) {
        v.push_back(c - '0');
    }
    int ans = 0;
    for (int cur = 0, i = 0; i < n; ++i) {
        ans += abs(v[i] - cur);
        cur = v[i];
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = i+1; j < 10; ++j) {
            ans = min(ans, try_swap(n, v, i, j));
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

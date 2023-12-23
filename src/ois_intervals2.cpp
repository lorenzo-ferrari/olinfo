#include "bits/stdc++.h"
using namespace std;
using LL = long long;

struct Segment {
    int n;
    vector<int> t;
    Segment(int n) : n(n), t(2 * n) {}
    void add(int p, int v) {
        for (t[p += n] += v; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    int query(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
};

void solve() {
    int n; cin >> n;
    vector<LL> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q; cin >> q;
    vector<array<int, 3>> qq(q);
    for (int i = 0; i < q; ++i) {
        cin >> qq[i][0] >> qq[i][1];
        --qq[i][0], --qq[i][1];
        qq[i][2] = i;
    }
    sort(begin(qq), end(qq), greater<array<int,3>>());
    vector<int> ans(q);
    Segment st(n);
    auto process = [&](int l) -> void {
        for (int j = 1; l + j <= n; ++j) {
            if (a[l + j - 1] % j == 0) {
                st.add(l + j - 1, 1);
            } else {
                break;
            }
        }
    };
    int cl = n;
    for (auto [l, r, i] : qq) {
        while (cl != l) {
            --cl;
            process(cl);
        }
        ans[i] = st.query(l, r+1);
    }
    for (int i : ans) {
        cout << i << "\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

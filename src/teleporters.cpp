#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

static constexpr int N = 2e6 + 42;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m; cin >> m;
    vector<array<int, 2>> adj;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        adj.push_back({a, b});
        adj.push_back({b, a});
    }
    sort(begin(adj), end(adj));
    int last = adj.back()[0];
    auto find_next = [&](int i) -> int {
        auto it = upper_bound(begin(adj), end(adj), array<int,2>{i, N});
        return (*it)[1];
    };
    int ans = 0;
    bitset<N> vis;
    for (int cur = 0; cur != last;) {
        vis[cur] = true;
        cur = find_next(cur);
        ++ans;
    }
    vector<int> cyc;
    for (auto [a, b] : adj) {
        if (vis[a] || a == last) continue;
        int len = 0;
        while (!vis[a]) {
            vis[a] = true;
            a = find_next(a);
            ++len;
        }
        cyc.push_back(len);
    }
    sort(begin(cyc), end(cyc));
    while (m--) {
        if (!cyc.empty()) {
            ans += 2 + cyc.back();
            cyc.pop_back();
        } else {
            ans += 1;
            cyc.push_back(1);
        }
    }
    cout << ans << "\n";
}


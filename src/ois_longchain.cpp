#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < n - 1; ++i) {
        cin >> a >> b;
        --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto works = [&](int x) -> bool {
        int root = 0;
        auto solve = [&](auto&& self, int v, int p) -> pair<bool, int> {
            // how long can the root->parent path be in a valid partition?
            // if no valid partition exists, return false
            multiset<int> d;
            for (int u : adj[v]) {
                if (u == p) continue;
                auto [b, l] = self(self, u, v);
                if (!b) return {false, 0};
                d.insert(l + 1);
            }
            if (d.empty()) {
                return {true, 0};
            }
            if (v == root) {
                if (d.size() % 2 == 1) {
                    d.insert(0);
                }
                while (!d.empty()) {
                    int mn = *begin(d);
                    int mx = *rbegin(d);
                    if (mn + mx < x) {
                        return {false, 0};
                    }
                    d.erase(begin(d));
                    d.erase(prev(end(d)));
                }
                return {true, 0};
            } else {
                int ans = *rbegin(d);
                d.erase(prev(end(d)));
                if (d.size() % 2 == 1) {
                    d.insert(0);
                }
                while (!d.empty()) {
                    auto a = begin(d);
                    auto b = d.lower_bound(x - *a);
                    if (a == b) ++b;
                    if (b != end(d)) {
                        d.erase(a);
                        d.erase(b);
                    } else if (*a + ans >= x) {
                        d.erase(a);
                        ans = *prev(end(d));
                        d.erase(prev(end(d)));
                    } else if (ans + *prev(end(d)) >= x) {
                        d.insert(ans);
                        ans = *a;
                        d.erase(a);
                    } else {
                        return {false, 0};
                    }
                }
                return {true, ans};
            }
        };
        return solve(solve, root, -1).first;
    };

    int l = 1, r = n;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (works(m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << "\n";
}

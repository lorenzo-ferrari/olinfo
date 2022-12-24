#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct AncSum {
    int n;
    vector<int> in, out;
    vector<LL> t;
    AncSum(int n, vector<vector<int>> adj) : n(n) {
        in.resize(n);
        out.resize(n);
        int tt = 0;
        auto dfs = [&](auto&& self, int v, int p) -> void {
            in[v] = tt;
            for (int u : adj[v]) {
                if (u == p) continue;
                self(self, u, v);
            }
            out[v] = ++tt;
        };
        dfs(dfs, 0, -1);
        t.assign(2*n, 0);
    }
    void add_range(int l, int r, LL v) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) t[l++] += v;
            if (r & 1) t[--r] += v;
        }
    }
    LL qry(int v) {
        LL ans = 0;
        for (v += n; v > 0; v >>= 1) {
            ans += t[v];
        }
        return ans;
    }
    void inc_node(int v, int x) {
        add_range(in[v], out[v], x);
    }
    LL ask_anc(int v) {
        return qry(out[v]-1);
    }
};

int main() {
    int n; cin >> n;
    vector<vector<int>> aa(n);
    for (int i = 1; i < n; ++i) {
        int p; cin >> p; --p;
        aa[p].push_back(i);
    }
    int m; cin >> m;
    vector<vector<int>> bb(m);
    for (int i = 1; i < m; ++i) {
        int p; cin >> p; --p;
        bb[p].push_back(i);
    }
    int k; cin >> k;
    vector<vector<array<LL, 2>>> e(n);
    for (int i = 0, x, y, c; i < k; ++i) {
        cin >> x >> y >> c; --x, --y;
        e[x].push_back({y, c});
    }
    int q; cin >> q;
    vector<vector<array<LL, 2>>> qq(n);
    for (int i = 0, x, y; i < q; ++i) {
        cin >> x >> y; --x, --y;
        qq[x].push_back({y, i});
    }

    AncSum anc(m, bb);

    vector<LL> ans(q);
    auto dfs = [&](auto&& self, int v, int p) -> void {
        for (auto [y, c] : e[v]) anc.inc_node(y, c);
        for (auto [y, t] : qq[v]) {
            ans[t] = anc.ask_anc(y);
        }
        for (int u : aa[v]) {
            if (u == p) continue;
            self(self, u, v);
        }
        for (auto [y, c] : e[v]) anc.inc_node(y, -c);
    };
    dfs(dfs, 0, -1);

    for (LL i : ans) {
        cout << i << "\n";
    }
}

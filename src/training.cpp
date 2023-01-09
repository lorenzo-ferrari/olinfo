/*
 *  First of all, bicolor the tree. Any admissible unpaved edges must connect
 *  vertexes of the same colour.
 *
 *  Consider each unpaved edge (a, b) the path a->...->b on the tree. A simple
 *  even cycles exist iff an edge is traversed by two or more paths.
 *
 *  Find the maximal sum of a edge-disjoint subset of the given paths.
 *
 *  dp[v][mask] is the maximal sum of edge-disjoint paths in the subtree of v
 *  considering only children in mask
 */

#include <bits/stdc++.h>
using namespace std;

struct Lca {
    static constexpr int LOG = 10;
    int n;
    vector<int> dep;
    vector<vector<int>> up;

    Lca(int _n, const vector<vector<int>>& adj) : n(_n) {
        dep.assign(n, 0);
        up.assign(n, vector<int>(LOG));
        auto dfs = [&](auto&& self, int v, int p) -> void {
            up[v][0] = p;
            for (int u : adj[v]) {
                if (u == p) continue;
                dep[u] = dep[v] + 1;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, 0);
        for (int i = 1; i < LOG; ++i) {
            for (int j = 0; j < n; ++j) {
                up[j][i] = up[up[j][i-1]][i-1];
            }
        }
    }

    int lift(int v, int k) const {
        for (int i = LOG-1; i >= 0; --i) {
            if (k & (1 << i)) {
                v = up[v][i];
            }
        }
        return v;
    }

    vector<int> get_dep() const { return dep; }
    vector<int> get_par() const {
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = up[i][0];
        }
        return ans;
    }

    int operator()(int a, int b) const {
        if (dep[a] > dep[b]) {
            swap(a, b);
        }
        b = lift(b, dep[b] - dep[a]);
        if (a == b) {
            return a;
        }
        for (int i = LOG-1; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }
};

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;
    vector<array<int, 3>> e;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b, c; i < m; ++i) {
        cin >> a >> b >> c; --a, --b;
        if (c) {
            e.push_back({a, b, c});
        } else {
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    Lca lca(n, adj);
    auto dep = lca.get_dep();
    auto par = lca.get_par();
    vector<vector<array<int, 3>>> paths(n);
    for (auto [a, b, c] : e) {
        if ((dep[a] & 1) == (dep[b] & 1)) {
            paths[lca(a, b)].push_back({a, b, c});
        }
    }

    constexpr int K = 10;
    constexpr int all = (1 << K) - 1;

    vector<vector<int>> dp(n, vector<int>(1 << 10));

    auto find_child = [&](int anc, int v) -> int {
        int cur = v;
        int prv = -1;
        while (cur != anc) {
            prv = cur;
            cur = par[cur];
        }
        return prv;
    };
    auto find_id = [&](int v, int u) -> int {
        return find(begin(adj[v]), end(adj[v]), u) - begin(adj[v]);
    };
    auto calc = [&](int anc, int v) -> int {
        int ans = dp[v][all];
        int cur = par[v];
        int prv = v;
        while (prv != anc) {
            ans += dp[cur][all ^ (1 << find_id(cur, prv))];
            prv = cur;
            cur = par[cur];
        }
        return ans;
    };
    auto dfs = [&](auto&& self, int v) -> void {
        for (int u : adj[v]) {
            if (u != par[v]) {
                self(self, u);
            }
        }
        vector<array<int, 2>> items;
        for (auto [a, b, c] : paths[v]) {
            if (a == v || b == v) {
                int end = a ^ b ^ v;
                int u = find_child(v, end);
                int i = find_id(v, u);
                items.push_back({1 << i, calc(u, end) + c});
            } else {
                int aa = find_child(v, a);
                int bb = find_child(v, b);
                int ia = find_id(v, aa);
                int ib = find_id(v, bb);
                int mask = (1 << ia) | (1 << ib);
                int inc = c + calc(aa, a) + calc(bb, b);
                items.push_back({mask, inc});
            }
        }
        for (int u : adj[v]) {
            if (u != par[v]) {
                items.push_back({1 << find_id(v, u), dp[u][all]});
            }
        }
        for (int i = 0; i < K; ++i) {
            items.push_back({1 << i, 0});
        }
        for (int mask = 0; mask < (1 << K); ++mask) {
            for (auto [tmask, w] : items) {
                if ((mask | tmask) == mask) {
                    dp[v][mask] = max(dp[v][mask], dp[v][mask ^ tmask] + w);
                }
            }
        }
    };
    dfs(dfs, 0);

    int ans = 0;
    for (auto [_, __, c] : e) {
        ans += c;
    }
    ans -= dp[0][all];
    
    cout << ans << "\n";
}

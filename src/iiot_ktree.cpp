#include "bits/stdc++.h"
using namespace std;
using LL = long long;

struct nd {
    int sum = 0;
    nd* l = nullptr;
    nd* r = nullptr;
    nd() : sum(0) {}
    nd(int s) : sum(s) {}
};
nd* build(int a, int b) {
    if (b <= a) return nullptr;
    nd* ret = new nd();
    if (b - a != 1) {
        ret->l = build(a, (a+b)/2);
        ret->r = build((a+b)/2, b);
    }
    return ret;
}
nd* inc(nd* old, int a, int b, int pos) {
    nd* ret = new nd(old->sum + 1);
    if (b - a == 1) return ret;
    int m = (a + b) / 2;
    if (pos < m) {
        ret->l = inc(old->l, a, m, pos);
        ret->r = old->r;
    } else {
        ret->l = old->l;
        ret->r = inc(old->r, m, b, pos);
    }
    return ret;
}

void print(nd* n) {
    if (n->l == nullptr) {
        cout << n->sum;
    } else {
        print(n->l);
        cout << " ";
        print(n->r);
    }
}

struct Segtree {
    int n;
    nd* zero;
    Segtree(int _n) {
        for (n = 1; n < _n; n <<= 1);
        zero = build(0, n);
    }
    nd* inc(int pos) {
        return ::inc(zero, 0, n, pos);
    }
    nd* inc(nd* old, int pos) {
        return ::inc(old, 0, n, pos);
    }
};

struct Lca {
    static constexpr int LG = 18;
    int n;
    vector<int> dep;
    vector<array<int, LG>> up;
    Lca(int _n, vector<int> p) : n(_n) {
        dep.assign(n, 0);
        up.assign(n, array<int, LG>{});
        for (int i = 0; i < n; ++i) up[i][0] = p[i];
        for (int i = 1; i < LG; ++i) {
            for (int j = 0; j < n; ++j) {
                up[j][i] = up[up[j][i-1]][i-1];
            }
        }
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[p[i]].push_back(i);
        }
        auto dfs = [&](auto&& self, int v, int p) -> void {
            for (int u : adj[v]) {
                if (u == p) continue;
                dep[u] = dep[v] + 1;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, -1);
    }
    int lift(int v, int k) {
        for (int i = LG-1; i >= 0; --i) {
            if (k & (1 << i)) {
                v = up[v][i];
                k -= 1 << i;
            }
        }
        return v;
    }
    int lca(int a, int b) {
        if (dep[a] > dep[b]) a = lift(a, dep[a] - dep[b]);
        if (dep[b] > dep[a]) b = lift(b, dep[b] - dep[a]);
        for (int i = LG-1; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        if (a == b) return a;
        return up[a][0];
      }
};

int main() {
    int n; cin >> n;
    vector<int> val(n), p(n);
    for (int i = 0; i < n; ++i) cin >> val[i];
    for (int i = 1; i < n; ++i) { cin >> p[i]; --p[i]; }

    Lca lca(n, p);

    const auto& dep = lca.dep;
    vector<int> o(n-1);  
    iota(begin(o), end(o), 1);
    sort(begin(o), end(o), [&](int i, int j){ return dep[i] < dep[j]; });

    Segtree seg(n+1);
    vector<nd*> roots(n);
    roots[0] = seg.inc(val[0]);
    for (int i : o) {
        roots[i] = seg.inc(roots[p[i]], val[i]);
    }

    int q; cin >> q;
    for (int v, u, k; q--;) {
        cin >> v >> u >> k; --v, --u;
        int l = lca.lca(v, u);
        nd* rv = roots[v];
        nd* ru = roots[u];
        nd* rl = roots[l];
        int a = 0, b = seg.n;
        while (b - a != 1) {
            int m = (a + b) / 2;
            int r = rv->r->sum + ru->r->sum - 2 * rl->r->sum + (m <= val[l] && val[l] < b);
            if (r >= k) {
                a = m;
                rv = rv->r;
                ru = ru->r;
                rl = rl->r;
            } else {
                k -= r;
                b = m;
                rv = rv->l;
                ru = ru->l;
                rl = rl->l;
            }
        }
        cout << a << "\n";
    }
}

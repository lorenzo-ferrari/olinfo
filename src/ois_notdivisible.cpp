#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int N = 1e5 + 1;
static constexpr int LG = 18;
static constexpr int BS = 512;

struct Lca {
    int n;
    vector<int> dep;
    vector<array<int, LG>> up;
    Lca(const vector<vector<int>>& adj) : n(adj.size()) {
        up.resize(n);
        dep.resize(n);
        auto dfs = [&](auto&& self, int v, int p) -> void {
            up[v][0] = p;
            for (int u : adj[v]) {
                if (u == p) continue;
                dep[u] = dep[v] + 1;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, 0);
        for (int i = 1; i < LG; ++i) {
            for (int j = 0; j < n; ++j) {
                up[j][i] = up[up[j][i-1]][i-1];
            }
        }
    }
    int operator()(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        for (int i = 0; i < LG; ++i) {
            if ((dep[b] - dep[a]) & (1 << i)) {
                b = up[b][i];
            }
        }
        if (a == b) return a;
        for (int i = LG-1; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        assert(up[a][0] == up[b][0]);
        return up[a][0];
    }
};

struct Mex {
    int cnt[BS]{};
    int frq[BS*BS]{};
    void insert(int i) {
        cnt[i/BS] += (frq[i] == 0);
        ++frq[i];
    }
    void erase(int i) {
        --frq[i];
        cnt[i/BS] -= (frq[i] == 0);
    }
    int get() {
        int b = 0;
        while (cnt[b] == BS) ++b;
        for (int i = b*BS;; ++i) {
            if (!frq[i]) {
                return i;
            }
        }
        return -1;
    }
};

vector<int> pr;
vector<int> lp(N*LG);

void sieve() {
    for (int i = 2; i < N*LG; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < N*LG; ++j) {
            assert(lp[i * pr[j]] == 0);
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    assert((int)pr.size() > N);
}

int main() {
    sieve();
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        if (lp[v[i]] == v[i]) {
            v[i] = lower_bound(begin(pr), end(pr), v[i]) - begin(pr);
        } else {
            v[i] = -1;
        }
    }
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b; --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int cur = 0;
    vector<int> ord;
    vector<int> st(n), en(n);
    auto dfs = [&](auto&& self, int i, int p) -> void {
        st[i] = cur++;
        ord.push_back(i);
        for (int j : adj[i]) {
            if (j == p) continue;
            self(self, j, i);
        }
        en[i] = cur++;
        ord.push_back(i);
    };
    dfs(dfs, 0, -1);

    // mo's algorithm on trees
    // https://codeforces.com/blog/entry/43230
    Lca lca(adj);
    int q; cin >> q;
    vector<array<int, 4>> qs;
    for (int i = 0, a, b; i < q; ++i) {
        cin >> a >> b; --a, --b;
        if (st[a] > st[b]) swap(a, b);
        int l = lca(a, b);
        if (a == l) {
            qs.push_back({st[a], st[b], -1, i});
        } else {
            qs.push_back({en[a], st[b], st[l], i});
        }
    }
    sort(begin(qs), end(qs), [&](array<int, 4> a, array<int, 4> b){
        if (a[0] / BS != b[0] / BS) return a[0] < b[0];
        if ((a[0] / BS) & 1) return a[1] > b[1];
        return a[1] < b[1];
    });
    Mex mex;
    bitset<N> s{};
    auto toggle = [&](int i) -> void {
        if (v[i] == -1) return;
        if (s[i]) mex.erase(v[i]);
        else mex.insert(v[i]);
        s[i] = !s[i];
    };
    int tl = 0, tr = -1;
    vector<int> ans(q);
    for (auto& [l, r, evt, i] : qs) {
        while (tl < l) toggle(ord[tl++]);
        while (tl > l) toggle(ord[--tl]);
        while (tr < r) toggle(ord[++tr]);
        while (tr > r) toggle(ord[tr--]);
        if (evt != -1) toggle(ord[evt]);
        ans[i] = mex.get();
        if (evt != -1) toggle(ord[evt]);
    }
    for (int i : ans) {
        cout << pr[i] << "\n";
    }
}

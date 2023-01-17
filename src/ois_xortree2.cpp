#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int LG = 30;

class Trie {
    struct node {
        int cnt = 0;
        array<int, 2> to{-1, -1};
        int& operator[](int i) { return to[i]; }
        node(){}
    };

    int root;
    stack<int> mxs;
    vector<int> hist;
    vector<node> nodes;

public:
    Trie() {
        root = new_node();
        mxs.push(0);
    }
    int new_node() {
        nodes.push_back(node());
        return nodes.size() - 1;
    }
    int get(int x) {
        int ans = 0;
        int n = root;
        for (int i = LG-1; i >= 0; --i) {
            int oth = (x >> i) & 1;
            int prf = oth ^ 1;
            if (nodes[n][prf] != -1) {
                n = nodes[n][prf];
                ans |= (1 << i);
            } else {
                n = nodes[n][oth];
            }
        }
        return ans;
    }
    void insert(int x) {
        hist.push_back(x);
        int n = root;
        for (int i = LG-1; i >= 0; --i) {
            ++nodes[n].cnt;
            int bit = (x >> i) & 1;
            if (nodes[n][bit] == -1) {
                nodes[n][bit] = new_node();
            }
            n = nodes[n][bit];
        }
        ++nodes[n].cnt;
        mxs.push(max(mxs.top(), get(x)));
        return;
    }
    void rollback() {
        int x = hist.back();
        hist.pop_back();
        mxs.pop();
        int n = root;
        for (int i = LG-1; i >= 0; --i) {
            --nodes[n].cnt;
            int bit = (x >> i) & 1;
            int nxt = nodes[n][bit];
            assert(nxt != -1); // fsr, fails
            if (nodes[nxt].cnt == 1) {
                nodes[n][bit] = -1;
            }
            n = nxt;
        }
        --nodes[n].cnt;
    }
    int get() const {
        return mxs.top();
    }
};

int main() {
    int n; cin >> n;
    int q; cin >> q;
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0, a, b, c; i < n-1; ++i) {
        cin >> a >> b >> c; --a, --b;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    vector<int> d(n);
    {
        auto dfs = [&](auto&& self, int v, int p) -> void {
            for (auto [u, w] : adj[v]) {
                if (u == p) continue;
                d[u] = d[v] ^ w;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, -1);
    }
    vector<bool> b(n);
    map<int, int> frq;
    set<int> s;
    auto get = [&]() -> int {
        int ans = 0;
        for (int i : s) for (int j : s) {
            ans = max(ans, i ^ j);
        }
        return ans;
    };
    unordered_map<int, int> start;
    vector<array<int, 3>> qs;
    for (int i = 0; i < q; ++i) {
        int x; cin >> x; --x;
        if (b[x]) {
            --frq[d[x]];
            if (!frq[d[x]]) {
                s.erase(d[x]);
                qs.push_back({d[x], start[d[x]], i});
                start.erase(d[x]);
            }
        } else {
            if (!frq[d[x]]) {
                s.insert(d[x]);
                start[d[x]] = i;
            }
            ++frq[d[x]];
        }
        b[x] = !b[x];
    }
    for (auto [key, t] : start) {
        qs.push_back({key, t, q});
    }
    int nq = 1;
    for (; nq < q; nq <<= 1);
    vector<vector<int>> st(2 * nq);
    auto update = [&](auto&& self, int i, int a, int b, int l, int r, int x) -> void {
        if (l <= a && b <= r) st[i].push_back(x);
        else if (r <= a || b <= l) return;
        else {
            self(self, 2*i  , a, (a+b)/2, l, r, x);
            self(self, 2*i+1, (a+b)/2, b, l, r, x);
        }
    };
    for (const auto& [x, l, r] : qs) {
        update(update, 1, 0, nq, l, r, x);
    }
    Trie t;
    vector<int> ans(nq);
    auto dfs = [&](auto&& self, int i, int a, int b) -> void {
        for (int x : st[i]) t.insert(x);
        if (b - a == 1) {
            ans[a] = t.get();
        } else {
            self(self, 2*i  , a, (a+b)/2);
            self(self, 2*i+1, (a+b)/2, b);
        }
        for (int j = 0; j < (int)st[i].size(); ++j) t.rollback();
    };
    dfs(dfs, 1, 0, nq);
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}

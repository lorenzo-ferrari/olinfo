#include "bits/stdc++.h"
using namespace std;
using LL = long long;

vector<int> p, s;
vector<set<pair<int, int>>> adj;

int find(int v) {
    return p[v] == v ? v : p[v] = find(p[v]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (s[a] < s[b]) {
        swap(a, b);
    }
    s[a] += s[b];
    p[b] = a;
    for (auto x : adj[b]) {
        adj[a].insert(x);
    }
    adj[b].clear();
}

void risolvi(int n, int m, int a[], int b[], int h[], LL ans[]) {
    p.resize(n+1);
    s.assign(n+1, 1);
    iota(begin(p), end(p), 0);
    adj.resize(n+1);
    for (int i = 0; i < m; ++i) {
        adj[a[i]].insert({h[i], b[i]});
        adj[b[i]].insert({h[i], a[i]});
    }

    fill(ans+1, ans+n+1, -1);

    LL timer = 0;
    vector<int> cur(n+1);
    auto geth = [&](int v) -> int {
        return cur[find(v)];
    };
    auto increase_level = [&](int v, int l) -> void {
        v = find(v);
        if (cur[v] < l) {
            timer += (LL)s[v] * (l - cur[v]);
            cur[v] = l;
        }
    };
    auto fill = [&](auto&& self, int v, int l) -> void {
        if (l <= geth(v)) {
            return;
        }
        if (ans[v] == -1) {
            ans[v] = timer;
        }
        while (!adj[find(v)].empty() && begin(adj[find(v)])->first < l) {
            auto [hh, u] = *begin(adj[find(v)]);
            adj[find(v)].erase(begin(adj[find(v)]));
            increase_level(v, hh);
            self(self, u, hh);
            merge(v, u);
        }
        increase_level(v, l);
    };
    fill(fill, 1, 1e7);
}

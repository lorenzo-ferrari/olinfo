#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL INF = 1e18;

void brucia(int n, vector<int>& m, vector<int>& b, vector<LL>& t) {
    vector<int> idx(n);
    iota(begin(idx), end(idx), 0);
    sort(begin(idx), end(idx), [&](int i, int j) {
        return m[i] < m[j];
    });

    vector<vector<array<LL, 2>>> adj(n);

    set<array<int, 2>> s;
    map<int, vector<int>> rm;
    for (int i = n-1; i >= 0; --i) {
        int cur = idx[i];
        while (!rm.empty() && prev(end(rm))->first > m[cur]) {
            for (int j : prev(end(rm))->second) {
                s.erase({m[j], j});
            }
            rm.erase(prev(end(rm)));
        }
        auto it = s.lower_bound({m[cur]+1, 0});
        if (it != end(s)) {
            int j = (*it)[1];
            adj[j].push_back({cur, m[j] - m[cur]});
        }
        if (b[cur] < m[cur]) {
            s.insert({m[cur], cur});
            rm[b[cur]].push_back(cur);
        }
    }
    s.clear();
    rm.clear();

    for (int i = 0; i < n; ++i) {
        int cur = idx[i];
        while (!rm.empty() && begin(rm)->first < m[cur]) {
            for (int j : begin(rm)->second) {
                s.erase({m[j], j});
            }
            rm.erase(begin(rm));
        }
        auto it = s.lower_bound({m[cur], 0});
        if (it != begin(s)) {
            int j = (*prev(it))[1];
            adj[j].push_back({cur, m[cur] - m[j]});
        }
        if (m[cur] < b[cur]) {
            s.insert({m[cur], cur});
            rm[b[cur]].push_back(cur);
        }
    }

    t.assign(n, INF);
    priority_queue<array<LL, 2>> Q;

    for (int i = 0; i < n; ++i) {
        if (m[i] == m[0]) {
            Q.push({0, i});
            t[i] = 0;
        }
    }
    while (!Q.empty()) {
        int v = Q.top()[1];
        int d =-Q.top()[0];
        Q.pop();
        if (d > t[v]) {
            continue;
        }
        for (auto [u, w] : adj[v]) {
            if (t[u] > t[v] + w) {
                t[u] = t[v] + w;
                Q.push({-t[u], u});
            }
        }
    }

    for (int i = 0; i != n; ++i) {
        if (t[i] == INF) {
            t[i] = -1;
        }
    }
}

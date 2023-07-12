#include "bits/stdc++.h"
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
using namespace std;
using LL = long long;

static constexpr int nn = 2002;
static constexpr int src = 0;
static constexpr int snk = nn - 1;
static array<int, nn> par;
static array<array<int, nn>, nn> o, c;
static array<vector<array<int, 2>>, nn> adj;

static int treshold;

static void add_edge(int v, int u, int w) {
    adj[v].push_back({u, w});
    adj[u].push_back({v, w});
    o[v][u] = 1;
};

// dfs ricorsiva a blocchi decisamente non per lamerare
static int g = 0;
static constexpr int STEP = 512;
static array<array<int, 2>, nn * STEP> st;
static bool dfs() {
    fill(begin(par), end(par), -1);
    g = 0;
    st[g++] = {src, 0};
    while (g) {
        auto [v, i] = st[--g];
        if (adj[v][i][1] < treshold) continue;
        if (i+STEP < (int)adj[v].size()) {
            st[g++] = {v, i+STEP};
        }
        for (int d = 0; d < STEP && i+d != (int)adj[v].size(); ++d) {
            int u = adj[v][i+d][0];
            int w = adj[v][i+d][1];
            if (w < treshold) break;
            if (par[u] == -1 && c[v][u]) {
                par[u] = v;
                if (u == snk) {
                    return true;
                }
                st[g++] = {u, 0};
            }
        }
    }
    return false;
}

static int flow;
static int maxflow(int treshold) {
    if (treshold > ::treshold) {
        flow = 0;
        c = o;
    }
    ::treshold = treshold;
    while (dfs()) {
        ++flow;
        int cur = snk;
        while (cur != src) {
            int prv = par[cur];
            --c[prv][cur];
            ++c[cur][prv];
            cur = prv;
        }
    }

    return flow;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> all;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        cin >> a[i][j];
        all.push_back(a[i][j]);
    }
    sort(begin(all), end(all));
    all.erase(unique(begin(all), end(all)), end(all));

    { // build
        for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
            add_edge(i+1, j+1+n, a[i][j]);
        }
        for (int i = 1; i <= n; ++i) add_edge(src, i, 1e9);
        for (int i = 1; i <= n; ++i) add_edge(i+n, snk, 1e9);
        c = o;
        for (auto& nb : adj) {
            sort(begin(nb), end(nb), [](array<int, 2> a, array<int, 2> b){
                    return a[1] > b[1];
            });
        }
    }

    int l = 0;
    int r = all.size();
    while (r - l > 1) {
        int m = (l + r) / 2;

        if (maxflow(all[m]) == n) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << all[l] << "\n";
}

// https://training.olinfo.it/#/task/islands/statement

/*
 *  Steps:
 *      - dfs & weighted dfs-tree
 *      - foreach cc, find the diameter of the dfs-tree
 *      - foreach cc, store the cycle as a successor graph
 *      - foreach node v in the cycle, recursively compute the height of its tree
 *      - sliding window to find the maximum values of:
 *          * max1 = height[v] + height[u] + dist(v, u)
 *          * max2 = height[v] + height[u] - dist(v, u)
 *      - cycle_path = max(max1, L + max2), where L is the total length of the cycle
 *      - add foreach cc max(diameter, cycle_path)
 */

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

vector<vector<array<int, 3>>> adj;
vector<vector<array<int, 2>>> tree;
vector<array<int, 2>> par;
vector<bool> vis, cyc;
int cycle_node = -1;

void dfs(int v, int pi) {
    vis[v] = true;
    for (auto [u, w, i] : adj[v]) {
        if (i == pi) continue;   // deal with cycles of length 2
        if (!vis[u]) {
            par[u] = {v, w};
            tree[v].push_back({u, w});
            tree[u].push_back({v, w});
            dfs(u, i);
        } else if (vis[u] && cycle_node == -1) {
            cycle_node = v;
            par[u] = {v, w};
        }
    }
}

void find_diam(int v, int p, LL dist, array<LL, 2>& max_dist) {
    max_dist = max(max_dist, array<LL, 2>{dist, v});
    for (auto [u, w] : tree[v]) {
        if (u == p) continue;
        find_diam(u, v, dist + w, max_dist);
    }
}

LL height(int v, int p) {
    LL ans = 0;
    for (auto [u, w] : tree[v]) {
        if (u == p) continue;
        if (cyc[u]) continue;
        ans = max(ans, w + height(u, v));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#if EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    adj.resize(n+1);
    tree.resize(n+1);
    par.resize(n+1);
    vis.resize(n+1);
    cyc.resize(n+1);
    for (int v = 1, u, w; v <= n; ++v) {
        cin >> u >> w;
        adj[v].push_back({u, w, v});
        adj[u].push_back({v, w, v});
    }

    LL ans = 0;
    for (int v = 1; v <= n; ++v) {
        if (!vis[v]) {
            // first dfs
            dfs(v, -1);

            // diameter
            array<LL, 2> max_dist{0, v};
            find_diam(v, -1, 0, max_dist);
            int u = max_dist[1];
            max_dist = {0, u};
            find_diam(u, -1, 0, max_dist);
            LL diameter = max_dist[0];

            // path traversing the cycle
            LL a = cycle_node;
            LL cycle_length = 0;
            while (par[a][0] != cycle_node) {
                cyc[a] = true;
                cycle_length += par[a][1];
                a = par[a][0];
            }
            cyc[a] = true;
            cycle_length += par[a][1];

            a = cycle_node;
            LL max1 = -1e9, max2 = -1e9;
            LL prv1 = height(a, -1);
            LL prv2 = prv1;
            while (par[a][0] != cycle_node) {
                auto [b, w] = par[a];
                prv1 += w;
                prv2 -= w;
                LL h = height(b, -1);
                max1 = max(max1, prv1 + h);
                max2 = max(max2, prv2 + h);
                prv1 = max(prv1, h);
                prv2 = max(prv2, h);
                a = b;
            }
            LL cycle_path = max(max1, cycle_length + max2);

            // increase the answer by the maximum path in the current cc
            ans += max(diameter, cycle_path);

            cycle_node = -1;    // reset
        }
    }

    cout << ans << "\n";
}

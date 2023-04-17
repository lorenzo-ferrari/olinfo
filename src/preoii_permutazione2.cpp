#include "bits/stdc++.h"
using namespace std;

bool chiedi(int);
void stato();
void sposta();

int flag[10];

void subtask7(int, int, int, int, int[]);

void indovina(int n, int a, int b, int c, int h[]) {
    if (b == 1) {
        subtask7(n, a, b, c, h);
        return;
    }

    vector<int> bsl(n), bsr(n), bsm(n);
    for (int i = 0; i < n; ++i) {
        bsl[i] = 0;
        bsr[i] = n;
    }

    int pos = 0, st = 1;
    vector<vector<int>> adj(n);
    for (int rep = 0; rep < 10; ++rep) {
        for (auto& x : adj) {
            x.clear();
        }

        for (int i = 0; i < n; ++i) {
            if (bsl[i] == bsr[i]) continue;
            bsm[i] = (bsl[i] + bsr[i]) / 2;
            adj[bsm[i]].push_back(i);
        }

        while (true) {
            for (auto u : adj[pos]) {
                if (chiedi(u)) {
                    bsr[u] = bsm[u];
                } else {
                    bsl[u] = bsm[u] + 1;
                }
            }
            if (pos + st < 0 || pos + st == n) {
                break;
            }
            sposta();
            pos += st;
        }

        stato();
        st = -st;
    }

    for (int i = 0; i < n; ++i) {
        h[bsl[i]] = i;
    }
}

void subtask7(int n, int a, int b, int c, int h[]) {
    static constexpr int BS = 31;

    vector<int> bsl(n), bsr(n);
    for (int i = 0; i < n; ++i) {
        bsl[i] = 0;
        bsr[i] = n;
    }

    int pos = 0, st = 1;
    for (int rep = 0; rep < 2; ++rep) {
        int step = (rep ? 1 : BS);
        vector<vector<int>> bsm(n);
        vector<vector<array<int, 2>>> adj(n);

        for (int i = 0; i < n; ++i) {
            if (bsl[i] == bsr[i]) continue;
            bsm[i].push_back(bsl[i] - 1);
            for (int j = bsl[i] + step - 1; j < bsr[i]; j += step) {
                bsm[i].push_back(j);
                adj[j].push_back({i, (j - bsl[i] + 1) / step});
            }
            bsm[i].push_back(bsr[i]);
        }

        vector<bool> vis(n);
        while (true) {
            for (auto [u, p] : adj[pos]) {
                if (vis[u]) continue;
                if (st == 1) {
                    if (chiedi(u)) {
                        bsl[u] = bsm[u][p-1] + 1;
                        bsr[u] = bsm[u][p];
                        vis[u] = true;
                    } else if (pos + step >= bsr[u]) {
                        bsl[u] = bsm[u][p] + 1;
                    }
                } else {
                    if (!chiedi(u)) {
                        bsl[u] = bsm[u][p] + 1;
                        bsr[u] = bsm[u][p + 1];
                        vis[u] = true;
                    } else if (pos - step <= bsl[u]) {
                        bsr[u] = bsm[u][p];
                    }
                }
            }
            if (pos + st < 0 || pos + st == n) {
                break;
            }
            sposta();
            pos += st;
        }
        if (rep == 0) {
            stato();
            st = -st;
        }
    }

    for (int i = 0; i < n; ++i) {
        h[bsl[i]] = i;
    }
}

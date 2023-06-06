#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int N = 200000;
static constexpr int R = 25000;
static constexpr int SQ = 1024;

static int h[N], p[N], f[R], in[N], out[N];
static vector<int> fi(R, -1), ff;
static vector<int> adj[N];
static vector<array<int, 2>> ev[R];
static vector<array<int, 2>> vs[R];
static LL sub[R][N / SQ];
static LL anc[R][N / SQ];

int t = 0;
static void dfs0(int v) {
    in[v] = t++;
    for (int u : adj[v]) {
        dfs0(u);
    }
    out[v] = t;
}

static int dfs1(int v, const int i, int acc = 0) {
    int cnt = 0;
    for (int u : adj[v]) {
        cnt += dfs1(u, i, acc + (h[v] == ff[i]));
    }
    sub[h[v]][i] += cnt;
    anc[h[v]][i] += acc;
    return cnt + (h[v] == ff[i]);
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int r; cin >> r;
    int q; cin >> q;
    cin >> h[0]; ++f[--h[0]];
    for (int i = 1; i < n; ++i) {
        cin >> p[i] >> h[i];
        --p[i], --h[i];
        adj[p[i]].push_back(i);
        ++f[h[i]];
    }
    for (int i = 0; i < r; ++i) {
        if (f[i] >= SQ) {
            fi[i] = ff.size();
            ff.push_back(i);
        }
    }

    dfs0(0);

    for (int v = 0; v < n; ++v) {
        vs[h[v]].push_back({in[v], v});
        ev[h[v]].push_back({in[v], +1});
        ev[h[v]].push_back({out[v],-1});
    }
    for (int i = 0; i < r; ++i) {
        sort(begin(ev[i]), end(ev[i]));
        sort(begin(vs[i]), end(vs[i]));
    }

    for (int i = 0; i < (int)ff.size(); ++i) {
        dfs1(0, i);
    }

    for (int r1, r2; q--;) {
        cin >> r1 >> r2;
        --r1, --r2;
        if (f[r2] >= SQ) {
            cout << sub[r1][fi[r2]] << endl;
        } else if (f[r1] >= SQ) {
            cout << anc[r2][fi[r1]] << endl;
        } else {
            LL ans = 0;
            int j = 0, act = 0;
            for (auto [tin, v] : vs[r2]) {
                while (j != (int)ev[r1].size() && ev[r1][j][0] <= tin) {
                    act += ev[r1][j][1];
                    ++j;
                }
                ans += act;
            }
            cout << ans << endl;
        }
    }
}

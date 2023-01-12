#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int N = 1000;

bitset<N> adj[N], adjj[N], par[N];

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int m; cin >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b; --a, --b;
        adj[a][b] = 1;
        par[b][a] = 1;
    }
    for (int i = 0; i < n; ++i) {
        adj[i][i] = 1;
        adjj[i] = adj[i];
        for (int j = 0; j < n; ++j) {
            if (adj[i][j]) adjj[i] |= adj[j];
        }
    }
    vector<int> coal;
    bitset<N> dom{0}, adm{0};
    auto take = [&](int v) -> void {
        adm &= ~par[v];
        adm &= ~adj[v];
        dom |= adjj[v];
        coal.push_back(v);
    };
    auto get_diff = [&](int i) -> int {
        return (~dom & adjj[i]).count();
    };
    for (int i = 0; i < n; ++i) adm[i] = 1;
    for (int i = 0; i < n; ++i) {
        if (!par[i].count()) {
            take(i);
        }
    }
    while (dom.count() != n) {
        int best = -1;
        for (int i = n-1; i >= 0; --i) {
            if (!adm[i]) continue;
            if (best == -1) best = i;
            else if (get_diff(best) < get_diff(i)) {
                best = i;
            }
        }
        assert(best != -1);
        take(best);
    }
    for (int i : coal) {
        cout << i+1 << " ";
    }
    cout << "\n";
}

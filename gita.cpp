#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

struct segment {
    int n;
    vector<int> t;

    segment(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.assign(2 * n, 0);
    }

    void update(int p, int v) {
        assert(p < n);
        for (t[p += n] += v; p > 1;)
            t[p >>= 1] += v;
    }

    int lower_bound(int s) {
        int p = 1;
        for (; p < n;) {
            if (t[p << 1] >= s) {
                p = p << 1;
            } else {
                s -= t[p << 1];
                p = p << 1 | 1;
            }
        }
        return p - n;
    }
};

int visita(int n, vector<int>& a, vector<int>& b, vector<int>& d, vector<int>& c) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        g[a[i]].push_back(b[i]);
        g[b[i]].push_back(a[i]);
    }
    vector<int> dd(n);
    vector<int> tmp = d;
    vector<int> dp(n);
    {
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < n; ++i)
            dd[i] = lower_bound(tmp.begin(), tmp.end(), d[i]) - tmp.begin();
    }
    segment t(n);
    function<int(int, int, int)> dfs = [&](int v, int p, int dep) {
        t.update(dd[v], 1);
        if (v && g[v].size() == 1) {
            dp[v] = t.lower_bound(c[v] + 1);
        } else {
            dp[v] = (dep) ? -1 : 1e9;
            for (int u : g[v]) {
                if (u == p)
                    continue;
                if (dep) dp[v] = max(dp[v], dfs(u, v, dep ^ 1));
                else     dp[v] = min(dp[v], dfs(u, v, dep ^ 1));
            }
        }
        t.update(dd[v], -1);
        return dp[v];
    };

    return tmp[dfs(0, -1, 1)];
}

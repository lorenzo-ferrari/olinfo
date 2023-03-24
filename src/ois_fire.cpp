#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct myset {
    int mx = 0;
    int sum = 1;
    multiset<int> s;
    myset() {}
    void insert(int v) {
        s.insert(v);
        sum += v;
        if (v > mx) {
            sum += mx - v;
            mx = v;
        }
    }
    void erase(int v) {
        s.erase(s.find(v));
        sum -= v;
        if (v == mx) {
            int nmax = (s.empty() ? 0 : *prev(s.end()));
            sum += mx - nmax;
            mx = nmax;
        }
    }
    int get() {return sum;}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<myset> dp(n);
    vector<int> par(n);
    function<int(int,int)> sol = [&](int v, int p) -> int {
        par[v] = p;
        dp[v] = myset();
        for (int u : adj[v]) {
            if (u == p) continue;
            dp[v].insert(sol(u, v));
        }
        return dp[v].get();
    };
    sol(0, -1);
    vector<int> ans(n);
    auto makeroot = [&](int v, int pp) -> void {
        par[pp] = v;
        par[v] = -1;
        dp[pp].erase(dp[v].get());
        dp[v].insert(dp[pp].get());
    };
    function<void(int,int)> getroots = [&](int v, int p) -> void {
        // v is root
        assert(par[v] == -1);
        ans[v] = dp[v].get();
        for (int u : adj[v]) {
            if (u == p) continue;
            makeroot(u, v);
            getroots(u, v);
            makeroot(v, u);
        }
    };
    getroots(0, -1);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i==n-1];
    }
}


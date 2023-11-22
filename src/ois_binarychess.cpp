#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;

struct Dsu {
    int n;
    vector<int> p;
    Dsu(int n) : n(n), p(n) {
        iota(begin(p), end(p), 0);
    }
    int find(int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }
    bool onion(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return false;
        }
        p[b] = a;
        return true;
    }
};

int main() {
    int r; cin >> r;
    int c; cin >> c;
    int n; cin >> n;
    map<int, vector<int>> cols;
    for (int i = 0, rr, cc; i < n; ++i) {
        cin >> rr >> cc;
        cols[cc].push_back(rr);
    }
    Dsu dsu(cols.size());
    int cnt = cols.size();
    auto add_edges = [&](function<int(int,int)> f) -> void {
        map<int, vector<int>> eq;
        int id = 0;
        for (auto it = begin(cols); it != end(cols); ++it, ++id) {
            for (int j : it->second) {
                eq[f(it->first, j)].push_back(id);
            }
        }
        for (auto [k, v] : eq) {
            for (int i : v) {
                cnt -= dsu.onion(i, v[0]);
            }
        }
    };
    add_edges([&](int i, int j){ return i-j; });
    add_edges([&](int i, int j){ return i+j; });
    add_edges([&](int i, int j){ return i; });
    add_edges([&](int i, int j){ return j; });

    int ans = 1;
    while (cnt--) {
        ans = 2 * ans % mod;
    }

    cout << ans << "\n";
}

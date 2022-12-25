#include <bits/stdc++.h>
using namespace std;
using LL = unsigned long long;

static constexpr int V = 3e4;

static vector<int> d[V + 1];

struct EnrichedMap {
    LL inc = 0;
    unordered_map<LL, LL> m;    // somma path inclusion/exclusion
    unordered_map<LL, LL> f;    // frequenza path inclusion/exclusion
    unordered_map<LL, LL> mr;   // somma path nodi reali
    unordered_map<LL, LL> fr;   // frequenza path nodi reali
    EnrichedMap() {}
    inline void increase(LL x) { inc += x; }
    inline void insert(int key, LL frq, LL val) {
        m[key] += val - frq * inc;
        f[key] += frq;
    }
    inline size_t size() const { return m.size(); }
    inline LL get_val(int key) { return m[key] + f[key] * inc; }
    inline LL get_frq(int key) { return f[key]; }
    inline vector<array<LL, 3>> get_elements() {
        vector<array<LL, 3>> ans;
        ans.reserve(m.size());
        for (const auto& [key, _] : m) {
            ans.push_back({key, f[key], m[key] + f[key] * inc});
        }
        return ans;
    }
    inline array<LL, 2> ask(int v) {
        int n = d[v].size();
        array<LL, 2> ans{};
        for (int mask = 1; mask < (1 << n); ++mask) {
            int mul = -1;
            int prd = 1;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    prd *= d[v][i];
                    mul *= -1;
                }
            }
            ans[0] += mul * get_val(prd);
            ans[1] += mul * get_frq(prd);
        }
        return ans;
    }
    inline LL merge(EnrichedMap& oth, LL mid) {
        LL ans = 0;
        for (auto [el, oth_sum] : oth.mr) {
            int oth_frq = oth.fr[el];
            oth_sum += oth.inc * oth_frq;
            auto [sum, frq] = ask(el);
            ans += sum * oth_frq;
            ans += frq * oth_sum;
            ans += mid * frq * oth_frq;
        }
        for (const auto& [key, frq, val] : oth.get_elements()) {
            insert(key, frq, val);
        }
        for (auto [el, oth_sum] : oth.mr) {
            int oth_frq = oth.fr[el];
            oth_sum += oth.inc * oth_frq;
            
            fr[el] += oth_frq;
            mr[el] += oth_sum - oth_frq * inc;
        }
        return ans;
    }
    inline LL add_root(int v) {
        auto [sum, frq] = ask(v);
        LL ans = sum + frq * v;
        int n = d[v].size();
        for (int mask = 1; mask < (1 << n); ++mask) {
            int prd = 1;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    prd *= d[v][i];
                }
            }
            insert(prd, 1, 0);
        }
        fr[v] += 1;
        mr[v] += -inc;
        increase(v);
        return ans;
    }
};

vector<int> v;
vector<vector<int>> adj;

LL ans = 0;
EnrichedMap solve(int a, int p) {
    EnrichedMap cur;
    for (int b : adj[a]) {
        if (b == p) continue;
        auto oth = solve(b, a);
        if (oth.size() > cur.size()) {
            swap(cur, oth);
        }
        ans += cur.merge(oth, v[a]);
    }
    ans += cur.add_root(v[a]);
    return cur;
};

int main() {
    for (int i = 1; i <= V; ++i) {
        int t = i;
        for (int j = 2; j*j <= t; ++j) {
            if (t % j) continue;
            d[i].push_back(j);
            while (t % j == 0) {
                t /= j;
            }
        }
        if (t != 1) {
            d[i].push_back(t);
        }
    }

    int n; cin >> n;
    v.resize(n);
    adj.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b; --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    solve(0, -1);

    cout << ans << "\n";
}

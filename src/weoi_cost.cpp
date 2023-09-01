#include "bits/stdc++.h"
using namespace std;
using LL = long long;

static constexpr int mod = 1000003;
static constexpr int INF = 1e9;

vector<int> pgv(vector<int> a) { // strictly greater
    int n = a.size();
    vector<int> ans(n);
    stack<array<int, 2>> st;
    st.push({INF, -1});
    for (int i = 0; i < n; ++i) {
        while (st.top()[0] <= a[i]) {
            st.pop();
        }
        ans[i] = st.top()[1];
        st.push({a[i], i});
    }
    return ans;
}

vector<int> ngv(vector<int> a) { // non-strictly greater
    int n = a.size();
    vector<int> ans(n);
    stack<array<int, 2>> st;
    st.push({INF, n});
    for (int i = n-1; i >= 0; --i) {
        while (st.top()[0] < a[i]) {
            st.pop();
        }
        ans[i] = st.top()[1];
        st.push({a[i], i});
    }
    return ans;
}

struct Dsu {
    LL sum;
    vector<int> p, s;
    vector<bool> act;

    Dsu(int n) : sum(0), p(n), s(n), act(n) {}

    void activate(int i) {
        assert(!act[i]);
        act[i] = true;
        p[i] = i;
        s[i] = 1;
        sum += 1;
    }

    int find(int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }

    void merge(int a, int b) {
        if (!act[a] || !act[b]) return;
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] < s[b]) {
            swap(a, b);
        }
        sum -= (LL)s[a]*s[a];
        sum -= (LL)s[b]*s[b];
        p[b] = a;
        s[a] += s[b];
        sum += (LL)s[a]*s[a];
    }

    LL get() { return sum; }
};

struct S {
    int n, g;
    Dsu dsu;
    vector<array<int, 2>> yi;
    S(vector<int> y) : n(y.size()), g(0), dsu(n), yi(n) {
        for (int i = 0; i < n; ++i) {
            yi[i] = {y[i], i};
        }
        sort(begin(yi), end(yi));
    }

    void update(int x) {
        while (g != n && yi[g][0] <= x) {
            int i = yi[g][1];
            dsu.activate(i);
            if (i != 0) dsu.merge(i-1, i);
            if (i != n-1) dsu.merge(i, i+1);
            ++g;
        }
    }

    LL get() { return dsu.get(); }
};

int solve(int n, int m, int k, vector<int> a, vector<int> b) {
    vector<array<int, 2>> ai(n), bi(m);
    for (int i = 0; i < n; ++i) ai[i] = {a[i], i};
    for (int i = 0; i < m; ++i) bi[i] = {b[i], i};
    sort(begin(ai), end(ai));
    sort(begin(bi), end(bi));

    LL ans = 0;
    {
        auto prv = pgv(a);
        auto nxt = ngv(a);
        S ys(b);
        for (auto [x, i] : ai) {
            ys.update(x);
            LL pp = i - prv[i];
            LL nn = nxt[i] - i;
            LL h = (2 * pp * nn - 1) % mod;
            LL v = ys.get() % mod;
            ans = (ans + x * h * v) % mod;
        }
    }

    {
        auto prv = pgv(b);
        auto nxt = ngv(b);
        S xs(a);
        for (auto [y, i] : bi) {
            xs.update(y - 1);
            LL pp = i - prv[i];
            LL nn = nxt[i] - i;
            LL v = (2 * pp * nn - 1) % mod;
            LL h = xs.get() % mod;
            ans = (ans + y * h * v) % mod;
        }
    }

    return ans;
}

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct Segment {
    int n;
    vector<int> t;
    vector<unordered_map<int, LL>> cache;
    Segment(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.resize(2 * n);
        cache.resize(n);
    }
    void update(int p, int s) {
        for (t[p += n] = s; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
            cache[p >> 1].clear();
        }
    }
    LL query(int i, int x) {
        if (i >= 2*n) return 0;
        if (t[i] <= x) return 0;
        if (i >= n) return t[i];
        if (cache[i].count(x)) return cache[i][x];
        return cache[i][x] = query(2*i, max(x, t[2*i+1])) + query(2*i+1, x);
    }
    LL get() {
        return query(1, -1);
    }
};

int main() {
    int n; cin >> n;
    int q; cin >> q;
    Segment st(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        st.update(i, x);
    }
    for (int i = 0, p, s; i < q; ++i) {
        cin >> p >> s;
        st.update(p, s);
        cout << st.get() << "\n";
    }
}

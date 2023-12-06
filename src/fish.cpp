#include "bits/stdc++.h"
using namespace std;
 
struct fish {
    int l;
    int g;
    bool operator<(const fish& oth) {
        return l < oth.l;
    }
};
 
struct Segtree {
    int n;
    int m;
    vector<int> t;
    Segtree(int n, int m) : n(n), m(m), t(2*n, 1) {}
    void inc(int p) {
        t[p + n] %= m;
        for (t[p += n] += 1; p > 1; p >>= 1) {
            t[p >> 1] = t[p] * t[p ^ 1] % m;
        }
    }
    int query(int l, int r) {
        int ans = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = ans * t[l++] % m;
            if (r & 1) ans = ans * t[--r] % m;
        }
        return ans;
    }
};
 
signed main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int n; cin >> n;
    int k; cin >> k;
    int m; cin >> m;
    vector<fish> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].l >> a[i].g; --a[i].g;
    }
    sort(begin(a), end(a));
    vector<int> last(k);
    vector<vector<int>> o(k);
    for (int i = 0; i < n; ++i) {
        o[a[i].g].emplace_back(a[i].l);
        last[a[i].g] = i;
    }
    vector<int> cs;
    vector<int> idx(k);
    for (int i = 0; i < n; ++i) {
        if (last[a[i].g] == i) {
            idx[a[i].g] = cs.size();
            cs.push_back(a[i].g);
        }
    }
 
    Segtree st(k, m);
 
    int ans = 0;
    vector<int> frq(k);
    for (int r = 0, l = 0; r < n; ++r) {
        int c = a[r].g;
        if (last[c] != r) continue;
        while (2*a[l].l <= a[r].l) {
            st.inc(idx[a[l].g]);
            ++frq[a[l].g];
            ++l;
        }
 
        int cur1 = st.query(0, idx[c]) * (frq[c] % m) % m;
 
        int ll = idx[c], rr = k;
        while (rr - ll > 1) {
            int mm = (ll + rr) / 2;
            if (o[cs[mm]].back() < 2 * o[c][frq[c]]) {
                ll = mm;
            } else {
                rr = mm;
            }
        }
        int cur2 = st.query(0, idx[c]) * st.query(idx[c]+1, ll+1) % m;
 
        ans = (ans + cur1 + cur2) % m;
    }
    
    cout << ans << "\n";
}

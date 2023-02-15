#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct nd {
    int parity = 0;
    LL ans = 0;
    LL sum = 0;
    LL mn_prf = 0;
    LL mx_prf = 0;
    LL mx_sp = 0;
    LL mx_sd = 0;
    nd() {}
    nd(LL x) {
        parity = 1;
        ans = x;
        sum = x;
        mn_prf = 0;
        mx_prf = x;
        mx_sp = 0;
        mx_sd = x;
    }
    bool odd() const {
        return parity & 1;
    }
};
nd join(const nd& a, const nd& b) {
    nd r;
    r.parity = a.parity ^ b.parity;
    r.ans = max(a.ans, b.ans);
    r.ans = max(r.ans, a.mx_sp + b.mx_prf);
    r.ans = max(r.ans, a.mx_sd - b.mn_prf);
    r.sum = a.sum + (a.odd() ? -b.sum : b.sum);
    r.mn_prf = min(a.mn_prf, a.sum + (a.odd() ? -b.mx_prf : b.mn_prf));
    r.mx_prf = max(a.mx_prf, a.sum + (a.odd() ? -b.mn_prf : b.mx_prf));
    r.mx_sp = max(b.mx_sp, (b.odd() ? a.mx_sd - b.sum : a.mx_sp + b.sum));
    r.mx_sd = max(b.mx_sd, (b.odd() ? a.mx_sp + b.sum : a.mx_sd - b.sum));
    return r;
}

struct Segment {
    int n;
    vector<nd> t;
    Segment(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.resize(2 * n);
        for (int i = 0; i < n; ++i) t[i + n] = nd(0);
        for (int i = n-1; i > 0; --i) t[i] = join(t[2*i], t[2*i+1]);
    }
    void upd(int p, int v) {
        p += n;
        for (t[p] = nd(v); p > 1; p >>= 1) {
            if (p & 1) {
                t[p >> 1] = join(t[p^1], t[p]);
            } else {
                t[p >> 1] = join(t[p], t[p^1]);
            }
        }
    }
    nd query(int l, int r, int i = 1, int a = 0, int b = -1) {
        if (b == -1) b = n;
        if (r <= a || b <= l) return nd();
        if (l <= a && b <= r) return t[i];
        return join(
                    query(l, r, 2*i  , a, (a+b)/2),
                    query(l, r, 2*i+1, (a+b)/2, b)
                    );
    }
};

int main() {
    int n; cin >> n;
    int q; cin >> q;
    Segment st(n);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        st.upd(i, x);
    }
    for (int i = 0, t, a, b; i < q; ++i) {
        cin >> t >> a >> b;
        if (t == 1) {
            st.upd(a-1, b);
        } else {
            cout << st.query(a-1, b).ans << "\n";
        }
    }
}


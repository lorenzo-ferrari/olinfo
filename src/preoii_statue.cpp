#include "bits/stdc++.h"
using namespace std;
using LL = long long;

LL somma(int l, int r);
LL subarray_massimo(int l, int r);
LL subarray_minimo(int l, int r);

static constexpr int K = 400;

struct nd {
    LL sum = 0;
    LL sub = 0;
    LL prf = 0;
    LL sff = 0;
};
nd join(const nd& a, const nd& b) {
    nd ans;
    ans.sum = a.sum + b.sum;
    ans.sub = max({a.sub, b.sub, a.sff + b.prf});
    ans.prf = max(a.prf, a.sum + b.prf);
    ans.sff = max(b.sff, a.sff + b.sum);
    return ans;
}

LL trova(int n) {
    nd ans;

    for (int i = 0; i * K < n; ++i) {
        int l = i * K;
        int r = min(n, (i+1)*K) - 1;
        nd cur;
        LL sum = somma(l, r);
        LL mx = subarray_massimo(l, r);
        LL mn = subarray_minimo(l, r);
        if (mx > -mn) {
            int ll = l-1, rr = r;
            while (rr - ll > 1) {
                int mm = (ll + rr) / 2;
                if (subarray_massimo(l, mm) == mx) {
                    rr = mm;
                } else {
                    ll = mm;
                }
            }
            cur.prf = somma(l, rr); 
            cur.sff = sum - (cur.prf - mx);
        } else {
            int ll = l-1, rr = r;
            while (rr - ll > 1) {
                int mm = (ll + rr) / 2;
                if (subarray_minimo(l, mm) == mn) {
                    rr = mm;
                } else {
                    ll = mm;
                }
            }
            LL minprf = somma(l, rr);
            cur.sff = sum - minprf;
            cur.prf = minprf - mn;
        }
        cur.sum = sum;
        cur.sub = mx;

        ans = join(ans, cur);
    }

    return ans.sub;
}

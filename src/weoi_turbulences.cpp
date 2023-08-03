#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int sgn(LL x) { return (x > 0) - (x < 0); }

LL revenue(int n, int k, vector<LL> a) {
    sort(begin(a), end(a), [](LL x, LL y){ return abs(x) < abs(y); });
    vector<LL> sff(n+1); sff[n] = -k;
    for (int i = n-1; i >= 0; --i) {
        sff[i] = sff[i + 1] + sgn(a[i]);
    }
    vector<LL> prf(n+1);
    for (int i = 0; i < n; ++i) {
        prf[i + 1] = prf[i] + a[i];
    }
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, prf[i] + sff[i] * abs(a[i]));
    }
    return ans;
}

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<LL> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    auto prf = a;
    auto sff = a;
    for (int i = 1; i < n  ; ++i)  prf[i] = max(a[i], prf[i - 1]);
    for (int i = n-2; i >= 0; --i) sff[i] = max(a[i], sff[i + 1]);
    LL ans = 0;
    for (int i = 1; i < n; ++i) ans += min(prf[i-1], sff[i]);
    cout << ans << "\n";
}

#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    LL m; cin >> m;
    LL n; cin >> n;
    vector<LL> e(n), l(n);
    for (int i = 0; i < n; ++i) {
        cin >> e[i] >> l[i];
    }
    LL d = 0, s = 0;
    for (int i = 0; i < n; ++i) {
        if (e[i] * l[i] <= s) {
            s -= e[i] * l[i];
        } else {
            e[i] -= s / l[i];
            LL daily = m / l[i];
            d += e[i] / daily;
            e[i] %= daily;
            if (e[i]) {
                ++d;
                s = m - l[i] * e[i];
            } else {
                s = m - l[i] * daily;
            }
        }
    }
    cout << d << " " << s << "\n";
}

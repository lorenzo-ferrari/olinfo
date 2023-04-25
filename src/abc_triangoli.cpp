#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));

    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        int y = i - 1;
        while (x < y) {
            if (a[i] <= a[x] + a[y]) {
                --y;
            } else {
                ans += y - x;
                ++x;
            }
        }
    }
    cout << ans << "\n";
}

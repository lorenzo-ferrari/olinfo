#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int len(int n) {
    while (!(n % 2)) n /= 2;
    while (!(n % 5)) n /= 5;
    LL p = 10 % n;
    for (int i = 1; i < n; ++i) {
        if (p == 1) {
            return i;
        }
        p = 10 * p % n;
    }
    return 0;
}

int main() {
    int n; cin >> n;
    array<int, 2> ans = {1, 0};
    for (int i = max(2,n-200); i < n; ++i) {
        int t = len(i);
        if (t >= ans[1]) {
            ans = {i, t};
        }
    }
    cout << ans[0] << "\n";
}

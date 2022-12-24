#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int f(int n) {
    int ans = 0;
    while (n) {
        ans |= (1 << (n%10));
        n /= 10;
    }
    return ans;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        LL x; cin >> x;
        int ans = 0;
        LL cur = x;
        int mask = 0;
        while (mask != (1 << 10) - 1) {
            ++ans;
            mask |= f(cur);
            cur += x;
        }
        cout << ans << "\n";
    }
}

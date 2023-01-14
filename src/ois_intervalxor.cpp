#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int maxim(int n) {
    int ans = 0;
    for (int i = 1; i <= n; i <<= 1) {
        ans |= i;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q; cin >> q;
    for (int i = 0; i < q; ++i) {
        int a; cin >> a;
        if (a % 4 == 0) {
            cout << a << " " << maxim(a) << "\n";
        } else if (a % 4 == 1) {
            cout << 1 << " " << a << "\n";
        } else if (a % 4 == 2) {
            cout << a+1 << " " << maxim(a+1) << "\n";
        } else {
            cout << 0 << " " << a << "\n";
        }
    }
}

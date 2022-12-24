#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(begin(a), end(a));
    LL cur = 1;
    LL ans = 1;
    for (int i = 1; i < n; ++i) {
        cur += (a[i] != a[i-1]);
        ans += cur;
    }
    cout << ans << "\n";
}

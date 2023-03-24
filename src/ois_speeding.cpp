#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define all(x) begin(x),end(x)

int flag[10];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    sort(all(a));
    sort(all(b));
    LL ans = 1;
    const LL mod = 1e9 + 7;
    for (int i = n-1; i >= 0; --i) {
        LL range = end(a) - lower_bound(all(a), b[i]);
        if (range < n-i) {
            ans = 0;
        } else {
            ans = ans * (range - (n-i) + 1) % mod;
        }
    }
    cout << ans << "\n";
}

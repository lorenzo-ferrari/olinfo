#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int q; cin >> q;
    vector<int> c(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i]; --c[i];
        p[c[i]] = i;
    }
    int ans = 0;
    vector<int> cnt(n);
    for (int x; q--;) {
        // car x overtakes car c[p[x]-1]
        cin >> x; --x;
        int y = c[p[x]-1];
        ++cnt[y];
        if (cnt[y] > cnt[ans] || (cnt[y] == cnt[ans] && y < ans)) {
            ans = y;
        }

        swap(p[x], p[y]);
        swap(c[p[x]], c[p[y]]);

        cout << ans+1 << "\n";
    }
}

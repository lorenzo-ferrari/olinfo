#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int m; cin >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    vector<int> ans(n+1);
    set<int> s;
    for (int i = n-1; i >= 0; --i) {
        s.insert(a[i]);
        ans[i] = s.size();
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[b[i] - 1] << "\n";
    }
}

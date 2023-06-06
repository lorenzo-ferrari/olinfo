#include "bits/stdc++.h"
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;
    int m; cin >> m;
    int k; cin >> k;
    vector<int> d(n);
    for (int& i : d) {
        cin >> i;
    }
    d.push_back(k);

    int ans = 0;
    int lst = 0;
    for (int i = 1; i <= n; ++i) {
        if (lst + m < d[i]) {
            ++ans;
            lst = d[i - 1];
        }
    }
    cout << ans << "\n";
}

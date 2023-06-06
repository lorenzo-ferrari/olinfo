#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    vector<string> a(n);
    for (auto& i : a) {
        cin >> i;
    }
    int m = a[0].size();

    int ans = 0;
    for (int i = 0; i < m; ++i) {
        bool good = true;
        for (int j = 1; j < n; ++j) {
            good &= (a[0][i] == a[j][i]);
        }
        if (good) {
            ++ans;
        } else {
            break;
        }
    }

    cout << ans << "\n";
}

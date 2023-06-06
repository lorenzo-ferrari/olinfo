#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }

    auto mx = *max_element(begin(a), end(a));

    vector<int> p;
    for (int i = 0; i < n; ++i) {
        if (a[i] == mx) {
            p.push_back(i);
        }
    }

    int ans = 1;
    for (int i = 0; i < (int)p.size(); ++i) {
        int cur = 1;
        cur += (i == 0 ? p[i] : p[i] - p[i - 1]);
        cur += (i == p.size() - 1 ? n - 1 - p[i] : p[i + 1] - p[i]);
        ans = max(ans, cur);
    }

    cout << ans << "\n";
}

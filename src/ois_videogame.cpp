#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int t; cin >> t;
    int n; cin >> n;
    vector<array<int, 2>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    int m; cin >> m;
    vector<array<int, 2>> b(m);
    for (auto& [x, y] : b) {
        cin >> x >> y;
    }
    sort(begin(a), end(a), greater<array<int, 2>>());
    sort(begin(b), end(b), greater<array<int, 2>>());
    int ans = 0;
    while (!a.empty() && !b.empty()) {
        auto ta = a.back();
        auto tb = b.back();
        if (ta[0] > tb[0]) {
            if (tb[1] < ta[0]) {
                b.pop_back();
            } else {
                b.back()[0] = ta[0];
            }
        } else if (ta[0] == tb[0]) {
            if (ta[1] <= tb[1]) {
                ans += ta[1] - ta[0] + 1;
                a.pop_back();
            } else {
                ans += tb[1] - tb[0] + 1;
                a.back()[0] = tb[1] + 1;
                b.pop_back();
            }
        } else if (ta[0] < tb[0]) {
            if (tb[0] > ta[0] + t || tb[0] > ta[1]) {
                a.pop_back();
            } else {
                a.back()[0] = tb[0];
            }
        }
    }
    cout << ans << "\n";
}

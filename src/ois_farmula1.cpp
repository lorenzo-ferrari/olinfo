#include "bits/stdc++.h"
using namespace std;
using LL = long long;

constexpr array<int, 11> pts{0,25,18,15,12,10,8,6,4,2,1};

void solve() {
    int n; cin >> n;
    int me = 0, oth = 0;
    for (int i = 0; i < n; ++i) {
        int pos; cin >> pos;
        me += (pos <= 10 ? pts[pos] : 0);
        oth += pts[1 + (pos == 1)];
    }
    if (me >= oth) {
        cout << "Champion\n";
    } else {
        cout << "Practice harder\n";
    }
};

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

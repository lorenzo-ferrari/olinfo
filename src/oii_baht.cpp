#include "bits/stdc++.h"
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(begin(a), end(a));

    int cur = 0;
    for (int i : a) {
        if (i > cur + 1) {
            break;
        }
        cur += i;
    }
    cout << cur+1 << "\n";
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}

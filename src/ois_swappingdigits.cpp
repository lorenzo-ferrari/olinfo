#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int calc(string s, char a, char b) {
    int n = s.size();
    if (n < 2) {
        return 1e9;
    }
    if (s[n-2] == a && s[n-1] == b) {
        return 0;
    }
    if (s[n-2] == b && s[n-1] == a) {
        return 1;
    }
    int ca = 0, cb = 0;
    for (char c : s) {
        ca += (c == a);
        cb += (c == b);
    }
    if (ca < 1 || cb < 1 || (a == b && ca < 2)) {
        return 1e9;
    }
    return 2 - (s[n-1] == b) - (s[n-2] == a);
}

void solve() {
    string s; cin >> s;
    int ans = 1e9;
    ans = min(ans, calc(s, '0', '0'));
    ans = min(ans, calc(s, '2', '5'));
    ans = min(ans, calc(s, '5', '0'));
    ans = min(ans, calc(s, '7', '5'));
    if (ans == 1e9) {
        cout << "-1\n";
    } else {
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        solve();
    }
}

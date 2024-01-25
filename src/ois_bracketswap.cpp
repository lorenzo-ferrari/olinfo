#include "bits/stdc++.h"
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    string s; cin >> s;
    int prf = 0, mn = 0;
    array<vector<int>, 2> p;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '(') {
            ++prf;
            p[0].push_back(i);
        } else {
            --prf;
            mn = min(mn, prf);
            p[1].push_back(i);
        }
    }

    int ans = (-mn + 1) / 2;
    cout << ans << "\n";
    for (int i = 0; i < ans; ++i) {
        cout << p[1][i] << " " << p[0][n / 2 - 1 - i] << "\n";
    }
}

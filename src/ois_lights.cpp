#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int c; cin >> c;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    int missing = c;
    vector<int> frq(c);
    int r = 0;
    while (missing) {
        missing -= (frq[v[r]] == 0);
        ++frq[v[r++]];
    }
    int ans = r;
    for (int l = 0; l < n; ++l) {
        missing += (frq[v[l]] == 1);
        --frq[v[l]];
        while (r != n && missing) {
            missing -= (frq[v[r]] == 0);
            ++frq[v[r++]];
        }
        if (missing) break;
        ans = min(ans, r - l - 1);
    }
    cout << ans << "\n";
}

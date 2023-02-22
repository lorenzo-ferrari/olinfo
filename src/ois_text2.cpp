#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<array<int, 26>> cnt(k);
    vector<string> s(n);
    for (auto& x : s) {
        cin >> x;
        for (int i = 0; i < k; ++i) {
            cnt[i][x[i]-'a']++;
        }
    }
    auto dist = [&](int i) -> int {
        int ans = 0;
        for (int j = 0; j < k; ++j) {
            ans += n - cnt[j][s[i][j]-'a'];
        }
        return ans;
    };
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (dist(i) < dist(best)) {
            best = i;
        }
    }
    cout << best << "\n";
}

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;

inline LL f(int n, int k) {
    LL ans = 1;
    for (int i = k+1; i <= n; ++i) {
        ans = ans * i % mod;
    }
    return ans;
}

int main() {
    int n; cin >> n;
    int k; cin >> k;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    int cnt = 0;
    LL ans = 1;
    map<int, int> frq;
    for (int i = 0; ans && i < n; ++i) {
        if (v[i] == 0) {
            ++frq[0];
            ++cnt;
        } else {
            ans *= frq[v[i]-1];
            ans %= mod;
            --frq[v[i]-1];
            ++frq[v[i]];
        }
    }
    ans = ans * f(k, k - cnt) % mod;
    cout << ans << "\n";
}

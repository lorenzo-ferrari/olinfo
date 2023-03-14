/*
 * let f(k) denote the answer for a prefix of length k
 * key insight: "f(t) given a shorter prefix p" is f(t) - f(p)
 * -> f(k+1) = f(k) + 1 + \sum_{c=1}^{N} { f(k+1) given lps(s[:k] + c) }
 * -> since lps(s[:k] + s[k]) == k+1, f(k+1) = n*f(k) + n - {...}
 * key insight: it can be proven that among all prefixes, the total number of subtractions is O(m)
 *
 */

#pragma GCC target("avx2")
#pragma GCC optimize("Ofast,unroll-loops")
#include <vector>
#include <bitset>
#include <iostream>

using namespace std;
using LL = long long;

static constexpr LL mod = 1e9 + 7;
static constexpr int N = 100;
static constexpr int M = 1000001;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    int m; cin >> m;
    vector<int> s(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i]; --s[i];
    }

    vector<bitset<N>> seen(m);
    vector<vector<int>> subs(m);

    vector<int> z(m);
    for (int i = 1, l, r = -1; i < m; ++i) {
        // standard Z algorithm
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < m && s[i + z[i]] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i, r = i + z[i];
        }

        // interesting part
        if (i + z[i] < m && !seen[i + z[i]].test(s[z[i]])) {
            seen[i + z[i]].set(s[z[i]]);
            subs[i + z[i]].push_back(z[i] + 1);
        }
    }

    vector<LL> dp(m+1);
    for (int i = 1; i <= m; ++i) {
        dp[i] = n * (dp[i - 1] + 1 + mod);
        for (int j : subs[i - 1]) {
            dp[i] -= dp[j];
        }
        dp[i] %= mod;
    }

    for (int i = 1; i <= m; ++i) {
        cout << dp[i] << "\n";
    }
}

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

static constexpr int LIM = 14348907;
static constexpr int K = 15;

static bool dp[LIM];
static int p3[K+1];

static vector<string> tokenize(string s, char sep) {
    vector<string> ans;
    istringstream ss(s);
    string t;
    while (getline(ss, t, sep)) {
        ans.push_back(t);
    }
    return ans;
}

static int translate(string clause) {
    // return trimask: {0, 1, 2} = {not in, a , !a}
    int ans = 0;
    for (int i = 1; i < (int)clause.size(); ++i) {
        if (clause[i] == '!') {
            ++i;
            int t = clause[i++] - 'a';
            ans += 2 * p3[t];
        } else {
            int t = clause[i++] - 'a';
            ans += p3[t];
        }
    }
    return ans;
}

static void solve() {
    fill(dp, dp + LIM, false);
    int k; cin >> k;
    string s; cin >> s;
    auto clauses = tokenize(s, '^');
    for (string s : clauses) {
        dp[translate(s)] ^= true;
    }
    int ans = 0;
    for (int mask = 0; mask < p3[k]; ++mask) if (dp[mask]) {
        int idx = -1;
        int tmp = mask;
        for (int i = 0; i < k; ++i, tmp /= 3) {
            if (tmp % 3 == 0) {
                idx = i;
                break;
            }
        }
        if (idx == -1) ++ans;
        else {
            dp[mask +   p3[idx]] ^= true;
            dp[mask + 2*p3[idx]] ^= true;
        }
    }
    cout << ans << "\n";
}

int main() {
    p3[0] = 1;
    for (int i = 1; i <= K; ++i) {
        p3[i] = 3 * p3[i-1];
    }
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

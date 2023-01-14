#include <bits/stdc++.h>
using namespace std;
using LL = unsigned long long;

static constexpr int LG = 20;

LL u1, au, bu, cu;
LL d1, ad, bd, cd;
LL m1, am, bm, cm;
map<int, array<LL, 3>> v;
map<int, array<LL, LG+1>> dp;

static LL getu(LL prv) { return (au * prv + bu) % cu; }
static LL getd(LL prv) { return (ad * prv + bd) % cd; }
static LL getm(LL prv) { return (am * prv + bm) % cm; }

static void calc(int s) {
    auto [u, d, m] = v[s];
    auto dp1 = dp[s-1];
    auto dp2 = dp[s-2];
    auto dpm = dp[s/2];
    array<LL, LG+1> ans;
    if (s >= 2) {
        for (int i = 0; i <= LG; ++i) {
            ans[i] = dp2[i] + d;
        }
    } else {
        fill(begin(ans), end(ans), 1e12);
    }
    ans[LG] = min(ans[LG], dp1[LG] + u);
    for (int i = 0; i <  LG; ++i) ans[i] = min(ans[i], dp1[i+1] + u);
    for (int i = 1; i <= LG; ++i) ans[i] = min(ans[i], dpm[i-1] + m);
    v[s+1] = {getu(u), getd(d), getm(m)};
    dp[s] = ans;
};
static void erase(int i) {
    if (i > 4) {
        v.erase(i+1);
        dp.erase(i);
    }
};

int main() {
    int n; cin >> n;
    int e; cin >> e;
    cin >> u1 >> au >> bu >> cu;
    cin >> d1 >> ad >> bd >> cd;
    cin >> m1 >> am >> bm >> cm;

    v[1] = {u1, d1, m1};
    for (int s = 1; s <= 4 && s <= n; ++s) calc(s);
    for (int s = 5; s <= n; ++s) {
        int nn = 2*s;
        stack<int> st;
        do {
            nn /= 2;
            st.push(nn);
        } while (nn % 2 == 0);
        while (!st.empty()) {
            calc(st.top());
            erase(st.top() - 2);
            st.pop();
        }
    }
    cout << dp[n][min(e, 20)] << "\n";
}

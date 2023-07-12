#include "bits/stdc++.h"
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
using namespace std;
using LL = long long;

int main() {
    int n; cin >> n;
    int k; cin >> k;
    priority_queue<int, vector<int>, greater<int>> hand;
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ans += x;
        hand.push(x);
        if ((int)hand.size() > k) {
            ans -= hand.top();
            hand.pop();
        }
        cout << ans << " \n"[i == n-1];
    }
}

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL stima(int n, int h[]) {
    for (int i = 0; i < n; ++i) {
        h[i] -= i;
    }
    nth_element(h, h+n/2, h+n);
    LL ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += abs(h[i] - h[n/2]);
    }
    return ans;
}

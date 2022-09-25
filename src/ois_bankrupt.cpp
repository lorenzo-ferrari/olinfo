#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int64_t n, ans, x[MAXN], y[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    ans = x[n - 1]*y[0] - x[0]*y[n - 1];
    for (int i = 0; i < n - 1; i++) ans += x[i]*y[i + 1] - x[i + 1]*y[i];
    ans = (ans < 0) ? -ans : ans;
    
    cout << ans/2 << "\n";
}
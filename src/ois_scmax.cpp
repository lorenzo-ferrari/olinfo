#include <stack>
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;
#define MAXN 100005

int n;
int t[2 * MAXN];
int p[MAXN], c[MAXN];
int nxt_c[MAXN], dp[MAXN], last[MAXN];

void modify(int value, int p) {
    for(t[p += n] = value; p > 1; p >>= 1)
        t[p >> 1] = max(t[p], t[p ^ 1]);
}

int query(int l, int r) { //interval [l, r)
    int ans = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if(l & 1) ans = max(ans, t[l++]);
        if(r & 1) ans = max(ans, t[--r]);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", p + i);
    for (int i = 0; i < n; i++) scanf("%d", c + i + 1);
    
    fill(last, last + n + 1, n);
    for (int i = n - 1; i >= 0; i--) {
        nxt_c[i] = last[c[p[i]]];
        last[p[i]] = i;
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = 1 + max(dp[nxt_c[i]], query(p[i], n + 1));
        ans = max(ans, dp[i]);
        if (dp[i] > query(p[i] - 1, p[i])) modify(dp[i], p[i] - 1);
    }

    printf("%d\n", ans);
}
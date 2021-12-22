#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define max(a, b) ((a < b) ? b : a);
#define min(a, b) ((a < b) ? a : b);
#define MAXN 150000
#define INF 2147483647
using namespace std;

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked(' ');
}

int main(){
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    int n = get_int();
    int a[MAXN], b[MAXN];
    for (int i = 0; i < n; i++) {
        a[i] = get_int();
        b[i] = get_int();
    }
    int ans = 0, i = 0, mnSX = INF, mxDX = -1, nxtDX = -1;
    while (i < n) {
        while (i < n && a[i] < mnSX) {
            mnSX = min(mnSX, b[i]);
            mxDX = max(mxDX, b[i]);
            i++;
        }
        while (i < n && a[i] < mxDX) {
            nxtDX = max(nxtDX, b[i]);
            i++;

        }

        mnSX = INF;
        mxDX = nxtDX;
        ans++;
    }
    print(ans);
}
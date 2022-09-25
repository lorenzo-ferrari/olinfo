#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
using namespace std;

inline int64_t getint() {
    int64_t n = 0;
    char c = getchar_unlocked();
    if (c == '-') {
        getchar_unlocked();
        getchar_unlocked();
        return -1;
    }
    while ('0' <= c && c <= '9') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    
    return n;
}

inline void putint(int64_t n) {
    if (!n) {
        putchar_unlocked('0');
        return;
    }
    
    int i = 0;
    char st[11];
    while (n) {
        st[i++] = n % 10 + '0';
        n /= 10;
    }
    
    while (i)
        putchar_unlocked(st[--i]);
}

int32_t main() {
    int64_t n = getint();
    int64_t ans = 0;
    for (int64_t prv = 0, v; n--; prv = v) {
        v = getint();
        if (v < prv)
            v = prv;
        ans += v;
    }
    
    putint(ans);
}
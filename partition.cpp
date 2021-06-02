#include <stdio.h>
#pragma GCC optimize ("O3")

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
    char S[5];
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

int n;
int t[200000];

inline int query(int l, int r) { // [l, r)
    int ans = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) ans += t[l++];
        if (r & 1) ans += t[--r];
    }

    return ans;
}

int main() {
    n = get_int();
    for (int i = 0, el; i < n; i++) {
        el = get_int() - 1;
        print(i + el - 2 * query(0, el));
        for (t[el += n] = 1; el > 1; el >>= 1) t[el >> 1] = t[el] + t[el ^ 1];
    }
}
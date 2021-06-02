#include <iostream>
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

int main() {
    int n = get_int();
    int h[1000000];
    int ans = 0, mx = 0, idx = n;

    for (int i = 0; i < n; i++)
        h[i] = get_int();

    for (int i = n - 1; i >= 0; i--) {
        if (mx > h[i] && idx - i > ans) ans = idx - i;
        if (h[i] >= mx) {
            mx = h[i];
            idx = i;
        }
    }

    print(ans);
}

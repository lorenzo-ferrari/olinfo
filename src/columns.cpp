#include <iostream>
#pragma GCC optimize ("O3")
#define min(a, b) ((a < b) ? a : b)
#define MAXL 10001
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

int main() {
    int n = get_int();
    int m = get_int();
    int t = get_int();
    int f[MAXL] {};
    while (n--)
        f[get_int()]++;
    
    int ans = t, tm = 0, half;
    for (; ans < MAXL && tm < m; ans++) {
        tm = f[ans];
        if (!(ans & 1))
            tm += (f[ans >> 1] >> 1);
        half = (ans - 1) >> 1;
        while (half) {
            tm += min(f[half], f[ans - half]);
            half--;
        }
        if (tm >= m) {
            print(ans);
            return 0;
        }
    }
    ans |= 1; ans ^= 1;
    while (ans < (MAXL << 1)) {
        if (!(ans & 1) && f[ans>>1] >= m) {
            print(ans);
            return 0;
        }
        ans += 2;
    }

    putchar_unlocked('I');
    putchar_unlocked('M');
    putchar_unlocked('P');
    putchar_unlocked('O');
    putchar_unlocked('S');
    putchar_unlocked('S');
    putchar_unlocked('I');
    putchar_unlocked('B');
    putchar_unlocked('L');
    putchar_unlocked('E');
}
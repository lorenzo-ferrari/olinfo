#include <iostream> 
#pragma GCC optimize ("O3")
using namespace std;
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define MAXN 1000000

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
    int k = get_int();
    int f[MAXN + 1]{};
    while (n--) 
        f[get_int()]++;
    int g = 0, ans = MAXN;
    int v[MAXN]{};
    for (int i = 0; i <= MAXN; i++) {
        while (f[i]--) {
            v[g++] = i;
            if (g >= k)
                ans = min(ans, v[g - 1] - v[g - k]);
        }
    }
    print(ans);
}
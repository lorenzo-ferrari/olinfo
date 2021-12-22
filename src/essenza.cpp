#include <fstream>
#pragma GCC optimize ("O3")
using namespace std;
#define min(a, b) (((a) < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

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
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    
    int k = get_int();
    int n = get_int();
    int p[1000];
    for (int i = 0; i < n; i++)
        p[i] = get_int();
    int ans = 0, mn = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        mx = 0;
        mn = p[i];
        for (int j = i + 1; j < n && j <= i+k; j++)
            mx = max(mx, p[j]);
        ans = max(ans, mx - mn);
    }

    print(ans);
}
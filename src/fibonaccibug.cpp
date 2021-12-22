#include <iostream>
#include <vector>
using namespace std;
#pragma GCC optimize ("O3")
#define int long long
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MAXF 27
#define MAXK 100000

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n)
{
    int i=0;
    char S[42];
    if (n == 0)
    {
        putchar_unlocked('0');
        putchar_unlocked('\n');
        return;
    }
    while(n>0)
    {
        S[i++]=n%10+'0';
        n/=10;
    }
    while(--i>=0)
        putchar_unlocked(S[i]);
    putchar_unlocked('\n');
}

int32_t main() {
    int f[MAXF];
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i < MAXF; i++) f[i] = f[i - 1] + f[i - 2];
    int t = get_int();
    while (t--) {
        int n = get_int();
        int k = get_int();
        int b[MAXF] {};
        int dp[MAXK + 1] {};

        for (int i = 0, ai, bi; i < n; i++) {
            ai = get_int();
            bi = get_int();
            if (ai < MAXF) b[ai] = max(b[ai], bi);
        }
        
        for (int i = 0; i <= k; i++)
            for (int j = 0; j < MAXF; j++)
                if (i + f[j] <= k)
                    dp[i + f[j]] = max(dp[i] + b[j], dp[i + f[j]]);

        print(dp[k]);
    }
}
#include <bits/stdc++.h>
using namespace std;

inline int64_t get_int() {
    char c = getchar_unlocked();
    int64_t n = 0;

    while (c >= '0') {
        n = 10 * n + c - '0';
        c = getchar_unlocked();
    }

    return n;
}

inline void print(int64_t n)
{
    int i=0;
    char S[20];
    
    while(n>0)
    {
        S[i++]=n%10+'0';
        n=n/10;
    }
    --i;
    while(i>=0)
        putchar_unlocked(S[i--]);
    printf("\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int64_t Q, N;
    Q = get_int();
    while (Q--) {
        N = get_int();
        print(((N ^ (1LL << (63 - __builtin_clzll(N)))) << 1) | 1);
    }
}
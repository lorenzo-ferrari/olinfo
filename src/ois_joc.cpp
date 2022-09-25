#include <iostream>
#include <vector>
#include <queue>
#pragma GCC optimize ("O3")
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

inline void print(int n)
{
    int i=0;
    char S[20];
    if (n == 0)
    {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while(n>0)
    {
        S[i++]=n%10+'0';
        n=n/10;
    }
    --i;
    while(i>=0)
        putchar_unlocked(S[i--]);
    putchar_unlocked(' ');
}

int sw[20], dp[1 << 21];

int32_t main() {
    int n = get_int();
    int k = get_int() - 1;
    int st = 0, base_sw = (1 << n) - 1;

    for (int i = 0; i < n; i++)
        if (get_int() != 0)
            st += (1 << i);
    
    fill(sw, sw + n, base_sw);
    fill(dp, dp + (1 << 21), 42);

    for (int i = 0, sz, a; i < n; i++) {
        sz = get_int();
        while (sz--) {
            sw[i] ^= (1 << (get_int() - 1));            
        }
    }

    int goal = 1 << k;
    queue <int> Q;
    Q.push(st);
    dp[st] = 0;
    while (dp[goal] == 42) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < n; i++) {
            if (!(x & (1 << i))) {
                int tx = x & sw[i] | (1 << i);
                if (dp[tx] > dp[x] + 1) {
                    dp[tx] = dp[x] + 1;
                    Q.push(tx);
                }
            }
        }
    }

    print(dp[goal]);
}
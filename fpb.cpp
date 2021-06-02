#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

const uint64_t MOD = 1e9 + 7;
const uint64_t MAXN = 5e4 + 42;
const uint64_t MAXK = 20;

uint64_t n, k;
uint64_t v[MAXN];
uint64_t tb[MAXN][18];
uint64_t dp[MAXN][MAXK];
uint64_t conta[MAXN][MAXK];

uint64_t query(uint64_t l, uint64_t r) { // [l, r)
    uint64_t lg = 63 - __builtin_clzll(r - l);
    // cout << l << " " << r << " " << __gcd(tb[l][lg], tb[r - (1 << lg)][lg]) << "\n";
    return __gcd(tb[l][lg], tb[r - (1 << lg)][lg]);
}

int32_t main() {
    scanf("%lu%lu", &n, &k);

    for (int64_t i = 0; i < n; i++) {
        scanf("%lu", v + i);
        tb[i][0] = v[i];
    }

    int64_t lg = 63 - __builtin_clzll(n);
    for (int64_t i = 1; i <= lg; i++)
        for (int64_t j = 0; j + (1 << i) <= n; j++)
            tb[j][i] = __gcd(tb[j][i - 1], tb[j + (1 << (i - 1))][i - 1]);
    
    // for (int64_t i = 0; i < n; i++) {
    //     for (int64_t j = i; j < n; j++) {
    //         printf("%lu ", query(i, j + 1));
    //     }
    //     printf("\n");
    // }

    // conta
    for (uint64_t i = 0; i <= n; i++) conta[i][0] = 1;
    for (uint64_t i = 1; i <= k; i++) {
        uint64_t pref = conta[0][i - 1];
        for (uint64_t j = 1; j <= n; j++) {
            conta[j][i] = (conta[j - 1][i] + pref) % MOD;
            pref = (pref + conta[j][i - 1]) % MOD;
            // printf("%lu ", conta[j][i]);
        }
        // printf("\n");
    }
    // printf("\n");

    // for (int i = 0; i <= k; i++) {
    //     for (int j = 0; j <= n; j++) {
    //         printf("%lu ", conta[j][i]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    // dp
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= n; j++) {
            dp[j][i] = dp[j - 1][i];
            for (int ii = 0; ii < j; ii++) {
                dp[j][i] = (dp[j][i] + dp[ii][i - 1] + conta[ii][i - 1] * query(ii, j)) % MOD;
            }
            // printf("%lu ", dp[j][i]);
        }
        // printf("\n");
    }

    // for (int j = 0; j <= k; j++) {
    //     for (int i = 0; i <= n; i++) {
    //         printf("%lu ", dp[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("%lu\n", (((conta[n][k] * k) % MOD) * v[0]) % MOD);
    printf("%lu\n", dp[n][k]);
}
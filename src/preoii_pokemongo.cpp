// https://training.olinfo.it/#/task/preoii_pokemongo/statement

#include "bits/stdc++.h"
using namespace std;

bool attack(int);

int N, K;

vector<map<int, pair<int, int>>> dp;
vector<map<int, int>> idp;

/*
 *  dp[k][j]: what is the best I can do with k eggs and j trials?
 *      * only consider j >= 2, so that j = O(sqrt(N))
 *      * as soon as dp[k][j] >= N, stop
 *      * O(K * sqrt(N))
 *  dp[k][j] = {max_n_detectable, first_move}
 */

void init(int N, int K) {
    ::N = N, ::K = K;
    dp.resize(K+1);
    idp.resize(K+1);
    for (int k = 2; k <= K; ++k) {
        for (int j = 1;; ++j) {
            int max_n, query;
            if (j <= k) {
                max_n = (1 << j) - 1;
                query = (1 << (j - 1)) - 1;
            } else {
                max_n = idp[k][j-1] + (k == 2 ? j-1 : idp[k-1][j-1]) + 1;
                query = (k == 2 ? j-1 : idp[k-1][j-1]);
            }
            dp[k][max_n] = {j, query};
            idp[k][j] = max_n;
            if (max_n >= N) {
                break;
            }
        }
    }
}

static int solve(int a, int b, int k) {
    if (a == b) return a;
    if (k == 1) {
        while (a < b && attack(a)) {
            a++;
        }
        return a;
    } else {
        int n = b - a;
        auto it = dp[k].lower_bound(n);
        assert(it != end(dp[k]));
        int query = a + min(n-1, it->second.second);
        if (attack(query)) {
            return solve(query+1, b, k);
        } else {
            return solve(a, query, k - 1);
        }
    }
}

int new_pokemon() {
    return solve(0, N, K);
}

#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int MAXS = 100000, MAXP = 50000, MAXD = 100;

int SS, PP;
vector <vector<int>> nxt;
unordered_map <int, unordered_map <int, int>> dp;

long long SOLVE_SAME(int S, int s[], int P, int p[]) {
    vector <int> pref (S + 1);
    for (int i = 1; i <= S; i++) {
        pref[i] = pref[i - 1] + (s[i - 1] == p[0]);
    }

    int r = 0, l = P;
    int64_t ans = 0;
    for (int r = 0; l < S + 1; r++) {
        while (l < S + 1 && pref[l] - pref[r] < P) l++;

        if (l < S + 1) {
            ans += S + 1 - l;
        }
    }

    return ans;
}

int solve (int ts, int tp, int p[]) {
    if (dp[ts][tp]) return dp[ts][tp];
    return dp[ts][tp] = ((tp == PP) ? ts : solve(nxt[ts][p[tp]], tp + 1, p)); 
}

long long conta(int S, int s[], int P, int p[]) {
    SS = S; PP = P;
    nxt.resize(S + 1, vector <int> (MAXD));
    nxt[S] = vector <int> (MAXD, S);
    for (int i = S - 1; i >= 0; i--) {
        nxt[i] = nxt[i + 1];
        if (i < S - 1) {
            nxt[i][s[i + 1]] = i + 1;
        }
    }
    
    bool same = 1;
    for (int i = 1; i < P; i++) {
        if (p[i] != p[0]) {
            same = 0;
            break;
        }
    }
    
    if (same) return SOLVE_SAME(S, s, P, p);

    int64_t ans = 0;
    for (int l = 0; l < S; l++) {
    //for (int l = S - 1; l >= 0; l--) {
        ans += S - solve(l, (s[l] == p[0]), p);
    }
    
    return ans;
}
/*/
 * prefix isn't enough, you need an ordered subsequence
 * probably nxt[s][dishes], where s[i][j] = position of the next j-th dish
 * -> build it in O(S*D)
 * int i = 0;
 * for (int j = 0; i < S && j < P; j++) {
 *  i = nxt[i][p[j]];
 * }
 * ans += s - i;
 * 
 * store already computed values in an u_map
 * u_map <int, u_map <int, int>> mp; mp[i][j] points to the last dish
/*/

/*
6 3
0 0 1 2 0 1
0 2 0

4
*/

/*
9 3
0 1 0 1 1 0 1 0 1
0 0 0

8
*/
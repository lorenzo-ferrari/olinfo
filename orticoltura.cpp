#include <iostream>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include <algorithm>
#pragma GCC optimize ("O3")
#define F first
#define S second
#define INF 2147483647
using namespace std;

void posiziona(int D, int T);
void budget(int B);

bool comp (pair <int, int> a, pair <int, int> b) { return a.F - a.S < b.F - b.S; } //sort for x-y

void irriga (int C, int N, vector <int> &X, vector <int> &P) {
    int n = N;
    vector <pair<int, int>> s(n);
    for (int i = 0; i < N; i++) {s[i] = {X[i], P[i]};}
    sort(s.begin(), s.end(), comp);
    vector <int> dp(n);
    vector <pair<int, int>> irr;
    irr.push_back({s[0].F, s[0].S});
    dp[0] = s[0].S + C;
    for (int i = 1; i < n; i++) {
        //int att = (s[i].F + s[i].S - s[i-1].F - s[i-1].S) / 2; // <- PROBLEM HERE!!! try s[i - 1] = {2, 2}, s[i] = {1M + 1, 1M}
        int prX = irr.back().F;
        int prP = irr.back().S;
        int att = max(0, (s[i].F - prX + s[i].S - prP) / 2);
        dp[i] = dp[i - 1];
        if (att == 0) continue;
        if (att < C + s[i].S) {
            irr.back().F += att;
            irr.back().S += att;
            dp[i] += att;
        } else {
            irr.push_back({s[i]});
            dp[i] += C + s[i].S;
        }
    }

    budget(dp[n - 1]);
    for (auto x : irr) posiziona(x.F, x.S);
}

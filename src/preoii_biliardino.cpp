#include <bits/stdc++.h>
#define MAXN 1000001
using namespace std;

int N;
bool special = 1;
long long T[MAXN+1], nextt[MAXN+1];
long long dp[MAXN+1];
int prox[MAXN+1][21];

void fill_nextt_dp()
{
    stack <pair<int, int>> S;

    for(int i = N-1; i >= 0; i--)
    {
        while(!S.empty() && S.top().first >= T[i])
            S.pop();
        
        if(S.empty())
            nextt[i] = N;
        else 
            nextt[i] = S.top().second;

        S.push({T[i], i});

        dp[i] = dp[nextt[i]] + T[i]*(nextt[i]-i);
    }        
}

void fill_prox()
{
    for(int i = 0; i < 20; i++) prox[N][i] = N;
    for(int i = N-1; i >= 0; i--)
    {
        prox[i][0] = i;
        prox[i][1] = nextt[i];

        for(int j = 2; j < 20; j++)
            prox[i][j] = prox[prox[i][j-1]][j-1];
    }
}

void inizia(int n, int t[])
{
    N = n;
    
    T[0] = (long long)t[0];

    for(int i = 1; i < n; i++) 
    {
        T[i] = (long long)t[i];
        if(T[i] > T[i-1]) special = 0;
    }

    fill_nextt_dp();
    fill_prox();    
}

int last_touch(int L, int R)
{
    int row = L, col = 0;
    if(R == N) return N;

    while(1)
    {
        if(prox[row][col] == R) return R;

        if(prox[row][1] > R) return prox[row][col];
            
        while(col < 20 && prox[row][col+1] <= R)
            col++;

        row = prox[row][col];
        col = 0;
    }
}

long long passaggio(int L, int R)
{
    if(special) return dp[L]-dp[R];
    
    int touch = last_touch(L, R);

    return dp[L]-dp[touch] + T[touch]*(long long)(R-touch);
}
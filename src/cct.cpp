#include <bits/stdc++.h>

#define MAXN 100000
#define MAXK 20

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, K;
int V[MAXN], C[MAXN];
int m[MAXN][MAXK+1];

int solve(int n, int c)
{
    if(n == N) return 0;

    c = min(c, K);

    if(m[n][c] != 0) 
        return m[n][c];

    int tot = solve(n+1, c+C[n]) + V[n];;

    if(c == K)
        tot = min(tot, solve(n+1, 0));
    
    return m[n][c] = tot;
}

int main()
{
    in >> N >> K;

    for(int i = 0; i < N; i++)
        in >> V[i];
    for(int i = 0; i < N; i++)
        in >> C[i];

    out << solve(0, 0);
}
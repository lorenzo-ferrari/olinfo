#include <bits/stdc++.h>
#define MAXN 1000
using namespace std;
ifstream in ("input.txt");
ofstream out ("output.txt");

int main()
{
    int Nm, Nf;
    int M[MAXN], F[MAXN];
    
    in >> Nm >> Nf;

    for(int i = 0; i < Nm; i++)
        in >> M[i];

    for(int i = 0; i < Nf; i++)
        in >> F[i];

    int dp[MAXN+1][MAXN+1] { };

    for(int i = Nm-1; i >= 0; i--)
        for(int j = Nf-1; j >= 0; j--)
            dp[i][j] = max(abs(M[i]-F[j]) + dp[i+1][j+1], max(dp[i+1][j], dp[i][j+1]));

    out << dp[0][0]; 
}
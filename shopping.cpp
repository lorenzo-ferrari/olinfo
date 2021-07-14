#include <bits/stdc++.h>

#define MAXN 100001

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, E, P;
int dp_taken[MAXN], dp_not_taken[MAXN];

int main()
{
    in >> N >> E;

    in >> P;

    if(P > E)
        dp_not_taken[1] = E;
    else 
    {
        dp_taken[1] = E-P;
        dp_not_taken[1] = P-1;
    }

    for(int i = 2; i <= N; i++)
    {
        in >> P;

        int check = max(dp_taken[i-1], dp_not_taken[i-1]);
        if(check < P)
            dp_not_taken[i] = check;
        else
        {
            dp_taken[i] = check - P; 
            dp_not_taken[i] = max(P-1, dp_taken[i-1]);
        }
    }
    
    out << max(dp_not_taken[N], dp_taken[N]);
}
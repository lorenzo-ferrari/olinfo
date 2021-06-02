#include <bits/stdc++.h>

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, E, P, check;
int dp_taken, dp_not_taken;

int main()
{
    in >> N >> E;

    in >> P;

    if(E < P)
    {
        dp_not_taken = E;
    }
    else 
    {
        dp_taken = E-P;
        dp_not_taken = P-1;
    }

    for(int i = 1; i < N; i++)
    {
        in >> P;

        check = max(dp_taken, dp_not_taken);

        if(check < P)
        {
            dp_not_taken = check;
        }
        else
        {
            dp_not_taken = max(P-1, dp_taken);
            dp_taken = check - P; 
            
        }
    }
    
    out << max(dp_not_taken, dp_taken);
}
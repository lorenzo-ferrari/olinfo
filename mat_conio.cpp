#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N = 0, counter = 1;
    char c = getchar_unlocked();
    while(c >= '0')
    {
        N = 10*N+c-'0';
        c = getchar_unlocked();
    }

    while(!(N & 1))
    {
        N = N>>1;
        ++counter;
    }

    for(int i = 3; i <= N; i+=2)
    {
        while(N%i == 0)
        {
            ++counter;
            N /= i;
        }
    }

    printf("%d", counter);    
}
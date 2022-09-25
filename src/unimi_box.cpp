#include <bits/stdc++.h>
#define INTERVALLO 9

#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-funsafe-loop-optimizations")

using namespace std;

int N, d, minimo;
int ottimo[5001];

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    char c = getchar_unlocked();
    while(c >= '0')
    {
        N = 10*N+c-'0';
        c = getchar_unlocked();
    }

    for(int i = 1; i <= N; i++) {
        d = sqrt(i);
        while(i%d != 0)
            d--;
        
        minimo = 2*(d + i/d);
        if(i/d - d > 2)
            for(int j = i-1; j > 0 && j > i-INTERVALLO; j--)
                minimo = min(minimo, ottimo[j]+ottimo[i-j]);

        ottimo[i] = minimo;
    }
    
    printf("%d", minimo);
}

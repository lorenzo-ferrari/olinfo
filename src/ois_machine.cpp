#include <bits/stdc++.h>
#define MAXD 1001
#define TEST 1550

#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-fexpensive-optimizations")
//#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")?

using namespace std;

int C, D, Y;
int M[MAXD], P[MAXD], total, optimal[TEST];

inline int get_int()
{
    int n = 0; 
    char c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }

    return n;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n = 0; 
    char c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
    C = n;
    
    n = 0; 
    c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
    D = n;
    
    
    n = 0; 
    c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
    Y = n;

    for(int i = 1; i <= D; i++)
    {
        n = 0; 
    c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
        M[i] = n;
    }

    for(int i = 1; i <= D; i++)
    {
        n = 0; 
    c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
        P[i] = n;
    }

    D = min(D, Y);
    
        //fill_optimal

        for(int i = 1; i <= D; i++)
        {
            total += M[i]+P[i-1]-P[i];
            int minimo = total+C;
            for(int j = 1; j <= i/2; j++)
                minimo = fmin(minimo, optimal[j]+optimal[i-j]);
            optimal[i] = minimo;
        }
        for(int i = D+1; i <= TEST; i++)
        {
            int minimo = optimal[1]+optimal[i-1];
            for(int j = 2; j <= i/2; j++)
                minimo = min(minimo, optimal[j]+optimal[i-j]);
    
            optimal[i] = minimo;
        }

    int minimo = Y*optimal[1];

    for(int i = 2; i <= TEST; i++)
        minimo = min(minimo, Y/i*optimal[i] + optimal[Y%i]);

    printf("%d", minimo); 
}
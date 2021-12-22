//sushi modificato...
#include <bits/stdc++.h>
#define MAXN 100000
#pragma GCC optimize("inline")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
using namespace std;
typedef pair<int, int> pii;
vector <pii> dp;

int b_search(int istante) 
{
    int left = 0, right = dp.size()-1, middle; 

    if(dp[right].first >= istante) return right;

    while(left < right)
    {
        middle = (left+right) >> 1;

        if(dp[middle].first >= istante && dp[middle+1].first < istante)
            return middle;
        if(dp[middle+1].first < istante)
            right = middle;
        else 
            left = middle;
    }
}

int main()
{
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    
    int N, a, b, c;
    pair<pii, int> piatti[MAXN];
    
    N = 0;
    char cc = getchar_unlocked();
    while(cc >= '0')
    {
        N = N*10+cc-'0';
        cc = getchar_unlocked();
    }

    for(int i = 0; i < N; i++)
    {
        a = 0;
        cc = getchar_unlocked();
        while(cc >= '0')
        {
            a = a*10+cc-'0';
            cc = getchar_unlocked();
        }
        
        c = 0;
        cc = getchar_unlocked();
        while(cc >= '0')
        {
            c = c*10+cc-'0';
            cc = getchar_unlocked();
        }
        
        b = 0;
        cc = getchar_unlocked();
        while(cc >= '0')
        {
            b = b*10+cc-'0';
            cc = getchar_unlocked();
        }
        
        c = c-a+1;
        
        piatti[i] = {{-a, c}, b};
    }

    sort(piatti, piatti+N); //sorta correttamente con primo

    dp.push_back({0, 0}); //istante, quantità di sushi preso

    for(int i = 0; i < N; i++)
    {
        a = -piatti[i].first.first;
        c = piatti[i].first.second;
        b = piatti[i].second;

        int now = b_search(a);
        int index = b_search(a+c);

        if(dp[now].second < dp[index].second+b)
            dp.push_back({a, dp[index].second+b});
    }

    printf("%d\n", dp.back().second);
}
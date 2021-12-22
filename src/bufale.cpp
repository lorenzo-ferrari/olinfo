#include <bits/stdc++.h>

#define MAXN 10000000

using namespace std;

long long solve(int N, int M[], int P[])
{
    long long result = 0;
    static int diff[MAXN];
    for(int i = 0; i < N; i++) {
        diff[i] = M[i]-P[i];
        result = result + M[i] + P[i];
    }
    nth_element(diff, diff+N/2, diff+N);
    for(int i = 0; i < N/2; i++)
        result -= diff[i];

    for(int i = N/2; i < N; i++)
        result += diff[i];

    return result/2;
}
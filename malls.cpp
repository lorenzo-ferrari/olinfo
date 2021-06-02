#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>

#define MAXN 100000

int N, K, maxDist, position;
int v[MAXN];

int main() {

      freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N, &K));
    for (int i = 0; i < N; i++) assert(1 == scanf("%d", &v[i]));
    std::sort(v, v+N);
    if(v[0] > K-v[N-1])
    {
        maxDist = v[0];
        position = 0;
    }
    else
    {
        maxDist = K - v[N-1];
        position = K;
    }

    for(int i = 1; i < N; i++)
    {
        int temp = (v[i]-v[i-1])/2;
        if(temp > maxDist)
        {
            maxDist = temp;
            position = (v[i]+v[i-1])/2;
        }
    }


    printf("%d\n", position);
    return 0;
}
#include <stdio.h>
#include <assert.h>
#define MAXN 1000000

int N, K, i, somma = 0, num = 0;
int L[MAXN];

int main() {

//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N, &K));
    for(i=0; i<N; i++)
    {
        assert(1 == scanf("%d", &L[i]));
        somma += L[i];
        int temp = L[i]/K;
        if(temp > 10 && L[i] != K*11)
            temp = 10;
        num += temp;
    }

    printf("%d %d\n", num, somma-K*num);
    return 0;
}
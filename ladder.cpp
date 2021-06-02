#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MAXN 1000000

int N, i, diff = 0;
int C[MAXN];

int main() {
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(1 == scanf("%d", &N));
    for(i=0; i<N; i++)
        assert(1 == scanf("%d", &C[i]));
    diff = fmax(diff, C[0]);
    for(i=1; i<N; i++)
        diff = fmax(diff, C[i]-C[i-1]);

    printf("%d\n", diff);
    return 0;
}


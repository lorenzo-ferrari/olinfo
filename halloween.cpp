#include <stdio.h>
#include <assert.h>

#define MAXN 100000

int N, i;
int C[MAXN];
long long int M, somma = 0;

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %lld", &N, &M));
    for(i=0; i<N; i++) {
        assert(1 == scanf("%d", &C[i]));
        somma += C[i];
    }
    M = M % somma;
    for(i = 0; M > 0; i++) {
        M -= C[i];
    }

    printf("%d\n", (i - 1 + N) % N);
    return 0;
}

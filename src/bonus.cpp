#include <stdio.h>
#include <assert.h>

#define MAXN 100000

long long N, best;
long long S[MAXN], P[MAXN];
double punti = 0, somma = 0;
double massimo = 0;

int main() {

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

    assert(1 == scanf("%lld", &N));
    for(long long i=0; i<N; i++) {
        assert(1 == scanf("%lld", &S[i]));
        punti += S[i];
        assert(1 == scanf("%lld", &P[i]));
        somma += P[i];
    }

    for(long long i = 0; i < N; i++)
    {
        double temp = (punti-S[i])/(somma-P[i]);
        if(temp > massimo)
        {
            massimo = temp;
            best = i;
        }
    }

    printf("%lld\n", best); // print the result
    return 0;
}


#include <cmath>
int quadri(int N, long long M, int V[])
{
    long long somma = 0;
    int i, j = 0, B = N;
    for(i = 0; j < N; i++)
    {
        while(somma + V[j] <= M  &&  j < N)
        {
            somma += V[j];
            j++;
        }
        B = fmin(B, j - i);
        somma -= V[i];
    }
    return B;
}
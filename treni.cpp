#include <cmath>
int v[1000001] { };
int tempo_massimo(int n, int a[], int b[])
{
    if(n == 0)
        return 0;
    if(n == 1)
    {
        v[n] = fmax(a[0], b[0]);
        return v[n];
    }
    if(v[n] == 0)
    {
        v[n] = fmax(a[n-1] + tempo_massimo(n-1, a, b), b[n-1] + tempo_massimo(n-2, a, b));
    }
    return v[n];
}

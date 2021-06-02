bool visita(int N, int A[])
{
    long long sommaTOT = 0, sommaTemp = 0;
    for(int i = 0; i < N; i++)
    {
        sommaTOT += A[i];
    }
    for(int i = 0; i < N; i++)
    {
        if((2 * sommaTemp) == (sommaTOT - A[i])) return true;
        sommaTemp += A[i];
    }

    return false;
}

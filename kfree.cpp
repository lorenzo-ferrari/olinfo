#include <algorithm>
bool m[100000001];
int Trova(int n, int k, int v[])
{
    if(k == 1)
    return 0;
    int counter = 0;
    std::sort(v, v + n);
    for(int i = 0; i < n; i++)
        if(!m[v[i]]) {
            counter++;
            m[v[i]] = 1;
            m[v[i] * k] = 1;
        }
    return counter;
}

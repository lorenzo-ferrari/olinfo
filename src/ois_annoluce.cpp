#include <bits/stdc++.h>

#define MAXN 100001

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, Q;
long double x, y, z;
long double query;
long double dist[MAXN];

int ricerca_binaria(long double target) 
{
    int up = N-1;
    int down = 0;

    if(dist[up] <= target) return N;

    while(up-down > 1)
    {
        int mid = (up+down+1)/2;

        if(dist[mid] > target)
            up = mid;
        else
            down = mid;
    }

    return up;
}

int main()
{
    in >> N;

    for(int i = 0; i < N; i++)
    {
        in >> x >> y >> z;
        dist[i] = (long double)sqrt(x*x + y*y + z*z);
    }

    sort(dist, dist + N);

    in >> Q;

    for(int i = 0; i < Q; i++)
    {
        in >> query;
        out << ricerca_binaria(query) << "\n";
    }

    in.close();
    out.close();

    return 0;
}
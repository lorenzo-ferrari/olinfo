#include <fstream>
#include <cmath>
using namespace std;

int n;
int v[1001];
int c[1001];
long long m[1001][1003] { };

long long torri(int i, int h)
{
    if(i == n)
        m[i][h] = 0;
    else if(m[i][h] == 0)
    {
        if(v[i] < h || i == 0)
            m[i][h] = fmin(torri(i+1, v[i]), torri(i+1, h) + c[i]);
        else
            m[i][h] = torri(i+1, h) + c[i];
    }

    return m[i][h];
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    in >> n;
    for(int i = 0; i < n; i++)
        in >> v[i] >> c[i];

    out << torri(0, 1001);
}

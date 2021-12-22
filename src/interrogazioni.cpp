#include <fstream>
#include <algorithm>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, k, minimo = 131072; //minimo = 1 << 17;
    int v[10000];
    in >> n >> k;
    for(int i = 0; i < n; i++)
    {
        in >> v[i];
    }
    sort(v, v + n);
    for(int i = 0; i <= n - k; i++)
    {
        if(minimo > v[i + k - 1] - v[i])
            minimo = v[i + k - 1] - v[i];
    }
    out << minimo;

    in.close();
    out.close();

    return 0;
}

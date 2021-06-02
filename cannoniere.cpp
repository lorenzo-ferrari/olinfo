#include <fstream>
using namespace std;
#define MAX 100
int v[MAX + 1] { };
int n, g, p, massimo = 0, player = 0;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> n;
    for(int i = 0; i < n; i++)
    {
        in >> g >> p;
        v[g] += p;
        if(v[g] > massimo)
        {
            player = g;
            massimo = v[g];
        }
    }

    out << player << " " << massimo;

    in.close();
    out.close();
    return 0;
}

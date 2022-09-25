#include <fstream>
#include <cmath>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n, massimo = -1;
    int v[100];
    in >> n;

    for(int i = 0; i < n; i++)
    {
        in >> v[i];
    }
    for(int i = 0; i < n - 1; i++)
    {
        massimo = fmax(massimo, abs(v[i] - v[i + 1]));
    }

    out << massimo;

    in.close();
    out.close();

    return 0;
}
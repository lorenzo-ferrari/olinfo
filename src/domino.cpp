#include <fstream>
#include <cmath>
using namespace std;

int domino(int n, int v[], int w[], bool controllo[], int prev)
{
    int massimo = 0;
    if(n == 0)
        return 0;
    for(int i = 0; i < n; i++)
    {
        if(prev == -1 && controllo[i] == false)
        {
            controllo[i] = true;
            massimo = fmax(massimo, fmax(domino(n, v, w, controllo, v[i]) + 1, domino(n, v, w, controllo, w[i]) + 1));
            controllo[i] = false;
        }
        else if(v[i] == prev && controllo[i] == false)
        {
            controllo[i] = true;
            massimo = fmax(massimo, domino(n, v, w, controllo, w[i]) + 1);
            controllo[i] = false;
        }
        else if(w[i] == prev && controllo[i] == false)
        {
            controllo[i] = true;
            massimo = fmax(massimo, domino(n, v, w, controllo, v[i]) + 1);
            controllo[i] = false;
        }
    }

    return massimo;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n;
    bool controllo[10] = {false};
    int v[10], w[10];
    in >> n;
    for(int i = 0; i < n; i++)
    {
        in >> v[i] >> w[i];
    }

    out << domino(n, v, w, controllo, -1);

    in.close();
    out.close();

    return 0;
}
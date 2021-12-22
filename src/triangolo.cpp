#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

int somma[200][200] { };

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, massimo = 0, temp;
    in >> n;
//INDICIZZO DA 1
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            in >> temp;
            somma[i][j] = temp + fmax(somma[i - 1][j], somma[i - 1][j - 1]);
        }
    }

    for(int j = 1; j <= n; j++)
    {
        massimo = fmax(massimo, somma[n][j]); //volendo si poteva direttamente effettuare un controllo durante lo riempimento della matrice
    }

    out << massimo;

    in.close();
    out.close();

    return 0;
}

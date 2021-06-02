#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int matrix[11][11] { };
int somma[11][11] { };

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, massimo = 0;
    in >> n;
//INDICIZZO DA 1
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= i; j++)
        {
            in >> matrix[i][j];
            somma[i][j] = matrix[i][j] + fmax(somma[i - 1][j], somma[i - 1][j - 1]);
        }
    }

    for(int j = 1; j <= n; j++)
    {
        massimo = fmax(massimo, somma[n][j]);
    }

    out << massimo;

    in.close();
    out.close();

    return 0;
}
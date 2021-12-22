#include <fstream>
#include <cmath>
using namespace std;

int viaggio(int pers, int n2, int n4, int n5, int n7, int p2, int p4, int p5, int p7)
{
    if(pers <= 0) return 0;
    int minimo = 1 << 30 ;
    if(n2 > 0)
        minimo = fmin(minimo, p2 + viaggio(pers - 2, n2 - 1, n4, n5, n7, p2, p4, p5, p7));
    if(n4 > 0)
        minimo = fmin(minimo, p4 + viaggio(pers - 4, n2, n4 - 1, n5, n7, p2, p4, p5, p7));
    if(n5 > 0)
        minimo = fmin(minimo, p5 + viaggio(pers - 5, n2, n4, n5 - 1, n7, p2, p4, p5, p7));
    if(n7 > 0)
        minimo = fmin(minimo, p7 + viaggio(pers - 7, n2, n4, n5, n7 - 1, p2, p4, p5, p7));

    return minimo;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int pers, n2, n4, n5, n7, p2, p4, p5, p7;
    in >> pers;
    in >> n2 >> p2;
    in >> n4 >> p4;
    in >> n5 >> p5;
    in >> n7 >> p7;

    out << viaggio(pers, n2, n4, n5, n7, p2, p4, p5, p7);

    in.close();
    out.close();

    return 0;
}
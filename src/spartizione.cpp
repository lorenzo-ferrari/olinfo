#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int g, p, somma = 0;
    in >> g >> p;

    for(int i = 1; g > 0; i++)
    {
        if(g >= i)
            somma += i;
        else
            somma += g;
        g -= (p - 1 + i);
    }

    out << somma;

    in.close();
    out.close();

    return 0;
}

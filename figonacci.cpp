#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    long index, modulo, somma = -1, n, nprev = 0;

    in >> index >> modulo;

    for(long i = 2; i <= index; i++)
    {
        n = (nprev * i - somma + modulo) % modulo;
        somma += n;
        somma = somma % modulo;
        nprev = n;
    }
    out << n % modulo;

    in.close();
    out.close();

    return 0;
}

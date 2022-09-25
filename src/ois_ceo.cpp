#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
     int n, imp;
     long long somma = 1, prod = 1;
     in >> n;
     for(int i = 0; i < n; i++)
     {
         in >> imp;
         prod*= imp;
         somma += prod;
     }
     out << somma;

    in.close();
    out.close();

    return 0;
}

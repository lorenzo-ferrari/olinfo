#include <fstream>
using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int n;
string a = "[O]";
string b = "[OOOO]";

void piastrelle(int n, string pref)
{
    if(n >= 2)
    {
        piastrelle(n - 1, pref + a);
        piastrelle(n - 2, pref + b);
    }
    else if (n == 1)
        piastrelle(n - 1, pref + a);

    if(n == 0)
        out << pref << endl;
}

int main()
{
    in >> n;
    piastrelle(n, "");

    in.close();
    out.close();

    return 0;
}
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    long long a, b;
    in >> a >> b;
    long long A = ceil(sqrt(a)), B = floor(sqrt(b));
    out << B - A + 1;

    return 0;
}
#include <fstream>
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if(b == 0)
        return a;
    return gcd(b, a%b);
}
int main()
{
    int a, b;
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> a >> b;

    int i = 20;
    while(gcd(a, i) != 1)
        i++;

    out << a/gcd(a, b) << " " << i;

    in.close();
    out.close();
}

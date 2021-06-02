#include <fstream>
#include <cmath>
using namespace std;

int salta(int n, int E[])
{

    int counter = 0;
    for(int i = 1; i < n; i++)
    {
        if(E[i] < E[i-1]-1)
            E[i] = E[i-1]-1;
    }
    int pos = 0;
    while(pos < n)
    {

        counter++;
        pos += E[pos];
    }

    return counter;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n;
    int E[100000];
    in >> n;
    for(int i = 0; i < n; i++)
    {
        in >> E[i];
    }

    out << salta(n, E);

    return 0;
}
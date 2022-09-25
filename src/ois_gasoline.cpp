#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n, minimo = 1001;
    long long somma = 0;
    int price[1000000], distance[1000000];
    in >> n;

    for(int i = 0; i < n; i++)
    {
        in >> price[i];
    }
    for(int i = 0; i < n; i++)
    {
        in >> distance[i];
    }
    for(int i = 0; i < n; i++)
    {
        if(minimo > price[i])
            minimo = price[i];
        somma += minimo * distance[i];
    }

    out << somma;

    in.close();
    out.close();

    return 0;
}

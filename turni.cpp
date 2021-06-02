#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, k, estremo1, estremo2, index = 0, counter = 0;
    int best[50];
    fill_n(best, 50, 0);
    in >> k >> n;

    for(int i = 0; i < n; i++)
    {
        in >> estremo1 >> estremo2;
        if(estremo2 - estremo1 > best[estremo1])
            best[estremo1] = estremo2 - estremo1;
    }

    for(int i = 0; i < k - 1; i++)
    {
        if(best[i] - 1 > best[i + 1])
            best[i + 1] = best[i] - 1;
    }

    for(index = 0, counter = 0; index < k; counter++)
    {
        index = index + best[index] + 1;
    }

    out << counter;

    out.close();
    in.close();

    return 0;
}
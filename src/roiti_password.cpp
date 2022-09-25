#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>

#define mod 1000000007
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int N;
    long long K, radcount = 0;
    in >> N >> K;

    double radk = sqrt(K);

    vector<int> freq(radk+1,0);
    vector<long long> coda;

    for (int i=0; i<N; i++)
    {
        long long temp;
        in >> temp;
        if (temp > radk)
            coda.push_back(temp);
        else if(temp != radk)
            freq[temp]++;
        else
            radcount++;
    }

    long long coppie = 0;
    for (int i=0; i<coda.size(); i++)
    {
        if (K%coda[i] == 0)
            coppie += freq[K/coda[i]];
        coppie %= mod;
    }


    coppie += radcount*(radcount-1)/2;

    out << coppie%mod;
}


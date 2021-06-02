#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int N, K;
    int T[1000000];
    long long sommaMax = 0, sommaTemp;

    in >> N;
    in >> K;

    for(int i = 0; i < N; i++)
    {
        in >> T[i];
    }
    for(int i = 0; i < K; i++)
    {
        sommaMax += T[i];
    }
    sommaTemp = sommaMax;
    for(int i = 0; i < N - K; i++)
    {
        sommaTemp = sommaTemp - T[i] + T[i + K];
        if(sommaTemp > sommaMax)
            sommaMax = sommaTemp;
    }
    out << sommaMax;

    in.close();
    out.close();

    return 0;
}
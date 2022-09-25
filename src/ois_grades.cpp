#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int V[100000];
    int N, voto, dimesione, inizio = -1, fine = -1;
    in >> N;
    for(int i = 0; i < N; i++)
    {
        in >> voto;
        V[i] = voto;
        if(voto > 5)
        {
            fine = i;
        }
    }
    for(int i = N - 1; i > -1; i--)
    {
        if(V[i] < 6)
        {
            inizio = i;
        }
    }
    if((inizio != -1 && fine != -1) && fine-inizio > 0)
    {
        out << fine - inizio + 1;
    }
    else
    {
        out << -1;
    }

    return 0;
}

#include <fstream>
using namespace std;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int n, m, macchina, s1, s2;
    int v[31];
    in >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        in >> macchina;
        v[macchina] = i;
    }
    for(int i = 0; i < m; i++)
    {
        in >> s1 >> s2;
        v[s1]--;
        v[s2]++;
    }

    for(int i = 1; i <= n; i++)
    {
        if(v[i] == 1)
            out << i;
    }
    in.close();
    out.close();

    return 0;
}
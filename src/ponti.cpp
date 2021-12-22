#include <fstream>
#include <vector>
#include <algorithm>
#define MAXN 10000
using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

bool visita[MAXN]{ };
vector<int> graph [MAXN];

void dfs(int n)
{
    if(visita[n] == 0) {
        visita[n] = 1;
        for(int i = 0; i < graph[n].size(); i++)
            dfs(graph[n][i]);
    }
}

int n, m, counter = 0;

int main()
{
    in >> n >> m;
    for(int i = 0; i < m; i++) {
        int nI, nF;
        in >> nI >> nF;
        graph[nI].push_back(nF);
        graph[nF].push_back(nI);
    }
    dfs(0);
    for(int i = 0; i < n; i++) {
        if(visita[i] == 0)
        {
            dfs(i);
            counter++;
        }
    }

    out << counter;

    in.close();
    out.close();
}
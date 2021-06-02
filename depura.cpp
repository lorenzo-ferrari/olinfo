#include <bits/stdc++.h>
#define MAXN 2000
using namespace std;

vector <int> graph[MAXN + 1];
bool pres[MAXN + 1];
bool impossibile = false;

void dfs(int n)
{
    if(!pres[n]) {
        pres[n] = 1;
        if(graph[n].size() == 0)
            impossibile = true;
        else
            for(int i = 0; i < graph[n].size(); i++) dfs(graph[n][i]);
    }
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int K, R, sostanza, numReg, regola, cur;
    in >> K >> R;
    for(int i = 0; i < K; i++) {
        in >> sostanza;
        pres[sostanza] = 1;
    }
    for(int i = 0; i < R; i++) {
        in >> sostanza >> numReg;
        for(int j = 0; j < numReg; j++) {
            in >> regola;
            graph[sostanza].push_back(regola);
        }
    }
    int counter = 0;
    dfs(1);
    for(int i = 1; i <= MAXN; i++)
        if(pres[i])
            counter++;

    if(impossibile)
        out << -1;
    else
        out << counter - K;

    in.close();
    out.close();
}

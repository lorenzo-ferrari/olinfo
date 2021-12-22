#include <bits/stdc++.h>

#define MAXN 10000
#define INF 1000000000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");



int N, M, u, v, cur, prec;
vector <int> graph[MAXN];
int H[MAXN];
bool vis[MAXN];

int main()
{
    in >> N >> M;
    
    for(int i = 0; i < N; i++)
        in >> H[i];
        
    for(int i = 0; i < M; i++)
    {
        in >> u >> v;
        
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    while(!vis[cur])
    {
        vis[cur] = 1;
        
        int minimo = INF, dir = -1;
        
        for(int i = 0; i < graph[cur].size(); i++)
        {
            int temp = graph[cur][i];
            
            if(temp != prec && H[temp] < minimo) 
            {
                dir = temp;
                minimo = H[temp];
            }
        }

        prec = cur;
        
        if(dir == -1)
            break;

        cur = dir;
    }
    
    out << cur;
    
    in.close();
    out.close();
}

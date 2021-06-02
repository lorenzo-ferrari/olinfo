#include <bits/stdc++.h>

#define MAXN 2000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

bitset <MAXN> adj [MAXN];

int main()
{
    int N;
    bool temp;
    
    in >> N;
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            in >> temp;
            if(temp)
                adj[i][j] = 1;
        }
            
    for(int i = 0; i < N-1; i++)
    {
        for(int j = i+1; j < N; j++)
        {
            if(adj[i][j] && (~adj[i] & adj[j]).any())
            {
                out << i+1 << " " << j+1 << " " << (~adj[i] & adj[j])._Find_first()+1;
                return 0;
            }
                
        }
    }
    
    out << -1;
    
}

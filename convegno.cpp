#include <bits/stdc++.h>

using namespace std;

int somma;
vector <int> tree[100001];

int coppie_function (int v)
{
    int tot = 0;
    
    for(int i = 0; i < tree[v].size(); i++)
        tot += coppie_function(tree[v][i])+1;
        
    somma += tot;
    
    return tot;
}

int coppie(int N, int C[])
{
    for(int i = 1; i <= N; i++)
        tree[C[i-1]+1].push_back(i);
        
    int just_for_start = coppie_function(0);
    
    return somma-N;
    
}
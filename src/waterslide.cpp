#include <bits/stdc++.h>
#define MAXN 100001
using namespace std;

int n, m, p;
vector <int> graph[MAXN];
double prob[MAXN];
bitset <MAXN> vis;
vector <int> st;

void dfs(int v){
    vis[v] = 1;
    for(int x : graph[v])
        if(!vis[x])
            dfs(x);
    st.push_back(v);
}

inline int get_int()
{
    int n = 0; 
    char c = getchar_unlocked();
    while(c >= '0')
    {
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }

    return n;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    n = get_int();
    m = get_int();
    p = get_int();

    for(int i = 0, u, v; i < m; i++){
        u = get_int();
        v = get_int();
        graph[u].push_back(v);
    }

    dfs(0);
    reverse(st.begin(), st.end());
    prob[0] = 1.0;

    for(int& i : st)
        for(int& j : graph[i])
            prob[j] += prob[i]/graph[i].size();
    
    printf("%ld\n", distance(prob, max_element(prob+n-p, prob+n)));
}
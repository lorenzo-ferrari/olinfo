#include <bits/stdc++.h>
#define MAXN 10000
using namespace std;

int main(){
    freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);
    int n, e;
    int m[MAXN];
    bitset <MAXN> vis;
    vector <int> graph[MAXN];
    scanf("%d%d", &n, &e);
    for(int i = 0; i < n; i++)
        scanf("%d", &m[i]);
    for(int i = 0, u, v; i < e; i++){
        scanf("%d%d", &u, &v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    stack <int> st;
    vis[0] = 1;
    st.push(0);
    while(!st.empty()){
        int cur = st.top();
        st.pop();
        for(int u : graph[cur])
            if(!vis[u]){
                vis[u] = 1;
                st.push(u);
            }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) ans += m[i]*vis[i];
    printf("%d\n", ans);
}
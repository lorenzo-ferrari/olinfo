#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int N = 1e6;
int n, ordered, timer=1;
pair<int, int> t[2*N];
int idxToOrder[N], until[N];
vector <int> graph[N];
bitset <N> vis;

int dfs(int v){
    idxToOrder[v] = ordered++;
    int ans = ordered;
    vis[v] = 1;
    for(int u : graph[v])
        if(!vis[u])
            ans = dfs(u);

    return until[v] = ans;
}

void range_update(int l, int r, int value){ //update in range [l, r)
    for(l+=n, r+=n; l<r; l>>=1, r>>=1){
        if(l&1) t[l++] = {value, timer};
        if(r&1) t[--r] = {value, timer};
    }
}

int query(int v){
    int ans = 0, ans_time = -1;
    for(v+=n; v>0; v>>=1){
        if(ans_time < t[v].second){
            ans = t[v].first;
            ans_time = t[v].second;
        }
    }

    return ans;
}

inline int get_int(){
    int a = 0;
    char c = getchar_unlocked();
    if(c < '0') c = getchar_unlocked();
    while(c >= '0'){
        a = 10*a+c-'0';
        c = getchar_unlocked();
    }
    return a;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int dummy = get_int();
    int p = get_int();
    int e = get_int();
    n = dummy+p;
    scanf("%d", &dummy); //dummy per evitare il -1
    for(int i = 1, par; i < n; i++){
        par = get_int();
        graph[par].push_back(i);           
    }

    dummy = dfs(0);

    for(int event, v; timer <= e; timer++){
        event = get_int();
        v = get_int();
        if(event == 0){
            range_update(idxToOrder[v], until[v], 0);
        }
        else if(event == 1){
            range_update(idxToOrder[v], until[v], 1);
        }
        else if(event == 2){
            printf("%d\n", query(idxToOrder[v]));
        }
    }
}
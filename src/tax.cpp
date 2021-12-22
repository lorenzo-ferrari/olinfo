#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

inline int get_int(){
    int n = 0;
    char c = getchar_unlocked();
    while(c >= '0'){
        n = 10*n+c-'0';
        c = getchar_unlocked();
    }
    return n;
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    double dist[300][300] { };
    int n = get_int(), m = get_int();
    for(int i = 0; i < n; i++) dist[i][i] = 1.0;
    for(int i = 0, a, b, c; i < m; i++){
        a = get_int();
        b = get_int();
        c = get_int();
        dist[a][b] = 1.0-c/1000.0;
    }

    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(dist[i][j] < dist[i][k]*dist[k][j])
                    dist[i][j] = dist[i][k]*dist[k][j];

    double worst = 1.0;
    pair<int, int> ans = {0, 0};
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(dist[i][j] < worst){
                worst = dist[i][j];
                ans = {i, j};
            }

    printf("%d %d\n", ans.first, ans.second);
}
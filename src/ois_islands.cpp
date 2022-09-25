#include <bits/stdc++.h>

#define MAXN 1000

using namespace std;

bool m[MAXN][MAXN];
bool vis[MAXN][MAXN];
int r, c, counter;

void dfs(int i, int j)
{
    if(i<0 || j<0 || i>=r || j>=c || vis[i][j] || !m[i][j]) return;

    vis[i][j] = 1;

    dfs(i-1, j);
    dfs(i+1, j);
    dfs(i, j+1);
    dfs(i, j-1);
}

int main() {
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    in >> r >> c;

    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            in >> m[i][j];

    for(int i = 1; i < r-1; i++) {
        if(!vis[i][0])
            dfs(i, 0);
        if(!vis[i][c-1])
            dfs(i, c-1);
    }
    for(int i = 1; i < c-1; i++) {
        if(!vis[0][i])
            dfs(0, i);
        if(!vis[r-1][i])
            dfs(r-1, i);
    }

    for(int i = 1; i < r-1; i++) {
        for(int j = 1; j < c-1; j++) {
            if(!vis[i][j] && m[i][j]) {
                dfs(i, j);
                counter++;
            }
        }
    }

    out << counter;

}

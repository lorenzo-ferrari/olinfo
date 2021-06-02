#include <queue>
#include <stdio.h>
#include <iostream>
using namespace std;

int n, m, ans;
char mp [1000][1000];
bool vis[1000][1000];

bool estintore;

void dfs(int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || mp[i][j] == '#' || vis[i][j]) return;
    if (mp[i][j] == '@') estintore = true;

    vis[i][j] = true;

    dfs(i + 1, j);
    dfs(i - 1, j);
    dfs(i, j + 1);
    dfs(i, j - 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d%d", &n, &m);

    char dummy;
    for (int i = 0; i < n; i++) {
        scanf("%c", &dummy);
        for (int j = 0; j < m; j++) {
            scanf("%c", &mp[i][j]);
        }
    }
    
    // for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cout << mp[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mp[i][j] != '#' && !vis[i][j]) {
                estintore = false;
                dfs(i, j);
                ans += !estintore;
            }
        }
    }

    printf("%d\n", ans);
}
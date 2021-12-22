#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");

  int n;
  cin >> n;

  const int N = 105;
  char g[N][N] {};

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cin >> g[i][j];

  int d[N][N];
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      d[i][j] = 1e9;

  bool vis[N][N] {};
  queue<pair<int, int>> Q;

  Q.push({1, 1});
  d[1][1] = 1;

  while (!Q.empty()) {
    int x = Q.front().first;
    int y = Q.front().second;
    Q.pop();

/*
    if (vis[x][y])
      continue;
    vis[x][y] = true;
*/

    if (g[x-1][y  ] == '*' && d[x-1][y  ] > d[x][y] + 1) {d[x-1][y  ] = d[x][y] + 1; Q.push({x-1, y  });}
    if (g[x-1][y-1] == '*' && d[x-1][y-1] > d[x][y] + 1) {d[x-1][y-1] = d[x][y] + 1; Q.push({x-1, y-1});}
    if (g[x  ][y-1] == '*' && d[x  ][y-1] > d[x][y] + 1) {d[x  ][y-1] = d[x][y] + 1; Q.push({x  , y-1});}
    if (g[x+1][y-1] == '*' && d[x+1][y-1] > d[x][y] + 1) {d[x+1][y-1] = d[x][y] + 1; Q.push({x+1, y-1});}
    if (g[x+1][y  ] == '*' && d[x+1][y  ] > d[x][y] + 1) {d[x+1][y  ] = d[x][y] + 1; Q.push({x+1, y  });}
    if (g[x+1][y+1] == '*' && d[x+1][y+1] > d[x][y] + 1) {d[x+1][y+1] = d[x][y] + 1; Q.push({x+1, y+1});}
    if (g[x  ][y+1] == '*' && d[x  ][y+1] > d[x][y] + 1) {d[x  ][y+1] = d[x][y] + 1; Q.push({x  , y+1});}
    if (g[x-1][y+1] == '*' && d[x-1][y+1] > d[x][y] + 1) {d[x-1][y+1] = d[x][y] + 1; Q.push({x-1, y+1});}
  }

  cout << d[n][n] << endl;
}
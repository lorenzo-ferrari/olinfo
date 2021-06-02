#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
using namespace std;

const int N = 1001;

int main() {
#ifdef EVAL
  ifstream cin ("input.txt");
  ofstream cout ("output.txt");
#endif

  int n, m;
  cin >> n >> m;

  int d[N][N];
  char g[N][N];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> g[i][j];
      d[i][j] = 1e9;
    }
  }

  d[0][0] = 0;

  queue<pair<int, int>> Q;
  Q.push({0, 0});

  while (!Q.empty()) {
    int x = Q.front().first;
    int y = Q.front().second;
    Q.pop();

    if (x>0   && y>0   && g[x-1][y-1]=='.' && d[x-1][y-1]>d[x][y]+1) {d[x-1][y-1]=d[x][y]+1; Q.push({x-1,y-1});}
    if (x>0   &&          g[x-1][y  ]=='.' && d[x-1][y  ]>d[x][y]+1) {d[x-1][y  ]=d[x][y]+1; Q.push({x-1,y  });}
    if (x>0   && y<m-1 && g[x-1][y+1]=='.' && d[x-1][y+1]>d[x][y]+1) {d[x-1][y+1]=d[x][y]+1; Q.push({x-1,y+1});}
    if (         y<m-1 && g[x  ][y+1]=='.' && d[x  ][y+1]>d[x][y]+1) {d[x  ][y+1]=d[x][y]+1; Q.push({x  ,y+1});}
    if (x<n-1 && y<m-1 && g[x+1][y+1]=='.' && d[x+1][y+1]>d[x][y]+1) {d[x+1][y+1]=d[x][y]+1; Q.push({x+1,y+1});}
    if (x<n-1 &&          g[x+1][y  ]=='.' && d[x+1][y  ]>d[x][y]+1) {d[x+1][y  ]=d[x][y]+1; Q.push({x+1,y  });}
    if (x<n-1 && y>0   && g[x+1][y-1]=='.' && d[x+1][y-1]>d[x][y]+1) {d[x+1][y-1]=d[x][y]+1; Q.push({x+1,y-1});}
    if (         y>0   && g[x  ][y-1]=='.' && d[x  ][y-1]>d[x][y]+1) {d[x  ][y-1]=d[x][y]+1; Q.push({x  ,y-1});}

    if (x>1   && g[x-2][y  ]=='.' && d[x-2][y  ]>d[x][y]+1) {d[x-2][y  ]=d[x][y]+1; Q.push({x-2,y  });}
    if (x<n-2 && g[x+2][y  ]=='.' && d[x+2][y  ]>d[x][y]+1) {d[x+2][y  ]=d[x][y]+1; Q.push({x+2,y  });}
    if (y>1   && g[x  ][y-2]=='.' && d[x  ][y-2]>d[x][y]+1) {d[x  ][y-2]=d[x][y]+1; Q.push({x  ,y-2});}
    if (y<m-2 && g[x  ][y+2]=='.' && d[x  ][y+2]>d[x][y]+1) {d[x  ][y+2]=d[x][y]+1; Q.push({x  ,y+2});}
  }

  cout << d[n-1][m-1] << "\n";
}
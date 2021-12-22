#include <bits/stdc++.h>

#define INF 1000000000
#define MAXN 200

using namespace std;

typedef pair <int, int> pii;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, Xi, Yi, Xf, Yf;
bool inizio;
char temp;
bool obstacles[MAXN][MAXN];
bool vis[MAXN][MAXN][4];
int curve_to_here[MAXN][MAXN][4];

void fill_matrix()
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            curve_to_here[i][j][0] = INF;
            curve_to_here[i][j][1] = INF;
            curve_to_here[i][j][2] = INF;
            curve_to_here[i][j][3] = INF;
        }
}

int main()
{
    in >> N;
    
    fill_matrix();
    
    for(int x = 0; x < N; x++)
    {
        for(int y = 0; y < N; y++)
        {
            in >> temp;
            if(temp == '#')
                obstacles[x][y] = 1;
            else if(temp == 'T' && !inizio)
            {
                Xi = x;
                Yi = y;
                inizio = 1;
            }
            else if(temp == 'T' && inizio)
            {
                Xf = x;
                Yf = y;
            }
        }
    }
    
    curve_to_here[Xi][Yi][0] = 0;
    curve_to_here[Xi][Yi][1] = 0;
    curve_to_here[Xi][Yi][2] = 0;
    curve_to_here[Xi][Yi][3] = 0;
    
    priority_queue <pair<pii, pii>> Q;
    
    Q.push({{0, 0}, {Xi, Yi}});
    Q.push({{0, 1}, {Xi, Yi}});
    Q.push({{0, 2}, {Xi, Yi}});
    Q.push({{0, 3}, {Xi, Yi}});
    
    while(!Q.empty())
    {
        int curve = -Q.top().first.first;
        int dir = Q.top().first.second;
        int Xcur = Q.top().second.first;
        int Ycur = Q.top().second.second;
        
        Q.pop();
        
        if(Xcur < 0 || Xcur >= N || Ycur < 0 || Ycur >= N || vis[Xcur][Ycur][dir])
            continue;
            
        vis[Xcur][Ycur][dir] = 1;
        
        switch (dir)
        {
            case 0: if(Xcur+1 >= 0 && Xcur+1 < N  && !obstacles[Xcur+1][Ycur] && curve_to_here[Xcur+1][Ycur][0] > curve)
                    {
                        curve_to_here[Xcur+1][Ycur][0] = curve;
                        Q.push({{-curve, 0}, {Xcur+1, Ycur}});
                    }
                    if(Ycur+1 >= 0 && Ycur+1 < N  && !obstacles[Xcur][Ycur+1] && curve_to_here[Xcur][Ycur+1][1] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur+1][1] = curve+1;
                        Q.push({{-(curve+1), 1}, {Xcur, Ycur+1}});
                    }
                    if(Xcur-1 >= 0 && Xcur-1 < N  && !obstacles[Xcur-1][Ycur] && curve_to_here[Xcur-1][Ycur][2] > curve+1)
                    {
                        curve_to_here[Xcur-1][Ycur][2] = curve+1;
                        Q.push({{-(curve+1), 2}, {Xcur-1, Ycur}});
                    }
                    if(Ycur-1 >= 0 && Ycur-1 < N  && !obstacles[Xcur][Ycur-1] && curve_to_here[Xcur][Ycur-1][3] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur-1][1] = curve+1;
                        Q.push({{-(curve+1), 3}, {Xcur, Ycur-1}});
                    }
                    
                    break;
            
            case 1: if(Xcur+1 >= 0 && Xcur+1 < N  && !obstacles[Xcur+1][Ycur] && curve_to_here[Xcur+1][Ycur][0] > curve+1)
                    {
                        curve_to_here[Xcur+1][Ycur][0] = curve+1;
                        Q.push({{-(curve+1), 0}, {Xcur+1, Ycur}});
                    }
                    if(Ycur+1 >= 0 && Ycur+1 < N  && !obstacles[Xcur][Ycur+1] && curve_to_here[Xcur][Ycur+1][1] > curve)
                    {
                        curve_to_here[Xcur][Ycur+1][1] = curve;
                        Q.push({{-curve, 1}, {Xcur, Ycur+1}});
                    }
                    if(Xcur-1 >= 0 && Xcur-1 < N  && !obstacles[Xcur-1][Ycur] && curve_to_here[Xcur-1][Ycur][2] > curve+1)
                    {
                        curve_to_here[Xcur-1][Ycur][2] = curve+1;
                        Q.push({{-(curve+1), 2}, {Xcur-1, Ycur}});
                    }
                    if(Ycur-1 >= 0 && Ycur-1 < N  && !obstacles[Xcur][Ycur-1] && curve_to_here[Xcur][Ycur-1][3] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur-1][1] = curve+1;
                        Q.push({{-(curve+1), 3}, {Xcur, Ycur-1}});
                    }
                    
                    break;
            
            case 2: if(Xcur+1 >= 0 && Xcur+1 < N  && !obstacles[Xcur+1][Ycur] && curve_to_here[Xcur+1][Ycur][0] > curve+1)
                    {
                        curve_to_here[Xcur+1][Ycur][0] = curve+1;
                        Q.push({{-(curve+1), 0}, {Xcur+1, Ycur}});
                    }
                    if(Ycur+1 >= 0 && Ycur+1 < N  && !obstacles[Xcur][Ycur+1] && curve_to_here[Xcur][Ycur+1][1] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur+1][1] = curve;
                        Q.push({{-(curve+1), 1}, {Xcur, Ycur+1}});
                    }
                    if(Xcur-1 >= 0 && Xcur-1 < N  && !obstacles[Xcur-1][Ycur] && curve_to_here[Xcur-1][Ycur][2] > curve)
                    {
                        curve_to_here[Xcur-1][Ycur][2] = curve;
                        Q.push({{-curve, 2}, {Xcur-1, Ycur}});
                    }
                    if(Ycur-1 >= 0 && Ycur-1 < N  && !obstacles[Xcur][Ycur-1] && curve_to_here[Xcur][Ycur-1][3] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur-1][1] = curve+1;
                        Q.push({{-(curve+1), 3}, {Xcur, Ycur-1}});
                    }
                    
                    break;
                    
            case 3: if(Xcur+1 >= 0 && Xcur+1 < N  && !obstacles[Xcur+1][Ycur] && curve_to_here[Xcur+1][Ycur][0] > curve+1)
                    {
                        curve_to_here[Xcur+1][Ycur][0] = curve+1;
                        Q.push({{-(curve+1), 0}, {Xcur+1, Ycur}});
                    }
                    if(Ycur+1 >= 0 && Ycur+1 < N  && !obstacles[Xcur][Ycur+1] && curve_to_here[Xcur][Ycur+1][1] > curve+1)
                    {
                        curve_to_here[Xcur][Ycur+1][1] = curve+1;
                        Q.push({{-(curve+1), 1}, {Xcur, Ycur+1}});
                    }
                    if(Xcur-1 >= 0 && Xcur-1 < N  && !obstacles[Xcur-1][Ycur] && curve_to_here[Xcur-1][Ycur][2] > curve+1)
                    {
                        curve_to_here[Xcur-1][Ycur][2] = curve+1;
                        Q.push({{-(curve+1), 2}, {Xcur-1, Ycur}});
                    }
                    if(Ycur-1 >= 0 && Ycur-1 < N  && !obstacles[Xcur][Ycur-1] && curve_to_here[Xcur][Ycur-1][3] > curve)
                    {
                        curve_to_here[Xcur][Ycur-1][1] = curve;
                        Q.push({{-curve, 3}, {Xcur, Ycur-1}});
                    }
                    
                    break;
        }
    }
    
    if(curve_to_here[Xf][Yf][0] == INF && curve_to_here[Xf][Yf][1] == INF && curve_to_here[Xf][Yf][2] == INF && curve_to_here[Xf][Yf][3] == INF)
    {
        out << -1;
    }
    else
    {
        out << min(min(curve_to_here[Xf][Yf][0], curve_to_here[Xf][Yf][1]), min(curve_to_here[Xf][Yf][2], curve_to_here[Xf][Yf][3]));
    }
    
    in.close();
    out.close();
    
    return 0;
}


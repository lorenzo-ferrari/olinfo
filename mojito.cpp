#include <bits/stdc++.h>

#define MAXN 101

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

typedef pair<int, int> pii;

int X, Y, N, xm, ym, counter;
pii R[MAXN];
pii P[MAXN];
bool gioca[MAXN];

int vicino(int x, int y) {
    int tempVicino = 0, dist = abs(x-R[0].first) + abs(y-R[0].second), tempDist;
    for(int i = 1; i < N; i++) {
        tempDist = abs(x-R[i].first) + abs(y-R[i].second);
        if(tempDist < dist) {
            dist = tempDist;
            tempVicino = i;
        }
        else if(tempDist == dist) {
            
            if(R[tempVicino].first < R[i].first)
                continue;
            else if(R[tempVicino].first > R[i].first) {
                dist = tempDist;
                tempVicino = i;
            }
            else if(R[tempVicino].second < R[i].second)
                continue;
            else {
                dist = tempDist;
                tempVicino = i;
            }
        }
    } 
    
    return tempVicino;
}

int main()
{
    in >> X >> Y >> xm >> ym >> N;
    
    for(int i = 0; i < N; i++)
        in >> R[i].first >> R[i].second >> P[i].first >> P[i].second;
    
    int dir = vicino(xm, ym);
    
    while(!gioca[dir]) {
        gioca[dir] = 1;
        counter++;
        dir = vicino(P[dir].first, P[dir].second);
    }
    
    out << counter;
    
    in.close();
    out.close();
}

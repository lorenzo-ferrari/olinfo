#include <bits/stdc++.h>

#define MAXN 100000

using namespace std;

vector <int> graph[MAXN];
bool pari [MAXN];
bool disp [MAXN];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N, M; assert(2 == scanf("%d %d", &N, &M));
    int sor, dest, cur, temp;
    for(int i=0; i<M; i++) {
        assert(2 == scanf("%d %d", &sor, &dest));
        graph[sor].push_back(dest);
    }
    queue <int> Q;
    Q.push(0);
    pari[0] = 1;
    while(!Q.empty()) {
        cur = Q.front();
        Q.pop();
        for(int i = 0; i < graph[cur].size(); i++) {
            temp = graph[cur][i];
            if(pari[cur] && !disp[temp]) {
                Q.push(temp);
                disp[temp] = 1;
            }
            if(disp[cur] && !pari[temp]) {
                Q.push(temp);
                pari[temp] = 1;
            }
        }
    }
    int counter = 0;
    for(int i = 0; i < N; i++)
        if(pari[i])
            counter++;
    printf("%d", counter);
}

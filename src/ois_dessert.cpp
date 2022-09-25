#include <bits/stdc++.h>
#define MAXN 1000000

using namespace std;

int N, M, amico, cur, counter = 0;
vector <int> v[MAXN];
int L[MAXN];
bool control[MAXN];
queue <int> Q;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    assert(1 == scanf("%d", &N));
    for (int i=0; i<N; i++) {
        assert(2 == scanf("%d %d", &M, &L[i]));
        for (int j=0; j<M; ++j) {
            assert(1 == scanf("%d", &amico));
            v[amico].push_back(i);
        }
    }
    for(int i = 0; i < N; i++)
        if(L[i] == 0)
            Q.push(i);

    while(!Q.empty()) {
        cur = Q.front();
        Q.pop();
        if(control[cur])
            continue;
        control[cur] = 1;
        counter++;
        for(int i = 0; i < v[cur].size(); i++) {
            L[v[cur][i]]--;
            if(L[v[cur][i]] <= 0) {
                Q.push(v[cur][i]);
            }
        }
    }


    printf("%d\n", counter);

    return 0;
}

#include <bits/stdc++.h>

#define MAXN 1000000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

typedef pair <int, int> pii;

int N, L, minimo = 2147483647;
int H[MAXN];
pii temp;
deque <pii> Q;
priority_queue <pii> removed;

int main()
{
    in >> N >> L;

    for(int i = 0; i < N; i++) {
        in >> H[i];

        if(!Q.empty() && Q.front().second <= i-L)
            Q.pop_front();

        while(!Q.empty() && Q.back().first < H[i]) {
            temp = Q.back();
            Q.pop_back();
            removed.push(temp);
        }

        Q.push_back({H[i], i});

        while(!removed.empty() && removed.top().second <= i-L)
            removed.pop();

        if(i >= L-1 && !Q.empty() && !removed.empty())
            minimo = min(minimo, abs(Q.front().first - removed.top().first));
        if(i >= L-1 && Q.size() >= 2)
            minimo = min(minimo, Q[0].first-Q[1].first);
    }

    out << minimo/2 << "\n";
}

#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

typedef pair<int, int> pii;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, M, A, B, W, K;
int money[MAXN];
vector <pair<pii, int>> trans;

int main()
{
    in >> N >> M;

    for(int i = 0; i < M; i++)
    {
        in >> A >> B >> W;
        money[A] -= W;
        money[B] += W;
    }

    for(int i = 0; i < N-1; i++)
    {
        if(money[i] == 0)
            continue;

        K++;

        if(money[i] < 0)
        {
            trans.push_back({{i+1, i}, -money[i]});
            money[i+1] += money[i];
        }
        else
        {
            trans.push_back({{i, i+1}, money[i]});
            money[i+1] += money[i];
        }
    }

    out << K << "\n";

    for(int i = 0; i < K; i++)
        out << trans[i].first.first << " " << trans[i].first.second << " " << trans[i].second << "\n";
    
    in.close();
    out.close();

    return 0;
}
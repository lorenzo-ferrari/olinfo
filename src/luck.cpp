#include <bits/stdc++.h>

#define MAXK 200
#define MAXC 10000

using namespace std;

int concatena[MAXK][MAXK];
pair<int, int> dp[MAXC+1][MAXK]; //[cifra][prev_lucky]
string lucky[MAXK];

int valuta(int i, int j)
{
    if(lucky[i][1] == lucky[j][0] && lucky[i][2] == lucky[j][1] && lucky[i][3] == lucky[j][2])
        return 1;
    if(lucky[i][2] == lucky[j][0] && lucky[i][3] == lucky[j][1])
        return 2;
    if(lucky[i][3] == lucky[j][0])
        return 3;
    return 4;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int K, C;
    
    in >> K >> C;

    //scanf("%d %d", &K, &C);

    for(int i = 0; i < K; i++)
        in >> lucky[i];
    
    for(int i = 0; i < K; i++)
        for(int j = 0; j < K; j++)
            concatena[i][j] = valuta(i, j); //come concateno J a I
        
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < K; j++)
            dp[i][j] = {0, -1};
    
    for(int i = 0; i < K; i++)
        dp[4][i] = {1, -1};
    
    for(int i = 5; i <= C; i++)
    {
        for(int j = 0; j < K; j++)
        {
            int index = -1;
            int best = 0;

            for(int _ = 0; _ < K; _++)
            {
                if(dp[i - concatena[_][j]][_].first + 1 > best)
                {
                    index = _;
                    best = dp[i - concatena[_][j]][_].first + 1;
                }
            }

            dp[i][j] = {best, index};
        }
    }

    /*for(int i = 0; i <= C; i++)
    {
        printf("%d: ", i);
        for(int j = 0; j < K; j++)
            printf("{%d, %d}  ", dp[i][j].first, dp[i][j].second);

        printf("\n");
    }*/

    stack <char> best_score;
    int maxx = 0, track = -1, prev = -1, pos = C-4;

    for(int i = 0; i < K; i++)
    {
        if(dp[C][i].first > maxx)
        {
            maxx = dp[C][i].first;
            track = dp[C][i].second;
            prev = i;
        }
    }

    //printf("%d", prev);

    best_score.push(lucky[prev][3]);
    best_score.push(lucky[prev][2]);
    best_score.push(lucky[prev][1]);
    best_score.push(lucky[prev][0]);

    //printf("\n%d\n", concatena[2][2]);

    //printf("%d ", track);

    while(pos > 0)
    {
        //cout << "#" << pos << "#";
        for(int i = concatena[track][prev]-1; i >= 0 && pos > 0; i--)
        {
            //cout << "Hello world!";
            pos--;
            best_score.push(lucky[track][i]);
        }

        prev = track;
        track = dp[pos+4][track].second;

        //printf("%d ", track);
    }

    while(!best_score.empty())
    {
        out << best_score.top();
        best_score.pop();
    }
}
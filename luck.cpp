#include <bits/stdc++.h>

#define MAXK 200
#define MAXC 10000

using namespace std;

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked(' ');
}

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
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int K = get_int();
    int C = get_int();

    for(int i = 0; i < K; i++) lucky[i] = getchar_unlocked();
    
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

    best_score.push(lucky[prev][3]);
    best_score.push(lucky[prev][2]);
    best_score.push(lucky[prev][1]);
    best_score.push(lucky[prev][0]);

    while(pos > 0)
    {
        for(int i = concatena[track][prev]-1; i >= 0 && pos > 0; i--)
        {
            pos--;
            best_score.push(lucky[track][i]);
        }

        prev = track;
        track = dp[pos+4][track].second;

    }

    while(!best_score.empty())
    {
        putchar_unlocked(best_score.top());
        best_score.pop();
    }
}
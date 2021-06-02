#include <bits/stdc++.h>

using namespace std;

int prefix, bestScore;
deque <pair<int, int>> Q;

int best_score(int N, int K, vector<int> &monete) {

    prefix = 0;

    Q.push_back({0, -1});

    for(int i = 0; i < N; i++) {
        prefix += monete[i];

        if(!Q.empty() && Q.front().second < i-K)
            Q.pop_front();

        bestScore = prefix - Q.front().first;

        while(!Q.empty() && Q.back().first > bestScore)
            Q.pop_back();

        Q.push_back({bestScore, i});
    }

    return bestScore;
}
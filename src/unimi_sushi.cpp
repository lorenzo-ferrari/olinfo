#include <bits/stdc++.h>
using namespace std;

inline int get_int(){
    int n = 0;
    char c = getchar_unlocked();
    while(c >= '0'){
        n = n*10+c-'0';
        c = getchar_unlocked();
    }
    return n;
}

vector <pair<int,int>> dp;

int b_search(int istante){
    int left = 0, right = dp.size()-1, middle; 

    if(dp[right].first >= istante) return right;

    while(left < right){
        middle = (right+left) >> 1;
        if(dp[middle].first >= istante && dp[middle+1].first < istante)
            return middle;
        if(dp[middle+1].first < istante)
            right = middle;
        else 
            left = middle;
    }
}

int main()
{
    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    
    int N, a, b, c;
    pair<pair<int,int>, int> piatti[100000];

    N = get_int();

    for(int i = 0; i < N; i++){
        a = get_int(); 
        b = get_int(); 
        c = get_int(); 
        
        piatti[i] = {{-a, c}, b};
    }

    sort(piatti, piatti+N);

    dp.push_back({0, 0});
    
    for(int i = 0; i < N; i++){
        int aa = -piatti[i].first.first;
        int cc = piatti[i].first.second;
        int bb = piatti[i].second;

        int now = b_search(aa);
        int index = b_search(aa+cc);

        if(dp[now].second < dp[index].second+bb)
            dp.push_back({aa, dp[index].second+bb});
    }

    printf("%d", dp.back().second);
}
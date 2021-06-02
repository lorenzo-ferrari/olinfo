#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;

const int MAXN = 1000000;
int parent[MAXN+1], _rank[MAXN+1];
int element;

int find_set(int v){
    if(parent[v] == v) return v;
    return parent[v] = find_set(parent[v]);
}

bool union_set(int a, int b){
    a = find_set(a);
    b = find_set(b);
    if(a != b){
        ++element;
        if(_rank[a] < _rank[b])
            swap(a, b);
        if(_rank[a] == _rank[b])
            ++_rank[a];
        parent[b] = a;

        return true;
    }
    return false;
}

int progetta(int N, int M, int K, vector<int> &A, vector<int> &B,vector<int> &W){
    int ans = 0;
    vector<int> bucket[1001];
    for(int i = 1; i <= N; i++) parent[i] = i;
    for(int i = 0; i < M; ++i)
        bucket[W[i]].push_back(i);
    for(int w = 1000; w >= 0 && element < N-K; --w){
        for(int i : bucket[w]){
            if(element >= N-K){
                break;
            }
            if(union_set(A[i], B[i])){
                ans += w;
            }
        }
    }

    return ans;
}
#include <bits/stdc++.h>
#define MAXN 100000
using namespace std;
typedef pair<int, int> pii;
pii v[MAXN];
int def[MAXN];

int main() {
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    v[0].first = 0;
    v[0].second = 0;
    int n; in >> n;
    char temp;
    for(int i = 1; i < n; i++) {
        in >> temp;
        if(temp == '<')
            v[i].first = v[i-1].first + 1;
        else
            v[i].first = v[i-1].first - 1;
        v[i].second = i;
    }
    sort(v, v+n);
    for(int i = 0; i < n; i++)
        def[v[i].second] = i+1;
    for(int i = 0; i < n; i++)
        out << def[i] << " ";

    in.close();
    out.close();
}

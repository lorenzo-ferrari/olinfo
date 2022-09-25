#include <bits/stdc++.h>

#define MAXN 100000
#define INF 1000000000

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

int N, P, tempH, counter;
int H[MAXN], sinistra[MAXN], destra[MAXN];

int main()
{
    in >> N >> P;
    in >> H[0];
    
    for(int i = 1; i < N; i++) {
        in >> tempH;
        H[i] = tempH;
        
        if(tempH < H[i-1])
            sinistra[i] = sinistra[i-1] + 1;
        else if(tempH == H[i-1])
            sinistra[i] = INF;
    }
    
    for(int i = N-2; i >= 0; i--) {
        if(H[i] < H[i+1])
            destra[i] = destra[i+1] + 1;
        else if(H[i] == H[i+1])
            destra[i] = INF;
            
        if(sinistra[i] < P && destra[i] < P)
            counter++;
    }
    
    if(sinistra[N-1] < P && destra[N-1] < P)
        counter++;
    out << counter;
}

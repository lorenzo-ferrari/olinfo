#include <bits/stdc++.h>

using namespace std;

ifstream in ("input.txt");
ofstream out ("output.txt");

unordered_map <int, int> M;

int H, tempH, N, massimo, piuFreq;

int main()
{
    in >> N;
    for(int i = 0; i < N; i++) 
    {
        in >> tempH;
        H += tempH;
        M[H]++;
        if(massimo < M[H]) {
            massimo = M[H];
            piuFreq = H;
        }
    }
    
    out << 5000+piuFreq;
}
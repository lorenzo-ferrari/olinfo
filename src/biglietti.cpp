#include <bits/stdc++.h>

using namespace std;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    
    int N, M, A, B;
    
    in >> N >> M >> A >> B;

    int t = (int)min((int)min(N/M*B + (N%M)*A, (int)(N/M + 1)*B), A*N);
    
    out << t;
}

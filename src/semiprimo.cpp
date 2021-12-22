#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000000;
int N;
bool prime(int n) {
    for(int i = 2; i <= sqrt(n); i++)
        if(n % i == 0)
            return 0;
    return 1;
}

int main() {
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    in >> N;
    for(int i = 2; i <= sqrt(N); i++) {
        if(N % i == 0) {
            if(prime(i) && prime(N/i)) {
                out << i << " " << N/i;
                return 0;
            }

        }
    }
    out << -1;
    in.close();
    out.close();
}

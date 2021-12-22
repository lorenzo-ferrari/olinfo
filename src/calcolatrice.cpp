#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;

long long trova(long long N)
{
    if(N % 10 == 0) return N;
    long long temp = N, rev = 0;
    while(temp != 0) {
        if(temp % 10 == 6) {
            rev = 10*rev + 9;
        }
        else if(temp % 10 == 9) {
            rev = 10*rev + 6;
        }
        else if (temp % 10 == 3 || temp % 10 == 4 || temp % 10 == 7)
            return N;
        else
            rev = 10*rev + temp % 10;
        
        temp /= 10;
    }
    if(rev < N)
        return rev;
    return N;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    long long N;
    in >> N;
    out << trova(N);

    return 0;
}

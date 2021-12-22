#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int f[30]{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040};
vector <char> code;
int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int N; in >> N;
    bool control = 0;
    for(int i = 29; i >= 0; i--) {
        if(N >= f[i]) control = 1;
        if(control && N >= f[i]) {
            code.push_back('1');
            N -= f[i];
        }
        else if(control && N < f[i])
            code.push_back('0');
    }
    for(int i = code.size()-1; i >= 0 ; i--) out << code[i];
}

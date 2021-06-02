#include <fstream>
using namespace std;
long n, r, c;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    
    in >> n >> r >> c;
    out << c*(r-c+1);
}

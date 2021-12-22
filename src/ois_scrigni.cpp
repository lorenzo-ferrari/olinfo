#include <fstream>
int main()
{
    long long n;
    std::ifstream in ("input.txt");
    std::ofstream out ("output.txt");
    in >> n;
    out<<((n*(n-1))/4.0);
}

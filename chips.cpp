#include <fstream>
#include <cmath>
using namespace std;

int bet(int A, int C, int r, int g, int b)
{
    int result;
    result = A * (r*r + g*g + b*b) + C * fmin(fmin(r, g), b);

    return result;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int T, A, C, r, g, b;
    in >> T;

    for(int i = 0; i < T; i++)
    {
        in >> A >> C >> r >> g >> b;

        if(bet(A, C, r + 1, g, b) >= bet(A, C, r, g + 1, b) && bet(A, C, r + 1, g, b) >= bet(A, C, r, g, b + 1))
            out << "RED" << "\n";
        else if(bet(A, C, r, g + 1, b) >= bet(A, C, r, g, b + 1))
            out << "GREEN" << "\n";
        else
            out << "BLUE" << "\n";
    }

    in.close();
    out.close();

    return 0;
}

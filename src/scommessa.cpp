#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");
    int n, control = 0, counter = 0;
    vector <int> v;

    in >> n;

    for(int i = 0; i < n; i++)
    {
        int temp;
        in >> temp;

        if(temp % 2 == 0)
            control++;
        else
            control--;

        if(control == 1 && temp % 2 == 0)
        {
            counter++;
            v.push_back(temp);
        }
    }

    out << counter << "\n";

    for(int i = 0; i < v.size(); i++)
        out << v[i] << " ";

    return 0;
}
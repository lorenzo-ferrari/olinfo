#include <fstream>
using namespace std;

int collatz(int n)
{
    int counter = 1;
    while(n > 1)
    {
        counter++;
        if(n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
    }

    return counter;
}

bool pollatz(int n)
{
    int counter = 1;
    int prova = collatz(n);
     while(n != 1 && counter < prova)
    {
        counter++;
        if(n % 2 == 0)
            n /= 2;
        else
            n = 5 * n + 1;
    }

    if(counter < prova) return true;

    return false;
}

int main()
{
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int a, b, counter = 0;

    in >> a >> b;

    for(int i = a; i <= b; i++)
    {
      counter += pollatz(i);
    }

    out << counter;

    in.close();
    out.close();

    return 0;
}

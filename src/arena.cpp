#include <fstream>
#include <algorithm>
#define MAX 100000

using namespace std;

 int n, e, l, p, q, explosions = 0, counter = 0;
 char temp;
 int v[MAX];

 int main()
 {
     ifstream in ("input.txt");
     ofstream out ("output.txt");

     in >> n >> e >> l;
     for(int i = 0; i < n; i++)
     {
        v[i] = l;
     }
     for(int i = 0; i < e; i++)
     {
        in >> p >> temp;
        if(temp == 'f')
        {
            in >> q;
            v[q]--;
        }
        else
        {
            v[p]++;
            explosions++;
        }
     }

     for(int i = 0; i < n; i++)
        if(v[i] > explosions)
            counter++;

     out << counter;

     in.close();
     out.close();
 }

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, counter;
ll budget;
int p[100000];
int c[100000];

int main()
{
   ifstream in ("input.txt");
   ofstream out ("output.txt");
   
   in >> n >> budget;
   
   for(int i = 0; i < n; i++)
        in >> p[i];
   for(int i = 0; i < n; i++)
        in >> c[i];
   
   for(int i = 0; i < n; i++) {
       if(p[i] <= budget) {
           counter++;
           budget -= p[i];
       }
       else
           budget += c[i];
   }
   
   cout << counter << " " << budget;
   
}

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    if(b == 0)
        return a;
    return gcd(b, a%b);
}

int n;
ll mcd = 0, temp;
vector <ll> divisori;


int main()
{
   ifstream in ("input.txt");
   ofstream out ("output.txt");
   
   in >> n;
   
   for(int i = 0; i < n; i++) {
       in >> temp;
       mcd = gcd(temp, mcd);
   }
   
   for(int i = 1; i <= sqrt(mcd); i++) {
       if(mcd % i == 0) {
           divisori.push_back(i);
           if(i != sqrt(mcd))
                divisori.push_back(mcd/i);
       }
   }
   
   sort(divisori.begin(), divisori.end());
   
   for(int i = 0; i < divisori.size(); i++)
        out << divisori[i] << " ";
    
}

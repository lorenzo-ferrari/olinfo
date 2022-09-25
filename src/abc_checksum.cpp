#include <bits/stdc++.h>

using namespace std;

unordered_map <int, int> check;

void inizializza(int P, int M)
{
    bool inutile = 1;
}

bool isPrime(int N)
{
    if(N == 1) return 0;
    if(N == 2) return 1;

    for(int i = 3; i <= sqrt(N); i+=2)
        if(N % i == 0)
            return 0;
    return 1;
}

int controlla(int C)
{
    int N = C;
    vector <int> div;
    
    if(C%2 == 0)
    {
      if(check[2] != 0) return check[2];

        div.push_back(2);

        while(N%2 == 0)
            N = N>>1;
            
        if(isPrime(N))
        {
            if(check[N] != 0) return check[N];

            div.push_back(N);
        }
    }
    
    for(int i = 1; i <= sqrt(N); i+=2)
    {
        if(C%i == 0)
        {
            if(isPrime(i))
            {
                if(check[i] != 0) return check[i];

                div.push_back(i);
    
                while(N%i == 0)
                    N /= i;
                    
                if(isPrime(N))
                {
                    if(check[N] != 0) return check[N];
    
                    div.push_back(N);
                }
            }
            else if(isPrime(N/i))
            {
                if(check[N/i] != 0) return check[N/i];

                div.push_back(N);
            }
        }
    }
    
    for(int i = 0; i < div.size(); i++)
        check[div[i]] = C;

    return 0;
}
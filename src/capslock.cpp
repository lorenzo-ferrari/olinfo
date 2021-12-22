#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N;
    
    scanf("%d", &N);
    
    char c = getchar_unlocked();
    
    for(int i = 0; i < N; i++)
    {
        c = getchar_unlocked();
        if(c >= 'a')
            printf("%c", char(c-32));
        else if(c >= 'A')
            printf("%c", char(c+32));
        else
            printf("%c", c);
    }
}

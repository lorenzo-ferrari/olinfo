#include <stdio.h> 
#include <stdlib.h> 

int n, counter_2, counter_5; 

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char c = getchar_unlocked();
    while(c > ' '){
        n = 10*n+c-'0';
        c = getchar_unlocked();

        if(c == 'x'){
            counter_2 += __builtin_ctz(n);

        if (n % 390625 == 0){
            n /= 390625;
            counter_5 += 8;
        }
        if (n % 625 == 0){
            n /= 625;
            counter_5 += 4;
        }
        if (n % 25 == 0){
            n /= 25;
            counter_5 += 2;
        }
        if (n % 5 == 0){
            n /= 5;
            counter_5++;
        }

            n = 0;
            c = getchar_unlocked();
        }
    }

    counter_2 += __builtin_ctz(n);

    if (n % 390625 == 0){
        n /= 390625;
        counter_5 += 8;
    }
    if (n % 625 == 0){
        n /= 625;
        counter_5 += 4;
    }
    if (n % 25 == 0){
        n /= 25;
        counter_5 += 2;
    }
    if (n % 5 == 0){
        n /= 5;
        counter_5++;
    }
    

    if(counter_2 < counter_5)
        printf("%d", counter_2);
    else
        printf("%d", counter_5);
}
    
        
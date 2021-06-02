int trova(int n) 
{
    if(n > 3) {
    int somma = 3;
    long long fact = 1;
    for(int i = 1; i < n; i++) {
        fact *= i;
        fact = fact % 1000000007;
        somma += fact;
        if(somma>1000000007) somma-=1000000007;
    }
    
    return somma;
    }
    if(n == 1) return 1;
    if(n == 2) return 2;
    if(n == 3) return 6;
}
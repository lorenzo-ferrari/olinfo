#include <fstream>
using namespace std;

int pow1(int base, int exp, int modulo ) {
    long y;
    if(base == 0) return 0;
    if (exp == 0) return 1;
    if (exp % 2 == 0)
    {
        y = pow1(base, exp/2, modulo);
        y = (y*y) % modulo;
    }
    else
    {
        y = (base % modulo);
        y = ( y * (pow1(base, exp-1, modulo) % modulo)) % modulo;
    }
    return (int)((y + modulo) % modulo);
}

int exponentMod(int A, int B, int C) 
{ 
    // Base cases 
    if (A == 0) 
        return 0; 
    if (B == 0) 
        return 1; 
  
    // If B is even 
    long y; 
    if (B % 2 == 0) { 
        y = exponentMod(A, B / 2, C); 
        y = (y * y) % C; 
    } 
  
    // If B is odd 
    else { 
        y = A % C; 
        y = (y * exponentMod(A, B - 1, C) % C) % C; 
    } 
  
    return (int)((y + C) % C); 
} 

void decifra(int N, int d, int L, int* messaggio, char* plaintext) {
    for(int i = 0; i < L; i++)
    {
        plaintext[i] = pow1(messaggio[i], d, N);
    }
    plaintext[L] = '\0';
}

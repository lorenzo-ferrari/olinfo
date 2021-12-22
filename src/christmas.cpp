#include <bitset>
#include <iostream>
#pragma GCC optimize ("O3")

inline int get_int() {
    int n = 0;
    char c = getchar_unlocked();
    while (c >= '0') {
        n = (n << 3) + (n << 1) + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

inline void print(int n) {
    int i = 0;
    char S[20];
    if (n == 0) {
        putchar_unlocked('0');
        putchar_unlocked(' ');
        return;
    }
    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked(' ');
}

int main(){
    int N = get_int();
    int B = get_int();
    int bb = B;
    std::bitset <10001> p;
    p[0] = true;
    while (N--) p |= (p << get_int());
    while (B < 10001 && !p[B]) B++;
    if (B == 10001) {while (!p[bb]) bb--; print(bb); return 0;}
    print(B);
}
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;

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

int main() {
    int n = get_int(), ans = 0;
    bool bold = false, italic = false;
    char c;
    while (n--) {
        c = getchar_unlocked();
        ans += ((c == 'I' || c == 'N') != bold);
        ans += ((c == 'i' || c == 'I') != italic);
        bold = (c == 'I' || c == 'N');
        italic = (c == 'I' || c == 'i');        
        c = getchar_unlocked();
    }
    print((ans + bold + italic) >> 1);
}
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

    while (n) {
        S[i++] = n % 10 + '0';
        n /= 10;
    }
    while (--i >= 0)
        putchar_unlocked(S[i]);
    putchar_unlocked('\n');
}

int main() {
	int t = get_int(), n, a;
	while (t--) {
		n = get_int();
		a = (1 << (32 - __builtin_clz(n))) - 1;

		if ((n&3) == 0) print(a + (n^a));
		else if ((n&3) == 1) print(a + (1^a));
		else if ((n&3) == 2) print(a + ((n+1)^a));
		else if ((n&3) == 3) print(a << 1);
	}
}

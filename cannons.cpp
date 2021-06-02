#include <queue>
#include <vector>
#include <iostream>
#pragma GCC optimize ("O3")
using namespace std;
#define F first
#define S second

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

const int INF = 1e9;
const int MAXN = 1e6;

int main() {
	int n = get_int();
	int t[MAXN];
	for (int i = 0; i < n; i++)
		t[i] = get_int();

	int d[MAXN];
	fill(d, d + n, INF);
	priority_queue <pair<int, int>> Q;
	d[0] = 0;
	Q.push({0, 0});
	while (!Q.empty()) {
		int v = Q.top().S;
		Q.pop();
		if (d[t[v]] > d[v]) {
			d[t[v]] = d[v];
			Q.push({-d[t[v]], t[v]});
		}
		if (v != 0 && d[v - 1] > d[v] + 1) {
			d[v - 1] = d[v] + 1;
			Q.push({-d[v - 1], v - 1});
		}
		if (v != n - 1 && d[v + 1] > d[v] + 1) {
			d[v + 1] = d[v] + 1;
			Q.push({-d[v + 1], v + 1});
		}
	}

	print(d[n - 1]);
}

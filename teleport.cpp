#include <iostream>
#include <queue>
#include <assert.h>
#pragma GCC optimize ("O3")
using namespace std;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MAXN 1000
#define INF 214748347

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


int n, m, cx, cy, mx, my;
char c;
bool p[MAXN][MAXN]{}, t[MAXN][MAXN];
int distc[MAXN][MAXN], distm[MAXN][MAXN];

int main() {
    n = get_int();
    m = get_int();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            distc[i][j] = INF;
            distm[i][j] = INF;
            c = getchar_unlocked();
            if (c == 'C') {cx = i; cy = j;}
            else if (c == 'M') {mx = i; my = j;}
            else if (c == '@') {t[i][j] = 1;}
            if (c != '#') {p[i][j] = 1;}
        }
        c = getchar_unlocked();
    }

    int ctx = -1, cty = -1, mtx = -1, mty = -1;
    queue <pair<int, int>> Q;
    Q.push({cx, cy});
    distc[cx][cy] = 0;
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        if (ctx == -1 && t[x][y]) {ctx = x; cty = y;}
        if (x > 0 && p[x - 1][y]) {
            if (distc[x - 1][y] > distc[x][y] + 1) {
                distc[x - 1][y] = distc[x][y] + 1;
                Q.push({x - 1, y});
            }
        }
        if (y > 0 && p[x][y - 1]) {
            if (distc[x][y - 1] > distc[x][y] + 1) {
                distc[x][y - 1] = distc[x][y] + 1;
                Q.push({x, y - 1});
            }
        }
        if (x < n - 1 && p[x + 1][y]) {
            if (distc[x + 1][y] > distc[x][y] + 1) {
                distc[x + 1][y] = distc[x][y] + 1;
                Q.push({x + 1, y});
            }
        }
        if (y < m - 1 && p[x][y + 1]) {
            if (distc[x][y + 1] > distc[x][y] + 1) {
                distc[x][y + 1] = distc[x][y] + 1;
                Q.push({x, y + 1});
            }
        }
    }

    Q.push({mx, my});
    distm[mx][my] = 0;
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        if (mtx == -1 && t[x][y]) {mtx = x; mty = y;}
        if (x > 0 && p[x - 1][y]) {
            if (distm[x - 1][y] > distm[x][y] + 1) {
                distm[x - 1][y] = distm[x][y] + 1;
                Q.push({x - 1, y});
            }
        }
        if (y > 0 && p[x][y - 1]) {
            if (distm[x][y - 1] > distm[x][y] + 1) {
                distm[x][y - 1] = distm[x][y] + 1;
                Q.push({x, y - 1});
            }
        }
        if (x < n - 1 && p[x + 1][y]) {
            if (distm[x + 1][y] > distm[x][y] + 1) {
                distm[x + 1][y] = distm[x][y] + 1;
                Q.push({x + 1, y});
            }
        }
        if (y < m - 1 && p[x][y + 1]) {
            if (distm[x][y + 1] > distm[x][y] + 1) {
                distm[x][y + 1] = distm[x][y] + 1;
                Q.push({x, y + 1});
            }
        }
    }

    assert(distc[mx][my] == distm[cx][cy]);
    
    int ans = distc[mx][my];
    if (ctx != -1 && mtx != -1) ans = min(ans, distc[ctx][cty] + distm[mtx][mty] + 1);

    print(ans);
}
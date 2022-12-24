#include <bits/stdc++.h>
using namespace std;

static constexpr int N = 1 << 20;

int n;
int t[2 * N];

int find_first(int l, int r, int x, bool what, int i = 1, int a = 0, int b = N) {
    if (r <= a || b <= l || t[i] <= x) return -1;
    if (b - a == 1) return a;
    if (what) {
        int o = find_first(l, r, x, what, 2*i, a, (a+b)/2);
        return o != -1 ? o : find_first(l, r, x, what, 2*i+1, (a+b)/2, b);
    } else {
        int o = find_first(l, r, x, what, 2*i+1, (a+b)/2, b);
        return o != -1 ? o : find_first(l, r, x, what, 2*i, a, (a+b)/2);
    }
}

pair<int, int> chiedi(int x) {
    int l = find_first(0, x+1, t[x + N], false);
    int r = find_first(x+1, n, t[x + N], true);
    if (l == -1) l = 0;
    if (r == -1) r = n-1;
    return {l, r};
}

void cambia(int x, int h) {
    for (t[x += N] = h; x > 1; x >>= 1) {
        t[x >> 1] = max(t[x], t[x^1]);
    }
}

void inizializza(int n, vector<int> h) {
    ::n = n;
    for (int i = 0; i < n; ++i) {
        t[i + N] = h[i];
    }
    for (int i = N-1; i > 0; --i) {
        t[i] = max(t[2*i], t[2*i+1]);
    }
}

#include <iostream>
#include <bitset>
using namespace std;

static constexpr int SIDE = 17000;
static bitset<SIDE> ans[SIDE];

int n, k, p[16];
bool g[10][10];

void solve(int x0, int y0, int deg) {
    if (deg == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                ans[x0 + i][y0 + j] = g[i][j];
            }
        }
        return;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j]) {
                solve(x0 + i*p[deg], y0 + j*p[deg], deg - 1);
            }
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c;
            g[i][j] = (c == '.');
        }
        getchar_unlocked();
    }

    int nn=1;
    for (int c = 0; c < k; ++c, nn *= n) {
        p[c] = nn;
    }

    solve(0, 0, k - 1);

    for (int i = 0; i < nn; ++i) {
        for (int j = 0; j < nn; ++j) {
            putchar_unlocked(ans[i][j] ? '.' : '*');
        }
        putchar_unlocked('\n');
    }
}

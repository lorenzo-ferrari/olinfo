#include <bits/stdc++.h>
#pragma GCC optimize("O3")
using namespace std;
using LL = long long;

static bool good[26][26][26];
static LL dp[26][26][10001];
static bool vis[26][26][10001];

LL solve(LL n, int l, int a, int b) {
    if (vis[a][b][l] || l <= 3) {
        return dp[a][b][l];
    }
    vis[a][b][l] = true;
    for (int c = 0; n > 0 && c < 26; ++c) {
        if (!good[a][b][c]) continue;
        dp[a][b][l] += solve(n, l-1, b, c);
        n -= solve(n, l-1, b, c);
    }
    return dp[a][b][l];
}

void build(LL& n, int l, int a, int b) {
    if (l == 3) {
        for (int c = 0; c < 26; ++c) {
            n -= good[a][b][c];
            if (!n) {
                cout << char(a + 'a');
                cout << char(b + 'a');
                cout << char(c + 'a');
                return;
            }
        }
    } else if (n <= solve(n, l, a, b)) {
        for (int c = 0; c < 26; ++c) {
            if (!good[a][b][c]) continue;
            if (n <= solve(n, l-1, b, c)) {
                cout << char(a + 'a');
                build(n, l-1, b, c);
                return;
            } else {
                n -= solve(n, l-1, b, c);
            }
        }
    } else {
        n -= solve(n, l, a, b);
    }
}

int main() {
    LL n; cin >> n;
    int l; cin >> l;
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        char a; cin >> a;
        char b; cin >> b;
        char c; cin >> c;
        good[a-'a'][b-'a'][c-'a'] = true;
        ++dp[a-'a'][b-'a'][3];
    }
    for (int a = 0; n && a < 26; ++a) for (int b = 0; n && b < 26; ++b) {
        build(n, l, a, b);
    }
    cout << "\n";
}

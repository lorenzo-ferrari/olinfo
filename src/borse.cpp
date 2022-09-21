#include <bits/stdc++.h>
using namespace std;

void solve(int n, int p, string s) {
    if (!n) {
        puts(s.c_str());
        return;
    }
    for (int i = 1; i <= p && i <= n; ++i) {
        solve(n - i, i, s + to_string(i) + " ");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n; cin >> n;
    solve(n, n, "");
}

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void radix_sort(vector<array<int, 3>>& a) {
    int n = a.size();
    {
        vector<int> cnt(n);
        for (auto& x : a) {
            ++cnt[x[1]];
        }
        vector<array<int, 3>> new_a(n);
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (auto& x : a) {
            int i = x[1];
            new_a[pos[i]] = x;
            ++pos[i];
        }
        a = new_a;
    }
    {
        vector<int> cnt(n);
        for (auto& x : a) {
            ++cnt[x[0]];
        }
        vector<array<int, 3>> new_a(n);
        vector<int> pos(n);
        for (int i = 1; i < n; ++i) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for (auto& x : a) {
            int i = x[0];
            new_a[pos[i]] = x;
            ++pos[i];
        }
        a = new_a;
    }
}

int main() {
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    vector<int> p(n), c(n);
    {
        // k = 0
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = {s[i], i};
        }
        sort(begin(a), end(a));

        for (int i = 0; i < n; ++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i].first == a[i-1].first) {
                c[p[i]] = c[p[i-1]];
            } else {
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
    }

    int k = 0;
    while ((1 << k) < n) {
        // k -> k+1;
        vector<array<int, 3>> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = {c[i], c[(i + (1 << k)) % n], i};
        }
        radix_sort(a);

        for (int i = 0; i < n; ++i) p[i] = a[i][2];
        c[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            if (a[i][0] == a[i-1][0] && a[i][1] == a[i-1][1]) {
                c[p[i]] = c[p[i-1]];
            } else {
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
        ++k;
    }
    vector<int> ans(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        ans[c[i] - 1] = i;
    }
    for (int i : ans) {
        cout << i << " ";
    }
}

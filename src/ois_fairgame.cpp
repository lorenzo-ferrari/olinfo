#include <deque>
#include <iostream>
#pragma GCC optimzie ("O3")
using namespace std;
#define F first
#define S second

const int INF = 2e9;
int n, k, m, p, q;

int main() {
	cin >> n >> k >> m >> p >> q;

    deque <pair<int, int>> Q[2]; //Q0 -> pari, Q1 -> dispari

    Q[0].push_back({q - p, 0});
    int mn = p - q;
    for (int i = 1; i <= n; i++) {
        mn = INF;

        if (!Q[0].empty() && Q[0].front().S < i - k) Q[0].pop_front();
        if (!Q[1].empty() && Q[1].front().S < i - k) Q[1].pop_front();

        if (!Q[0].empty()) mn = min(mn, Q[0].front().F + m * (i & 1));
        if (!Q[1].empty()) mn = min(mn, Q[1].front().F + m * ((i+1) & 1));

        while (!Q[i & 1].empty() && Q[i & 1].back().F >= -mn)
            Q[i & 1].pop_back();
        Q[i & 1].push_back({-mn, i});
    }

    cout << -mn << "\n";
}

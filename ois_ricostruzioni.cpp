#include <deque>
#include <iostream>
using namespace std;
#define F first
#define S second

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);

    int ans = 1e9;
    deque <pair<int, int>> mn, mx;
    
    for (int i = 0, h; i < n; i++) {
        cin >> h;
        
        while (!mn.empty() && mn.front().F > h)
            mn.pop_front();
        if (!mn.empty() && mn.back().S <= i - k)
            mn.pop_back();
        mn.push_front({h, i});

        while (!mx.empty() && mx.front().F < h)
            mx.pop_front();
        if (!mx.empty() && mx.back().S <= i - k)
            mx.pop_back();
        mx.push_front({h, i});

        if (i >= k - 1)
            ans = min(ans, mx.back().F - mn.back().F);
    }

    printf("%d\n", ans);

}
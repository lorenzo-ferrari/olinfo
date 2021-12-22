#include <cmath>
#include <iostream>
using namespace std;

int mx(int n, int p) {
    int ans = 1;
    while (ans * p <= n)
        ans *= p;
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    int ans = 1;
    for (int i = 2; i*i <= n; i++)
        ans = max(ans, mx(n, i));

    printf("%d\n", ans);
}
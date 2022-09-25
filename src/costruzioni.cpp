#include <bits/stdc++.h>
using namespace std;

int demolisci(int n, int k, int v[]) {
    int sum = 0;
    for (int i = 0; i < k; ++i)
        sum += v[i];
    int ans = sum;
    for (int i = k; i < n; ++i) {
        sum += v[i] - v[i - k];
        ans = min(ans, sum);
    }
    return ans;
}

int main() {
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    int n, k, v[100000];
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> v[i];
    cout << demolisci(n, k, v) << "\n";
}

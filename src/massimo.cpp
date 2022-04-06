#include <vector>
#include <algorithm>
#pragma GCC optimize ("O3")

int trova_massimo(int n, std::vector<int> v) {
    int mx = -1024;
    while (n--) if (mx < v[n]) mx = v[n];
    return mx;
}

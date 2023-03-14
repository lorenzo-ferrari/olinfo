#include <bits/stdc++.h>
using namespace std;

vector<int> phi, d, primes;

void sieve(int n = 4e6+42) {
    phi.resize(n);
    d.resize(n, 1);
    for (int i = 2; i < n; ++i) {
        if (d[i] == 1) {
            d[i] = i;
            phi[i] = i-1;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= d[i] && i*primes[j] < n; ++j) {
            d[i*primes[j]] = primes[j];
            if (d[i] == primes[j]) {
                phi[i*primes[j]] = phi[i] * primes[j];
            } else {
                phi[i*primes[j]] = phi[i] * (primes[j] - 1);
            }
        }
    }
}

void evadi(int q, vector<int>& ns) {
    sieve();
    for (int& n : ns) {
        int ans = 0;
        for (int i = 1; i*i <= n; ++i) {
            if (n % i) continue;
            ans += phi[n/i-1];
            if (i*i != n) {
                ans += phi[i-1];
            }
        }
        n = ans;
    }
}

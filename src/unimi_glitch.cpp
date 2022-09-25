#include <iostream>
#include <unordered_map>
#pragma GCC optimize("O3")
using namespace std;
#define MAXN 50005

const uint64_t m = 4000000007;
const uint64_t p1 = 31;
const uint64_t p2 = 137;
const uint64_t p3 = 53;

uint64_t pw1[MAXN];
uint64_t pw2[MAXN];
uint64_t pw3[MAXN];
uint64_t inv1;
uint64_t inv2;
uint64_t inv3;


uint64_t n;
uint64_t s[MAXN];

inline bool cond1(uint64_t l) {
    if (l == 0) return true;

    uint64_t hash_value = 0;
    for (int i = 0; i < l; i++) {
        hash_value = (hash_value + s[i] * pw1[i]) % m;
    }

    unordered_map <uint64_t, bool> mp;
    for (uint64_t i = 0; i < n - l; i++) {
        
        mp[hash_value] = true;
        hash_value = (hash_value + m - s[i]) % m;
        hash_value = (hash_value * inv1) % m;
        hash_value = (hash_value + s[i + l] * pw1[l - 1]) % m;

        if (mp[hash_value])
            return true;
    }

    return false;
}

inline bool cond2(uint64_t l) {
    if (l == 0) return true;

    uint64_t hash_value = 0;
    for (int i = 0; i < l; i++) {
        hash_value = (hash_value + s[i] * pw2[i]) % m;
    }

    unordered_map <uint64_t, bool> mp;
    for (uint64_t i = 0; i < n - l; i++) {
        
        mp[hash_value] = true;
        hash_value = (hash_value - s[i] + m) % m;
        hash_value = (hash_value * inv2) % m;
        hash_value = (hash_value + s[i + l] * pw2[l - 1]) % m;

        if (mp[hash_value])
            return true;
    }

    return false;    
}

inline bool cond3(uint64_t l) {
    if (l == 0) return true;

    uint64_t hash_value = 0;
    for (int i = 0; i < l; i++) {
        hash_value = (hash_value + s[i] * pw3[i]) % m;
    }

    unordered_map <uint64_t, bool> mp;
    for (uint64_t i = 0; i < n - l; i++) {
        
        mp[hash_value] = true;
        hash_value = (hash_value - s[i] + m) % m;
        hash_value = (hash_value * inv3) % m;
        hash_value = (hash_value + s[i + l] * pw3[l - 1]) % m;

        if (mp[hash_value])
            return true;
    }

    return false;    
}

inline uint64_t bs () {
    uint64_t l = 0, r = n, mid;
    while (l < r - 1) {
        mid = l + (r - l) / 2;
        if (cond1(mid) && cond2(mid) && cond3(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return ((cond1(r-1) && cond2(r-1) && cond3(r-1)) ? r-1 : l);
}

uint64_t fastexp(uint64_t x, uint64_t y) {
    uint64_t ans = 1;
    
    while (y) {
        if (y & 1)
            ans = (ans * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }

    return ans;
}

int main() {
    scanf("%lu", &n);

    char c;
    scanf("%c", &c);
    for (uint64_t i = 0; i < n; i++) {
        scanf("%c", &c);
        s[i] = c - 'a' + 1;
    }

    pw1[0] = 1;
    pw2[0] = 1;
    pw3[0] = 1;

    for (uint64_t i = 1; i <= n; i++) {
        pw1[i] = (pw1[i - 1] * p1) % m;
        pw2[i] = (pw2[i - 1] * p2) % m;
        pw3[i] = (pw3[i - 1] * p3) % m;
    }

    inv1 = fastexp(p1, m - 2);
    inv2 = fastexp(p2, m - 2);
    inv3 = fastexp(p3, m - 2);

    // for (int i = 1; i <= n; i++) cout << cond1(i) << cond2(i) << "\n";

    printf("%lu\n", bs());
}
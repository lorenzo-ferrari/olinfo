#include <bits/stdc++.h>
using namespace std;

#define int __int128_t
#define abs(x) (((x) < 0) ? -(x) : (x))

int GCD;
int t, c1, c2;

int justGCD(int a, int b) {
    if (b > a) return justGCD(b, a);
    if (b == 0) return a;
    return justGCD(b, a % b);
    
}

int gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    
    //cout << (int64_t)x1 << " " << (int64_t)b << " " << (int64_t)y1 << " " << (int64_t)(a % b) << " " << (int64_t)d << "\n";
    int ta = b;
    int tb = a % b;
    int diff = abs(x1 - y1);
    if (x1 < y1) {
        x1 += ((diff + tb) / 2 / tb) * tb;
        y1 = (d - x1 * ta) / tb;
    } else if (y1 > x1) {
        y1 += ((diff + ta) / 2 / ta) * ta;
        x1 = (d - y1 * tb) / ta;
    }
    
    if (x1 * ta + y1 * tb != d)
        cout << (int64_t)x1 << " " << (int64_t)ta << " " << (int64_t)y1 << " " << (int64_t)tb << " " << (int64_t)d << "\n";

    assert (x1 * ta + y1 * tb == d);
    
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int32_t main() {
    uint64_t tt, cc1, cc2;
    cin >> tt >> cc1 >> cc2;
    int t = tt, c1 = cc1, c2 = cc2;
    int x, y;
    //cin >> t >> c1 >> c2;
    t = t - c1 - c2;
    GCD = justGCD(c1, c2);
    c1 /= GCD;
    c2 /= GCD;
    t /= GCD;
    bool swapped = 0;
    if (c1 < c2) {
        swap(c1, c2);
        swapped = 1;
    }
    //c1 >= c2

    int g = gcd(c1, c2, x, y);

    if (t % g) {
        cout << "NO SOLUTION" << "\n";
        return 0;
    } else {
        x = t / g * x;
        y = t / g * y;

        if (x < 0) {
            int k = ((abs(x) + c2 / g - 1) / (c2 / g)) * (c2 / g) * c1;
            x += k / c1;
            y -= k / c2;
        }
        if (y < 0) {
            int k = ((abs(y) + c1 / g - 1) / (c1 / g)) * (c1 / g) * c2;
            x -= k / c1;
            y += k / c2;
        }

        {
            int k = (y / (c1 / g)) * (c1 / g) * c2;
            y -= k / c2;
            x += k / c1;
        }       

        if (swapped) {
            swap(x, y);
        }
        cout << (uint64_t)(x + 1) << " " << (uint64_t)(y + 1) << "\n";
    }
}
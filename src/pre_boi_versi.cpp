/*
 * max A a dx
 * min B a dx
 * -> posso fare qualunque valore in [B,A] ?
 */

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int direziona(int n, vector<int> a, vector<int> b) {
    int A = 0;
    for (int i = 0, j = 0; i < n; ++i) {
        while (j != n && b[j] < a[i]) ++j;
        if (j != n) {
            ++A;
            ++j;
        }
    }
    int B = 0;
    for (int i = 0, l = 0; i < n; ++i) {
        if (b[l] < a[i]) {
            ++l;
        } else {
            ++B;
        }
    }
    return A - B + 1;
}

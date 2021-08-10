#include <bits/stdc++.h>
using namespace std;

void Bake(int);

int o;
int I[8];
deque<int> ord[1 << 8];

void Init() {}

bool psb(int mask) {
    for (int i = 0; i < 8; ++i)
        if ((mask & (1 << i)) && !I[i])
            return false;
    return true;
}

void decrease(int mask) {
    for (int j = 0; j < 8; ++j)
        if (mask & (1 << j))
            --I[j];
}

void check() {
    int x = 1e9;
    int mask = 0;
    for (int i = 0; i < (1 << 8); ++i) {
        if (!ord[i].empty() && ord[i].front() < x && psb(i)) {
            x = ord[i].front();
            mask = i;
        }
    }
    if (x != 1e9) {
        Bake(x);
        decrease(mask);
        ord[mask].pop_front();
    }
}

void Order(int N, int *A) {
    int mask = 0;
    for (int i = 0; i < N; ++i)
        mask |= 1 << A[i];
    ord[mask].push_back(o++);
    check();
}

void Delivery(int i) {
    I[i]++;
    check();
}

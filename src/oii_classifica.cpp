#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int n;
    vector<int> t;
    Segment(int _n) {
        for (n = 1; n < _n; n <<= 1);
        t.assign(2 * n, 0);
        for (int i = 0; i < n; ++i) t[i + n] = 1;
        for (int i = n-1; i > 0; --i) t[i] = t[2*i] + t[2*i+1];
    }
    int at(int p) {
        int i = 1;
        while (i < n) {
            i *= 2;
            if (t[i] < p) {
                p -= t[i];
                ++i;
            }
        }
        return i - n;
    }
    int sum(int l, int r) {
        int ans = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += t[l++];
            if (r & 1) ans += t[--r];
        }
        return ans;
    }
    int prev(int p) {
        assert(t[p + n]);
        return at(sum(0, p));
    }
    void set(int p, int v) {
        for (t[p += n] = v; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p^1];
        }
    }
};

vector<int> itp;
vector<int> pti;
Segment* st;

void inizia(int n, int ids[]) {
    itp.resize(n);
    pti.resize(n);
    for (int i = 0; i < n; ++i) {
        itp[ids[i]] = i;
        pti[i] = ids[i];
    }
    st = new Segment(n);
}

void supera(int i) {
    int pi = itp[i];
    int pj = st->prev(pi);
    int j = pti[pj];
    swap(itp[i], itp[j]);
    swap(pti[pi], pti[pj]);
}

void squalifica(int i) {
    st->set(itp[i], 0);
}

int partecipante(int pos) {
    return pti[st->at(pos)];
}

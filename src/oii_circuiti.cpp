#include "bits/stdc++.h"
using namespace std;

struct reg {
    int i = 0;
    string name, op;
    reg(string n, string o)
        : name(n), op(o) {}
    string get() {
        return name + "[" + to_string(i++) + "]";
    }
    string get(string a, string b, string r = "-") {
        if (a == "-") return b;
        if (b == "-") return a;
        string ans = (r != "-" ? r : get());
        cout << ans << " = " << a << " " << op << " " << b << "\n";
        return ans;
    }
};

reg rsum("somma", "+");
reg rmax("mx", "max");

void solve_sum(int n) {
    auto reg = [&](int i) -> string {
        if (i == 1) return "out[0]";
        if (i >= n) return "in[" + to_string(i - n) + "]";
        return "somma[" + to_string(i) + "]";
    };
    for (int i = n-1; i > 0; --i) {
        cout << reg(i) << " = " << reg(2*i) << " + " << reg(2*i+1) << "\n";
    }
}

void solve_pref(int _n) {
    int n = 1;
    while (n < _n) {
        n <<= 1;
    }

    vector<vector<string>> s(n, vector<string>(n, "0"));
    s[0][0] = rsum.get("in[0]", "0", "out[0]");
    for (int i = 1; i < _n; ++i) {
        s[i][i] = "in[" + to_string(i) + "]";
    }
    for (int i = _n; i < n; ++i) s[i][i] = "-";
    function<string(int,int)> calc = [&](int l, int r) -> string {
        if (l >= _n) return "-";
        if (r >= _n) return calc(l, _n-1);
        if (s[l][r] != "0") return s[l][r];
        int sz = r - l + 1;
        int pw = 1 << (31 - __builtin_clz(sz));
        string name = (l ? "-" : "out["+to_string(r)+"]");
        assert(l % pw == 0 && "error, [l,r] disaligned");
        if (pw == sz) {
            int m = l + sz / 2;
            s[l][r] = rsum.get(calc(l, m - 1), calc(m, r), name);
        } else {
            // minimal number of registers: m = r - (sz & -sz) + 1
            // minimal number of cycles: m = l + pw - 1
            int m = r - (sz & -sz) + 1;
            s[l][r] = rsum.get(calc(l, m - 1), calc(m, r), name);
        }
        return s[l][r];
    };
    string all = calc(0, n-1);
    for (int i = 0; i < _n; ++i) {
        calc(0, i);
    }
}

void solve_subarr(int _n) {
    struct nd {
        string ans{"-"};
        string sum{"-"};
        string prf{"-"};
        string sff{"-"};
        nd() {}
    };
    auto join = [&](nd a, nd b, bool last, bool first_layer) -> nd {
        if (a.ans == "-" || b.ans == "-") {
            return a.ans == "-" ? b : a;
        }
        if (last) {
            auto tmp = rmax.get(a.ans, b.ans);
            auto sum = rsum.get(a.sff, b.prf);
            cout << "out[0] = " << tmp << " max " << sum << "\n";
            return nd();
        }
        nd ans;
        ans.sum = rsum.get(a.sum, b.sum);
        auto tmp = rmax.get(a.ans, b.ans);
        auto sum = (first_layer ? ans.sum : rsum.get(a.sff, b.prf));
        ans.ans = rmax.get(tmp, sum);
        auto prf = rsum.get(a.sum, b.prf);
        ans.prf = rmax.get(a.prf, prf);
        auto sff = rsum.get(a.sff, b.sum);
        ans.sff = rmax.get(b.sff, sff);
        return ans;
    };

    int n;
    for (n = 1; n < _n; n <<= 1);
    vector<nd> st(2 * n);
    for (int i = 0; i < _n; ++i) {
        st[i + n].ans = rmax.get("in[" + to_string(i) + "]", "0");
        st[i + n].prf = st[i + n].ans;
        st[i + n].sff = st[i + n].ans;
        st[i + n].sum = "in[" + to_string(i) + "]";
    }
    for (int i = n-1; i > 0; --i) {
        st[i] = join(st[2*i], st[2*i+1], i == 1, 2*i >= n);
    }
}

int main() {
    int t; cin >> t;
    int n; cin >> n;
    int c; cin >> c;
    switch (t) {
        case 1: solve_sum(n); break;
        case 2: solve_pref(n); break;
        case 3: solve_subarr(n); break;
        default: assert(0 && "errore, t non in {1,2,3}");
    }
}

/*
run.sh:

#!/bin/bash

for i in $(seq 0 9)
do
    echo "running on input_00$i"
    ./x < input/input_00$i.txt > output/output_00$i.txt
done
zip output.zip output/*
*/

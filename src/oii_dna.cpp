#include <bits/stdc++.h>
using namespace std;

bool test(string s);

unordered_map<string, bool> memo;

bool ask(const string& s) {
    if (memo.find(s) != memo.end()) {
        return memo[s];
    } else {
        return memo[s] = test(s);
    }
}

string nsqrtn(int n, string cur) {
    string prv = cur;
    while (cur.size() != n) {
        if (ask(cur + "1")) {
            cur = prv = cur + "1";
        } else {
            cur += "0";
        }
        if (int(cur.size() - prv.size()) > 100) {
            if (ask(cur)) {
                prv = cur;
            } else {
                break;
            }
        }
    }
    while ((int)prv.size() != n && (ask(prv + "0") || ask(prv + "1"))) {
        if (ask(prv + "0")) {
            prv += "0";
        } else {
            prv += "1";
        }
    }
    while ((int)prv.size() != n) {
        if (ask("0" + prv)) {
            prv = "0" + prv;
        } else {
            prv = "1" + prv;
        }
    }
    return prv;
}

string analizza(int n) {
if (ask(string(200, '0'))) {
        return nsqrtn(n, string(200, '0'));
    }
    int l = 0, r = 200;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (ask(string(m, '0'))) {
            l = m;
        } else {
            r = m;
        }
    }
    string cur = string(l, '0');
    string prv = cur;
    while ((int)cur.size() != n && (int)(cur.size() - prv.size()) <= l) {
        if (ask(cur + "1")) {
            cur = prv = cur + "1";
        } else {
            cur += "0";
        }
    }
    while (ask(prv + "0")) {
        prv += "0";
    }
    while ((int)prv.size() != n) {
        if (ask("0" + prv)) {
            prv = "0" + prv;
        } else {
            prv = "1" + prv;
        }
    }
    return prv;
}

#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#define TL 5
using namespace std;

bool test(string);

clock_t tbegin;
vector<string> nopes;
unordered_map<string, bool> memo;

bool ask(string s) {
  if (memo.find(s) != memo.end()) {
    return memo[s];
  }
  for (const string& x : nopes) {
    if (s.find(x) != string::npos) {
      return memo[s] = false;
    }
    if (clock() - tbegin > TL * CLOCKS_PER_SEC) {
      break;
    }
  }
  memo[s] = test(s);
  if (!memo[s]) {
    nopes.push_back(s);
  }
  return memo[s];
}

string find_suff(int n, string cur) {
  while ((int)cur.size() != n && (ask(cur + "0") || ask(cur + "1"))) {
    if (ask(cur + "0"))
      cur += "0";
    else
      cur += "1";
  }
  return cur;
}

string analizza(int n) {
  tbegin = clock();
  // trova un suffisso, aka both cur+0 and cur+1 false
  // -> trovato il suffisso, kinda ez
  string cur = "";
  int l = 0, r = n + 1;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (ask(string(m, '0')))
      l = m;
    else
      r = m;
  }
  if (l == 0) return string(n, '1');
  cur = string(l, '0');
  string prv = cur;
  int K = 100;
  while ((int)cur.size() != n) {
    // prv was true for sure
    if (int(cur.size() - prv.size()) > l) break;
    if (int(cur.size() - prv.size()) > K) {
      if (ask(cur + "0"))
        prv = (cur += "0");
      else if (ask(cur + "1"))
        prv = (cur += "1");
      else
        break;
    }
    cur += "1";
    if (ask(cur)) {
      prv = cur;
    } else {
      cur.back() ^= 1;
    }
  }
  cur = find_suff(n, prv);
  while ((int)cur.size() != n) {
    if (ask("0" + cur))
      cur = "0" + cur;
    else
      cur = "1" + cur;
  }
  return cur;
}

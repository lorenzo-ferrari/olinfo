/*
Findinf Bridges Online
https://cp-algorithms.com/graph/bridge-searching-online.html

* keep one Dsu for 2-connected components and one for 1-connected components
* for 2-connected components, normal Dsu
* for 1-connected components
  - compress each 2-connected component in its representative node
  - who is the parent of the compressed component?
*/

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define watch(x) cerr << (#x) << " is " << x << "\n"
#ifndef LORENZO
#define cerr if(0) cerr
#endif

struct Dsu {
  vector<int> cc;
  vector<int> sz;
  explicit Dsu(int n) {
    sz.assign(n, 1);
    cc.resize(n);
    for (int i = 0; i < n; ++i) cc[i] = i;
  }
  virtual int find(int v) {
    // cerr << "find_2(" << v << ")\n";
    if (v == -1) return -1;
    // cerr << "cc_2[" << v << "] = " << cc[v] << "\n";
    return cc[v] == v ? v : cc[v] = find(cc[v]);
  }
  bool onion(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    cc[b] = a;
    return true;
  }
};

struct EnrichedDsu : Dsu {
  vector<int> par; // directed edges from the original graph
  Dsu * nxt;
  explicit EnrichedDsu(int n, Dsu * nxt) : Dsu(n), nxt(nxt) {
    par.assign(n, -1);
  }
  int find(int v) override {
    v = nxt->find(v);
    return cc[v] == v ? v : cc[v] = find(cc[v]);
  }
  int add_edge(int a, int b) {
    // return delta bridges after adding edge (a,b)
    a = nxt->find(a);
    b = nxt->find(b);
    if (a == b) return 0;
    int ca = find(a);
    int cb = find(b);
    if (ca != cb) {
      if (sz[a] < sz[b]) {
        swap(a, b);
        swap(ca, cb);
      }
      make_root(b);
      par[b] = cc[b] = a;
      sz[ca] += sz[cb];
      return 1;
    } else {
      return merge_path(a, b);
    }
  }
  void  make_root(int v) {
    // reverse the edges in the path v...find(v);
    v = nxt->find(v);
    int root = v;
    int child = -1;
    while (v != -1) {
      int p = nxt->find(par[v]);
      par[v] = child;
      cc[v] = root;
      child = v;
      v = p;
    }
    sz[root] = sz[child];
  }
  int merge_path(int a, int b) {
    // return delta bridges after adding an edge
    // limit the number of times an edge is merged
    // to do: compress each node v to nxt->find(v);
    vector<int> pa, pb;
    for (int i = a; i != -1; i = par[i]) { i = nxt->find(i); pa.push_back(i); }
    for (int i = b; i != -1; i = par[i]) { i = nxt->find(i); pb.push_back(i); }
    int lca = -1;
    while (!pa.empty() && !pb.empty() && pa.back() == pb.back()) {
      lca = pa.back();
      pa.pop_back();
      pb.pop_back();
    }
    assert(lca != -1);
    int ret = 0;
    for (int i : pa) {
      nxt->cc[i] = lca;
      ret -= 1; // nxt->onion(i, lca);
    }
    for (int i : pb) {
      nxt->cc[i] = lca;
      ret -= 1; // nxt->onion(i, lca);
    }
    return ret;
  }

// // COPY PASTE
// int merge_path (int a, int b) {
//     ++lca_iteration;
//     vector<int> path_a, path_b;
//     int lca = -1;
//     while (lca == -1) {
//         if (a != -1) {
//             a = nxt->find(a);
//             path_a.push_back(a);
//             if (last_visit[a] == lca_iteration){
//                 lca = a;
//                 break;
//                 }
//             last_visit[a] = lca_iteration;
//             a = par[a];
//         }
//         if (b != -1) {
//             b = nxt->find(b);
//             path_b.push_back(b);
//             if (last_visit[b] == lca_iteration){
//                 lca = b;
//                 break;
//                 }
//             last_visit[b] = lca_iteration;
//             b = par[b];
//         }
//
//     }
//     int ret = 0;
//     for (int v : path_a) {
//         nxt->cc[v] = lca;
//         if (v == lca)
//             break;
//         --ret;
//     }
//     for (int v : path_b) {
//         nxt->cc[v] = lca;
//         if (v == lca)
//             break;
//         --ret;
//     }
//     return ret;
// }
// // end COPY PASTE

};

int main() {
#ifdef LORENZO
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n; cin >> n;
  int m; cin >> m;
  int q; cin >> q;
  Dsu two(n);
  EnrichedDsu one(n, &two);
  int bridges = 0;
  for (int i = 0, a, b; i < m; ++i) {
    cin >> a >> b;
    --a, --b;
    bridges += one.add_edge(a, b);
    watch(bridges);
  }
  for (int i = 0, a, b; i < q; ++i) {
    cin >> a >> b;
    --a, --b;
    bridges += one.add_edge(a, b);
    cout << bridges << "\n";
    watch(bridges);
  }
}

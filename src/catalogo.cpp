#pragma GCC optimize ("O3")
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using LL = long long;
gp_hash_table<LL, int> mp;

void aggiungi(LL id) { ++mp[id]; }
void togli(LL id) { --mp[id]; }
int conta(LL id) { return mp[id]; }

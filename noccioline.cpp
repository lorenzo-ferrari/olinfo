#pragma GCC optimize ("O3")
#define abs(a) (((a) > 0) ? (a) : -(a))

int ContaOperazioni(int n, int k, int secchi[]) {
    int tot = n * k, deltaTot = 0;
    for (int i = 0; i < n; i++) {
        deltaTot += abs(k - secchi[i]);
        tot -= secchi[i];
    }
    return ((deltaTot - abs(tot)) >> 1) + abs(tot);
}
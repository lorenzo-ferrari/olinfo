#include <iostream>
#pragma GCC optimize("O3")
using namespace std;
#define F first
#define S second

typedef enum { OK, RISOLTO, IMPOSSIBILE } stato_t;

typedef struct {
    int domino1;
    int domino2;
} coppia_t;

const int INF = 1e9;
const int MAXH = 1e3;
const int MAXN = 5e6 + 5;

stato_t correggi(int n, int h[], coppia_t *scambio) {
	int l = -1, r = -1;
	int c[MAXN]{};
	int fine[MAXN]{};

	// 0 cade sempre
	for (int i = 1; i < n; i++) {
		if (i-1 + h[i-1] < n)
			fine[i-1 + h[i-1]]++;
        fine[i] += fine[i - 1];
		c[i] = i - fine[i];

		if (c[i] == 0 && l == -1) l = i;
		if (c[i] == 0) r = i;
	}

	if (l == -1) return OK;
    if (r - l + 1 >= MAXH) return IMPOSSIBILE;

	int nextOne[MAXN]; // 
	int lastOne[MAXN];

	lastOne[0] = -1;
	for (int i = 1; i < n; i++)
		lastOne[i] = (c[i] == 1) ? i : lastOne[i - 1];

	nextOne[n - 1] = n;
	for (int i = n - 2; i >= 0; i--)
		nextOne[i] = (c[i] == 1) ? i : nextOne[i + 1];

    // nota che tutti gli i  l <= i < r sono inutili da spostare avanti o indietro

    // muovi i < l AVANTI in modo che faccia cadere sia l che r, O(H^2)
    for (int i = max(0, r - MAXH + 1); i < l; i++) {
        for (int j = i + 1; j <= l; j++) {
            // guarda se scambiando i con j funziona -> guarda se i cade
            if (j + h[i] > r && h[i] > h[j] && nextOne[min(n, i + h[j])] > j) {
                scambio->domino1 = i;
                scambio->domino2 = j;
                return RISOLTO;
            }
        }
    }

    // muovi i >= r INDIETRO in modo che faccia cadere sia l che r, O(H^2)
    for (int i = min(n, l + MAXH) - 1; i >= r; i--) {
        for (int j = l - 1; j + h[i] > r; j--) {
            if (j + h[i] > lastOne[min(n, i + h[i]) - 1] || i + h[j] > lastOne[min(n, i + h[i]) - 1]) {
                scambio->domino1 = i;
                scambio->domino2 = j;
                return RISOLTO;
            }
        }
    }

    // O(N + H) ~ O(N)
    // fai vincoli "per usarne uno lungo i, devo scambiarlo con uno lungo v[i].F"
    pair<int, int> v[MAXH + 1];
    for (int i = 0; i <= MAXH; i++) v[i] = {INF, -1};
    for (int i = 0; i < n; i++) {
        v[h[i]] = min(v[h[i]], {max(0, lastOne[min(n, i + h[i]) - 1] - i + 1), i});
    }

    for (int i = MAXH - 1; i >= 0; i--) {
        v[i] = min(v[i], v[i + 1]);
    }

    for (int i = l - 1; i >= 0 && i > r - MAXH + 1; i--) {
        int req = r - i + 1; // lunghezza minima richiesta
        if (h[i] > v[req].F) {
            scambio->domino1 = i;
            scambio->domino2 = v[req].S;
            return RISOLTO;
        }
    }

    return IMPOSSIBILE;
}
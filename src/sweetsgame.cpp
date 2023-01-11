/*
 * https://training.olinfo.it/#/task/sweetsgame/statement
 *
 * ..X.X.X..
 * .X.X.X.X.
 * X.X.X.X.X
 * .X.X.X.X.
 * ..X.X.X..
 *
 */

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const vector<bitset<9>> cells {
    bitset<9>("001010100"),
    bitset<9>("010101010"),
    bitset<9>("101010101"),
    bitset<9>("010101010"),
    bitset<9>("001010100")
};

int di[3]{0, 1, 1};
int dj[3]{2, 1,-1};

vector<int> moves;

int tr(int i, int j) {
    assert(cells[i][j]);
    int cnt = 0;
    for (int ii = 0; ii <= i; ++ii) for (int jj = 0; jj < 9 && (ii != i || jj != j); ++jj) {
        cnt += cells[ii][jj];
    }
    assert(0 <= cnt && cnt <= 18);
    return cnt;
}

int main() {
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 9; ++j) {
        if (!cells[i][j]) continue;
        for (int k = 0; k < 3; ++k) {
            int ii = i, jj = j, mask = 0;
            do {
                mask |= (1 << tr(ii, jj));
                moves.push_back(mask);
                ii += di[k], jj += dj[k];
            } while(0 <= ii && ii < 5 && 0 <= jj && jj < 9 && cells[ii][jj]);
        }
    }
    sort(begin(moves), end(moves));
    moves.resize(unique(begin(moves), end(moves)) - begin(moves));
    static bool state[1 << 19]{};
    for (int mask = 1; mask < (1 << 19); ++mask) {
        for (int move : moves) {
            if ((mask | move) == mask && !state[mask ^ move]) {
                state[mask] = true;
                break;
            }
        }
    }
#ifdef EVAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int mask = 0;
    int cnt = 0;
    for (int i = 0; i < 5; ++i) for (int j = 0; j < 9; ++j) {
        if (cells[i][j]) {
            char c; cin >> c;
            if (c == 'O') {
                mask |= (1 << cnt);
            }
            ++cnt;
        }
    }
    if (state[mask]) {
        cout << "Karlsson\n";
    } else {
        cout << "Lillebror\n";
    }
}

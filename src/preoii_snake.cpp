#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int riga;
    int colonna;
} cella_t;
bool operator ==(cella_t a, cella_t b) {
  return a.riga == b.riga && a.colonna == b.colonna;
}
bool operator !=(cella_t a, cella_t b) {
  return !(a == b);
}

typedef enum
{
  SOPRA,
  SOTTO,
  DESTRA,
  SINISTRA
} direzione_t;

cella_t posizione_mela();

void muovi(direzione_t);

vector<vector<cella_t>> nxt;

void fill_nxt(int R, int C) {
  nxt.resize(R, vector<cella_t>(C));
  if (R % 2 == 0) {
/*
4 5
>>>>v
^v<<<
^>>>v
^<<<<
*/
    nxt[0][0] = {0, 1};
    for (int r = 1; r < R; ++r) nxt[r][0] = {r-1, 0};
    for (int r = 0; r < R; ++r) {
      if (r & 1) {
        if (r != R-1) nxt[r][1] = {r+1, 1};
        else nxt[r][1] = {R-1, 0};
        for (int c = C-1; c > 1; --c) nxt[r][c] = {r, c-1};
      } else {
        nxt[r][C-1] = {r+1, C-1};
        for (int c = C-2; c > 0; --c) nxt[r][c] = {r, c+1};
      }
    }
  } else if (C % 2 == 0) {
/*
5 4
>>>v
^v<v
^v^v
^v^v
^<^<
*/
    nxt[0][C-1] = {1, C-1};
    for (int c = 0; c < C-1; ++c) nxt[0][c] = {0, c+1};
    for (int c = 0; c < C; ++c) {
      if (c & 1) {
        nxt[R-1][c] = {R-1, c-1};
        for (int r = 1; r < R-1; ++r) nxt[r][c] = {r+1, c};
      } else {
        if (c != 0) nxt[1][c] = {1, c-1};
        else nxt[1][c] = {0, 0};
        for (int r = 2; r < R; ++r) nxt[r][c] = {r-1, c};
      }
    }
  }
}

void gioca(int R, int C) {
  fill_nxt(R, C);
  cella_t cur {0, 0};
  for (int len = 1; len < R*C; ++len) {
    cella_t p = posizione_mela();
    while (cur != p) {
      auto tmp = nxt[cur.riga][cur.colonna];
      int dr = tmp.riga - cur.riga;
      int dc = tmp.colonna - cur.colonna;
      if (dr == -1) muovi(SOPRA);
      if (dr == 1) muovi(SOTTO);
      if (dc == -1) muovi(SINISTRA);
      if (dc == 1) muovi(DESTRA);
      cur = tmp;
    }
  }
}
